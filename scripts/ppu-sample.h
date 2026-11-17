/* Colour at the PPU output, without mGBA's internal layer flags. */
static uint16_t ppu_rgb555(color_t pixel){
#ifndef COLOR_16_BIT
 return M_RGB8_TO_BGR5(pixel);
#elif defined(COLOR_5_6_5)
 return (pixel>>11)|((pixel>>1)&0x3e0)|((pixel&31)<<10);
#else
 return pixel&0x7fff;
#endif
}
/* Hardware frame phase, with zero at the start of scanline 160. */
static uint32_t cycles_since_vblank(struct GBA*gba){
 return ((gba->video.vcount+228-160)%228)*1232+
  ((gba->memory.io[REG_DISPSTAT/2]&2)?1232:VIDEO_HDRAW_LENGTH)-
  (gba->video.event.when-mTimingCurrentTime(&gba->timing));
}
