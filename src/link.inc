/* GBA SIO multiplayer, 115200 baud. Host owns all rules/RNG; clients render
 * checked events and animate locally. No framebuffer or SRAM crosses cable.
 * All participants need the same ROM (build fingerprint in the handshake). */
static int link_create,link_avatar_edit,link_avatar_armed;
/* SIO parent clocks the bus; game authority is elected independently. */
static int link_host_device=-1,link_host_ready,link_setup_ready;
static int link_profile_pending,link_config_mode,link_choose_armed,link_back_mode;
static int link_join_prompt;
static u32 link_profile_render_key;
static u32 link_profile_base_key,link_profile_answer_key,link_keyboard_key;
static int link_profile_cursor,link_keyboard_cursor,link_keyboard_valid;
static int link_preview_valid,link_preview_mode,link_preview_player;
static int link_preview_cursor,link_preview_choice,link_preview_base_cursor,link_preview_base_choice;
static int link_is_host(void){return link_host_device>=0&&(mp.local+1)%3==link_host_device;}
static int link_active,link_connected,link_start_armed,link_cancelled;
static u16 link_avatar;
static int link_name_edit,link_name_cursor,link_name_pos,link_name_wait;
static char link_name_answer[21];
static u16 link_keys,link_submit;
static int link_keys_fresh; /* The host received owner input to apply. */
static volatile u32 link_serial;
static u32 link_boot_serial;
static volatile u32 link_completed_at;
static int link_session;
static u32 link_last_packet,link_event_key,link_packets,link_events;
static u32 link_clock_offset;
static int link_event_valid,link_resync;
/* Logical input events: one key each, directions carry an owner-side
 * autorepeat count. VBlank produces them from the owner's exact key timing,
 * so the authority never derives presses or autorepeat from held keys that
 * are sampled only once per packet. */
enum{LINK_TAP_SIZE=32,LINK_TAP_MAX=4,LINK_REMOTE_SIZE=16};
static volatile u16 link_tap_queue[LINK_TAP_SIZE];
static volatile u32 link_tap_context[LINK_TAP_SIZE];
static volatile u8 link_tap_read,link_tap_write;

static u16 link_remote_queue[LINK_REMOTE_SIZE];static u8 link_remote_read,link_remote_write;
static int link_remote_player;
static u32 link_remote_context;
static void link_tap_push(unsigned index,int coalesce){
 unsigned tail=(link_tap_write+LINK_TAP_SIZE-1)%LINK_TAP_SIZE;
 if(coalesce&&link_tap_context[tail]==presentation_event&&link_tap_read!=link_tap_write&&(link_tap_queue[tail]&15)==index&&(link_tap_queue[tail]>>4)<LINK_TAP_MAX-1){link_tap_queue[tail]+=16;return;}
 unsigned next=(link_tap_write+1)%LINK_TAP_SIZE;
 if(next!=link_tap_read){link_tap_context[link_tap_write]=presentation_event;link_tap_queue[link_tap_write]=index;link_tap_write=next;}
}
typedef struct {u32 context,at;u16 previous,armed;} DirectionRepeat;
static DirectionRepeat link_repeat;
static u16 directional_repeat(DirectionRepeat*r,u16 keys,u16 pressed){
 u16 directions=keys&(UP|DOWN|LEFT|RIGHT);
 if(r->context!=presentation_event){r->context=presentation_event;r->armed=0;}
 r->armed=(r->armed|pressed)&directions;
 if(keys!=r->previous||(pressed&(UP|DOWN|LEFT|RIGHT)))r->at=video_ticks+(navigation_menu()?30:18);
 else if(r->armed&&(int)(video_ticks-r->at)>=0){
  pressed|=r->armed;r->at=video_ticks+(navigation_menu()?12:5);
 }
 r->previous=keys;
 return pressed;
}
static void link_capture_input(u16 pressed){
 if(!link_active||link_name_edit||link_avatar_edit){link_repeat.armed=0;return;}
 u16 events=directional_repeat(&link_repeat,input_keys&~L,pressed&~L);
 /* Simultaneous presses keep local order: directions before buttons. */
 for(unsigned bit=4;bit<8;bit++)if(events&(1u<<bit))link_tap_push(bit+1,1);
 for(unsigned bit=0;bit<4;bit++)if(events&(1u<<bit))link_tap_push(bit+1,0);
 if(events&R)link_tap_push(9,0);
}
/* Input word: held keys in bits 0-8, event key index+1 in bits 10-13 and
 * its count-1 in bits 14-15. Held keys never generate presses remotely. */
static void link_sample_input(void){
 u16 ime=REG16(0x04000208);REG16(0x04000208)=0;
 u16 event=0;
 if(link_name_edit||link_avatar_edit)link_tap_read=link_tap_write;
 while(link_tap_read!=link_tap_write&&link_tap_context[link_tap_read]!=presentation_event)
  link_tap_read=(link_tap_read+1)%LINK_TAP_SIZE;
 if(link_tap_read!=link_tap_write){event=link_tap_queue[link_tap_read];link_tap_read=(link_tap_read+1)%LINK_TAP_SIZE;}
 u16 key=event&15?1u<<((event&15)-1):0;
 link_submit=(link_name_edit||link_avatar_edit)?0:((input_keys|key)&~L)|((event&15)<<10)|((event>>4)<<14);
 /* During play the authority consumes only edges. Use the otherwise idle
  * held-key field for the source presentation, retaining the lobby format. */
 if(event&&game.mode!=MP_LOBBY)link_submit=(link_submit&0xfc00)|0x200|(presentation_event&511);
 REG16(0x04000208)=ime;
}
/* The authority applies one received press per main-loop iteration. Presses
 * still queued when the turn changes belong to the previous owner. */
static void link_queue_remote(u16 word,int player){
 unsigned index=(word>>10)&15,count=(word>>14)+1;
 if(player!=link_remote_player||link_remote_context!=presentation_event)link_remote_read=link_remote_write;
 link_remote_context=presentation_event;
 link_remote_player=player;
 if(!index||index>9)return;
 if(game.mode==MP_LOBBY ? (word&0x200)!=0 : (word&1023)!=(0x200|(presentation_event&511)))return;
 while(count--){
  unsigned next=(link_remote_write+1)%LINK_REMOTE_SIZE;
  if(next==link_remote_read)break;
  link_remote_queue[link_remote_write]=1u<<(index-1);link_remote_write=next;
 }
}
static u16 link_next_remote(int player){
 if(player!=link_remote_player||link_remote_context!=presentation_event){link_remote_read=link_remote_write;link_remote_player=player;}
 if(link_remote_read==link_remote_write)return 0;
 u16 key=link_remote_queue[link_remote_read];link_remote_read=(link_remote_read+1)%LINK_REMOTE_SIZE;
 return key;
}
/* Compare rule state, not the clock, RNG cursor or intermediate poses. This
 * also catches input changes within a mode (cursor, choice, typed answer). */
