/* Mode 0 VRAM (4bpp, 1D objects).
 * CBB0: ground, editable first six tile rows, current wheel phase.
 * CBB1: score badges and statistics from y=56. CBB2: foreground UI.
 * SBB28..31: fixed BG0..BG3 maps. OBJ VRAM holds the complete cast.
 * Priority from front to back: UI, chests/assistant/host, statistics,
 * contestants, wheel, board/studio. Lower OAM indices win object ties. */
enum {BITMAP_SCREEN,STUDIO_SCREEN,CASH_SCREEN,PAPER_SCREEN};
static int studio_frame,studio_live,board_upload,stats_upload,overlay_upload;
static int wheel_phase,wheel_multi,shown_phase,shown_multi,credits_top;
static u32 board_tiles[180*8],stats_tiles[390*8],overlay_tiles[600*8];
typedef struct {u16 y,x,tile,pad;} OamEntry;
static OamEntry studio_oam[128];
static unsigned object_count,previous_objects;
static u32 *const tile_vram=(u32*)0x06000000;

static InkLayer cash_ink={.tiles=cash_canvas,.rows=20};
static int cash_has_base,cash_showed_base,cash_map_loaded,cash_full,partial_keyboard,keyboard_cells[2];
static InkLayer board_ink={.tiles=board_tiles,.rows=6};
static InkLayer stats_ink={.tiles=stats_tiles,.first=7,.rows=13};
static InkLayer ui_ink={.tiles=overlay_tiles,.rows=20};

static void scene_object(const StudioObject*obj,int x,int y,int priority){
 for(int row=0;row<obj->rows;row++)for(int col=0;col<obj->cols;col++){
  int px=x+16*col,py=y+16*row;
  if(px<=-16||px>=240||py<=-16||py>=160)continue;
  OamEntry*o=&studio_oam[127-object_count++];
  o->y=py&255;o->x=(px&511)|(1<<14);
  o->tile=(obj->bank<<12)|(priority<<10)|(obj->tile+4*(row*obj->cols+col));
 }
}
static void studio_palette(void){
 volatile u16*bg=(volatile u16*)0x05000000,*obj=(volatile u16*)0x05000200;
 for(int i=0;i<16;i++){
  bg[13*16+i]=palette[i^13];
  for(int bank=0;bank<16;bank++)obj[16*bank+i]=palette[i^bank];
 }
}
typedef struct {u32*dest;const u32*source;unsigned words;} TileCopy;
static TileCopy uploads[48]; /* 20 UI rows + 13 score rows + 8 fixed banks. */
static unsigned upload_count;
static void queue_tiles(u32*dest,const u32*source,unsigned words){
 uploads[upload_count++]=(TileCopy){dest,source,words};
}
static void queue_ink(const InkLayer*l,u32*dest){
 if(!studio_live){queue_tiles(dest,l->tiles,l->rows*240);return;}
 for(int row=0;row<l->rows;row++){
  int left=l->old_left[row]<l->left[row]?l->old_left[row]:l->left[row];
  int right=l->old_right[row]>l->right[row]?l->old_right[row]:l->right[row];
  if(right<=left)continue;
  int offset=(row*30+left)*8;
  queue_tiles(dest+offset,l->right[row]>l->left[row]?l->tiles+offset:0,(right-left)*8);
 }
}
/* Mode 4 shares VRAM with the tile engine. Preload everything outside the
 * currently scanned bitmap. Only the intersection is due at the next VBlank. */
static void preload_hidden_vram(void){
 u32*first=tile_vram+((REG16(0x4000000)&16)?0xa000/4:0),*end=first+9600;
 for(unsigned i=0;i<upload_count;i++){
  TileCopy*t=&uploads[i];
  if(t->dest<first){
   unsigned n=first-t->dest;if(n>t->words)n=t->words;
   dma_words(t->dest,t->source,n);t->dest+=n;t->source+=n;t->words-=n;
  }
  unsigned visible=t->dest<end?(unsigned)(end-t->dest):0;
  if(t->words>visible){
   dma_words(t->dest+visible,t->source+visible,t->words-visible);t->words=visible;
  }
 }
}
/* Empty retained rows are much cheaper to erase from a fixed IWRAM word
 * than to stream from EWRAM. Keep the same audio-friendly DMA burst limit. */
