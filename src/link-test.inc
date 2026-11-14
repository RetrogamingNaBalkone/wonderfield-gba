/* Temporary raw-SIO echo diagnostic. It deliberately bypasses link_exchange,
 * packet headers, build IDs and snapshots, so faults can be localized below
 * the game protocol. No settings or save data are changed. */
typedef struct {
 int running,role,baud,pace,peers,timed_out,inflight;
 u32 transfers,passed,errors,repeats,timeouts,completed_at;
 u16 tx,probe,prior,last,status,rx[4];
} LinkTest;
static volatile LinkTest link_test={.role=-1,.baud=3,.pace=1};
static u32 link_test_redraw,link_test_started,link_test_begin_frame,link_test_seconds;
static int link_test_details,link_test_ran;
static volatile unsigned link_test_hardware_errors,link_test_data_errors,link_test_members,link_test_changed;
static volatile u32 link_test_progress_at;
static volatile u16 link_test_completed_tx;
static u16 link_test_next(u16 value){
 do{value=(value>>1)^((value&1)?0xb400:0);}while(value==0xffff);
 return value;
}
static void link_test_stop(void){
 REG16(0x04000200)&=~128;REG16(0x04000128)=0;
 REG16(0x04000134)=0x8000;link_test.running=0;link_test.inflight=0;
}
static void link_test_enter(void){
 link_test_stop();link_test.timed_out=0;link_test_details=link_test_ran=0;set_mode(LINK_TEST);
}
static void link_test_start(void){
 link_test_stop();link_test.role=-1;link_test.peers=link_test.timed_out=0;
 link_test_ran=1;link_test_seconds=0;link_test_begin_frame=video_ticks;
 link_test_hardware_errors=link_test_data_errors=link_test_members=link_test_changed=0;
 link_test.transfers=link_test.passed=link_test.errors=link_test.repeats=link_test.timeouts=0;
 link_test.tx=link_test.probe=0xace1;link_test.prior=link_test.last=0;
 link_test_completed_tx=0;link_test.status=0;for(int i=0;i<4;i++)link_test.rx[i]=0xffff;
 link_test_progress_at=link_test.completed_at=link_test_started=input_clock();
 REG16(0x0400012a)=link_test.tx;REG16(0x04000134)=0;
 REG16(0x04000128)=0x6000|link_test.baud;REG16(0x04000202)=128;
 link_test.running=1;REG16(0x04000200)|=128;
}
static void link_test_irq(void){
 if(!link_test.running)return;
 link_test_completed_tx=link_test.tx;link_test.status=link_status;link_test.role=(link_status>>4)&3;
 link_test.transfers++;link_test.inflight=0;link_test.completed_at=input_clock();
 int present=0;unsigned members=0;int hardware=(link_status&64)!=0,bad=0;
 for(int i=0;i<4;i++){link_test.rx[i]=link_received[i];if(link_received[i]!=0xffff){present++;members|=1u<<i;}}
 if(present>1&&!link_test_members&&!hardware){
  link_test.peers=present;link_test_members=members;link_test_progress_at=link_test.completed_at;
 }
 if(link_test_members&&members!=link_test_members)link_test_changed=1;
 if(link_test.role==0){
  int ready=present>1&&members==link_test_members;
  if(link_received[0]!=link_test.tx)bad=1;
  for(int i=1;i<4;i++)if(link_received[i]!=0xffff&&link_received[i]!=link_test.probe){
   ready=0;
   if(link_received[i]!=link_test.prior&&link_received[i]!=0xace1)bad=1;
  }
  if(ready&&!bad&&!hardware){link_test_progress_at=link_test.completed_at;link_test.passed++;link_test.prior=link_test.probe;link_test.probe=link_test_next(link_test.probe);}
  else if(present>1)link_test.repeats++;
 }else{
  u16 received=link_received[0];
  if(received==0xffff)bad=1;
  else{
   if(link_test.last==received)link_test.repeats++;
   else if(!link_test.last||received==link_test_next(link_test.last)){
    if(!hardware&&members==link_test_members)link_test.passed++;
   }
   else bad=1;
   if(!bad&&!hardware&&members==link_test_members)link_test_progress_at=link_test.completed_at;
   link_test.last=received;link_test.tx=received;
   REG16(0x0400012a)=received;
  }
 }
 if(hardware)link_test_hardware_errors++;
 if(bad)link_test_data_errors++;
 if(bad||hardware)link_test.errors++;
}
static void link_test_update(u16 pressed,u16 repeat){
 if(pressed&SELECT){link_test_details^=1;dirty=1;}
 if(pressed&B){link_test_stop();mp.choice=3;set_mode(MP_SETUP);return;}
 if(pressed&A){if(link_test.running)link_test_stop();else link_test_start();dirty=1;return;}
 if(!link_test.running){
  if(pressed&L){link_test.baud=(link_test.baud+3)%4;dirty=1;}
  if(pressed&R){link_test.baud=(link_test.baud+1)%4;dirty=1;}
  if(repeat&UP){link_test.pace=(link_test.pace+3)%4;dirty=1;}
  if(repeat&DOWN){link_test.pace=(link_test.pace+1)%4;dirty=1;}
  return;
 }
 link_test_seconds=(video_ticks-link_test_begin_frame)/60;
 /* Snapshot and act on IRQ-owned state atomically. Otherwise the first
  * completion after a long initial wait can set peers between reading the
  * old timestamp and testing peers, causing a false immediate timeout. */
 u16 ime=REG16(0x04000208);REG16(0x04000208)=0;
 u32 now=input_clock(),age=now-link_test.completed_at;
 if((link_test.inflight&&now-link_test_started>16777216u)||
    (link_test.peers&&now-link_test_progress_at>33554432u)){
  link_test.timeouts++;link_test.timed_out=1;link_test_stop();dirty=1;
 }else{
  static const u32 pauses[]={4096,16778,67109,268435};
  if(link_test.role<=0&&!link_test.inflight&&age>=pauses[link_test.pace]&&
     (REG16(0x04000128)&0x88)==8){
   /* Before the first assigned ID, all units may request START; it is
    * read-only on children. Keep this request atomic with role detection. */
   link_test.tx=link_test.probe;REG16(0x0400012a)=link_test.tx;
   link_test_started=now;link_test.inflight=1;REG16(0x04000128)|=128;
   if(link_test.role<0&&!(REG16(0x04000128)&128))link_test.inflight=0;
  }
 }
 REG16(0x04000208)=ime;
}
