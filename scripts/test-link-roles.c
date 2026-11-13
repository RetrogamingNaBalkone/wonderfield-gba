/* Create/join flows through real ROM input, with stock or fault-model SIO. */
#define main link_regression_main
#include "test-link.c"
#undef main
static uint32_t prefs_addr,avatars_addr,create_addr,avatar_edit_addr,role_error_addr;
static int scenario,graphics;
static void press(int node,unsigned keys){
 for(int i=0;i<count;i++)if(node<0||i==node)c[i]->setKeys(c[i],keys);
 run(12);for(int i=0;i<count;i++)c[i]->setKeys(c[i],0);run(20);
}
static void select_roles(int retry){
 for(int i=0;i<count;i++){
  int creator=retry?i==0:scenario==1?0:scenario==2?1:scenario==3?i==1:i==0;
  int previous=retry?(scenario==1?0:scenario==2?1:scenario==3?i==1:i==0):1;
  if(creator!=previous)press(i,128);
  press(i,1);
  assert(rd(i,create_addr)==(unsigned)creator);
  assert(rd(i,game_addr+12)==(unsigned)(creator?32:27));
  if(creator){
   /* Only the creator has settings; use conspicuously different values. */
   wr(i,prefs_addr,0);wr(i,prefs_addr+4,0);wr(i,prefs_addr+8,graphics);
   wr(i,prefs_addr+16,1);wr(i,prefs_addr+20,5);
   press(i,1);assert(rd(i,game_addr+12)==27);
  }
 }
 for(int i=0;i<count;i++){
  for(int j=0;j<i;j++)press(i,16);
  press(i,1);press(i,8);
  assert(rd(i,game_addr+12)==(rd(i,create_addr)?33:30)||(scenario>=1&&scenario<=3&&!retry&&rd(i,game_addr+12)==31));
  if(scenario==4&&i==0){press(0,1);run(2400);assert(rd(0,game_addr+12)==30&&!transfers);}
 }
 for(int i=0;i<count;i++)if(rd(i,create_addr)&&rd(i,game_addr+12)==33)press(i,1);
 run(240);
}
static void play(void){
 for(int i=0;i<count;i++){
  assert(rd(i,game_addr+12)==30||(i&&rd(i,game_addr+12)==33));
  assert(rd(i,prefs_addr)==0&&rd(i,prefs_addr+4)==0&&rd(i,prefs_addr+8)==(unsigned)graphics);
  assert(rd(i,prefs_addr+16)==1&&rd(i,prefs_addr+20)==5);
  assert(rd(i,avatar_edit_addr)==(unsigned)(i!=0));
 }
 press(0,8);run(60);assert(rd(0,game_addr+12)==30);
 for(int i=1;i<count;i++){press(i,32);press(i,1);}
 run(120);
 for(int i=0;i<count;i++){
  assert(!rd(i,avatar_edit_addr));
  for(int j=1;j<count;j++)assert(rd(i,avatars_addr+((j+2)%3)*4)==(unsigned)(graphics?8:6));
 }
 press(0,8);run(180);
 for(int i=0;i<count;i++)assert(rd(i,game_addr+12)!=30&&rd(i,game_addr+12)!=31&&rd(i,game_addr+24)==rd(0,game_addr+24));
}
int main(int argc,char**argv){
 assert(argc==12);mLogSetDefaultLogger(&logger);
 count=atoi(argv[2]);scenario=atoi(argv[3]);graphics=atoi(argv[4]);
 game_addr=strtoul(argv[5],0,16);mp_addr=strtoul(argv[6],0,16);prefs_addr=strtoul(argv[7],0,16);
 avatars_addr=strtoul(argv[8],0,16);create_addr=strtoul(argv[9],0,16);avatar_edit_addr=strtoul(argv[10],0,16);role_error_addr=strtoul(argv[11],0,16);
 unsigned char saved[3][128];
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
 press(-1,1);press(-1,128);press(-1,128);press(-1,1);
 for(int i=0;i<count;i++)assert(rd(i,game_addr+12)==39);
 select_roles(0);
 if(scenario>=1&&scenario<=3){
  for(int i=0;i<count;i++){
   assert((rd(i,game_addr+12)==31||rd(i,game_addr+12)==30)&&rd(i,role_error_addr)==(unsigned)scenario);
   press(i,2);assert(rd(i,game_addr+12)==39);
  }
  select_roles(1);
 }
 play();
 for(int i=0;i<count;i++)for(int j=0;j<128;j++)assert(c[i]->busRead8(c[i],0x0e000000+j)==saved[i][j]);
 printf("PASS create/join count=%d scenario=%d graphics=%d: roles, host settings, avatar readiness, start, SRAM\n",count,scenario,graphics);
 return 0;
}