static u32 link_semantic_key(void);
static void link_rebase_state(Scene*view,volatile Cash*money,u32 elapsed){
 view->now+=elapsed;view->speech_at+=elapsed;view->start+=elapsed;
 view->phase_at+=elapsed;view->spin_at+=elapsed;view->title_at+=elapsed;
 view->chest_until+=elapsed;view->host_at+=elapsed;view->host_phase_at+=elapsed;
 money->next_at+=elapsed;money->pause_at+=elapsed;
}
static void link_rebase(u32 elapsed){link_rebase_state(&scene,&cash,elapsed);}
static char link_sent_name[11];
static unsigned link_sent_status;
static volatile u16 link_received[4],link_status;
/* Block transport. The cable parent clocks every transfer of a block:
 *   probes until every member shows READY(kind,n), then
 *   HEADER(seq,kind,n), n data words, CRC-16, ASK, COMMIT or RETRY.
 * Each child answers from its serial IRQ: its own n words, their CRC-16,
 * then a verdict on the parent's words. A reply written in the IRQ after
 * transfer k is latched for transfer k+1, so a block costs n+4 transfers.
 * A child accepts only the block its main loop armed (kind and length) and
 * advertises it as READY, so an unready console costs one probe transfer,
 * not a whole block.
 * Commit is two-phase: the parent commits only after every member's CRC
 * and verdict check. Every later probe repeats COMMIT for the last committed
 * block, so a child that missed it catches up; a child never infers a commit
 * from other words, because payload seen out of position may resemble them. */
enum{LINK_BLOCK_MAX=64,LINK_HEADER=0xd000,LINK_READY=0x9000,LINK_IDLE=0xc1d0,LINK_ASK=0xe500,LINK_COMMIT=0xe5c0,LINK_RETRY=0xe5a0,LINK_OK=0xb5a0,LINK_BAD=0xb520};
/* Header: 0xd000|seq<<10|attempt<<9|kind<<6|(n-1). The attempt bit keeps a
 * child's stale verdict from the previous try of the same block from passing. */
enum{LINK_REQUEST,LINK_CONTROL,LINK_BUILD,LINK_LOBBY,LINK_PUBLISH,LINK_HASH,LINK_VERDICT};
enum{LINK_RX_IDLE,LINK_RX_DATA,LINK_RX_CRC,LINK_RX_ASK,LINK_RX_COMMIT};
static unsigned link_crc16(unsigned crc,unsigned word);
static int link_cancel_requested(void);
static void link_idle_reply(void);
static volatile u16 link_tx[LINK_BLOCK_MAX],link_rx[4][LINK_BLOCK_MAX],link_tx_crc;
static volatile unsigned link_armed,link_arm_kind,link_arm_n;
/* Every console receives every SIOMULTI slot. A child also keeps and checks
 * the other children's slots it needs (link_arm_need), so three consoles
 * with a child host need no relay block: the verdict covers those slots. */
static volatile unsigned link_arm_need,link_rx_peer_crc[4];
static volatile unsigned link_rx_state,link_rx_pos,link_rx_n,link_rx_seq,link_rx_attempt,link_rx_crc,link_rx_good,link_rx_present;
static volatile unsigned link_pending_commit,link_pending_seq;
static volatile unsigned link_done,link_present,link_request_ready,link_control_ready;
/* CONTROL carries no guest data: the IRQ arms it right after REQUEST and keeps
 * its words, so a keepalive completes while the guest's main loop renders. */
static volatile u16 link_control[2];
static volatile unsigned link_fault,link_retries,link_errors;
/* A hardware ERROR sample is treated as a damaged transfer: the block fails
 * its check and is repeated. Only a persistent run of errors ends the session. */
enum{LINK_ERROR_LIMIT=16};
static unsigned link_sequence,link_members;
static int link_in_packet; /* A packet is in progress across main-loop iterations. */
static u16 link_last_commit=LINK_IDLE; /* Probe word: repeats the last COMMIT. */
static int link_wire_bad;
/* Turnaround between transfers. It doubles while blocks fail, so a child
 * whose serial IRQ is late still sees every transfer, and halves back after
 * each success. */
static u32 link_gap=4096;
static volatile u16 link_wire_word; /* Last word on the wire, shown on the error screen. */
static int link_stage,link_error_stage;
static volatile int link_master,link_started;
static volatile int link_restart;
static u16 link_error_status;
static u16 link_error_received,link_error_expected;
static int link_mismatch(u16 received,u16 expected){link_error_received=received;link_error_expected=expected;return 0;}
static u16 link_remote[4];
static char link_name[11],link_saved_names[8][11];
static unsigned link_lobby_status(void){return link_avatar|(link_name_edit?16:0)|(link_avatar_edit?32:0);}
static int link_lobby_changed(void){
 if(link_lobby_status()!=link_sent_status)return 1;
 for(int i=0;i<11;i++)if(link_name[i]!=link_sent_name[i])return 1;
 return 0;
}
static char link_incoming_names[3][11];
static int link_saved_scores[8];
static struct {
 Match match;int rule,rounds;Game game;Scene scene;SoundCommand sound;Cash cash;u32 cash_seed;u32 event,tokens[2];char names[3][11];
 u8 durations[10];int eliminated,dictionary,plus,characters,pool[8],ai_index,avatars[3],humans,name_conflicts,name_editing,avatar_editing;char records[8][11];int scores[8];
} link_snapshot;
static u16 link_previous[sizeof link_snapshot/2];
/* Snapshot byte codec. XOR against the verified wire baseline. Each token
 * combines a zero skip and a literal run (four bits each, 255-byte extensions).
 * Small integer fields usually need just one token and one changed byte. */
