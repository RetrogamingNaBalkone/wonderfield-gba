/* Actual menu flow: first creator is authority, independently of SIO port. */
#define main link_regression_main
#include "test-link.c"
#undef main
static uint32_t prefs_addr,avatars_addr,create_addr,avatar_edit_addr,host_addr;
static int scenario,graphics,host,retried;
static uint32_t address(const char*name){const char*v=getenv(name);assert(v);return strtoul(v,0,16);}
static void capture(const char*stage){
 const char*directory=getenv("ROLE_SCREENSHOTS");
 if(!directory||count!=2||(scenario!=1&&scenario!=8)||graphics!=1)return;
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
 if(creator)assert(rd(i,game_addr+12)==32||rd(i,game_addr+12)==30);
 else assert(rd(i,address("ROLE_PROFILE_PENDING"))==1);
 assert(!rd(i,address("ROLE_NAME_EDIT")));
}
static void configure(int i){
 assert(rd(i,game_addr+12)==32||rd(i,address("ROLE_CONFIG_MODE"))==32);
 wr(i,prefs_addr,0);wr(i,prefs_addr+4,0);wr(i,prefs_addr+8,graphics);
 wr(i,prefs_addr+16,1);wr(i,prefs_addr+20,5);
}
static unsigned key_color(int node,unsigned cursor){
 unsigned page=(c[node]->busRead16(c[node],0x04000000)&16)?0xa000:0;
 return c[node]->busRead8(c[node],0x06000000+page+(88+cursor/8*16)*240+10+cursor%8*28);
}
static void verify_keyboard_frame(int node,int shared){
 unsigned char pixels[240*160];
 unsigned page=(c[node]->busRead16(c[node],0x04000000)&16)?0xa000:0;
 for(unsigned i=0;i<sizeof pixels;i++)pixels[i]=c[node]->busRead8(c[node],0x06000000+page+i);
 if(shared){wr(node,address("ROLE_KEYBOARD_VALID"),0);wr(node,address("ROLE_DIRTY"),1);}
 else{wr(node,address("ROLE_PROFILE_CURSOR"),0xffffffffu);wr(node,address("ROLE_PROFILE_RENDER_KEY"),0xffffffffu);}
 run(24);page=(c[node]->busRead16(c[node],0x04000000)&16)?0xa000:0;
 for(unsigned i=0;i<sizeof pixels;i++)assert(pixels[i]==c[node]->busRead8(c[node],0x06000000+page+i));
 printf("PASS: incremental %s keyboard matches a full redraw (node %d)\n",shared?"game":"name",node);
}
static void latency(const char*label,int node,uint32_t cursor,int shared){
 unsigned worst=0,local_worst=0,owner_worst=0,paint_worst=0;
 for(int phase=0;phase<8;phase++){
  run(24+phase);unsigned before=rd(shared?host:node,cursor),frames=0,local=0,owner=0,paint=0,synced=0;
  assert(key_color(node,before)==14);
  c[node]->setKeys(c[node],16);
  for(;frames<120;frames++){
   run(1);if(frames==1)c[node]->setKeys(c[node],0);
   if(!local&&rd(shared?host:node,cursor)!=before)local=frames+1;
   if(!owner&&(rd(node,cursor)!=before||(shared&&getenv("LINK_PREVIEW_SUPPORTED")&&rd(node,address("ROLE_PREVIEW_VALID"))&&rd(node,address("ROLE_PREVIEW_CURSOR"))!=before)))owner=frames+1;
   if(!paint&&key_color(node,(before+1)%32)==14&&key_color(node,before)==11)paint=frames+1;
   int ready=1;for(int i=0;i<count;i++)if((shared||i==node)&&rd(i,cursor)==before)ready=0;
   if(ready&&!synced)synced=frames+1;
   if(ready&&paint)break;
  }
  c[node]->setKeys(c[node],0);assert(frames<120);
  if(synced>worst)worst=synced;if(local>local_worst)local_worst=local;
  if(owner>owner_worst)owner_worst=owner;
  if(paint>paint_worst)paint_worst=paint;
  run(30);for(int i=0;i<count;i++)if(shared||i==node)assert(rd(i,cursor)==(before+1)%32);
 }
 printf("LATENCY {\"profile\":\"%s\",\"node\":%d,\"owner_frames\":%u,\"visible_frames\":%u,\"host_frames\":%u,\"all_frames\":%u}\n",label,node,owner_worst,paint_worst,local_worst,worst);fflush(stdout);
 if(getenv("LINK_PREVIEW_SUPPORTED")&&count==2){assert(owner_worst<=8);assert(paint_worst<=10);assert(local_worst<=10);assert(worst<=(shared?20u:6u));}
 if(getenv("LINK_PREVIEW_SUPPORTED"))verify_keyboard_frame(node,shared);
}
static void elect(void){
 if(scenario>=8){
  /* Existing host on a child port, then create on the cable parent. */
  enter(host,1);configure(host);press(host,1);run(120);
  assert(rd(host,game_addr+12)==30);
  for(int i=0;i<count;i++)if(i!=host)enter(i,1);
  run(300);
  for(int i=0;i<count;i++)if(i!=host){
   assert(rd(i,host_addr)==(unsigned)host);
   assert(rd(i,address("ROLE_JOIN_PROMPT"))==1);
   assert(!rd(i,address("ROLE_NAME_EDIT"))&&rd(i,address("ROLE_PROFILE_PENDING")));
  }
  /* The invitation keeps waiting and cannot consume the create tap. */
  run(180);
  capture("existing-lobby-invitation");
  if(scenario==9){
   int guest=0;
   /* Two-console retry is the reported flow. With three consoles, also
    * verify declining does not accept the other pending invitation. */
   if(count==3){press(guest,2);assert(rd(guest,game_addr+12)==39);assert(rd(2,address("ROLE_JOIN_PROMPT")));return;}
   for(int attempt=0;attempt<3;attempt++){
    run(3*attempt);press(guest,2);assert(rd(guest,game_addr+12)==39);
    enter(guest,1);run(300);
    assert(rd(guest,address("ROLE_JOIN_PROMPT"))&&rd(guest,host_addr)==(unsigned)host);
   }
   printf("PASS: three decline/reopen attempts preserve the existing host and profile\n");
  }
  for(int i=0;i<count;i++)if(i!=host){press(i,1);assert(!rd(i,address("ROLE_JOIN_PROMPT"))&&!rd(i,create_addr));}
  printf("PASS: existing child-port lobby wins; new creators explicitly accept before profile entry\n");
 }else if(scenario==5){
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
    press(guest,16);press(guest,8);assert(rd(host,address("ROLE_CONFIG_MODE"))==32&&rd(host,prefs_addr+16)==rule);
   }
   for(int i=0;i<count;i++)if(i==host){
    configure(i);
    if(i!=host){wr(i,prefs_addr,1);wr(i,prefs_addr+8,!graphics);wr(i,prefs_addr+16,2);}
    c[i]->setKeys(c[i],1);
   }
   run(12);for(int i=0;i<count;i++)c[i]->setKeys(c[i],0);
  }
 }
 run(300);
 if(scenario==4)for(int i=0;i<count;i++)if(i!=host){assert(rd(i,address("ROLE_JOIN_PROMPT")));press(i,1);}
 if(scenario==6){
  for(int i=0;i<count;i++)if(i!=host)wr(i,create_addr,1);
  run(120);
  for(int i=0;i<count;i++)if(i!=host){assert(rd(i,address("ROLE_JOIN_PROMPT")));press(i,1);}
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
static void measure_event(const char*label,int owner){
 unsigned mode=rd(host,game_addr+12),revision=0,at=0,frames,wire=transfers;
 c[owner]->setKeys(c[owner],1);
 for(frames=1;frames<=900;frames++){
  run(1);if(frames==2)c[owner]->setKeys(c[owner],0);
  if(!at&&rd(host,game_addr+12)!=mode){at=frames;mode=rd(host,game_addr+12);revision=rd(host,address("ROLE_PRESENTATION_EVENT"));}
  int ready=at!=0;
  for(int i=0;i<count;i++){
   assert(rd(i,game_addr+12)!=31);
   if(rd(i,game_addr+12)!=mode||rd(i,address("ROLE_PRESENTATION_EVENT"))<revision)ready=0;
  }
  if(ready)break;
 }
 c[owner]->setKeys(c[owner],0);assert(at&&frames<=900);
 printf("EVENT_LATENCY {\"event\":\"%s\",\"owner\":%d,\"mode\":%u,\"host_to_all_frames\":%u,\"press_to_all_frames\":%u,\"transfers\":%u}\n",label,owner,mode,frames-at,frames,(unsigned)transfers-wire);fflush(stdout);
 if(count==2&&getenv("LINK_EVENT_COMPACT"))assert(frames-at<=32);
 anim_messages();run(20);
}
static void event_turn(int owner,int choice){
 wr(host,game_addr+12,1);wr(host,game_addr+20,(owner+2)%3);wr(host,game_addr+81*4,!choice);run(120);
 press(owner,choice?16:32);
 for(int t=0;t<600;t++){
  int ready=1;for(int i=0;i<count;i++)if(rd(i,game_addr+12)!=1||rd(i,game_addr+20)!=(unsigned)(owner+2)%3||rd(i,game_addr+81*4)!=(unsigned)choice)ready=0;
  if(ready)return;
  /* Fixtures can be written during an older packet; wait for the new
   * owner and a real navigation event before timing the next action. */
  if(t&&t%120==0)press(owner,choice?16:32);
  run(1);
 }
 assert(0);
}
static void event_latency(void){
 for(int owner=0;owner<count;owner++){
  event_turn(owner,0);measure_event("solve_prompt",owner);
  event_turn(owner,1);measure_event("spin_start",owner);
  assert(rd(host,game_addr+12)==2);measure_event("spin_result_message",owner);
 }
 disconnected=count-1;run(360);for(int i=0;i<count;i++)assert(rd(i,game_addr+12)==31);
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
 if(getenv("LINK_EVENT_LATENCY")){event_latency();return;}
 /* The elected host owns rules, but still cannot act for another player. */
 if(getenv("LINK_LATENCY")){
  for(int i=0;i<count;i++){
   event_turn(i,0);
   press(i,1);run(180);
   for(int j=0;j<count;j++)assert(rd(j,game_addr+12)==5);
   latency("keyboard",i,game_addr+70*4,1);
   unsigned cursor=rd(host,game_addr+70*4);
   c[i]->setKeys(c[i],16);run(2);c[i]->setKeys(c[i],0);run(1);
   c[i]->setKeys(c[i],1);run(2);c[i]->setKeys(c[i],0);run(180);
   for(int j=0;j<count;j++){
    assert(rd(j,game_addr+70*4)==(cursor+1)%32);
    assert(rd(j,game_addr+80*4)==1);
    assert(c[j]->busRead8(c[j],game_addr+88*4)==128+(cursor+1)%32);
   }
   printf("PASS: queued direction then A selects the authoritative letter once (owner %d)\n",i);
  }
 }
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
 if(getenv("LINK_BENCHMARK")||getenv("LINK_LATENCY"))perf_stage=address("ROLE_STAGE");
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
 if(getenv("LINK_LATENCY"))for(int i=0;i<count;i++)latency("name",i,address("ROLE_NAME_CURSOR"),0);
 if(scenario==7){
  /* Cancel together: otherwise faster polling may correctly report that
   * the first guest has disconnected before the others press B. */
  press(-1,2);
  for(int i=0;i<count;i++)assert(rd(i,game_addr+12)==39);
  retried=1;elect();printf("PASS: cancel during host settings returns to role menu; fresh election succeeds\n");
 }
 if(scenario!=9||count!=3)play();
 for(int i=0;i<count;i++)for(int j=0;j<128;j++)assert(c[i]->busRead8(c[i],0x0e000000+j)==saved[i][j]);
 printf("PASS create/join count=%d host=%d scenario=%d graphics=%d: election, profiles, settings, input, disconnect, SRAM\n",count,host,scenario,graphics);
 return 0;
}
