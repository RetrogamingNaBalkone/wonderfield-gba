/* GBA SIO multiplayer, 115200 baud. Host owns all rules/RNG; clients render
 * complete checked snapshots. No pointer, framebuffer, or SRAM crosses cable.
 * All participants need the same ROM (build fingerprint in the handshake). */
static int link_active,link_connected,link_start_armed,link_cancelled;
static u16 link_avatar;
static int link_name_edit,link_name_cursor,link_name_pos;
static char link_name_answer[21];
static u16 link_keys,link_oldkeys,link_submit;
static u32 link_repeat_at;
static volatile u32 link_serial;
static volatile u16 link_received[4],link_status;
/* Stop-and-wait byte phases. SD-ready describes the electrical mode, not
 * whether the remote CPU has consumed a word. Replies are published by IRQ
 * only after link_exchange has supplied the next application word. */
static volatile u16 link_reply,link_decoded,link_low;
static volatile unsigned link_pending,link_phase,link_done,link_fault;
static unsigned link_sequence;
static int link_stage,link_error_stage;
static volatile int link_master,link_started;
static u16 link_error_status;
static u16 link_remote[4];
static char link_name[11],link_saved_names[8][11];
static char link_incoming_names[3][11];
static int link_saved_scores[8];
static struct {
 Match match;int rule,rounds;Game game;Scene scene;SoundCommand sound;Cash cash;u32 cash_seed;char names[3][11],first[96],second[96];
 u8 durations[10];int eliminated,dictionary,plus,characters,pool[8],ai_index,avatars[3],humans,name_conflicts,name_editing;char records[8][11];int scores[8];
} link_snapshot;
static u16 link_previous[sizeof link_snapshot/2];
static char link_message1[96],link_message2[96];
static void link_copy(volatile void*d,const volatile void*s,unsigned n){volatile u8*a=d;const volatile u8*b=s;while(n--)*a++=*b++;}
static void link_text(char*d,const char*s,unsigned cap){unsigned i=0;while(s&&s[i]&&i+1<cap){d[i]=s[i];i++;}d[i]=0;}
static void link_irq(void){
 u16 status=REG16(0x04000128);
 /* A delayed IRQ may belong to a duplicate phase preceding the transfer
  * now in flight. Receive registers are partial and ERROR is undefined
  * while BUSY. Wait for this transfer's completion instead. */
 if(status&128)return;
 link_status=status;
 for(int i=0;i<4;i++)link_received[i]=REG16(0x04000120+i*2);
 if(link_master==0&&link_received[0]!=0xffff)link_started=1;
 if(link_master==1)for(int i=1;i<4;i++)if(link_received[i]!=0xffff)link_started=1;
 if(link_status&64)link_fault=1;
 if(link_master==0&&!link_fault){
  u16 word=link_received[0],tag=word&0xff00;
  if(!link_done&&!(link_phase&1)&&(tag==0xa000||tag==0xa200))link_phase=tag&0x200;
  unsigned low=0xa000|(link_phase&0x200);
  if(link_pending&&tag==low){
   link_low=word&255;
   REG16(0x0400012a)=low|(link_reply&255);
   link_phase|=1;
  }else if(link_pending&&(link_phase&1)&&tag==(low|0x100)){
   link_decoded=link_low|((word&255)<<8);
   REG16(0x0400012a)=tag|(link_reply>>8);
   link_pending=0;link_phase=(link_phase^0x200)&0x200;link_done++;
  }
  /* Duplicate phases keep the last acknowledgement, including while the
   * main loop is drawing, hashing, or preparing the following word. */
 }
 link_serial++;
}
static void link_close(void){if(link_active&&mp.local!=2){link_copy(record_names,link_saved_names,sizeof record_names);link_copy(record_scores,link_saved_scores,sizeof record_scores);}REG16(0x04000200)&=~128;REG16(0x04000128)=0;REG16(0x04000134)=0x8000;link_active=0;}
static void link_open(void){
 link_connected=1;link_start_armed=link_cancelled=link_name_edit=0;link_name_cursor=game.cursor;
 link_copy(link_saved_names,record_names,sizeof record_names);link_copy(link_saved_scores,record_scores,sizeof record_scores);
 link_text(link_name,mp.names[2],11);link_avatar=avatars[2];link_oldkeys=link_submit=0;
 for(unsigned i=0;i<sizeof link_previous/2;i++)link_previous[i]=0;
 for(unsigned i=0;i<sizeof link_snapshot;i++)((u8*)&link_snapshot)[i]=0;
 link_pending=link_phase=link_done=link_fault=link_sequence=0;
 link_master=-1;link_started=link_stage=link_error_stage=0;link_status=link_error_status=0;
 REG16(0x0400012a)=0;
 REG16(0x04000134)=0;REG16(0x04000128)=0x6003;
 REG16(0x04000202)=128;REG16(0x04000200)|=128;link_active=1;
}
/* Poll local input inside the SIO waits too: an absent peer must not trap
 * either console in the lobby until the cable timeout expires. */
