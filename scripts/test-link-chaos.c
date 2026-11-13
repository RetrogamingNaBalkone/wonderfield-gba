/* Deterministic adversarial ROM tests; reuse the same mGBA cable model. */
#define main link_regression_main
#include "test-link.c"
#undef main
static uint32_t prefs_addr,avatars_addr,stage_addr,error_addr,active_addr,match_addr;
static unsigned seed,target,phase,amount,fired,kind,selected_word;
static uint8_t sram_before[3][128];
static int success;
static unsigned random32(void){seed^=seed<<13;seed^=seed>>17;seed^=seed<<5;return seed;}
static void diagnostic(void){
 if(success)return;
 fprintf(stderr,"DIAG kind=%u seed=%u target=%u phase=%u amount=%u transfers=%d fired=%u\n",kind,seed,target,phase,amount,transfers,fired);
 for(int i=0;i<count;i++)if(c[i])fprintf(stderr,"device %d mode=%u stage=%u error=%u active=%u SIOCNT=%04x\n",i,rd(i,game_addr+12),rd(i,stage_addr),rd(i,error_addr),rd(i,active_addr),g[i]->sio.siocnt);
}
static void keys(int i,unsigned k,unsigned frames){c[i]->setKeys(c[i],k);run(frames);c[i]->setKeys(c[i],0);run(12);}
static void records(void){for(int i=0;i<count;i++)for(int j=0;j<128;j++)assert(c[i]->busRead8(c[i],0x0e000000+j)==sram_before[i][j]);}
static void no_errors(void){for(int i=0;i<count;i++)assert(rd(i,game_addr+12)!=31);}
static void avatars(void){
 for(int i=0;i<count;i++){
  assert(!rd(i,active_addr));
  for(int option=0;option<3;option++)wr(i,prefs_addr+option*4,1);
  wr(i,prefs_addr+16,0);wr(i,prefs_addr+20,3);wr(i,avatars_addr+8,i);
  wr(i,mp_addr,2);wr(i,mp_addr+4,1);wr(i,mp_addr+16,2);
  wr(i,game_addr+12,27);wr(i,game_addr+80*4,1);wr(i,game_addr+88*4,'A'+i);
  c[i]->setKeys(c[i],8);
 }
 run(20);for(int i=0;i<count;i++)c[i]->setKeys(c[i],0);run(20);
 for(int i=0;i<count;i++)assert(rd(i,game_addr+12)==33);
}
static int synced(int n){
 for(int i=0;i<n;i++){
  if(rd(i,game_addr+12)!=30||rd(i,mp_addr)!=(unsigned)n)return 0;
  for(int j=0;j<n;j++)if(c[i]->busRead8(c[i],mp_addr+28+((j+2)%3)*11)!='A'+j)return 0;
 }
 return 1;
}
static void lobby(int n){for(int t=0;t<400&&!synced(n);t++)run(1);assert(synced(n));run(12);no_errors();records();}
static void join_all(void){for(int i=0;i<count;i++)c[i]->setKeys(c[i],1);run(20);for(int i=0;i<count;i++)c[i]->setKeys(c[i],0);lobby(count);}
static void start(void){
 keys(0,8,20);run(160);
 for(int i=0;i<count;i++){assert(rd(i,active_addr));assert(rd(i,game_addr+12)!=30);assert(rd(i,game_addr+12)!=31);assert(rd(i,game_addr+24)==rd(0,game_addr+24));}
}
static void errors(int except,unsigned frames){
 for(unsigned t=0;t<frames;t++){
  int done=1;for(int i=0;i<count;i++)if(i!=except&&rd(i,game_addr+12)!=31)done=0;
  if(done){records();return;}run(1);
 }
 assert(!"error propagation exceeded deadline");
}
static void retry(void){
 disconnected=-1;ready_block=irq_block_mask=0;transfer_hook=0;receive_hook=0;
 for(int i=0;i<count;i++)c[i]->setKeys(c[i],2);
 run(24);for(int i=0;i<count;i++)c[i]->setKeys(c[i],0);run(24);
 for(int i=0;i<count;i++)assert(!rd(i,active_addr));
 avatars();join_all();start();records();
}
static void trigger(void){
 if(fired||rd(0,stage_addr)!=phase)return;
 fired=1;
 if(kind==3||kind==9)disconnected=target;
 if(kind==4||kind==13)ready_block=1;
 if(kind==5||kind==8)irq_block_mask=1u<<target;
 if(kind==15)c[target]->setKeys(c[target],2);
}
static void corrupt(int i){
 if((unsigned)i!=target||rd(0,stage_addr)!=phase)return;
 if(kind==6){if(!fired){g[i]->sio.siocnt|=64;fired=1;}return;}
 unsigned word=g[i]->memory.io[REG_SIOMULTI0/2];
 if(!fired&&(word&0xfd00)==0xa000){selected_word=word;fired=1;}
 if(fired==1&&word==selected_word)g[i]->memory.io[REG_SIOMULTI0/2]^=1;
 if(fired==1&&(word&0xff00)==((selected_word&0xff00)|0x100))fired=2;
}
static void arm(void){
 fired=0;
 if(kind==6||kind==7||kind==14)receive_hook=corrupt;else transfer_hook=trigger;
 for(int t=0;t<600&&!fired;t++)run(1);
 assert(fired);
}
static void release_irq(void){
 irq_block_mask=0;
 if(g[target]->sio.mode==SIO_MULTI&&!(g[target]->sio.siocnt&128))GBARaiseIRQ(g[target],GBA_IRQ_SIO,0);
}
int main(int argc,char**argv){
 assert(argc==16);atexit(diagnostic);mLogSetDefaultLogger(&logger);
 count=atoi(argv[2]);kind=atoi(argv[3]);seed=strtoul(argv[4],0,0);target=atoi(argv[5]);phase=atoi(argv[6]);amount=atoi(argv[7]);
 game_addr=strtoul(argv[8],0,16);mp_addr=strtoul(argv[9],0,16);prefs_addr=strtoul(argv[10],0,16);avatars_addr=strtoul(argv[11],0,16);stage_addr=strtoul(argv[12],0,16);error_addr=strtoul(argv[13],0,16);active_addr=strtoul(argv[14],0,16);match_addr=strtoul(argv[15],0,16);
 assert(count>=2&&count<=3&&target<(unsigned)count&&seed);
 for(int i=0;i<count;i++){
  c[i]=mCoreFind(argv[1]);assert(c[i]&&c[i]->init(c[i]));mCoreInitConfig(c[i],NULL);
  mCoreConfigSetDefaultIntValue(&c[i]->config,"useBios",0);mCoreConfigSetDefaultIntValue(&c[i]->config,"skipBios",1);mCoreConfigSetDefaultValue(&c[i]->config,"idleOptimization","ignore");mCoreLoadConfig(c[i]);
  c[i]->setVideoBuffer(c[i],calloc(240*160,sizeof(color_t)),240);assert(mCoreLoadFile(c[i],argv[1]));c[i]->reset(c[i]);g[i]=c[i]->board;
  nodes[i].id=i;nodes[i].d.init=yes;nodes[i].d.deinit=nothing;nodes[i].d.load=yes;nodes[i].d.unload=yes;nodes[i].d.writeRegister=cable_write;GBASIOSetDriver(&g[i]->sio,&nodes[i].d,SIO_MULTI);
 }
 run(100);for(int i=0;i<count;i++)for(int j=0;j<128;j++)sram_before[i][j]=c[i]->busRead8(c[i],0x0e000000+j);
 if(kind==16)initial_role_mask=1u<<target;
 avatars();
 if(kind==16){
  keys(target,1,12);run(60);for(int i=0;i<count;i++)if((unsigned)i!=target)keys(i,1,12);
  lobby(count);start();
 }else if(kind==0){
  static const int permutations[6][3]={{0,1,2},{0,2,1},{1,0,2},{1,2,0},{2,0,1},{2,1,0}};
  int order[3];for(int i=0;i<count;i++)order[i]=count==2?(i+(seed-1)%2)%2:permutations[(seed-1)%6][i];
  printf("ORDER");for(int i=0;i<count;i++)printf(" %d",order[i]);puts("");
  for(int j=0;j<count;j++){keys(order[j],1,12);if(j+1<count){run(amount);assert(rd(order[j],game_addr+12)==30);assert(!transfers);}}
  lobby(count);start();
 }else if(kind==1){
  for(int attempt=0;attempt<3;attempt++){
   printf("CANCEL attempt %d mode before A %u\n",attempt,rd(target,game_addr+12));fflush(stdout);
   keys(target,1,12);run(amount);assert(rd(target,game_addr+12)==30);
   keys(target,2,12);assert(rd(target,game_addr+12)==26);assert(!rd(target,active_addr));
   /* Re-enter through the existing name/avatar handlers. */
   wr(target,mp_addr,2);wr(target,mp_addr+4,1);wr(target,mp_addr+16,2);wr(target,game_addr+12,27);wr(target,game_addr+80*4,1);wr(target,game_addr+88*4,'A'+target);
   keys(target,8,20);assert(rd(target,game_addr+12)==33);
  }
  join_all();start();
 }else if(kind==11){
  assert(count==3);disconnected=2;keys(0,1,12);keys(1,1,12);lobby(2);
  disconnected=-1;keys(2,1,12);run(200);
  if(synced(3)){puts("OUTCOME late join synchronized");start();}
  else{errors(-1,2000);puts("OUTCOME late join rejected safely");retry();}
 }else if(kind==8||kind==14||kind==15){
  fired=0;if(kind==14)receive_hook=corrupt;else transfer_hook=trigger;
  for(int i=0;i<count;i++)c[i]->setKeys(c[i],1);run(20);for(int i=0;i<count;i++)c[i]->setKeys(c[i],0);
  for(int t=0;t<400&&!fired;t++)run(1);assert(fired);
  if(kind==15){c[target]->setKeys(c[target],0);assert(rd(target,game_addr+12)==26);errors(target,2000);}
  else errors(-1,2000);
  if(kind==8)release_irq();retry();
 }else{
  if(kind==13)for(int i=0;i<count;i++){
   /* Set the clock before any transaction owns a deadline. Jumping it in
    * mid-transaction would simulate 256 seconds elapsed, not wraparound. */
   c[i]->busWrite16(c[i],0x0400010e,0);c[i]->busWrite16(c[i],0x0400010a,0);
   c[i]->busWrite16(c[i],0x0400010c,0xff00);c[i]->busWrite16(c[i],0x04000108,0);
   c[i]->busWrite16(c[i],0x0400010e,0x84);c[i]->busWrite16(c[i],0x0400010a,0x80);
   /* A running timer data write sets its NEXT reload, not its counter.
    * Restore reload zero or this would jump back to FF00 every second. */
   c[i]->busWrite16(c[i],0x0400010c,0);
  }
  join_all();
  if(kind==2){keys(target,2,12);assert(rd(target,game_addr+12)==26);errors(target,2000);retry();}
  else{
   start();
   if(kind==10){uint64_t before=cable_clock(target);c[target]->reset(c[target]);clock_offset[target]=before-mTimingGlobalTime(&g[target]->timing);irq_due[target]=0;errors(target,400);run(100);assert(rd(target,game_addr+12)==0);retry();}
   else if(kind==17){
    for(unsigned cycle=0;cycle<amount;cycle++){
     target=random32()%count;
     irq_block_mask=1u<<target;run(1+random32()%60);release_irq();run(100);no_errors();
     unsigned action=random32()%3;
     printf("CYCLE %u target=%u action=%u rng=%u\n",cycle,target,action,seed);fflush(stdout);
     if(action==0){disconnected=target;errors(-1,400);}
     else if(action==1){
      uint64_t before=cable_clock(target);c[target]->reset(c[target]);clock_offset[target]=before-mTimingGlobalTime(&g[target]->timing);irq_due[target]=0;
      errors(target,400);run(100);
     }else{ready_block=1;errors(-1,400);}
     retry();records();
    }
   }else if(kind==12){
    int before=transfers;
    for(unsigned step=0;step<amount;step++){
     for(int i=0;i<count;i++)c[i]->setKeys(c[i],(random32()%3)?1u<<(random32()%10):0);
     irq_delay=1000+random32()%60000;run(1+random32()%12);no_errors();
    }
    irq_delay=0;for(int i=0;i<count;i++)c[i]->setKeys(c[i],0);run(160);no_errors();records();assert(transfers>before+100);
   }else{
    if(kind==13)for(int i=0;i<count;i++)assert(c[i]->busRead16(c[i],0x0400010c)<0xff00);
    arm();
    if(kind==4||kind==5||kind==9||kind==13){
     run(amount);ready_block=0;if(kind==5)release_irq();if(kind==9)disconnected=-1;
     if(amount<100&&kind!=9){run(160);no_errors();assert(rd(0,active_addr));}
     else if(amount>=180||kind==9){errors(-1,400);retry();}
     else{
      run(300);int any=0;for(int i=0;i<count;i++)any|=rd(i,game_addr+12)==31;
      if(any){errors(-1,400);puts("OUTCOME boundary timeout");retry();}else{puts("OUTCOME boundary recovered");no_errors();}
     }
    }else{errors(-1,400);retry();}
   }
  }
 }
 records();success=1;printf("PASS chaos kind=%u count=%d transfers=%d delayed=%u busy=%u\n",kind,count,transfers,delayed_irqs,busy_irqs);return 0;
}
