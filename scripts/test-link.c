/* ROM test in mGBA cores with a test cable bus. Requires the mGBA headers/library.
 * The bus models multi registers, transfer duration, player IDs and SIO IRQ;
 * it is not a substitute for testing a physical GBA cable. */
#include <mgba/core/core.h>
#include <mgba/internal/gba/gba.h>
#include <mgba/internal/gba/io.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#undef assert
#define assert(x) do {if(!(x)){fprintf(stderr,"FAIL line %d: %s\n",__LINE__,#x);exit(1);}}while(0)
static void quiet(struct mLogger*l,int c,enum mLogLevel level,const char*f,va_list a){(void)l;(void)c;(void)level;(void)f;(void)a;}
static struct mLogger logger={quiet,0};
static struct mCore*c[3];static struct GBA*g[3];static int count,disconnected=-1;
static struct Node{struct GBASIODriver d;int id;}nodes[3];
static uint16_t sent[4];static uint64_t deadline;static int pending,transfers;
static unsigned irq_delay,time_scale=1,delayed_irqs,busy_irqs;
static uint32_t perf_stage;static unsigned stage_transfers[16];
static void record_transfer(void){if(perf_stage){unsigned stage=c[0]->busRead32(c[0],perf_stage);if(stage<16)stage_transfers[stage]++;}}
static uint64_t irq_due[3];
static uint64_t clock_offset[3];
static uint64_t cable_clock(int i){return clock_offset[i]+mTimingGlobalTime(&g[i]->timing);}
/* Optional fault controls used by test-link-chaos.c. */
static unsigned irq_block_mask,ready_block,initial_role_mask;
static void (*transfer_hook)(void);
static void (*receive_hook)(int);
static int cable_online(int i){return disconnected<0||i<disconnected;}
static int cable_ready(void){
 if(ready_block||!cable_online(0))return 0;
 for(int i=0;i<count;i++)if(cable_online(i)&&g[i]->sio.mode!=SIO_MULTI)return 0;
 return 1;
}
static int join_order;
static unsigned join_delay=2400;
static void cable_pins(void){
 int ready=cable_ready();
 for(int i=0;i<count;i++)if(g[i]->sio.mode==SIO_MULTI){
  /* Before all physical peers select multiplayer, SI is not a valid role
   * indication. Exercise the allowed high level on the parent as well. */
  /* During transmission a child's SI is pulled low by the preceding GBA.
   * Role detection must sample an idle, ready bus, not a data phase. */
  int local_ready=ready&&cable_online(i);
  int slave=!local_ready||(i&&!(g[i]->sio.siocnt&128));
  if(!transfers&&local_ready&&(initial_role_mask&(1u<<i)))slave=!slave;
  g[i]->sio.siocnt=(g[i]->sio.siocnt&~12)|(local_ready?8:0)|(slave?4:0);
 }
}
static uint32_t game_addr,mp_addr;
static bool yes(struct GBASIODriver*d){(void)d;return true;}
static void nothing(struct GBASIODriver*d){(void)d;}
#ifdef LINK_NATIVE
#include "test-link-native.inc"
#endif
static uint16_t cable_write(struct GBASIODriver*d,uint32_t address,uint16_t value){
 struct Node*n=(struct Node*)d;
 if(address==REG_SIOCNT){
  if(!n->id&&(value&128)&&!pending){
   record_transfer();if(transfer_hook)transfer_hook();
   for(int i=0;i<4;i++)sent[i]=i<count&&cable_online(i)&&g[i]->sio.mode==SIO_MULTI?g[i]->memory.io[REG_SIOMLT_SEND/2]:0xffff;
   deadline=cable_clock(0)+GBASIOCyclesPerTransfer[value&3][count-1];pending=1;
   for(int i=0;i<count;i++){
    if(!cable_online(i)||g[i]->sio.mode!=SIO_MULTI)continue;
    /* ERROR is undefined while BUSY; choose the high value to ensure that
     * a delayed IRQ cannot treat an in-flight transfer as a cable failure. */
    g[i]->sio.siocnt|=128|64;
    /* Real hardware and mGBA lockstep clear receive registers at START. */
    for(int j=0;j<4;j++)g[i]->memory.io[REG_SIOMULTI0/2+j]=0xffff;
   }
  }
  int ready=cable_ready();
  if(n->id)value=(value&~128)|(g[n->id]->sio.siocnt&128);
  int slave=n->id||!ready;
  if(!transfers&&ready&&(initial_role_mask&(1u<<n->id)))slave=!slave;
  return (value&0xff83)|(ready?8:0)|(slave?4:0)|(n->id<<4);
 }
 return value;
}
static uint32_t rd(int i,uint32_t a){return c[i]->busRead32(c[i],a);}
static void wr(int i,uint32_t a,uint32_t v){c[i]->busWrite32(c[i],a,v);}
static void run(unsigned frames){
#ifdef LINK_NATIVE
 native_run(frames);return;
#endif
 uint64_t end=cable_clock(0)+(uint64_t)frames*time_scale*280896;
 while(cable_clock(0)<end){
  uint64_t min=UINT64_MAX;int who=0;
  for(int i=0;i<count;i++){uint64_t t=cable_clock(i);if(t<min){min=t;who=i;}}
  if(pending&&min>=deadline){
   for(int i=0;i<count;i++){
    if(!cable_online(i)||g[i]->sio.mode!=SIO_MULTI)continue;
    for(int j=0;j<4;j++)g[i]->memory.io[(REG_SIOMULTI0/2)+j]=sent[j];
    g[i]->sio.siocnt=(g[i]->sio.siocnt&~0xf4)|(i<<4)|(i?4:0);g[i]->sio.rcnt|=1;
    if(receive_hook)receive_hook(i);
    if(!(irq_block_mask&(1u<<i))&&(g[i]->sio.siocnt&0x4000)){
     /* Model a slave whose CPU cannot service SIO promptly (e.g. audio IRQ).
      * Timers and serial hardware continue; pending IRQs coalesce. */
     if(i&&irq_delay&&transfers%37==0&&!irq_due[i]){
      irq_due[i]=min+irq_delay;delayed_irqs++;
     }else if(!irq_due[i])GBARaiseIRQ(g[i],GBA_IRQ_SIO,0);
    }
   }pending=0;transfers++;
  }
  for(int i=1;i<count;i++)if(irq_due[i]&&min>=irq_due[i]){
   if(g[i]->sio.siocnt&128)busy_irqs++;
   if(cable_online(i)&&!(irq_block_mask&(1u<<i)))GBARaiseIRQ(g[i],GBA_IRQ_SIO,0);
   irq_due[i]=0;
  }
  c[who]->runLoop(c[who]);
  cable_pins();
 }
}
static void benchmark(const char*label){
 int authority=getenv("LINK_AUTHORITY")?atoi(getenv("LINK_AUTHORITY")):0;
 run(60);unsigned before=rd(authority,game_addr+4),sent_before=transfers,stages[16];
 memcpy(stages,stage_transfers,sizeof stages);uint64_t ticks=cable_clock(0);
 run(600);ticks=cable_clock(0)-ticks;unsigned updates=rd(authority,game_addr+4)-before;
 for(int i=0;i<count;i++)assert(rd(i,game_addr+12)!=31);
 printf("BENCH {\"profile\":\"%s\",\"consoles\":%d,\"updates\":%u,\"transfers\":%u,\"cycles\":%llu,\"by_stage\":[",label,count,updates,(unsigned)transfers-sent_before,(unsigned long long)ticks);
 for(int i=0;i<16;i++)printf("%s%u",i?",":"",stage_transfers[i]-stages[i]);puts("]}");fflush(stdout);
}
#include "test-link-animations.inc"
static int avatar_screen(int i){return getenv("LINK_AVATAR_EDIT_ADDR")&&rd(i,game_addr+12)==33&&rd(i,strtoul(getenv("LINK_AVATAR_EDIT_ADDR"),0,16));}
static void finish_avatars(void){
 if(!getenv("LINK_AVATAR_EDIT_ADDR"))return;
 uint32_t editing=strtoul(getenv("LINK_AVATAR_EDIT_ADDR"),0,16),names=strtoul(getenv("LINK_NAME_EDIT_ADDR"),0,16);
 for(int attempt=0;attempt<2;attempt++){
  run(20);
  for(int i=0;i<count;i++)if(rd(i,editing)&&!rd(i,names))c[i]->setKeys(c[i],1);
  run(20);for(int i=0;i<count;i++)c[i]->setKeys(c[i],0);run(40);
 }
}
int main(int argc,char**argv){
 if(getenv("LINK_STAGE_ADDR"))perf_stage=strtoul(getenv("LINK_STAGE_ADDR"),0,16);
 if(getenv("LINK_IRQ_DELAY"))irq_delay=strtoul(getenv("LINK_IRQ_DELAY"),0,0);
 if(getenv("LINK_TIME_SCALE"))time_scale=strtoul(getenv("LINK_TIME_SCALE"),0,0);
 if(getenv("LINK_JOIN_ORDER"))join_order=atoi(getenv("LINK_JOIN_ORDER"));
 if(getenv("LINK_JOIN_DELAY"))join_delay=strtoul(getenv("LINK_JOIN_DELAY"),0,0);
 assert(time_scale>=1&&time_scale<=10);
 mLogSetDefaultLogger(&logger);assert(argc==7||argc==12||argc==15);int names_case=argc>=12?atoi(argv[7]):0;uint32_t avatars_addr=strtoul(argv[6],0,16);uint32_t prefs_addr=strtoul(argv[5],0,16);count=atoi(argv[2]);game_addr=strtoul(argv[3],0,16);mp_addr=strtoul(argv[4],0,16);
 for(int i=0;i<count;i++){
  c[i]=mCoreFind(argv[1]);assert(c[i]);assert(c[i]->init(c[i]));mCoreInitConfig(c[i],NULL);
  mCoreConfigSetDefaultIntValue(&c[i]->config,"useBios",0);mCoreConfigSetDefaultIntValue(&c[i]->config,"skipBios",1);
  mCoreConfigSetDefaultValue(&c[i]->config,"idleOptimization","ignore");mCoreLoadConfig(c[i]);
  c[i]->setVideoBuffer(c[i],calloc(240*160,sizeof(color_t)),240);assert(mCoreLoadFile(c[i],argv[1]));c[i]->reset(c[i]);g[i]=c[i]->board;
#ifdef LINK_NATIVE
  install_driver(i);
#else
  nodes[i].id=i;nodes[i].d.init=yes;nodes[i].d.deinit=nothing;nodes[i].d.load=yes;nodes[i].d.unload=yes;nodes[i].d.writeRegister=cable_write;
  GBASIOSetDriver(&g[i]->sio,&nodes[i].d,SIO_MULTI);
#endif
 }
 run(100);
 if(getenv("LINK_CREATE_ADDR"))for(int i=0;i<count;i++)wr(i,strtoul(getenv("LINK_CREATE_ADDR"),0,16),1);
 if(argc==15)for(int i=0;i<count;i++){wr(i,strtoul(argv[13],0,16),i?0:2);wr(i,strtoul(argv[14],0,16),i?1:8);}
 for(int i=0;i<count;i++){
  for(int option=0;option<3;option++)wr(i,prefs_addr+option*4,i==0);
  wr(i,avatars_addr+8,names_case?1:i+1);
  wr(i,mp_addr,2);wr(i,mp_addr+4,1);wr(i,mp_addr+16,2);wr(i,game_addr+12,27);wr(i,game_addr+80*4,1);
  wr(i,game_addr+88*4,128+i);c[i]->setKeys(c[i],8);
  if(names_case){
   const char *name=names_case==1?"AAAAAAAAAA":names_case==2?"1-\xeb\xa9 \x88\x83\x90\x8e\x8a":(names_case==4||(names_case==5&&i==0))?"\x81\x80\x83\x88\x90\x80":names_case==5?(i==1?"ANNA":"BORIS"):i<2?"ANNA":"BORIS";
   wr(i,game_addr+80*4,strlen(name));
   for(int j=0;j<11;j++)c[i]->busWrite8(c[i],game_addr+88*4+j,j<(int)strlen(name)?name[j]:0);
  }
 }
 run(20);for(int i=0;i<count;i++)c[i]->setKeys(c[i],0);
 run(20);for(int i=0;i<count;i++)assert(rd(i,game_addr+12)==33);
 /* Legacy packet fixtures preselect avatars; real join UI has separate tests. */
 if(getenv("LINK_CREATE_ADDR"))for(int i=0;i<count;i++)wr(i,strtoul(getenv("LINK_CREATE_ADDR"),0,16),i==0);
 if(join_order){
  int first=join_order==1?0:count-1;
  c[first]->setKeys(c[first],1);run(20);c[first]->setKeys(c[first],0);
  run(join_delay);
  printf("waiting device %d after %u frames: mode %u\n",first,join_delay*time_scale,rd(first,game_addr+12));fflush(stdout);
  assert(rd(first,game_addr+12)==30);
  assert(transfers==0);
  for(int i=0;i<count;i++)if(i!=first)c[i]->setKeys(c[i],1);
 }else for(int i=0;i<count;i++)c[i]->setKeys(c[i],1);
 run(20);for(int i=0;i<count;i++)c[i]->setKeys(c[i],0);
 run(160);finish_avatars();
 for(int i=0;i<count;i++)printf("lobby device %d: mode %u, consoles %u\n",i,rd(i,game_addr+12),rd(i,mp_addr));
 fflush(stdout);
 for(int i=0;i<count;i++){assert(rd(i,game_addr+12)==30||avatar_screen(i)||(names_case&&names_case!=2&&rd(i,game_addr+12)==27));assert(rd(i,mp_addr)==(uint32_t)count);}
 if(names_case&&names_case!=2&&(names_case!=5||count==2)){
  uint32_t edit=strtoul(argv[8],0,16),answer=strtoul(argv[9],0,16),pos=strtoul(argv[10],0,16),cursor=strtoul(argv[11],0,16);
  for(int i=0;i<count;i++){
   int conflict=names_case==5?(count==2&&i==0):(names_case==4&&count==2)||i==1||(i==2&&(names_case==1||names_case==4));
   assert(rd(i,edit)==(uint32_t)conflict);
  }
  c[0]->setKeys(c[0],8);run(30);c[0]->setKeys(c[0],0);run(30);
  for(int i=0;i<count;i++)assert(rd(i,game_addr+12)==30||avatar_screen(i)||(rd(i,game_addr+12)==27&&rd(i,edit)));
  for(int i=0;i<count;i++)if(rd(i,edit)){
   unsigned length=rd(i,pos),selection=rd(i,cursor);char before[21];
   for(int j=0;j<21;j++)before[j]=c[i]->busRead8(c[i],answer+j);
   c[i]->setKeys(c[i],i%2?2:1);run(30);c[i]->setKeys(c[i],0);run(30);
   assert(rd(i,edit)==2&&rd(i,pos)==length&&rd(i,cursor)==selection);
   for(int j=0;j<21;j++)assert(c[i]->busRead8(c[i],answer+j)==(unsigned char)before[j]);
   /* Submitting the unchanged duplicate brings the message back. */
   c[i]->setKeys(c[i],8);run(30);c[i]->setKeys(c[i],0);run(40);assert(rd(i,edit)==1);
   c[i]->setKeys(c[i],1);run(30);c[i]->setKeys(c[i],0);run(30);assert(rd(i,edit)==2);
   for(unsigned j=0;j<length;j++){c[i]->setKeys(c[i],2);run(20);c[i]->setKeys(c[i],0);run(20);}
   assert(rd(i,pos)==0);
   /* Empty input and spaces each produce the empty-name message (state 3).
    * Dismissing via A/B must neither insert nor erase input. */
   for(int spaces=0;spaces<2;spaces++){
    if(spaces){c[i]->setKeys(c[i],256);run(20);c[i]->setKeys(c[i],0);run(20);}
    c[i]->setKeys(c[i],8);run(30);c[i]->setKeys(c[i],0);run(30);
    assert(rd(i,edit)==3&&rd(i,pos)==(unsigned)spaces);
    c[i]->setKeys(c[i],spaces?2:1);run(30);c[i]->setKeys(c[i],0);run(30);
    assert(rd(i,edit)==2&&rd(i,pos)==(unsigned)spaces);
   }
   c[i]->setKeys(c[i],2);run(20);c[i]->setKeys(c[i],0);run(20);
   assert(rd(i,pos)==0);
   for(int j=0;j<=i;j++){c[i]->setKeys(c[i],16);run(20);c[i]->setKeys(c[i],0);run(20);}
   c[i]->setKeys(c[i],1);run(20);c[i]->setKeys(c[i],0);run(20);
   c[i]->setKeys(c[i],8);run(30);c[i]->setKeys(c[i],0);run(60);
   assert(rd(i,edit)==0);
   for(int j=0;j<count;j++)assert(rd(j,game_addr+12)==30||avatar_screen(j)||(rd(j,game_addr+12)==27&&rd(j,edit)));
  }
  printf("PASS: duplicate blocks start; A/B preserve text/cursor; retry and correction keep cable connected\n");
 }
 char roster[3][11];
 for(int device=0;device<count;device++){
  uint32_t address=mp_addr+28+((device+2)%3)*11;
  for(int j=0;j<11;j++){
   roster[device][j]=c[0]->busRead8(c[0],address+j);
   for(int i=1;i<count;i++)assert(c[i]->busRead8(c[i],address+j)==(unsigned char)roster[device][j]);
  }
  assert(roster[device][0]&&roster[device][10]==0);
  for(int j=0;j<device;j++)assert(strcmp(roster[device],roster[j]));
 }
 if(names_case==1)assert(!strcmp(roster[0],"AAAAAAAAAA"));
 if(names_case==2)for(int i=0;i<count;i++)assert(roster[i][0]=='1'+i);
 if(names_case==3){assert(!strcmp(roster[0],"ANNA"));if(count==3)assert(!strcmp(roster[2],"BORIS"));}
 finish_avatars();
 printf("PASS: unique bounded names synchronized in lobby (case %d)\n",names_case);
 if(getenv("LINK_BENCHMARK"))benchmark("lobby");
 c[1]->setKeys(c[1],8);run(30);c[1]->setKeys(c[1],0);run(20);
 assert(rd(0,game_addr+12)==30);
 c[0]->setKeys(c[0],8);run(30);c[0]->setKeys(c[0],0);run(120);
 printf("PASS: automatic console count, lobby waits, host-only start\n");
 for(int i=0;i<count;i++)printf("device %d mode %u player %u local %u viewer %u word %u transfers %d\n",i,rd(i,game_addr+12),rd(i,game_addr+20),rd(i,mp_addr+12),rd(i,mp_addr+8),rd(i,game_addr+24),transfers);
 for(int i=0;i<count;i++){assert(rd(i,game_addr+12)!=31);assert(rd(i,game_addr+12)!=30);assert(rd(i,mp_addr+12)==(i+2)%3);assert(rd(i,mp_addr+8)==(i+2)%3);assert(rd(i,game_addr+24)==rd(0,game_addr+24));}
 for(int i=0;i<count;i++)for(int option=0;option<3;option++)assert(rd(i,prefs_addr+option*4)==1);
 for(int i=0;i<count;i++)for(int device=0;device<count;device++)assert(rd(i,avatars_addr+((device+2)%3)*4)==(uint32_t)(names_case?1:device+1));
 for(int i=0;i<count;i++)for(int device=0;device<count;device++)for(int j=0;j<11;j++)assert(c[i]->busRead8(c[i],mp_addr+28+((device+2)%3)*11+j)==(unsigned char)roster[device][j]);
 printf("PASS: all selected avatars synchronized\n");
 printf("PASS: host dictionary, Plus and character settings synchronized\n");
 if(getenv("LINK_ANIMATIONS")){animation_tests();return 0;}
 if(getenv("LINK_BENCHMARK")){
  wr(0,game_addr+12,1);wr(0,game_addr+20,2);wr(0,game_addr+81*4,1);
  benchmark("human_turn");return 0;
 }
 /* A spectator cannot choose for player two. The owning console can. */
 wr(0,game_addr+12,1);wr(0,game_addr+20,0);wr(0,game_addr+81*4,1);run(30);
 c[0]->setKeys(c[0],1);run(30);c[0]->setKeys(c[0],0);assert(rd(0,game_addr+12)==1);
 c[1]->setKeys(c[1],1);run(90);c[1]->setKeys(c[1],0);assert(rd(0,game_addr+12)!=1);run(30);
 for(int i=1;i<count;i++){assert(rd(i,game_addr+20)==rd(0,game_addr+20));assert(rd(i,game_addr+24)==rd(0,game_addr+24));}
 printf("PASS: %d consoles, perspectives, dictionary/word sync, owner-only input (%d transfers)\n",count,transfers);
 if(argc==15){
  uint32_t match=strtoul(argv[12],0,16),rule=strtoul(argv[13],0,16),rounds=strtoul(argv[14],0,16);
  for(int i=0;i<count;i++){assert(rd(i,rule)==2);assert(rd(i,rounds)==8);}
  /* A wins match ends at the target, not at a fixed round count. Switch
   * the fixture to points-with-risk for the fixed-round tied-score test. */
  wr(0,rule,1);run(30);
  for(int i=0;i<count;i++)assert(rd(i,rule)==1);
  /* Final main round: two leaders tie on points. Third sits out. */
  wr(0,game_addr+16,7);wr(0,game_addr+20,2);wr(0,game_addr+79*4,1);
  wr(0,game_addr+9*4,500);wr(0,game_addr+10*4,100);wr(0,game_addr+11*4,500);
  wr(0,match+6*4,1);wr(0,match+7*4,0);wr(0,match+8*4,0);
  wr(0,game_addr+12,9);run(80);
  for(int i=0;i<count;i++)assert(rd(i,game_addr+12)==9);
  c[0]->setKeys(c[0],1);run(30);c[0]->setKeys(c[0],0);run(60);
  for(int i=0;i<count;i++){
   assert(rd(i,game_addr+12)==36);assert(rd(i,match+10*4)==5);assert(rd(i,match+14*4)==1);
   for(int j=0;j<16;j++)assert(rd(i,match+j*4)==rd(0,match+j*4));
  }
  c[0]->setKeys(c[0],1);run(30);c[0]->setKeys(c[0],0);run(60);
  for(int i=0;i<count;i++){assert(rd(i,match+9*4)==1);assert(rd(i,mp_addr+24)==2);assert(rd(i,game_addr+20)==2);}
  /* Empty shootout repeats with identical membership, even after scores change. */
  wr(0,mp_addr+24,7);wr(0,game_addr+79*4,0);wr(0,game_addr+12,9);run(60);
  for(int i=0;i<count;i++)assert(rd(i,game_addr+12)==9);
  c[0]->setKeys(c[0],1);run(30);c[0]->setKeys(c[0],0);run(60);
  c[0]->setKeys(c[0],1);run(30);c[0]->setKeys(c[0],0);run(60);
  for(int i=0;i<count;i++){assert(rd(i,match+10*4)==5);assert(rd(i,mp_addr+24)==2);assert(rd(i,game_addr+16)==7);}
  wr(0,game_addr+9*4,9000);wr(0,game_addr+20,2);wr(0,game_addr+79*4,1);wr(0,game_addr+12,9);run(80);
  for(int i=0;i<count;i++)assert(rd(i,game_addr+12)==9);
  c[0]->setKeys(c[0],1);run(30);c[0]->setKeys(c[0],0);run(60);
  for(int i=0;i<count;i++){assert(rd(i,game_addr+12)==36);assert(rd(i,match+13*4)==2);assert(rd(i,match+14*4)==2);}
  printf("PASS: host rules/round count, standings, leader-only repeated shootout and winner synchronized\n");
 }
 disconnected=count-1;run(300);
 for(int i=0;i<count;i++)assert(rd(i,game_addr+12)==31);
 printf("PASS: disconnect reports error without continuing the game\n");
 if(irq_delay){assert(delayed_irqs&&busy_irqs);printf("PASS: %u delayed slave IRQs (%u cycles each), %u during BUSY\n",delayed_irqs,irq_delay,busy_irqs);}
 return 0;
}