static int link_cancel_requested(void){
 if(game.mode==MP_LOBBY&&!link_name_edit&&!(link_snapshot.name_conflicts&(1<<mp.local))&&((link_submit|~REG16(0x04000130))&B))link_cancelled=1;
 return link_cancelled;
}
static int link_timed_out(u32 start){
 /* A player may still be booting the other cartridge or entering a name.
  * Keep waiting until a peer transmits; malformed handshakes still time out. */
 if(game.mode==MP_LOBBY&&!link_started)return 0;
 return input_clock()-start>(game.mode==MP_LOBBY?503316480u:33554432u);
}
static int link_wire_exchange(u16 value){
 if(link_cancel_requested())return 0;
 u32 serial=link_serial,start=input_clock();int master=link_master;
 REG16(0x0400012a)=value;
 if(master){
  /* Inter-word turnaround gives slaves time to consume and prepare replies. */
  while(input_clock()-start<4096){}
  while(!(REG16(0x04000128)&8)){if(link_cancel_requested()||link_timed_out(start))return 0;}
  REG16(0x04000128)|=128;
 }
 while(link_serial==serial){if(link_cancel_requested()||link_timed_out(start))return 0;}
 if(link_status&64)return 0;
 for(int i=0;i<4;i++)link_remote[i]=link_received[i];
 mp.local=((link_status>>4&3)+2)%3;
 return 1;
}
static int link_exchange(u16 value){
 u32 start=input_clock();
 if(!link_master){
  unsigned done=link_done;
  link_reply=value;link_pending=1;
  while(link_done==done){
   if(link_fault||link_cancel_requested()||link_timed_out(start))return 0;
  }
  link_remote[0]=link_decoded;
  mp.local=((link_status>>4&3)+2)%3;
  return 1;
 }
 u16 result[4]={value,0xffff,0xffff,0xffff};unsigned members=0;
 for(unsigned phase=0;phase<2;phase++){
  u16 tag=0xa000|link_sequence|(phase<<8);
  for(;;){
   if(!link_wire_exchange(tag|((value>>(phase*8))&255)))return 0;
   int ready=1;unsigned present=0;
   for(int i=1;i<4;i++)if(link_remote[i]!=0xffff){
    present|=1u<<i;
    if((link_remote[i]&0xff00)!=tag)ready=0;
   }
   if(phase&&present!=members)return 0;
   if(ready){
    if(!phase)members=present;
    for(int i=1;i<4;i++)if(present&(1u<<i)){
     if(!phase)result[i]=link_remote[i]&255;
     else result[i]|=(link_remote[i]&255)<<8;
    }
    break;
   }
   if(link_cancel_requested()||link_timed_out(start))return 0;
  }
  if(!members)break;
 }
 /* With no peers, keep the first sequence for a console joining the lobby. */
 if(members)link_sequence^=0x200;
 for(int i=0;i<4;i++)link_remote[i]=result[i];
 return 1;
}
static u32 link_hash(const void*data,unsigned n){const u8*p=data;u32 h=2166136261u;while(n--)h=(h^*p++)*16777619u;return h;}
static int link_word(u16 host,u16 reply,u16*out){
 int master=link_master;
 if(!link_exchange(master?host:reply))return 0;
 if(out)*out=link_remote[0];return 1;
}
static int link_frame(void){
 if(link_master<0){
  link_stage=1;
  /* GBATEK initialization order: wait for SD-ready BEFORE reading SI.
   * SI is not a reliable role indication while another GBA is booting. */
  u16 status;
  while(((status=REG16(0x04000128))&0x88)!=8)if(link_cancel_requested())return 0;
  link_master=!(status&4);
 }
 int master=link_master;u16 header=0xa710;
 u32 start=input_clock();link_stage=2;
 /* A client advertises readiness only after drawing its previous snapshot.
  * Repeated headers are harmless; the separate START word begins the packet. */
 if(master){
  for(;;){
   if(!link_exchange(header))return 0;
   int ready=1,connected=1;
   for(int i=1;i<4;i++)if(link_remote[i]!=0xffff){
    if(i!=connected||i==3)return 0;
    connected++;if(link_remote[i]!=header)ready=0;
   }
   if(game.mode!=MP_LOBBY&&connected!=mp.humans)return 0;
   if(ready&&connected>=2){
    if(game.mode==MP_LOBBY)mp.humans=connected;
    link_connected=connected;break;
   }
   if(link_timed_out(start))return 0;
  }
  if(!link_exchange(0xb17e))return 0;
 }else{
  for(;;){
   if(!link_exchange(header))return 0;
   if(link_remote[0]==0xb17e)break;
   if(link_remote[0]!=header||link_timed_out(start))return 0;
  }
 }
 u16 value;
 link_stage=3;
 if(!link_word(MULTIPLAYER_BUILD&65535,MULTIPLAYER_BUILD&65535,&value))return 0;
 if(value!=(MULTIPLAYER_BUILD&65535))return 0;
 if(master)for(int i=1;i<mp.humans;i++)if(link_remote[i]!=value)return 0;
 if(!link_word(MULTIPLAYER_BUILD>>16,MULTIPLAYER_BUILD>>16,&value))return 0;
 if(value!=(MULTIPLAYER_BUILD>>16))return 0;
 if(master)for(int i=1;i<mp.humans;i++)if(link_remote[i]!=value)return 0;
 link_stage=4;
 if(!link_word(link_submit,link_submit,0))return 0;
 if(master){int device=(game.player+1)%3;link_keys=human(game.player)?link_remote[device]:link_remote[0];if(game.mode==MP_LOBBY)link_keys=link_remote[0];}
 for(int j=0;j<6;j++){
  u16 pair=(u8)link_name[j*2];if(j<5)pair|=(u16)(u8)link_name[j*2+1]<<8;
  if(!link_word(pair,pair,0))return 0;
  if(master)for(int i=0;i<mp.humans;i++){int p=(i+2)%3;link_incoming_names[p][j*2]=link_remote[i]&255;if(j<5)link_incoming_names[p][j*2+1]=link_remote[i]>>8;}
 }
 link_stage=5;
 if(!link_word(link_avatar,link_avatar,0))return 0;
 if(master)for(int i=0;i<mp.humans;i++){
  if(link_remote[i]>(prefs.characters?8:6))return 0;
  avatars[(i+2)%3]=link_remote[i];
 }
 if(!link_word(link_name_edit,link_name_edit,0))return 0;
 if(master){
  link_snapshot.name_conflicts=link_name_conflicts(link_incoming_names);
  link_snapshot.name_editing=0;
  for(int i=0;i<mp.humans;i++)if(link_remote[i])link_snapshot.name_editing|=1<<((i+2)%3);
  link_snapshot.match=match;link_snapshot.rule=prefs.rule;link_snapshot.rounds=prefs.rounds;
  link_snapshot.humans=mp.humans;
  link_copy(&link_snapshot.cash,&cash,sizeof cash);link_snapshot.cash_seed=cash_initial_seed;
  link_snapshot.sound=sound_command;link_snapshot.dictionary=prefs.dictionary;link_snapshot.plus=prefs.plus;link_snapshot.characters=prefs.characters;link_snapshot.ai_index=mp_ai_index;link_copy(link_snapshot.pool,opponent_pool,sizeof opponent_pool);
  link_copy(link_snapshot.records,record_names,sizeof record_names);link_copy(link_snapshot.scores,record_scores,sizeof record_scores);
  link_copy(&link_snapshot.game,&game,sizeof game);link_copy(&link_snapshot.scene,&scene,sizeof scene);
  link_copy(link_snapshot.avatars,avatars,sizeof avatars);link_copy(link_snapshot.names,mp.names,sizeof mp.names);link_snapshot.eliminated=mp.eliminated;
  link_copy(link_snapshot.durations,host_durations,sizeof host_durations);
  link_text(link_snapshot.first,message1,96);link_text(link_snapshot.second,message2,96);
 }
 link_stage=6;
 u16*words=(u16*)&link_snapshot;unsigned changed=0;
 if(master)for(unsigned i=0;i<sizeof link_snapshot/2;i++)if(words[i]!=link_previous[i])changed++;
 if(!link_word(changed,0,&value))return 0;
 if(value>sizeof link_snapshot/2)return 0;
 if(master){
  for(unsigned i=0;i<sizeof link_snapshot/2;i++)if(words[i]!=link_previous[i]){
   if(!link_word(i,0,0)||!link_word(words[i],0,0))return 0;
  }
 }else{
  unsigned count=value,previous=0;
  for(unsigned j=0;j<count;j++){
   u16 index;if(!link_word(0,0,&index))return 0;
   if(index>=sizeof link_snapshot/2||(j&&index<=previous))return 0;previous=index;
   if(!link_word(0,0,&value))return 0;words[index]=value;
  }
 }
 link_stage=7;
 u32 hash=link_hash(&link_snapshot,sizeof link_snapshot),remote_hash;
 if(!link_word(hash&65535,hash&65535,&value))return 0;remote_hash=value;
 if(master)for(int i=1;i<mp.humans;i++)if(link_remote[i]!=value)return 0;
 if(!link_word(hash>>16,hash>>16,&value))return 0;remote_hash|=(u32)value<<16;
 if(master)for(int i=1;i<mp.humans;i++)if(link_remote[i]!=value)return 0;
 if(hash!=remote_hash)return 0;
 if(master)for(unsigned i=0;i<sizeof link_snapshot/2;i++)link_previous[i]=words[i];
 if(!master){
  if(link_snapshot.humans<2||link_snapshot.humans>3)return 0;
  match=link_snapshot.match;prefs.rule=link_snapshot.rule;prefs.rounds=link_snapshot.rounds;
  mp.humans=link_connected=link_snapshot.humans;
  link_copy(record_names,link_snapshot.records,sizeof record_names);link_copy(record_scores,link_snapshot.scores,sizeof record_scores);
  link_copy(&game,&link_snapshot.game,sizeof game);link_copy(&scene,&link_snapshot.scene,sizeof scene);
  link_copy(avatars,link_snapshot.avatars,sizeof avatars);link_copy(mp.names,link_snapshot.names,sizeof mp.names);mp.eliminated=link_snapshot.eliminated;prefs.dictionary=link_snapshot.dictionary;prefs.plus=link_snapshot.plus;prefs.characters=link_snapshot.characters;mp_ai_index=link_snapshot.ai_index;link_copy(opponent_pool,link_snapshot.pool,sizeof opponent_pool);
  link_copy(host_durations,link_snapshot.durations,sizeof host_durations);
  link_text(link_message1,link_snapshot.first,96);link_text(link_message2,link_snapshot.second,96);
  message1=link_message1;message2=link_message2;mp.viewer=mp.local;
  if(game.mode==CASH)cash_remote_sync(&link_snapshot.cash,link_snapshot.cash_seed);
  if(sound_command.sequence!=link_snapshot.sound.sequence){
   sound_command=link_snapshot.sound;
   if(sound_command.type==1)speaker_effect(sound_command.a,sound_command.seed);
   else if(sound_command.type==2)speaker_tone(sound_command.a,sound_command.b);
  }
 }
 return 1;
}
