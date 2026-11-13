"""Raw echo diagnostic: menu, baud/pacing, delayed start, faults and restart."""
import argparse, concurrent.futures, hashlib, json, os, shlex, subprocess
from pathlib import Path
from emulator import ROOT, symbols

p=argparse.ArgumentParser(description=__doc__)
p.add_argument('--native',action='store_true')
p.add_argument('--jobs',type=int,default=4)
p.add_argument('--smoke',action='store_true',help='four boundary configurations after UI-only edits')
p.add_argument('--report',type=Path,default=ROOT/'build/qa/link-diagnostic.json')
a=p.parse_args();build=Path(os.environ['MGBA_BUILD']).resolve();flags=[]
for line in (build/'CMakeFiles/mgba.dir/flags.make').read_text().splitlines():
 if line.startswith(('C_DEFINES =','C_INCLUDES =')):flags+=shlex.split(line.split('=',1)[1])
 if line.startswith('C_FLAGS ='):flags += [f for f in shlex.split(line.split('=',1)[1]) if f.startswith('-D')]
if a.native:flags+=['-DLINK_NATIVE']
exe=ROOT/'build/qa'/('diagnostic-'+a.report.stem);exe.parent.mkdir(parents=True,exist_ok=True)
subprocess.run(['cc',*flags,str(ROOT/'scripts/test-link-diagnostic.c'),'-L'+str(build),'-Wl,-rpath,'+str(build),'-lmgba','-o',str(exe)],check=True)
data=(ROOT/'build/gba/pole.gba').read_bytes();sha=hashlib.sha256(data).hexdigest()
rom=ROOT/'build/qa/link-chaos-roms'/f'{sha}.gba';rom.parent.mkdir(parents=True,exist_ok=True)
if not rom.exists():
 temporary=rom.with_suffix(f'.{os.getpid()}.tmp');temporary.write_bytes(data);os.replace(temporary,rom)
s=symbols();cases=[(n,baud,pace,first) for n in (2,3) for baud in range(4) for pace in (0,3) for first in (0,n-1)]
if a.smoke:cases=[(2,3,0,0),(2,0,3,1),(3,3,0,2),(3,0,3,0)]
def run(case):
 cmd=[str(exe),str(rom),*map(str,case),hex(s['game']),hex(s['link_test'])]
 try:
  r=subprocess.run(cmd,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True,timeout=180)
  out=r.stdout;code=r.returncode
 except subprocess.TimeoutExpired as e:
  out=str(e.stdout);code=124
 print('PASS' if code==0 else 'FAIL',case,flush=True)
 return dict(count=case[0],baud=case[1],pace=case[2],first=case[3],passed=code==0,output=out)
with concurrent.futures.ThreadPoolExecutor(max_workers=a.jobs) as pool:results=list(pool.map(run,cases))
a.report.parent.mkdir(parents=True,exist_ok=True)
a.report.write_text(json.dumps(dict(rom_sha256=sha,native=a.native,tests=results),indent=2)+'\n')
print(f'{sum(t["passed"] for t in results)}/{len(results)} passed')
raise SystemExit(any(not t['passed'] for t in results))
