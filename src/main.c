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
#define A_RELEASE 0x8000
enum {TITLE,TURN,SPIN,LETTER,PLUS,SOLVE,RESULT,PRIZE,CHEST,ROUND_END,GAME_OVER,HELP,RECORDS,NAME=14,INTRO,REVEAL,CREDITS,AI_ANSWER,GIFT_PAGES,CASH=21,AI_CHEST,MENU,AUTHORS,RESTART_CONFIRM,MP_SETUP,MP_NAME,MP_PASS,MP_LOBBY=30,MP_ERROR,MP_OPTIONS,MP_AVATAR,MP_COUNT,MP_DEPART,MP_SUMMARY,MP_OPTION_HELP,LINK_TEST,MP_CONNECT};
enum {REACTION,MISS,ZERO,BANKRUPT,BONUS,CHEST_RESULT,WRONG_WORD};
enum {MESSAGE_TICKS=180,LONG_MESSAGE_TICKS=240};
enum {TITLE_GRID_HALF=12,TITLE_LOGO_AT=24,TITLE_READY_AT=36};
/* Read-only diagnostic state is also used by the emulator integration checks. */
typedef struct {
 u32 magic,frame,rng; int mode,round,player,word_id,sector,sector_value;
 int score[3],opponent[6],revealed[20],used[32],cursor,keyboard;
 int streak,spin_ticks,spin_steps,spin_wait,wait,next_mode,next_player;
 int solved,solve_pos,choice,deal,prize,reserved,best,paused,return_mode;
 char answer[21];
} Game;
volatile Game game;
typedef struct {u32 sequence,seed;int type,a,b;} SoundCommand;
static SoundCommand sound_command;
static void game_effect(unsigned id,u32 seed){sound_command.sequence++;sound_command.type=1;sound_command.a=id;sound_command.seed=seed;speaker_effect(id,seed);}
static void game_tone(int hz,int duration){sound_command.sequence++;sound_command.type=2;sound_command.a=hz;sound_command.b=duration;speaker_tone(hz,duration);}
static u8 framebuffer[240*160] __attribute__((aligned(4)));
static u8 cash_canvas[240*160] __attribute__((aligned(4)));
typedef struct {u32 drawn,total,rng,next_at,pause_at;int ready;u32 credit;} Cash;
static volatile Cash cash;
static u32 cash_initial_seed;
static void cash_remote_sync(const Cash*target,u32 seed);
static const char *message1,*message2;
static char sector_message[32],turn_line[32];
volatile u32 video_ticks;
typedef struct {
 u32 now,speech_at,last_redraw,start,phase_at,spin_at,title_at,chest_until;
 int phase,pending_mode,pending_wait,actor_x,actor_stop,old_score,reward_chest,chest_money;
 int reveal_target[20];
 int ai_letter,pending_score,spin_half,spin_target;
 u32 host_at,host_seed;int host_active;
 int host_phase;u32 host_phase_at;
 int gift_final,gift_page;
} Scene;
static Scene scene;
/* Stable player ids: 2 is player one, 0 player two, 1 player three/AI. */
static struct {int humans,link,viewer,local,edit,choice,eliminated;char names[3][11];} mp={1,0,2,2,0,0,0,{{0}}};
static struct {int dictionary,plus,characters,choice,rule,rounds;} prefs;
enum {MP_POINTS,MP_RISK,MP_WINS};
typedef struct {
 int bank[3],start[3],wins[3];
 int shootout,participants,settled,round_winner,winner,next;
 int previous_word;
} Match;
static Match match;
static int option_help_value;
static int option_value(void){return prefs.choice==0?prefs.dictionary:prefs.choice==1?prefs.plus:prefs.choice==2?prefs.characters:prefs.choice==3?prefs.rule:prefs.rounds;}
static int opponent_pool[8],mp_ai_index;
static int avatars[3];
static int mp_name_error;
static int human(int p){return p==2||mp.humans==3||(mp.humans==2&&p==0);}
static int player_number(int p){return (p+1)%3+1;}
static const char*player_intro(int p){return p==2?msg_5384:p==0?msg_5391:msg_539e;}
static int perspective(int slot){return (mp.viewer+slot+1)%3;}
static const char* character_name(int id){return id<6?opponent_names[id]:id==6?"ФРЕКЕН БОК":"БАГИРА";}
static const char* player_name(int p){return !human(p)?character_name(opponent_pool[mp_ai_index]):mp.names[p];}
static const char*round_number(void){
 static char digits[11];unsigned n=(unsigned)game.round+1;int i=10;digits[i]=0;
 do{digits[--i]='0'+n%10;n/=10;}while(n);
 return digits+i;
}
static const char*mp_stage(void){
 static char title[32];
 if(match.shootout)return "ПЕРЕСТРЕЛКА";
 if(prefs.rule!=MP_WINS&&game.round+1==prefs.rounds)return "ПОСЛЕДНИЙ РАУНД";
 const char*prefix="РАУНД ",*n=round_number();int i=0;
 while(*prefix)title[i++]=*prefix++;
 while(*n)title[i++]=*n++;
 if(prefs.rule!=MP_WINS){const char*suffix=" ИЗ ";while(*suffix)title[i++]=*suffix++;title[i++]='0'+prefs.rounds;}
 title[i]=0;return title;
}
static void link_irq(void);
static void link_test_irq(void);
static void link_close(void);
static int link_frame(void);
static void mp_setup(void);
static void mp_depart(int wrong);
static void intro_begin(void);
static void reveal_begin(void);
static int scene_tick(u16 pressed);
static volatile u16 input_events[32],input_keys;
static volatile u8 input_read,input_write;
static volatile u32 input_entropy;
static volatile u32 input_seed_salt;
static u32 input_seed_counter;
static int fast_input=1;
static volatile u32 startup_input_polls;
static int start_pending,title_seen;
static volatile struct {int value,count;u32 rerolls;} spin_history;
static u32 mix_input(u32 value){
 value^=value>>16;value*=0x7feb352du;value^=value>>15;value*=0x846ca68bu;return value^(value>>16);
}
static u32 boot_seed(void){
 /* Records own bytes 0..127. A separate versioned counter survives resets,
  * even when the player repeats exactly the same input timing. Byte accesses
  * are required for SRAM; an invalid/incomplete record starts a new sequence. */
 volatile u8*s=(volatile u8*)0x0e000080;u32 count=0,inverse=0;
 for(int i=0;i<4;i++){count|=(u32)s[4+i]<<(i*8);inverse|=(u32)s[8+i]<<(i*8);}
 if(s[0]!='R'||s[1]!='N'||s[2]!='G'||s[3]!=1||inverse!=~count)count=0;
 count++;s[0]=0;
 for(int i=0;i<4;i++){s[4+i]=count>>(i*8);s[8+i]=(~count)>>(i*8);}
 s[1]='N';s[2]='G';s[3]=1;s[0]='R';
 return mix_input(count);
}
static u32 input_clock(void){
 /* Timers 0/1 belong to audio. Timer 2 counts CPU clocks, 3 its overflows. */
 u16 high,low;do{high=REG16(0x0400010c);low=REG16(0x04000108);}while(high!=REG16(0x0400010c));
 return ((u32)high<<16)|low;
}
static void seed_from_input(void){
 /* Mix at the draw boundary, even when no new key edge arrived since the
  * previous draw. The timer/counter diversify samples; the final avalanche
  * spreads timing differences through all RNG bits rather than only XORing
  * the same input snapshot into successive LCG states. No SRAM is required. */
 input_seed_counter++;
 input_seed_salt=input_entropy^mix_input(input_clock()^input_seed_counter*0x9e3779b9u);
 game.rng=mix_input(game.rng^input_seed_salt);
}
static void capture_keys(void){
 u16 keys=(~REG16(0x04000130))&1023,changed=keys^input_keys,pressed=keys&changed;input_keys=keys;
 if(changed){
  /* Capture both edges, including hold duration and releases during rendering.
   * Keep timing separate until a new draw: pause/skip cannot reroll a spin. */
  input_entropy=mix_input(input_entropy^input_clock()^((u32)changed<<16)^keys^video_ticks);
 }
 /* Queue startup A releases in order, even if a whole tap arrived while
  * rendering. The start draw must include the release's timing entropy. */
 u16 event=pressed;if(fast_input&&(changed&A)&&!(keys&A))event|=A_RELEASE;
 if(event){
  u8 next=(input_write+1)&31;if(next!=input_read){input_events[input_write]=event;input_write=next;}
 }
}
void game_irq(unsigned flags){if(flags&1){video_ticks++;capture_keys();}if(flags&128)link_irq();speaker_irq(flags);}

