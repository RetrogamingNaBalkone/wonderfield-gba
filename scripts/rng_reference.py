"""DOS spin model from analysis/listing.asm, independent counter simulation."""
def dos_spin(seed, sector):
 def random_n(n):
  nonlocal seed
  seed=(seed*134775813+1)&0xffffffff
  return (seed>>16)%n
 for _ in range(6):random_n(100)  # 0936 -> 08e4 noise
 phase=((12-sector)*2)&31
 limit=random_n(20)+10
 for speed in (4,3,2,1):
  for counter in range(limit+1):
   if counter%(5-speed)==0:phase=(phase+1)&31
  limit=random_n(10)+5
 if phase&1:phase=(phase+1)&31
 return (28-phase//2)%16,seed
