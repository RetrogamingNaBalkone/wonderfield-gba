/* Drive the drawing entry points in two real cartridges with frozen game
 * state. The PPU, VRAM, DMA restrictions, scanline OBJ limits and palettes
 * are those of mGBA. No renderer is linked into the comparison program. */
#include <mgba/core/core.h>
#include <mgba/internal/gba/gba.h>
#include <mgba/internal/arm/arm.h>
#include <mgba/internal/gba/io.h>
#include "ppu-sample.h"
#include <stdio.h>
#include <stdlib.h>

#define IDLE 0x0203fff0u
static struct mCore *core;
static color_t pixels[240*160];

static void quiet(struct mLogger*l,int c,enum mLogLevel level,const char*f,va_list a){
 (void)l;(void)c;(void)level;(void)f;(void)a;
}
static uint32_t invoke(uint32_t fn){
 if(!fn)return 0;
 uint32_t lr=IDLE|1,pc=fn&~1u;
 core->writeRegister(core,"lr",&lr);
 core->writeRegister(core,"pc",&pc);
 struct GBA*gba=core->board;
 uint64_t start=mTimingGlobalTime(&gba->timing);
 for(;;){
  core->step(core);
  pc=gba->cpu->gprs[ARM_PC];
  if(pc==IDLE+2||pc==IDLE+4)return mTimingGlobalTime(&gba->timing)-start;
  if(mTimingGlobalTime(&gba->timing)-start>2808960){fprintf(stderr,"Renderer timed out at %08x\n",pc);exit(2);}
 }
}
int main(int argc,char**argv){
 if(argc!=2)return 1;
 struct mLogger logger={quiet,0};mLogSetDefaultLogger(&logger);
 core=mCoreFind(argv[1]);if(!core||!core->init(core))return 1;
 mCoreInitConfig(core,NULL);
 mCoreConfigSetDefaultIntValue(&core->config,"useBios",0);
 mCoreConfigSetDefaultIntValue(&core->config,"skipBios",1);
 mCoreConfigSetDefaultValue(&core->config,"idleOptimization","ignore");
 mCoreLoadConfig(core);core->setVideoBuffer(core,pixels,240);
 if(!mCoreLoadFile(core,argv[1]))return 1;
 core->reset(core);
 for(int i=0;i<90;i++)core->runFrame(core);

 core->busWrite16(core,IDLE,0xe7fe);
 uint32_t cpsr=0x3f,sp=0x03007800;
 core->writeRegister(core,"cpsr",&cpsr);core->writeRegister(core,"sp",&sp);
 uint32_t frame=core->frameCounter(core),setup_cycles=0;
 char command;unsigned a,b,d;
 while(scanf(" %c",&command)==1){
  if(command=='w'&&scanf("%x %x",&a,&b)==2)core->busWrite32(core,a,b);
  else if(command=='b'&&scanf("%x %x",&a,&b)==2)core->busWrite8(core,a,b);
  else if(command=='c'&&scanf("%x",&a)==1){setup_cycles+=invoke(a);}
  else if(command=='f'&&scanf("%x %x %x",&a,&b,&d)==3){
   uint32_t cycles=setup_cycles+invoke(a);
   cycles+=invoke(b);

   invoke(d);
   struct GBA*gba=core->board;
   unsigned line=gba->video.vcount;
   uint32_t phase=cycles_since_vblank(gba);
   uint32_t frames=core->frameCounter(core)-frame;
   uint32_t display=core->busRead16(core,0x04000000);
   core->runFrame(core);frame=core->frameCounter(core);setup_cycles=0;
   uint32_t frame_info[]={cycles,line,display,phase,frames};

   fwrite(frame_info,sizeof frame_info,1,stdout);
   uint16_t rgb[240*160];
   for(unsigned i=0;i<240*160;i++)rgb[i]=ppu_rgb555(pixels[i]);
   fwrite(rgb,sizeof rgb,1,stdout);fflush(stdout);
  }else return 1;
 }
 core->deinit(core);return 0;
}
