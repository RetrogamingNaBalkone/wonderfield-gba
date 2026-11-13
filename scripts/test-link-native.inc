/* Single-thread frontend scheduling for mGBA's unmodified lockstep driver.
 * Cycle credits/waits follow the contract used by MultiplayerController.cpp;
 * serial registers, pin states, transfers and IRQs are owned by libmgba. */
#include <mgba/internal/gba/sio/lockstep.h>
static struct GBASIOLockstep native_bus;
static struct GBASIOLockstepNode native_nodes[3];
static int native_awake[3],native_credits[3];
static unsigned native_wait_mask;
static int native_removed=-1;
static bool native_signal(struct mLockstep*b,unsigned mask){
 (void)b;native_wait_mask&=~mask;
 if(!native_wait_mask&&!native_awake[0]){native_awake[0]=1;return true;}return false;
}
static bool native_wait(struct mLockstep*b,unsigned mask){
 if(b->transferActive==TRANSFER_STARTED){transfers++;record_transfer();}
 int was_awake=native_awake[0];native_wait_mask|=mask;native_awake[0]=0;return was_awake;
}
static void native_add(struct mLockstep*b,int id,int32_t cycles){
 (void)b;assert(cycles>=0);
 if(id){native_credits[id]+=cycles;return;}
 for(int i=1;i<count;i++)if(i!=native_removed&&g[i]->sio.mode<=SIO_MULTI){
  native_credits[i]+=cycles;
  if(!native_awake[i])native_nodes[i].nextEvent+=native_credits[i];
  native_awake[i]=1;
 }
}
static int32_t native_use(struct mLockstep*b,int id,int32_t cycles){
 (void)b;native_credits[id]-=cycles;if(native_credits[id]<=0)native_awake[id]=0;return native_credits[id];
}
static int32_t native_unused(struct mLockstep*b,int id){(void)b;return native_credits[id];}
static void native_unload(struct mLockstep*b,int id){
 if(id){native_credits[id]=0;native_awake[id]=1;native_signal(b,1u<<id);}
 else for(int i=1;i<count;i++){
  native_credits[i]+=native_nodes[0].eventDiff;
  if(!native_awake[i])native_nodes[i].nextEvent+=native_credits[i];
  native_awake[i]=1;
 }
}
static void install_driver(int i){
 if(!i){
  mLockstepInit(&native_bus.d);GBASIOLockstepInit(&native_bus);
  native_bus.d.signal=native_signal;native_bus.d.wait=native_wait;
  native_bus.d.addCycles=native_add;native_bus.d.useCycles=native_use;
  native_bus.d.unusedCycles=native_unused;native_bus.d.unload=native_unload;
 }
 native_awake[i]=1;GBASIOLockstepNodeCreate(&native_nodes[i]);
 assert(GBASIOLockstepAttachNode(&native_bus,&native_nodes[i]));
 GBASIOSetDriver(&g[i]->sio,&native_nodes[i].d,SIO_MULTI);
}
static void native_run(unsigned frames){
 if(disconnected>=0&&native_removed<0){
  native_removed=disconnected;
  GBASIOSetDriver(&g[disconnected]->sio,NULL,SIO_MULTI);
  GBASIOLockstepDetachNode(&native_bus,&native_nodes[disconnected]);
  native_awake[disconnected]=1;
 }
 uint64_t end=cable_clock(0)+(uint64_t)frames*time_scale*280896;
 while(cable_clock(0)<end){
  uint64_t min=UINT64_MAX;int who=-1;
  for(int i=0;i<count;i++)if(native_awake[i]&&cable_clock(i)<min){who=i;min=cable_clock(i);}
  assert(who>=0);c[who]->runLoop(c[who]);
 }
}
