"""Create/join menu, host-only settings, role errors and synchronized avatar selection."""
import argparse, concurrent.futures, hashlib, json, os, shlex, subprocess
from pathlib import Path
from emulator import ROOT, symbols

p=argparse.ArgumentParser(description=__doc__)
p.add_argument('--native',action='store_true')
p.add_argument('--jobs',type=int,default=4)
p.add_argument('--scenario',type=int,choices=range(5))
p.add_argument('--report',type=Path,default=ROOT/'build/qa/link-roles.json')
a=p.parse_args();build=Path(os.environ['MGBA_BUILD']).resolve();flags=[]
for line in (build/'CMakeFiles/mgba.dir/flags.make').read_text().splitlines():
 if line.startswith(('C_DEFINES =','C_INCLUDES =')):flags+=shlex.split(line.split('=',1)[1])
 if line.startswith('C_FLAGS ='):flags += [f for f in shlex.split(line.split('=',1)[1]) if f.startswith('-D')]
if a.native:flags+=['-DLINK_NATIVE']
exe=ROOT/'build/qa'/('roles-'+a.report.stem);exe.parent.mkdir(parents=True,exist_ok=True)
subprocess.run(['cc',*flags,str(ROOT/'scripts/test-link-roles.c'),'-L'+str(build),'-Wl,-rpath,'+str(build),'-lmgba','-o',str(exe)],check=True)
data=(ROOT/'build/gba/pole.gba').read_bytes();sha=hashlib.sha256(data).hexdigest()
rom=ROOT/'build/qa/link-chaos-roms'/f'{sha}.gba';rom.parent.mkdir(parents=True,exist_ok=True)
if not rom.exists():
 temporary=rom.with_suffix(f'.{os.getpid()}.tmp');temporary.write_bytes(data);os.replace(temporary,rom)
s=symbols();s['prefs']=s.get('prefs',s.get('prefs.0'))
cases=[(n,scenario,graphics) for n in (2,3) for scenario in range(5) for graphics in ((0,1) if scenario==0 else (1,))]
if a.scenario is not None:cases=[case for case in cases if case[1]==a.scenario]
def run(case):
 cmd=[str(exe),str(rom),*map(str,case),*[hex(s[k]) for k in ('game','mp','prefs','avatars','link_create','link_avatar_edit','link_role_error')]]
 try:
  r=subprocess.run(cmd,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True,timeout=180)
  out=r.stdout;code=r.returncode
 except subprocess.TimeoutExpired as e:
  out=str(e.stdout);code=124
 print('PASS' if code==0 else 'FAIL',case,flush=True)
 return dict(count=case[0],scenario=case[1],graphics=case[2],passed=code==0,output=out)
with concurrent.futures.ThreadPoolExecutor(max_workers=a.jobs) as pool:results=list(pool.map(run,cases))
a.report.parent.mkdir(parents=True,exist_ok=True)
a.report.write_text(json.dumps(dict(rom_sha256=sha,native=a.native,tests=results),indent=2)+'\n')
print(f'{sum(t["passed"] for t in results)}/{len(results)} passed')
raise SystemExit(any(not t['passed'] for t in results))
