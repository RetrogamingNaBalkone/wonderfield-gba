/* POLE game rules recovered in analysis/decompiled.c; addresses in docs/reverse.md. */
#include "assets.h"
#include "speaker.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#define REG16(a) (*(volatile u16 *)(a))
#define REG32(a) (*(volatile u32 *)(a))
#define A 1
#define B 2
#define SELECT 4
#define START 8
#define RIGHT 16
#define LEFT 32
#define UP 64
#define DOWN 128
#define R 256
#define L 512
enum {TITLE,TURN,SPIN,LETTER,PLUS,SOLVE,RESULT,PRIZE,CHEST,ROUND_END,GAME_OVER,HELP,RECORDS,GALLERY,NAME,INTRO,REVEAL,CREDITS,AI_ANSWER,GIFT_PAGES,FINAL_RECORDS,CASH};
/* Read-only diagnostic state is also used by the emulator integration checks. */
typedef struct {
 u32 magic,frame,rng; int mode,round,player,word_id,sector,sector_value;
 int score[3],opponent[6],revealed[20],used[32],cursor,keyboard;
 int streak,spin_ticks,spin_steps,spin_wait,wait,next_mode,next_player;
 int solved,solve_pos,choice,deal,prize,album,best,paused,return_mode;
 char answer[21];
} Game;
volatile Game game;
static u8 framebuffer[240*160] __attribute__((aligned(4)));
static u8 cash_canvas[240*160] __attribute__((aligned(4)));
static volatile struct {u32 drawn,total,rng,next_at,pause_at;int ready;u32 credit;} cash;
static const char *message1,*message2;
static char sector_message[32],turn_line[32];
volatile u32 video_ticks;
static struct {
 u32 now,speech_at,last_redraw,start,phase_at,spin_at,title_at,chest_until;
 int phase,pending_mode,pending_wait,actor_x,actor_stop,old_score,reward_chest,chest_money;
 int reveal_target[20];
 int ai_letter,pending_score,spin_half,spin_target;
 u32 host_at,host_seed;int host_active;
 int host_phase;u32 host_phase_at;
 int gift_final,gift_page;
} scene;
static void intro_begin(void);
static void reveal_begin(void);
static int scene_tick(u16 pressed);
static volatile u16 input_events[32],input_keys;
static volatile u8 input_read,input_write;
static void capture_keys(void){
 u16 keys=(~REG16(0x04000130))&1023,pressed=keys&~input_keys;input_keys=keys;
 if(pressed){u8 next=(input_write+1)&31;if(next!=input_read){input_events[input_write]=pressed;input_write=next;}}
}
void game_irq(unsigned flags){if(flags&1){video_ticks++;capture_keys();}speaker_irq(flags);}

