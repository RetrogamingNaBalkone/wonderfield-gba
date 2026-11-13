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
 if(!message1||!*message1||game.mode==SPIN||(game.mode==REVEAL&&scene.now-scene.start>=MESSAGE_TICKS))return 0;
 if(game.mode==TURN&&human(game.player)&&scene.now-scene.speech_at>120)return 0;
 return 1;
}
static void board(void){
 /* Three coherent rows: 8 px, 16 px, 8 px. Letters belong to the middle row. */
 rect(30,2,181,33,7);
 if(game.mode==INTRO&&scene.phase<4){
  const char*t=mp.humans>1?mp_stage():game.round==0?msg_568e:game.round==1?msg_569c:msg_56a8;while(*t==' ')t++;
  int n=len(t),x=30+((20-n)/2)*9;
  for(int i=0;i<n;i++)glyph(x+i*9+1,11,(u8)t[i],0,0);
 }else{
  int n=len(word()),cw=9,x=30+((20-n)/2)*cw;
  for(int i=0;i<n;i++){
   rect(x+i*cw+1,11,cw-1,15,game.revealed[i]?7:8);
   if(game.revealed[i])glyph(x+i*cw+1,11,(u8)word()[i],0,0);
   if(game.mode==PLUS&&human(game.player)&&game.cursor==i){
    int selected_x=x+i*cw+1;
    rect(selected_x,11,cw-1,15,14);border(selected_x,11,cw-1,15,15);
    for(int row=0;row<3;row++)line(selected_x+1+row,5+row,6-row*2,0);
   }
  }
 }
 for(int x=30;x<=210;x+=9)rect(x,2,1,33,0);
 for(int y=2;y<=34;y+=8)if(y!=18)line(30,y,181,0);
 rect(30,35,181,9,7);
 if(mp.humans>1){
  const char*n=round_number();int suffix=prefs.rule==MP_WINS?0:2;
  int right=match.shootout?210:210-(len(n)+suffix)*8;
  if(game.mode!=INTRO){
   const char*topic=words[game.word_id].topic;int limit=(right-30-(match.shootout?0:8))/8;
   for(int i=0;topic[i]&&i<limit;i++)glyph(30+i*8,35,(u8)topic[i],1,0);
  }
  if(!match.shootout){text(right,35,n,1,0);if(suffix){text(194,35,"/",1,0);glyph(202,35,'0'+prefs.rounds,1,0);}}
 }else{
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
  u32*d=(u32*)(framebuffer+((mp.humans>1?44:43)+y)*240+(mp.humans>1?28:32));
  for(int x=0;x<32;x++)d[x]=source[y*32+x];
 }
 /* Wheel frames include the old wall behind transparent pixels. Preserve the
  * stationary wall when shifting the multiplayer wheel four pixels left. */
 if(mp.humans>1)for(int y=0;y<13;y++)for(int x=0;x<128;x++){
  int old=(43+y)*240+32+x,dest=old-4+240;
  if(((const u8*)source)[y*128+x]==stage_background[old])framebuffer[dest]=stage_background[dest];
 }
}
static void score_badge(int player,int x,int y){
 int value=game.score[player];
 if(mp.humans>1&&prefs.rule==MP_POINTS)value-=match.bank[player];
 if(value==0){const Sprite*s=&sprites_half[28];image(s,x+(44-s->w)/2,y,7);return;}
 rect(x,y,44,10,5);border(x,y,44,10,0);number(x+2,y+1,value,1,0);
}
static int host_visible(void){
 if(!scene.host_active||!speech_visible()||game.mode==AI_ANSWER||game.mode==AI_CHEST)return 0;
 if(game.mode==TITLE||game.mode==HELP||game.mode==MENU||game.mode==RECORDS||game.mode==SOLVE||game.mode==NAME||game.mode==GIFT_PAGES||game.mode==AUTHORS||game.mode==RESTART_CONFIRM)return 0;
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
static const Sprite*avatar_portrait(int avatar){
 if(!avatar)return &extra_sprites[6];
 if(!prefs.characters)return &sprites_half[opponent_sprites[avatar-1]];
 const u8 portraits[8]={11,12,9,7,8,10,0,1};return &extra_sprites[portraits[avatar-1]];
}
static void multiplayer_labels(int who,int center,int bottom);
static void people(void){
 for(int player=0;player<2;player++){
  int who=mp.humans>1?perspective(player):player;
  int intro_phase=mp.humans>1?player_number(who):player+1;
  int visible=game.mode!=INTRO||scene.phase>=intro_phase;
  if(!visible)continue;
  int character=mp.humans>1?opponent_pool[mp_ai_index]:game.opponent[game.round*2+player];
  int x=player?153:3,y=mp.humans>1?75:83;
  const Sprite*portrait;
  if(mp.humans>1&&human(who)&&!avatars[who]){
   int pose=6;if(game.player==who)pose=player?2:4;
   portrait=&extra_sprites[pose];x+=(29-portrait->w)/2;
  }else{
   if(mp.humans>1&&human(who))character=avatars[who]-1;
   if(!(mp.humans>1&&human(who))&&game.mode==INTRO&&scene.phase==intro_phase&&scene.now-scene.phase_at<54)
    portrait=&sprites_half[53+(scene.now-scene.phase_at)/18];
   else if(!prefs.characters)portrait=&sprites_half[opponent_sprites[character]];
   else{const u8 portraits[8]={11,12,9,7,8,10,0,1};portrait=&extra_sprites[portraits[character]];}
  }
  int height=portrait->h;
  while(mp.humans>1&&height>0){int ink=0;for(int col=0;col<portrait->w;col++)if(portrait->data[(height-1)*portrait->w+col]!=2)ink=1;if(ink)break;height--;}
  if(!(mp.humans>1&&(mp.eliminated&(1<<who))))image(portrait,x,y,2);
  score_badge(who,player?141:1,mp.humans>1?63:73);
  if(mp.humans>1){
   int left=portrait->w,right=0;
   for(int row=0;row<height;row++)for(int col=0;col<portrait->w;col++)if(portrait->data[row*portrait->w+col]!=2){if(col<left)left=col;if(col>right)right=col;}
   multiplayer_labels(who,x+(left+right+1)/2,y+height);
  }

 }
 /* Host rectangle: [185,240), separate from the widest contestant [153,182). */
 half_image(27,185,62,-1);
 int face,eyes,eye_y;host_pose(&face,&eyes,&eye_y);
 half_image(face,196,63,-1);
 if(eyes>=0)half_image(eyes,204,eye_y+6,-1);
 if(mp.humans==1)score_badge(2,164,142);
}
/* Six-pixel statistics use the original font; unusually long values compress
 * within their own fixed field, retaining every digit rather than clipping. */
static void compact_text(int x,int y,const char*s,int width,u8 color){
 int n=len(s),step=n*6<=width?6:width/n;if(step<1)step=1;
 for(int k=0;k<n;k++)for(int row=0;row<8;row++)for(int col=0;col<8;col++)
  if(font8[(u8)s[k]*8+row]&(128>>col))pixel(x+k*step+col*step/8,y+row,color);
}
/* Labels follow the same perspective as their portrait; speech and choices
 * may cover them temporarily, just as they cover the stage. */
static void player_name_label(int who,int side){
 const char*name=player_name(who);int n=len(name);
 int x=(side?163:23)-n*4;if(x<1)x=1;if(side&&x+n*8>185)x=185-n*8;if(side)x+=4;
 text(x,46,name,1,mp.eliminated&(1<<who)?8:15);
}
static void multiplayer_labels(int who,int center,int bottom){
 int y=bottom+2;if(y<112)y=112;
 u8 color=mp.eliminated&(1<<who)?8:0;
 if(prefs.rule==MP_POINTS){
  int value=game.score[who],digits=1;for(int v=value;v>=10;v/=10)digits++;
  int x=center-digits*4;if(x<0)x=0;
  number(x,y,value,1,color);
 }else if(prefs.rule==MP_WINS){
  int x=center-12;if(x<0)x=0;
  number(x,y,match.wins[who],1,color);text(x+8,y,"/",1,color);number(x+16,y,prefs.rounds,1,color);
 }
}
static void multiplayer_panel(void){
 if(mp.humans==1||(game.keyboard&&game.mode==LETTER))return;
 int who=mp.viewer;u8 color=mp.eliminated&(1<<who)?8:0;
 text(4,152,player_name(who),1,color);
 if(prefs.rule==MP_POINTS)number(100,152,game.score[who],1,color);
 else if(prefs.rule==MP_WINS){
  number(108,152,match.wins[who],1,color);text(116,152,"/",1,color);number(124,152,prefs.rounds,1,color);
 }
 score_badge(who,prefs.rule==MP_RISK?100:148,150);
}
static void speech_shape(int x,int y,const int*left,const int*right,int height){
 /* Outline the final silhouette, so no black stroke is lost to resampling. */
 for(int yy=0;yy<height;yy++)for(int xx=left[yy];xx<=right[yy];xx++){
  int edge=xx==left[yy]||xx==right[yy]||yy==0||yy==height-1;
  if(!edge)edge=xx<left[yy-1]||xx>right[yy-1]||xx<left[yy+1]||xx>right[yy+1];
  pixel(x+xx,y+yy,edge?0:14);
 }
}
static void speech_strip(const Sprite*s,int x,int y,int width,int transparent){
 int left[160],right[160],columns[240],sx=0,remainder=0;
 for(int xx=0;xx<width;xx++){columns[xx]=sx;remainder+=s->w;while(remainder>=width){remainder-=width;sx++;}}
 for(int yy=0;yy<s->h;yy++){
  left[yy]=width;right[yy]=-1;
  for(int xx=0;xx<width;xx++)if(s->data[yy*s->w+columns[xx]]!=transparent){
   if(left[yy]==width)left[yy]=xx;right[yy]=xx;
  }
 }
 speech_shape(x,y,left,right,s->h);
}
static void speech(void){
 if(!speech_visible())return;
 if(game.mode==AI_ANSWER||game.mode==AI_CHEST){
  const Sprite*s=&sprites[39];int x=(mp.humans>1?game.player==perspective(1):game.player!=0)?141:1,w=98;
  speech_strip(s,x,35,w,2);
  label_center(x+3,44,w-6,message1,0,0);return;
 }
 int n=len(message1),n2=message2?len(message2):0;if(n2>n)n=n2;
 int w=n*8+12;if(w<64)w=64;if(w>232)w=232;
 int x=236-w,h=36,y=game.mode==CASH?35:26,left[46],right[46];
 for(int yy=0;yy<h;yy++){
  int d=yy<h/2?yy:h-1-yy,inset=d==0?4:d==1?2:d==2?1:0;
  left[yy]=inset;right[yy]=w-1-inset;
 }
 /* A fixed tail beside the left cheek never scales across the host's face. */
 for(int yy=h;yy<46;yy++){
  int radius=45-yy;left[yy]=194-x-radius;right[yy]=194-x+radius;
 }
 speech_shape(x,y,left,right,46);
 label_center(x+3,y+2,w-6,message1,0,0);
 if(message2&&*message2)label_center(x+3,y+18,w-6,message2,0,0);
}
static void keyboard(void){
 rect(3,84,234,66,1);border(3,84,234,66,0);
 for(int i=0;i<32;i++){
  int x=8+(i%8)*28,y=86+(i/8)*16;
  int used=game.mode==SOLVE?fixed_letter(i):game.mode==LETTER&&game.used[i];
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
 for(int x=5;x<240;x+=23){int h=age<TITLE_GRID_HALF?age*120/TITLE_GRID_HALF:120;rect(x,134-h,1,h,6);}
 for(int y=14;y<=134;y+=20){int w=age<TITLE_GRID_HALF?0:age<TITLE_LOGO_AT?(age-TITLE_GRID_HALF)*230/TITLE_GRID_HALF:230;line(5,y,w,6);}
 border(5,14,230,121,6);
 centered(0,"Посвящается друзьям",1,0);
 if(age>=TITLE_LOGO_AT)for(int i=0;i<2;i++){
  const Sprite*s=&title_logos[i];int left=i?104:9;
  for(int y=0;y<s->h;y++)for(int x=0;x<s->w;x++)
   if(s->data[y*s->w+x]!=7)pixel(left+x,23+y,s->data[y*s->w+x]);
 }
 if(age>=TITLE_READY_AT){
  text(40,124,"КАПИТАЛ-ШОУ",1,0);centered(139,"A: Играть",1,1);
  centered(151,"START: Меню",1,0);
  /* Keep the beta label right-aligned in the title footer. */
  const char*version="2.0beta2";
  int version_len=len(version),version_x=230-version_len*4;
  for(int i=0;i<version_len;i++)for(int y=0;y<6;y++)for(int x=0;x<4;x++)
   if(font6[(u8)version[i]*6+y]&(128>>x))pixel(version_x+i*4+x,122+y,0);
 }
}
static void menu(void){
 const char*title_items[4]={"Играть","Справка","Рекорды","Об авторах"};
 const char*pause_items[4]={"Продолжить","Справка","Об авторах","Начать заново"};
 int count=4;
 rect(0,0,240,160,7);border(3,3,234,143,0);centered(8,ui.origin==TITLE?"МЕНЮ":"ПАУЗА",0,0);
 for(int i=0;i<count;i++){
  int y=38+i*24,selected=i==ui.choice;
  rect(20,y-3,200,22,selected?8:7);if(selected)border(20,y-3,200,22,0);
  centered(y,ui.origin==TITLE?title_items[i]:pause_items[i],0,selected?15:0);
 }
 centered(151,menu_button()==SELECT?"A: Подтвердить B/SELECT: Назад":"A: Подтвердить B/START: Назад",1,0);
}
static void help(void){
 static const char*commands[7]={"Крестовина: Перемещение","A: Подтвердить / Далее","B: Назад / Стереть","START: Меню / Пауза","L: Включить / Выключить звук","Имя: R пробел, SELECT меню","Имя: START - сохранить"};
 rect(0,0,240,160,7);border(3,3,234,143,0);centered(5,"УПРАВЛЕНИЕ",0,0);
 for(int i=0;i<7;i++)text(8,25+i*16,commands[i],0,0);
 centered(151,menu_button()==SELECT?"B / SELECT: Назад":"B / START: Назад",1,0);
}
static void restart_confirm(void){
 const char*items[2]={"Вернуться в меню","Начать заново"};
 rect(0,0,240,160,7);border(3,3,234,143,0);
 centered(8,"Начать заново?",0,0);
 centered(45,"Текущая игра будет потеряна",0,0);
 for(int i=0;i<2;i++){
  int y=86+i*26,selected=ui.confirm==i;
  rect(20,y-3,200,22,selected?8:7);if(selected)border(20,y-3,200,22,0);
  centered(y,items[i],0,selected?15:0);
 }
 centered(151,menu_button()==SELECT?"A: Подтвердить B/SELECT: Назад":"A: Подтвердить B/START: Назад",1,0);
}
static void footer(void){
 const char*t=0;
 if((game.mode==ROUND_END&&!(mp.humans==1&&human(game.player)&&game.round==2))||
    (game.mode==GAME_OVER&&game.deal!=6)||
    (game.mode==CASH&&cash.drawn==cash.total))t="A: Продолжить";
 if(human(game.player)){
  if(game.mode==LETTER)t="A: Выбрать букву";
  if(game.mode==PLUS)t="A: Открыть букву";
  if(game.mode==CHEST)t="A: Выбрать шкатулку";
 }
 if(game.mode==SOLVE)t=game.solve_pos==len(word())?"A: Назвать слово  B: Стереть":"A: Буква  B: Стереть";
 if(t||mp.humans==1){int y=152;rect(0,y,240,160-y,7);if(t)centered(y,t,1,0);}
}
static void mute_icon(void){
 if(sound_on)return;
 /* 12x10 white speaker/slash on a contrasting 14x12 backing. */
 rect(1,1,14,12,8);rect(2,5,3,4,15);
 for(int i=0;i<4;i++)rect(5+i,5-i,1,4+i*2,15);
 for(int i=0;i<10;i++){rect(12-i,2+i,3,1,8);pixel(13-i,2+i,15);}
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
static void certificate_base(void){
 int left=(240-certificate_logos[0].w-certificate_logos[1].w)/2;
 rect(0,0,240,160,7);
 for(int i=0;i<2;i++){
  const Sprite*s=&certificate_logos[i];
  image(s,left,0,7);
  left+=s->w;
 }
 line(4,47,232,1);
}
static void dos_author(void){
 certificate_base();int y=certificate_paragraph(50,msg_4099,0,0,0);
 certificate_paragraph(y,msg_40d8,0,0,0);
}
static void gba_author(void){
 rect(0,0,240,160,7);
 rect(8,24,111,111,15);
 for(int y=0;y<29;y++)for(int x=0;x<29;x++){
  unsigned bit=y*29+x;if(channel_qr[bit/8]&(1u<<(bit%8)))rect(20+x*3,36+y*3,3,3,0);
 }
 text(128,34,"GBA-версия от",0,0);
 text(128,65,"Ретрогейминг",0,0);text(128,82,"на балконе",0,0);
 centered(140,"t.me/RetroGamingNaBalkone",1,0);
}
static void page_footer(int page,int total){
 rect(0,151,240,9,7);text(4,152,game.mode==GIFT_PAGES&&page==0?"A: Продолжить":"A: Далее  B: Назад",1,0);
 glyph(208,152,'1'+page,1,0);glyph(216,152,'/',1,0);glyph(224,152,'0'+total,1,0);
}
static void authors(void){
 if(ui.author_page)gba_author();else dos_author();
 page_footer(ui.author_page,2);
}
static void gift_certificate(void){
 /* 1000:47bd / 42b4: original pages followed by the GBA attribution. */
 if(scene.gift_page>=2){if(scene.gift_page==2)dos_author();else gba_author();page_footer(scene.gift_page,4);return;}
 certificate_base();
 int y=50;
 if(scene.gift_page==0){
  if(scene.gift_final){
   char score[12],reverse[12];int n=0;unsigned value=game.score[mp.humans>1?game.player:2];
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
 }
 page_footer(scene.gift_page,4);
}
static void setup_player_heading(void){
 if(mp.link){centered(7,"ВАШ ИГРОК",0,0);return;}
 text(72,7,"ИГРОК",0,0);glyph(120,7,'1'+(mp.edit+1)%3,0,0);
 text(136,7,"ИЗ",0,0);glyph(160,7,'0'+mp.humans,0,0);
}
static int standing_value(int who,int before){
 if(prefs.rule!=MP_WINS)return before?match.start[who]:game.score[who];
 /* Settlement awards exactly one win in an ordinary solved round. */
 return match.wins[who]-(before&&match.settled&&!match.shootout&&match.round_winner==who);
}
static int standing_place(int who,int before){
 int place=0,value=standing_value(who,before);
 for(int p=0;p<3;p++){
  int other=standing_value(p,before);
  if(other>value||(other==value&&player_number(p)<player_number(who)))place++;
 }
 return place;
}
static int final_place(int who){
 /* A shootout is won by solving the word, not by its accumulated points. */
 if(who==match.winner)return 0;
 int place=1,value=standing_value(who,0);
 for(int p=0;p<3;p++)if(p!=match.winner){
  int other=standing_value(p,0);
  if(other>value||(other==value&&player_number(p)<player_number(who)))place++;
 }
 return place;
}
static void standings(int final){
 rect(0,0,240,160,7);border(3,3,234,145,0);
 centered(12,final?"ПОБЕДИТЕЛЬ ИГРЫ":"ПРОМЕЖУТОЧНЫЕ ИТОГИ",1,0);
 centered(30,final?player_name(match.winner):mp_stage(),0,0);
 compact_text(12,64,"МЕСТО",30,0);text(50,64,"ИМЯ",1,0);
 if(prefs.rule==MP_WINS)compact_text(140,64,"ПОБЕД",30,0);
 text(184,64,"СЧЕТ",1,0);
 for(int who=0;who<3;who++){
  int place=final?final_place(who):standing_place(who,0),y=80+place*22;
  number(22,y,place+1,0,0);text(50,y,player_name(who),0,0);
  if(prefs.rule==MP_WINS)number(152,y,match.wins[who],0,0);
  number(184,y,game.score[who],0,0);
  int previous=standing_place(who,1);
  if(!final&&(game.round>0||match.shootout)&&previous!=place)for(int row=0;row<5;row++){
   int width=1+row*2,ty=y+3+(previous>place?row:4-row);
   rect(37-row,ty,width,1,0);
  }
 }
 centered(151,"A: Продолжить",1,0);
}
static void render(void){
 if(game.mode==MP_SUMMARY){
  standings(match.next==2);return;
 }
 if(game.mode==MP_OPTION_HELP){
  const char*titles[]={"СЛОВАРЬ","ДВЕ ШКАТУЛКИ","ПЕРСОНАЖИ","ПРАВИЛА",prefs.rule==MP_WINS?"ПОБЕД ДЛЯ ВЫИГРЫША":"ЧИСЛО РАУНДОВ","НАЧАТЬ ИГРУ"};
  const char*rules[]={"По очкам","По очкам с риском","По победам"};
  int setting=prefs.choice,value=option_help_value,count=setting<3?2:setting==3?3:1;
  rect(0,0,240,160,7);border(3,3,234,143,0);centered(8,titles[setting],0,0);
  centered(29,setting<3?(value?"Версия 2":"Версия 1"):setting==3?rules[value]:setting==4?(prefs.rule==MP_WINS?"От 1 до 5":"От 1 до 8"):"Подготовка участников",0,0);
  if(count>1){text(12,29,"<",0,0);text(220,29,">",0,0);if(value==option_value())centered(47,"Выбрано",1,0);}
  const char*lines[5]={"","","","",""};
  if(setting==0){
   lines[0]=value?"686 слов из второй игры.":"495 слов из первой игры.";
   if(value){lines[1]="Включает темы Кулинария";lines[2]="и Напитки.";}
  }else if(setting==1){
   lines[0]="За 3 верные буквы подряд";lines[1]="можно выбрать шкатулку.";
   lines[2]=value?"Плюс идет в зачет серии.":"Плюс не идет в зачет серии.";
  }else if(setting==2){
   lines[0]=value?"8 персонажей второй игры.":"6 персонажей первой игры.";
   lines[1]=value?"Добавлены Фрекен Бок":"Графика первой игры.";
   if(value){lines[2]="и Багира. Новая графика";lines[3]="прежних героев.";}
  }else if(setting==3){
   if(value==MP_POINTS){lines[0]="Максимальный общий счет.";lines[1]="Банкрот: потеря за раунд.";lines[2]="x2/x4: очки этого раунда.";lines[3]="Ничья: перестрелка.";}
   else if(value==MP_RISK){lines[0]="Максимальный общий счет.";lines[1]="Банкрот: весь счет в ноль.";lines[2]="x2/x4: весь общий счет.";lines[3]="Ничья: перестрелка.";}
   else{lines[0]="Первый до N побед.";lines[1]="Очки не решают исход.";lines[2]="Банкрот: счет 0, победы целы.";lines[3]="x2/x4: весь общий счет.";lines[4]="Без перестрелки.";}
  }else if(setting==4){
   if(prefs.rule==MP_WINS){lines[0]="Побед для выигрыша матча.";lines[1]="По умолчанию: 3 победы.";lines[2]="Все выбыли - без победы.";lines[3]="Играем до цели.";}
   else{lines[0]="Число основных раундов.";lines[1]="Перестрелки не входят.";}
  }else{lines[0]="Далее: имена и аватары.";lines[1]=mp.link?"Затем - ожидание по кабелю.":"Затем начинается партия.";}
  for(int i=0;i<5;i++)centered(60+i*16,lines[i],0,0);
  centered(151,count>1?"< / >: Варианты  B: Назад":"B: Назад",1,0);return;
 }
 if(game.mode==MP_OPTIONS&&mp.humans>1){
  rect(0,0,240,160,7);border(3,3,234,138,0);centered(6,"ПАРАМЕТРЫ ИГРЫ",0,0);
  const char*rules[]={"По очкам","По очкам с риском","По победам"};
  const char*items[]={prefs.dictionary?"Словарь: v2":"Словарь: v1",prefs.plus?"Две шкатулки: v2":"Две шкатулки: v1",prefs.characters?"Персонажи: v2":"Персонажи: v1","Правила","Раундов: 3","НАЧАТЬ ИГРУ"};
  const int rows[]={74,91,108,24,57,125};
  for(int i=0;i<6;i++){
   int y=rows[i],selected=prefs.choice==i;u8 color=selected?15:0;
   if(selected){rect(12,y-2,216,i==3?33:18,8);border(12,y-2,216,i==3?33:18,0);}
   if(i==4){if(prefs.rule==MP_WINS){text(32,y,"Побед для выигрыша:",0,color);glyph(192,y,'0'+prefs.rounds,0,color);}else{text(80,y,"Раундов:",0,color);glyph(152,y,'0'+prefs.rounds,0,color);}}
   else centered(y,items[i],0,color);
   if(i==3)centered(y+15,rules[prefs.rule],0,color);
  }
  centered(143,"SELECT: Описание",1,0);
  centered(152,prefs.choice==5?"A: Играть  B: Назад":"A: Изменить  B: Назад",1,0);return;
 }

 if(game.mode==MP_OPTIONS){
  rect(0,0,240,160,7);border(3,3,234,148,0);centered(7,"ПАРАМЕТРЫ ИГРЫ",0,0);
  const char*items[]={prefs.dictionary?"Словарь: v2":"Словарь: v1",prefs.plus?"Две шкатулки: v2":"Две шкатулки: v1",prefs.characters?"Персонажи: v2":"Персонажи: v1"};
  for(int i=0;i<3;i++){
   int y=26+i*20,selected=prefs.choice==i;
   rect(20,y-2,200,20,selected?8:7);if(selected)border(20,y-2,200,20,0);
   centered(y,items[i],0,selected?15:0);
  }
  if(prefs.choice==0){
   centered(88,prefs.dictionary?"686 слов, включая темы":"495 слов из первой игры",0,0);
   if(prefs.dictionary)centered(104,"Кулинария и Напитки",0,0);
  }else if(prefs.choice==1){
   centered(88,"За 3 верные буквы подряд",0,0);
   centered(104,prefs.plus?"Плюс идет в зачет":"Плюс не идет в зачет",0,0);
  }else if(prefs.choice==2){
   centered(88,prefs.characters?"Добавлены Фрекен Бок и Багира":"6 персонажей",0,0);
   centered(104,prefs.characters?"Новая графика прежних героев":"Графика первой игры",0,0);
  }
  line(20,121,200,8);
  rect(20,125,200,22,prefs.choice==3?8:7);
  if(prefs.choice==3)border(20,125,200,22,0);
  centered(129,"НАЧАТЬ ИГРУ",0,prefs.choice==3?15:0);
  centered(151,prefs.choice==3?"A: Играть  B: Назад":"A: Изменить  B: Назад",1,0);return;
 }
 if(game.mode==MP_SETUP){
  rect(0,0,240,160,7);border(3,3,234,143,0);centered(8,"Режим игры",0,0);
  const char*options[]={"Один игрок","Локальный мультиплеер","Мультиплеер по кабелю","Проверка связи"};
  for(int i=0;i<4;i++){int y=34+i*26;if(mp.choice==i){rect(20,y-3,200,22,8);border(20,y-3,200,22,0);}centered(y,options[i],0,mp.choice==i?15:0);}
  centered(151,"A: Выбрать  B: Назад",1,0);return;
 }
 if(game.mode==MP_CONNECT){
  rect(0,0,240,160,7);border(3,3,234,143,0);centered(8,"Игра по кабелю",0,0);
  const char*options[]={"Создать игру","Подключиться"};
  for(int i=0;i<2;i++){int y=40+i*28;if(game.choice==i){rect(20,y-3,200,22,8);border(20,y-3,200,22,0);}centered(y,options[i],0,game.choice==i?15:0);}
  centered(101,game.choice?"Правила и графику задает":"Создатель выбирает правила",1,0);
  centered(114,game.choice?"создатель игры":"и использует главный разъем",1,0);
  centered(151,"A: Выбрать  B: Назад",1,0);return;
 }
 if(game.mode==LINK_TEST){
  /* Freeze one completed-transfer snapshot; drawing must not mix words
   * from different IRQs or compare a new TX against an older RX. */
  LinkTest test;unsigned hardware_errors,data_errors,changed;u16 completed_tx;
  u16 ime=REG16(0x04000208);REG16(0x04000208)=0;
  link_copy(&test,&link_test,sizeof test);hardware_errors=link_test_hardware_errors;
  data_errors=link_test_data_errors;changed=link_test_changed;completed_tx=link_test_completed_tx;
  REG16(0x04000208)=ime;
  rect(0,0,240,160,7);border(3,3,234,143,0);
  const char*baud[]={"9600","38400","57600","115200"};
  const char*pace[]={"0.25","1","4","16"};
  if(!link_test_details){
   centered(8,"Проверка связи",0,0);
   const char*status=!link_test_ran?"Готов к проверке":test.timed_out?(test.peers?"Обмен прервался":"Нет ответа на запуск"):changed?"Состав GBA изменился":test.errors?"Обнаружены ошибки":!test.running?"Тест остановлен":!test.peers?"Ждем другую GBA":"Обмен идет без ошибок";
   centered(29,status,0,test.errors||test.timed_out?4:0);
   if(!link_test_ran){
    centered(51,"Откройте тест на всех GBA",1,0);
    centered(65,"Нажмите A на каждой консоли",1,0);
   }else if(!test.peers){
    centered(51,"Нет ответа от второй GBA",1,0);
    centered(65,"Запустите этот тест и на нем",1,0);
   }else{
    centered(48,test.role==0?"Эта консоль - ведущая":"Эта консоль - клиент",1,0);
    text(20,62,"Участников:",1,0);number(108,62,test.peers,1,0);
    text(140,62,"Секунд:",1,0);number(196,62,link_test_seconds,1,0);
   }
   if(link_test_ran){
    text(20,78,"Проверено:",1,0);number(108,78,test.passed,1,0);
    text(20,92,"Искажения:",1,0);number(108,92,data_errors,1,0);
    text(140,92,"Сбои:",1,0);number(188,92,hardware_errors,1,0);
   }
   text(20,108,"Бод:",1,0);text(52,108,baud[test.baud],1,0);
   text(128,108,"Пауза:",1,0);text(176,108,pace[test.pace],1,0);text(212,108,"мс",1,0);
   centered(124,test.running?"A: Стоп  B: Назад":"L/R: Бод  Вверх/вниз: Пауза",1,0);
   centered(138,"SELECT: подробности",1,0);
   centered(151,test.running?"Оставьте тест на 30 секунд":"A: Старт  B: Назад",1,0);return;
  }
  centered(6,"Данные диагностики",0,0);
  text(10,24,"ID:",1,0);number(34,24,test.role+1,1,0);
  text(64,24,"GBA:",1,0);number(96,24,test.peers,1,0);
  text(128,24,"SIO:",1,0);number(160,24,test.status,1,0);
  text(10,39,"RX:",1,0);number(42,39,test.transfers,1,0);
  text(128,39,"OK:",1,0);number(160,39,test.passed,1,0);
  text(10,54,"ERR:",1,0);number(42,54,test.errors,1,0);
  text(128,54,"WAIT:",1,0);number(168,54,test.repeats,1,0);
  text(10,69,"TX:",1,0);number(42,69,completed_tx,1,0);
  text(128,69,"TO:",1,0);number(160,69,test.timeouts,1,0);
  for(int i=0;i<4;i++){
   int x=10+(i&1)*118,y=84+(i/2)*15;
   number(x,y,i+1,1,0);text(x+8,y,":",1,0);number(x+24,y,test.rx[i],1,0);
  }
  centered(117,"WAIT: ожидания, не ошибки",1,0);
  centered(132,"SELECT: результат  B: Назад",1,0);
  centered(151,test.running?"A: Стоп с сохранением данных":"A: Начать заново",1,0);return;
 }
 if(game.mode==MP_COUNT){
  rect(0,0,240,160,7);border(3,3,234,143,0);centered(8,"Число игроков",0,0);
  centered(31,mp.link?"Мультиплеер по кабелю":"Локальный мультиплеер",0,0);
  for(int i=0;i<2;i++){int y=60+i*27,selected=mp.humans==i+2;if(selected){rect(20,y-3,200,22,8);border(20,y-3,200,22,0);}centered(y,i?"3 игрока":"2 игрока",0,selected?15:0);}
  centered(121,mp.humans==2?"Третий - компьютер":"Все трое - люди",0,0);
  centered(151,"A: Выбрать  B: Назад",1,0);return;
 }
 if(game.mode==MP_AVATAR){
  rect(0,0,240,160,7);border(3,3,234,143,0);
  setup_player_heading();centered(27,player_name(mp.edit),0,0);
  int count=prefs.characters?9:7,columns=(count+1)/2;
  for(int i=0;i<count;i++){
   int row=i/columns,length=row?count-columns:columns;
   int x=(240-(length*44-4))/2+(i%columns)*44,y=44+row*50;
   int selected=i==avatars[mp.edit];
   rect(x,y,40,48,selected?8:7);border(x,y,40,48,selected?15:0);
   const Sprite*portrait=avatar_portrait(i);
   image(portrait,x+(40-portrait->w)/2,y+(48-portrait->h)/2,2);
  }
  centered(151,link_active&&!link_create?"A: Готово  B: Отмена":"A: Готово  B: К имени",1,0);return;
 }
 if(game.mode==MP_NAME){
  rect(0,0,240,160,7);setup_player_heading();
  if(mp_name_error){border(8,35,224,95,0);centered(48,mp_name_error==2?"Имя не может быть пустым":"Имя уже занято",0,0);centered(73,(const char*)game.answer,0,0);centered(105,"A / B: Изменить имя",1,0);return;}
  centered(32,"Введите имя",0,0);text(70,60,(const char*)game.answer,0,0);centered(75,"R: Пробел START: Готово",1,0);keyboard();centered(151,"A: Буква B: Стереть",1,0);return;
 }
 if(game.mode==MP_PASS){rect(0,0,240,160,7);border(3,3,234,143,0);centered(40,"Передайте GBA игроку",0,0);centered(70,player_name(game.player),0,0);centered(115,"A: Готов",0,0);return;}
 if(game.mode==MP_LOBBY){
  rect(0,0,240,160,7);border(3,3,234,143,0);centered(16,"Мультиплеер по кабелю",0,0);
  centered(37,link_connected==2?"2 игрока + компьютер":link_connected==3?"3 игрока":"Подключите остальные GBA",0,0);
  if(link_connected>=2)for(int i=0;i<link_connected;i++){
   int p=(i+2)%3;number(36,57+i*17,i+1,0,0);text(60,57+i*17,mp.names[p],0,p==mp.local?1:0);
  }
  if(link_snapshot.name_conflicts||link_snapshot.name_editing)centered(108,"Ждем исправления имени",1,0);
  else if(link_snapshot.avatar_editing)centered(108,"Ждем выбора аватаров",1,0);
  centered(122,link_connected<2?"Ожидание участников...":(link_snapshot.name_conflicts||link_snapshot.name_editing)?"Имена должны различаться":link_snapshot.avatar_editing?"Участники готовятся":mp.local==2?"START: Начать игру":"Ждем ведущего игрока",0,0);
  centered(151,"B: Отменить ожидание",1,0);return;
 }
 if(game.mode==MP_ERROR&&link_role_error){
  rect(0,0,240,160,7);border(3,3,234,143,0);centered(19,"Проверьте роли игроков",0,0);
  centered(48,link_role_error==1?"Нет создателя игры":link_role_error==2?"Создатель должен быть один":"Создатель на другом разъеме",1,0);
  centered(73,"Главный разъем: Создать игру",1,0);
  centered(90,"Остальные: Подключиться",1,0);
  centered(121,"B: Выбрать роль заново",1,0);return;
 }
 if(game.mode==MP_ERROR){rect(0,0,240,160,7);border(3,3,234,143,0);centered(30,"Связь потеряна",0,0);centered(59,"Одинаковая ROM и режим",1,0);centered(76,"Кабель GBA на 2/3 игроков",1,0);text(24,90,"Код:",1,0);number(64,90,link_error_stage,1,0);text(88,90,"SIO:",1,0);number(128,90,link_error_status,1,0);text(24,104,"RX:",1,0);number(56,104,link_error_received,1,0);text(112,104,"OK:",1,0);number(144,104,link_error_expected,1,0);text(24,118,"CRC:",1,0);number(64,118,link_retries,1,0);text(112,118,"W:",1,0);number(144,118,link_wire_word,1,0);centered(137,"B: В меню",1,0);return;}


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
 if(game.mode==MENU){menu();return;}
 if(game.mode==RESTART_CONFIRM){restart_confirm();return;}
 if(game.mode==HELP){help();return;}
 if(game.mode==AUTHORS){authors();return;}
 if(game.mode==RECORDS){
  rect(0,0,240,160,7);centered(0,msg_478c,0,1);centered(14,msg_479e,0,1);
  for(int i=0;i<8;i++){number(8,32+i*15,i+1,1,1);text(28,32+i*15,record_names[i],1,0);number(152,32+i*15,record_scores[i],1,0);}
  centered(148,"A / B: Назад",1,1);return;
 }
 if(game.mode==NAME){rect(0,0,240,160,7);centered(5,"8 лучших игроков",0,1);centered(29,"Ваше имя:",0,0);text(70,60,(const char*)game.answer,0,0);centered(75,"R: Пробел  START: Сохранить",1,0);keyboard();centered(151,"A: Буква  B: Стереть",1,0);return;}
 if(game.mode==SOLVE){rect(0,0,240,160,0);centered(8,msg_f20,0,15);keyboard();footer();return;}
 /* While the credits enter, the uncovered stage is still visible. Once
  * they fill the display, no hidden stage objects need to be drawn. */
 if(game.mode!=CREDITS||scene.now-scene.start<40){studio();board();wheel();people();}
 if(game.mode==CREDITS){
  int top=160-(int)((scene.now-scene.start)*4);if(top<0)top=0;
  rect(0,top,240,160,1);
  const char*lines[10]={msg_4ebd,msg_4ecf,msg_4ee3,msg_4ef5,msg_4f08,msg_4f18,msg_4f2a,msg_4f38,msg_4f47,msg_4f5a};
  for(int i=0;i<10;i++)centered(top+4+i*14,lines[i],0,14);
  centered(top+151,"A: Следующий раунд",1,14);
  return;
 }
 if(game.mode==REVEAL){
  int id=(game.sector_value!=100&&scene.now-scene.start<MESSAGE_TICKS)||scene.actor_stop?23:((scene.now/6)%4==0?24:(scene.now/6)%4==2?25:26);
  /* Both side walls are foreground boundaries: the figure passes behind them. */
  const Sprite*s=&sprites_half[id];
  for(int y=0;y<s->h;y++)for(int x=0;x<s->w;x++){
   int px=scene.actor_x+x;u8 color=s->data[y*s->w+x];
   if(px>=15&&px<225&&color!=2)pixel(px,12+y,color);
  }
 }
 /* Keep names during the host's introduction; hide only during the walk,
  * including stops at letters. Plus starts walking without that delay. */
 int walking=game.mode==REVEAL&&(game.sector_value==100||scene.now-scene.start>=MESSAGE_TICKS);
 if(mp.humans>1&&!walking)for(int side=0;side<2;side++){
  int who=perspective(side);
  if(game.mode!=INTRO||scene.phase>=player_number(who))player_name_label(who,side);
 }
 if(game.mode==CHEST||game.mode==AI_CHEST){
  int phase=(scene.now-scene.speech_at)/6;
  int animate=game.mode==CHEST&&scene.now-scene.speech_at<90;
  int y=mp.humans>1?90:96;
  image(&sprites[animate&&!(phase&1)?37:36],18,y,7);image(&sprites[animate&&(phase&1)?37:36],115,y,7);
  if(human(game.player)||game.mode==AI_CHEST)border(game.choice?113:16,mp.humans>1?88:94,40,42,14);
 }
 if(game.mode==RESULT&&scene.now<scene.chest_until){
  int y=mp.humans>1?90:96;
  image(&sprites[scene.chest_money?38:37],game.choice?115:18,y,7);image(&sprites[36],game.choice?18:115,y,7);
 }
 if(game.mode==PRIZE){
  /* Both alternatives stay visible; a shared frame makes this one switch. */
  int y=122;
  rect(6,y,150,25,0);
  for(int option=0;option<2;option++){
   int x=option?81:7,w=option?74:73,selected=game.choice==option;
   const char*t=option?(game.deal?"ПРИЗ":"ИГРАЕМ"):(game.deal?"ДЕНЬГИ":"ПРИЗ");
   rect(x,y+1,w,23,selected?1:7);
   label_center(x,y+5,w,t,0,selected?15:0);
  }
 }
 if(game.mode==TURN&&human(game.player)){
  int y=110;
  rect(6,y,150,37,0);
  for(int option=0;option<2;option++){
   int x=option?81:7,w=option?74:73,selected=game.choice==option;
   rect(x,y+1,w,35,selected?1:7);
   label_center(x,112,w,option?"Кручу":"Скажу",0,selected?15:0);label_center(x,129,w,option?"БАРАБАН":"СЛОВО",0,selected?15:0);
  }
 }
 if(game.keyboard&&game.mode==LETTER)keyboard();
 /* Speech is the final scene overlay and cannot be overwritten by the wheel. */
 speech();multiplayer_panel();footer();
}
