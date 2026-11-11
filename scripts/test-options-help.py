"""ROM UI: contextual help browses alternatives without changing settings."""
import hashlib,json,runpy,struct
from emulator import Emulator,ROOT
m=runpy.run_path(str(ROOT/'scripts/test-multiplayer.py'))
tap,read=m['tap'],m['read']
checks=[]
for cable in (False,True):
 e=Emulator();m['options'](e,2,cable)
 assert e.state()[3]==32
 e.screenshot('options-help-menu.png')
 for setting in (3,4,0,1,2,5):
  tap(e,5) # From Start to dictionary, then subsequent settings.
  before=read(e,'prefs',24);values=struct.unpack('<6i',before)
  assert values[3]==setting
  current=values[setting if setting<3 else 4 if setting==3 else 5]
  tap(e,2);assert e.state()[3]==37
  assert struct.unpack('<i',read(e,'option_help_value',4))[0]==current
  count=2 if setting<3 else 3 if setting==3 else 1
  for step in range(count):
   if not cable:e.screenshot(f'options-help-{setting}-{step}.png')
   tap(e,7)
   expected=(current+step+1)%count if count>1 else current
   assert struct.unpack('<i',read(e,'option_help_value',4))[0]==expected
   assert read(e,'prefs',24)==before
  tap(e,6)
  assert struct.unpack('<i',read(e,'option_help_value',4))[0]==((current-1)%count if count>1 else current)
  for close in (0,8,2):
   tap(e,close);assert e.state()[3]==32 and read(e,'prefs',24)==before
   tap(e,2);assert e.state()[3]==37
   assert struct.unpack('<i',read(e,'option_help_value',4))[0]==current
  tap(e,0)
 checks.append({'cable':cable,'all_settings_browsed_without_mutation':True,'reopen_on_selected_value':True,'all_close_buttons':True})
 # Start still opens player entry after closing its help.
 tap(e,8);assert e.state()[3]==27
 e.close()
report={'rom_sha256':hashlib.sha256((ROOT/'build/gba/pole.gba').read_bytes()).hexdigest(),'checks':checks}
(ROOT/'docs/verification/options-help-tests.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps(report,indent=2))