static u16 oldkeys;
static u32 repeat_at,rendered_key=~0u,solve_fixed;
static u8 host_durations[10];
volatile u32 rendered_frames;
static volatile int dirty=1;
static int sound_on=1;
static char record_names[8][11];
static int record_scores[8],record_entry=-1,selected_words[3];
static const char save_id[] __attribute__((used,section(".rodata.save_id")))="SRAM_V113";
static unsigned divide(unsigned a,unsigned b){unsigned q=0,r=0;for(int i=31;i>=0;i--){r=(r<<1)|((a>>i)&1);if(r>=b){r-=b;q|=1u<<i;}}return q;}
static int len(const char *s){int n=0;while(s[n])n++;return n;}
static unsigned random_n(unsigned n){game.rng=game.rng*134775813u+1;return (game.rng>>16)%n;}
static void effect(unsigned id){u32 seed=game.rng;if(!id)for(int i=0;i<6;i++)random_n(100);speaker_effect(id,seed);}
static void pixel(int x,int y,u8 c){if((unsigned)x<240 && (unsigned)y<160)framebuffer[y*240+x]=c;}
static void rect(int x,int y,int w,int h,u8 c){for(int j=0;j<h;j++)for(int i=0;i<w;i++)pixel(x+i,y+j,c);}
static void line(int x,int y,int w,u8 c){rect(x,y,w,1,c);}
static void glyph(int x,int y,unsigned c,int small,u8 color){int h=small?8:14;const u8 *f=small?font8:font14;for(int j=0;j<h;j++)for(int i=0;i<8;i++)if(f[c*h+j]&(128>>i))pixel(x+i,y+j,color);}
static void text(int x,int y,const char *s,int small,u8 c){int advance=8;for(int i=0;s[i];i++)glyph(x+i*advance,y,(u8)s[i],small,c);}
static void centered(int y,const char*s,int small,u8 c){text((240-len(s)*8)/2,y,s,small,c);}
static void number(int x,int y,int value,int small,u8 c){char b[12];int n=0;unsigned v=value<0?-value:value;do{b[n++]='0'+v%10;v/=10;}while(v);if(value<0)b[n++]='-';for(int i=n-1;i>=0;i--)glyph(x+(n-1-i)*8,y,b[i],small,c);}
static void sprite(int id,int x,int y,int scale,int transparent){const Sprite*s=&sprites[id];int w=(s->w*scale)>>8,h=(s->h*scale)>>8;unsigned step=divide(65536,scale);for(int j=0;j<h;j++){int sy=(j*step)>>8;for(int i=0;i<w;i++){int sx=(i*step)>>8;u8 c=s->data[sy*s->w+sx];if(c!=transparent)pixel(x+i,y+j,c);}}}
static void beep(int hz,int duration){speaker_tone(hz,duration*4);}
static void vblank(void){while(REG16(0x04000006)>=160){}while(REG16(0x04000006)<160){}}
static void dma_words(u32*destination,const u32*source,unsigned count){while(count){unsigned n=count>64?64:count;REG32(0x040000d4)=(u32)source;REG32(0x040000d8)=(u32)destination;REG32(0x040000dc)=0x84000000|n;source+=n;destination+=n;count-=n;}}
static void present(void){static unsigned page;page^=1;u32*destination=(u32*)(page?0x0600a000:0x06000000);dma_words(destination,(const u32*)framebuffer,9600);vblank();REG16(0x04000000)=0x0404|(page?16:0);}
static void save(void){
 volatile u8*s=(volatile u8*)0x0e000000;u32 hash=2166136261u;int p=4;
 for(int i=0;i<8;i++){for(int j=0;j<11;j++)s[p++]=record_names[i][j];for(int j=0;j<4;j++)s[p++]=record_scores[i]>>(j*8);}
 for(int i=4;i<p;i++)hash=(hash^s[i])*16777619;
 for(int i=0;i<4;i++)s[p+i]=hash>>(i*8);
 s[0]='P';s[1]='O';s[2]='L';s[3]='2';
}
static int load(void){
 volatile u8*s=(volatile u8*)0x0e000000;u32 hash=2166136261u,stored=0;int valid=s[0]=='P'&&s[1]=='O'&&s[2]=='L'&&s[3]=='2';
 for(int i=4;i<124;i++)hash=(hash^s[i])*16777619;
 for(int i=0;i<4;i++)stored|=(u32)s[124+i]<<(i*8);
 valid=valid&&hash==stored;int p=4;
 for(int i=0;i<8;i++){for(int j=0;j<11;j++)record_names[i][j]=valid?s[p++]:j<len(initial_names[i])?initial_names[i][j]:0;record_names[i][10]=0;record_scores[i]=0;if(valid){for(int j=0;j<4;j++)record_scores[i]|=(u32)s[p++]<<(j*8);}else record_scores[i]=initial_scores[i];}
 return record_scores[0];
}
static const char*word(void){return words[game.word_id].word;}
static void set_mode(int mode){if(mode==TITLE)scene.title_at=video_ticks;game.mode=mode;game.wait=0;dirty=1;}
static void say(const char*a,const char*b){
 message1=a;message2=b;scene.speech_at=scene.host_at=scene.host_phase_at=video_ticks;
 scene.host_active=1;scene.host_phase=0;effect(0);scene.host_seed=game.rng;
 host_durations[0]=12;host_durations[1]=host_durations[2]=9;host_durations[9]=6;
 u32 seed=scene.host_seed;
 for(int i=0;i<3;i++){
  seed=seed*134775813u+1;host_durations[3+i*2]=6+((seed>>16)&1)*12;
  seed=seed*134775813u+1;host_durations[4+i*2]=6+((seed>>16)&1)*3;
 }
 /* Speech used to advance on the eight-VBlank redraw cadence. Keep
  * that wall-clock pacing after removing the render-bound delay. */
 for(int i=0;i<10;i++)host_durations[i]=(host_durations[i]+7)&~7;
 dirty=1;
}
static void farewell(void){set_mode(GAME_OVER);game.keyboard=0;game.deal=0;say(msg_f9a,msg_fa9);}
static void result(const char*a,const char*b,int next,int player){say(a,b);set_mode(RESULT);game.next_mode=next;game.next_player=player;game.wait=game.player==2?0:65;}
static int nextplayer(void){return (game.player+1)%3;}
static void begin_turn(void){set_mode(TURN);game.choice=1;const char*a=game.player==2?msg_d9a:game.player==0?msg_d8c:msg_d93;int p=0;while(a[p]){turn_line[p]=a[p];p++;}for(int i=0;msg_da1[i];i++)turn_line[p++]=msg_da1[i];turn_line[p]=0;say(turn_line,msg_da9);if(game.player!=2)game.wait=65;}
static void new_round(void){int duplicate;do{game.word_id=random_n(495);duplicate=0;for(int i=0;i<game.round;i++)if(selected_words[i]==game.word_id)duplicate=1;}while(duplicate);selected_words[game.round]=game.word_id;for(int i=0;i<20;i++)game.revealed[i]=0;for(int i=0;i<32;i++)game.used[i]=0;game.score[0]=game.score[1]=0;game.player=2;game.streak=0;game.solved=0;game.deal=game.prize=game.keyboard=0;begin_turn();intro_begin();}
static void new_game(void){game.round=0;game.score[2]=0;game.sector=12;for(int i=0;i<6;i++)game.opponent[i]=i;for(int i=0;i<20;i++){int a=random_n(6),b=random_n(6),t=game.opponent[a];game.opponent[a]=game.opponent[b];game.opponent[b]=t;}new_round();}
static int hidden(void){int n=0;for(int i=0;word()[i];i++)if(!game.revealed[i])n++;return n;}
static void finish_round(void){
 for(int i=0;word()[i];i++)game.revealed[i]=1;
 game.solved=1;set_mode(ROUND_END);
 if(game.player==2&&game.round==2)say(msg_f7b,msg_f8a);
 else{
  const char*a=game.player==2?msg_d9a:game.player==0?msg_d8c:msg_d93;
  int p=0;while(a[p]){turn_line[p]=a[p];p++;}
  for(int i=0;msg_e9f[i];i++)turn_line[p++]=msg_e9f[i];
  turn_line[p]=0;say(turn_line,msg_ea6);
 }
 effect(3);
}
static void gift_begin(int final){
 scene.gift_final=final;scene.gift_page=0;scene.host_active=0;game.keyboard=0;
 if(final){game.prize=random_n(10);game.deal=0;}
 set_mode(GIFT_PAGES);
}
static void final_records(void){
 record_entry=-1;for(int i=7;i>=0;i--)if(game.score[2]>record_scores[i])record_entry=i;
 if(record_entry<0){set_mode(RECORDS);return;}
 for(int i=7;i>record_entry;i--){record_scores[i]=record_scores[i-1];for(int j=0;j<11;j++)record_names[i][j]=record_names[i-1][j];}
 record_scores[record_entry]=game.score[2];for(int j=0;j<11;j++)record_names[record_entry][j]=0;
 for(int j=0;j<21;j++)game.answer[j]=0;game.cursor=game.solve_pos=0;set_mode(NAME);
}
static void award_letter(int letter){
 int count=0;
 for(int i=0;word()[i];i++)if((u8)word()[i]==128+letter&&!game.revealed[i]){game.revealed[i]=1;count++;}
 game.used[letter]=1;game.keyboard=0;
 if(count){
  if(game.sector_value<100)game.score[game.player]+=game.sector_value*count;
  else if(game.sector_value/100==2)game.score[game.player]*=game.sector_value%100;
  effect(1);
  if(game.sector_value==100){
   /* DOS 1fcf returns straight to 1698. Only ordinary letter selection
    * (1a3a) calls host dialogue 3: Plus has no "there is that letter". */
   message1=message2="";scene.host_active=0;
   game.next_mode=TURN;game.next_player=game.player;
   set_mode(hidden()?TURN:ROUND_END);return;
  }
  if(!hidden()){set_mode(ROUND_END);say(msg_e77,msg_e65);return;}
  if(game.streak==3){game.streak=0;result(msg_e77,msg_e65,CHEST,game.player);return;}
  result(msg_e77,msg_e65,TURN,game.player);
 }else{effect(0);game.streak=0;result(msg_e7f,msg_e90,TURN,nextplayer());}
}