static u8 link_delta[sizeof link_snapshot*2];
static unsigned link_encode_delta(void){
 const u8*current=(const u8*)&link_snapshot,*previous=(const u8*)link_previous;
 unsigned at=0,out=0;
 while(at<sizeof link_snapshot){
  unsigned start=at;
  while(at<sizeof link_snapshot&&current[at]==previous[at])at++;
  unsigned skip=at-start,literal=at;
  while(at<sizeof link_snapshot&&current[at]!=previous[at])at++;
  unsigned count=at-literal;
  link_delta[out++]=((skip<15?skip:15)<<4)|(count<15?count:15);
  if(skip>=15){unsigned n=skip-15;while(n>=255){link_delta[out++]=255;n-=255;}link_delta[out++]=n;}
  if(count>=15){unsigned n=count-15;while(n>=255){link_delta[out++]=255;n-=255;}link_delta[out++]=n;}
  for(unsigned i=0;i<count;i++)link_delta[out++]=current[literal+i]^previous[literal+i];
 }
 return out;
}
static int link_delta_count(unsigned*at,unsigned length,unsigned first,unsigned*out){
 unsigned count=first;
 if(first==15){
  unsigned extra;
  do{
   if(*at>=length)return 0;
   extra=link_delta[(*at)++];count+=extra;
   if(count>sizeof link_snapshot)return 0;
  }while(extra==255);
 }
 *out=count;return 1;
}
static int link_decode_delta(unsigned length){
 u8*target=(u8*)&link_snapshot;unsigned at=0,out=0;
 if(!length||length>sizeof link_delta)return 0;
 while(at<length){
  unsigned token=link_delta[at++],skip,count;
  if(!link_delta_count(&at,length,token>>4,&skip)||!link_delta_count(&at,length,token&15,&count))return 0;
  if((!skip&&!count)||skip>sizeof link_snapshot-out)return 0;
  out+=skip;
  if(count>sizeof link_snapshot-out||count>length-at)return 0;
  for(unsigned i=0;i<count;i++)target[out++]^=link_delta[at++];
 }
 return out==sizeof link_snapshot;
}
/* End snapshot byte codec. */
static char link_message1[96],link_message2[96];
static void link_copy(volatile void*d,const volatile void*s,unsigned n){volatile u8*a=d;const volatile u8*b=s;while(n--)*a++=*b++;}
static void link_text(char*d,const char*s,unsigned cap){unsigned i=0;while(s&&s[i]&&i+1<cap){d[i]=s[i];i++;}d[i]=0;}
/* FNV-1a over the whole snapshot: an end-to-end check beside the block CRC. */
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
static int link_navigation_only(u32 event_key){
 if(!link_event_valid||event_key==link_event_key||game.mode!=link_snapshot.game.mode)return 0;
 if(game.mode!=TURN&&game.mode!=LETTER&&game.mode!=SOLVE&&game.mode!=PLUS)return 0;
 if(game.cursor<0||game.cursor>31||game.choice<0||game.choice>1)return 0;
 /* Compare with the previous publication after undoing only navigation.
  * Scores, answer text, turn changes and presentation events use snapshots. */
 int cursor=game.cursor,choice=game.choice;
 game.cursor=link_snapshot.game.cursor;game.choice=link_snapshot.game.choice;
 u32 previous=link_semantic_key();game.cursor=cursor;game.choice=choice;
 return previous==link_event_key;
}
static u16 link_request_word(void){
 /* Requests share one logical word: fresh session, changed event, create,
  * configured lobby, lobby/game, resync and the input owner. */
 int lobby=game.mode==MP_LOBBY;
 u32 event_key=link_is_host()?link_semantic_key():0;
 int event=!link_event_valid||event_key!=link_event_key||(lobby&&link_lobby_changed());
 unsigned owner=human(game.player)?(game.player+1)%3:(mp.local+1)%3;
 return (link_resync?128:0)|(owner<<5)|0xa700|(!link_session?1:0)|(event?2:0)|(link_create?4:0)|(link_setup_ready?8:0)|(lobby?16:0);
}
static void link_prepare_request(void){
 u16 request=link_request_word();
 u16 ime=REG16(0x04000208);REG16(0x04000208)=0;
 if(!link_request_ready&&!link_control_ready&&(!link_armed||(link_arm_kind==LINK_REQUEST&&link_rx_state==LINK_RX_IDLE&&!link_pending_commit))){
  /* Keep an input event already armed; otherwise take the next one. */
  if(!link_armed||!(link_tx[1]&0xfc00)){link_sample_input();link_tx[1]=link_submit;}
  link_tx[0]=request;
  link_tx_crc=link_crc16(link_crc16(0xffff,link_tx[0]),link_tx[1]);
  link_arm_kind=LINK_REQUEST;link_arm_n=2;link_arm_need=0;link_armed=1;
  if(link_rx_state==LINK_RX_IDLE)link_idle_reply();
 }
 REG16(0x04000208)=ime;
}
static int link_due(void){
 if(!link_session)return 1;
 /* Guests no longer wait inside every packet; notice B here as well. */
 if(link_cancel_requested())return 1;
 if(link_master)return (game.mode==MP_LOBBY&&link_lobby_changed())||(link_is_host()&&(!link_event_valid||link_semantic_key()!=link_event_key))||video_ticks-link_last_packet>=2;
 /* The REQUEST block is armed ahead of the parent and answered by IRQ while
  * this console renders; the packet continues once it has committed. */
 link_prepare_request();
 return link_control_ready||video_ticks-link_last_packet>=(game.mode==MP_LOBBY?30u:120u);
}
/* CRC-16/CCITT over 16-bit words, MSB first. */
static unsigned link_crc16(unsigned crc,unsigned word){
 crc^=word;
 for(unsigned bit=0;bit<16;bit++)crc=crc&0x8000?((crc<<1)^0x1021)&0xffff:(crc<<1)&0xffff;
 return crc;
}
static void link_commit(void){
 unsigned kind=link_arm_kind;
 link_pending_commit=0;link_present=link_rx_present;
 link_armed=0;link_done++;
 if(kind==LINK_REQUEST){
  link_request_ready=1;
  link_tx[0]=link_tx[1]=0;link_tx_crc=link_crc16(link_crc16(0xffff,0),0);
  link_arm_kind=LINK_CONTROL;link_arm_n=2;link_arm_need=0;link_armed=1;
 }else if(kind==LINK_CONTROL){
  link_control[0]=link_rx[0][0];link_control[1]=link_rx[0][1];link_control_ready=1;
 }
}
static void link_idle_reply(void){REG16(0x0400012a)=link_armed?LINK_READY|(link_arm_kind<<6)|(link_arm_n-1):LINK_IDLE;}
static void link_child_irq(u16 word,int error){
 unsigned state=link_rx_state;
 if(state==LINK_RX_DATA){
  unsigned pos=link_rx_pos;
  link_rx[0][pos]=word;link_rx_crc=link_crc16(link_rx_crc,word);if(error)link_rx_good=0;
  for(unsigned slot=1,need=link_arm_need;need;slot++)if(need&(1u<<slot)){
   need&=~(1u<<slot);u16 peer=link_received[slot];
   link_rx[slot][pos]=peer;link_rx_peer_crc[slot]=link_crc16(link_rx_peer_crc[slot],peer);
  }
  link_rx_pos=++pos;
  REG16(0x0400012a)=pos<link_rx_n?link_tx[pos]:link_tx_crc;
  if(pos==link_rx_n)link_rx_state=LINK_RX_CRC;
  return;
 }
 if(state==LINK_RX_CRC){
  if(error||word!=link_rx_crc)link_rx_good=0;
  for(unsigned slot=1;slot<4;slot++)if((link_arm_need&(1u<<slot))&&link_received[slot]!=link_rx_peer_crc[slot])link_rx_good=0;
  REG16(0x0400012a)=(link_rx_good?LINK_OK:LINK_BAD)|link_rx_attempt<<2|link_rx_seq;
  link_rx_state=LINK_RX_ASK;return;
 }
 if(state==LINK_RX_ASK){
  /* Every member answers ASK with a verdict, never 0xffff: an exact roster. */
  unsigned present=0;for(int i=1;i<4;i++)if(link_received[i]!=0xffff)present|=1u<<i;
  link_rx_present=present;
  REG16(0x0400012a)=LINK_IDLE;
  link_pending_commit=link_rx_good&&!error;link_pending_seq=link_rx_seq;
  link_rx_state=LINK_RX_COMMIT;return;
 }
 if(state==LINK_RX_COMMIT){
  link_rx_state=LINK_RX_IDLE;
  if(!error&&word==(LINK_COMMIT|link_pending_seq)){if(link_pending_commit)link_commit();link_idle_reply();return;}
  if(!error&&word==(LINK_RETRY|link_pending_seq)){link_pending_commit=0;link_idle_reply();return;}
  /* Missed COMMIT/RETRY: keep the verdict and examine this word as idle. */
 }
 if(error)return;
 /* A parent re-entering from the role menu starts a fresh transport. */
 if(word==0xc091&&link_session&&game.mode==MP_LOBBY){link_restart=1;REG16(0x0400012a)=0xc092;return;}
 if(link_restart)return;
 if(link_pending_commit&&word==(LINK_COMMIT|link_pending_seq)){link_commit();link_idle_reply();return;}
 if(link_pending_commit&&word==(LINK_RETRY|link_pending_seq)){link_pending_commit=0;link_idle_reply();return;}
 if((word&0xf000)!=LINK_HEADER){link_idle_reply();return;}
 unsigned seq=(word>>10)&3,kind=(word>>6)&7,n=(word&63)+1;
 if(link_pending_commit){
  /* A newer block while ours awaits COMMIT: wait for the repeated COMMIT.
   * The same sequence number means the parent is retrying ours. */
  if(seq!=link_pending_seq){link_idle_reply();return;}
  link_pending_commit=0;
 }
 if(!link_armed||kind!=link_arm_kind||n!=link_arm_n){link_idle_reply();return;}
 link_rx_seq=seq;link_rx_attempt=(word>>9)&1;link_rx_n=n;link_rx_pos=0;link_rx_crc=0xffff;link_rx_good=1;link_rx_state=LINK_RX_DATA;
 for(int slot=1;slot<4;slot++)link_rx_peer_crc[slot]=0xffff;
 REG16(0x0400012a)=link_tx[0];
}
/* Parent block engine. The serial IRQ handles each completion and the HBlank
 * IRQ starts the next transfer once the turnaround has passed, so the main
 * loop keeps running while a block crosses the cable. */
