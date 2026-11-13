/* GBA SIO multiplayer, 115200 baud. Host owns all rules/RNG; clients render
 * checked events and animate locally. No framebuffer or SRAM crosses cable.
 * All participants need the same ROM (build fingerprint in the handshake). */
static int link_create,link_role_error,link_avatar_edit,link_avatar_armed;
static int link_active,link_connected,link_start_armed,link_cancelled;
static u16 link_avatar;
static int link_name_edit,link_name_cursor,link_name_pos;
static char link_name_answer[21];
static u16 link_keys,link_oldkeys,link_submit;
static u32 link_repeat_at;
static volatile u32 link_serial;
static u32 link_boot_serial;
static volatile u32 link_completed_at;
static int link_session;
static u32 link_last_packet,link_event_key,link_packets,link_events;
static int link_event_valid;
static u16 link_taps;
/* Compare rule state, not the clock, RNG cursor or intermediate poses. This
 * also catches input changes within a mode (cursor, choice, typed answer). */
static u32 link_semantic_key(void);
static void link_rebase(u32 elapsed){
 scene.now+=elapsed;scene.speech_at+=elapsed;scene.start+=elapsed;
 scene.phase_at+=elapsed;scene.spin_at+=elapsed;scene.title_at+=elapsed;
 scene.chest_until+=elapsed;scene.host_at+=elapsed;scene.host_phase_at+=elapsed;
 cash.next_at+=elapsed;cash.pause_at+=elapsed;
}
static char link_sent_name[11];
static volatile u16 link_received[4],link_status;
/* Stop-and-wait: low byte, high byte, CRC, commit. Tags alone do not
 * validate the payload. Neither CPU may consume an unchecked word. */
static volatile u16 link_reply,link_decoded,link_low,link_ack;
static volatile unsigned link_pending,link_phase,link_done,link_fault,link_retries;
static volatile u16 link_wire_word;
static unsigned link_sequence;
static int link_stage,link_error_stage;
static volatile int link_master,link_started;
static u16 link_error_status;
static u16 link_error_received,link_error_expected;
static int link_mismatch(u16 received,u16 expected){link_error_received=received;link_error_expected=expected;return 0;}
static u16 link_remote[4];
static char link_name[11],link_saved_names[8][11];
static char link_incoming_names[3][11];
static int link_saved_scores[8];
static struct {
 Match match;int rule,rounds;Game game;Scene scene;SoundCommand sound;Cash cash;u32 cash_seed;u32 event,tokens[2];char names[3][11];
 u8 durations[10];int eliminated,dictionary,plus,characters,pool[8],ai_index,avatars[3],humans,name_conflicts,name_editing,avatar_editing;char records[8][11];int scores[8];
} link_snapshot;
static u16 link_previous[sizeof link_snapshot/2];
static char link_message1[96],link_message2[96];
static void link_copy(volatile void*d,const volatile void*s,unsigned n){volatile u8*a=d;const volatile u8*b=s;while(n--)*a++=*b++;}
static void link_text(char*d,const char*s,unsigned cap){unsigned i=0;while(s&&s[i]&&i+1<cap){d[i]=s[i];i++;}d[i]=0;}
/* CRC-8/ATM over both bytes. The snapshot hash remains an independent
 * end-to-end check; this CRC permits retransmission before consuming data. */