static u16 oldkeys;
static u32 repeat_at,rendered_key=~0u,solve_fixed;
static u8 host_durations[10];
volatile u32 rendered_frames;
static volatile int dirty=1;
static int sound_on=1;
static char record_names[8][11];
static int record_scores[8],record_entry=-1,selected_words[WORD_COUNT];
/* Keep UI state separate: diagnostic Game and scene offsets stay compatible. */
static volatile struct {int active,origin,choice,viewer;u32 since;int wait,author_page,confirm;} ui;
static int result_reason;
static char pending_last_name[11];
static int pending_last_score,record_pending;
static const char save_id[] __attribute__((used,section(".rodata.save_id")))="SRAM_V113";
static unsigned divide(unsigned a,unsigned b){unsigned q=0,r=0;for(int i=31;i>=0;i--){r=(r<<1)|((a>>i)&1);if(r>=b){r-=b;q|=1u<<i;}}return q;}
static int len(const char *s){int n=0;while(s[n])n++;return n;}
static unsigned random_n(unsigned n){game.rng=game.rng*134775813u+1;return (game.rng>>16)%n;}
static void effect(unsigned id){u32 seed=game.rng;if(!id)for(int i=0;i<6;i++)random_n(100);game_effect(id,seed);}
static void pixel(int x,int y,u8 c){if((unsigned)x<240 && (unsigned)y<160)framebuffer[y*240+x]=c;}
static void rect(int x,int y,int w,int h,u8 c){
 if(x<0){w+=x;x=0;}if(y<0){h+=y;y=0;}
 if(x>=240||y>=160||w<=0||h<=0)return;
 if(w>240-x)w=240-x;if(h>160-y)h=160-y;
 for(int j=0;j<h;j++){u8*row=framebuffer+(y+j)*240+x;for(int i=0;i<w;i++)row[i]=c;}
}
static void line(int x,int y,int w,u8 c){rect(x,y,w,1,c);}
static void glyph(int x,int y,unsigned c,int small,u8 color){int h=small?8:14;const u8 *f=small?font8:font14;for(int j=0;j<h;j++)for(int i=0;i<8;i++)if(f[c*h+j]&(128>>i))pixel(x+i,y+j,color);}
static void text(int x,int y,const char *s,int small,u8 c){int advance=8;for(int i=0;s[i];i++)glyph(x+i*advance,y,(u8)s[i],small,c);}
static void centered(int y,const char*s,int small,u8 c){text((240-len(s)*8)/2,y,s,small,c);}
static void number(int x,int y,int value,int small,u8 c){char b[12];int n=0;unsigned v=value<0?-value:value;do{b[n++]='0'+v%10;v/=10;}while(v);if(value<0)b[n++]='-';for(int i=n-1;i>=0;i--)glyph(x+(n-1-i)*8,y,b[i],small,c);}
static void beep(int hz,int duration){game_tone(hz,duration*4);}
static void poll_startup_keys(void){
 /* capture_keys also runs in VBlank: serialize its edge/queue updates. */
 u16 ime=REG16(0x04000208);REG16(0x04000208)=0;capture_keys();startup_input_polls++;REG16(0x04000208)=ime;
}
static void vblank(void){
 if(fast_input){
  while(REG16(0x04000006)>=160)poll_startup_keys();
  while(REG16(0x04000006)<160)poll_startup_keys();
 }else{while(REG16(0x04000006)>=160){}while(REG16(0x04000006)<160){}}
}
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
static void set_mode(int mode){if(mode==TITLE){scene.title_at=video_ticks-(title_seen?TITLE_READY_AT:0);title_seen=1;fast_input=1;start_pending=0;}game.mode=mode;game.wait=0;dirty=1;}
static int message_done(u16 pressed,unsigned duration){return (pressed&A)||scene.now-scene.speech_at>=duration;}
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
static void result(const char*a,const char*b,int next,int player){say(a,b);set_mode(RESULT);game.next_mode=next;game.next_player=player;game.wait=human(game.player)?0:65;}
static int nextplayer(void){int p=game.player;for(int i=0;i<3;i++){p=(p+1)%3;if(!(mp.eliminated&(1<<p)))return p;}return game.player;}
static void begin_turn(void){int pass=mp.humans>1&&!mp.link&&human(game.player)&&mp.viewer!=game.player;if(mp.humans>1&&!mp.link&&human(game.player))mp.viewer=game.player;set_mode(TURN);game.choice=1;const char*a=mp.humans>1?(game.player==2?"Первый":game.player==0?"Второй":"Третий"):human(game.player)?msg_d9a:game.player==0?msg_d8c:msg_d93;int p=0;while(a[p]){turn_line[p]=a[p];p++;}for(int i=0;msg_da1[i];i++)turn_line[p++]=msg_da1[i];turn_line[p]=0;say(turn_line,msg_da9);if(!human(game.player))game.wait=65;if((mp.humans>1||prefs.plus)&&game.streak==3&&(mp.humans>1||human(game.player))){game.streak=0;result_reason=BONUS;result(msg_eb5,msg_ec8,CHEST,game.player);}else if(pass)set_mode(MP_PASS);}
static void new_round(void){
 spin_history.count=0;if(game.round||match.shootout)seed_from_input();
 int duplicate,previous=match.previous_word;
 int word_count=prefs.dictionary?WORD_COUNT:BASE_WORD_COUNT,history=game.round%word_count;
 do{game.word_id=random_n(prefs.dictionary?WORD_COUNT:BASE_WORD_COUNT);duplicate=0;
  for(int i=0;i<history+match.shootout&&i<word_count;i++)if(selected_words[i]==game.word_id)duplicate=1;
  if(previous==game.word_id)duplicate=1;
 }while(duplicate);
 if(!match.shootout)selected_words[history]=game.word_id;
 match.previous_word=game.word_id;
 for(int i=0;i<20;i++)game.revealed[i]=0;for(int i=0;i<32;i++)game.used[i]=0;
 mp.eliminated=mp.humans>1?(7^match.participants):0;
 if(mp.humans==1)for(int i=0;i<2;i++)game.score[i]=game.round*(random_n(4)*15+5);
 for(int i=0;i<3;i++){match.start[i]=game.score[i];match.bank[i]=game.score[i];}
 match.settled=0;match.round_winner=-1;
 game.player=2;while(mp.eliminated&(1<<game.player))game.player=(game.player+1)%3;
 game.streak=0;game.solved=0;game.deal=game.prize=game.keyboard=0;begin_turn();intro_begin();
}
/* Total is authoritative; bank protects only completed rounds in points mode.
 * Saturate at the representable integer boundary, never wrap into a loss. */