static void choose_letter(int letter){
 int before[20],count=0;
 for(int i=0;i<20;i++){before[i]=game.revealed[i];if(i<len(word())&&(u8)word()[i]==128+letter&&!before[i])count++;}
 scene.old_score=game.score[game.player];
 award_letter(letter);
 if(count){scene.pending_score=game.score[game.player];game.score[game.player]=scene.old_score;for(int i=0;i<20;i++){scene.reveal_target[i]=game.revealed[i];game.revealed[i]=before[i];}reveal_begin();}
}

static void ai_announce(int letter,int position){
 int p=0;const char*a=position?msg_1fc6:msg_1a30;
 if(position){int v=position;if(v>=10)turn_line[p++]='0'+v/10;turn_line[p++]='0'+v%10;}
 while(*a)turn_line[p++]=*a++;
 if(!position){turn_line[p++]=128+letter;for(int i=0;msg_1a38[i];i++)turn_line[p++]=msg_1a38[i];}
 turn_line[p]=0;scene.ai_letter=letter;set_mode(AI_ANSWER);say(turn_line,"");scene.host_active=0;
}
static void ai_letter(void){int remaining=hidden(),n=len(word()),letter;if(remaining*2>n&&remaining>=2){do{letter=random_n(32);}while(game.used[letter]);}else if(random_n(game.round+2)==0){do{letter=random_n(32);}while(game.used[letter]);}else{int p;do{p=random_n(n);}while(game.revealed[p]);letter=(u8)word()[p]-128;}ai_announce(letter,0);}
static void prize_offer(void){
 const char*t=game.deal==1?msg_41be:game.deal==2?msg_41c2:game.deal==3?msg_41c7:msg_41cf;
 int p=0;while(*t)sector_message[p++]=*t++;
 for(int i=0;msg_ff1[i];i++)sector_message[p++]=msg_ff1[i];sector_message[p]=0;say(msg_fe8,sector_message);
}
static void open_letter(void){set_mode(LETTER);game.cursor=0;game.keyboard=game.player==2;if(game.sector_value<100){int p=0;while(msg_dbb[p]){sector_message[p]=msg_dbb[p];p++;}int v=game.sector_value;if(v>=10)sector_message[p++]='0'+v/10;sector_message[p++]='0'+v%10;for(int i=0;msg_dc2[i];i++)sector_message[p++]=msg_dc2[i];sector_message[p]=0;say(sector_message,msg_dca);}else say(game.sector_value==300?msg_e47:msg_e12,msg_dca);if(game.player!=2)game.wait=55;}
static void stop_spin(void){int sector=game.sector;game.sector_value=sector_values[wheel_sectors[sector]-4];if(game.sector_value!=100)game.streak++;if(game.sector_value<0){game.streak=0;game.score[game.player]=0;result(msg_dfe,msg_dea,TURN,nextplayer());}else if(!game.sector_value){game.streak=0;result(msg_dda,msg_dea,TURN,nextplayer());}else if(game.sector_value==100){set_mode(PLUS);game.cursor=0;while(game.revealed[game.cursor])game.cursor++;say(msg_e26,msg_e33);if(game.player!=2)game.wait=60;}else if(game.sector_value==300&&game.player==2){set_mode(PRIZE);game.choice=1;game.deal=0;game.prize=10;say(msg_e47,msg_e54);}else{open_letter();}}
static void start_spin(void){
 set_mode(SPIN);int draw=64+random_n(32);
 scene.spin_target=(game.sector-draw)&15;
 /* Keep the same draw/RNG, animate only the equivalent one to two turns. */
 game.spin_steps=16+(draw&15);game.spin_ticks=0;game.spin_wait=1;scene.spin_half=0;scene.spin_at=video_ticks;
 say(msg_da9,"");scene.host_active=0;
}
static void end_result(void){int next=game.next_mode;game.player=game.next_player;if(next==TURN)begin_turn();else if(next==CHEST){set_mode(CHEST);game.choice=0;say(msg_eda,msg_ee6);if(game.player!=2)game.wait=60;}else if(next==GAME_OVER)farewell();else if(next==FINAL_RECORDS)final_records();else set_mode(next);}
static int fixed_letter(int letter){return (solve_fixed>>letter)&1;}
static void solve_advance(void){while(game.solve_pos<len(word())&&game.revealed[game.solve_pos])game.solve_pos++;}
static void solve_word(void){set_mode(SOLVE);game.solve_pos=0;solve_fixed=0;int n=len(word());for(int i=0;i<21;i++){game.answer[i]=i<n&&game.revealed[i]?word()[i]:0;if(i<n&&game.revealed[i])solve_fixed|=1u<<((u8)word()[i]-128);}solve_advance();game.cursor=0;while(game.cursor<31&&fixed_letter(game.cursor))game.cursor++;game.keyboard=1;say(msg_f20,"");}
static void confirm_word(void){int good=1;for(int i=0;word()[i];i++)if(game.answer[i]!=word()[i])good=0;if(good)finish_round();else{game.keyboard=0;game.streak=0;result(msg_f5b,msg_f6b,GAME_OVER,game.player);}}
#include "presentation.inc"
#include "scene.inc"
static void update(u16 pressed,u16 repeat){
 scene.now=video_ticks;
 if(game.mode==HELP){
  if(pressed&(A|B|START)){
   if(game.return_mode!=TITLE){
    u32 duration=video_ticks-(u32)game.paused;
    scene.speech_at+=duration;scene.start+=duration;scene.phase_at+=duration;scene.spin_at+=duration;
    scene.host_at+=duration;scene.host_phase_at+=duration;scene.chest_until+=duration;
    if(game.return_mode==CASH)cash.next_at+=duration;
   }
   set_mode(game.return_mode);return;
  }
  if(pressed&SELECT){set_mode(TITLE);return;}return;
 }
 if(game.mode==TITLE){if(pressed&(A|START))new_game();else if(pressed&SELECT){game.return_mode=TITLE;set_mode(HELP);}else if(pressed&R){game.album=0;set_mode(GALLERY);}else if(pressed&L)set_mode(RECORDS);return;}
 if(game.mode==RECORDS){if(pressed&(A|B|START))set_mode(TITLE);return;}
 if(game.mode==GALLERY){if(repeat&RIGHT)game.album=(game.album+1)%57;if(repeat&LEFT)game.album=(game.album+56)%57;if(pressed&B)set_mode(TITLE);if(repeat&(LEFT|RIGHT))dirty=1;return;}
 if(pressed&L){sound_on=!sound_on;speaker_enable(sound_on);}
 if(pressed&((game.mode==SOLVE||game.mode==NAME)?SELECT:START)){
  game.return_mode=game.mode;game.paused=video_ticks;
  if(game.mode==CASH){cash.pause_at=video_ticks;speaker_tone(0,1);}
  set_mode(HELP);return;
 }
 if(scene_tick(pressed))return;
 if(game.mode==GIFT_PAGES){
  if((pressed&B)&&scene.gift_page>0){scene.gift_page--;dirty=1;}
  else if(pressed&A){if(scene.gift_page<2){scene.gift_page++;dirty=1;}else if(scene.gift_final)final_records();else farewell();}
  return;
 }
 if(game.mode==TURN){if(game.player!=2){if(scene.now-scene.speech_at>=40)start_spin();}else{if(repeat&(LEFT|RIGHT)){int choice=(repeat&RIGHT)?1:0;if(choice!=game.choice){game.choice=choice;dirty=1;}}if(pressed&A){if(game.choice)start_spin();else solve_word();}}return;}
 if(game.mode==SPIN){
  if(pressed&A){game.sector=scene.spin_target;game.spin_steps=0;scene.spin_half=0;stop_spin();return;}
  /* The original renderer spent five VBlank per wheel phase. Preserve
   * its speed explicitly without changing spin_wait or the tone pitch. */
  unsigned spin_delay=game.spin_wait<5?5:(unsigned)game.spin_wait;
  if(scene.now-scene.spin_at>=spin_delay){game.wait=0;scene.spin_half^=1;scene.spin_at=scene.now;dirty=1;
   if(!scene.spin_half){game.spin_ticks++;game.sector=(game.sector+15)&15;game.spin_steps--;if(game.spin_steps<8)game.spin_wait=2+(8-game.spin_steps)*2;speaker_tone(55+(game.spin_steps%10)*10+game.spin_wait*100,1);if(game.spin_steps<=0){game.sector=scene.spin_target;stop_spin();}}
  }return;
 }
 if(game.mode==AI_ANSWER){if(scene.now-scene.speech_at>=120||((pressed&A)&&scene.now-scene.speech_at>=24))choose_letter(scene.ai_letter);return;}
 if(game.mode==RESULT){if(pressed&A || (game.player!=2&&scene.now-scene.speech_at>=80))end_result();return;}
 if(game.mode==LETTER||game.mode==SOLVE){if(game.player!=2){if(scene.now-scene.speech_at>=40)ai_letter();return;}if(repeat&LEFT)game.cursor=(game.cursor+31)%32;if(repeat&RIGHT)game.cursor=(game.cursor+1)%32;if(repeat&UP)game.cursor=(game.cursor+24)%32;if(repeat&DOWN)game.cursor=(game.cursor+8)%32;if(repeat&(UP|DOWN|LEFT|RIGHT))dirty=1;if(game.mode==SOLVE){
  if(pressed&B){int p=game.solve_pos;do{p--;}while(p>=0&&game.revealed[p]);if(p>=0){game.solve_pos=p;game.answer[p]=0;dirty=1;}}
  if(pressed&A){if(fixed_letter(game.cursor))beep(110,10);else if(game.solve_pos<len(word())){game.answer[game.solve_pos++]=128+game.cursor;solve_advance();dirty=1;}}
  if((pressed&START)&&game.solve_pos==len(word()))confirm_word();
 }else if(pressed&A){if(!game.used[game.cursor])choose_letter(game.cursor);else beep(110,10);}return;}
 if(game.mode==PLUS){
  int n=len(word());
  /* DOS 1000:1fd6/226d: only the human enters the position selector.
   * AI chooses one hidden position independently of keypad input. */
  if(game.player!=2){
   if(scene.now-scene.speech_at>=40){do{game.cursor=random_n(n);}while(game.revealed[game.cursor]);ai_announce((u8)word()[game.cursor]-128,game.cursor+1);}
   return;
  }
  if(repeat&(LEFT|RIGHT)){int delta=repeat&RIGHT?1:n-1;do{game.cursor=(game.cursor+delta)%n;}while(game.revealed[game.cursor]);dirty=1;}
  if(pressed&A)choose_letter((u8)word()[game.cursor]-128);return;
 }
 if(game.mode==CHEST){if(repeat&(LEFT|RIGHT)){game.choice=1-game.choice;dirty=1;}if(pressed&A||(game.player!=2&&scene.now-scene.speech_at>=328)){int reward=random_n(2)==(unsigned)game.choice?100:0;game.score[game.player]+=reward;scene.chest_until=scene.now+120;scene.chest_money=reward!=0;result(reward?msg_ef1:msg_f07,reward?msg_efa:msg_f10,TURN,game.player);}return;}
 if(game.mode==PRIZE){
  if(repeat&(LEFT|RIGHT)){int choice=(repeat&RIGHT)?1:0;if(choice!=game.choice){game.choice=choice;dirty=1;}}
  if(pressed&A){
   if(!game.deal){if(game.choice==1){open_letter();say(msg_fba,msg_fc7);}else{game.deal=1;game.prize=100;game.choice=1;prize_offer();}}
   else if(!game.choice){cash_begin();}
   else if(game.deal<4){game.deal++;game.prize=game.deal==2?1000:game.deal==3?100000:1000000;prize_offer();}
   else{game.deal=6;game.prize=random_n(10);set_mode(GAME_OVER);say(msg_ffa,msg_1029);}
  }return;
 }
 if(game.mode==ROUND_END&&(pressed&A)&&game.player==2&&game.round<2){credits_begin();return;}
 if(game.mode==ROUND_END){if(pressed&A){if(game.player!=2)farewell();else gift_begin(1);}return;}
 if(game.mode==NAME){
  int old_cursor=game.cursor,old_pos=game.solve_pos;
  if(repeat&LEFT)game.cursor=(game.cursor+31)%32;if(repeat&RIGHT)game.cursor=(game.cursor+1)%32;if(repeat&UP)game.cursor=(game.cursor+24)%32;if(repeat&DOWN)game.cursor=(game.cursor+8)%32;
  if((pressed&A)&&game.solve_pos<10)game.answer[game.solve_pos++]=128+game.cursor;
  if((pressed&R)&&game.solve_pos<10)game.answer[game.solve_pos++]=' ';
  if((pressed&B)&&game.solve_pos>0)game.answer[--game.solve_pos]=0;
  if(pressed&START){const char*n=game.solve_pos?(const char*)game.answer:"ИГРОК";for(int i=0;i<11;i++)record_names[record_entry][i]=i<len(n)?n[i]:0;game.best=record_scores[0];save();set_mode(RECORDS);}
  if(game.cursor!=old_cursor||game.solve_pos!=old_pos)dirty=1;return;
 }
 if(game.mode==GAME_OVER){if(pressed&A){if(game.deal==6)gift_begin(0);else if(game.deal==5)farewell();else set_mode(TITLE);}return;}
}
void gba_main(void){
 extern void gba_irq(void);REG32(0x03007ffc)=(u32)gba_irq;game.magic=0x504f4c45;game.rng=1;game.word_id=-1;game.best=load();REG16(0x04000204)=0x4317;REG16(0x04000000)=0x0404;for(int i=0;i<16;i++)((volatile u16*)0x05000000)[i]=palette[i];speaker_init();REG16(0x04000200)|=1;REG16(0x04000004)|=8;set_mode(TITLE);
 for(;;){
  /* VBlank queues taps even while a bitmap is being drawn. Drain in order. */
  u16 ime=REG16(0x04000208);REG16(0x04000208)=0;capture_keys();
  u16 keys=input_keys,pressed=0;
  if(input_read!=input_write){pressed=input_events[input_read];input_read=(input_read+1)&31;}
  REG16(0x04000208)=ime;
  u16 repeat=pressed;
  u32 now=video_ticks;
  if(keys!=oldkeys||(pressed&(UP|DOWN|LEFT|RIGHT)))repeat_at=now+18;
  else if((keys&(UP|DOWN|LEFT|RIGHT))&&(int)(now-repeat_at)>=0){repeat|=keys&(UP|DOWN|LEFT|RIGHT);repeat_at=now+5;}
  oldkeys=keys;game.frame++;if(game.mode==TITLE)game.rng+=game.frame;update(pressed,repeat);
  scene.now=video_ticks;visual_tick();u32 key=visual_key();if(key!=rendered_key)dirty=1;
  if(dirty){scene.last_redraw=scene.now;render();present();rendered_key=key;rendered_frames++;dirty=0;}else vblank();
 }
}
