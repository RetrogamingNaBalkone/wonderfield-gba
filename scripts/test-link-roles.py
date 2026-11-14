"""Create/join menu, first-creator election, host-only settings and synchronized profiles."""
import argparse, concurrent.futures, hashlib, json, os, shlex, subprocess
from pathlib import Path
from emulator import ROOT, symbols

p=argparse.ArgumentParser(description=__doc__)
p.add_argument('--animations',action='store_true')
p.add_argument('--benchmark',action='store_true')
p.add_argument('--consoles',type=int,choices=(2,3))
p.add_argument('--graphics',type=int,choices=(0,1))
p.add_argument('--screenshots',type=Path)
p.add_argument('--native',action='store_true')
p.add_argument('--jobs',type=int,default=4)
p.add_argument('--scenario',type=int,choices=range(10))
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
for key in ('link_profile_pending','link_name_edit','link_name_pos','link_config_mode','link_setup_ready','link_host_ready','link_join_prompt','scene','link_events'):
 os.environ['ROLE_'+key.removeprefix('link_').upper()]=hex(s[key])
for key in ('scene','cash','link_events','video_ticks','message1','message2','message_tokens'):
 os.environ['LINK_'+key.removeprefix('link_').upper()+'_ADDR']=hex(s[key])
os.environ['ROLE_STAGE']=hex(s['link_stage'])
if a.animations:os.environ['LINK_ANIMATIONS']='1'
if a.benchmark:os.environ['LINK_BENCHMARK']='1'
cases=[(n,scenario,graphics) for n in (2,3) for scenario in range(10) for graphics in ((0,1) if scenario<=2 else (1,))]
if a.consoles is not None:cases=[case for case in cases if case[0]==a.consoles]
if a.graphics is not None:cases=[case for case in cases if case[2]==a.graphics]
if a.screenshots:
 a.screenshots.mkdir(parents=True,exist_ok=True);os.environ['ROLE_SCREENSHOTS']=str(a.screenshots.resolve())
if a.scenario is not None:cases=[case for case in cases if case[1]==a.scenario]
def run(case):
 cmd=[str(exe),str(rom),*map(str,case),*[hex(s[k]) for k in ('game','mp','prefs','avatars','link_create','link_avatar_edit','link_host_device')]]
 try:
  r=subprocess.run(cmd,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True,timeout=180)
  out=r.stdout;code=r.returncode
 except subprocess.TimeoutExpired as e:
  out=str(e.stdout);code=124
 print('PASS' if code==0 else 'FAIL',case,flush=True)
 return dict(host_device=0 if case[1] in (0,4) else case[0]-1 if case[1]==2 else 1,count=case[0],scenario=case[1],graphics=case[2],passed=code==0,output=out)
with concurrent.futures.ThreadPoolExecutor(max_workers=a.jobs) as pool:results=list(pool.map(run,cases))
a.report.parent.mkdir(parents=True,exist_ok=True)
a.report.write_text(json.dumps(dict(rom_sha256=sha,native=a.native,tests=results),indent=2)+'\n')
print(f'{sum(t["passed"] for t in results)}/{len(results)} passed')
raise SystemExit(any(not t['passed'] for t in results))