enum{LINK_M_IDLE,LINK_M_PROBE,LINK_M_HEADER,LINK_M_DATA,LINK_M_CRC,LINK_M_ASK,LINK_M_DECIDE,LINK_M_DONE,LINK_M_FAILED};
static volatile unsigned link_m_state,link_m_kind,link_m_n,link_m_k,link_m_seq,link_m_attempt,link_m_polls,link_m_wait,link_m_ok,link_m_want,link_m_present;
static volatile u16 link_m_next,link_m_crc,link_m_slot_crc[4],link_m_crcs[4];
static volatile u32 link_m_sent_at;
static void link_m_send(u16 word){link_m_next=word;link_m_want=1;}
static void link_m_stop(void){
 u16 ime=REG16(0x04000208);REG16(0x04000208)=0;
 link_m_state=LINK_M_IDLE;link_m_want=0;REG16(0x04000004)&=~16;
 REG16(0x04000208)=ime;
}
static void link_hblank(void){
 if(!link_m_want||link_master!=1)return;
 if(link_m_wait){link_m_wait--;return;}
 if(input_clock()-link_completed_at<link_gap)return;
 u16 control=REG16(0x04000128);if((control&0x88)!=8)return; /* Busy, or a child not ready. */
 link_wire_word=link_m_next;REG16(0x0400012a)=link_m_next;
 link_m_want=0;link_m_sent_at=input_clock();REG16(0x04000128)=control|128;
}
static void link_parent_irq(int error){
 volatile u16*slot=link_received;unsigned state=link_m_state;
 if(error){link_wire_bad=1;if(link_errors>=LINK_ERROR_LIMIT){link_m_state=LINK_M_FAILED;return;}}
 if(state==LINK_M_PROBE){
  /* Probe until every member has armed this block. */
  unsigned present=0,armed=1;u16 ready=LINK_READY|(link_m_kind<<6)|(link_m_n-1);
  for(int i=1;i<4;i++)if(slot[i]!=0xffff){present|=1u<<i;if(slot[i]!=ready&&(link_m_kind==LINK_REQUEST||(link_members&(1u<<i))))armed=0;}
  if(link_m_kind!=LINK_REQUEST&&(link_members&~present)){link_m_state=LINK_M_FAILED;return;} /* A member left. */
  if(!armed){
   /* Back off to 65536 cycles: a child whose serial IRQ is delayed must get
    * a completion outside BUSY, or it would never see a probe at all. */
   if(++link_m_polls>4){unsigned shift=link_m_polls<8?link_m_polls-4:4;link_m_wait=(4096u<<shift)/1232;}
   link_m_send(link_last_commit);return;
  }
  link_wire_bad=0;link_m_present=present;link_m_state=LINK_M_HEADER;
  link_m_send(LINK_HEADER|(link_m_seq<<10)|(link_m_attempt<<9)|(link_m_kind<<6)|(link_m_n-1));return;
 }
 if(state==LINK_M_HEADER){
  link_m_k=0;link_m_crc=0xffff;for(int i=1;i<4;i++)link_m_slot_crc[i]=0xffff;
  link_m_state=LINK_M_DATA;link_m_send(link_tx[0]);return;
 }
 if(state==LINK_M_DATA){
  unsigned k=link_m_k;u16 word=link_tx[k];
  link_rx[0][k]=word;link_m_crc=link_crc16(link_m_crc,word);
  for(int i=1;i<4;i++){link_rx[i][k]=slot[i];if(link_m_present&(1u<<i))link_m_slot_crc[i]=link_crc16(link_m_slot_crc[i],slot[i]);}
  link_m_k=++k;
  if(k<link_m_n)link_m_send(link_tx[k]);else{link_m_state=LINK_M_CRC;link_m_send(link_m_crc);}
  return;
 }
 if(state==LINK_M_CRC){
  for(int i=0;i<4;i++)link_m_crcs[i]=slot[i];
  link_m_state=LINK_M_ASK;link_m_send(LINK_ASK|link_m_seq);return;
 }
 if(state==LINK_M_ASK){
  unsigned present=0;for(int i=1;i<4;i++)if(slot[i]!=0xffff)present|=1u<<i;
  if(link_m_kind==LINK_REQUEST)link_members=present;
  else if(link_members&~present){link_m_state=LINK_M_FAILED;return;}
  int ok=!link_wire_bad;
  for(int i=1;i<4;i++)if(link_members&(1u<<i)){
   if(slot[i]!=(LINK_OK|link_m_attempt<<2|link_m_seq)||!(link_m_present&(1u<<i))||link_m_slot_crc[i]!=link_m_crcs[i])ok=0;
  }
  link_m_ok=ok;link_m_state=LINK_M_DECIDE;
  link_m_send((ok?LINK_COMMIT:LINK_RETRY)|link_m_seq);return;
 }
 if(state==LINK_M_DECIDE){
  if(link_m_ok){
   link_sequence++;link_last_commit=LINK_COMMIT|link_m_seq;if(link_gap>4096)link_gap>>=1;
   link_m_state=LINK_M_DONE;REG16(0x04000004)&=~16;return;
  }
  link_retries++;link_m_attempt^=1;if(link_gap<0x20000)link_gap<<=1;
  link_m_state=LINK_M_PROBE;link_m_send(link_last_commit);
 }
}
static void link_irq(void){
 u16 status=REG16(0x04000128);
 /* A delayed IRQ may belong to a transfer preceding the one now in flight.
  * Receive registers are partial and ERROR is undefined while BUSY. */
 if(status&128)return;
 link_status=status;
 for(int i=0;i<4;i++)link_received[i]=REG16(0x04000120+i*2);
 if(game.mode==LINK_TEST){link_test_irq();link_serial++;return;}
 if(link_master==0&&link_received[0]!=0xffff)link_started=1;
 if(link_master==1)for(int i=1;i<4;i++)if(link_received[i]!=0xffff)link_started=1;
 int error=(link_status&64)!=0;
 if(error){if(++link_errors>=LINK_ERROR_LIMIT)link_fault=1;}else link_errors=0;
 if(link_master==0){link_wire_word=link_received[0];if(!link_fault)link_child_irq(link_received[0],error);}
 if(link_master==1&&link_m_state>=LINK_M_PROBE&&link_m_state<LINK_M_DONE)link_parent_irq(error);
 link_completed_at=input_clock();link_serial++;
}
static void link_transport_reset(void){
 u16 ime=REG16(0x04000208);REG16(0x04000208)=0;
 link_armed=link_rx_state=link_pending_commit=link_request_ready=link_control_ready=0;
 link_done=link_fault=link_errors=link_sequence=link_members=0;link_restart=0;link_last_commit=LINK_IDLE;link_gap=4096;
 link_m_state=LINK_M_IDLE;link_m_want=0;REG16(0x04000004)&=~16;link_in_packet=0;
 REG16(0x04000208)=ime;
}
static void link_close(void){link_m_state=LINK_M_IDLE;link_m_want=0;REG16(0x04000004)&=~16;REG16(0x04000200)&=~2;link_in_packet=0;if(link_active&&!link_is_host()){link_copy(record_names,link_saved_names,sizeof record_names);link_copy(record_scores,link_saved_scores,sizeof record_scores);}REG16(0x04000200)&=~128;REG16(0x04000128)=0;REG16(0x04000134)=0x8000;link_active=0;}
static void link_open(void){
 link_back_mode=game.mode==MP_CONNECT?MP_CONNECT:MP_SETUP;
 link_host_device=-1;link_host_ready=0;link_setup_ready=1;link_profile_pending=link_config_mode=link_choose_armed=0;
 link_join_prompt=0;
 link_preview_valid=0;
 link_profile_render_key=~0u;
 link_profile_cursor=-1;link_keyboard_valid=0;
 link_last_packet=video_ticks;link_event_valid=0;link_tap_read=link_tap_write=0;link_remote_read=link_remote_write=0;link_remote_player=-1;link_repeat=(DirectionRepeat){0};link_packets=link_events=0;
 link_clock_offset=0;link_resync=0;
 link_session=0;for(int i=0;i<11;i++)link_sent_name[i]=0;
 link_sent_status=~0u;
 link_avatar_edit=!link_create;link_avatar_armed=0;
 link_connected=1;link_start_armed=link_cancelled=link_name_edit=link_name_wait=0;link_name_cursor=game.cursor;
 link_copy(link_saved_names,record_names,sizeof record_names);link_copy(link_saved_scores,record_scores,sizeof record_scores);
 link_text(link_name,mp.names[2],11);link_avatar=avatars[2];link_submit=0;
 for(unsigned i=0;i<sizeof link_previous/2;i++)link_previous[i]=0;
 for(unsigned i=0;i<sizeof link_snapshot;i++)((u8*)&link_snapshot)[i]=0;
 link_transport_reset();link_retries=0;
 link_master=-1;link_started=link_stage=link_error_stage=0;link_status=link_error_status=0;
 link_restart=0;
 link_error_received=link_error_expected=0;
 link_boot_serial=link_serial;
 REG16(0x0400012a)=0;
 REG16(0x04000134)=0;REG16(0x04000128)=0x6003;
 REG16(0x04000202)=130;REG16(0x04000200)|=130;link_active=1;link_keys_fresh=0;
}
/* Discover while the creator edits rules. Only start a hardware transfer
 * when the bus is ready; absent peers must leave the settings responsive. */
