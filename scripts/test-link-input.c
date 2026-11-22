/* Host-side model of cable input: production event functions from link.inc,
 * owner VBlank capture, packet sampling and authority application. Compares
 * the number of cursor moves and A presses with local play's own logic. */
#include <stdio.h>
#include <stdlib.h>
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;
static u16 io[0x300];
#define REG16(a) (io[((a)-0x04000000)/2])
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
static volatile u32 video_ticks;static volatile u16 input_keys;
static int link_active=1,link_name_edit,link_avatar_edit;static u16 link_submit;
enum {MP_LOBBY=30};
static struct {int mode;} game;
static u32 presentation_event;
static int navigation_menu(void){return game.mode==MP_LOBBY;}
#include "link-input-under-test.inc"
static int failures;
/* Local play: src/main.c pressed/repeat from VBlank-ordered presses. */
static unsigned local_moves(const u16*held,unsigned frames,u16 key){
 u16 old=0;u32 repeat_at=0;unsigned moves=0;
 for(u32 t=0;t<frames;t++){u16 keys=held[t],pressed=keys&~old,repeat=pressed;
  if(keys!=old||(pressed&(UP|DOWN|LEFT|RIGHT)))repeat_at=t+18;
  else if((keys&(UP|DOWN|LEFT|RIGHT))&&(int)(t-repeat_at)>=0){repeat|=keys&(UP|DOWN|LEFT|RIGHT);repeat_at=t+5;}
  old=keys;if(repeat&key)moves++;}
 return moves;
}
/* Cable: VBlank capture on the owner, a packet every `period` VBlanks starting
 * at `offset`, one applied press per authority iteration. */
static unsigned cable_moves(const u16*held,unsigned frames,u16 key,unsigned period,unsigned offset,int change_owner_at){
 link_tap_read=link_tap_write=0;link_remote_read=link_remote_write=0;link_remote_player=-1;link_repeat=(DirectionRepeat){0};
 input_keys=0;unsigned moves=0;int player=0;
 for(u32 t=0;t<frames+400;t++){
  video_ticks=t;u16 keys=t<frames?held[t]:0,pressed=keys&~input_keys;input_keys=keys;link_capture_input(pressed);
  if(change_owner_at>=0&&t==(u32)change_owner_at)player=1;
  if(t%period==offset%period){link_sample_input();
   /* After a turn change the authority reads the new owner's console. */
   link_queue_remote(player?0:link_submit,player);}
  u16 p=link_next_remote(player);if(p&key)moves++;
 }
 return moves;
}
static void check(const char*name,const u16*held,unsigned frames,u16 key){
 unsigned want=local_moves(held,frames,key);
 for(unsigned period=2;period<=12;period+=2)for(unsigned offset=0;offset<period;offset++){
  unsigned got=cable_moves(held,frames,key,period,offset,-1);
  if(got!=want){printf("FAIL %s period %u offset %u: local %u cable %u\n",name,period,offset,want,got);failures++;return;}
 }
 printf("PASS %s: %u moves at every packet period/offset\n",name,want);
}
int main(void){
 static u16 held[600];
 for(unsigned gap=3;gap<=14;gap+=1)for(unsigned taps=2;taps<=6;taps++){
  for(unsigned t=0;t<600;t++)held[t]=t<gap*taps&&t%gap<2?RIGHT:0;
  char name[64];snprintf(name,sizeof name,"%u RIGHT taps every %u VBlanks",taps,gap);check(name,held,600,RIGHT);
  for(unsigned t=0;t<600;t++)held[t]=t<gap*taps&&t%gap<2?A:0;
  snprintf(name,sizeof name,"%u A taps every %u VBlanks",taps,gap);check(name,held,600,A);
 }
 for(unsigned hold=1;hold<=80;hold+=3){
  for(unsigned t=0;t<600;t++)held[t]=t>=5&&t<5+hold?DOWN:0;
  char name[64];snprintf(name,sizeof name,"DOWN held %u VBlanks",hold);check(name,held,600,DOWN);
 }
 /* Direction then A in the same VBlank keeps direction-first order. */
 link_tap_read=link_tap_write=0;link_remote_read=link_remote_write=0;link_remote_player=-1;link_repeat=(DirectionRepeat){0};input_keys=0;
 video_ticks=1;input_keys=RIGHT|A;link_capture_input(RIGHT|A);link_sample_input();link_queue_remote(link_submit,0);
 link_sample_input();link_queue_remote(link_submit,0);
 u16 first=link_next_remote(0),second=link_next_remote(0);
 if(first!=RIGHT||second!=A){printf("FAIL simultaneous order %x %x\n",first,second);failures++;}else printf("PASS simultaneous RIGHT+A applies RIGHT then A\n");
 /* Presses queued for the previous owner are dropped on a turn change. */
 for(unsigned t=0;t<600;t++)held[t]=t<60?RIGHT:0;
 unsigned after=cable_moves(held,600,RIGHT,12,0,30);
 unsigned within=local_moves(held,31,RIGHT);
 if(after>within){printf("FAIL owner change applied %u moves, owner had %u\n",after,within);failures++;}
 else printf("PASS owner change discards the previous owner's queued presses (%u <= %u)\n",after,within);
 /* Name/avatar editing never produces remote presses. */
 link_name_edit=1;link_tap_read=link_tap_write=0;input_keys=A;link_capture_input(A);link_sample_input();
 if(link_submit||link_tap_read!=link_tap_write){printf("FAIL name edit produced input\n");failures++;}else printf("PASS name edit produces no cable input\n");
 link_name_edit=0;
 input_keys=A;link_capture_input(A);link_sample_input();
 u16 delayed=link_submit;
 presentation_event++;link_queue_remote(delayed,0);
 if(link_next_remote(0)){puts("FAIL delayed confirmation crossed an action");failures++;}
 input_keys=A;link_capture_input(A);link_sample_input();link_queue_remote(link_submit,0);
 presentation_event++;
 if(link_next_remote(0)){puts("FAIL queued confirmation crossed an action");failures++;}
 input_keys=A;link_capture_input(A);presentation_event++;link_sample_input();
 if(link_submit>>10){puts("FAIL stale owner event transmitted");failures++;}
 return failures?1:0;
}
