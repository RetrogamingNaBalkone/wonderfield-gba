/* Actual menu flow: first creator is authority, independently of SIO port. */
#define main link_regression_main
#include "test-link.c"
#undef main
static uint32_t prefs_addr,avatars_addr,create_addr,avatar_edit_addr,host_addr;
static int scenario,graphics,host,retried;
static uint32_t address(const char*name){const char*v=getenv(name);assert(v);return strtoul(v,0,16);}
static void capture(const char*stage){
 const char*directory=getenv("ROLE_SCREENSHOTS");
 if(!directory||count!=2||scenario!=1||graphics!=1)return;
 for(int i=0;i<count;i++){
  char path[1024];snprintf(path,sizeof path,"%s/%s-port%d.ppm",directory,stage,i);
  FILE*out=fopen(path,"wb");assert(out);fprintf(out,"P6\n240 160\n255\n");
  unsigned page=(c[i]->busRead16(c[i],0x04000000)&16)?0xa000:0;
  for(unsigned j=0;j<240*160;j++){
   unsigned index=c[i]->busRead8(c[i],0x06000000+page+j);
   unsigned rgb=c[i]->busRead16(c[i],0x05000000+index*2);
   fputc((rgb&31)*255/31,out);fputc(((rgb>>5)&31)*255/31,out);fputc(((rgb>>10)&31)*255/31,out);
  }
  fclose(out);
 }
}
static void press(int node,unsigned keys){
 for(int i=0;i<count;i++)if(node<0||i==node)c[i]->setKeys(c[i],keys);
 run(12);for(int i=0;i<count;i++)c[i]->setKeys(c[i],0);run(24);
}
static void enter(int i,int creator){
 if(rd(i,game_addr+81*4)!=(unsigned)!creator)press(i,128);
 press(i,1);assert(rd(i,create_addr)==(unsigned)creator);
 if(creator)assert(rd(i,game_addr+12)==32);
 else assert(rd(i,address("ROLE_PROFILE_PENDING"))==1);
 assert(!rd(i,address("ROLE_NAME_EDIT")));
}
static void configure(int i){
 assert(rd(i,game_addr+12)==32);
 wr(i,prefs_addr,0);wr(i,prefs_addr+4,0);wr(i,prefs_addr+8,graphics);
 wr(i,prefs_addr+16,1);wr(i,prefs_addr+20,5);
}
static void elect(void){
 if(scenario==5){
  enter(host,1);run(2400);assert(rd(host,game_addr+12)==32);
  /* Real settings/help input works for forty seconds with no participant. */
  press(host,64);press(host,16);press(host,4);assert(rd(host,game_addr+12)==37);
  press(host,2);assert(rd(host,game_addr+12)==32);
  wr(host,prefs_addr+12,5);configure(host);press(host,1);run(2400);
  assert(rd(host,game_addr+12)==30&&!rd(host,address("ROLE_NAME_EDIT")));
  for(int i=0;i<count;i++)if(i!=host)enter(i,0);
 }else{
  for(int i=0;i<count;i++)enter(i,scenario==3?0:scenario==4?1:i==host);
  if(scenario==7&&!retried)return;
  if(scenario==3){
   run(240);
   for(int i=0;i<count;i++)assert(rd(i,host_addr)==0xffffffffu&&!rd(i,address("ROLE_NAME_EDIT")));
   press(host,1);run(240);
   assert(rd(host,address("ROLE_CONFIG_MODE"))==32);
   wr(host,prefs_addr,0);wr(host,prefs_addr+4,0);wr(host,prefs_addr+8,graphics);
   wr(host,prefs_addr+16,1);wr(host,prefs_addr+20,5);press(host,1);
  }else{
   capture("host-settings");
   /* A guest cannot affect the creator's offline settings. */
   if(scenario!=4){
    int guest=(host+1)%count;unsigned rule=rd(host,prefs_addr+16);
    press(guest,16);press(guest,8);assert(rd(host,game_addr+12)==32&&rd(host,prefs_addr+16)==rule);
   }
   for(int i=0;i<count;i++)if(scenario==4||i==host){
    configure(i);
    if(i!=host){wr(i,prefs_addr,1);wr(i,prefs_addr+8,!graphics);wr(i,prefs_addr+16,2);}
    c[i]->setKeys(c[i],1);
   }
   run(12);for(int i=0;i<count;i++)c[i]->setKeys(c[i],0);
  }
 }
 run(300);
 if(scenario==6){
  for(int i=0;i<count;i++)if(i!=host)wr(i,create_addr,1);
  run(120);
 }
 for(int i=0;i<count;i++){
  assert(rd(i,host_addr)==(unsigned)host&&rd(i,address("ROLE_HOST_READY")));
  assert(rd(i,address("ROLE_NAME_EDIT"))==2);
  assert(rd(i,prefs_addr)==0&&rd(i,prefs_addr+4)==0&&rd(i,prefs_addr+8)==(unsigned)graphics);
  assert(rd(i,prefs_addr+16)==1&&rd(i,prefs_addr+20)==5);
 }
 capture("name-entry");
 printf("PASS: host port %d, offline settings/open lobby, profiles only after discovery\n",host);
}
static void play(void){
 press(0,8);assert(rd(0,address("ROLE_NAME_EDIT"))==3);
 press(0,1);assert(rd(0,address("ROLE_NAME_EDIT"))==2&&!rd(0,address("ROLE_NAME_POS")));
 press(0,256);press(0,8);assert(rd(0,address("ROLE_NAME_EDIT"))==3);
 press(0,2);assert(rd(0,address("ROLE_NAME_EDIT"))==2&&rd(0,address("ROLE_NAME_POS"))==1);
 press(0,2);assert(!rd(0,address("ROLE_NAME_POS")));
 for(int i=0;i<count;i++){
  for(int j=0;j<i;j++)press(i,16);
  press(i,1);press(i,8);run(60);
  assert(!rd(i,address("ROLE_NAME_EDIT"))&&rd(i,avatar_edit_addr));
 }
 press(host,32);press(host,1);run(60);assert(!rd(host,avatar_edit_addr));
 press(host,8);run(60);assert(rd(host,game_addr+12)==30);
 for(int i=0;i<count;i++)if(i!=host){press(i,32);press(i,1);}
 run(180);
 for(int i=0;i<count;i++){
  assert(!rd(i,avatar_edit_addr));
  for(int j=0;j<count;j++)assert(rd(i,avatars_addr+((j+2)%3)*4)==(unsigned)(graphics?8:6));
 }
 capture("lobby");
 press((host+1)%count,8);run(60);assert(rd(host,game_addr+12)==30);
 press(host,8);run(240);
 for(int i=0;i<count;i++)assert(rd(i,game_addr+12)!=30&&rd(i,game_addr+12)!=31&&rd(i,game_addr+24)==rd(host,game_addr+24));
 capture("game");
 /* The elected host owns rules, but still cannot act for another player. */
 int owner=(host+1)%count;wr(host,game_addr+12,1);wr(host,game_addr+20,(owner+2)%3);wr(host,game_addr+81*4,1);run(120);
 if(getenv("LINK_BENCHMARK"))benchmark("elected_host_human_turn");
 press(host,1);assert(rd(host,game_addr+12)==1);
 press(owner,1);
 for(int t=0;t<300;t++){int ready=1;for(int i=0;i<count;i++)if(rd(i,game_addr+12)!=2)ready=0;if(ready)break;run(1);}
 run(8);for(int i=0;i<count;i++)assert(rd(i,game_addr+12)==2);
 uint32_t scene=address("ROLE_SCENE"),events=address("ROLE_EVENTS");unsigned target=rd(host,scene+156),before[3],poses[3];
 for(int i=0;i<count;i++){before[i]=rd(i,events);poses[i]=rd(i,game_addr+73*4);assert(rd(i,scene+156)==target);}
 run(60);
 for(int i=0;i<count;i++){assert(rd(i,events)==before[i]);assert(rd(i,game_addr+73*4)>poses[i]);}
 press(owner,1);run(120);
 for(int i=0;i<count;i++)assert(rd(i,game_addr+28)==target&&rd(i,game_addr+12)!=2);
 printf("PASS: elected host publishes events; owner input, local animation and target agree\n");
 if(getenv("LINK_ANIMATIONS")){animation_tests();return;}
 disconnected=count-1;run(360);
 for(int i=0;i<count;i++)assert(rd(i,game_addr+12)==31);
}
int main(int argc,char**argv){
 assert(argc==12);mLogSetDefaultLogger(&logger);
 count=atoi(argv[2]);scenario=atoi(argv[3]);graphics=atoi(argv[4]);
 host=scenario==0||scenario==4?0:scenario==2?count-1:1;
 char host_text[4];snprintf(host_text,sizeof host_text,"%d",host);setenv("LINK_AUTHORITY",host_text,1);
 if(getenv("LINK_BENCHMARK"))perf_stage=address("ROLE_STAGE");
 game_addr=strtoul(argv[5],0,16);mp_addr=strtoul(argv[6],0,16);prefs_addr=strtoul(argv[7],0,16);
 avatars_addr=strtoul(argv[8],0,16);create_addr=strtoul(argv[9],0,16);avatar_edit_addr=strtoul(argv[10],0,16);host_addr=strtoul(argv[11],0,16);
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
 elect();
 if(scenario==7){
  int guest=(host+1)%count;press(guest,2);assert(rd(guest,game_addr+12)==39);
  for(int i=0;i<count;i++)if(i!=guest)c[i]->setKeys(c[i],2);
  run(32);for(int i=0;i<count;i++)c[i]->setKeys(c[i],0);run(32);
  for(int i=0;i<count;i++)assert(rd(i,game_addr+12)==39);
  retried=1;elect();printf("PASS: cancel during host settings returns to role menu; fresh election succeeds\n");
 }
 play();
 for(int i=0;i<count;i++)for(int j=0;j<128;j++)assert(c[i]->busRead8(c[i],0x0e000000+j)==saved[i][j]);
 printf("PASS create/join count=%d host=%d scenario=%d graphics=%d: election, profiles, settings, input, disconnect, SRAM\n",count,host,scenario,graphics);
 return 0;
}