static int link_probe(void){
 if(link_serial!=link_boot_serial){
  if((link_status>>4)&3)return 1;
  /* A completion from the previous connection may arrive after reopen.
   * The parent must send its new bootstrap before starting phase zero. */
  if(link_received[0]==0xc091)for(int i=1;i<4;i++)if(link_received[i]!=0xffff)return 1;
 }
 if((REG16(0x04000128)&0x88)==8){
  REG16(0x0400012a)=0xc091;REG16(0x04000128)|=128;
 }
 return 0;
}
/* Poll local input inside the SIO waits too: an absent peer must not trap
 * either console in the lobby until the cable timeout expires. */
static int link_cancel_requested(void){
 if(game.mode==MP_LOBBY&&!link_name_edit&&link_config_mode!=MP_OPTION_HELP&&(!link_host_ready||!(link_snapshot.name_conflicts&(1<<mp.local)))&&(input_keys&B))link_cancelled=1;
 return link_cancelled;
}
static int link_timed_out(u32 start){
 /* Once a lobby has synchronized, inactivity means a departing peer, not
  * someone still booting. Measure silence rather than total packet time so
  * large initial/recovery snapshots keep their existing progress budget. */
 u32 last_completion=link_completed_at;
 if(game.mode==MP_LOBBY&&link_session&&input_clock()-last_completion>16777216u)return 1;
 /* A player may still be booting the other cartridge or entering a name.
  * Keep waiting until a peer transmits; malformed handshakes still time out. */
 if(game.mode==MP_LOBBY&&!link_started)return 0;
 return input_clock()-start>(game.mode==MP_LOBBY?503316480u:33554432u);
}
/* Start exchanging link_tx[0..n-1]; link_block_poll() reports completion.
 * The parent receives every member's words in link_rx[slot] (its own in slot
 * 0); a child receives the parent's words in link_rx[0] and the slots in
 * need. The REQUEST block also fixes this packet's member slots. */
