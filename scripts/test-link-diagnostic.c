/* Exercise the diagnostic through actual menu/input handlers on mGBA CPUs. */
#define main link_regression_main
#include "test-link.c"
#undef main
static uint32_t test_addr;
static unsigned injected;
static unsigned hardware_injected,hardware_passed,hardware_errors;
static uint32_t field(int i,unsigned offset){return rd(i,test_addr+offset);}
static void press(int device,unsigned key){
 for(int i=0;i<count;i++)if(device<0||i==device)c[i]->setKeys(c[i],key);
 run(12);
 for(int i=0;i<count;i++)c[i]->setKeys(c[i],0);
 run(12);
}
static void corrupt_echo(int i){
 if(i||injected||sent[0]==0xace1||sent[1]!=sent[0])return;
 g[0]->memory.io[REG_SIOMULTI1/2]^=1;injected=1;
}
static void hardware_fault(int i){
 if(i!=1||hardware_injected==2)return;
 if(hardware_injected){
  assert(field(i,32)==hardware_passed&&field(i,36)==hardware_errors+1);
  hardware_injected=2;return;
 }
 unsigned last=c[i]->busRead16(c[i],test_addr+58);
 if(last&&g[i]->memory.io[REG_SIOMULTI0/2]!=last){
  hardware_passed=field(i,32);hardware_errors=field(i,36);
  g[i]->sio.siocnt|=64;hardware_injected=1;
 }
}
static void healthy(void){
 for(int i=0;i<count;i++){
  printf("node=%d role=%u transfers=%u ok=%u err=%u wait=%u timeout=%u\n",i,field(i,4),field(i,28),field(i,32),field(i,36),field(i,40),field(i,44));
  printf(" running=%u inflight=%u last_at=%u now_hi=%u now_lo=%u mode=%u SIO=%04x\n",field(i,0),field(i,24),field(i,48),c[i]->busRead16(c[i],0x0400010c),c[i]->busRead16(c[i],0x04000108),rd(i,game_addr+12),g[i]->sio.siocnt);
 }
 for(int i=0;i<count;i++){
  assert(rd(i,game_addr+12)==38&&field(i,0)==1&&field(i,4)==(unsigned)i);
  assert(field(i,16)==(unsigned)count&&field(i,32)>10&&!field(i,36)&&!field(i,44));
 }
}
int main(int argc,char**argv){
 assert(argc==8);mLogSetDefaultLogger(&logger);
 count=atoi(argv[2]);unsigned baud=atoi(argv[3]),pace=atoi(argv[4]),first=atoi(argv[5]);
 game_addr=strtoul(argv[6],0,16);test_addr=strtoul(argv[7],0,16);
 uint8_t saved[3][128];
 for(int i=0;i<count;i++){
  c[i]=mCoreFind(argv[1]);assert(c[i]&&c[i]->init(c[i]));mCoreInitConfig(c[i],NULL);
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
 run(100);for(int i=0;i<count;i++)for(int j=0;j<128;j++)saved[i][j]=c[i]->busRead8(c[i],0x0e000000+j);
 press(-1,1);for(int i=0;i<count;i++)assert(rd(i,game_addr+12)==26);
 for(int j=0;j<3;j++)press(-1,128);press(-1,1);
 for(int i=0;i<count;i++)assert(rd(i,game_addr+12)==38&&!field(i,0));
 for(unsigned j=baud;j<3;j++)press(-1,512);
 for(unsigned j=1;j!=pace;j=(j+1)%4)press(-1,128);
 for(int i=0;i<count;i++)assert(field(i,8)==baud&&field(i,12)==pace);
 press(first,1);run(120);assert(!transfers&&field(first,0));
 for(int i=0;i<count;i++)if((unsigned)i!=first)press(i,1);
 run(180);healthy();
 press(-1,4);run(30);press(-1,4);
#ifndef LINK_NATIVE
 receive_hook=corrupt_echo;uint32_t before=field(0,32);run(180);receive_hook=0;
 assert(injected&&field(0,36)==1&&field(0,32)>before+10);
 for(int i=0;i<count;i++)assert(field(i,0)&&!field(i,44));
 irq_delay=20000;run(180);irq_delay=0;
 for(int i=0;i<count;i++)assert(field(i,0)&&!field(i,44));
 receive_hook=hardware_fault;run(180);receive_hook=0;
 assert(hardware_injected==2);
 printf("PASS: hardware-faulted child sample is not counted as checked\n");
#endif
 press(count-1,2);assert(rd(count-1,game_addr+12)==26);run(180);
 for(int i=0;i<count-1;i++)assert(!field(i,0)&&field(i,20)&&field(i,44)==1);
 press(count-1,1);assert(rd(count-1,game_addr+12)==38);press(-1,1);run(180);healthy();
#ifndef LINK_NATIVE
 disconnected=1;run(180);
 for(int i=0;i<count;i++)assert(!field(i,0)&&field(i,20)&&field(i,44)==1);
 disconnected=-1;press(-1,1);run(180);healthy();
#endif
 press(-1,2);for(int i=0;i<count;i++){
  assert(rd(i,game_addr+12)==26&&!field(i,0)&&!(g[i]->memory.io[REG_IE/2]&128));
  for(int j=0;j<128;j++)assert(c[i]->busRead8(c[i],0x0e000000+j)==saved[i][j]);
 }
 printf("PASS raw diagnostic count=%d baud=%u pace=%u first=%u\n",count,baud,pace,first);return 0;
}
