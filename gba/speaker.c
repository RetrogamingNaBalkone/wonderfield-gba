#include "speaker.h"
#define R16(a) (*(volatile unsigned short*)(a))
#define R32(a) (*(volatile unsigned*)(a))
typedef struct {unsigned short hz,ms;} Note;
static Note notes[256];
static unsigned count,index,remaining,phase,increment,buffer,enabled=1;
static unsigned fifo[8] __attribute__((aligned(4)));
volatile struct {unsigned irqs,samples,transitions,hz;} speaker_diag;
volatile unsigned speaker_silent_buffers;
extern unsigned pole_udiv(unsigned,unsigned);
static void fill(void){
 if(!remaining&&index>=count){
  unsigned*p=&fifo[buffer*4];p[0]=p[1]=p[2]=p[3]=0;increment=0;
  speaker_diag.samples+=16;speaker_silent_buffers++;return;
 }
 signed char*p=(signed char*)&fifo[buffer*4];for(unsigned i=0;i<16;i++){
 if(!remaining){if(index<count){Note n=notes[index++];remaining=pole_udiv((unsigned)n.ms*32768+500,1000);if(!remaining)remaining=1;unsigned hz=n.hz;if(hz>18){unsigned pit=pole_udiv(1193181,hz);hz=pole_udiv(1193181,pit);increment=(hz*1024+pole_udiv((1193181-hz*pit)*1024,pit))*128;}else increment=0;speaker_diag.hz=hz;speaker_diag.transitions++;}else increment=0;}
 if(remaining)remaining--;phase+=increment;p[i]=(enabled&&increment)?(phase&0x80000000?64:-64):0;speaker_diag.samples++;
}}
static void arm(void){R16(0x040000c6)=0;R32(0x040000bc)=(unsigned)&fifo[buffer*4];R32(0x040000c0)=0x040000a0;R16(0x040000c4)=4;R16(0x040000c6)=0xf640;}
void speaker_init(void){R16(0x04000084)=0x80;R16(0x04000080)=0;R16(0x04000088)=0x200;R16(0x04000082)=0x0b04;buffer=0;fill();for(int i=0;i<4;i++)R32(0x040000a0)=fifo[i];fill();for(int i=0;i<4;i++)R32(0x040000a0)=fifo[i];fill();buffer=1;fill();buffer=0;arm();R16(0x04000100)=65024;R16(0x04000102)=0x80;R16(0x04000200)|=0x200;R16(0x04000208)=1;}
void speaker_irq(unsigned flags){if(flags&0x200){fill();buffer^=1;arm();speaker_diag.irqs++;}}
void speaker_enable(int on){enabled=on;}
static void add(unsigned hz,unsigned ms){if(ms&&count<256)notes[count++]=(Note){hz,ms};}
void speaker_tone(unsigned hz,unsigned ms){unsigned short old=R16(0x04000208);R16(0x04000208)=0;count=index=remaining=0;add(hz,ms);R16(0x04000208)=old;}
void speaker_queue_tone(unsigned hz,unsigned ms){
 unsigned short old=R16(0x04000208);R16(0x04000208)=0;
 if(index==count)index=count=0;
 else if(count==256&&index){unsigned used=index;for(unsigned i=used;i<count;i++)notes[i-used]=notes[i];count-=used;index=0;}
 add(hz,ms);R16(0x04000208)=old;
}
void speaker_effect(unsigned effect,unsigned random_seed){unsigned short old=R16(0x04000208);R16(0x04000208)=0;count=index=remaining=0;
 /* Each sequence is taken from the Sound/Delay/NoSound calls at these addresses.
  * Delay is Turbo Pascal milliseconds; scheduling no longer depends on PC CPU. */
 if(effect==0){/* 1000:08e4 */for(unsigned i=1;i<=6;i++){random_seed=random_seed*134775813u+1;add((random_seed>>16)%100,6-i);add(0,1);}}
 if(effect==1){/* 1000:1a3a: four phases of the letter-selection animation */for(unsigned e=0;e<=3;e++)for(unsigned i=1;i<=10;i++){add(i*10+e*100+50,1);add(0,e*4+i/5);}}
 if(effect==2){/* 1000:1698: entry sweep, then exit sweep */for(unsigned i=20;i<=100;i++){add(i,1);add(0,(100-i)/5);}}
 if(effect==3){/* 1000:1698: exit sweep */for(unsigned i=100;i>=20;i--){add(i,(100-i)/10);add(0,1);}}
 if(effect==4){/* 1000:37eb: sliding prompt */for(unsigned i=40;i>0;i--){add(1000-i*20,1);add(0,i);}}
 R16(0x04000208)=old;
}
