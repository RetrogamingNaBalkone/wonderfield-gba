/* Exercise the production codec, extracted verbatim by test-link-codec.py. */
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
typedef uint8_t u8;
typedef uint16_t u16;
static struct {u8 before[16],data[CODEC_SNAPSHOT_SIZE],after[16];} guarded;
#define link_snapshot guarded.data
static u16 link_previous[(CODEC_SNAPSHOT_SIZE+1)/2];
#include "link-codec-under-test.inc"
static uint32_t seed=1;
static unsigned random32(void){seed^=seed<<13;seed^=seed>>17;seed^=seed<<5;return seed;}
static void guards(void){
 for(unsigned i=0;i<16;i++){assert(guarded.before[i]==0xa5);assert(guarded.after[i]==0x5a);}
}
int main(void){
 u8 expected[CODEC_SNAPSHOT_SIZE],saved[sizeof link_delta];
 memset(guarded.before,0xa5,16);memset(guarded.after,0x5a,16);
 for(unsigned trial=0;trial<2000;trial++){
  u8*base=(u8*)link_previous;
  for(unsigned i=0;i<sizeof link_snapshot;i++){
   base[i]=random32();
   unsigned change=trial%8==0?0:trial%8==1?1:trial%8==2?(i&1):random32()%(trial%29+1)==0;
   expected[i]=link_snapshot[i]=base[i]^(change?(random32()%255)+1:0);
  }
  unsigned length=link_encode_delta();assert(length&&length<=sizeof link_delta);guards();
  memcpy(saved,link_delta,length);memcpy(link_snapshot,base,sizeof link_snapshot);
  assert(link_decode_delta(length));assert(!memcmp(link_snapshot,expected,sizeof expected));guards();
  if(trial<32)for(unsigned cut=0;cut<length;cut++){
   memcpy(link_snapshot,base,sizeof link_snapshot);memcpy(link_delta,saved,length);
   assert(!link_decode_delta(cut));guards();
  }
 }
 for(unsigned trial=0;trial<20000;trial++){
  unsigned length=random32()%(sizeof link_delta+1);
  for(unsigned i=0;i<length;i++)link_delta[i]=random32();
  (void)link_decode_delta(length);guards();
 }
 assert(!link_decode_delta(sizeof link_delta+1));
 puts("PASS: round trips, truncated packets, malformed runs, bounds and guards");
}
