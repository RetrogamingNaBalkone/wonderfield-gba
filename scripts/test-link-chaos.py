"""Run deterministic adversarial mGBA cable scenarios, retaining each seed/log."""
import argparse, concurrent.futures, hashlib, json, os, shlex, subprocess, time
from pathlib import Path
from emulator import ROOT, symbols
CASE_NAMES={0:'startup order',1:'cancel waiting and retry',2:'cancel lobby and retry',3:'break cable chain',4:'pause SD-ready',5:'pause serial IRQ',6:'completed-transfer hardware error',7:'corrupt snapshot',8:'suppress first IRQ',9:'unplug/replug',10:'reset console',11:'hot-add third console',12:'random buttons and IRQ jitter',13:'timer wrap',14:'corrupt build fingerprint',15:'cancel initial packet',16:'ambiguous initial SI',17:'repeated mixed failures',18:'replay HEADER payload over START',19:'corrupt child reply',20:'persistent payload corruption'}
p=argparse.ArgumentParser(description=__doc__,epilog='Cases: '+', '.join(f'{k}={v}' for k,v in CASE_NAMES.items()))
p.add_argument('--jobs',type=int,default=3)
p.add_argument('--case',type=int,choices=CASE_NAMES)
p.add_argument('--count',type=int,choices=(2,3),default=2)
p.add_argument('--seed',type=int,default=1)
p.add_argument('--target',type=int,default=1)
p.add_argument('--phase',type=int,default=2)
p.add_argument('--amount',type=int,default=60)
p.add_argument('--rom',type=Path,default=ROOT/'build/gba/pole.gba')
p.add_argument('--elf',type=Path,default=ROOT/'build/gba/pole.elf')
p.add_argument('--report',type=Path,default=ROOT/'build/qa/link-chaos.json')
p.add_argument('--matrix', choices=('full','startup','wrap','stateful','bootstrap','crc'), default='full')
a=p.parse_args()
build=Path(os.environ['MGBA_BUILD']).resolve();flags=[]
for line in (build/'CMakeFiles/mgba.dir/flags.make').read_text().splitlines():
 if line.startswith(('C_DEFINES =','C_INCLUDES =')): flags+=shlex.split(line.split('=',1)[1])
 if line.startswith('C_FLAGS ='):flags += [f for f in shlex.split(line.split('=',1)[1]) if f.startswith('-D')]
exe=ROOT/'build/qa'/('test-link-chaos-'+a.report.stem);exe.parent.mkdir(parents=True,exist_ok=True)
subprocess.run(['cc',*flags,str(ROOT/'scripts/test-link-chaos.c'),'-L'+str(build),'-Wl,-rpath,'+str(build),'-lmgba','-o',str(exe)],check=True)
s=symbols(a.elf);s['prefs']=s.get('prefs',s.get('prefs.0'))
for key in ('link_create','link_avatar_edit','link_name_edit'):
 if key in s:os.environ[key.upper()+'_ADDR']=hex(s[key])
 else:os.environ.pop(key.upper()+'_ADDR',None)
rom_bytes=a.rom.read_bytes();rom_hash=hashlib.sha256(rom_bytes).hexdigest()
frozen_rom=ROOT/'build/qa/link-chaos-roms'/f'{rom_hash}.gba'
frozen_rom.parent.mkdir(parents=True,exist_ok=True)
if not frozen_rom.exists():frozen_rom.write_bytes(rom_bytes)
addresses=[hex(s[k]) for k in ('game','mp','prefs','avatars','link_stage','link_error_stage','link_active','match','link_error_received','link_error_expected')]
cases=[]
def add(n,k,seed=1,target=1,phase=2,amount=60):cases.append(dict(count=n,kind=k,seed=seed,target=target,phase=phase,amount=amount))
if a.case is not None:add(a.count,a.case,a.seed,a.target,a.phase,a.amount)
else:
 for n in (2,3):
  for seed in range(1,3 if n==2 else 7):
   for duration in ((0,1,60,1800,2400) if n==2 else (1,2400)):add(n,0,seed,amount=duration)
  for node in range(n):
   add(n,16,target=node)
   for k in (1,2,10):add(n,k,target=node,amount=2400 if k==1 else 60)
   for phase in (2,4,6,7):
    for k in (3,5):add(n,k,target=node,phase=phase,amount=60)
   for duration in (119,120,121,180):add(n,5,target=node,amount=duration)
   for phase in (2,3,5,6,7):add(n,15,target=node,phase=phase)
   add(n,8,target=node)
   add(n,8,target=node,phase=1)
  for phase in (2,4,6,7):
   for duration in (1,60,119,120,121,180):add(n,4,phase=phase,amount=duration)
   add(n,6,phase=phase)
  add(n,7,phase=6);add(n,14,phase=3);add(n,20,phase=3)
  for node in range(1,n):
   add(n,18,target=node,amount=1)
   for stage in (2,3,6,7):add(n,19,target=node,phase=stage)
  for duration in (60,180):add(n,13,amount=duration)
  for seed in range(1,9):add(n,12,seed=seed,amount=150)
  for seed in (1,17,123,0xC0FFEE):add(n,17,seed=seed,amount=6)
 add(3,11,target=2)
 if a.matrix=='startup':cases=[c for c in cases if c['kind']==0]
 if a.matrix=='wrap':cases=[c for c in cases if c['kind']==13]
 if a.matrix=='stateful':cases=[c for c in cases if c['kind']==17]
 if a.matrix=='crc':cases=[c for c in cases if c['kind'] in (7,14,18,19,20)]
 if a.matrix=='bootstrap':cases=[c for c in cases if c['kind']==8 and c['phase']==1]
logs=ROOT/'build/qa/link-chaos-logs'/a.report.stem;logs.mkdir(parents=True,exist_ok=True)
def run(item):
 idx,case=item;cmd=[str(exe),str(frozen_rom),*[str(case[k]) for k in ('count','kind','seed','target','phase','amount')],*addresses]
 started=time.monotonic()
 try:
  result=subprocess.run(cmd,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True,timeout=180)
  out=result.stdout;code=result.returncode
 except subprocess.TimeoutExpired as e:
  out=(e.stdout or b'').decode() if isinstance(e.stdout,bytes) else e.stdout or '';out+='\nPROCESS TIMEOUT';code=124
 path=logs/f'{idx:03d}.log';path.write_text(out)
 entry={**case,'name':CASE_NAMES[case['kind']],'passed':code==0,'exit_code':code,'seconds':round(time.monotonic()-started,2),'log':str(path.relative_to(ROOT)),'output':out}
 print(('PASS' if code==0 else 'FAIL'),idx,case,flush=True)
 return idx,entry
results=[None]*len(cases)
with concurrent.futures.ThreadPoolExecutor(max_workers=a.jobs) as pool:
 for idx,result in pool.map(run,enumerate(cases)):
  results[idx]=result
  a.report.parent.mkdir(parents=True,exist_ok=True)
  a.report.write_text(json.dumps({'rom_sha256':rom_hash,'tests':[x for x in results if x is not None]},indent=2)+'\n')
failed=[r for r in results if not r['passed']]
print(f'{len(results)-len(failed)}/{len(results)} passed; report: {a.report}')
raise SystemExit(bool(failed))
