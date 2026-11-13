/* Live ROM input with deterministic rare-state fixtures. No animation code is
 * reimplemented here: observe each core's local poses and event counters. */
static uint32_t anim_address(const char*name){const char*v=getenv(name);assert(v);return strtoul(v,0,16);}
static void anim_messages(void){
 /* The authority changes mode before its event finishes crossing the cable.
  * Wait for that particular event's tokens/mode, never for matching text: the
  * latter would conceal a broken local formatter or a subsequent dialogue. */
 int authority=getenv("LINK_AUTHORITY")?atoi(getenv("LINK_AUTHORITY")):0;
 uint32_t tokens=anim_address("LINK_MESSAGE_TOKENS_ADDR");
 unsigned first=rd(authority,tokens),second=rd(authority,tokens+4),mode=rd(authority,game_addr+12);
 for(int t=0;t<300;t++){
  int ready=1;
  for(int i=0;i<count;i++)if(rd(i,tokens)!=first||rd(i,tokens+4)!=second||rd(i,game_addr+12)!=mode)ready=0;
  if(ready)break;run(1);assert(t<299);
 }
 for(int line=0;line<2;line++){
  uint32_t address=anim_address(line?"LINK_MESSAGE2_ADDR":"LINK_MESSAGE1_ADDR");
  uint32_t original=rd(0,address);
  for(int i=1;i<count;i++)for(unsigned j=0;j<96;j++){
   unsigned ch=c[0]->busRead8(c[0],original+j);
   assert(c[i]->busRead8(c[i],rd(i,address)+j)==ch);
   if(!ch)break;assert(j<95);
  }
 }
}
static void anim_mode(unsigned mode){
 for(int t=0;t<300;t++){int ready=1;for(int i=0;i<count;i++){assert(rd(i,game_addr+12)!=31);if(rd(i,game_addr+12)!=mode)ready=0;}if(ready){run(8);anim_messages();return;}run(1);}
 assert(0);
}
static void anim_tap(int node){c[node]->setKeys(c[node],1);run(12);c[node]->setKeys(c[node],0);run(12);}
static void animation_tests(void){
 int authority=getenv("LINK_AUTHORITY")?atoi(getenv("LINK_AUTHORITY")):0;
 uint32_t scene=anim_address("LINK_SCENE_ADDR"),events=anim_address("LINK_EVENTS_ADDR"),cash=anim_address("LINK_CASH_ADDR");
 unsigned poses[3],before[3],sent_before;
 wr(authority,game_addr+12,1);wr(authority,game_addr+20,2);wr(authority,game_addr+81*4,1);run(60);
 anim_tap(0);anim_mode(2);unsigned target=rd(authority,scene+156);
 for(int i=0;i<count;i++){before[i]=rd(i,events);poses[i]=rd(i,game_addr+73*4);assert(rd(i,scene+156)==target);}
 sent_before=transfers;anim_tap(1);run(60);
 for(int i=0;i<count;i++){assert(rd(i,game_addr+12)==2);assert(rd(i,game_addr+73*4)>poses[i]);assert(rd(i,events)==before[i]);}
 printf("ANIMATION spin: %u transfers over 84 VBlanks, zero pose events; spectator cannot skip\n",(unsigned)transfers-sent_before);
 for(int t=0;t<1000&&rd(authority,game_addr+12)==2;t++)run(1);
 assert(rd(authority,game_addr+12)!=2);run(60);
 for(int i=0;i<count;i++)assert(rd(i,game_addr+28)==target);
 anim_messages();printf("PASS: local wheel animation reaches authoritative target on every console\n");
 /* Start another spin and skip from its owner. */
 wr(authority,game_addr+12,1);wr(authority,game_addr+20,0);wr(authority,game_addr+81*4,1);run(60);
 anim_tap(1);anim_mode(2);target=rd(authority,scene+156);anim_tap(1);run(60);
 /* The skip has already reached the authority; its result still needs both
  * relay legs when the host is on a child port. Keep the input deadline and
  * separately wait for the checked result, as for other mode transitions. */
 assert(rd(authority,game_addr+12)!=2);anim_mode(rd(authority,game_addr+12));
 for(int i=0;i<count;i++){assert(rd(i,game_addr+12)!=2);assert(rd(i,game_addr+28)==target);}
 printf("PASS: owner skip retains the previously announced wheel target\n");
 for(int reaction=0;reaction<2;reaction++){
  wr(authority,game_addr+12,4);wr(authority,game_addr+20,0);wr(authority,game_addr+32,reaction?50:100);wr(authority,game_addr+70*4,0);
  for(int j=0;j<20;j++)wr(authority,game_addr+(18+j)*4,0);
  for(int j=0;j<32;j++)wr(authority,game_addr+(38+j)*4,0);
  run(60);anim_tap(1);anim_mode(16);
  unsigned old_score=rd(authority,game_addr+9*4),score=rd(authority,scene+148);
  if(reaction)run(180);
  for(int i=0;i<count;i++){before[i]=rd(i,events);poses[i]=rd(i,scene+44);}
  sent_before=transfers;run(60);
  for(int i=0;i<count;i++){assert(rd(i,game_addr+12)==16);assert(rd(i,scene+44)>poses[i]);assert(rd(i,events)==before[i]);assert(rd(i,game_addr+9*4)==old_score);}
  printf("ANIMATION assistant reaction=%d: %u transfers over 60 VBlanks, zero pose events\n",reaction,(unsigned)transfers-sent_before);
  for(int t=0;t<1000&&rd(authority,game_addr+12)==16;t++)run(1);
  assert(rd(authority,game_addr+12)!=16);run(60);
  for(int i=0;i<count;i++){assert(rd(i,game_addr+9*4)==score);for(int j=0;j<20;j++)assert(rd(i,game_addr+(18+j)*4)==rd(authority,game_addr+(18+j)*4));}
 }
 anim_messages();printf("PASS: helper moves/opens letters locally; score is committed only by the host\n");
 uint32_t ticks=anim_address("LINK_VIDEO_TICKS_ADDR");
 wr(authority,game_addr+12,17);wr(authority,game_addr+20,2);wr(authority,scene+12,rd(authority,ticks));anim_mode(17);
 unsigned round=rd(authority,game_addr+16);
 for(int i=0;i<count;i++){before[i]=rd(i,events);poses[i]=rd(i,scene)-rd(i,scene+12);}
 run(60);
 for(int i=0;i<count;i++){assert(rd(i,events)==before[i]);assert(rd(i,scene)-rd(i,scene+12)>poses[i]);assert(rd(i,game_addr+16)==round);}
 anim_tap(0);anim_mode(15);
 for(int i=0;i<count;i++){assert(rd(i,game_addr+16)==round+1);before[i]=rd(i,events);poses[i]=rd(i,scene+172);}
 run(40);
 for(int i=0;i<count;i++){assert(rd(i,events)==before[i]);assert(rd(i,scene+172)>poses[i]);}
 printf("PASS: credits clock and host mouth animate locally; round transition remains authoritative\n");
 if(count==2){
  wr(authority,game_addr+12,4);wr(authority,game_addr+20,1);wr(authority,game_addr+32,100);wr(authority,scene+4,rd(authority,ticks)-180);
  anim_mode(18);anim_messages();printf("PASS: AI position announcement is formatted locally\n");
  wr(authority,game_addr+12,3);wr(authority,game_addr+32,50);wr(authority,scene+4,rd(authority,ticks)-180);
  run(60);anim_mode(18);anim_messages();printf("PASS: AI letter announcement is formatted locally\n");
 }
 wr(authority,game_addr+12,7);wr(authority,game_addr+20,2);wr(authority,game_addr+81*4,0);wr(authority,game_addr+82*4,0);run(60);
 for(int offer=1;offer<=4;offer++){
  anim_tap(0);run(60);anim_messages();
  for(int i=0;i<count;i++){assert(rd(i,game_addr+12)==7);assert(rd(i,game_addr+82*4)==(unsigned)offer);}
 }
 printf("PASS: all four prize offers are formatted locally\n");
 wr(authority,game_addr+12,7);wr(authority,game_addr+20,2);wr(authority,game_addr+81*4,0);wr(authority,game_addr+82*4,3);wr(authority,game_addr+83*4,100000);run(60);anim_messages();
 anim_tap(0);anim_mode(21);run(150);
 for(int i=0;i<count;i++){before[i]=rd(i,events);poses[i]=rd(i,cash);}
 sent_before=transfers;run(60);
 for(int i=0;i<count;i++){assert(rd(i,cash)>poses[i]);assert(rd(i,events)==before[i]);}
 printf("ANIMATION cash: %u transfers over 60 VBlanks, zero note events\n",(unsigned)transfers-sent_before);
 anim_tap(0);run(60);
 for(int i=0;i<count;i++){assert(rd(i,cash)==10000);assert(rd(i,cash+4)==10000);assert(rd(i,cash+8)==rd(authority,cash+8));}
 printf("PASS: cash seed/amount animates locally; skip converges to identical final state\n");
 disconnected=count-1;run(300);
 for(int i=0;i<count;i++)assert(rd(i,game_addr+12)==31);
 printf("PASS: keepalive detects disconnect during local presentation\n");
}
