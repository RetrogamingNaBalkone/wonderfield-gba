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
 set_mode(pending);game.wait=wait;scene.speech_at=video_ticks;
}
static int scene_tick(u16 pressed){
 if(game.mode!=SPIN&&scene.now-scene.last_redraw>=3){scene.last_redraw=scene.now;dirty=1;}
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
  if(scene.now-scene.start<90)return 1;
  scene.host_active=0;
  if(scene.now-scene.phase_at>=3){
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