static u32 link_hash(const void*data,unsigned n);
static u32 link_semantic_key(void){
 Game state=game;
 state.frame=state.rng=0;state.wait=0;
 state.spin_ticks=state.spin_steps=state.spin_wait=0;
 if(state.mode==SPIN)state.sector=0;
 if(state.mode==REVEAL)for(int i=0;i<20;i++)state.revealed[i]=0;
 u32 key=link_hash(&state,sizeof state);
 /* No visual timer/pose may become a reason to publish another event. */
 u32 extra[]={presentation_event,scene.phase,scene.gift_page,scene.gift_final,
  cash.total,cash.drawn==cash.total,game.mode==SPIN||game.mode==CASH?0:sound_command.sequence};
 return key^link_hash(extra,sizeof extra)^link_hash(&match,sizeof match)^link_hash(&prefs,sizeof prefs)^(unsigned)mp.eliminated;
}
static int link_due(void){
 if(game.mode==MP_LOBBY||!link_session||link_role_error)return 1;
 if(link_master)return !link_event_valid||link_semantic_key()!=link_event_key||video_ticks-link_last_packet>=6;
 /* A new low-byte phase is the host's request. The final commit ACK from
  * the preceding packet is not a request. Keep rendering until it arrives. */
 return (link_received[0]&0xff00)==(0xa000|(link_phase&0x200))||video_ticks-link_last_packet>=120;
}
static unsigned link_crc(u16 word){
 unsigned crc=0;
 for(unsigned byte=0;byte<2;byte++){
  crc^=(word>>(byte*8))&255;
  for(unsigned bit=0;bit<8;bit++)crc=((crc<<1)^((crc&128)?7:0))&255;
 }
 return crc;
}
static void link_irq(void){
 u16 status=REG16(0x04000128);
 /* A delayed IRQ may belong to a duplicate phase preceding the transfer
  * now in flight. Receive registers are partial and ERROR is undefined
  * while BUSY. Wait for this transfer's completion instead. */
 if(status&128)return;
 link_status=status;
 for(int i=0;i<4;i++)link_received[i]=REG16(0x04000120+i*2);
 if(game.mode==LINK_TEST){link_test_irq();link_serial++;return;}
 if(link_master==0&&link_received[0]!=0xffff)link_started=1;
 if(link_master==1)for(int i=1;i<4;i++)if(link_received[i]!=0xffff)link_started=1;
 if(link_status&64)link_fault=1;
 if(link_master==0&&!link_fault){
  u16 word=link_received[0],tag=word&0xff00;link_wire_word=word;
  if(!link_done&&!(link_phase&1)&&(tag==0xa000||tag==0xa200))link_phase=tag&0x200;
  unsigned low=0xa000|(link_phase&0x200);
  if(link_pending&&tag==low){
   link_low=word&255;link_phase=(link_phase&0x200)|1;
   REG16(0x0400012a)=low|(link_reply&255);
  }else if(link_pending&&(link_phase&1)&&tag==(low|0x100)){
   link_decoded=link_low|((word&255)<<8);
   link_phase=(link_phase&0x200)|3;
   REG16(0x0400012a)=tag|(link_reply>>8);
  }else if(link_pending&&(link_phase&2)&&tag==(low|0x400)){
   if((word&255)==link_crc(link_decoded)){
    link_phase|=4;
    REG16(0x0400012a)=tag|link_crc(link_reply);
   }else{
    link_phase&=~4u;link_retries++;
    REG16(0x0400012a)=(low|0x800); /* NACK: retry both bytes. */
   }
  }else if(link_pending&&(link_phase&4)&&word==((low|0x500)|0x5a)){
   link_ack=word;link_pending=0;
   link_phase=(link_phase^0x200)&0x200;link_done++;
   /* The main loop publishes this ACK only after copying link_decoded. */
  }
  /* Duplicate phases keep the last acknowledgement, including while the
   * main loop is drawing, hashing, or preparing the following word. */
 }
 link_completed_at=input_clock();link_serial++;
}
static void link_close(void){if(link_active&&mp.local!=2){link_copy(record_names,link_saved_names,sizeof record_names);link_copy(record_scores,link_saved_scores,sizeof record_scores);}REG16(0x04000200)&=~128;REG16(0x04000128)=0;REG16(0x04000134)=0x8000;link_active=0;}
static void link_open(void){
 link_last_packet=video_ticks;link_event_valid=0;link_taps=0;link_packets=link_events=0;
 link_session=0;for(int i=0;i<11;i++)link_sent_name[i]=0;
 link_role_error=0;link_avatar_edit=!link_create;link_avatar_armed=0;
 link_connected=1;link_start_armed=link_cancelled=link_name_edit=0;link_name_cursor=game.cursor;
 link_copy(link_saved_names,record_names,sizeof record_names);link_copy(link_saved_scores,record_scores,sizeof record_scores);
 link_text(link_name,mp.names[2],11);link_avatar=avatars[2];link_oldkeys=link_submit=0;
 for(unsigned i=0;i<sizeof link_previous/2;i++)link_previous[i]=0;
 for(unsigned i=0;i<sizeof link_snapshot;i++)((u8*)&link_snapshot)[i]=0;
 link_pending=link_phase=link_done=link_fault=link_sequence=0;link_ack=link_wire_word=0;link_retries=0;
 link_master=-1;link_started=link_stage=link_error_stage=0;link_status=link_error_status=0;
 link_error_received=link_error_expected=0;
 link_boot_serial=link_serial;
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
static int link_wire_exchange(u16 value,u32 exchange_start){
 if(link_cancel_requested())return 0;
 u32 serial=link_serial;int master=link_master;
 link_wire_word=value;REG16(0x0400012a)=value;
 if(master){
  /* Preserve the 4096-cycle turnaround, counting work already done since
   * the previous IRQ instead of adding another full delay after that work. */
  while(input_clock()-link_completed_at<4096){}
  while(!(REG16(0x04000128)&8)){if(link_cancel_requested()||link_timed_out(exchange_start))return 0;}
  REG16(0x04000128)|=128;
 }
 /* Once START was issued, an IRQ must arrive even before the first peer
  * word. Initial lobby waiting must not disable this hardware deadline. */
 u32 wire_start=input_clock();
 while(link_serial==serial){if(link_cancel_requested()||link_timed_out(exchange_start)||input_clock()-wire_start>(game.mode==MP_LOBBY?503316480u:33554432u))return 0;}
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
  REG16(0x0400012a)=link_ack;
  mp.local=((link_status>>4&3)+2)%3;
  return 1;
 }
 u16 result[4]={value,0xffff,0xffff,0xffff};unsigned members=0;
 unsigned phase=0;
 while(phase<4){
  /* Keep the alternating word bit separate from the four phase tags. */
  unsigned tags[4]={0,0x100,0x400,0x500};
  u16 tag=0xa000|link_sequence|tags[phase];
  unsigned payload=phase<2?(value>>(phase*8))&255:phase==2?link_crc(value):0x5a;
  int retry=0;unsigned polls=0;
  for(;;){
   int started=link_started;
   if(!link_wire_exchange(tag|payload,start))return 0;
   if(!started)start=input_clock();
   int ready=1;unsigned present=0;
   for(int i=1;i<4;i++)if(link_remote[i]!=0xffff){
    present|=1u<<i;
    if((link_remote[i]&0xff00)!=tag)ready=0;
    if(phase==2&&((link_remote[i]&0xff00)==(0xa800|link_sequence)))retry=1;
   }
   if(phase&&present!=members)return 0;
   if(retry)break;
   if(ready){
    if(!phase)members=present;
    for(int i=1;i<4;i++)if(present&(1u<<i)){
     if(!phase)result[i]=link_remote[i]&255;
     else if(phase==1)result[i]|=(link_remote[i]&255)<<8;
     else if(phase==2&&(link_remote[i]&255)!=link_crc(result[i]))retry=1;
     else if(phase==3&&(link_remote[i]&255)!=0x5a)return 0;
    }
    break;
   }
   if(link_cancel_requested()||link_timed_out(start))return 0;
   /* A peer may be drawing. Do not flood the cable with the same phase. */
   if(++polls>2){
    unsigned shift=polls<6?polls-2:4;u32 pause=input_clock();
    while(input_clock()-pause<(4096u<<shift))if(link_cancel_requested()||link_timed_out(start))return 0;
   }
  }
  if(!members)break;
  if(link_timed_out(start))return 0;
  if(retry)link_retries++;
  phase=retry?0:phase+1;
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
  /* Bootstrap with one hardware transfer, then use the assigned ID, not
   * a cached SI pin level. START is read-only on children, so requesting
   * it on every console starts exactly one transfer, on the parent. A
   * late main loop may already have received it in IRQ while rendering. */
  while(link_serial==link_boot_serial){
   if(link_cancel_requested())return 0;
   if((REG16(0x04000128)&0x88)==8){REG16(0x0400012a)=0xc091;REG16(0x04000128)|=128;break;}
  }
  u32 boot_start=input_clock();
  while(link_serial==link_boot_serial)if(link_cancel_requested()||input_clock()-boot_start>503316480u)return 0;
  if(link_status&64)return 0;
  unsigned id=(link_status>>4)&3;if(id>=3)return 0;
  link_master=id==0;mp.local=(id+2)%3;
  link_started=id!=0;
  if(!id)for(int i=1;i<4;i++)if(link_received[i]!=0xffff)link_started=1;
 }
 int master=link_master;u16 header=0xa710;
 int full=!link_session,lobby=game.mode==MP_LOBBY;
 u32 event_key=master?link_semantic_key():0;
 int event=lobby||!link_event_valid||event_key!=link_event_key;
 u32 start=input_clock();link_stage=2;
 /* A client advertises readiness only after drawing its previous snapshot.
  * Repeated headers are harmless; the separate START word begins the packet. */
 if(master){
  for(;;){
   int started=link_started;
   if(!link_exchange(header))return 0;
   if(!started)start=input_clock();
   int ready=1,connected=1;
   for(int i=1;i<4;i++)if(link_remote[i]!=0xffff){
    if(i!=connected||i==3)return 0;
    connected++;
    if(link_remote[i]==(header|1))full=1;
    else if(link_remote[i]!=header)ready=0;
   }
   if(!lobby&&(connected!=mp.humans||full))return 0;
   if(ready&&connected>=2){
    if(game.mode==MP_LOBBY)mp.humans=connected;
    if(link_connected!=connected)full=1;
    link_connected=connected;break;
   }
   if(link_timed_out(start))return 0;
  }
  /* The parent announces packet contents; clients may still be displaying
   * the preceding mode during a lobby-to-game transition. */
  if(!link_exchange(0xb178|(full?2:0)|(lobby?4:0)|(!event?1:0)))return 0;
 }else{
  for(;;){
   if(!link_exchange(header|(link_session?0:1)))return 0;
   if((link_remote[0]&0xfff8)==0xb178){
    event=!(link_remote[0]&1);full=(link_remote[0]&2)!=0;lobby=(link_remote[0]&4)!=0;
    if(!link_session&&!full)return link_mismatch(link_remote[0],0xb17e);
    break;
   }
   if(link_remote[0]!=header)return link_mismatch(link_remote[0],header);
   if(link_timed_out(start))return 0;
  }
 }
 u16 value;
 if(full){
 link_stage=3;
 if(!link_word(MULTIPLAYER_BUILD&65535,MULTIPLAYER_BUILD&65535,&value))return 0;
 if(value!=(MULTIPLAYER_BUILD&65535))return link_mismatch(value,MULTIPLAYER_BUILD&65535);
 if(master)for(int i=1;i<mp.humans;i++)if(link_remote[i]!=value)return link_mismatch(link_remote[i],value);
 if(!link_word(MULTIPLAYER_BUILD>>16,MULTIPLAYER_BUILD>>16,&value))return 0;
 if(value!=(MULTIPLAYER_BUILD>>16))return link_mismatch(value,MULTIPLAYER_BUILD>>16);
 if(master)for(int i=1;i<mp.humans;i++)if(link_remote[i]!=value)return link_mismatch(link_remote[i],value);
 /* Roles are explicit, but the cable still determines the hardware parent.
  * Report a bad choice to every participant before accepting game input. */
 link_stage=8;
 if(!link_word(link_create,link_create,0))return 0;
 unsigned role_error=0;
 if(master){
  if(!link_remote[0])role_error=1;
  for(int i=1;i<mp.humans;i++)if(link_remote[i])role_error=link_create?2:3;
 }
 if(!link_word(role_error,0,&value))return 0;
 /* Keep exchanging while showing the role warning. Closing a child here
  * would remove its final ACK before the parent can collect it. */
 if(value){link_role_error=value;return 1;}
 link_session=1;
 /* A joining lobby participant needs a complete base, not deltas against
  * a snapshot it has never received. Existing peers reset that base too. */
 if(master)for(unsigned i=0;i<sizeof link_previous/2;i++)link_previous[i]=0;
 else for(unsigned i=0;i<sizeof link_snapshot;i++)((u8*)&link_snapshot)[i]=0;
 }
 link_stage=4;
 if(!link_word(link_submit,link_submit,0))return 0;
 if(master){int device=(game.player+1)%3;link_keys=human(game.player)?link_remote[device]:link_remote[0];if(game.mode==MP_LOBBY)link_keys=link_remote[0];}
 link_packets++;link_last_packet=video_ticks;
 if(!event)return 1; /* Input/keepalive: no poses, text or snapshot hash. */
 link_events++;
 u32 event_at=video_ticks;
 if(lobby){
  int name_changed=full;
  for(int j=0;j<11;j++)if(link_name[j]!=link_sent_name[j])name_changed=1;
  /* Avatar and edit flags fit in one word. Names are sent only when at
   * least one participant changed theirs, or a fresh session needs them. */
  unsigned status=link_avatar|(link_name_edit?16:0)|(link_avatar_edit?32:0)|(name_changed?64:0);
  link_stage=5;
  if(!link_word(status,status,0))return 0;
  unsigned names_needed=full;
  if(master){
   link_snapshot.name_editing=link_snapshot.avatar_editing=0;
   for(int i=0;i<mp.humans;i++){
    unsigned state=link_remote[i],avatar=state&15;
    if((state&~127u)||avatar>(prefs.characters?8u:6u))return 0;
    avatars[(i+2)%3]=avatar;
    if(state&16)link_snapshot.name_editing|=1<<((i+2)%3);
    if(state&32)link_snapshot.avatar_editing|=1<<((i+2)%3);
    if(state&64)names_needed=1;
   }
  }
  if(!link_word(names_needed,0,&value))return 0;
  if(value>1)return 0;
  if(value){
   link_stage=4;
   for(int j=0;j<6;j++){
    u16 pair=(u8)link_name[j*2];if(j<5)pair|=(u16)(u8)link_name[j*2+1]<<8;
    if(!link_word(pair,pair,0))return 0;
    if(master)for(int i=0;i<mp.humans;i++){int p=(i+2)%3;link_incoming_names[p][j*2]=link_remote[i]&255;if(j<5)link_incoming_names[p][j*2+1]=link_remote[i]>>8;}
   }
   link_copy(link_sent_name,link_name,sizeof link_sent_name);
  }
  if(master)link_snapshot.name_conflicts=link_name_conflicts(link_incoming_names);
 }
 if(master){
  link_snapshot.match=match;link_snapshot.rule=prefs.rule;link_snapshot.rounds=prefs.rounds;
  link_snapshot.humans=mp.humans;
  link_copy(&link_snapshot.cash,&cash,sizeof cash);link_snapshot.cash_seed=cash_initial_seed;
  link_snapshot.sound=sound_command;link_snapshot.dictionary=prefs.dictionary;link_snapshot.plus=prefs.plus;link_snapshot.characters=prefs.characters;link_snapshot.ai_index=mp_ai_index;link_copy(link_snapshot.pool,opponent_pool,sizeof opponent_pool);
  link_copy(link_snapshot.records,record_names,sizeof record_names);link_copy(link_snapshot.scores,record_scores,sizeof record_scores);
  link_copy(&link_snapshot.game,&game,sizeof game);link_copy(&link_snapshot.scene,&scene,sizeof scene);link_snapshot.scene.now=event_at;
  link_copy(link_snapshot.avatars,avatars,sizeof avatars);link_copy(link_snapshot.names,mp.names,sizeof mp.names);link_snapshot.eliminated=mp.eliminated;
  link_copy(link_snapshot.durations,host_durations,sizeof host_durations);
  link_snapshot.event=presentation_event;link_copy(link_snapshot.tokens,message_tokens,sizeof message_tokens);
 }
 link_stage=6;
 u16*words=(u16*)&link_snapshot;unsigned changed=0;
 if(master)for(unsigned i=0;i<sizeof link_snapshot/2;i++)if(words[i]!=link_previous[i])changed++;
 if(!link_word(changed,0,&value))return 0;
 if(value>sizeof link_snapshot/2)return 0;
 if(master){
  for(unsigned i=0;i<sizeof link_snapshot/2;){
   if(words[i]==link_previous[i]){i++;continue;}
   unsigned run=1;
   while(i+run<sizeof link_snapshot/2&&words[i+run]!=link_previous[i+run])run++;
   /* Isolated words retain index/value encoding. Runs of at least three
    * changes share one index and length, without growing sparse deltas. */
   if(run<3){if(!link_word(i,0,0)||!link_word(words[i],0,0))return 0;i++;}
   else{
    if(!link_word(i|0x8000,0,0)||!link_word(run,0,0))return 0;
    for(unsigned j=0;j<run;j++)if(!link_word(words[i+j],0,0))return 0;
    i+=run;
   }
  }
 }else{
  unsigned remaining=value,previous=0;
  while(remaining){
   u16 encoded;if(!link_word(0,0,&encoded))return 0;
   unsigned index=encoded&0x7fff,run=1;
   if(encoded&0x8000){u16 length;if(!link_word(0,0,&length))return 0;run=length;if(run<3)return 0;}
   if(index<previous||index>=sizeof link_snapshot/2||run>remaining||run>sizeof link_snapshot/2-index)return 0;
   for(unsigned j=0;j<run;j++){if(!link_word(0,0,&value))return 0;words[index+j]=value;}
   previous=index+run;remaining-=run;
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
  presentation_event=link_snapshot.event;link_copy(message_tokens,link_snapshot.tokens,sizeof message_tokens);
  message1=message_decode(message_tokens[0],link_message1);message2=message_decode(message_tokens[1],link_message2);mp.viewer=mp.local;
  if(game.mode==CASH)cash_remote_sync(&link_snapshot.cash,link_snapshot.cash_seed);
  if(sound_command.sequence!=link_snapshot.sound.sequence){
   sound_command=link_snapshot.sound;
   if(sound_command.type==1)speaker_effect(sound_command.a,sound_command.seed);
   else if(sound_command.type==2)speaker_tone(sound_command.a,sound_command.b);
  }
 }
 /* Delivery time does not consume the local animation's lifetime. */
 if(!lobby)link_rebase(video_ticks-(master?event_at:link_snapshot.scene.now));
 link_event_key=event_key;link_event_valid=1;link_last_packet=video_ticks;dirty=1;
 return 1;
}