static struct {unsigned kind,done;int control;u32 start;} link_wait;
static int link_block_begin(unsigned kind,unsigned n,unsigned need){
 if(!n||n>LINK_BLOCK_MAX)return 0;
 link_wait.kind=kind;link_wait.start=input_clock();link_wait.control=0;
 unsigned crc=0xffff;
 if(!link_master)for(unsigned k=0;k<n;k++)crc=link_crc16(crc,link_tx[k]);
 u16 ime=REG16(0x04000208);REG16(0x04000208)=0;
 if(!link_master){
  /* A prepared REQUEST may have committed just now: the parent has moved on.
   * CONTROL is armed by the IRQ after REQUEST: never re-arm it. These checks
   * share the interrupt-free section that arms the block; the IRQ only
   * rewrites link_tx when it arms CONTROL after a committed REQUEST. */
  if(kind==LINK_REQUEST&&link_request_ready){link_wait.done=link_done-1;REG16(0x04000208)=ime;return 1;}
  if(kind==LINK_CONTROL&&(link_control_ready||(link_armed&&link_arm_kind==LINK_CONTROL))){link_wait.control=1;REG16(0x04000208)=ime;return 1;}
  link_arm_kind=kind;link_arm_n=n;link_arm_need=need;link_tx_crc=crc;link_wait.done=link_done;link_armed=1;
  if(link_rx_state==LINK_RX_IDLE)link_idle_reply();
  REG16(0x04000208)=ime;
  return 1;
 }
 link_m_kind=kind;link_m_n=n;link_m_seq=link_sequence&3;link_m_attempt=link_m_polls=link_m_wait=0;
 link_m_state=LINK_M_PROBE;link_m_send(link_last_commit);link_m_sent_at=input_clock();
 REG16(0x04000004)|=16;
 REG16(0x04000208)=ime;
 return 1;
}
/* 1: committed, 2: still crossing the cable, 0: failed or cancelled. */
static int link_block_poll(void){
 if(!link_master){
  if(link_wait.control){
   if(!link_control_ready){
    if(link_restart||link_fault||link_cancel_requested()||link_timed_out(link_wait.start))return 0;
    return 2;
   }
   link_control_ready=0;link_rx[0][0]=link_control[0];link_rx[0][1]=link_control[1];
  }else{
   if(link_done==link_wait.done){
    if(link_restart||link_fault||link_cancel_requested()||link_timed_out(link_wait.start)){
     u16 ime=REG16(0x04000208);REG16(0x04000208)=0;link_armed=0;REG16(0x04000208)=ime;return 0;
    }
    return 2;
   }
   if(link_restart)return 0;
   if(link_wait.kind==LINK_REQUEST)link_request_ready=0;
   if(link_wait.kind==LINK_CONTROL){link_control_ready=0;link_rx[0][0]=link_control[0];link_rx[0][1]=link_control[1];}
  }
  mp.local=((link_status>>4&3)+2)%3;
  return 1;
 }
 unsigned state=link_m_state;
 if(state==LINK_M_DONE){link_m_state=LINK_M_IDLE;mp.local=((link_status>>4&3)+2)%3;return 1;}
 if(state==LINK_M_FAILED){link_m_stop();return 0;}
 if(!link_started)link_wait.start=input_clock();
 /* Once a transfer was started, its completion must arrive. */
 u32 deadline=game.mode==MP_LOBBY?503316480u:33554432u;
 /* HBlank can start the next transfer during input_clock(). Read its
  * timestamp first: subtracting a newer IRQ timestamp from the earlier
  * clock sample wraps to almost 2^32 and disconnects a healthy cable. */
 u32 sent_at=link_m_sent_at;
 if(link_cancel_requested()||link_timed_out(link_wait.start)||
    (!link_m_want&&input_clock()-sent_at>deadline&&sent_at==link_m_sent_at)){link_m_stop();return 0;}
 return 2;
}
/* Authority words in link_pub reach every console's link_pub in one block:
 * the parent collects a child host's slot, and the third console reads that
 * slot itself. */
static u16 link_pub[LINK_BLOCK_MAX];
static unsigned link_publish_begin(unsigned n){
 int authority=link_is_host();
 for(unsigned k=0;k<n;k++)link_tx[k]=authority?link_pub[k]:0;
 unsigned need=!link_master&&!authority&&link_host_device>0?1u<<link_host_device:0;
 return link_block_begin(LINK_PUBLISH,n,need);
}
static void link_publish_end(unsigned n){
 if(link_is_host())return;
 unsigned from=link_host_device>0?(unsigned)link_host_device:0;
 for(unsigned k=0;k<n;k++)link_pub[k]=link_rx[from][k];
}
/* Every console contributes link_tx[0..n-1]; the parent and the elected host
 * end with all of them in link_collected[slot]. A host on a child port reads
 * the other child's slot itself. */
static u16 link_collected[3][LINK_BLOCK_MAX],link_own[LINK_BLOCK_MAX];
static unsigned link_collect_need;
static int link_collect_begin(unsigned kind,unsigned n){
 for(unsigned k=0;k<n;k++)link_own[k]=link_tx[k];
 unsigned self=(mp.local+1)%3;
 link_collect_need=!link_master&&link_is_host()&&link_connected==3?1u<<(3-self):0;
 return link_block_begin(kind,n,link_collect_need);
}
static void link_collect_end(unsigned n){
 unsigned self=(mp.local+1)%3;
 for(int i=0;i<link_connected;i++)for(unsigned k=0;k<n;k++)
  link_collected[i][k]=link_master||i==0||(link_collect_need&(1u<<i))?link_rx[i][k]:i==(int)self?link_own[k]:0;
}
static u32 link_hash(const void*data,unsigned n){const u8*p=data;u32 h=2166136261u;while(n--)h=(h^*p++)*16777619u;return h;}
/* A packet is a coroutine: each call advances it as far as the blocks on the
 * cable allow and returns 2 while a block is still crossing, so the main loop
 * keeps updating and drawing. Its state lives in link_step. */