static u32 blank_word __attribute__((section(".iwram.data")));
FAST static void clear_vram(u32*dest,unsigned words){
 while(words){
  unsigned n=words>64?64:words;
  REG32(0x040000d4)=(u32)&blank_word;REG32(0x040000d8)=(u32)dest;
  REG32(0x040000dc)=0x85000000u|n;dest+=n;words-=n;
 }
}
static void studio_present(void){
 upload_count=0;
 if(!studio_live){
  static const u32 blank[8]={0};

  queue_tiles(tile_vram+0xe000/4,(const u32*)studio_maps,2048);cash_map_loaded=0;
  queue_tiles(tile_vram+0x10000/4,(const u32*)studio_atlas,sizeof studio_atlas/4);
  queue_tiles(tile_vram+0x8000/4,blank,8);
  for(unsigned i=0;i<128-object_count;i++)studio_oam[i].y=0x200;
  previous_objects=128;
 }
 if(studio_frame==STUDIO_SCREEN&&studio_live!=STUDIO_SCREEN){
  static const u32 blank[8]={0};
  queue_tiles(tile_vram,(const u32*)studio_ground,sizeof studio_ground/4);
  queue_tiles(tile_vram+0x4000/4,blank,8);
 }
 if(studio_frame==STUDIO_SCREEN&&cash_map_loaded){
  queue_tiles(tile_vram+29*512,(const u32*)studio_maps+512,512);cash_map_loaded=0;
 }
 int opening_cash=studio_frame==CASH_SCREEN&&cash_has_base&&!cash.drawn;
 if(studio_frame==CASH_SCREEN){
  if(opening_cash){
   if(studio_live!=CASH_SCREEN||!cash_showed_base)
    queue_tiles(tile_vram+8,(const u32*)cash_ground,sizeof cash_ground/4);
   if(!cash_map_loaded){queue_tiles(tile_vram+29*512,(const u32*)cash_map,512);cash_map_loaded=1;}
  }else if(studio_live!=CASH_SCREEN||cash_showed_base||cash_full)queue_tiles(tile_vram+8,cash_canvas,sizeof cash_canvas/4);
  else queue_ink(&cash_ink,tile_vram+8);
  cash_showed_base=opening_cash;cash_full=0;
  for(int i=0;i<20;i++){cash_ink.left[i]=cash_ink.old_left[i]=30;cash_ink.right[i]=cash_ink.old_right[i]=0;}
 }
 if(board_upload)queue_tiles(tile_vram+64*8,board_tiles,sizeof board_tiles/4);
 if(stats_upload)queue_ink(&stats_ink,tile_vram+0x4000/4+97*8);
 if(overlay_upload)queue_ink(&ui_ink,tile_vram+0x8000/4+8);
 if(partial_keyboard){
  for(int i=0;i<2;i++){
   int cell=keyboard_cells[i],x=8+cell%8*28,y=86+cell/8*16;
   for(int row=y/8;row<=(y+14)/8;row++){
    int offset=(row*30+x/8)*8;
    queue_tiles(tile_vram+0x8000/4+8+offset,overlay_tiles+offset,((x+25)/8-x/8+1)*8);
   }
  }
 }
 if(studio_frame==STUDIO_SCREEN&&(studio_live!=STUDIO_SCREEN||wheel_phase!=shown_phase||wheel_multi!=shown_multi)){
  const u32*frame=(const u32*)studio_wheel+wheel_phase*1792;
  u32*dest=tile_vram+256*8;
  queue_tiles(dest,wheel_multi?(const u32*)studio_wheel_shifted+wheel_phase*256:frame,256);
  queue_tiles(dest+256,frame+256,1536);
  shown_phase=wheel_phase;shown_multi=wheel_multi;
 }
 if(!studio_live)preload_hidden_vram();
 vblank();
 for(unsigned i=0;i<upload_count;i++){
  TileCopy*t=&uploads[i];
  if(t->source)dma_words(t->dest,t->source,t->words);else clear_vram(t->dest,t->words);
 }
 if(!studio_live){
  REG16(0x4000008)=(28<<8)|(2<<2);              /* foreground */

  REG16(0x400000c)=(30<<8)|(1<<2)|2;            /* statistics */
  REG16(0x400000e)=(31<<8)|3;                   /* ground */
 }
 REG16(0x400000a)=((studio_frame==CASH_SCREEN&&!opening_cash?28:29)<<8)|3;
 REG16(0x4000014)=studio_frame!=STUDIO_SCREEN?0:wheel_multi?-28:-32;REG16(0x4000016)=studio_frame!=STUDIO_SCREEN?0:wheel_multi?-44:-43;
 unsigned count=previous_objects>object_count?previous_objects:object_count;
 for(unsigned i=object_count;i<previous_objects;i++)studio_oam[127-i].y=0x200;
 dma_words((u32*)0x07000000+(128-count)*2,(const u32*)(studio_oam+128-count),count*2);
 previous_objects=object_count;
 /* Two narrow windows implement the original assistant's wall clipping.
  * The board, labels and speech remain visible across both boundaries. */
 u16 display=studio_frame==STUDIO_SCREEN?0x1f40:studio_frame==CASH_SCREEN?0x1340:0x0140;
 if(game.mode==REVEAL){
  REG16(0x4000040)=15;REG16(0x4000042)=(225<<8)|240;
  REG16(0x4000044)=REG16(0x4000046)=(12<<8)|57;
  REG16(0x4000048)=0x0f0f;REG16(0x400004a)=0x1f;display|=0x6000;
 }else if(game.mode==CREDITS&&credits_top){
  REG16(0x4000040)=240;REG16(0x4000044)=credits_top;
  REG16(0x4000048)=0x1e;REG16(0x400004a)=0x1f;display|=0x2000;
 }
 REG16(0x4000012)=-credits_top;
 REG16(0x05000000)=palette[studio_frame==PAPER_SCREEN?13:0];
 REG16(0x4000000)=display;studio_live=studio_frame;
}