static void score_add(int p,int amount){game.score[p]=game.score[p]>2147483647-amount?2147483647:game.score[p]+amount;}
static void score_multiply(int p,int factor){
 int base=mp.humans>1&&prefs.rule==MP_POINTS?match.bank[p]:0;
 int value=game.score[p]-base,room=2147483647-base;
 game.score[p]=base+(value>room/factor?room:value*factor);
}
static void mp_settle(void){
 if(match.settled)return;
 match.settled=1;match.round_winner=game.solved?game.player:-1;match.winner=-1;
 if(match.shootout){
  if(game.solved){match.winner=game.player;match.next=2;}else match.next=1;
 }else{
  if(game.solved)match.wins[game.player]++;
  match.next=0;
  if(prefs.rule==MP_WINS){
   if(game.solved&&match.wins[game.player]>=prefs.rounds){match.winner=game.player;match.next=2;}
  }else if(game.round+1>=prefs.rounds){
   int leaders=0,best=-1;
   for(int p=0;p<3;p++){
    if(best<0||game.score[p]>game.score[best]){best=p;leaders=1<<p;}
    else if(game.score[p]==game.score[best])leaders|=1<<p;
   }
   if(leaders==(1<<best)){match.winner=best;match.next=2;}
   else{match.participants=leaders;match.next=1;}
  }
 }
 for(int p=0;p<3;p++)match.bank[p]=game.score[p];
}
static void new_game(void){
 fast_input=0;seed_from_input();match=(Match){0};match.participants=7;match.winner=match.round_winner=match.previous_word=-1;game.round=0;for(int i=0;i<3;i++)game.score[i]=0;game.sector=12;
 int count=prefs.characters?8:6;mp_ai_index=0;
 for(int i=0;i<count;i++)opponent_pool[i]=i;
 for(int i=0;i<20;i++){int a=random_n(count),b=random_n(count),t=opponent_pool[a];opponent_pool[a]=opponent_pool[b];opponent_pool[b]=t;}
 for(int i=0;i<6;i++)game.opponent[i]=opponent_pool[i];
 new_round();
}
static int hidden(void){int n=0;for(int i=0;word()[i];i++)if(!game.revealed[i])n++;return n;}
static void finish_round(void){
 for(int i=0;word()[i];i++)game.revealed[i]=1;
 game.solved=1;set_mode(ROUND_END);
 if(mp.humans>1)say(player_name(game.player),"выиграл раунд!");
 else if(human(game.player)&&game.round==2)say(msg_f7b,msg_f8a);
 else{
  const char*a=mp.humans>1?(game.player==2?"Первый":game.player==0?"Второй":"Третий"):human(game.player)?msg_d9a:game.player==0?msg_d8c:msg_d93;
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
 if(mp.humans>1){set_mode(TITLE);return;}
 int winner=2;
 ui.viewer=0;
 record_entry=-1;for(int i=7;i>=0;i--)if(game.score[winner]>record_scores[i])record_entry=i;
 if(record_entry<0){set_mode(RECORDS);return;}
 for(int j=0;j<11;j++)pending_last_name[j]=record_names[7][j];
 pending_last_score=record_scores[7];record_pending=1;
 for(int i=7;i>record_entry;i--){record_scores[i]=record_scores[i-1];for(int j=0;j<11;j++)record_names[i][j]=record_names[i-1][j];}
 record_scores[record_entry]=game.score[winner];for(int j=0;j<11;j++)record_names[record_entry][j]=0;

 for(int j=0;j<21;j++)game.answer[j]=0;game.cursor=game.solve_pos=0;set_mode(NAME);
}
static void award_letter(int letter){
 int count=0;
 for(int i=0;word()[i];i++)if((u8)word()[i]==128+letter&&!game.revealed[i]){game.revealed[i]=1;count++;}
 game.used[letter]=1;game.keyboard=0;
 if(count){
  if(game.sector_value<100)score_add(game.player,game.sector_value*count);
  else if(game.sector_value/100==2)score_multiply(game.player,game.sector_value%100);
  effect(1);
  if(game.sector_value==100){
   /* DOS 1fcf returns straight to 1698. Only ordinary letter selection
    * (1a3a) calls host dialogue 3: Plus has no "there is that letter". */
   message1=message2="";scene.host_active=0;
   game.next_mode=TURN;game.next_player=game.player;
   set_mode(hidden()?TURN:ROUND_END);return;
  }
  if(!hidden()){set_mode(ROUND_END);say(msg_e77,msg_e65);return;}
  if(mp.humans==1&&!prefs.plus&&game.streak==3){game.streak=0;result_reason=REACTION;result(msg_e77,msg_e65,CHEST,game.player);return;}
  result_reason=REACTION;result(msg_e77,msg_e65,TURN,game.player);
 }else{effect(0);game.streak=0;result_reason=MISS;result(msg_e7f,msg_e90,TURN,nextplayer());}
}

static void choose_letter(int letter){
 int before[20],count=0,n=len(word());
 for(int i=0;i<20;i++){before[i]=game.revealed[i];if(i<n&&(u8)word()[i]==128+letter&&!before[i])count++;}
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
static void open_letter(void){set_mode(LETTER);game.cursor=0;game.keyboard=human(game.player);if(game.sector_value<100){int p=0;while(msg_dbb[p]){sector_message[p]=msg_dbb[p];p++;}int v=game.sector_value;if(v>=10)sector_message[p++]='0'+v/10;sector_message[p++]='0'+v%10;for(int i=0;msg_dc2[i];i++)sector_message[p++]=msg_dc2[i];sector_message[p]=0;say(sector_message,msg_dca);}else say(game.sector_value==300?msg_e47:msg_e12,msg_dca);if(!human(game.player))game.wait=55;}
static void stop_spin(void){int sector=game.sector;game.sector_value=sector_values[wheel_sectors[sector]-4];if(prefs.plus||game.sector_value!=100)game.streak++;if(game.sector_value<0){game.streak=0;game.score[game.player]=mp.humans>1&&prefs.rule==MP_POINTS?match.bank[game.player]:0;result_reason=BANKRUPT;result(msg_dfe,msg_dea,TURN,nextplayer());}else if(!game.sector_value){game.streak=0;result_reason=ZERO;result(msg_dda,msg_dea,TURN,nextplayer());}else if(game.sector_value==100){set_mode(PLUS);game.cursor=0;while(game.revealed[game.cursor])game.cursor++;say(msg_e26,msg_e33);if(!human(game.player))game.wait=60;}else if(game.sector_value==300&&human(game.player)){set_mode(PRIZE);game.choice=1;game.deal=0;game.prize=10;say(msg_e47,msg_e54);}else{open_letter();}}
static int spin_draw(void){
 /* DOS four speed stages; the fifth duration is drawn although unused. */
 unsigned limit=10+random_n(20),half_steps=0;
 for(unsigned divisor=1;divisor<=4;divisor++){
  half_steps+=limit/divisor+1;
  limit=5+random_n(10);
 }
 return (half_steps+1)/2;
}
static void start_spin(void){
 seed_from_input();
 set_mode(SPIN);say(msg_da9,"");scene.host_active=0;
 /* Speech consumes the original six noise draws once. A third equal award
  * gets one further four-stage draw, shared across contestants in this round.
  * The second candidate is always accepted, so repeats remain possible. */
 int draw=spin_draw(),target=(game.sector-draw)&15;
 int value=sector_values[wheel_sectors[target]-4];
 if(spin_history.count>=2&&value==spin_history.value){
  spin_history.rerolls++;draw=spin_draw();target=(game.sector-draw)&15;
  value=sector_values[wheel_sectors[target]-4];
 }
 spin_history.count=value==spin_history.value?spin_history.count+1:1;
 spin_history.value=value;
 scene.spin_target=target;
 /* Resolve all draws before animation so skipping preserves the result. */
 game.spin_steps=16+(draw&15);game.spin_ticks=0;game.spin_wait=1;scene.spin_half=0;scene.spin_at=video_ticks;
}
static void mp_depart_message(void){set_mode(MP_DEPART);say(player_name(game.player),"покидает раунд");}
static void end_result(void){
 /* Dismissing the bonus also ends its overlay, even before its timeout.
  * The expired deadline is part of Scene and travels to cable clients. */
 scene.chest_until=scene.now;
 int next=game.next_mode;game.player=game.next_player;if(next==TURN)begin_turn();else if(next==CHEST){set_mode(CHEST);game.choice=0;say(msg_eda,msg_ee6);if(!human(game.player))game.wait=60;}else if(next==GAME_OVER)farewell();else if(next==MP_DEPART)mp_depart_message();else set_mode(next);}
static void open_chest(void){
 int reward=random_n(2)==(unsigned)game.choice?100:0;
 score_add(game.player,reward);scene.chest_until=scene.now+180;scene.chest_money=reward!=0;
 result_reason=CHEST_RESULT;
 result(reward?msg_ef1:msg_f07,reward?msg_efa:msg_f10,TURN,game.player);
}
static int fixed_letter(int letter){return (solve_fixed>>letter)&1;}
static void solve_advance(void){while(game.solve_pos<len(word())&&game.revealed[game.solve_pos])game.solve_pos++;}
static void solve_word(void){set_mode(SOLVE);game.solve_pos=0;solve_fixed=0;int n=len(word());for(int i=0;i<21;i++){game.answer[i]=i<n&&game.revealed[i]?word()[i]:0;if(i<n&&game.revealed[i])solve_fixed|=1u<<((u8)word()[i]-128);}solve_advance();game.cursor=0;while(game.cursor<31&&fixed_letter(game.cursor))game.cursor++;game.keyboard=1;say(msg_f20,"");}
static void mp_depart(int wrong){
 mp.eliminated|=1<<game.player;game.keyboard=0;game.streak=0;
 if(wrong){result_reason=WRONG_WORD;result(msg_f5b,msg_f6b,MP_DEPART,game.player);}
 else mp_depart_message();
}
static void mp_depart_finish(void){
 int p=nextplayer();
 if(p==game.player){
  game.solved=0;set_mode(ROUND_END);say("Все игроки","покинули раунд!");
 }else{game.player=p;begin_turn();}
}
static void confirm_word(void){int good=1;for(int i=0;word()[i];i++)if(game.answer[i]!=word()[i])good=0;if(good)finish_round();else{game.keyboard=0;game.streak=0;result_reason=WRONG_WORD;if(mp.humans>1)mp_depart(1);else result(msg_f5b,msg_f6b,GAME_OVER,game.player);}}
static void cancel_record(void){
 if(!record_pending)return;
 for(int i=record_entry;i<7;i++){record_scores[i]=record_scores[i+1];for(int j=0;j<11;j++)record_names[i][j]=record_names[i+1][j];}
 record_scores[7]=pending_last_score;for(int j=0;j<11;j++)record_names[7][j]=pending_last_name[j];
 record_pending=0;record_entry=-1;
}
static void menu_open(void){
 ui.active=1;ui.origin=game.mode;ui.choice=0;ui.since=video_ticks;ui.wait=game.wait;
 game.return_mode=game.mode;game.paused=video_ticks;
 if(game.mode==CASH){cash.pause_at=video_ticks;game_tone(0,1);}
 set_mode(MENU);
}
static void menu_close(void){
 u32 duration=video_ticks-ui.since;
 scene.speech_at+=duration;scene.start+=duration;scene.phase_at+=duration;scene.spin_at+=duration;
 scene.title_at+=duration;scene.host_at+=duration;scene.host_phase_at+=duration;scene.chest_until+=duration;
 if(ui.origin==CASH)cash.next_at+=duration;
 /* Restoring the mode must not reset its clocks, wait, or input. */
 game.mode=ui.origin;game.wait=ui.wait;ui.active=0;dirty=1;
}
/* Keep START available for saving a name, including while its menu is open. */
static u16 menu_button(void){return (ui.active?ui.origin:game.mode)==NAME?SELECT:START;}
static void mp_setup(void){mp.choice=0;mp.link=0;mp.humans=1;mp.viewer=mp.local=2;ui.active=0;set_mode(MP_SETUP);}
static void options_begin(void){prefs.dictionary=prefs.plus=prefs.characters=mp.humans>1;prefs.rule=MP_POINTS;prefs.rounds=3;prefs.choice=mp.humans>1?5:3;set_mode(MP_OPTIONS);}
/* Names use the game's single-byte CP866 alphabet, not UTF-8. */
static void name_clean(char out[11],const char*in){
 int n=0,space=0;
 for(int i=0;i<10&&in[i];i++){
  if(in[i]==' '){space=n>0;continue;}
  if(space&&n<10)out[n++]=' ';
  if(n<10)out[n++]=in[i];space=0;
 }
 for(;n<11;n++)out[n]=0;
}
static int name_equal(const char*a,const char*b){
 char x[11],y[11];name_clean(x,a);name_clean(y,b);
 for(int i=0;i<11;i++){if(x[i]!=y[i])return 0;if(!x[i])return 1;}
 return 1;
}
/* Reserve the roster before the fixed AI is drawn. Three humans have no AI. */
static int name_reserved(const char*n){
 if(mp.humans==3)return 0;
 for(int i=0;i<(prefs.characters?8:6);i++)if(name_equal(n,character_name(i)))return 1;
 return 0;
}
static int name_taken(const char*n,int self){
 if(name_reserved(n))return 1;
 for(int p=0;p<3;p++)if(p!=self&&human(p)&&name_equal(n,mp.names[p]))return 1;
 return 0;
}
static const char*default_name(int p){return p==2?"1-ый ИГРОК":p==0?"2-ой ИГРОК":"3-ий ИГРОК";}
/* Validate a complete cable roster in device order. The earlier device
 * keeps a duplicate name; later devices edit it without leaving the lobby. */
static int link_name_conflicts(char incoming[3][11]){
 int conflicts=0;
 for(int i=0;i<mp.humans;i++){
  int p=(i+2)%3;char clean[11];name_clean(clean,incoming[p]);
  if(name_equal(clean,default_name(2)))name_clean(clean,default_name(p));
  for(int j=0;j<11;j++)mp.names[p][j]=clean[j];
  int clash=!clean[0]||name_reserved(clean);
  for(int j=0;j<i;j++)if(name_equal(clean,mp.names[(j+2)%3]))clash=1;
  if(clash)conflicts|=1<<p;
 }
 return conflicts;
}
static void mp_name_begin(void){mp_name_error=0;for(int i=0;i<21;i++)game.answer[i]=0;game.cursor=game.solve_pos=0;set_mode(MP_NAME);}
static void mp_defaults(void){
 for(int p=0;p<3;p++)avatars[p]=0;
 const char*n[3]={"2-ой ИГРОК","КОМПЬЮТЕР","1-ый ИГРОК"};
 if(mp.humans==3)n[1]="3-ий ИГРОК";
 for(int p=0;p<3;p++)for(int i=0;i<11;i++)mp.names[p][i]=i<len(n[p])?n[p][i]:0;
}
#include "link.inc"
#include "link-test.inc"
#include "presentation.inc"
#include "scene.inc"
static void update(u16 pressed,u16 repeat){
 scene.now=video_ticks;
 if(game.mode==MP_SETUP){
  if(pressed&B){set_mode(TITLE);return;}
  if(repeat&UP){mp.choice=(mp.choice+3)%4;dirty=1;}
  if(repeat&DOWN){mp.choice=(mp.choice+1)%4;dirty=1;}
  if(pressed&A){
   if(mp.choice==3){link_test_enter();return;}
   mp.link=mp.choice==2;mp.humans=mp.choice?2:1;
   if(mp.choice==2){game.choice=0;set_mode(MP_CONNECT);}
   else if(mp.choice==1)set_mode(MP_COUNT);else{mp_defaults();options_begin();}
  }
  return;
 }
 if(game.mode==MP_CONNECT){
  if(pressed&B){set_mode(MP_SETUP);return;}
  if(repeat&(UP|DOWN)){game.choice^=1;dirty=1;}
  if(pressed&A){
   link_create=game.choice==0;mp.link=1;mp.humans=2;mp.local=mp.viewer=mp.edit=2;
   mp_defaults();if(link_create)options_begin();else mp_name_begin();
  }
  return;
 }
 if(game.mode==MP_COUNT){
  if(pressed&B){set_mode(MP_SETUP);return;}
  if(repeat&(UP|DOWN|LEFT|RIGHT)){mp.humans=5-mp.humans;dirty=1;}
  if(pressed&A){mp_defaults();options_begin();}
  return;
 }
 if(game.mode==MP_OPTION_HELP){
  if(pressed&(A|B|SELECT)){set_mode(MP_OPTIONS);return;}
  int count=prefs.choice<3?2:prefs.choice==3?3:1;
  if(count>1&&(repeat&(LEFT|RIGHT))){option_help_value=(option_help_value+count+(repeat&LEFT?-1:1))%count;dirty=1;}
  return;
 }
 if(game.mode==MP_OPTIONS){
  if(mp.humans>1&&(pressed&SELECT)){option_help_value=option_value();set_mode(MP_OPTION_HELP);return;}
  if(pressed&B){set_mode(mp.link?MP_CONNECT:mp.humans>1?MP_COUNT:MP_SETUP);return;}
  int count=mp.humans>1?6:4;
  const int order[]={3,4,0,1,2,5};int position=prefs.choice;
  if(mp.humans>1)for(int i=0;i<count;i++)if(order[i]==prefs.choice)position=i;
  if(repeat&UP){position=(position+count-1)%count;dirty=1;}
  if(repeat&DOWN){position=(position+1)%count;dirty=1;}
  prefs.choice=mp.humans>1?order[position]:position;
  if((repeat&(LEFT|RIGHT))||(pressed&A)){
   int delta=repeat&LEFT?-1:1;
   if(prefs.choice==0)prefs.dictionary^=1;
   else if(prefs.choice==1)prefs.plus^=1;
   else if(prefs.choice==2)prefs.characters^=1;
   else if(mp.humans>1&&prefs.choice==3){prefs.rule=(prefs.rule+3+delta)%3;if(prefs.rule==MP_WINS&&prefs.rounds>5)prefs.rounds=5;}
   else if(mp.humans>1&&prefs.choice==4){int limit=prefs.rule==MP_WINS?5:8;prefs.rounds=(prefs.rounds+limit-1+delta)%limit+1;}
   else if(pressed&A){if(mp.humans==1)new_game();else{mp.edit=2;mp_name_begin();}}
   dirty=1;
  }
  return;
 }
 if(game.mode==MP_NAME){
  if(mp_name_error){if(pressed&(A|B)){mp_name_error=0;dirty=1;}return;}
  if(repeat&LEFT)game.cursor=(game.cursor+31)%32;if(repeat&RIGHT)game.cursor=(game.cursor+1)%32;
  if(repeat&UP)game.cursor=(game.cursor+24)%32;if(repeat&DOWN)game.cursor=(game.cursor+8)%32;
  if((pressed&A)&&game.solve_pos<10)game.answer[game.solve_pos++]=128+game.cursor;
  if((pressed&R)&&game.solve_pos<10)game.answer[game.solve_pos++]=' ';
  if((pressed&B)&&!game.solve_pos&&mp.link){set_mode(link_create?MP_OPTIONS:MP_CONNECT);return;}
  if((pressed&B)&&game.solve_pos)game.answer[--game.solve_pos]=0;
  if(pressed&START){
   char candidate[11];name_clean(candidate,(const char*)game.answer);
   if(!candidate[0]){mp_name_error=2;dirty=1;return;}
   if(!mp.link&&name_taken(candidate,mp.edit)){mp_name_error=1;dirty=1;return;}
   for(int i=0;i<11;i++)mp.names[mp.edit][i]=candidate[i];
   if(mp.link&&!link_create){link_open();set_mode(MP_LOBBY);}
   else{if(avatars[mp.edit]>=(prefs.characters?9:7))avatars[mp.edit]=0;set_mode(MP_AVATAR);}
  }
  dirty=1;return;
 }
 if(game.mode==MP_AVATAR){
  int count=prefs.characters?9:7,columns=(count+1)/2;
  if(repeat&LEFT){avatars[mp.edit]=(avatars[mp.edit]+count-1)%count;dirty=1;}
  if(repeat&RIGHT){avatars[mp.edit]=(avatars[mp.edit]+1)%count;dirty=1;}
  if(repeat&(UP|DOWN)){
   int avatar=avatars[mp.edit];
   int target=avatar>=columns?avatar-columns:avatar+columns;
   avatars[mp.edit]=target<count?target:count-1;dirty=1;
  }
  if(pressed&B){set_mode(MP_NAME);return;}
  if(pressed&(A|START)){
   if(mp.link){link_open();set_mode(MP_LOBBY);}
   else if(mp.edit==2){mp.edit=0;mp_name_begin();}
   else if(mp.edit==0&&mp.humans==3){mp.edit=1;mp_name_begin();}
   else new_game();
  }
  return;
 }
 if(game.mode==MP_LOBBY){return;}
 if(game.mode==MP_ERROR){if(pressed&B){link_close();if(link_role_error){game.choice=link_create?0:1;set_mode(MP_CONNECT);}else{mp.link=0;mp.humans=1;set_mode(TITLE);}}return;}
 if(game.mode==MP_PASS){if(pressed&A)set_mode(TURN);return;}

 if(mp.humans>1&&game.mode==ROUND_END){if(pressed&A){mp_settle();set_mode(MP_SUMMARY);}return;}
 if(start_pending){
  if(pressed&A_RELEASE){int select_mode=start_pending==2;start_pending=0;ui.active=ui.viewer=0;if(select_mode)mp_setup();else{mp.humans=1;mp.link=0;mp.viewer=2;options_begin();}}
  return;
 }
 pressed&=~A_RELEASE;
 if(pressed&L){sound_on=!sound_on;speaker_enable(sound_on);dirty=1;}
 if(!mp.link&&(pressed&menu_button())){if(game.mode==RESTART_CONFIRM)set_mode(MENU);else if(ui.active)menu_close();else menu_open();return;}
 if(game.mode==RESTART_CONFIRM){
  if(pressed&B){set_mode(MENU);return;}
  if(repeat&(UP|DOWN)){ui.confirm^=1;dirty=1;}
  if(pressed&A){
   if(!ui.confirm)set_mode(MENU);
   else{cancel_record();ui.active=ui.viewer=0;set_mode(TITLE);}
  }
  return;
 }
 if(game.mode==MENU){
  int count=4;
  if(pressed&B){menu_close();return;}
  if(repeat&UP){ui.choice=(ui.choice+count-1)%count;dirty=1;}
  if(repeat&DOWN){ui.choice=(ui.choice+1)%count;dirty=1;}
  if(pressed&A){
   if(ui.choice==0){if(ui.origin==TITLE){fast_input=1;start_pending=2;}else menu_close();}
   else if(ui.choice==1)set_mode(HELP);
   else if((ui.origin==TITLE&&ui.choice==3)||(ui.origin!=TITLE&&ui.choice==2)){ui.author_page=0;set_mode(AUTHORS);}
   else if(ui.origin==TITLE){ui.viewer=1;set_mode(RECORDS);}
   else{ui.confirm=0;set_mode(RESTART_CONFIRM);}
  }
  return;
 }
 if(game.mode==HELP){
  if(pressed&B){set_mode(MENU);return;}
  return;
 }
 if(game.mode==AUTHORS){
  if(pressed&B){if(ui.author_page){ui.author_page=0;dirty=1;}else set_mode(MENU);}
  else if(pressed&A){if(!ui.author_page){ui.author_page=1;dirty=1;}else set_mode(MENU);}
  return;
 }
 if(game.mode==TITLE){if(pressed&A){fast_input=1;start_pending=2;}return;}
 if(game.mode==RECORDS){if(pressed&(A|B))set_mode(ui.viewer?MENU:TITLE);return;}
 if(game.mode==MP_SUMMARY){
  if(pressed&A){
   if(match.next==2){game.player=match.winner;gift_begin(1);}
   else if(match.next==1){match.shootout=1;new_round();}
   else credits_begin();
  }
  return;
 }
 if(scene_tick(pressed))return;
 if(game.mode==GIFT_PAGES){
  if((pressed&B)&&scene.gift_page>0){scene.gift_page--;dirty=1;}
  else if(pressed&A){if(scene.gift_page<3){scene.gift_page++;dirty=1;}else if(scene.gift_final)final_records();else if(mp.humans>1)mp_depart(0);else farewell();}
  return;
 }
 if(game.mode==TURN){if(!human(game.player)){if(message_done(pressed,MESSAGE_TICKS))start_spin();}else{if(repeat&(LEFT|RIGHT)){int choice=(repeat&RIGHT)?1:0;if(choice!=game.choice){game.choice=choice;dirty=1;}}if(pressed&A){if(game.choice)start_spin();else solve_word();}}return;}
 if(game.mode==SPIN){
  if(pressed&A){game.sector=scene.spin_target;game.spin_steps=0;scene.spin_half=0;stop_spin();return;}
  /* The original renderer spent five VBlank per wheel phase. Preserve
   * its speed explicitly without changing spin_wait or the tone pitch. */
  unsigned spin_delay=game.spin_wait<5?5:(unsigned)game.spin_wait;
  if(scene.now-scene.spin_at>=spin_delay){game.wait=0;scene.spin_half^=1;scene.spin_at=scene.now;dirty=1;
   if(!scene.spin_half){game.spin_ticks++;game.sector=(game.sector+15)&15;game.spin_steps--;if(game.spin_steps<8)game.spin_wait=2+(8-game.spin_steps)*2;game_tone(55+(game.spin_steps%10)*10+game.spin_wait*100,1);if(game.spin_steps<=0){game.sector=scene.spin_target;stop_spin();}}
  }return;
 }
 if(game.mode==AI_ANSWER){if(message_done(pressed,MESSAGE_TICKS))choose_letter(scene.ai_letter);return;}
 if(game.mode==MP_DEPART){if(message_done(pressed,MESSAGE_TICKS))mp_depart_finish();return;}
 if(game.mode==RESULT){
  unsigned duration=result_reason==BANKRUPT||result_reason==WRONG_WORD?LONG_MESSAGE_TICKS:MESSAGE_TICKS;
  if(message_done(pressed,duration))end_result();return;
 }
 if(game.mode==LETTER||game.mode==SOLVE){if(!human(game.player)){if(message_done(pressed,MESSAGE_TICKS))ai_letter();return;}if(repeat&LEFT)game.cursor=(game.cursor+31)%32;if(repeat&RIGHT)game.cursor=(game.cursor+1)%32;if(repeat&UP)game.cursor=(game.cursor+24)%32;if(repeat&DOWN)game.cursor=(game.cursor+8)%32;if(repeat&(UP|DOWN|LEFT|RIGHT))dirty=1;if(game.mode==SOLVE){
  if(pressed&B){int p=game.solve_pos;do{p--;}while(p>=0&&game.revealed[p]);if(p>=0){game.solve_pos=p;game.answer[p]=0;dirty=1;}}
  if(pressed&A){if(game.solve_pos==len(word()))confirm_word();else if(fixed_letter(game.cursor))beep(110,10);else{game.answer[game.solve_pos++]=128+game.cursor;solve_advance();dirty=1;}}
 }else if(pressed&A){if(!game.used[game.cursor])choose_letter(game.cursor);else beep(110,10);}return;}
 if(game.mode==PLUS){
  int n=len(word());
  /* DOS 1000:1fd6/226d: only the human enters the position selector.
   * AI chooses one hidden position independently of keypad input. */
  if(!human(game.player)){
   if(message_done(pressed,MESSAGE_TICKS)){do{game.cursor=random_n(n);}while(game.revealed[game.cursor]);ai_announce((u8)word()[game.cursor]-128,game.cursor+1);}
   return;
  }
  if(repeat&(LEFT|RIGHT)){int delta=repeat&RIGHT?1:n-1;do{game.cursor=(game.cursor+delta)%n;}while(game.revealed[game.cursor]);dirty=1;}
  if(pressed&A)choose_letter((u8)word()[game.cursor]-128);return;
 }
 if(game.mode==CHEST){
  if(!human(game.player)){
   /* Let the chests settle and the host finish, then give the opponent
    * its own readable answer. Keypad input never chooses for the AI. */
   if(message_done(pressed,MESSAGE_TICKS)){game.choice=random_n(2);set_mode(AI_CHEST);say(game.choice?"Правая!":"Левая!","");scene.host_active=0;}
   return;
  }
  if(repeat&(LEFT|RIGHT)){game.choice=1-game.choice;dirty=1;}
  if(pressed&A)open_chest();return;
 }
 if(game.mode==AI_CHEST){if(message_done(pressed,MESSAGE_TICKS))open_chest();return;}
 if(game.mode==PRIZE){
  if(repeat&(LEFT|RIGHT)){int choice=(repeat&RIGHT)?1:0;if(choice!=game.choice){game.choice=choice;dirty=1;}}
  if(pressed&A){
   if(!game.deal){if(game.choice==1){open_letter();say(msg_fba,msg_fc7);}else{game.deal=1;game.prize=100;game.choice=1;prize_offer();}}
   else if(!game.choice){cash_begin();}
   else if(game.deal<4){game.deal++;game.prize=game.deal==2?1000:game.deal==3?100000:1000000;prize_offer();}
   else{game.deal=6;game.prize=random_n(10);set_mode(GAME_OVER);say(msg_ffa,msg_1029);}
  }return;
 }
 if(game.mode==ROUND_END&&(pressed&A)&&human(game.player)&&game.round<2){credits_begin();return;}
 if(game.mode==ROUND_END){if((pressed&A)||(human(game.player)&&game.round==2&&scene.now-scene.speech_at>=300)){if(!human(game.player))farewell();else gift_begin(1);}return;}
 if(game.mode==NAME){
  int old_cursor=game.cursor,old_pos=game.solve_pos;
  if(repeat&LEFT)game.cursor=(game.cursor+31)%32;if(repeat&RIGHT)game.cursor=(game.cursor+1)%32;if(repeat&UP)game.cursor=(game.cursor+24)%32;if(repeat&DOWN)game.cursor=(game.cursor+8)%32;
  if((pressed&A)&&game.solve_pos<10)game.answer[game.solve_pos++]=128+game.cursor;
  if((pressed&R)&&game.solve_pos<10)game.answer[game.solve_pos++]=' ';
  if((pressed&B)&&game.solve_pos>0)game.answer[--game.solve_pos]=0;
  if(pressed&START){const char*n=game.solve_pos?(const char*)game.answer:"ИГРОК";for(int i=0;i<11;i++)record_names[record_entry][i]=i<len(n)?n[i]:0;game.best=record_scores[0];save();record_pending=0;ui.viewer=0;set_mode(RECORDS);}
  if(game.cursor!=old_cursor||game.solve_pos!=old_pos)dirty=1;return;
 }
 if(game.mode==GAME_OVER){if((pressed&A)||(game.deal==6&&scene.now-scene.speech_at>=180)){if(game.deal==6)gift_begin(0);else if(game.deal==5)farewell();else set_mode(TITLE);}return;}
}
/* Local lobby editing stays outside synchronized gameplay state. Every
 * console continues exchanging packets while a participant corrects a name. */
static void link_edit_name(u16 pressed,u16 repeat){
 if(!link_name_edit){
  if(!(link_snapshot.name_conflicts&(1<<mp.local)))return;
  link_name_edit=1;link_text(link_name_answer,link_name,21);
  link_name_pos=len(link_name_answer);return;
 }
 if(link_name_edit==1||link_name_edit==3){if(pressed&(A|B))link_name_edit=2;return;}
 if(repeat&LEFT)link_name_cursor=(link_name_cursor+31)%32;
 if(repeat&RIGHT)link_name_cursor=(link_name_cursor+1)%32;
 if(repeat&UP)link_name_cursor=(link_name_cursor+24)%32;
 if(repeat&DOWN)link_name_cursor=(link_name_cursor+8)%32;
 if((pressed&A)&&link_name_pos<10)link_name_answer[link_name_pos++]=128+link_name_cursor;
 if((pressed&R)&&link_name_pos<10)link_name_answer[link_name_pos++]=' ';
 if((pressed&B)&&link_name_pos)link_name_answer[--link_name_pos]=0;
 link_name_answer[link_name_pos]=0;
 if(pressed&START){
  char candidate[11];name_clean(candidate,link_name_answer);
  if(!candidate[0]){link_name_edit=3;return;}
  link_text(link_name,candidate,11);link_name_edit=0;
 }
}
static void link_render_name(void){
 Game saved=game;int edit=mp.edit,error=mp_name_error;
 game.mode=MP_NAME;game.cursor=link_name_cursor;game.solve_pos=link_name_pos;
 for(int i=0;i<21;i++)game.answer[i]=link_name_answer[i];
 mp.edit=mp.local;mp_name_error=link_name_edit==3?2:link_name_edit==1;
 render();game=saved;mp.edit=edit;mp_name_error=error;
 mute_icon();present();
}
static void link_edit_avatar(u16 pressed,u16 repeat){
 if(!link_avatar_armed){if((REG16(0x04000130)&(A|START))==(A|START))link_avatar_armed=1;return;}
 int count=prefs.characters?9:7,columns=(count+1)/2;
 if(repeat&LEFT)link_avatar=(link_avatar+count-1)%count;
 if(repeat&RIGHT)link_avatar=(link_avatar+1)%count;
 if(repeat&(UP|DOWN)){int next=link_avatar>=columns?link_avatar-columns:link_avatar+columns;link_avatar=next<count?next:count-1;}
 if(pressed&(A|START))link_avatar_edit=0;
}
static void link_render_avatar(void){
 Game saved=game;int edit=mp.edit,avatar=avatars[mp.local];
 game.mode=MP_AVATAR;mp.edit=mp.local;avatars[mp.local]=link_avatar;
 render();game=saved;mp.edit=edit;avatars[mp.local]=avatar;
 mute_icon();present();
}
void gba_main(void){
 REG16(0x0400010a)=0;REG16(0x0400010e)=0;
 REG16(0x04000108)=0;REG16(0x0400010c)=0;
 REG16(0x0400010e)=0x84;REG16(0x0400010a)=0x80;
 extern void gba_irq(void);REG32(0x03007ffc)=(u32)gba_irq;game.magic=0x504f4c45;REG16(0x04000204)=0x4317;game.rng=boot_seed();game.word_id=-1;game.best=load();REG16(0x04000000)=0x0404;for(int i=0;i<16;i++)((volatile u16*)0x05000000)[i]=palette[i];speaker_init();REG16(0x04000200)|=1;REG16(0x04000004)|=8;set_mode(TITLE);
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
  oldkeys=keys;
  if(game.mode==LINK_TEST){
   link_test_update(pressed,repeat);
   if(game.mode==LINK_TEST){
    if(dirty||video_ticks-link_test_redraw>=6){render();present();link_test_redraw=video_ticks;dirty=0;}
    else if(!link_test.running)vblank();
    continue;
   }
   pressed=repeat=0;
  }
  if(mp.link&&link_active){
   if(pressed&L){sound_on=!sound_on;speaker_enable(sound_on);dirty=1;}
   link_submit=(link_name_edit||link_avatar_edit)?0:(keys|pressed)&~L;
   if(!link_frame()){
    link_error_stage=link_stage;link_error_status=link_status;
    link_close();
    if(link_cancelled){
     if(link_role_error){game.choice=link_create?0:1;set_mode(MP_CONNECT);}
     else{mp_setup();mp.choice=2;}pressed=repeat=0;
     /* The B tap may also be queued by VBlank while SIO was waiting. */
     ime=REG16(0x04000208);REG16(0x04000208)=0;
     capture_keys();input_read=input_write;REG16(0x04000208)=ime;
    }else set_mode(MP_ERROR);
   }
   if(link_active&&link_role_error){
    Game saved=game;game.mode=MP_ERROR;render();game=saved;mute_icon();present();continue;
   }
   if(link_active&&game.mode==TITLE){link_close();mp.link=0;mp.humans=1;dirty=1;}
   if(link_active&&game.mode==MP_LOBBY){
    if(link_name_edit&&mp.local==2)link_start_armed=0;
    link_edit_name(pressed,repeat);
    if(link_name_edit){link_render_name();continue;}
    if(link_avatar_edit){link_edit_avatar(pressed,repeat);if(link_avatar_edit){link_render_avatar();continue;}}
   }
   if(link_active&&mp.local!=2){dirty=1;render();mute_icon();present();continue;}
   if(link_active){keys=link_keys;pressed=keys&~link_oldkeys;repeat=pressed;
    if(keys!=link_oldkeys)link_repeat_at=video_ticks+18;
    else if((keys&(UP|DOWN|LEFT|RIGHT))&&(int)(video_ticks-link_repeat_at)>=0){repeat|=keys&(UP|DOWN|LEFT|RIGHT);link_repeat_at=video_ticks+5;}
    link_oldkeys=keys;
    if(game.mode==MP_LOBBY){
     dirty=1;
     if(!(keys&START)&&!(oldkeys&START))link_start_armed=1;
     if(link_start_armed&&(pressed&START)&&mp.humans>=2&&!link_snapshot.name_conflicts&&!link_snapshot.name_editing&&!link_snapshot.avatar_editing)new_game();
    }
   }
  }
  game.frame++;update(pressed,repeat);
  scene.now=video_ticks;visual_tick();u32 key=visual_key();if(key!=rendered_key)dirty=1;
  if(dirty){scene.last_redraw=scene.now;render();mute_icon();present();rendered_key=key;rendered_frames++;dirty=0;}else vblank();
 }
}
