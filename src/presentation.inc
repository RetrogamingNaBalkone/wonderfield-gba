/* The DOS stage, rebuilt from its original artwork at GBA dimensions.
 * Layer order is intentional: stage, board, wheel, people, panels, speech.
 * No moving part may paint over a spoken sentence. */
static void image(const Sprite*s,int x,int y,int transparent){
 int left=x<0?-x:0,right=s->w,top=y<0?-y:0,bottom=s->h;
 if(x+right>240)right=240-x;if(y+bottom>160)bottom=160-y;
 for(int yy=top;yy<bottom;yy++){
  u8*d=framebuffer+(y+yy)*240+x;const u8*b=s->data+yy*s->w;
  for(int xx=left;xx<right;xx++){u8 v=b[xx];if(v!=transparent)d[xx]=v;}
 }
}
static void half_image(int id,int x,int y,int transparent){image(&sprites_half[id],x,y,transparent);}
static void border(int x,int y,int w,int h,u8 c){line(x,y,w,c);line(x,y+h-1,w,c);rect(x,y,1,h,c);rect(x+w-1,y,1,h,c);}
static void label_center(int x,int y,int width,const char*t,int small,u8 color){text(x+(width-len(t)*8)/2,y,t,small,color);}
static void studio(void){
 dma_words((u32*)framebuffer,(const u32*)stage_background,9600);
}
static int speech_visible(void){
 if(!message1||!*message1||game.mode==SPIN||(game.mode==REVEAL&&scene.now-scene.start>=90))return 0;
 if(game.mode==TURN&&scene.now-scene.speech_at>120)return 0;
 return 1;
}
static void board(void){
 /* Three coherent rows: 8 px, 16 px, 8 px. Letters belong to the middle row. */
 rect(30,2,181,33,7);
 if(game.mode==INTRO&&scene.phase<4){
  const char*t=game.round==0?msg_568e:game.round==1?msg_569c:msg_56a8;while(*t==' ')t++;
  int n=len(t),x=30+((20-n)/2)*9;
  for(int i=0;i<n;i++)glyph(x+i*9+1,11,(u8)t[i],0,0);
 }else{
  int n=len(word()),cw=9,x=30+((20-n)/2)*cw;
  for(int i=0;i<n;i++){
   rect(x+i*cw+1,11,cw-1,15,game.revealed[i]?7:8);
   if(game.revealed[i])glyph(x+i*cw+1,11,(u8)word()[i],0,0);
   if(game.mode==PLUS&&game.cursor==i)line(x+i*cw+1,25,cw-1,14);
  }
 }
 for(int x=30;x<=210;x+=9)rect(x,2,1,33,0);
 for(int y=2;y<=34;y+=8)if(y!=18)line(30,y,181,0);
 rect(30,35,181,9,7);
 if(!speech_visible()){
  if(game.mode!=INTRO)text(30,35,words[game.word_id].topic,1,0);
  if(len(words[game.word_id].topic)<=18){text(194,35,"/3",1,0);glyph(186,35,'1'+game.round,1,0);}
 }
 line(30,43,181,8);
}
static void wheel(void){
 int phase=(24-game.sector*2)&31;
 if(game.mode==SPIN)phase+=scene.spin_half;
 const u32*source=(const u32*)(wheel_bitmaps+(phase&31)*(128*112));
 for(int y=0;y<112;y++){
  u32*d=(u32*)(framebuffer+(43+y)*240+32);
  for(int x=0;x<32;x++)d[x]=source[y*32+x];
 }
}
static void score_badge(int player,int x,int y){
 int value=game.score[player];
 if(value==0){const Sprite*s=&sprites_half[28];image(s,x+(44-s->w)/2,y,7);return;}
 rect(x,y,44,10,5);border(x,y,44,10,0);number(x+2,y+1,value,1,0);
}
static int host_visible(void){
 if(!scene.host_active||!speech_visible()||game.mode==AI_ANSWER)return 0;
 if(game.mode==TITLE||game.mode==HELP||game.mode==RECORDS||game.mode==GALLERY||game.mode==SOLVE||game.mode==NAME||game.mode==GIFT_PAGES)return 0;
 if(game.mode==CASH&&cash.ready)return 0;
 if(game.mode==CREDITS&&scene.now-scene.start>=26)return 0;
 return 1;
}
static void host_pose(int*face,int*eyes,int*eye_y){
 /* DOS 1000:0936 rests on face 45 + eyes 43. 42/45 change the mouth;
  * 43/44 are eye strips, not mouth sprites. No independent idle timer. */
 *face=45;*eyes=43;*eye_y=75;
 if(!host_visible())return;
 int phase=scene.host_phase;
 if(phase<3){*eyes=phase==1?43:44;return;}
 if(phase<9){if(!(phase&1)){*face=42;*eyes=-1;}return;}
 /* 1000:0bce: raised eyes 43, then 44; hold the speaking pose until clear. */
 *face=42;*eyes=phase==9?43:44;*eye_y=71;
}
static void people(void){
 for(int player=0;player<2;player++){
  int visible=game.mode!=INTRO||scene.phase>=player+1;
  if(!visible)continue;
  int id=opponent_sprites[game.opponent[game.round*2+player]];
  int x=player?153:3,y=83;
  if(game.mode==INTRO&&scene.phase==player+1&&scene.now-scene.phase_at<54){
   int phase=(scene.now-scene.phase_at)/18;
   half_image(53+phase,x,y,2);
  }else half_image(id,x,y,2);
  score_badge(player,player?141:1,73);
 }
 /* Host rectangle: [185,240), separate from the widest contestant [153,182). */
 half_image(27,185,56,-1);
 int face,eyes,eye_y;host_pose(&face,&eyes,&eye_y);
 half_image(face,196,57,-1);
 if(eyes>=0)half_image(eyes,204,eye_y,-1);
 rect(164,138,76,12,5);border(164,138,76,12,0);
 text(168,140,"ВЫ",1,0);
 int value=game.score[2],digits=1;unsigned v=value<0?-value:value;
 while(v>=10){v/=10;digits++;}if(value<0)digits++;
 number(238-digits*8,140,value,1,0);
}
static void speech_strip(const Sprite*s,int x,int y,int width,int top,int height,int transparent){
 /* Resolve columns once; division per pixel stalls ARM7 during speech. */
 int columns[240],sx=0,remainder=0;
 for(int xx=0;xx<width;xx++){columns[xx]=sx;remainder+=s->w;while(remainder>=width){remainder-=width;sx++;}}
 for(int yy=0;yy<height;yy++)for(int xx=0;xx<width;xx++){
  u8 c=s->data[(top+yy)*s->w+columns[xx]];if(c!=transparent)pixel(x+xx,y+yy,c);
 }
}
static void speech(void){
 if(!speech_visible())return;
 if(game.mode==AI_ANSWER){
  const Sprite*s=&sprites[39];int x=game.player?141:1,w=98;
  speech_strip(s,x,35,w,0,s->h,2);
  label_center(x+3,44,w-6,message1,0,0);return;
 }
 /* DOS colour 1 is transparent. Stretch only the body, keep the tail local. */
 /* Leave the waiting assistant visible beside the host's reaction balloon. */
 const Sprite*s=&sprites[35];int x=game.mode==CASH?104:game.mode==REVEAL?50:4,w=236-x,h=36,y=35;
 for(int yy=0;yy<h;yy++)for(int xx=0;xx<w;xx++){
  int sx=xx<8?xx:xx>=w-8?s->w-(w-xx):s->w/2;
  int sy=yy<3?yy:yy>=h-3?27+yy-(h-3):15;
  u8 c=s->data[sy*s->w+sx];if(c!=1)pixel(x+xx,y+yy,c);
 }
 /* The shrinking lower curve and tail must never be tiled across the screen. */
 speech_strip(s,x,y+h,w,30,s->h-30,1);
 label_center(x+3,y+2,w-6,message1,0,0);
 if(message2&&*message2)label_center(x+3,y+18,w-6,message2,0,0);
}
static void keyboard(void){
 rect(3,84,234,66,1);border(3,84,234,66,0);
 for(int i=0;i<32;i++){
  int x=8+(i%8)*28,y=86+(i/8)*16;
  int used=game.mode==SOLVE?fixed_letter(i):game.mode!=NAME&&game.used[i];
  rect(x,y,26,15,i==game.cursor?14:11);border(x,y,26,15,0);
  /* The first row of CP866 0x89 is its breve: keep it off the key border. */
  glyph(x+9,y+1,128+i,0,used?8:0);
  if(used)line(x+3,y+7,20,0);
 }
 if(game.mode==SOLVE){
  int n=len(word());rect(4,62,232,20,0);
  for(int i=0;i<n;i++){int x=(240-n*10)/2+i*10;glyph(x,64,game.answer[i]?(u8)game.answer[i]:'_',0,game.revealed[i]?8:15);}
  if(game.solve_pos<n)line((240-n*10)/2+game.solve_pos*10,79,8,14);
 }
}
static void title(void){
 unsigned age=scene.now-scene.title_at;
 rect(0,0,240,160,7);
 for(int x=5;x<240;x+=23){int h=age<40?age*3:120;rect(x,134-h,1,h,6);}
 for(int y=14;y<=134;y+=20){int w=age<40?0:age<80?(age-40)*6:230;line(5,y,w,6);}
 border(5,14,230,121,6);
 centered(0,"Посвящается друзьям",1,0);
 if(age>=80)for(int i=0;i<2;i++){
  const Sprite*s=&title_logos[i];int left=i?104:9;
  for(int y=0;y<s->h;y++)for(int x=0;x<s->w;x++)
   if(s->data[y*s->w+x]!=7)pixel(left+x,23+y,s->data[y*s->w+x]);
 }
 if(age>=100)text(40,124,"КАПИТАЛ-ШОУ",1,0);centered(139,"A / START: играть",1,1);
 if(age>=100){
  /* The original compact font fits wholly inside the final grid cell. */
  const char*version="1.1";
  for(int i=0;i<3;i++)for(int y=0;y<6;y++)for(int x=0;x<4;x++)
   if(font6[(u8)version[i]*6+y]&(128>>x))pixel(218+i*4+x,122+y,0);
 }
 centered(151,"SELECT: помощь  L: рекорды",1,0);
}
static void help(void){
 rect(0,0,240,160,1);centered(3,"УПРАВЛЕНИЕ",0,14);
 text(4,24,"A: подтвердить / далее",1,15);
 text(4,37,"Крестовина: выбор",1,15);
 text(4,50,"B: скрыть / стереть",1,15);
 text(4,63,"START: пауза / продолжить",1,15);
 text(4,76,"При вводе SELECT: пауза",1,15);
 text(4,89,"При вводе START: OK",1,15);
 text(4,102,"L: включить / выключить звук",1,15);
 text(4,115,"На паузе SELECT: меню",1,15);
 centered(134,"Автор игры Дима Башуров",1,14);
 centered(150,"A / B / START: назад",1,15);
}
static void footer(void){
 rect(0,152,240,8,7);
 const char*t="A: далее   START: пауза";
 if(game.mode==TURN&&game.player==2)t="ВЛЕВО/ВПРАВО: выбор  A: OK";
 if(game.mode==LETTER)t=game.keyboard?"A: буква  B: скрыть":"A / B: выбрать букву";
 if(game.mode==SOLVE)t="A: буква B: стереть START: OK";
 if(game.mode==REVEAL)t="A: пропустить помощницу";
 if(game.mode==SPIN)t="A: пропустить вращение";
 if(game.mode==PRIZE||game.mode==CHEST)t="ВЛЕВО/ВПРАВО: выбор  A: OK";
 if(game.mode==GAME_OVER)t="A: главное меню";
 if(game.mode==CASH)t=cash.drawn<cash.total?"A: пропустить выдачу денег":"A: продолжить";
 centered(152,t,1,0);
}
static int certificate_paragraph(int y,const char*a,const char*b,const char*c,u8 color){
 char joined[128],rows[5][30];int length=0,count=0,pos=0;const char*parts[3]={a,b,c};
 for(int i=0;i<3;i++)if(parts[i])for(int j=0;parts[i][j]&&length<127;j++)joined[length++]=parts[i][j];
 joined[length]=0;
 while(pos<length&&count<5){
  int n=0,space=-1;while(pos+n<length&&n<29){if(joined[pos+n]==' ')space=n;n++;}
  if(pos+n<length&&joined[pos+n]!=' '&&space>0)n=space;
  for(int i=0;i<n;i++)rows[count][i]=joined[pos+i];rows[count][n]=0;count++;pos+=n;
  if(joined[pos]==' ')pos++;
 }
 if(color==15)rect(4,y-2,232,count*16+2,1);
 for(int i=0;i<count;i++)centered(y+i*16,rows[i],0,color);
 return y+count*16+2;
}
static void gift_certificate(void){
 /* 1000:47bd / 42b4: complete DOS gift text, paged at native 8x14. */
 rect(0,0,240,160,7);sprite(46,68,0,80,7);sprite(47,125,0,64,7);line(4,47,232,1);
 int y=50;
 if(scene.gift_page==0){
  if(scene.gift_final){
   char score[12],reverse[12];int n=0;unsigned value=game.score[2];
   do{reverse[n++]='0'+value%10;value/=10;}while(value);
   for(int i=0;i<n;i++)score[i]=reverse[n-1-i];score[n]=0;
   y=certificate_paragraph(y,msg_46aa,score,msg_46ca,0);
  }else y=certificate_paragraph(y,msg_41d7,0,0,0);
  y=certificate_paragraph(y,scene.gift_final?msg_46d2:msg_41fd,0,0,0);
  certificate_paragraph(y,gift_names[game.prize],scene.gift_final?msg_46fc:msg_4224,0,15);
 }else if(scene.gift_page==1){
  y=certificate_paragraph(y,scene.gift_final?msg_4718:msg_4240,0,0,0);
  y=certificate_paragraph(y,scene.gift_final?msg_4739:msg_4261,0,0,15);
  certificate_paragraph(y,scene.gift_final?msg_475d:msg_4285,0,0,0);
 }else{
  y=certificate_paragraph(y,msg_4099,0,0,0);
  certificate_paragraph(y,msg_40d8,0,0,0);
 }
 rect(0,151,240,9,7);text(4,152,"A: далее  B: назад",1,0);text(216,152,"/3",1,0);glyph(208,152,'1'+scene.gift_page,1,0);
}
static void render(void){
 if(game.mode==CASH){
  dma_words((u32*)framebuffer,(const u32*)cash_canvas,9600);
  /* During the short opening line the host speaks; banknotes then cover
   * the original portrait/lettering as well, exactly as the DOS screen. */
  if(!cash.ready){int face,eyes,eye_y;host_pose(&face,&eyes,&eye_y);half_image(face,196,76,-1);if(eyes>=0)half_image(eyes,204,eye_y+19,-1);}
  /* The original cash line remains visible until the player continues. */
  speech();footer();return;
 }
 if(game.mode==GIFT_PAGES){gift_certificate();return;}
 if(game.mode==TITLE){title();return;}
 if(game.mode==HELP){help();return;}
 if(game.mode==RECORDS){
  rect(0,0,240,160,7);centered(0,msg_478c,0,1);centered(14,msg_479e,0,1);
  for(int i=0;i<8;i++){number(8,32+i*15,i+1,1,1);text(28,32+i*15,record_names[i],1,0);number(152,32+i*15,record_scores[i],1,0);}
  centered(148,"A / B: назад",1,1);return;
 }
 if(game.mode==NAME){rect(0,0,240,160,7);centered(5,"8 лучших игроков",0,1);centered(29,"Ваше имя:",0,0);text(70,60,(const char*)game.answer,0,0);keyboard();centered(151,"A: буква B: стереть START: OK",1,0);return;}
 if(game.mode==GALLERY){
  rect(0,0,240,160,7);const Sprite*s=&sprites[game.album];int scale=256;
  if(s->w>220)scale=divide(220*256,s->w);if((s->h*scale)>>8>120)scale=divide(120*256,s->h);
  sprite(game.album,(240-((s->w*scale)>>8))/2,18,scale,-1);number(3,3,game.album,1,0);centered(150,"ВЛЕВО/ВПРАВО  B: назад",1,0);return;
 }
 if(game.mode==SOLVE){rect(0,0,240,160,0);centered(8,msg_f20,0,15);keyboard();footer();return;}
 /* While the credits enter, the uncovered stage is still visible. Once
  * they fill the display, no hidden stage objects need to be drawn. */
 if(game.mode!=CREDITS||scene.now-scene.start<40){studio();board();wheel();people();}
 if(game.mode==CREDITS){
  int top=160-(int)((scene.now-scene.start)*4);if(top<0)top=0;
  rect(0,top,240,160,1);
  const char*lines[10]={msg_4ebd,msg_4ecf,msg_4ee3,msg_4ef5,msg_4f08,msg_4f18,msg_4f2a,msg_4f38,msg_4f47,msg_4f5a};
  for(int i=0;i<10;i++)centered(top+4+i*14,lines[i],0,14);
  centered(top+151,"A: продолжить",1,15);return;
 }
 if(game.mode==REVEAL){
  int id=(game.sector_value!=100&&scene.now-scene.start<90)||scene.actor_stop?23:((scene.now/6)%4==0?24:(scene.now/6)%4==2?25:26);
  /* Both side walls are foreground boundaries: the figure passes behind them. */
  const Sprite*s=&sprites_half[id];
  for(int y=0;y<s->h;y++)for(int x=0;x<s->w;x++){
   int px=scene.actor_x+x;u8 color=s->data[y*s->w+x];
   if(px>=15&&px<225&&color!=2)pixel(px,12+y,color);
  }
 }
 if(game.mode==CHEST){
  int phase=(scene.now-scene.speech_at)/6;
  int animate=scene.now-scene.speech_at<90;
  image(&sprites[animate&&!(phase&1)?37:36],18,96,7);image(&sprites[animate&&(phase&1)?37:36],115,96,7);border(game.choice?113:16,94,40,42,14);
 }
 if(game.mode==RESULT&&scene.now<scene.chest_until){
  image(&sprites[scene.chest_money?38:37],game.choice?115:18,96,7);image(&sprites[36],game.choice?18:115,96,7);
 }
 if(game.mode==PRIZE){
  if(game.deal){
   rect(6,99,150,48,7);border(6,99,150,48,0);
   int digits=1,value=game.prize;while(value>=10){value/=10;digits++;}
   number(81-digits*4,102,game.prize,0,0);
  }
  /* Both alternatives stay visible; a shared frame makes this one switch. */
  rect(6,122,150,25,0);
  for(int option=0;option<2;option++){
   int x=option?81:7,w=option?74:73,selected=game.choice==option;
   const char*t=option?(game.deal?"ПРИЗ":"ИГРАЕМ"):(game.deal?"ДЕНЬГИ":"ПРИЗ");
   rect(x,123,w,23,selected?1:7);
   label_center(x,127,w,t,0,selected?15:0);
  }
 }
 if(game.mode==TURN&&game.player==2){
  rect(6,110,150,37,0);
  for(int option=0;option<2;option++){
   int x=option?81:7,w=option?74:73,selected=game.choice==option;
   rect(x,111,w,35,selected?1:7);
   label_center(x,112,w,option?"Кручу":"Скажу",0,selected?15:0);
   label_center(x,129,w,option?"БАРАБАН":"СЛОВО",0,selected?15:0);
  }
 }
 if(game.mode==GAME_OVER&&game.deal==6){
  rect(3,103,177,31,7);label_center(3,108,177,gift_names[game.prize],0,0);
 }
 if(game.keyboard&&game.mode==LETTER)keyboard();
 /* Speech is the final scene overlay and cannot be overwritten by the wheel. */
 speech();footer();
}
