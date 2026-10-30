/* Non-blocking versions of DOS introduction, face movement and letter reveal. */
static void intro_phrase(void){
 switch(scene.phase){
 case 0:say(msg_1011,msg_101d);break;
 case 1:say(msg_5384,opponent_names[game.opponent[game.round*2]]);break;
 case 2:say(msg_5391,opponent_names[game.opponent[game.round*2+1]]);break;
 case 3:say(msg_539e,msg_53ab);break;
 case 4:say(msg_f30,msg_f20);break;
 default:say(msg_f3f,words[game.word_id].topic);break;
 }
}
static void intro_begin(void){
 set_mode(INTRO);scene.phase=0;scene.phase_at=video_ticks;intro_phrase();
}
static void reveal_begin(void){
 scene.pending_mode=game.mode;scene.pending_wait=game.wait;
 /* Be visible while the host reacts; do not wait outside the screen. */
 set_mode(REVEAL);scene.start=video_ticks;scene.actor_x=32;scene.actor_stop=0;scene.phase_at=video_ticks;
}
static void credits_begin(void){set_mode(CREDITS);scene.start=video_ticks;}
static void complete_reveal(void){
 for(int i=0;i<20;i++)game.revealed[i]=scene.reveal_target[i];
 game.score[game.player]=scene.pending_score;
 scene.host_active=0;
 int pending=scene.pending_mode,wait=scene.pending_wait;
 if(pending==ROUND_END){finish_round();return;}
 if(pending==TURN){begin_turn();return;}
 set_mode(pending);game.wait=wait;scene.speech_at=video_ticks;
}
static unsigned cash_random(unsigned n){cash.rng=cash.rng*134775813u+1;return (cash.rng>>16)%n;}
static u32 cash_advance(u32 seed,unsigned count){
 u32 mul=134775813u,add=1;
 while(count){if(count&1)seed=seed*mul+add;add*=mul+1;mul*=mul;count>>=1;}return seed;
}
static void cash_note(void){
 /* DOS 1000:4442..447c: Random(50), Random(400), Random(295),
  * transparent colour 2; retain every previous stamp. */
 unsigned hz=cash_random(50),x=cash_random(400),y=cash_random(295);
 /* The blitter's Pascal argument order is X then Y on the stack. */
 int px=(int)(x*35/96),py=(int)(y/2);
 const Sprite*s=&sprites_half[56];
 for(int yy=0;yy<s->h;yy++)for(int xx=0;xx<s->w;xx++){
  int dx=px+xx,dy=py+yy;u8 c=s->data[yy*s->w+xx];
  if(c!=2&&(unsigned)dx<240&&(unsigned)dy<152)cash_canvas[dy*240+dx]=c;
 }
 unsigned before=cash.drawn*5672/1000;cash.drawn++;
 speaker_queue_tone(hz,cash.drawn*5672/1000-before);
}
static void cash_skip(void){
 if(cash.total>=10000){
  /* A fixed finished picture makes even a million-ruble skip constant-time. */
  cash.rng=cash_advance(cash.rng,(cash.total-cash.drawn)*3);
  dma_words((u32*)cash_canvas,(const u32*)cash_finished_bitmap,9600);
  cash.drawn=cash.total;
 }else while(cash.drawn<cash.total)cash_note();
 cash.ready=1;scene.host_active=0;speaker_tone(0,1);dirty=1;
}
static void cash_begin(void){
 game.deal=5;game.keyboard=0;set_mode(CASH);say(msg_ffa,msg_1004);
 cash.drawn=0;cash.total=game.prize/10;cash.rng=game.rng;cash.ready=0;cash.credit=0;cash.next_at=video_ticks+120;
 rect(0,0,240,160,7);half_image(46,4,4,7);half_image(47,73,4,7);
 half_image(27,185,75,-1);half_image(45,196,76,-1);half_image(43,204,94,-1);
 dma_words((u32*)cash_canvas,(const u32*)framebuffer,9600);
}
static void visual_tick(void){
 /* One transition per displayed pose; never skip a short mouth pulse
  * when rendering took longer than its deadline. Rendering is read-only. */
 if(host_visible()&&scene.host_phase<10&&scene.now-scene.host_phase_at>=host_durations[scene.host_phase]){
  scene.host_phase++;scene.host_phase_at=scene.now;
 }
}
static u32 visual_key(void){
 u32 key=(u32)game.mode<<24,age;
 if(game.mode==TITLE){age=scene.now-scene.title_at;return key|(age<80?age:age<100?80:100);}
 if(game.mode==SOLVE||game.mode==NAME||game.mode==GIFT_PAGES||game.mode==HELP||game.mode==RECORDS||game.mode==GALLERY)return key;
 if(speech_visible())key|=1;
 if(host_visible())key|=(scene.host_phase+1)<<1;
 if(game.mode==INTRO&&(scene.phase==1||scene.phase==2)){
  age=scene.now-scene.phase_at;key|=(age<54?age/18:3)<<5;
 }
 if(game.mode==CHEST){age=scene.now-scene.speech_at;key|=(age<90?(age/6)&1:2)<<7;}
 if(game.mode==RESULT&&scene.now<scene.chest_until)key|=1u<<9;
 /* Reveal steps already invalidate at their five-VBlank cadence. An
  * independent gait redraw between steps would delay the next movement. */
 if(game.mode==SPIN)key|=((game.sector*2+scene.spin_half)&31)<<10;
 if(game.mode==CREDITS){age=scene.now-scene.start;key|=(age<40?age:40)<<10;}
 return key;
}
static int scene_tick(u16 pressed){
 if(game.mode==CASH){
  if(pressed&A){
   if(cash.drawn<cash.total){
    cash_skip();
   }else farewell();
   return 1;
  }
  if(cash.drawn<cash.total&&(int)(scene.now-cash.next_at)>=0){
   /* 5000-cycle DOS reference: 5.672 ms/note; a GBA VBlank is 16.743 ms.
    * Carry fractions and catch up after drawing, rather than slowing the
    * original animation to one bill per rendered frame. */
   cash.ready=1;scene.host_active=0;cash.credit+=(scene.now-cash.next_at+1)*16743;
   unsigned notes=divide(cash.credit,5672);cash.credit%=5672;cash.next_at=scene.now+1;
   while(notes--&&cash.drawn<cash.total)cash_note();dirty=1;
  }
  return 1;
 }
 if(game.mode==INTRO){
  if((pressed&A)||(scene.now-scene.phase_at>150)){
   if(++scene.phase>=6){begin_turn();return 1;}
   scene.phase_at=scene.now;intro_phrase();
  }
  return 1;
 }
 if(game.mode==CREDITS){
  if(((pressed&A)&&scene.now-scene.start>30)||scene.now-scene.start>600){game.round++;new_round();}
  return 1;
 }
 if(game.mode==REVEAL){
  if(pressed&A){complete_reveal();return 1;}
  if(game.sector_value!=100&&scene.now-scene.start<90)return 1;
  scene.host_active=0;
  /* Walking and each stop previously advanced once per five-VBlank
   * rendered frame. Use that cadence independently of rendering cost. */
  if(scene.now-scene.phase_at>=5){
   scene.phase_at=scene.now;
   int n=len(word()),left=30+((20-n)/2)*9,next=-1;
   for(int i=0;i<n;i++)if(scene.reveal_target[i]&&!game.revealed[i]){next=i;break;}
   if(scene.actor_stop>0){
    scene.actor_stop--;
    /* Turn the cell halfway through the stop, with the figure beside it. */
    if(scene.actor_stop==3&&next>=0)game.revealed[next]=1;
   }else{
    int target=next>=0?left+(next+1)*9:225;
    if(scene.actor_x+4>=target){scene.actor_x=target;if(next>=0)scene.actor_stop=6;}
    else scene.actor_x+=4;
   }
   dirty=1;
   if(scene.actor_x>=225){complete_reveal();return 1;}
  }
  return 1;
 }
 return 0;
}