static struct {
 int pt,full,lobby,input_device,expected,was_ready,event,authority,navigation;
 u16 control;unsigned length,at,n;u32 event_key,start,event_at;
 int hold; /* An in-game event: deliver without yielding (see link_service). */
} link_step;
#define LINK_AWAIT(begin) do{if(!(begin))return 0;link_step.pt=__LINE__;case __LINE__:;{int r_=link_block_poll();if(r_==2)return 2;if(!r_)return 0;}}while(0)
static int link_packet(void){
 u16 value;u16*words=(u16*)&link_snapshot;
 switch(link_step.pt){
 case 0:
 if(link_master<0){
  link_stage=1;
  /* Bootstrap with one hardware transfer, then use the assigned ID, not
   * a cached SI pin level. START is read-only on children, so requesting
   * it on every console starts exactly one transfer, on the parent. A
   * late main loop may already have received it in IRQ while rendering. */
  /* Waiting for the other consoles yields to the game, like every block. */
  link_step.pt=__LINE__;case __LINE__:;
  if(link_serial==link_boot_serial){
   if(link_cancel_requested())return 0;
   if((REG16(0x04000128)&0x88)!=8)return 2;
   REG16(0x0400012a)=0xc091;REG16(0x04000128)|=128;
  }
  link_step.start=input_clock();
  link_step.pt=__LINE__;case __LINE__:;
  if(link_serial==link_boot_serial){
   if(link_cancel_requested()||input_clock()-link_step.start>503316480u)return 0;
   return 2;
  }
  if(link_status&64)return 0;
  unsigned id=(link_status>>4)&3;if(id>=3)return 0;
  link_master=id==0;mp.local=(id+2)%3;
  link_started=id!=0;
  if(!id)for(int i=1;i<4;i++)if(link_received[i]!=0xffff)link_started=1;
 }
 link_step.full=!link_session;link_step.lobby=game.mode==MP_LOBBY;
 link_step.input_device=0;link_step.expected=mp.humans;link_step.event=0;link_step.was_ready=link_host_ready;
 link_stage=2;
 /* REQUEST: every console's request word and input event. */
 if(link_master){
  link_step.start=input_clock();
  for(;;){
   link_tx[0]=link_request_word();link_sample_input();link_tx[1]=link_submit;
   LINK_AWAIT(link_block_begin(LINK_REQUEST,2,0));
   if(!link_started)link_step.start=input_clock();
   {
    int connected=1;
    for(int i=1;i<4;i++)if(link_members&(1u<<i)){
     if(i!=connected||i==3)return 0;
     connected++;
     if((link_rx[i][0]&0xff00)!=0xa700)return link_mismatch(link_rx[i][0],0xa710);
     if(link_rx[i][0]&1)link_step.full=1;
    }
    if(!link_step.lobby&&(connected!=mp.humans||link_step.full))return 0;
    if(connected>=2){
     if(link_connected!=connected)link_step.full=1;
     link_connected=connected;mp.humans=connected;
     if(link_host_device<0){
      /* An already opened lobby beats a new creator still editing rules,
       * including when the existing host occupies a child cable port.
       * Requests in the same exchange tie deterministically by port. */
      for(int ready_host=1;ready_host>=0&&link_host_device<0;ready_host--)
       for(int i=0;i<connected;i++)if((link_rx[i][0]&4)&&(!ready_host||(link_rx[i][0]&8))){link_host_device=i;break;}
     }
     if(link_host_device>=connected)return 0;
     if(link_host_device>=0){
      unsigned host_request=link_rx[link_host_device][0];
      link_step.lobby=(host_request&16)!=0;link_host_ready=(host_request&8)!=0;
      if(!link_step.lobby&&(link_step.full||connected!=link_step.expected))return 0;
      link_step.input_device=link_step.lobby?link_host_device:(host_request>>5)&3;
      if(link_step.input_device>=connected)return 0;
      link_step.event=link_step.full||(host_request&2);
      if(link_step.lobby){
       if(link_host_ready!=link_step.was_ready)link_step.event=1;
       for(int i=0;i<connected;i++)if(link_rx[i][0]&2)link_step.event=1;
      }
     }else{link_step.lobby=1;link_host_ready=0;link_step.event=0;}
     for(int i=0;i<connected;i++)if(link_rx[i][0]&128){link_step.full=1;link_step.event=1;}
     break;
    }
   }
   if(link_timed_out(link_step.start))return 0;
   /* Alone in the lobby: let the game draw between requests. */
   link_step.pt=__LINE__;return 2;case __LINE__:;
  }
  link_keys=link_rx[link_step.input_device][1];
  if(link_is_host())link_keys_fresh=1;
  /* CONTROL: decisions and the owner's input, which only the host consumes. */
  {
   unsigned host=link_host_device<0?3:link_host_device;
   link_tx[0]=0xb170|(link_step.full?2:0)|(link_step.lobby?4:0)|(!link_step.event?1:0)|(host<<9)|(link_host_ready?128:0);
   link_tx[1]=link_keys;
  }
  LINK_AWAIT(link_block_begin(LINK_CONTROL,2,0));
 }else{
  /* REQUEST is armed ahead (link_prepare_request) and answered by IRQ. */
  link_prepare_request();
  LINK_AWAIT(link_block_begin(LINK_REQUEST,2,0));
  LINK_AWAIT(link_block_begin(LINK_CONTROL,2,0));
  {
   u16 control=link_rx[0][0];
   if((control&0xf970)!=0xb170)return link_mismatch(control,0xb176);
   link_step.event=!(control&1);link_step.full=(control&2)!=0;link_step.lobby=(control&4)!=0;
   unsigned host=(control>>9)&3;link_host_device=host==3?-1:(int)host;
   link_host_ready=(control&128)!=0;
   if(!link_session&&!link_step.full)return link_mismatch(control,0xb176);
   link_connected=1;for(int i=1;i<4;i++)if(link_present&(1u<<i))link_connected++;
   if(link_connected>3||link_host_device>=link_connected)return 0;
   mp.humans=link_connected;
   if(link_is_host()){link_keys=link_rx[0][1];link_keys_fresh=1;}
  }
 }
 link_step.authority=link_is_host();link_step.navigation=0;
 if(link_step.full){
  link_stage=3;
  link_tx[0]=MULTIPLAYER_BUILD&65535;link_tx[1]=MULTIPLAYER_BUILD>>16;
  LINK_AWAIT(link_block_begin(LINK_BUILD,2,0));
  for(int i=0;i<(link_master?link_connected:1);i++)for(int k=0;k<2;k++)
   if(link_rx[i][k]!=link_tx[k])return link_mismatch(link_rx[i][k],link_tx[k]);
  link_session=1;
  /* A joining lobby participant needs a complete base, not deltas against
   * a snapshot it has never received. Existing peers reset that base too. */
  if(link_step.authority)for(unsigned i=0;i<sizeof link_previous/2;i++)link_previous[i]=0;
  else for(unsigned i=0;i<sizeof link_snapshot;i++)((u8*)&link_snapshot)[i]=0;
 }
 link_packets++;link_last_packet=video_ticks;
 if(!link_step.event)return 1; /* Input/keepalive: no poses, text or snapshot hash. */
 link_events++;
 link_step.event_at=video_ticks;link_step.hold=!link_step.lobby;
 if(link_step.lobby){
  /* LOBBY: avatar/edit flags and the name from every console in one block. */
  link_stage=5;
  link_tx[0]=link_lobby_status();
  for(int j=0;j<6;j++){u16 pair=(u8)link_name[j*2];if(j<5)pair|=(u16)(u8)link_name[j*2+1]<<8;link_tx[1+j]=pair;}
  LINK_AWAIT(link_collect_begin(LINK_LOBBY,7));
  link_collect_end(7);
  link_sent_status=link_lobby_status();link_copy(link_sent_name,link_name,sizeof link_sent_name);
  if(link_step.authority){
   link_snapshot.name_editing=link_snapshot.avatar_editing=0;
   for(int i=0;i<mp.humans;i++){
    unsigned state=link_collected[i][0],avatar=state&15,p=(i+2)%3;
    if((state&~63u)||avatar>(prefs.characters?8u:6u))return 0;
    avatars[p]=avatar;
    if(state&16)link_snapshot.name_editing|=1<<p;
    if(state&32)link_snapshot.avatar_editing|=1<<p;
    for(int j=0;j<6;j++){link_incoming_names[p][j*2]=link_collected[i][1+j]&255;if(j<5)link_incoming_names[p][j*2+1]=link_collected[i][1+j]>>8;}
   }
   link_snapshot.name_conflicts=link_name_conflicts(link_incoming_names);
  }
 }
 /* The authority takes its snapshot now: the game may advance while the
  * rest of the packet crosses, and later changes become the next event. */
 link_step.control=0;
 if(link_step.authority){
  link_step.event_key=link_semantic_key();
  if(!link_step.lobby&&!link_step.full&&link_navigation_only(link_step.event_key))
   link_step.control=0x8000|(game.cursor&31)|((game.choice&1)<<5)|(game.mode<<6)|(game.player<<12);
 }
 if(link_step.authority&&!link_step.control){
  link_snapshot.match=match;link_snapshot.rule=prefs.rule;link_snapshot.rounds=prefs.rounds;
  link_snapshot.humans=mp.humans;
  link_copy(&link_snapshot.cash,&cash,sizeof cash);link_snapshot.cash_seed=cash_initial_seed;
  link_snapshot.sound=sound_command;link_snapshot.dictionary=prefs.dictionary;link_snapshot.plus=prefs.plus;link_snapshot.characters=prefs.characters;link_snapshot.ai_index=mp_ai_index;link_copy(link_snapshot.pool,opponent_pool,sizeof opponent_pool);
  link_copy(link_snapshot.records,record_names,sizeof record_names);link_copy(link_snapshot.scores,record_scores,sizeof record_scores);
  link_copy(&link_snapshot.game,&game,sizeof game);link_copy(&link_snapshot.scene,&scene,sizeof scene);link_snapshot.scene.now=link_step.event_at;
  /* Per-iteration counters the guests never read; keep them out of deltas. */
  link_snapshot.game.frame=0;link_snapshot.scene.last_redraw=0;
  /* Exclude accumulated packet pauses from the wire timeline. Otherwise
   * every pause changes all deadlines again in the following snapshot. */
  link_rebase_state(&link_snapshot.scene,&link_snapshot.cash,0u-link_clock_offset);
  link_copy(link_snapshot.avatars,avatars,sizeof avatars);link_copy(link_snapshot.names,mp.names,sizeof mp.names);link_snapshot.eliminated=mp.eliminated;
  link_copy(link_snapshot.durations,host_durations,sizeof host_durations);
  link_snapshot.event=presentation_event;link_copy(link_snapshot.tokens,message_tokens,sizeof message_tokens);
 }
 /* PUBLISH: navigation assignment or the byte delta's length. */
 link_stage=4;
 link_step.length=link_step.authority&&!link_step.control?link_encode_delta():0;
 link_pub[0]=link_step.control;link_pub[1]=link_step.control?0:0x8000|link_step.length;
 LINK_AWAIT(link_publish_begin(2));
 link_publish_end(2);
 value=link_pub[0];
 if(link_step.authority&&value!=link_step.control)return 0;
 if(value&&(!(value&0x8000)||(value&0x4000)||link_step.full||link_step.lobby))return 0;
 link_step.navigation=value!=0;
 if(link_step.navigation){
  if(((value>>6)&63)!=(unsigned)link_snapshot.game.mode||((value>>12)&3)!=(unsigned)link_snapshot.game.player)return 0;
  link_snapshot.game.cursor=value&31;link_snapshot.game.choice=(value>>5)&1;
  /* A committed CRC-checked assignment preserves the verified baseline:
   * every peer applies the same cursor/choice to the same snapshot. */
  goto commit_event;
 }
 if(!(link_pub[1]&0x8000))return 0;
 link_step.length=link_pub[1]&0x7fff;
 if(!link_step.length||link_step.length>sizeof link_delta)return 0;
 link_stage=6;
 for(link_step.at=0;link_step.at<link_step.length;link_step.at+=link_step.n*2){
  link_step.n=(link_step.length-link_step.at+1)/2;if(link_step.n>LINK_BLOCK_MAX)link_step.n=LINK_BLOCK_MAX;
  for(unsigned k=0;k<link_step.n;k++){unsigned i=link_step.at+k*2;link_pub[k]=link_step.authority?link_delta[i]|(i+1<link_step.length?link_delta[i+1]<<8:0):0;}
  LINK_AWAIT(link_publish_begin(link_step.n));
  link_publish_end(link_step.n);
  for(unsigned k=0;k<link_step.n;k++){
   unsigned i=link_step.at+k*2;u16 pair=link_pub[k];
   if(i+1>=link_step.length&&(pair>>8))return 0;
   if(!link_step.authority){link_delta[i]=pair&255;if(i+1<link_step.length)link_delta[i+1]=pair>>8;}
  }
 }
 if(!link_step.authority&&!link_decode_delta(link_step.length))return 0;
 link_stage=7;
 /* HASH from every console, then the parent's verdict to every console. */
 {u32 hash=link_hash(&link_snapshot,sizeof link_snapshot);link_tx[0]=hash&65535;link_tx[1]=hash>>16;}
 LINK_AWAIT(link_block_begin(LINK_HASH,2,0));
 {
  int mismatch=0;
  for(int i=0;i<(link_master?link_connected:1);i++)if(link_rx[i][0]!=link_tx[0]||link_rx[i][1]!=link_tx[1])mismatch=1;
  link_tx[0]=link_master?mismatch:0;
 }
 LINK_AWAIT(link_block_begin(LINK_VERDICT,1,0));
 value=link_rx[0][0];
 if(value>1)return 0;
 if(value){
  /* Roll back to the committed baseline and request a full snapshot. */
  link_copy(&link_snapshot,link_previous,sizeof link_snapshot);
  link_resync=1;link_event_valid=0;
  return 1;
 }
commit_event:
 link_resync=0;
 for(unsigned i=0;i<sizeof link_snapshot/2;i++)link_previous[i]=words[i];
 if(!link_step.authority&&link_step.navigation){game.cursor=link_snapshot.game.cursor;game.choice=link_snapshot.game.choice;}
 else if(!link_step.authority){
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
 if(!link_step.lobby&&!link_step.navigation){
  u32 elapsed=video_ticks-(link_step.authority?link_step.event_at:link_snapshot.scene.now);
  link_rebase(elapsed);if(link_step.authority)link_clock_offset+=elapsed;
 }
 /* The applied lobby snapshot was built from the name sent in this packet. */
 if(link_step.lobby){int same=1;for(int i=0;i<11;i++)if(link_sent_name[i]!=link_name[i])same=0;if(same)link_name_wait=0;}
 link_event_key=link_step.authority?link_step.event_key:0;link_event_valid=1;link_last_packet=video_ticks;dirty=1;
 return 1;
 }
 return 0;
}
#undef LINK_AWAIT
/* Called on every main-loop iteration: starts a due packet or advances the
 * one in progress. 0 means the session failed. */
enum{LINK_SLICE=8};
static int link_service(void){
 if(!link_in_packet){if(!link_due())return 1;link_in_packet=1;link_step.pt=0;link_step.hold=0;}
 /* Follow the packet while it crosses, but return to the game after an
  * eight-frame slice: waiting for peers, the bootstrap, keepalives and lobby
  * packets (full snapshots on joins) no longer freeze it. An in-game event
  * is delivered without yielding: its presentation clock excludes the whole
  * delivery, which is only right if the game did not run meanwhile. */
 u32 slice=video_ticks;int result;
 while((result=link_packet())==2&&(link_step.hold||video_ticks-slice<LINK_SLICE)){}
 if(result==2)return 1;
 link_in_packet=0;
 /* A guest arms the next REQUEST before returning to render, so the IRQ can
  * answer the parent's next packet without waiting for this main loop. */
 if(result&&!link_master&&link_active&&link_session)link_prepare_request();
 return result;
}
