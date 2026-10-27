
/* 1000:0000 FUN_1000_0000 */

void __cdecl16near FUN_1000_0000(void)

{
  FUN_174b_0a35();
  FUN_1ad9_00d8();
  return;
}



/* 1000:0053 pole_load_resources */

void __cdecl16near pole_load_resources(void)

{
  byte bVar1;
  ulong uVar2;
  ulong uVar3;
  int iVar4;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  bool bVar5;
  undefined4 uVar6;
  undefined1 *puVar7;
  undefined2 uVar8;
  undefined2 uVar9;
  undefined2 uVar10;
  undefined1 local_306 [252];
  int local_20a;
  int local_204;
  undefined1 local_202 [128];
  undefined1 local_182 [256];
  byte local_82 [128];
  
  FUN_1ad9_0644(0xff,local_182,unaff_SS,0x16,0x1000);
  FUN_1ad9_1779(local_182,unaff_SS,local_202,unaff_SS);
  FUN_1ad9_17a7(0x80,local_202,unaff_SS);
  iVar4 = FUN_1ad9_0207();
  if (iVar4 != 0) {
    uVar9 = 0xef8;
    puVar7 = local_306;
    uVar8 = unaff_SS;
    uVar10 = unaff_DS;
    FUN_1ad9_062a(0x1f,0x1ad9);
    FUN_1ad9_06b7(local_182,unaff_SS);
    FUN_1ad9_06b7(0x25,0x1ad9);
    FUN_1ad9_173b(0,puVar7,uVar8);
    FUN_1ad9_16be(uVar9,uVar10);
    FUN_1ad9_020e();
    FUN_1ad9_00d8();
  }
  FUN_1ad9_1892(0,0,1,local_82,unaff_SS,local_202,unaff_SS);
  FUN_1ad9_020e();
  _local_20a = (ulong)CONCAT12(local_82[0],local_20a);
  if (local_82[0] != 0) {
    local_204 = 1;
    while( true ) {
      bVar1 = local_82[local_204];
      uVar6 = FUN_1ad9_0329((uint)bVar1 << 7);
      iVar4 = (local_204 + -1) * 4;
      *(undefined2 *)(iVar4 + 0xa08) = (int)uVar6;
      *(undefined2 *)(iVar4 + 0xa0a) = (int)((ulong)uVar6 >> 0x10);
      uVar6 = *(undefined4 *)((local_204 + -1) * 4 + 0xa08);
      FUN_1ad9_1892(0,0,(uint)bVar1,(int)uVar6,(int)((ulong)uVar6 >> 0x10),local_202,unaff_SS);
      FUN_1ad9_020e();
      uVar3 = _local_20a;
      uVar2 = _local_20a >> 0x10;
      bVar5 = local_204 == (int)uVar2;
      _local_20a = uVar3;
      if (bVar5) break;
      local_204 = local_204 + 1;
    }
  }
  FUN_1ad9_1828(local_202,unaff_SS);
  FUN_1ad9_020e();
  FUN_1ad9_0644(0xff,local_182,unaff_SS,0x30,0x1ad9);
  FUN_1ad9_1779(local_182,unaff_SS,local_202,unaff_SS);
  FUN_1ad9_17a7(0x80,local_202,unaff_SS);
  iVar4 = FUN_1ad9_0207();
  if (iVar4 != 0) {
    uVar9 = 0xef8;
    puVar7 = local_306;
    uVar8 = unaff_SS;
    uVar10 = unaff_DS;
    FUN_1ad9_062a(0x1f,0x1ad9);
    FUN_1ad9_06b7(local_182,unaff_SS);
    FUN_1ad9_06b7(0x25,0x1ad9);
    FUN_1ad9_173b(0,puVar7,uVar8);
    FUN_1ad9_16be(uVar9,uVar10);
    FUN_1ad9_020e();
    FUN_1ad9_00d8();
  }
  uVar6 = FUN_1ad9_0329(0x800);
  *(undefined2 *)0xbf4 = (int)uVar6;
  *(undefined2 *)0xbf6 = (int)((ulong)uVar6 >> 0x10);
  FUN_1ad9_1892(&local_204,unaff_SS,0xc,(int)*(undefined4 *)0xbf4,
                (int)((ulong)*(undefined4 *)0xbf4 >> 0x10),local_202,unaff_SS);
  FUN_1ad9_020e();
  uVar6 = FUN_1ad9_0329(0x800);
  *(undefined2 *)0xbf8 = (int)uVar6;
  *(undefined2 *)0xbfa = (int)((ulong)uVar6 >> 0x10);
  FUN_1ad9_1892(&local_204,unaff_SS,0x10,(int)*(undefined4 *)0xbf8,
                (int)((ulong)*(undefined4 *)0xbf8 >> 0x10),local_202,unaff_SS);
  FUN_1ad9_020e();
  uVar6 = FUN_1ad9_0329(0xe00);
  *(undefined2 *)0xbfc = (int)uVar6;
  *(undefined2 *)0xbfe = (int)((ulong)uVar6 >> 0x10);
  FUN_1ad9_1892(&local_204,unaff_SS,0x1c,(int)*(undefined4 *)0xbfc,
                (int)((ulong)*(undefined4 *)0xbfc >> 0x10),local_202,unaff_SS);
  FUN_1ad9_020e();
  FUN_1ad9_1828(local_202,unaff_SS);
  FUN_1ad9_020e();
  FUN_1ad9_0644(0xff,local_182,unaff_SS,0x39,0x1ad9);
  FUN_1ad9_1779(local_182,unaff_SS,0x7cc,unaff_DS);
  FUN_1ad9_17a7(0xd,0x7cc,unaff_DS);
  iVar4 = FUN_1ad9_0207();
  if (iVar4 == 0) {
    local_204 = 1;
    while( true ) {
      FUN_1ad9_185c(local_204 * 0xd + 0x55d,unaff_DS);
      FUN_1ad9_020e();
      if (local_204 == 8) break;
      local_204 = local_204 + 1;
    }
    FUN_1ad9_1828(0x7cc,unaff_DS);
    FUN_1ad9_020e();
  }
  else {
    local_204 = 1;
    while( true ) {
      iVar4 = local_204 * 0xd + 0x55d;
      _local_20a = CONCAT22(unaff_DS,iVar4);
      if ((bool)((byte)local_204 & 1)) {
        FUN_1ad9_0644(10,iVar4,unaff_DS,0x42,0x1ad9);
      }
      else {
        FUN_1ad9_0644(10,iVar4,unaff_DS,0x4a,0x1ad9);
      }
      *(int *)((int)_local_20a + 0xb) = local_204 * -0xf + 0x87;
      if (local_204 == 8) break;
      local_204 = local_204 + 1;
    }
  }
  return;
}



/* 1000:03a5 pole_draw_font */

/* WARNING: Removing unreachable block (ram,0x0001048f) */

void pole_draw_font(undefined4 param_1,int param_2,int param_3,undefined1 param_4,int param_5,
                   uint param_6,undefined4 param_7)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  undefined2 uVar5;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  byte local_111;
  int local_10c;
  uint local_10a;
  byte local_102 [256];
  
  FUN_1ad9_0644(0xff,local_102,unaff_SS,(int)param_7,(int)((ulong)param_7 >> 0x10));
  out(0x3ce,5);
  out(0x3cf,2);
  if (local_102[0] != 0) {
    local_10a = 1;
    while( true ) {
      bVar1 = (byte)param_6 & 7;
      bVar2 = 8 - bVar1;
      iVar3 = param_5 * 0x50 + (param_6 >> 3);
      iVar4 = FUN_1ad9_0279();
      local_10c = 0;
      while( true ) {
        if (param_3 == 5) {
          local_111 = *(byte *)((int)*(undefined4 *)0xbf4 + iVar4 + local_10c);
        }
        else if (param_3 == 7) {
          local_111 = *(byte *)((int)*(undefined4 *)0xbf8 + iVar4 + local_10c);
        }
        else {
          local_111 = *(byte *)((int)*(undefined4 *)0xbfc + iVar4 + local_10c);
        }
        out(0x3ce,8);
        out(0x3cf,local_111 >> bVar1);
        uVar5 = (undefined2)((ulong)param_1 >> 0x10);
        FUN_1ad9_19d9(param_4,1,(int)param_1 + local_10c * 0x50 + iVar3,uVar5);
        if (bVar2 != 8) {
          out(0x3ce,8);
          out(0x3cf,local_111 << (bVar2 & 0x1f));
          FUN_1ad9_19d9(param_4,1,(int)param_1 + local_10c * 0x50 + iVar3 + 1,uVar5);
        }
        if (local_10c == param_3) break;
        local_10c = local_10c + 1;
      }
      param_6 = param_6 + param_2;
      if (local_10a == local_102[0]) break;
      local_10a = local_10a + 1;
    }
  }
  return;
}



/* 1000:05ca pole_init_ega_palette */

void __cdecl16near pole_init_ega_palette(void)

{
  int iVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  
  uVar2 = 0x174b;
  iVar1 = FUN_174b_016f(0x5fb5,0x1000);
  if (iVar1 < 0) {
    uVar2 = 0x1ad9;
    FUN_1ad9_00d8();
  }
  *(undefined2 *)0x96c = 3;
  *(undefined2 *)0x96a = 1;
  FUN_174b_0759(0x5c9,uVar2,0x96a,unaff_DS,0x96c,unaff_DS);
  FUN_174b_0d05(0x2e,6);
  FUN_174b_0d05(0x14,4);
  FUN_174b_0d05(0x27,5);
  *(undefined2 *)0x9f4 = 0;
  FUN_1a70_000b(0x9f4);
  if (*(int *)0x9f4 == 0) {
    *(undefined2 *)0x7b4 = 0;
  }
  else {
    *(undefined2 *)0x7b4 = 1;
  }
  if (0 < *(int *)0x7b4) {
    *(undefined2 *)0x9f4 = 2;
    FUN_1a70_000b(0x9f4);
    *(undefined2 *)0x9f4 = 7;
    *(undefined2 *)0x9f8 = 0;
    *(undefined2 *)0x9fa = 0x27f;
    FUN_1a70_000b(0x9f4);
  }
  return;
}



/* 1000:068b FUN_1000_068b */

void FUN_1000_068b(undefined1 param_1,undefined2 param_2,uint param_3,int param_4)

{
  uint uVar1;
  undefined2 local_4;
  
  out(0x3ce,5);
  out(0x3cf,2);
  out(0x3ce,8);
  out(0x3cf,0xff);
  FUN_1ad9_19d9(param_1,1,param_4,0xa000);
  out(0x3ce,5);
  out(0x3cf,1);
  FUN_1ad9_19b6(1,param_4,0xa000,param_4,0xa000);
  if (param_3 < 0x8000) {
    local_4 = 0;
    uVar1 = 0;
    while( true ) {
      FUN_1ad9_19d9(CONCAT11((char)(uVar1 >> 8),1),param_2,param_4,0xa000);
      param_4 = param_4 + 0x50;
      if (local_4 == param_3) break;
      uVar1 = local_4;
      local_4 = local_4 + 1;
    }
  }
  return;
}



/* 1000:0725 FUN_1000_0725 */

void FUN_1000_0725(undefined2 param_1,uint param_2,int param_3,int param_4)

{
  undefined2 local_4;
  
  out(0x3ce,5);
  out(0x3cf,1);
  if (param_2 < 0x8000) {
    local_4 = 0;
    while( true ) {
      FUN_1ad9_19b6(param_1,param_3,0xa000,param_4,0xa000);
      param_4 = param_4 + 0x50;
      param_3 = param_3 + 0x50;
      if (local_4 == param_2) break;
      local_4 = local_4 + 1;
    }
  }
  return;
}



/* 1000:077e FUN_1000_077e */

void __cdecl16near FUN_1000_077e(void)

{
  char cVar1;
  undefined1 uVar2;
  undefined2 unaff_DS;
  
  while( true ) {
    cVar1 = FUN_1a77_02fa();
    if (cVar1 == '\0') break;
    uVar2 = FUN_1a77_030c();
    *(undefined1 *)0x964 = uVar2;
  }
  if (0 < *(int *)0x7b4) {
    do {
      *(undefined2 *)0x9f4 = 3;
      FUN_1a70_000b(0x9f4);
    } while (*(int *)0x9f6 != 0);
  }
  return;
}



/* 1000:07b9 FUN_1000_07b9 */

void __cdecl16near FUN_1000_07b9(void)

{
  char cVar1;
  undefined1 uVar2;
  uint uVar3;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  int local_16;
  undefined1 local_14 [18];
  
  FUN_174b_0d49(local_14,unaff_SS);
  uVar3 = 0;
  local_16 = 0;
  while( true ) {
    uVar3 = FUN_174b_0d05(uVar3 & 0xff00,local_16);
    if (local_16 == 0xf) break;
    local_16 = local_16 + 1;
  }
  FUN_1000_077e();
  do {
    *(undefined2 *)0x9f6 = 0;
    if (0 < *(int *)0x7b4) {
      *(undefined2 *)0x9f4 = 3;
      FUN_1a70_000b(0x9f4);
    }
    *(undefined1 *)0x964 = 7;
    cVar1 = FUN_1a77_02fa();
    if (cVar1 != '\0') {
      uVar2 = FUN_1a77_030c();
      *(undefined1 *)0x964 = uVar2;
    }
    if (*(char *)0x964 == '\x1b') {
      FUN_1000_0000();
    }
    if (*(char *)0x964 == '\x13') {
      *(int *)0x862 = 1 - *(int *)0x862;
    }
  } while ((*(char *)0x964 != ' ') && (*(int *)0x9f6 != 1));
  *(undefined1 *)0x964 = 7;
  FUN_174b_0c5d(local_14,unaff_SS);
  return;
}



/* 1000:0858 FUN_1000_0858 */

void FUN_1000_0858(int param_1)

{
  char cVar1;
  undefined1 uVar2;
  undefined2 unaff_DS;
  
  FUN_1000_077e();
  do {
    if (0 < param_1) {
      param_1 = param_1 + -1;
    }
    pascal_delay_ms(0x32);
    *(undefined2 *)0x9f6 = 0;
    if (0 < *(int *)0x7b4) {
      *(undefined2 *)0x9f4 = 3;
      FUN_1a70_000b(0x9f4);
    }
    *(undefined1 *)0x964 = 7;
    cVar1 = FUN_1a77_02fa();
    if (cVar1 != '\0') {
      uVar2 = FUN_1a77_030c();
      *(undefined1 *)0x964 = uVar2;
    }
    if (*(char *)0x964 == '\x1b') {
      FUN_1000_0000();
    }
    if (*(char *)0x964 == '\x13') {
      *(int *)0x862 = 1 - *(int *)0x862;
    }
    if (*(char *)0x964 == '\t') {
      FUN_1000_07b9();
    }
  } while (((*(char *)0x964 != ' ') && (*(int *)0x9f6 != 1)) && (param_1 != 1));
  return;
}



/* 1000:08e4 pole_speaker_transition */

void __cdecl16near pole_speaker_transition(void)

{
  undefined2 uVar1;
  undefined2 local_4;
  
  local_4 = 1;
  while( true ) {
    pascal_random_bound(100);
    uVar1 = FUN_1ad9_0279();
    pc_speaker_sound_hz(uVar1);
    pascal_delay_ms(6 - local_4);
    pc_speaker_no_sound();
    pascal_delay_ms(1);
    if (local_4 == 6) break;
    local_4 = local_4 + 1;
  }
  return;
}



/* 1000:0936 FUN_1000_0936 */

void __cdecl16near FUN_1000_0936(void)

{
  undefined2 unaff_DS;
  
  FUN_1000_0725(0x15,0xbe,0x2bfb,0xa8fb);
  pole_speaker_transition();
  pole_blit_rle(0x10,0xad,0x1ff,0,0xa000,(int)*(undefined4 *)0xabc,
                (int)((ulong)*(undefined4 *)0xabc >> 0x10));
  pascal_delay_ms(0x1e);
  pole_blit_rle(0x10,0xd1,0x214,0,0xa000,(int)*(undefined4 *)0xab4,
                (int)((ulong)*(undefined4 *)0xab4 >> 0x10));
  return;
}



/* 1000:09a4 pole_draw_score */

void pole_draw_score(int param_1)

{
  int iVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  undefined2 uVar5;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined2 uVar6;
  undefined2 uVar7;
  byte local_106 [256];
  int local_6;
  int local_4;
  
  FUN_1000_068b(7,0xd,0x1d,
                (*(int *)(param_1 * 2 + 0x8c) + -1) * 0x50 + (*(int *)(param_1 * 2 + 0x86) + -4) / 8
               );
  iVar1 = *(int *)(param_1 * 2 + 0x84e);
  if (0 < iVar1) {
    local_4 = 1;
    while( true ) {
      pascal_random_bound(10);
      uVar2 = FUN_1ad9_0279();
      pc_speaker_sound_hz(uVar2);
      uVar5 = (undefined2)((ulong)*(undefined4 *)0xa80 >> 0x10);
      uVar2 = (undefined2)*(undefined4 *)0xa80;
      uVar7 = 0xa000;
      uVar6 = 0;
      iVar3 = pascal_random_bound(0xc);
      iVar3 = *(int *)(param_1 * 2 + 0x86) + -4 + iVar3;
      iVar4 = pascal_random_bound(7);
      pole_blit_rle(1,*(int *)(param_1 * 2 + 0x8c) + -1 + iVar4,iVar3,uVar6,uVar7,uVar2,uVar5);
      pc_speaker_no_sound();
      if (local_4 == iVar1) break;
      local_4 = local_4 + 1;
    }
  }
  if (*(int *)(param_1 * 2 + 0x84e) < 1) {
    pole_blit_rle(2,*(int *)(param_1 * 2 + 0x8c) + 10,*(int *)(param_1 * 2 + 0x86) + 4,0,0xa000,
                  (int)*(undefined4 *)0xa78,(int)((ulong)*(undefined4 *)0xa78 >> 0x10));
  }
  else {
    pole_blit_rle(1,*(undefined2 *)(param_1 * 2 + 0x8c),*(undefined2 *)(param_1 * 2 + 0x86),0,0xa000
                  ,(int)*(undefined4 *)0xa80,(int)((ulong)*(undefined4 *)0xa80 >> 0x10));
    iVar1 = *(int *)(param_1 * 2 + 0x84e);
    FUN_1ad9_12f6(0xff,local_106,unaff_SS,0,iVar1,iVar1 >> 0xf);
    local_4 = -1;
    while( true ) {
      local_6 = -1;
      while (pole_draw_font(0,0xa000,8,0xd,0,*(int *)(param_1 * 2 + 0x8c) + 4 + local_6,
                            *(int *)(param_1 * 2 + 0x86) + 0x22 + (uint)local_106[0] * -4 + local_4,
                            local_106,unaff_SS), local_6 != 1) {
        local_6 = local_6 + 1;
      }
      if (local_4 == 1) break;
      local_4 = local_4 + 1;
    }
    pole_draw_font(0,0xa000,8,0xd,0xf,*(int *)(param_1 * 2 + 0x8c) + 4,
                   *(int *)(param_1 * 2 + 0x86) + 0x22 + (uint)local_106[0] * -4,local_106,unaff_SS)
    ;
  }
  return;
}



/* 1000:0bce FUN_1000_0bce */

void __cdecl16near FUN_1000_0bce(void)

{
  undefined2 unaff_DS;
  
  pole_speaker_transition();
  pole_blit_rle(0x10,0xc9,0x214,0,0xa000,(int)*(undefined4 *)0xab4,
                (int)((ulong)*(undefined4 *)0xab4 >> 0x10));
  pascal_delay_ms(100);
  pole_blit_rle(0x10,0xc9,0x214,0,0xa000,(int)*(undefined4 *)0xab8,
                (int)((ulong)*(undefined4 *)0xab8 >> 0x10));
  pascal_delay_ms(100);
  return;
}



/* 1000:0c28 FUN_1000_0c28 */

void __cdecl16near FUN_1000_0c28(void)

{
  int iVar1;
  undefined2 unaff_DS;
  undefined2 local_4;
  
  pole_speaker_transition();
  pole_blit_rle(0x10,0xd1,0x214,0,0xa000,(int)*(undefined4 *)0xab8,
                (int)((ulong)*(undefined4 *)0xab8 >> 0x10));
  pascal_delay_ms(200);
  pole_blit_rle(0x10,0xd1,0x214,0,0xa000,(int)*(undefined4 *)0xab4,
                (int)((ulong)*(undefined4 *)0xab4 >> 0x10));
  pascal_delay_ms(0x96);
  pole_blit_rle(0x10,0xd1,0x214,0,0xa000,(int)*(undefined4 *)0xab8,
                (int)((ulong)*(undefined4 *)0xab8 >> 0x10));
  pascal_delay_ms(0x96);
  pole_blit_rle(0x10,0xad,0x1ff,0,0xa000,(int)*(undefined4 *)0xab0,
                (int)((ulong)*(undefined4 *)0xab0 >> 0x10));
  pole_blit_rle(0x10,0xc9,0x214,0,0xa000,(int)*(undefined4 *)0xab8,
                (int)((ulong)*(undefined4 *)0xab8 >> 0x10));
  local_4 = 1;
  while( true ) {
    pole_speaker_transition();
    pole_blit_rle(0x10,0xad,0x1ff,0,0xa000,(int)*(undefined4 *)0xabc,
                  (int)((ulong)*(undefined4 *)0xabc >> 0x10));
    pole_blit_rle(0x10,0xd1,0x214,0,0xa000,(int)*(undefined4 *)0xab4,
                  (int)((ulong)*(undefined4 *)0xab4 >> 0x10));
    iVar1 = pascal_random_bound(2);
    pascal_delay_ms(iVar1 * 200 + 100);
    pole_blit_rle(0x10,0xad,0x1ff,0,0xa000,(int)*(undefined4 *)0xab0,
                  (int)((ulong)*(undefined4 *)0xab0 >> 0x10));
    iVar1 = pascal_random_bound(2);
    pascal_delay_ms(iVar1 * 0x32 + 100);
    if (local_4 == 3) break;
    local_4 = local_4 + 1;
  }
  return;
}



/* 1000:1034 pole_host_dialogue */

void pole_host_dialogue(int param_1)

{
  int iVar1;
  undefined2 uVar2;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar3;
  undefined2 uVar4;
  undefined1 local_146 [256];
  byte local_46 [22];
  byte local_30 [22];
  undefined1 local_1a [22];
  undefined2 local_4;
  
  uVar2 = 0x1000;
  FUN_1000_0c28();
  local_4 = 0x2bfb;
  FUN_1000_0725(0x15,0xbe,0xa8fb,0x2bfb);
  pole_blit_rle(1,0x8e,0x1dc,0,0xa000,(int)*(undefined4 *)0xa94,
                (int)((ulong)*(undefined4 *)0xa94 >> 0x10));
  if (param_1 == 1) {
    iVar1 = *(int *)0x856;
    if (iVar1 == 1) {
      FUN_1ad9_0644(0x14,local_1a,unaff_SS,0xd8c,0x1000);
    }
    else if (iVar1 == 2) {
      FUN_1ad9_0644(0x14,local_1a,unaff_SS,0xd93,0x1000);
    }
    else if (iVar1 == 3) {
      FUN_1ad9_0644(0x14,local_1a,unaff_SS,0xd9a,0x1000);
    }
    puVar3 = local_146;
    uVar2 = unaff_SS;
    FUN_1ad9_062a(local_1a,unaff_SS);
    FUN_1ad9_06b7(0xda1,0x1ad9);
    FUN_1ad9_0644(0x14,local_30,unaff_SS,puVar3,uVar2);
    uVar2 = 0x1ad9;
    FUN_1ad9_0644(0x14,local_46,unaff_SS,0xda9,0x1ad9);
  }
  if (param_1 == 2) {
    if ((0 < *(int *)0x84e) && (*(int *)0x84e < 100)) {
      FUN_1ad9_12f6(0x14,local_1a,unaff_SS,0,*(int *)0x84e,*(int *)0x84e >> 0xf);
      puVar3 = local_146;
      uVar2 = unaff_SS;
      FUN_1ad9_062a(0xdbb,0x1ad9);
      FUN_1ad9_06b7(local_1a,unaff_SS);
      FUN_1ad9_06b7(0xdc2,0x1ad9);
      FUN_1ad9_0644(0x14,local_30,unaff_SS,puVar3,uVar2);
      uVar2 = 0x1ad9;
      FUN_1ad9_0644(0x14,local_46,unaff_SS,0xdca,0x1ad9);
    }
    if (*(int *)0x84e == 0) {
      FUN_1ad9_0644(0x14,local_30,unaff_SS,0xdda,uVar2);
      uVar2 = 0x1ad9;
      FUN_1ad9_0644(0x14,local_46,unaff_SS,0xdea,0x1ad9);
    }
    if (*(int *)0x84e < 0) {
      FUN_1ad9_0644(0x14,local_30,unaff_SS,0xdfe,uVar2);
      uVar2 = 0x1ad9;
      FUN_1ad9_0644(0x14,local_46,unaff_SS,0xdea,0x1ad9);
    }
    if (*(int *)0x84e / 100 == 2) {
      FUN_1ad9_0644(0x14,local_30,unaff_SS,0xe12,uVar2);
      uVar2 = 0x1ad9;
      FUN_1ad9_0644(0x14,local_46,unaff_SS,0xdca,0x1ad9);
    }
    if (*(int *)0x84e == 100) {
      FUN_1ad9_0644(0x14,local_30,unaff_SS,0xe26,uVar2);
      uVar2 = 0x1ad9;
      FUN_1ad9_0644(0x14,local_46,unaff_SS,0xe33,0x1ad9);
    }
    if (*(int *)0x84e == 300) {
      FUN_1ad9_0644(0x14,local_30,unaff_SS,0xe47,uVar2);
      uVar2 = 0x1ad9;
      FUN_1ad9_0644(0x14,local_46,unaff_SS,0xe54,0x1ad9);
    }
  }
  if (param_1 == 3) {
    if (*(int *)0x5d6 < 1) {
      FUN_1ad9_0644(0x14,local_30,unaff_SS,0xe7f,uVar2);
      uVar2 = 0x1ad9;
      FUN_1ad9_0644(0x14,local_46,unaff_SS,0xe90,0x1ad9);
    }
    else {
      FUN_1ad9_0644(0x14,local_46,unaff_SS,0xe65,uVar2);
      uVar2 = 0x1ad9;
      FUN_1ad9_0644(0x14,local_30,unaff_SS,0xe77,0x1ad9);
    }
  }
  if (param_1 == 4) {
    iVar1 = *(int *)0x856;
    if (iVar1 == 1) {
      FUN_1ad9_0644(0x14,local_1a,unaff_SS,0xd8c,uVar2);
    }
    else if (iVar1 == 2) {
      FUN_1ad9_0644(0x14,local_1a,unaff_SS,0xd93,uVar2);
    }
    else if (iVar1 == 3) {
      FUN_1ad9_0644(0x14,local_1a,unaff_SS,0xd9a,uVar2);
    }
    puVar3 = local_146;
    uVar2 = unaff_SS;
    FUN_1ad9_062a(local_1a,unaff_SS);
    FUN_1ad9_06b7(0xe9f,0x1ad9);
    FUN_1ad9_0644(0x14,local_30,unaff_SS,puVar3,uVar2);
    uVar2 = 0x1ad9;
    FUN_1ad9_0644(0x14,local_46,unaff_SS,0xea6,0x1ad9);
  }
  if (param_1 == 5) {
    FUN_1ad9_0644(0x14,local_30,unaff_SS,0xeb5,uVar2);
    uVar2 = 0x1ad9;
    FUN_1ad9_0644(0x14,local_46,unaff_SS,0xec8,0x1ad9);
  }
  if (param_1 == 6) {
    FUN_1ad9_0644(0x14,local_30,unaff_SS,0xeda,uVar2);
    uVar2 = 0x1ad9;
    FUN_1ad9_0644(0x14,local_46,unaff_SS,0xee6,0x1ad9);
  }
  if (param_1 == 7) {
    FUN_1ad9_0644(0x14,local_30,unaff_SS,0xef1,uVar2);
    uVar2 = 0x1ad9;
    FUN_1ad9_0644(0x14,local_46,unaff_SS,0xefa,0x1ad9);
  }
  if (param_1 == 8) {
    FUN_1ad9_0644(0x14,local_30,unaff_SS,0xf07,uVar2);
    uVar2 = 0x1ad9;
    FUN_1ad9_0644(0x14,local_46,unaff_SS,0xf10,0x1ad9);
  }
  if (param_1 == 9) {
    FUN_1ad9_0644(0x14,local_46,unaff_SS,0xf20,uVar2);
    uVar2 = 0x1ad9;
    FUN_1ad9_0644(0x14,local_30,unaff_SS,0xf30,0x1ad9);
  }
  if (param_1 == 10) {
    FUN_1ad9_0644(0x14,local_30,unaff_SS,0xf3f,uVar2);
    uVar2 = 0x1ad9;
    FUN_1ad9_0644(0x14,local_46,unaff_SS,0x694,unaff_DS);
  }
  if (param_1 == 0xb) {
    FUN_1ad9_0644(0x14,local_30,unaff_SS,0xf45,uVar2);
    uVar2 = 0x1ad9;
    FUN_1ad9_0644(0x14,local_46,unaff_SS,0xf53,0x1ad9);
  }
  if (param_1 == 0xc) {
    FUN_1ad9_0644(0x14,local_30,unaff_SS,0xf5b,uVar2);
    uVar2 = 0x1ad9;
    FUN_1ad9_0644(0x14,local_46,unaff_SS,0xf6b,0x1ad9);
  }
  if (param_1 == 0xd) {
    FUN_1ad9_0644(0x14,local_30,unaff_SS,0xf7b,uVar2);
    uVar2 = 0x1ad9;
    FUN_1ad9_0644(0x14,local_46,unaff_SS,0xf8a,0x1ad9);
  }
  if (param_1 == 0xe) {
    FUN_1ad9_0644(0x14,local_30,unaff_SS,0xf9a,uVar2);
    uVar2 = 0x1ad9;
    FUN_1ad9_0644(0x14,local_46,unaff_SS,0xfa9,0x1ad9);
  }
  if (param_1 == 0xf) {
    FUN_1ad9_0644(0x14,local_30,unaff_SS,0xfba,uVar2);
    uVar2 = 0x1ad9;
    FUN_1ad9_0644(0x14,local_46,unaff_SS,0xfc7,0x1ad9);
  }
  if (param_1 == 0x10) {
    FUN_1ad9_0644(0x14,local_30,unaff_SS,0xfd7,uVar2);
    uVar2 = 0x1ad9;
    FUN_1ad9_0644(0x14,local_46,unaff_SS,0xfe1,0x1ad9);
  }
  if (param_1 == 0x11) {
    FUN_1ad9_0644(0x14,local_30,unaff_SS,0xfe8,uVar2);
    puVar3 = local_146;
    uVar4 = unaff_SS;
    FUN_1ad9_062a(0x864,unaff_DS);
    FUN_1ad9_06b7(0xff1,0x1ad9);
    uVar2 = 0x1ad9;
    FUN_1ad9_0644(0x14,local_46,unaff_SS,puVar3,uVar4);
  }
  if (param_1 == 0x12) {
    FUN_1ad9_0644(0x14,local_30,unaff_SS,0xffa,uVar2);
    uVar2 = 0x1ad9;
    FUN_1ad9_0644(0x14,local_46,unaff_SS,0x1004,0x1ad9);
  }
  if (param_1 == 0x13) {
    FUN_1ad9_0644(0x14,local_30,unaff_SS,0x1011,uVar2);
    uVar2 = 0x1ad9;
    FUN_1ad9_0644(0x14,local_46,unaff_SS,0x101d,0x1ad9);
  }
  if (param_1 == 0x14) {
    FUN_1ad9_0644(0x14,local_30,unaff_SS,0xffa,uVar2);
    FUN_1ad9_0644(0x14,local_46,unaff_SS,0x1029,0x1ad9);
  }
  pole_draw_font(0,0xa000,8,0xd,0,0x91,(uint)local_30[0] * -4 + 0x22a,local_30,unaff_SS);
  pole_draw_font(0,0xa000,8,0xd,0,0x9e,(uint)local_46[0] * -4 + 0x22a,local_46,unaff_SS);
  FUN_1000_0bce();
  return;
}



/* 1000:1698 pole_reveal_and_award */

void __cdecl16near pole_reveal_and_award(void)

{
  undefined4 uVar1;
  char cVar2;
  undefined1 uVar3;
  undefined1 extraout_AH;
  undefined2 uVar4;
  int iVar5;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar6;
  undefined1 local_11c [256];
  int local_1c;
  int local_1a;
  int local_18;
  int local_16;
  int local_14;
  int local_12;
  int local_10;
  uint local_e;
  int local_c;
  int local_a;
  int local_8;
  undefined2 local_6;
  int local_4;
  
  pc_speaker_no_sound();
  local_1a = 1;
  local_1c = (*(int *)0x600 + 5) * 0x10 + 0x6e;
  FUN_1000_0725(0x50,0x78,32000,0);
  local_6 = 48000;
  local_e = 0x28;
  local_10 = 0x19;
  local_16 = 0;
  local_14 = 0;
  local_a = 0x7d5;
  local_12 = 0x14;
  local_8 = local_a;
  while( true ) {
    pc_speaker_sound_hz(*(int *)0x862 * local_12);
    pascal_delay_ms(1);
    pc_speaker_no_sound();
    pascal_delay_ms((100 - local_12) / 5);
    if (local_12 == 100) break;
    local_12 = local_12 + 1;
  }
  do {
    local_8 = (local_e >> 3) + local_10 * 0x50;
    local_14 = local_14 + 1;
    if (local_16 == 10) {
      FUN_1000_0725(2,0x13,local_4 + 0x640,local_4);
      puVar6 = local_11c;
      uVar4 = unaff_SS;
      FUN_1ad9_075a(CONCAT11(extraout_AH,*(undefined1 *)0x7b0));
      pole_draw_font(32000,0xa000,8,0xd,0,0x26,local_c,puVar6,uVar4);
    }
    FUN_1000_0725(6,0x5a,local_6,local_8 + 32000);
    if (local_16 < 1) {
      iVar5 = local_14 % 4;
      if (iVar5 == 0) {
        local_18 = 0x18;
        local_12 = 10;
      }
      else if (iVar5 == 1) {
        local_18 = 0x1a;
        local_12 = 0;
      }
      else if (iVar5 == 2) {
        local_18 = 0x19;
        local_12 = 0xc;
      }
      else if (iVar5 == 3) {
        local_18 = 0x1a;
        local_12 = 3;
      }
    }
    else {
      local_18 = 0x17;
    }
    if (0 < local_16) {
      local_16 = local_16 + 1;
    }
    if (0x14 < local_16) {
      local_16 = 0;
    }
    uVar1 = *(undefined4 *)(local_18 * 4 + 0xa08);
    pole_blit_rle(2,local_10,local_e,32000,0xa000,(int)uVar1,(int)((ulong)uVar1 >> 0x10));
    FUN_1000_0725(6,0x5a,local_8,local_8 + 32000);
    FUN_1000_0725(6,0x5a,local_a,local_a + 32000);
    local_a = local_8;
    if (local_16 == 0) {
      pascal_random_bound(100);
      uVar4 = FUN_1ad9_0279();
      pc_speaker_sound_hz(uVar4);
    }
    FUN_1000_0725(6,0x5a,local_a + 32000,local_6);
    pc_speaker_no_sound();
    if (local_16 == 0) {
      local_e = local_e + local_12;
    }
    if (local_1c < (int)local_e) {
      local_4 = *(int *)(local_1a * 2 + 0x5fe) * 2 + -0x7e37;
      local_c = (*(int *)(local_1a * 2 + 0x5fe) + 5) * 0x10 + 0x7d;
      local_1a = local_1a + 1;
      if (*(int *)0x5d6 < local_1a) {
        local_1c = 1000;
      }
      else {
        local_1c = (*(int *)(local_1a * 2 + 0x5fe) + 5) * 0x10 + 0x6e;
      }
      local_16 = 1;
    }
    pascal_delay_ms(0x32);
    *(undefined1 *)0x964 = 7;
    cVar2 = FUN_1a77_02fa();
    if (cVar2 != '\0') {
      uVar3 = FUN_1a77_030c();
      *(undefined1 *)0x964 = uVar3;
    }
    if (*(char *)0x964 == '\x13') {
      *(int *)0x862 = 1 - *(int *)0x862;
    }
    if (*(char *)0x964 == '\t') {
      FUN_1000_07b9();
    }
    if (*(char *)0x964 == '\x1b') {
      FUN_1000_0000();
    }
  } while ((int)local_e < 0x247);
  FUN_1000_0725(8,0x5b,local_8,local_8 + 32000);
  local_12 = 100;
  while( true ) {
    pc_speaker_sound_hz(*(int *)0x862 * local_12);
    pascal_delay_ms((100 - local_12) / 10);
    pc_speaker_no_sound();
    pascal_delay_ms(1);
    if (local_12 == 0x14) break;
    local_12 = local_12 + -1;
  }
  if (*(int *)0x84e < 100) {
    *(int *)(*(int *)0x856 * 2 + 0x84e) =
         *(int *)0x84e * *(int *)0x5d6 + *(int *)(*(int *)0x856 * 2 + 0x84e);
  }
  else if (*(int *)0x84e / 100 == 2) {
    *(int *)(*(int *)0x856 * 2 + 0x84e) =
         (*(int *)0x84e % 100) * *(int *)(*(int *)0x856 * 2 + 0x84e);
  }
  pole_draw_score(*(undefined2 *)0x856);
  return;
}



/* 1000:1a3a pole_select_letter */

void __cdecl16near pole_select_letter(void)

{
  undefined4 uVar1;
  char cVar2;
  undefined1 uVar3;
  int iVar4;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar5;
  undefined1 *puVar6;
  undefined2 uVar7;
  undefined1 local_216 [256];
  undefined1 local_116 [254];
  uint local_18;
  int local_16;
  int local_14;
  uint local_12;
  int local_10;
  uint local_e;
  int local_c;
  uint local_a;
  int local_8;
  int local_6;
  undefined2 local_4;
  
  if (*(int *)0x856 == 3) {
    local_6 = 0x59b0;
    FUN_1000_0725(0x50,0x3c,0xd6b0,0x59b0);
    if (0 < *(int *)0x7b4) {
      *(undefined2 *)0x9f4 = 4;
      *(undefined2 *)0x9f8 = 0x140;
      *(undefined2 *)0x9fa = 100;
      FUN_1a70_000b(0x9f4);
    }
    local_14 = 0;
    local_16 = 0;
    FUN_1000_077e();
    local_4 = 48000;
    local_a = local_14 * 0x14;
    local_c = 0x13a;
    local_8 = (local_a >> 3) + 0x6220;
    do {
      local_6 = (local_a >> 3) + local_c * 0x50;
      FUN_1000_0725(3,0x1a,local_4,local_6 + 32000);
      pole_blit_rle(2,local_c,local_a,32000,0xa000,(int)*(undefined4 *)0xa7c,
                    (int)((ulong)*(undefined4 *)0xa7c >> 0x10));
      FUN_1000_0725(3,0x1a,local_6,local_6 + 32000);
      FUN_1000_0725(3,0x1a,local_8,local_8 + 32000);
      local_8 = local_6;
      FUN_1000_0725(3,0x1a,local_6 + 32000,local_4);
      *(undefined1 *)0x964 = 7;
      cVar2 = FUN_1a77_02fa();
      if (cVar2 != '\0') {
        uVar3 = FUN_1a77_030c();
        *(undefined1 *)0x964 = uVar3;
      }
      if (*(char *)0x964 == '\x13') {
        *(int *)0x862 = 1 - *(int *)0x862;
      }
      if (*(char *)0x964 == '\t') {
        FUN_1000_07b9();
      }
      if (*(char *)0x964 == '\0') {
        uVar3 = FUN_1a77_030c();
        *(undefined1 *)0x964 = uVar3;
        if (*(char *)0x964 == 'K') {
          local_14 = local_14 + -1;
        }
        if (*(char *)0x964 == 'M') {
          local_14 = local_14 + 1;
        }
      }
      if (0 < *(int *)0x7b4) {
        *(undefined2 *)0x9f4 = 3;
        FUN_1a70_000b(0x9f4);
        if (*(uint *)0x9f8 < 0x131) {
          local_14 = local_14 + -1;
          *(undefined2 *)0x9f4 = 4;
          *(undefined2 *)0x9f8 = 0x140;
          *(undefined2 *)0x9fa = 100;
          FUN_1a70_000b(0x9f4);
        }
        if (0x14f < *(uint *)0x9f8) {
          local_14 = local_14 + 1;
          *(undefined2 *)0x9f4 = 4;
          *(undefined2 *)0x9f8 = 0x140;
          *(undefined2 *)0x9fa = 100;
          FUN_1a70_000b(0x9f4);
        }
      }
      if (local_14 < 0) {
        local_14 = 0;
      }
      if (0x1f < local_14) {
        local_14 = 0x1f;
      }
      local_a = local_14 * 0x14;
      local_c = 0x13a;
      if (*(char *)0x964 == '\x1b') {
        FUN_1000_0000();
      }
      if ((*(char *)0x964 == ' ') || ((0 < *(int *)0x7b4 && (*(int *)0x9f6 == 1)))) {
        if (*(int *)(local_14 * 2 + 0x628) == 0) {
          local_16 = 1;
        }
        else {
          pc_speaker_sound_hz(*(int *)0x862 * 1000);
          pascal_delay_ms(0x32);
          pc_speaker_no_sound();
        }
      }
      pascal_delay_ms(0x1e);
    } while (local_16 < 1);
    pc_speaker_sound_hz(*(int *)0x862 * 100);
    FUN_1000_0725(3,0x1a,local_6,local_6 + 32000);
    pc_speaker_no_sound();
  }
  else {
    local_10 = 0;
    local_18 = (uint)*(byte *)0x67e;
    if (local_18 != 0) {
      local_e = 1;
      while( true ) {
        if (*(int *)(local_e * 2 + 0x5d6) == 0) {
          local_10 = local_10 + 1;
        }
        if (local_e == local_18) break;
        local_e = local_e + 1;
      }
    }
    local_12 = local_18;
    if ((local_10 * 2 - local_18 == 0 || local_10 * 2 < (int)local_18) || (local_10 < 2)) {
      iVar4 = pascal_random_bound(*(int *)0x858 + 2);
      if (iVar4 == 0) {
        local_a = 0;
      }
      else {
        local_a = 1;
      }
    }
    else {
      local_a = 0;
    }
    if (local_a == 0) {
      do {
        local_14 = pascal_random_bound(0x20);
      } while (*(int *)(local_14 * 2 + 0x628) != 0);
    }
    else {
      do {
        iVar4 = pascal_random_bound(local_12);
        local_10 = iVar4 + 1;
      } while (*(int *)(local_10 * 2 + 0x5d6) != 0);
      *(undefined1 *)0x964 = *(undefined1 *)(iVar4 + 0x67f);
      for (local_14 = 0; *(char *)(local_14 + 0x9b) != *(char *)0x964; local_14 = local_14 + 1) {
      }
    }
    iVar4 = *(int *)(*(int *)0x856 * 2 + 0x92) / 8;
    local_6 = iVar4 + 0x2260;
    FUN_1000_0725(0x14,0x28,iVar4 + -0x60a0,local_6);
    pole_blit_rle(2,0x6e,*(undefined2 *)(*(int *)0x856 * 2 + 0x92),0,0xa000,
                  (int)*(undefined4 *)0xaa4,(int)((ulong)*(undefined4 *)0xaa4 >> 0x10));
    puVar6 = local_216;
    uVar7 = unaff_SS;
    FUN_1ad9_062a(0x1a30,0x1ad9);
    puVar5 = local_116;
    FUN_1ad9_075a(CONCAT11((char)((uint)(local_14 + 1) >> 8),*(undefined1 *)(local_14 + 0x9b)));
    FUN_1ad9_06b7(puVar5,unaff_SS);
    FUN_1ad9_06b7(0x1a38,0x1ad9);
    pole_draw_font(0,0xa000,8,0xd,0,0x76,*(int *)(*(int *)0x856 * 2 + 0x92) + 6,puVar6,uVar7);
    FUN_1000_0858(0x28);
    FUN_1000_0725(0x14,0x28,local_6,local_6 + 32000);
  }
  *(undefined2 *)(local_14 * 2 + 0x628) = 1;
  local_a = local_14 * 0x14;
  local_c = 0x14c;
  local_e = 0;
  while( true ) {
    if ((int)local_e < 3) {
      uVar1 = *(undefined4 *)((local_e + 0x12) * 4 + 0xa08);
      pole_blit_rle(0x10,local_c,local_a,0,0xa000,(int)uVar1,(int)((ulong)uVar1 >> 0x10));
    }
    else {
      out(0x3ce,5);
      out(0x3cf,0);
      FUN_174b_0b9e(7,1);
      FUN_174b_13aa(local_c + 0x12,local_a + 0x13,local_c,local_a);
    }
    local_10 = 1;
    while( true ) {
      pc_speaker_sound_hz((local_10 * 10 + local_e * 100 + 0x32) * *(int *)0x862);
      pascal_delay_ms(1);
      pc_speaker_no_sound();
      pascal_delay_ms(local_e * 4 + local_10 / 5);
      if (local_10 == 10) break;
      local_10 = local_10 + 1;
    }
    if (local_e == 3) break;
    local_e = local_e + 1;
  }
  *(undefined1 *)0x7b0 = *(undefined1 *)(local_14 + 0x9b);
  *(undefined2 *)0x5d6 = 0;
  local_18 = (uint)*(byte *)0x67e;
  if (local_18 != 0) {
    local_e = 1;
    while( true ) {
      if ((*(char *)(local_e + 0x67e) == *(char *)0x7b0) && (*(int *)(local_e * 2 + 0x5d6) == 0)) {
        *(int *)0x5d6 = *(int *)0x5d6 + 1;
        *(uint *)(*(int *)0x5d6 * 2 + 0x5fe) = local_e;
        *(undefined2 *)(local_e * 2 + 0x5d6) = 1;
      }
      if (local_e == local_18) break;
      local_e = local_e + 1;
    }
  }
  pole_host_dialogue(3);
  FUN_1000_0858(0x28);
  FUN_1000_0936();
  return;
}



/* 1000:1fcf pole_plus_select_position */

void __cdecl16near pole_plus_select_position(void)

{
  undefined4 uVar1;
  uint uVar2;
  char cVar3;
  undefined1 uVar4;
  int iVar5;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar6;
  undefined1 local_11a [254];
  uint local_1c;
  undefined1 local_1a [4];
  int local_16;
  uint local_14;
  int local_10;
  uint local_e;
  int local_c;
  uint local_a;
  int local_8;
  int local_6;
  undefined2 local_4;
  
  if (*(int *)0x856 == 3) {
    local_6 = 800;
    FUN_1000_0725(0x50,0x3c,0x8020,800);
    if (0 < *(int *)0x7b4) {
      *(undefined2 *)0x9f4 = 4;
      *(undefined2 *)0x9f8 = 0x140;
      *(undefined2 *)0x9fa = 100;
      FUN_1a70_000b(0x9f4);
    }
    local_14 = 1;
    local_16 = 0;
    FUN_1000_077e();
    local_4 = 48000;
    local_a = local_14 * 0x10 + 200;
    local_c = 0xc;
    local_8 = (local_a >> 3) + 0x3c0;
    do {
      local_6 = (local_a >> 3) + local_c * 0x50;
      FUN_1000_0725(3,0x1a,local_4,local_6 + 32000);
      pole_blit_rle(2,local_c,local_a,32000,0xa000,(int)*(undefined4 *)0xa7c,
                    (int)((ulong)*(undefined4 *)0xa7c >> 0x10));
      FUN_1000_0725(3,0x1a,local_6,local_6 + 32000);
      FUN_1000_0725(3,0x1a,local_8,local_8 + 32000);
      local_8 = local_6;
      FUN_1000_0725(3,0x1a,local_6 + 32000,local_4);
      *(undefined1 *)0x964 = 7;
      cVar3 = FUN_1a77_02fa();
      if (cVar3 != '\0') {
        uVar4 = FUN_1a77_030c();
        *(undefined1 *)0x964 = uVar4;
      }
      if (*(char *)0x964 == '\x13') {
        *(int *)0x862 = 1 - *(int *)0x862;
      }
      if (*(char *)0x964 == '\t') {
        FUN_1000_07b9();
      }
      if (*(char *)0x964 == '\0') {
        uVar4 = FUN_1a77_030c();
        *(undefined1 *)0x964 = uVar4;
        if (*(char *)0x964 == 'K') {
          local_14 = local_14 - 1;
        }
        if (*(char *)0x964 == 'M') {
          local_14 = local_14 + 1;
        }
      }
      if (0 < *(int *)0x7b4) {
        *(undefined2 *)0x9f4 = 3;
        FUN_1a70_000b(0x9f4);
        if (*(uint *)0x9f8 < 0x131) {
          local_14 = local_14 - 1;
          *(undefined2 *)0x9f4 = 4;
          *(undefined2 *)0x9f8 = 0x140;
          *(undefined2 *)0x9fa = 100;
          FUN_1a70_000b(0x9f4);
        }
        if (0x14f < *(uint *)0x9f8) {
          local_14 = local_14 + 1;
          *(undefined2 *)0x9f4 = 4;
          *(undefined2 *)0x9f8 = 0x140;
          *(undefined2 *)0x9fa = 100;
          FUN_1a70_000b(0x9f4);
        }
      }
      if ((int)local_14 < 1) {
        local_14 = 1;
      }
      if ((int)(uint)*(byte *)0x67e < (int)local_14) {
        local_14 = (uint)*(byte *)0x67e;
      }
      local_a = local_14 * 0x10 + 200;
      local_c = 0xc;
      if (*(char *)0x964 == '\x1b') {
        FUN_1000_0000();
      }
      if ((*(char *)0x964 == ' ') || ((0 < *(int *)0x7b4 && (*(int *)0x9f6 == 1)))) {
        if (*(int *)(local_14 * 2 + 0x5d6) == 0) {
          local_16 = 1;
        }
        else {
          pc_speaker_sound_hz(*(int *)0x862 * 1000);
          pascal_delay_ms(0x32);
          pc_speaker_no_sound();
        }
      }
      pascal_delay_ms(0x1e);
    } while (local_16 < 1);
    pc_speaker_sound_hz(*(int *)0x862 * 100);
    FUN_1000_0725(3,0x1a,local_6,local_6 + 32000);
    pc_speaker_no_sound();
  }
  else {
    do {
      iVar5 = pascal_random_bound(*(undefined1 *)0x67e);
      local_14 = iVar5 + 1;
    } while (*(int *)(local_14 * 2 + 0x5d6) != 0);
    iVar5 = *(int *)(*(int *)0x856 * 2 + 0x92) / 8;
    local_6 = iVar5 + 0x2260;
    FUN_1000_0725(0x14,0x28,iVar5 + -0x60a0,local_6);
    pole_blit_rle(2,0x6e,*(undefined2 *)(*(int *)0x856 * 2 + 0x92),0,0xa000,
                  (int)*(undefined4 *)0xaa4,(int)((ulong)*(undefined4 *)0xaa4 >> 0x10));
    FUN_1ad9_12f6(2,local_1a,unaff_SS,0,local_14,(int)local_14 >> 0xf);
    puVar6 = local_11a;
    FUN_1ad9_062a(local_1a,unaff_SS);
    FUN_1ad9_06b7(0x1fc6,0x1ad9);
    pole_draw_font(0,0xa000,8,0xd,0,0x76,*(int *)(*(int *)0x856 * 2 + 0x92) + 6,puVar6,unaff_SS);
    FUN_1000_0858(0x28);
    FUN_1000_0725(0x14,0x28,local_6,local_6 + 32000);
  }
  *(undefined1 *)0x7b0 = *(undefined1 *)(local_14 + 0x67e);
  *(undefined2 *)0x5d6 = 0;
  local_1c = (uint)*(byte *)0x67e;
  if (local_1c != 0) {
    local_e = 1;
    while( true ) {
      if ((*(char *)(local_e + 0x67e) == *(char *)0x7b0) && (*(int *)(local_e * 2 + 0x5d6) == 0)) {
        *(int *)0x5d6 = *(int *)0x5d6 + 1;
        *(uint *)(*(int *)0x5d6 * 2 + 0x5fe) = local_e;
        *(undefined2 *)(local_e * 2 + 0x5d6) = 1;
      }
      if (local_e == local_1c) break;
      local_e = local_e + 1;
    }
  }
  local_e = 0;
  uVar2 = local_e;
  do {
    local_e = uVar2;
    uVar2 = local_e + 1;
  } while (*(char *)0x7b0 != *(char *)(local_e + 0x9b));
  *(undefined2 *)(local_e * 2 + 0x628) = 1;
  local_a = local_e * 0x14;
  local_c = 0x14c;
  local_e = 0;
  while( true ) {
    if ((int)local_e < 3) {
      uVar1 = *(undefined4 *)((local_e + 0x12) * 4 + 0xa08);
      pole_blit_rle(0x10,local_c,local_a,0,0xa000,(int)uVar1,(int)((ulong)uVar1 >> 0x10));
    }
    else {
      out(0x3ce,5);
      out(0x3cf,0);
      FUN_174b_0b9e(7,1);
      FUN_174b_13aa(local_c + 0x12,local_a + 0x13,local_c,local_a);
    }
    local_10 = 1;
    while( true ) {
      pc_speaker_sound_hz((local_10 * 10 + local_e * 100 + 0x32) * *(int *)0x862);
      pascal_delay_ms(1);
      pc_speaker_no_sound();
      pascal_delay_ms(local_e * 4 + local_10 / 5);
      if (local_10 == 10) break;
      local_10 = local_10 + 1;
    }
    if (local_e == 3) break;
    local_e = local_e + 1;
  }
  return;
}



/* 1000:24bd pole_normalize_key */

byte pole_normalize_key(undefined1 param_1)

{
  byte bVar1;
  undefined2 unaff_DS;
  int local_6;
  byte local_4;
  
  local_4 = 0x20;
  bVar1 = FUN_1ad9_19ed(param_1);
  if (bVar1 < 0x80) {
    local_6 = 1;
    while( true ) {
      if (*(byte *)(local_6 + 0x294) == bVar1) {
        local_4 = *(byte *)(local_6 + 0x2b6);
      }
      if (local_6 == 0x21) break;
      local_6 = local_6 + 1;
    }
  }
  if ((0x7f < bVar1) && (bVar1 < 0xa0)) {
    local_4 = bVar1;
  }
  if ((0x9f < bVar1) && (bVar1 < 0xb0)) {
    local_4 = bVar1 - 0x20;
  }
  if ((0xdf < bVar1) && (bVar1 < 0xf0)) {
    local_4 = bVar1 + 0xb0;
  }
  return local_4;
}



/* 1000:254e pole_guess_full_word */

undefined1 __cdecl16near pole_guess_full_word(void)

{
  undefined1 uVar1;
  int iVar2;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar3;
  undefined2 uVar4;
  undefined1 *puVar5;
  undefined2 uVar6;
  undefined1 local_30e [256];
  undefined1 local_20e [254];
  uint local_110;
  undefined1 local_10c [256];
  int local_c;
  uint local_8;
  int local_6;
  
  out(0x3ce,5);
  out(0x3cf,0);
  FUN_174b_149e(0);
  local_110 = *(byte *)0x67e - 1;
  if (local_110 < 0x8000) {
    local_8 = 0;
    while (FUN_174b_0b55(0x140,local_8 * 0x10 + 0x14,300,local_8 * 0x10 + 4), local_8 != local_110)
    {
      local_8 = local_8 + 1;
    }
  }
  local_c = 0;
  local_10c[0] = 0;
  local_6 = 0x5eb1;
  local_8 = 0;
  do {
    *(undefined1 *)0x964 = 7;
    iVar2 = FUN_1a77_02fa();
    if ((char)iVar2 != '\0') {
      iVar2 = FUN_1a77_030c();
      *(undefined1 *)0x964 = (char)iVar2;
    }
    if (*(char *)0x964 == '\x13') {
      iVar2 = 1 - *(int *)0x862;
      *(int *)0x862 = iVar2;
    }
    uVar1 = (undefined1)((uint)iVar2 >> 8);
    if (*(char *)0x964 == '\t') {
      FUN_1000_07b9();
      uVar1 = extraout_AH;
    }
    if (*(char *)0x964 == '\x1b') {
      FUN_1000_0000();
      uVar1 = extraout_AH_00;
    }
    if ((*(char *)0x964 == '\b') && (0 < local_c)) {
      FUN_1ad9_07db(1,local_c,local_10c,unaff_SS);
      FUN_1000_068b(7,1,0xd,local_c * 2 + local_6);
      local_c = local_c + -1;
      FUN_1000_068b(7,1,0xd,local_c * 2 + local_6);
      uVar1 = extraout_AH_01;
    }
    if (0x20 < *(byte *)0x964) {
      uVar1 = pole_normalize_key(CONCAT11(uVar1,*(undefined1 *)0x964));
      *(undefined1 *)0x964 = uVar1;
    }
    if ((0x20 < *(byte *)0x964) && (local_c < (int)(uint)*(byte *)0x67e)) {
      FUN_1000_068b(7,1,0xd,local_c * 2 + local_6);
      puVar5 = local_20e;
      uVar4 = unaff_SS;
      FUN_1ad9_075a(CONCAT11(extraout_AH_02,*(undefined1 *)0x964));
      pole_draw_font(0,0xa000,8,0xd,0,0x12f,local_c * 0x10 + 8,puVar5,uVar4);
      puVar5 = local_30e;
      uVar6 = unaff_SS;
      FUN_1ad9_062a(local_10c,unaff_SS);
      puVar3 = local_20e;
      uVar4 = unaff_SS;
      FUN_1ad9_075a(CONCAT11(extraout_AH_03,*(undefined1 *)0x964));
      FUN_1ad9_06b7(puVar3,uVar4);
      FUN_1ad9_0644(0xff,local_10c,unaff_SS,puVar5,uVar6);
      local_c = local_c + 1;
    }
    pascal_delay_ms(0x19);
    local_8 = local_8 + 1;
    if (0x27 < (int)local_8) {
      local_8 = 0;
    }
    FUN_1000_068b(((int)local_8 / 0x14) * 7,1,2,local_c * 2 + local_6 + 800);
  } while (*(char *)0x964 != '\r');
  FUN_1ad9_0644(0x14,0x668,unaff_DS,local_10c,unaff_SS);
  FUN_1000_068b(7,(uint)*(byte *)0x67e * 2 + 3,0x14,24000);
  uVar1 = 0;
  if (*(char *)0x668 == *(char *)0x67e) {
    if (*(byte *)0x67e != 0) {
      local_8 = 1;
      while( true ) {
        if (*(char *)(local_8 + 0x668) != *(char *)(local_8 + 0x67e)) {
          uVar1 = 1;
        }
        if (local_8 == *(byte *)0x67e) break;
        local_8 = local_8 + 1;
      }
    }
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}



/* 1000:27db pole_enter_highscore_name */

void pole_enter_highscore_name(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  undefined1 extraout_AH_04;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar3;
  undefined2 uVar4;
  undefined1 *puVar5;
  undefined2 uVar6;
  undefined1 local_30c [256];
  undefined1 local_20c [258];
  undefined1 local_10a [256];
  int local_a;
  int local_6;
  int local_4;
  
  local_a = 0;
  local_10a[0] = 0;
  local_4 = (param_1 * 0xe + 0xc3) * 0x50 + 0x3e;
  local_6 = 0;
  do {
    *(undefined1 *)0x964 = 7;
    iVar2 = FUN_1a77_02fa();
    if ((char)iVar2 != '\0') {
      iVar2 = FUN_1a77_030c();
      *(undefined1 *)0x964 = (char)iVar2;
    }
    if (*(char *)0x964 == '\x13') {
      iVar2 = 1 - *(int *)0x862;
      *(int *)0x862 = iVar2;
    }
    uVar1 = (undefined1)((uint)iVar2 >> 8);
    if (*(char *)0x964 == '\t') {
      FUN_1000_07b9();
      uVar1 = extraout_AH;
    }
    if (*(char *)0x964 == '\x1b') {
      FUN_1000_0000();
      uVar1 = extraout_AH_00;
    }
    if ((*(char *)0x964 == '\b') && (0 < local_a)) {
      FUN_1ad9_07db(1,local_a,local_10a,unaff_SS);
      FUN_1000_068b(0,1,0xd,local_4 + local_a);
      local_a = local_a + -1;
      FUN_1000_068b(0,1,0xd,local_4 + local_a);
      uVar1 = extraout_AH_01;
    }
    if (0x20 < *(byte *)0x964) {
      uVar1 = pole_normalize_key(CONCAT11(uVar1,*(undefined1 *)0x964));
      *(undefined1 *)0x964 = uVar1;
    }
    if ((0x1f < *(byte *)0x964) && (local_a < 10)) {
      FUN_1000_068b(0,1,0xd,local_4 + local_a);
      puVar5 = local_20c;
      uVar4 = unaff_SS;
      FUN_1ad9_075a(CONCAT11(extraout_AH_02,*(undefined1 *)0x964));
      pole_draw_font(0,0xa000,8,0xd,7,param_1 * 0xe + 0xc3,local_a * 8 + 0x1f1,puVar5,uVar4);
      puVar5 = local_20c;
      uVar4 = unaff_SS;
      FUN_1ad9_075a(CONCAT11(extraout_AH_03,*(undefined1 *)0x964));
      pole_draw_font(0,0xa000,8,0xd,0xf,param_1 * 0xe + 0xc3,local_a * 8 + 0x1f0,puVar5,uVar4);
      puVar5 = local_30c;
      uVar6 = unaff_SS;
      FUN_1ad9_062a(local_10a,unaff_SS);
      puVar3 = local_20c;
      uVar4 = unaff_SS;
      FUN_1ad9_075a(CONCAT11(extraout_AH_04,*(undefined1 *)0x964));
      FUN_1ad9_06b7(puVar3,uVar4);
      FUN_1ad9_0644(0xff,local_10a,unaff_SS,puVar5,uVar6);
      local_a = local_a + 1;
    }
    pascal_delay_ms(0x19);
    local_6 = local_6 + 1;
    if (0x27 < local_6) {
      local_6 = 0;
    }
    FUN_1000_068b((local_6 / 0x14) * 0xb,1,2,local_4 + local_a + 800);
  } while (*(char *)0x964 != '\r');
  FUN_1ad9_0644(10,param_1 * 0xd + 0x55d,unaff_DS,local_10a,unaff_SS);
  return;
}



/* 1000:29f1 pole_load_word_pair */

void __cdecl16near pole_load_word_pair(void)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 local_86 [128];
  uint local_6;
  uint local_4;
  
  FUN_1ad9_1779(0x29e8,0x1000,local_86,unaff_SS);
  FUN_1ad9_17a7(0x15,local_86,unaff_SS);
  FUN_1ad9_020e();
  FUN_1ad9_185c(0x694,unaff_DS);
  FUN_1ad9_020e();
  local_6 = FUN_1ad9_1341(&local_4,unaff_SS,0x694,unaff_DS);
  do {
    do {
      iVar2 = pascal_random_bound(local_6);
      uVar3 = iVar2 + 1;
      local_4 = uVar3;
    } while (*(uint *)0x6aa == uVar3);
  } while ((*(uint *)0x6ac == uVar3) || (*(uint *)0x6ae == uVar3));
  *(uint *)(*(int *)0x858 * 2 + 0x6aa) = uVar3;
  local_6 = uVar3;
  if (0 < (int)uVar3) {
    local_4 = 1;
    while( true ) {
      FUN_1ad9_185c(0x67e,unaff_DS);
      FUN_1ad9_020e();
      FUN_1ad9_185c(0x694,unaff_DS);
      FUN_1ad9_020e();
      if (local_4 == uVar3) break;
      local_4 = local_4 + 1;
    }
  }
  FUN_1ad9_1828(local_86,unaff_SS);
  FUN_1ad9_020e();
  bVar1 = *(byte *)0x67e;
  if (bVar1 != 0) {
    for (local_4 = 1; *(char *)(local_4 + 0x67e) = *(char *)(local_4 + 0x67e) + -0x20,
        local_4 != bVar1; local_4 = local_4 + 1) {
    }
  }
  bVar1 = *(byte *)0x694;
  if (bVar1 != 0) {
    for (local_4 = 1; *(char *)(local_4 + 0x694) = *(char *)(local_4 + 0x694) + -0x20,
        local_4 != bVar1; local_4 = local_4 + 1) {
    }
  }
  return;
}



/* 1000:2b4e pole_draw_wheel */

void __cdecl16near pole_draw_wheel(void)

{
  undefined4 uVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  undefined2 in_BX;
  undefined2 unaff_DS;
  undefined2 local_4;
  
  uVar1 = *(undefined4 *)(((*(int *)0x970 + 3) % 4) * 4 + 0xa08);
  pole_blit_rle(3,0x73,0xa0,0,0xa000,(int)uVar1,(int)((ulong)uVar1 >> 0x10));
  local_4 = 0;
  while( true ) {
    iVar4 = local_4 * 2 + *(int *)0x970 >> 0xf;
    FUN_1ad9_0cb9();
    FUN_1ad9_0ca5();
    uVar2 = FUN_1ad9_0cab();
    FUN_1ad9_0dc9(0x1ad9,uVar2,in_BX,iVar4);
    FUN_1ad9_0ca5();
    iVar4 = FUN_1ad9_0cc5();
    FUN_1ad9_0ddc();
    FUN_1ad9_0ca5();
    iVar3 = FUN_1ad9_0cc5();
    uVar1 = *(undefined4 *)(*(int *)(local_4 * 2 + 0x50) * 4 + 0xa08);
    pole_blit_rle(7,iVar3 + 0xc4,iVar4 + 0x105,0,0xa000,(int)uVar1,(int)((ulong)uVar1 >> 0x10));
    if (local_4 == 0xf) break;
    local_4 = local_4 + 1;
  }
  pole_blit_rle(7,0x98,0x10b,0,0xa000,(int)*(undefined4 *)0xa48,
                (int)((ulong)*(undefined4 *)0xa48 >> 0x10));
  return;
}



/* 1000:2c6a pole_spin_wheel */

void __cdecl16near pole_spin_wheel(void)

{
  undefined4 uVar1;
  char cVar2;
  undefined1 uVar3;
  undefined2 uVar4;
  int iVar5;
  int iVar6;
  undefined2 uVar7;
  undefined2 unaff_DS;
  bool bVar8;
  int local_e;
  int local_c;
  uint local_a;
  uint local_8;
  int local_4;
  
  local_c = 0;
  local_a = 0;
  local_8 = 0;
  do {
    bVar8 = false;
    if (local_c != 0) {
      if (local_c == 4) {
        *(int *)0x970 = *(int *)0x970 + 1;
        bVar8 = true;
      }
      else if (local_c == 3) {
        bVar8 = local_8 % 2 == 0;
        if (bVar8) {
          *(int *)0x970 = *(int *)0x970 + 1;
        }
      }
      else if (local_c == 2) {
        bVar8 = local_8 % 3 == 0;
        if (bVar8) {
          *(int *)0x970 = *(int *)0x970 + 1;
        }
      }
      else if ((local_c == 1) && (local_8 % 4 == 0)) {
        bVar8 = true;
        *(int *)0x970 = *(int *)0x970 + 1;
      }
    }
    if (((local_c == 0) && (local_a != 0)) && (*(int *)0x970 % 2 == 1)) {
      *(int *)0x970 = *(int *)0x970 + 1;
    }
    if (0x1f < *(int *)0x970) {
      *(int *)0x970 = *(int *)0x970 + -0x20;
    }
    FUN_1000_068b(7,0x1c,0xac,0xa104);
    uVar1 = *(undefined4 *)(((*(int *)0x970 + 3) % 4) * 4 + 0xa08);
    pole_blit_rle(3,0x73,0xa0,32000,0xa000,(int)uVar1,(int)((ulong)uVar1 >> 0x10));
    if (bVar8) {
      uVar4 = FUN_1ad9_0279();
      pc_speaker_sound_hz(uVar4);
    }
    local_4 = 0;
    while( true ) {
      uVar7 = 0;
      iVar6 = ((int)*(uint *)0x970 >> 0xf) + (uint)CARRY2(*(uint *)0x970,local_4 << 1);
      FUN_1ad9_0cb9();
      FUN_1ad9_0ca5();
      uVar4 = FUN_1ad9_0cab();
      FUN_1ad9_0dc9(0x1ad9,uVar4,uVar7,iVar6);
      FUN_1ad9_0ca5();
      iVar6 = FUN_1ad9_0cc5();
      FUN_1ad9_0ddc();
      FUN_1ad9_0ca5();
      iVar5 = FUN_1ad9_0cc5();
      uVar1 = *(undefined4 *)(*(int *)(local_4 * 2 + 0x50) * 4 + 0xa08);
      pole_blit_rle(7,iVar5 + 0xc4,iVar6 + 0x105,32000,0xa000,(int)uVar1,(int)((ulong)uVar1 >> 0x10)
                   );
      pc_speaker_no_sound();
      if (local_4 == 0xf) break;
      local_4 = local_4 + 1;
    }
    pc_speaker_no_sound();
    if (local_c != 0) {
      local_8 = local_8 + 1;
    }
    if (local_a < local_8) {
      iVar6 = pascal_random_bound(10);
      local_a = iVar6 + 5;
      if (local_c != 0) {
        local_c = local_c + -1;
      }
      local_8 = 0;
    }
    pole_blit_rle(7,0x98,0x10b,32000,0xa000,(int)*(undefined4 *)0xa48,
                  (int)((ulong)*(undefined4 *)0xa48 >> 0x10));
    FUN_1000_0725(0x1c,0xac,0x2404,0xa104);
    *(undefined1 *)0x964 = 7;
    cVar2 = FUN_1a77_02fa();
    if (cVar2 != '\0') {
      uVar3 = FUN_1a77_030c();
      *(undefined1 *)0x964 = uVar3;
    }
    if (*(char *)0x964 == '\x13') {
      *(int *)0x862 = 1 - *(int *)0x862;
    }
    if (*(char *)0x964 == '\t') {
      FUN_1000_07b9();
    }
    if (0 < *(int *)0x7b4) {
      *(undefined2 *)0x9f4 = 3;
      FUN_1a70_000b(0x9f4);
    }
    if ((local_c == 0) && (local_a == 0)) {
      if (*(int *)0x856 < 3) {
        FUN_1000_0858(0x32);
      }
      FUN_1000_0936();
      local_c = 4;
      iVar6 = pascal_random_bound(0x14);
      local_a = iVar6 + 10;
    }
    if (*(char *)0x964 == '\x1b') {
      FUN_1000_0000();
    }
  } while (((local_c != 0) || (local_a == 0)) || (*(int *)0x970 % 2 != 0));
  *(int *)0x972 = (0x1c - *(int *)0x970 / 2) % 0x10;
  *(undefined2 *)0x84e = *(undefined2 *)((*(int *)(*(int *)0x972 * 2 + 0x50) + -4) * 2 + 0x70);
  local_e = 1;
  while( true ) {
    pc_speaker_sound_hz((local_e * -0x1e + 1000) * *(int *)0x862);
    pascal_delay_ms(local_e / 5);
    pascal_delay_ms(local_e / 3);
    pc_speaker_no_sound();
    if (local_e == 0x1e) break;
    local_e = local_e + 1;
  }
  return;
}



/* 1000:302a FUN_1000_302a */

void FUN_1000_302a(int param_1)

{
  bool bVar1;
  char cVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  bVar1 = false;
  if (0 < *(int *)0x7b4) {
    *(undefined2 *)0x9f4 = 4;
    *(undefined2 *)0x9f8 = 0x140;
    *(undefined2 *)0x9fa = 100;
    FUN_1a70_000b(0x9f4);
  }
  *(undefined2 *)(param_1 + -8) = 1;
  FUN_1000_077e();
  do {
    FUN_1000_068b(7,0x14,0x1a,0xc800);
    pole_blit_rle(2,0xf0,*(int *)(param_1 + -8) * 0x3c + 0x12,32000,0xa000,(int)*(undefined4 *)0xa7c
                  ,(int)((ulong)*(undefined4 *)0xa7c >> 0x10));
    FUN_1000_0725(0x14,0x1a,0x4b00,0xc800);
    *(undefined1 *)0x964 = 7;
    cVar2 = FUN_1a77_02fa();
    if (cVar2 != '\0') {
      uVar3 = FUN_1a77_030c();
      *(undefined1 *)0x964 = uVar3;
    }
    if (*(char *)0x964 == '\x13') {
      *(int *)0x862 = 1 - *(int *)0x862;
    }
    if (*(char *)0x964 == '\t') {
      FUN_1000_07b9();
    }
    uVar3 = *(char *)0x964 == '\0';
    if ((bool)uVar3) {
      uVar4 = FUN_1a77_030c();
      *(undefined1 *)0x964 = uVar4;
      FUN_1ad9_08df(0x300a,0x1a77,*(undefined1 *)0x964);
      if (!(bool)uVar3) {
        *(int *)(param_1 + -8) = 1 - *(int *)(param_1 + -8);
      }
    }
    if (0 < *(int *)0x7b4) {
      *(undefined2 *)0x9f4 = 3;
      FUN_1a70_000b(0x9f4);
      if ((*(uint *)0x9f8 < 300) || (0x154 < *(uint *)0x9f8)) {
        *(int *)(param_1 + -8) = 1 - *(int *)(param_1 + -8);
        *(undefined2 *)0x9f4 = 4;
        *(undefined2 *)0x9f8 = 0x140;
        *(undefined2 *)0x9fa = 100;
        FUN_1a70_000b(0x9f4);
      }
    }
    if (*(char *)0x964 == '\x1b') {
      FUN_1000_0000();
    }
    if ((*(char *)0x964 == ' ') || ((0 < *(int *)0x7b4 && (*(int *)0x9f6 == 1)))) {
      bVar1 = true;
    }
    pascal_delay_ms(0x1e);
  } while (!bVar1);
  FUN_1000_068b(7,0x14,0x1a,0x4b00);
  return;
}



/* 1000:31cb pole_bonus_chests */

void __cdecl16near pole_bonus_chests(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 uVar3;
  undefined2 unaff_DS;
  int local_c;
  int local_a;
  int local_4;
  
  FUN_1000_068b(7,0x14,0x50,0xc800);
  pole_blit_rle(7,0x10b,6,32000,0xa000,(int)*(undefined4 *)0xa9c,
                (int)((ulong)*(undefined4 *)0xa9c >> 0x10));
  pole_blit_rle(7,0x113,0x40,32000,0xa000,(int)*(undefined4 *)0xa9c,
                (int)((ulong)*(undefined4 *)0xa9c >> 0x10));
  pole_blit_rle(7,0x100,0x42,32000,0xa000,(int)*(undefined4 *)0xaa0,
                (int)((ulong)*(undefined4 *)0xaa0 >> 0x10));
  local_4 = 0x28;
  while( true ) {
    pc_speaker_sound_hz((local_4 * -0x14 + 1000) * *(int *)0x862);
    FUN_1000_0725(0x14,local_4 * -2 + 0x50,local_4 * 0xa0 + 0x4b00,0xc800);
    pc_speaker_no_sound();
    pascal_delay_ms(local_4);
    if (local_4 == 0) break;
    local_4 = local_4 + -1;
  }
  FUN_1000_0858(0);
  FUN_1000_068b(7,0x14,0x33,0xc800);
  pc_speaker_sound_hz(*(int *)0x862 * 1000);
  pole_blit_rle(7,0x110,6,32000,0xa000,(int)*(undefined4 *)0xa98,
                (int)((ulong)*(undefined4 *)0xa98 >> 0x10));
  pc_speaker_no_sound();
  pc_speaker_sound_hz(*(int *)0x862 * 100);
  pole_blit_rle(7,0x118,0x40,32000,0xa000,(int)*(undefined4 *)0xa98,
                (int)((ulong)*(undefined4 *)0xa98 >> 0x10));
  pc_speaker_no_sound();
  pc_speaker_sound_hz(*(int *)0x862 * 500);
  FUN_1000_0725(0x14,0x50,0x4b00,0xc800);
  pc_speaker_no_sound();
  FUN_1000_0858(0x28);
  iVar2 = pascal_random_bound(0x14);
  iVar2 = (iVar2 + 10) * 2;
  local_c = 1;
  if (0 < iVar2) {
    local_4 = 1;
    while( true ) {
      pascal_random_bound(100);
      uVar3 = FUN_1ad9_0279();
      pc_speaker_sound_hz(uVar3);
      pascal_delay_ms(10);
      pc_speaker_no_sound();
      pascal_delay_ms(0x32);
      if (local_4 % 2 == 0) {
        local_c = 1 - local_c;
      }
      FUN_1000_068b(7,0x14,0x50,0xc800);
      if ((bool)((byte)local_4 & 1)) {
        pole_blit_rle(7,0x106,0x28,32000,0xa000,(int)*(undefined4 *)0xa98,
                      (int)((ulong)*(undefined4 *)0xa98 >> 0x10));
        pole_blit_rle(7,0x122,0x1e,32000,0xa000,(int)*(undefined4 *)0xa98,
                      (int)((ulong)*(undefined4 *)0xa98 >> 0x10));
      }
      else {
        pole_blit_rle(7,0x110,6,32000,0xa000,(int)*(undefined4 *)0xa98,
                      (int)((ulong)*(undefined4 *)0xa98 >> 0x10));
        pole_blit_rle(7,0x118,0x40,32000,0xa000,(int)*(undefined4 *)0xa98,
                      (int)((ulong)*(undefined4 *)0xa98 >> 0x10));
      }
      FUN_1000_0725(0x14,0x50,0x4b00,0xc800);
      if (local_4 == iVar2) break;
      local_4 = local_4 + 1;
    }
  }
  FUN_1000_0936();
  pole_host_dialogue(6);
  FUN_1000_302a(&stack0xfffe);
  FUN_1000_0936();
  FUN_1000_068b(7,0x14,0x50,0xc800);
  uVar1 = *(undefined4 *)((0x25 - local_a) * 4 + 0xa08);
  pole_blit_rle(7,(1 - local_a) * -5 + 0x110,6,32000,0xa000,(int)uVar1,(int)((ulong)uVar1 >> 0x10));
  uVar1 = *(undefined4 *)((local_a + 0x24) * 4 + 0xa08);
  pole_blit_rle(7,local_a * -5 + 0x118,0x40,32000,0xa000,(int)uVar1,(int)((ulong)uVar1 >> 0x10));
  FUN_1000_0725(0x14,0x50,0x4b00,0xc800);
  if (local_c == local_a) {
    *(int *)(*(int *)0x856 * 2 + 0x84e) = *(int *)(*(int *)0x856 * 2 + 0x84e) + 100;
    if (local_c == 1) {
      pole_blit_rle(7,0x100,0x42,0,0xa000,(int)*(undefined4 *)0xaa0,
                    (int)((ulong)*(undefined4 *)0xaa0 >> 0x10));
    }
    else {
      pole_blit_rle(7,0xf8,8,0,0xa000,(int)*(undefined4 *)0xaa0,
                    (int)((ulong)*(undefined4 *)0xaa0 >> 0x10));
    }
    pole_host_dialogue(7);
    pole_draw_score(*(undefined2 *)0x856);
  }
  else {
    pole_host_dialogue(8);
  }
  FUN_1000_0858(0);
  FUN_1000_0936();
  FUN_1000_068b(7,0x14,0x50,0x4b00);
  return;
}



/* 1000:35f9 FUN_1000_35f9 */

void FUN_1000_35f9(int param_1)

{
  bool bVar1;
  char cVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  bVar1 = false;
  if (0 < *(int *)0x7b4) {
    *(undefined2 *)0x9f4 = 4;
    *(undefined2 *)0x9f8 = 0x140;
    *(undefined2 *)0x9fa = 100;
    FUN_1a70_000b(0x9f4);
  }
  *(undefined2 *)(param_1 + -10) = 1;
  FUN_1000_077e();
  do {
    FUN_1000_068b(7,0x14,0x1a,0xc800);
    pole_blit_rle(2,0xf0,*(int *)(param_1 + -10) * 0x3c + 0x1e,32000,0xa000,
                  (int)*(undefined4 *)0xa7c,(int)((ulong)*(undefined4 *)0xa7c >> 0x10));
    FUN_1000_0725(0x14,0x1a,0x4b00,0xc800);
    *(undefined1 *)0x964 = 7;
    cVar2 = FUN_1a77_02fa();
    if (cVar2 != '\0') {
      uVar3 = FUN_1a77_030c();
      *(undefined1 *)0x964 = uVar3;
    }
    if (*(char *)0x964 == '\t') {
      FUN_1000_07b9();
    }
    if (*(char *)0x964 == '\x13') {
      *(int *)0x862 = 1 - *(int *)0x862;
    }
    uVar3 = *(char *)0x964 == '\0';
    if ((bool)uVar3) {
      uVar4 = FUN_1a77_030c();
      *(undefined1 *)0x964 = uVar4;
      FUN_1ad9_08df(0x35d9,0x1a77,*(undefined1 *)0x964);
      if (!(bool)uVar3) {
        *(int *)(param_1 + -10) = 1 - *(int *)(param_1 + -10);
      }
    }
    if (0 < *(int *)0x7b4) {
      *(undefined2 *)0x9f4 = 3;
      FUN_1a70_000b(0x9f4);
      if ((*(uint *)0x9f8 < 300) || (0x154 < *(uint *)0x9f8)) {
        *(int *)(param_1 + -10) = 1 - *(int *)(param_1 + -10);
        *(undefined2 *)0x9f4 = 4;
        *(undefined2 *)0x9f8 = 0x140;
        *(undefined2 *)0x9fa = 100;
        FUN_1a70_000b(0x9f4);
      }
    }
    if (*(char *)0x964 == '\x1b') {
      FUN_1000_0000();
    }
    if ((*(char *)0x964 == ' ') || ((0 < *(int *)0x7b4 && (*(int *)0x9f6 == 1)))) {
      bVar1 = true;
    }
    pascal_delay_ms(0x1e);
  } while (!bVar1);
  FUN_1000_068b(7,0x14,0x1a,0x4b00);
  return;
}



/* 1000:37eb pole_choice_prompt */

int pole_choice_prompt(int param_1)

{
  undefined2 uVar1;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar2;
  undefined2 uVar3;
  undefined1 local_1e [2];
  undefined1 local_1c [2];
  undefined1 local_1a [14];
  int local_c;
  int local_6;
  int local_4;
  
  uVar1 = 0x1000;
  FUN_1000_068b(7,0x14,0x50,0xc800);
  pole_blit_rle(2,0x10e,2,32000,0xa000,(int)*(undefined4 *)0xa78,
                (int)((ulong)*(undefined4 *)0xa78 >> 0x10));
  pole_blit_rle(2,0x10e,0x44,32000,0xa000,(int)*(undefined4 *)0xa78,
                (int)((ulong)*(undefined4 *)0xa78 >> 0x10));
  if (param_1 == 1) {
    puVar2 = local_1c;
    uVar1 = unaff_SS;
    FUN_1ad9_062a(0x379a,0x1000);
    pole_draw_font(32000,0xa000,8,0xd,0,0x122,0xc,puVar2,uVar1);
    puVar2 = local_1e;
    uVar1 = 0x1ad9;
    uVar3 = unaff_SS;
    FUN_1ad9_062a(0x37a8,0x1ad9);
    pole_draw_font(32000,0xa000,8,0xd,0,0x131,0xc,puVar2,uVar3);
  }
  if (param_1 == 2) {
    puVar2 = local_1a;
    uVar3 = unaff_SS;
    FUN_1ad9_062a(0x37b7,uVar1);
    pole_draw_font(32000,0xa000,8,0xd,0,0x122,0x12,puVar2,uVar3);
    puVar2 = local_1c;
    uVar1 = 0x1ad9;
    uVar3 = unaff_SS;
    FUN_1ad9_062a(0x37c3,0x1ad9);
    pole_draw_font(32000,0xa000,8,0xd,0,0x131,0x12,puVar2,uVar3);
  }
  if (param_1 == 3) {
    puVar2 = local_1c;
    uVar3 = unaff_SS;
    FUN_1ad9_062a(0x37d0,uVar1);
    pole_draw_font(32000,0xa000,8,0xd,0,0x122,0x12,puVar2,uVar3);
    puVar2 = local_1c;
    FUN_1ad9_062a(0x37dd,0x1ad9);
    pole_draw_font(32000,0xa000,8,0xd,0,0x131,0x12,puVar2,unaff_SS);
  }
  local_6 = 0x28;
  while( true ) {
    pc_speaker_sound_hz((local_6 * -0x14 + 1000) * *(int *)0x862);
    FUN_1000_0725(0x14,local_6 * -2 + 0x50,local_6 * 0xa0 + 0x4b00,0xc800);
    pc_speaker_no_sound();
    pascal_delay_ms(local_6);
    if (local_6 == 0) break;
    local_6 = local_6 + -1;
  }
  FUN_1000_35f9(&stack0xfffe);
  FUN_1000_068b(7,0x14,0x50,0x4b00);
  if (local_c == 1) {
    local_4 = 0;
  }
  else {
    local_4 = param_1;
  }
  return local_4;
}



/* 1000:3b8a pole_intro */

void __cdecl16near pole_intro(void)

{
  undefined2 uVar1;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar2;
  undefined1 local_10c [256];
  uint local_c;
  int local_a;
  uint local_8;
  int local_6;
  int local_4;
  
  FUN_174b_0b9e(7,1);
  FUN_174b_149e(7);
  FUN_174b_0b19(3,0,0);
  local_4 = 0;
  while( true ) {
    FUN_174b_13aa(0x159 - local_4,0x26c - local_4,0x159 - local_4,local_4 + 0x14);
    pascal_delay_ms(10);
    if (local_4 == 0xa0) break;
    local_4 = local_4 + 1;
  }
  FUN_1000_0858(0x28);
  local_4 = 0;
  while( true ) {
    FUN_174b_1362(0xb9 - local_4,0xb4 - local_4,0x159,0x14);
    FUN_174b_13aa(0xb9 - local_4,local_4 + 0x1cc,0xb9 - local_4,0xb4 - local_4);
    FUN_174b_1362(0x159,0x26c,0xb9 - local_4,local_4 + 0x1cc);
    pascal_delay_ms(5);
    if (local_4 == 0xa0) break;
    local_4 = local_4 + 1;
  }
  FUN_174b_0b19(0,0,0);
  FUN_174b_0b9e(7,1);
  FUN_174b_13aa(0x159,0x26c,0x19,0x14);
  FUN_174b_0b9e(4,1);
  local_6 = 1;
  while( true ) {
    local_4 = 0;
    while (FUN_174b_13aa(local_4 * 0x28 + 0x1b,local_6 * 10 + 0x14,local_4 * 0x28 + 0x19,
                         (local_6 + -1) * 10 + 0x14), local_4 != 8) {
      local_4 = local_4 + 1;
    }
    pascal_delay_ms(10);
    if (local_6 == 0x3c) break;
    local_6 = local_6 + 1;
  }
  local_6 = 1;
  while( true ) {
    local_4 = 0;
    while (FUN_174b_13aa(local_6 * 8 + 0x19,local_4 * 0x32 + 0x15,(local_6 + -1) * 8 + 0x19,
                         local_4 * 0x32 + 0x13), local_4 != 0xc) {
      local_4 = local_4 + 1;
    }
    pascal_delay_ms(10);
    if (local_6 == 0x28) break;
    local_6 = local_6 + 1;
  }
  FUN_1000_0858(0x32);
  pole_blit_rle(7,0x3c,0x5a,0,0xa000,(int)*(undefined4 *)0xac0,
                (int)((ulong)*(undefined4 *)0xac0 >> 0x10));
  pole_blit_rle(7,0x3c,0x118,0,0xa000,(int)*(undefined4 *)0xac4,
                (int)((ulong)*(undefined4 *)0xac4 >> 0x10));
  FUN_1000_0858(0x32);
  uVar1 = 0x1ad9;
  FUN_1ad9_0644(0xff,0x864,unaff_DS,0x39fd,0x1a77);
  local_c = (uint)*(byte *)0x864;
  if (local_c != 0) {
    local_8 = 1;
    while( true ) {
      if ((int)local_8 < 9) {
        local_a = -0xf;
      }
      else {
        local_a = 0;
      }
      local_4 = -1;
      while( true ) {
        local_6 = -1;
        while( true ) {
          puVar2 = local_10c;
          uVar1 = unaff_SS;
          FUN_1ad9_075a(*(undefined1 *)(local_8 + 0x864));
          pole_draw_font(0,0xa000,8,0xd,0,local_6 + 0xee,local_8 * 0x32 + local_4 + local_a,puVar2,
                         uVar1);
          if (local_6 == 2) break;
          local_6 = local_6 + 1;
        }
        if (local_4 == 1) break;
        local_4 = local_4 + 1;
      }
      pc_speaker_sound_hz(*(int *)0x862 * local_8 * 100);
      local_4 = 0;
      while( true ) {
        puVar2 = local_10c;
        uVar1 = unaff_SS;
        FUN_1ad9_075a(*(undefined1 *)(local_8 + 0x864));
        pole_draw_font(0,0xa000,8,0xd,0xf,local_4 + 0xee,local_8 * 0x32 + local_a,puVar2,uVar1);
        if (local_4 == 1) break;
        local_4 = local_4 + 1;
      }
      pc_speaker_no_sound();
      uVar1 = 0x1a77;
      pascal_delay_ms(0xfa);
      if (local_8 == local_c) break;
      local_8 = local_8 + 1;
    }
  }
  FUN_1ad9_0644(0xff,0x864,unaff_DS,0x3a0a,uVar1);
  pole_draw_font(0,0xa000,8,7,7,2,0x44,0x864,unaff_DS);
  FUN_1ad9_0644(0xff,0x864,unaff_DS,0x3a4a,0x1ad9);
  pole_draw_font(0,0xa000,8,7,7,0xc,0xb0,0x864,unaff_DS);
  FUN_1ad9_0644(0xff,0x864,unaff_DS,0x3a71,0x1ad9);
  pole_draw_font(0,0xa000,0x19,0xd,0,0x1b,0x50,0x864,unaff_DS);
  pole_draw_font(0,0xa000,0x19,0xd,0,0x1c,0x50,0x864,unaff_DS);
  FUN_1000_068b(0,0x50,0x46,0x6040);
  FUN_1ad9_0644(0xff,0x864,unaff_DS,0x3a85,0x1ad9);
  pole_draw_font(0,0xa000,8,7,7,0x136,0x1b,0x864,unaff_DS);
  FUN_1ad9_0644(0xff,0x864,unaff_DS,0x3acd,0x1ad9);
  pole_draw_font(0,0xa000,8,7,7,0x140,99,0x864,unaff_DS);
  FUN_1ad9_0644(0xff,0x864,unaff_DS,0x3b0c,0x1ad9);
  pole_draw_font(0,0xa000,8,7,7,0x14a,99,0x864,unaff_DS);
  FUN_1ad9_0644(0xff,0x864,unaff_DS,0x3b4b,0x1ad9);
  pole_draw_font(0,0xa000,8,7,7,0x154,99,0x864,unaff_DS);
  FUN_1000_0858(0);
  return;
}



/* 1000:4121 FUN_1000_4121 */

void __cdecl16near FUN_1000_4121(void)

{
  undefined2 unaff_SS;
  byte local_102 [256];
  
  FUN_1ad9_0644(0xff,local_102,unaff_SS,0x4099,0x1000);
  pole_draw_font(0,0xa000,8,7,0,0x14c,(uint)local_102[0] * -4 + 0x140,local_102,unaff_SS);
  FUN_1ad9_0644(0xff,local_102,unaff_SS,0x40d8,0x1ad9);
  pole_draw_font(0,0xa000,8,7,0,0x155,(uint)local_102[0] * -4 + 0x140,local_102,unaff_SS);
  return;
}



/* 1000:42b4 pole_prize_negotiation */

void __cdecl16near pole_prize_negotiation(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int iVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined2 uVar6;
  undefined2 uVar7;
  undefined1 *puVar8;
  undefined1 local_10e [256];
  undefined4 local_e;
  int local_8;
  int local_6;
  int local_4;
  
  FUN_1000_068b(7,0x50,0x15e,0);
  pole_blit_rle(7,10,10,0,0xa000,(int)*(undefined4 *)0xac0,
                (int)((ulong)*(undefined4 *)0xac0 >> 0x10));
  pole_blit_rle(7,10,200,0,0xa000,(int)*(undefined4 *)0xac4,
                (int)((ulong)*(undefined4 *)0xac4 >> 0x10));
  pole_blit_rle(7,0xac,0x1e0,0,0xa000,(int)*(undefined4 *)0xa74,
                (int)((ulong)*(undefined4 *)0xa74 >> 0x10));
  pole_blit_rle(0x10,0xad,0x1ff,0,0xa000,(int)*(undefined4 *)0xabc,
                (int)((ulong)*(undefined4 *)0xabc >> 0x10));
  pole_blit_rle(0x10,0xd1,0x214,0,0xa000,(int)*(undefined4 *)0xab4,
                (int)((ulong)*(undefined4 *)0xab4 >> 0x10));
  local_6 = 0;
  uVar1 = 0x1000;
  do {
    if (local_6 == 0) {
      FUN_1ad9_0644(0xff,0x864,unaff_DS,0x41be,uVar1);
      local_e = 10;
      uVar2 = 0x1ad9;
    }
    else if (local_6 == 1) {
      FUN_1ad9_0644(0xff,0x864,unaff_DS,0x41c2,uVar1);
      local_e = 100;
      uVar2 = 0x1ad9;
    }
    else if (local_6 == 2) {
      FUN_1ad9_0644(0xff,0x864,unaff_DS,0x41c7,uVar1);
      local_e = 10000;
      uVar2 = 0x1ad9;
    }
    else {
      uVar2 = uVar1;
      if (local_6 == 3) {
        uVar2 = 0x1ad9;
        FUN_1ad9_0644(0xff,0x864,unaff_DS,0x41cf,uVar1);
        local_e = 100000;
      }
    }
    pole_host_dialogue(0x11);
    local_4 = pole_choice_prompt(3);
    FUN_1000_0936();
    local_6 = local_6 + 1;
  } while ((local_6 < 4) && (uVar1 = uVar2, local_4 != 0));
  if (local_4 == 0) {
    pole_host_dialogue(0x12);
    do {
      local_e = CONCAT22((int)((ulong)local_e >> 0x10) - (uint)((int)local_e == 0),(int)local_e + -1
                        );
      uVar1 = pascal_random_bound(0x32);
      pc_speaker_sound_hz(uVar1);
      uVar5 = (undefined2)((ulong)*(undefined4 *)0xae8 >> 0x10);
      uVar4 = (undefined2)*(undefined4 *)0xae8;
      uVar7 = 0xa000;
      uVar6 = 0;
      uVar1 = pascal_random_bound(400);
      uVar2 = pascal_random_bound(0x127);
      pole_blit_rle(2,uVar2,uVar1,uVar6,uVar7,uVar4,uVar5);
      pc_speaker_no_sound();
      if (local_e < 0) break;
    } while ((0 < local_e._2_2_) || ((int)local_e != 0));
  }
  else {
    pole_host_dialogue(0x14);
    local_8 = 0xbe;
    FUN_1ad9_0644(0xff,0x864,unaff_DS,0x41d7,uVar2);
    local_8 = local_8 + 0x12;
    pole_draw_font(0,0xa000,8,0xd,0,local_8,(uint)*(byte *)0x864 * -4 + 0xf0,0x864,unaff_DS);
    FUN_1ad9_0644(0xff,0x864,unaff_DS,0x41fd,0x1ad9);
    local_8 = local_8 + 0x12;
    pole_draw_font(0,0xa000,8,0xd,0,local_8,(uint)*(byte *)0x864 * -4 + 0xf0,0x864,unaff_DS);
    puVar8 = local_10e;
    iVar3 = pascal_random_bound(10);
    FUN_1ad9_062a(iVar3 * 0x19 + 0x19a,unaff_DS);
    FUN_1ad9_06b7(0x4224,0x1ad9);
    FUN_1ad9_0644(0xff,0x864,unaff_DS,puVar8,unaff_SS);
    local_8 = local_8 + 0x12;
    pole_draw_font(0,0xa000,8,0xd,0xf,local_8,(uint)*(byte *)0x864 * -4 + 0xf0,0x864,unaff_DS);
    FUN_1ad9_0644(0xff,0x864,unaff_DS,0x4240,0x1ad9);
    local_8 = local_8 + 0x12;
    pole_draw_font(0,0xa000,8,0xd,0,local_8,(uint)*(byte *)0x864 * -4 + 0xf0,0x864,unaff_DS);
    FUN_1ad9_0644(0xff,0x864,unaff_DS,0x4261,0x1ad9);
    local_8 = local_8 + 0x12;
    pole_draw_font(0,0xa000,8,0xd,0xf,local_8,(uint)*(byte *)0x864 * -4 + 0xf0,0x864,unaff_DS);
    FUN_1ad9_0644(0xff,0x864,unaff_DS,0x4285,0x1ad9);
    local_8 = local_8 + 0x12;
    pole_draw_font(0,0xa000,8,0xd,0,local_8,(uint)*(byte *)0x864 * -4 + 0xf0,0x864,unaff_DS);
  }
  FUN_1000_4121();
  FUN_1000_0858(0);
  FUN_1000_0936();
  return;
}



/* 1000:47bd pole_final_highscores */

void __cdecl16near pole_final_highscores(void)

{
  uint uVar1;
  ulong uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  bool bVar5;
  undefined1 *puVar6;
  undefined2 uVar7;
  undefined1 local_10c [4];
  undefined1 local_108 [252];
  int local_c;
  int local_8;
  int local_6;
  int local_4;
  
  FUN_1000_068b(7,0x50,0x15e,0);
  pole_blit_rle(7,10,10,0,0xa000,(int)*(undefined4 *)0xac0,
                (int)((ulong)*(undefined4 *)0xac0 >> 0x10));
  pole_blit_rle(7,10,200,0,0xa000,(int)*(undefined4 *)0xac4,
                (int)((ulong)*(undefined4 *)0xac4 >> 0x10));
  pole_blit_rle(7,0xac,0x1e0,0,0xa000,(int)*(undefined4 *)0xa74,
                (int)((ulong)*(undefined4 *)0xa74 >> 0x10));
  pole_blit_rle(0x10,0xad,0x1ff,0,0xa000,(int)*(undefined4 *)0xabc,
                (int)((ulong)*(undefined4 *)0xabc >> 0x10));
  pole_blit_rle(0x10,0xd1,0x214,0,0xa000,(int)*(undefined4 *)0xab4,
                (int)((ulong)*(undefined4 *)0xab4 >> 0x10));
  FUN_1ad9_12f6(0xff,0x864,unaff_DS,0,*(int *)0x854,*(int *)0x854 >> 0xf);
  puVar6 = local_108;
  uVar7 = unaff_SS;
  FUN_1ad9_062a(0x46aa,0x1ad9);
  FUN_1ad9_06b7(0x864,unaff_DS);
  FUN_1ad9_06b7(0x46ca,0x1ad9);
  FUN_1ad9_0644(0xff,0x864,unaff_DS,puVar6,uVar7);
  pole_draw_font(0,0xa000,8,0xd,0,0xd0,(uint)*(byte *)0x864 * -4 + 0xf0,0x864,unaff_DS);
  FUN_1ad9_0644(0xff,0x864,unaff_DS,0x46d2,0x1ad9);
  pole_draw_font(0,0xa000,8,0xd,0,0xe2,(uint)*(byte *)0x864 * -4 + 0xf0,0x864,unaff_DS);
  puVar6 = local_108;
  uVar7 = unaff_SS;
  iVar4 = pascal_random_bound(10);
  FUN_1ad9_062a(iVar4 * 0x19 + 0x19a,unaff_DS);
  FUN_1ad9_06b7(0x46fc,0x1ad9);
  FUN_1ad9_0644(0xff,0x864,unaff_DS,puVar6,uVar7);
  pole_draw_font(0,0xa000,8,0xd,0xf,0xf4,(uint)*(byte *)0x864 * -4 + 0xf0,0x864,unaff_DS);
  FUN_1ad9_0644(0xff,0x864,unaff_DS,0x4718,0x1ad9);
  pole_draw_font(0,0xa000,8,0xd,0,0x106,(uint)*(byte *)0x864 * -4 + 0xf0,0x864,unaff_DS);
  FUN_1ad9_0644(0xff,0x864,unaff_DS,0x4739,0x1ad9);
  pole_draw_font(0,0xa000,8,0xd,0xf,0x118,(uint)*(byte *)0x864 * -4 + 0xf0,0x864,unaff_DS);
  FUN_1ad9_0644(0xff,0x864,unaff_DS,0x475d,0x1ad9);
  pole_draw_font(0,0xa000,8,0xd,0,0x12a,(uint)*(byte *)0x864 * -4 + 0xf0,0x864,unaff_DS);
  FUN_1000_4121();
  pole_host_dialogue(0xd);
  FUN_1000_0858(0);
  FUN_1000_0936();
  local_8 = 0;
  uVar1 = *(uint *)0x854;
  bVar5 = -1 < (int)uVar1 >> 0xf;
  if (((int)uVar1 < 0 && bVar5) || ((bVar5 && (*(uint *)0x5d0 < uVar1)))) {
    for (local_6 = 8; 1 < local_6; local_6 = local_6 + -1) {
      uVar1 = *(uint *)0x854;
      bVar5 = (int)uVar1 >> 0xf < 0;
      if ((-1 < (int)uVar1 || bVar5) &&
         ((bVar5 || (uVar1 <= *(uint *)((local_6 + -1) * 0xd + 0x568))))) break;
    }
    _local_c = CONCAT22(local_6 + 1,local_c);
    if (local_6 + 1 < 9) {
      for (local_4 = 8;
          FUN_1ad9_025d(0xd,local_4 * 0xd + 0x55d,unaff_DS,(local_4 + -1) * 0xd + 0x55d,unaff_DS),
          uVar3 = _local_c, uVar2 = (ulong)_local_c >> 0x10, bVar5 = local_4 != (int)uVar2,
          _local_c = uVar3, bVar5; local_4 = local_4 + -1) {
      }
    }
    *(undefined2 *)(local_6 * 0xd + 0x568) = *(undefined2 *)0x854;
    *(undefined1 *)(local_6 * 0xd + 0x55d) = 0;
    local_8 = local_6;
  }
  FUN_1000_068b(0,0x14,0xa0,0xb25c);
  FUN_1ad9_0644(0xff,0x864,unaff_DS,0x478c,0x1ad9);
  pole_draw_font(32000,0xa000,8,0xd,0xf,0xaa,0x1e9,0x864,unaff_DS);
  pole_draw_font(32000,0xa000,8,0xd,7,0xaa,0x1e8,0x864,unaff_DS);
  FUN_1ad9_0644(0xff,0x864,unaff_DS,0x479e,0x1ad9);
  pole_draw_font(32000,0xa000,8,0xd,0xf,0xb8,0x1e9,0x864,unaff_DS);
  pole_draw_font(32000,0xa000,8,0xd,7,0xb8,0x1e8,0x864,unaff_DS);
  local_4 = 1;
  while( true ) {
    local_c = local_4 * 0xd + 0x55d;
    if (local_4 == local_8) {
      local_6 = 0xf;
    }
    else {
      local_6 = 0xb;
    }
    FUN_1ad9_12f6(0xff,0x864,unaff_DS,0,local_4,local_4 >> 0xf);
    puVar6 = local_10c;
    uVar7 = unaff_SS;
    FUN_1ad9_062a(0x864,unaff_DS);
    FUN_1ad9_06b7(0x47b0,0x1ad9);
    FUN_1ad9_06b7(local_c,unaff_DS);
    FUN_1ad9_0644(0xff,0x864,unaff_DS,puVar6,uVar7);
    pole_draw_font(32000,0xa000,8,0xd,local_6 + -8,local_4 * 0xe + 0xc3,0x1e1,0x864,unaff_DS);
    pole_draw_font(32000,0xa000,8,0xd,local_6,local_4 * 0xe + 0xc3,0x1e0,0x864,unaff_DS);
    FUN_1ad9_12f6(0xff,0x864,unaff_DS,4,*(undefined2 *)(local_c + 0xb),0);
    puVar6 = local_10c;
    uVar7 = unaff_SS;
    FUN_1ad9_062a(0x864,unaff_DS);
    FUN_1ad9_06b7(0x47b2,0x1ad9);
    FUN_1ad9_0644(0xff,0x864,unaff_DS,puVar6,uVar7);
    pole_draw_font(32000,0xa000,8,0xd,local_6 + -8,local_4 * 0xe + 0xc3,0x24f,0x864,unaff_DS);
    pole_draw_font(32000,0xa000,8,0xd,local_6,local_4 * 0xe + 0xc3,0x24e,0x864,unaff_DS);
    if (local_4 == 8) break;
    local_4 = local_4 + 1;
  }
  local_4 = 0x50;
  while( true ) {
    pc_speaker_sound_hz((local_4 * -0x14 + 0x640) * *(int *)0x862);
    FUN_1000_0725(0x13,local_4 * -2 + 0xa0,local_4 * 0xa0 + 0x33cc,0xb0cc);
    pc_speaker_no_sound();
    pascal_delay_ms(local_4);
    if (local_4 == 0) break;
    local_4 = local_4 + -1;
  }
  if (0 < local_8) {
    pole_enter_highscore_name(local_8);
    FUN_1ad9_0644(0xff,0x864,unaff_DS,0x47b4,0x1a77);
    FUN_1ad9_1779(0x864,unaff_DS,0x7cc,unaff_DS);
    FUN_1ad9_17b0(0xd,0x7cc,unaff_DS);
    FUN_1ad9_020e();
    local_4 = 1;
    while( true ) {
      FUN_1ad9_1863(local_4 * 0xd + 0x55d,unaff_DS);
      FUN_1ad9_020e();
      if (local_4 == 8) break;
      local_4 = local_4 + 1;
    }
    FUN_1ad9_1828(0x7cc,unaff_DS);
    FUN_1ad9_020e();
  }
  FUN_1000_0858(0);
  return;
}



/* 1000:4f66 pole_credits */

void __cdecl16near pole_credits(void)

{
  undefined2 unaff_DS;
  undefined2 local_4;
  
  FUN_1000_0725(0x15,0xaa,0xb2fb,0x35fb);
  pole_blit_rle(0x10,0xad,0x1e1,32000,0xa000,(int)*(undefined4 *)0xad8,
                (int)((ulong)*(undefined4 *)0xad8 >> 0x10));
  FUN_1ad9_0644(0xff,0x864,unaff_DS,0x4ebd,0x1000);
  pole_draw_font(32000,0xa000,8,7,0xe,0xae,(uint)*(byte *)0x864 * -4 + 0x22d,0x864,unaff_DS);
  FUN_1ad9_0644(0xff,0x864,unaff_DS,0x4ecf,0x1ad9);
  pole_draw_font(32000,0xa000,8,7,0xe,0xf8,(uint)*(byte *)0x864 * -4 + 0x22d,0x864,unaff_DS);
  FUN_1ad9_0644(0xff,0x864,unaff_DS,0x4ee3,0x1ad9);
  pole_draw_font(32000,0xa000,8,7,0xe,0x100,(uint)*(byte *)0x864 * -4 + 0x22d,0x864,unaff_DS);
  FUN_1ad9_0644(0xff,0x864,unaff_DS,0x4ef5,0x1ad9);
  pole_draw_font(32000,0xa000,8,7,0xe,0x108,(uint)*(byte *)0x864 * -4 + 0x22d,0x864,unaff_DS);
  FUN_1ad9_0644(0xff,0x864,unaff_DS,0x4f08,0x1ad9);
  pole_draw_font(32000,0xa000,8,7,0xe,0x110,(uint)*(byte *)0x864 * -4 + 0x22d,0x864,unaff_DS);
  FUN_1ad9_0644(0xff,0x864,unaff_DS,0x4f18,0x1ad9);
  pole_draw_font(32000,0xa000,8,7,0xe,0x118,(uint)*(byte *)0x864 * -4 + 0x22d,0x864,unaff_DS);
  FUN_1ad9_0644(0xff,0x864,unaff_DS,0x4f2a,0x1ad9);
  pole_draw_font(32000,0xa000,8,7,0xe,0x120,(uint)*(byte *)0x864 * -4 + 0x22d,0x864,unaff_DS);
  FUN_1ad9_0644(0xff,0x864,unaff_DS,0x4f38,0x1ad9);
  pole_draw_font(32000,0xa000,8,7,0xe,0x128,(uint)*(byte *)0x864 * -4 + 0x22d,0x864,unaff_DS);
  FUN_1ad9_0644(0xff,0x864,unaff_DS,0x4f47,0x1ad9);
  pole_draw_font(32000,0xa000,8,7,0xe,0x130,(uint)*(byte *)0x864 * -4 + 0x22d,0x864,unaff_DS);
  FUN_1ad9_0644(0xff,0x864,unaff_DS,0x4f5a,0x1ad9);
  pole_draw_font(32000,0xa000,8,7,0xe,0x13a,(uint)*(byte *)0x864 * -4 + 0x22d,0x864,unaff_DS);
  local_4 = 0x50;
  while( true ) {
    pc_speaker_sound_hz((local_4 * -0x14 + 0x6a4) * *(int *)0x862);
    FUN_1000_0725(0x15,local_4 * -2 + 0xa0,local_4 * 0xa0 + 0x364b,0xb34b);
    pc_speaker_no_sound();
    pascal_delay_ms(local_4 / 2);
    if (local_4 == 0) break;
    local_4 = local_4 + -1;
  }
  FUN_1000_0858(0);
  pole_blit_rle(7,0xac,0x1e0,0,0xa000,(int)*(undefined4 *)0xa74,
                (int)((ulong)*(undefined4 *)0xa74 >> 0x10));
  pole_blit_rle(0x10,0xad,0x1ff,0,0xa000,(int)*(undefined4 *)0xabc,
                (int)((ulong)*(undefined4 *)0xabc >> 0x10));
  pole_blit_rle(0x10,0xd1,0x214,0,0xa000,(int)*(undefined4 *)0xab4,
                (int)((ulong)*(undefined4 *)0xab4 >> 0x10));
  return;
}



/* 1000:53b3 pole_introduce_players */

void __cdecl16near pole_introduce_players(void)

{
  undefined4 uVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar4;
  undefined1 local_16 [8];
  int local_e;
  int local_c;
  int local_a;
  int local_8;
  int local_6;
  int local_4;
  
  pole_host_dialogue(0x13);
  local_c = 0;
  while( true ) {
    if (local_c < 2) {
      local_e = *(int *)((*(int *)0x858 * 2 + 1 + local_c) * 2 + 0x55c);
    }
    else {
      local_e = 0;
    }
    if (local_c == 0) {
      local_8 = 0x30;
      local_a = 0x95;
    }
    else if (local_c == 1) {
      local_8 = 10;
      local_a = 0x95;
    }
    else if (local_c == 2) {
      local_8 = 0x1e;
      local_a = 0xdc;
    }
    local_4 = 0;
    while( true ) {
      FUN_1000_068b(7,10,0x5a,local_8 + 32000 + local_a * 0x50);
      if (local_4 < 3) {
        uVar1 = *(undefined4 *)((local_4 + 0x35) * 4 + 0xa08);
        pole_blit_rle(2,local_a,local_8 << 3,32000,0xa000,(int)uVar1,(int)((ulong)uVar1 >> 0x10));
      }
      else if (0 < local_e) {
        uVar1 = *(undefined4 *)(*(int *)(local_e * 0xd + -0xb) * 4 + 0xa08);
        pole_blit_rle(2,local_a,local_8 << 3,32000,0xa000,(int)uVar1,(int)((ulong)uVar1 >> 0x10));
      }
      if (local_c < 2) {
        FUN_1000_0725(10,0x5a,local_a * 0x50 + local_8,local_8 + 32000 + local_a * 0x50);
      }
      local_6 = 1;
      while( true ) {
        pc_speaker_sound_hz((local_6 * 10 + local_4 * 100 + 0x32) * *(int *)0x862);
        pascal_delay_ms(1);
        pc_speaker_no_sound();
        uVar2 = 0x1a77;
        pascal_delay_ms(local_4 * 4 + local_6 / 4);
        if (local_6 == 0x14) break;
        local_6 = local_6 + 1;
      }
      if (local_4 == 3) break;
      local_4 = local_4 + 1;
    }
    if (local_c == 0) {
      uVar2 = 0x1ad9;
      FUN_1ad9_0644(0xff,0x864,unaff_DS,0x5384,0x1a77);
    }
    uVar3 = uVar2;
    if (local_c == 1) {
      uVar3 = 0x1ad9;
      FUN_1ad9_0644(0xff,0x864,unaff_DS,0x5391,uVar2);
    }
    uVar2 = uVar3;
    if (local_c == 2) {
      uVar2 = 0x1ad9;
      FUN_1ad9_0644(0xff,0x864,unaff_DS,0x539e,uVar3);
    }
    if (local_e == 0) {
      pole_draw_font(0,0xa000,8,0xd,0,local_a + 0x48,(local_8 + 9) * 8,0x864,unaff_DS);
      puVar4 = local_16;
      uVar3 = unaff_SS;
      FUN_1ad9_062a(0x53ab,uVar2);
      pole_draw_font(0,0xa000,8,0xd,0,local_a + 0x56,(local_8 + 9) * 8 + 0x18,puVar4,uVar3);
    }
    else {
      pole_draw_font(0,0xa000,8,0xd,0,local_a + -0x1d,local_8 << 3,0x864,unaff_DS);
      pole_draw_font(0,0xa000,8,0xd,0,local_a + -0x10,local_8 * 8 + 4,local_e * 0xd + -9,unaff_DS);
    }
    if (local_c == 2) break;
    local_c = local_c + 1;
  }
  FUN_1000_0858(0);
  FUN_1000_0936();
  return;
}



/* 1000:56b2 entry */

/* WARNING: This function may have set the stack pointer */

void entry(void)

{
  int *piVar1;
  char cVar2;
  int *piVar3;
  undefined4 uVar4;
  int iVar5;
  undefined2 uVar6;
  byte bVar7;
  char cVar8;
  byte bVar9;
  undefined2 unaff_BP;
  int *piVar10;
  char *pcVar11;
  undefined2 uVar12;
  undefined2 unaff_DS;
  undefined2 uVar13;
  bool bVar14;
  
  DAT_1c79_4ebe = 0x1000;
  DAT_1c79_4ebc = 0x56b7;
  FUN_1ad9_0000();
  DAT_1c79_4ebe = 0x1ad9;
  DAT_1c79_4ebc = 0x56bc;
  FUN_1a77_0000();
  DAT_1c79_4ebe = 0x1a77;
  DAT_1c79_4ebc = 0x56c1;
  FUN_174b_1019();
  DAT_1c79_4dbc = 0x174b;
  DAT_1c79_4dba = 0x56cd;
  DAT_1c79_4ebe = unaff_BP;
  FUN_1ad9_11d7();
  DAT_1c79_4dbc = 0x56d0;
  pole_load_resources();
  DAT_1c79_4dbc = 0x56d3;
  pole_init_ega_palette();
  *(undefined2 *)0x862 = 1;
  *(undefined2 *)0x96e = 1;
  while (*(undefined2 *)(*(int *)0x96e * 2 + 0x55c) = *(undefined2 *)0x96e, *(int *)0x96e != 6) {
    *(int *)0x96e = *(int *)0x96e + 1;
  }
  *(undefined2 *)0x85a = 1;
  while( true ) {
    DAT_1c79_4dbc = 6;
    DAT_1c79_4dba = 0x1ad9;
    DAT_1c79_4db8 = 0x570e;
    iVar5 = pascal_random_bound();
    *(int *)0x96e = iVar5 + 1;
    DAT_1c79_4dbc = 6;
    DAT_1c79_4dba = 0x1ad9;
    uVar12 = 0x1ad9;
    DAT_1c79_4db8 = 0x571b;
    iVar5 = pascal_random_bound();
    *(int *)0x7b6 = iVar5 + 1;
    *(undefined2 *)0x85c = *(undefined2 *)(*(int *)0x96e * 2 + 0x55c);
    *(undefined2 *)(*(int *)0x96e * 2 + 0x55c) = *(undefined2 *)(*(int *)0x7b6 * 2 + 0x55c);
    *(undefined2 *)(*(int *)0x7b6 * 2 + 0x55c) = *(undefined2 *)0x85c;
    if (*(int *)0x85a == 0x14) break;
    *(int *)0x85a = *(int *)0x85a + 1;
  }
  DAT_1c79_4dbc = 0x5757;
  pole_intro();
  *(undefined2 *)0x858 = 0;
  *(undefined2 *)0x96e = 1;
  while (*(undefined2 *)(*(int *)0x96e * 2 + 0x84e) = 0, *(int *)0x96e != 3) {
    *(int *)0x96e = *(int *)0x96e + 1;
  }
  *(undefined2 *)0x96e = 0;
  while (*(undefined2 *)(*(int *)0x96e * 2 + 0x6aa) = 0, *(int *)0x96e != 2) {
    *(int *)0x96e = *(int *)0x96e + 1;
  }
  do {
    *(undefined2 *)0x96e = 1;
    while( true ) {
      DAT_1c79_4dbc = 4;
      DAT_1c79_4db8 = 0x57ae;
      DAT_1c79_4dba = uVar12;
      pascal_random_bound();
      DAT_1c79_4dbc = 0x1ad9;
      uVar12 = 0x1ad9;
      DAT_1c79_4dba = 0x57c5;
      uVar6 = FUN_1ad9_0279();
      *(undefined2 *)(*(int *)0x96e * 2 + 0x84e) = uVar6;
      if (*(int *)0x96e == 2) break;
      *(int *)0x96e = *(int *)0x96e + 1;
    }
    out(0x3ce,5);
    out(0x3cf,0);
    DAT_1c79_4dbc = 1;
    DAT_1c79_4dba = 3;
    DAT_1c79_4db8 = 0x1ad9;
    DAT_1c79_4db6 = 0x57ef;
    FUN_174b_0b9e();
    DAT_1c79_4dbc = 0;
    DAT_1c79_4dba = 0;
    DAT_1c79_4db8 = 0x280;
    DAT_1c79_4db6 = 10;
    DAT_1c79_4db4 = 0x174b;
    DAT_1c79_4db2 = 0x5802;
    FUN_174b_13aa();
    DAT_1c79_4dbc = 1;
    DAT_1c79_4dba = 8;
    DAT_1c79_4db8 = 0x174b;
    DAT_1c79_4db6 = 0x580f;
    FUN_174b_0b9e();
    DAT_1c79_4dbc = 0;
    DAT_1c79_4dba = 10;
    DAT_1c79_4db8 = 0x280;
    DAT_1c79_4db6 = 0xc;
    DAT_1c79_4db4 = 0x174b;
    DAT_1c79_4db2 = 0x5823;
    FUN_174b_13aa();
    DAT_1c79_4dbc = 1;
    DAT_1c79_4dba = 1;
    DAT_1c79_4db8 = 0x174b;
    DAT_1c79_4db6 = 0x5830;
    FUN_174b_0b9e();
    DAT_1c79_4dbc = 0;
    DAT_1c79_4dba = 0xd;
    DAT_1c79_4db8 = 0x280;
    DAT_1c79_4db6 = 0x6b;
    DAT_1c79_4db4 = 0x174b;
    DAT_1c79_4db2 = 0x5844;
    FUN_174b_13aa();
    DAT_1c79_4dbc = 1;
    DAT_1c79_4dba = 8;
    DAT_1c79_4db8 = 0x174b;
    DAT_1c79_4db6 = 0x5851;
    FUN_174b_0b9e();
    DAT_1c79_4dbc = 0;
    DAT_1c79_4dba = 0x6c;
    DAT_1c79_4db8 = 0x280;
    DAT_1c79_4db6 = 0x6e;
    DAT_1c79_4db4 = 0x174b;
    DAT_1c79_4db2 = 0x5865;
    FUN_174b_13aa();
    DAT_1c79_4dbc = 1;
    DAT_1c79_4dba = 7;
    DAT_1c79_4db8 = 0x174b;
    DAT_1c79_4db6 = 0x5872;
    FUN_174b_0b9e();
    DAT_1c79_4dbc = 0;
    DAT_1c79_4dba = 0x6f;
    DAT_1c79_4db8 = 0x280;
    DAT_1c79_4db6 = 0x15e;
    DAT_1c79_4db4 = 0x174b;
    DAT_1c79_4db2 = 0x5886;
    FUN_174b_13aa();
    DAT_1c79_4dbc = 1;
    DAT_1c79_4dba = 8;
    DAT_1c79_4db8 = 0x174b;
    DAT_1c79_4db6 = 0x5893;
    FUN_174b_0b9e();
    DAT_1c79_4dbc = 0;
    DAT_1c79_4dba = 0x14a;
    DAT_1c79_4db8 = 0x280;
    DAT_1c79_4db6 = 0x14b;
    DAT_1c79_4db4 = 0x174b;
    DAT_1c79_4db2 = 0x58a7;
    FUN_174b_13aa();
    *(undefined2 *)0x85a = 0;
    DAT_1c79_4dba = 0x174b;
    while( true ) {
      DAT_1c79_4dbc = 3;
      DAT_1c79_4db8 = 0x58bb;
      iVar5 = pascal_random_bound();
      uVar4 = *(undefined4 *)((iVar5 + 0x1f) * 4 + 0xa08);
      DAT_1c79_4dbc = (int)((ulong)uVar4 >> 0x10);
      DAT_1c79_4dba = (int)uVar4;
      DAT_1c79_4db8 = 0xa000;
      DAT_1c79_4db6 = 0;
      DAT_1c79_4db4 = (int)(((ulong)*(uint *)0x85a % 0xc) * 0x34) + 5;
      DAT_1c79_4db2 = (*(uint *)0x85a / 0xc) * 0x1f + 0xf;
      DAT_1c79_4db0 = 1;
      DAT_1c79_4dae = 0x5902;
      pole_blit_rle();
      if (*(int *)0x85a == 0x23) break;
      *(int *)0x85a = *(int *)0x85a + 1;
      DAT_1c79_4dba = 0x1ad9;
    }
    DAT_1c79_4dbc = (int)((ulong)*(undefined4 *)0xaa8 >> 0x10);
    DAT_1c79_4dba = (int)*(undefined4 *)0xaa8;
    DAT_1c79_4db8 = 0xa000;
    DAT_1c79_4db6 = 0;
    DAT_1c79_4db4 = 0;
    DAT_1c79_4db2 = 0x19;
    DAT_1c79_4db0 = 7;
    DAT_1c79_4dae = 0x5927;
    pole_blit_rle();
    DAT_1c79_4dbc = (int)((ulong)*(undefined4 *)0xaac >> 0x10);
    DAT_1c79_4dba = (int)*(undefined4 *)0xaac;
    DAT_1c79_4db8 = 0xa000;
    DAT_1c79_4db6 = 0;
    DAT_1c79_4db4 = 600;
    DAT_1c79_4db2 = 0x19;
    DAT_1c79_4db0 = 7;
    DAT_1c79_4dae = 0x5946;
    pole_blit_rle();
    DAT_1c79_4dbc = (int)((ulong)*(undefined4 *)0xa90 >> 0x10);
    DAT_1c79_4dba = (int)*(undefined4 *)0xa90;
    DAT_1c79_4db8 = 0xa000;
    DAT_1c79_4db6 = 0;
    DAT_1c79_4db4 = 0x45;
    DAT_1c79_4db2 = 3;
    DAT_1c79_4db0 = 1;
    DAT_1c79_4dae = 0x5965;
    pole_blit_rle();
    DAT_1c79_4dbc = (int)((ulong)*(undefined4 *)0xa90 >> 0x10);
    DAT_1c79_4dba = (int)*(undefined4 *)0xa90;
    DAT_1c79_4db8 = 0xa000;
    DAT_1c79_4db6 = 0;
    DAT_1c79_4db4 = 0x22f;
    DAT_1c79_4db2 = 3;
    DAT_1c79_4db0 = 1;
    DAT_1c79_4dae = 0x5984;
    pole_blit_rle();
    out(0x3ce,5);
    out(0x3cf,0);
    DAT_1c79_4dbc = 1;
    DAT_1c79_4dba = 7;
    DAT_1c79_4db8 = 0x1ad9;
    DAT_1c79_4db6 = 0x599d;
    FUN_174b_0b9e();
    DAT_1c79_4dbc = 0x78;
    DAT_1c79_4dba = 0xf;
    DAT_1c79_4db8 = 0x208;
    DAT_1c79_4db6 = 0x5f;
    DAT_1c79_4db4 = 0x174b;
    DAT_1c79_4db2 = 0x59b2;
    FUN_174b_13aa();
    DAT_1c79_4dbc = 1;
    DAT_1c79_4dba = 8;
    DAT_1c79_4db8 = 0x174b;
    DAT_1c79_4db6 = 0x59bf;
    FUN_174b_0b9e();
    DAT_1c79_4dbc = 0;
    DAT_1c79_4dba = 0x174b;
    DAT_1c79_4db8 = 0x59c7;
    FUN_174b_149e();
    *(undefined2 *)0x96e = 0;
    while( true ) {
      DAT_1c79_4dbc = 0x78;
      DAT_1c79_4dba = *(int *)0x96e * 0x14 + 0xf;
      DAT_1c79_4db8 = 0x208;
      DAT_1c79_4db6 = *(int *)0x96e * 0x14 + 0xf;
      DAT_1c79_4db4 = 0x174b;
      DAT_1c79_4db2 = 0x59f7;
      FUN_174b_1362();
      if (*(int *)0x96e == 4) break;
      *(int *)0x96e = *(int *)0x96e + 1;
    }
    *(undefined2 *)0x96e = 0;
    while( true ) {
      DAT_1c79_4dbc = *(int *)0x96e * 0x10 + 0x78;
      DAT_1c79_4dba = 0x5f;
      DAT_1c79_4db8 = *(int *)0x96e * 0x10 + 0x78;
      DAT_1c79_4db6 = 0xf;
      DAT_1c79_4db4 = 0x174b;
      uVar12 = 0x174b;
      DAT_1c79_4db2 = 0x5a2e;
      FUN_174b_1362();
      if (*(int *)0x96e == 0x19) break;
      *(int *)0x96e = *(int *)0x96e + 1;
    }
    iVar5 = *(int *)0x858;
    if (iVar5 == 0) {
      DAT_1c79_4dbc = 0x174b;
      DAT_1c79_4dba = 0x568e;
      DAT_1c79_4db6 = 0x864;
      DAT_1c79_4db4 = 0xff;
      DAT_1c79_4db2 = 0x174b;
      uVar12 = 0x1ad9;
      DAT_1c79_4db0 = 0x5a50;
      FUN_1ad9_0644();
    }
    else if (iVar5 == 1) {
      DAT_1c79_4dbc = 0x174b;
      DAT_1c79_4dba = 0x569c;
      DAT_1c79_4db6 = 0x864;
      DAT_1c79_4db4 = 0xff;
      DAT_1c79_4db2 = 0x174b;
      uVar12 = 0x1ad9;
      DAT_1c79_4db0 = 0x5a6a;
      FUN_1ad9_0644();
    }
    else if (iVar5 == 2) {
      DAT_1c79_4dbc = 0x174b;
      DAT_1c79_4dba = 0x56a8;
      DAT_1c79_4db6 = 0x864;
      DAT_1c79_4db4 = 0xff;
      DAT_1c79_4db2 = 0x174b;
      uVar12 = 0x1ad9;
      DAT_1c79_4db0 = 0x5a84;
      FUN_1ad9_0644();
    }
    DAT_1c79_4dba = 0x864;
    DAT_1c79_4db8 = 0xcc;
    DAT_1c79_4db6 = 0x4e;
    DAT_1c79_4db4 = 0;
    DAT_1c79_4db2 = 0xd;
    DAT_1c79_4db0 = 0x10;
    DAT_1c79_4dae = 0xa000;
    DAT_1c79_4dac = 0;
    DAT_1c79_4daa = 0x5aa9;
    pole_draw_font();
    DAT_1c79_4dbc = (int)((ulong)*(undefined4 *)0xa74 >> 0x10);
    DAT_1c79_4dba = (int)*(undefined4 *)0xa74;
    DAT_1c79_4db8 = 0xa000;
    DAT_1c79_4db6 = 0;
    DAT_1c79_4db4 = 0x1e0;
    DAT_1c79_4db2 = 0xac;
    DAT_1c79_4db0 = 7;
    DAT_1c79_4dae = 0x5ac8;
    pole_blit_rle();
    DAT_1c79_4dbc = (int)((ulong)*(undefined4 *)0xabc >> 0x10);
    DAT_1c79_4dba = (int)*(undefined4 *)0xabc;
    DAT_1c79_4db8 = 0xa000;
    DAT_1c79_4db6 = 0;
    DAT_1c79_4db4 = 0x1ff;
    DAT_1c79_4db2 = 0xad;
    DAT_1c79_4db0 = 0x10;
    DAT_1c79_4dae = 0x5ae7;
    pole_blit_rle();
    DAT_1c79_4dbc = (int)((ulong)*(undefined4 *)0xab4 >> 0x10);
    DAT_1c79_4dba = (int)*(undefined4 *)0xab4;
    DAT_1c79_4db8 = 0xa000;
    DAT_1c79_4db6 = 0;
    DAT_1c79_4db4 = 0x214;
    DAT_1c79_4db2 = 0xd1;
    DAT_1c79_4db0 = 0x10;
    DAT_1c79_4dae = 0x5b06;
    pole_blit_rle();
    *(undefined2 *)0x85a = 0;
    while( true ) {
      DAT_1c79_4dbc = (int)((ulong)*(undefined4 *)0xa4c >> 0x10);
      DAT_1c79_4dba = (int)*(undefined4 *)0xa4c;
      DAT_1c79_4db8 = 0xa000;
      DAT_1c79_4db6 = 0;
      DAT_1c79_4db4 = *(int *)0x85a * 0x14;
      DAT_1c79_4db2 = 0x14c;
      DAT_1c79_4db0 = 8;
      DAT_1c79_4dae = 0x5b35;
      pole_blit_rle();
      if (*(int *)0x85a == 0x1f) break;
      *(int *)0x85a = *(int *)0x85a + 1;
    }
    *(undefined2 *)0x85a = 0;
    DAT_1c79_4db6 = uVar12;
    while( true ) {
      DAT_1c79_4dbc = 0x1d7d;
      DAT_1c79_4dba = 0x3d7e;
      DAT_1c79_4db8 =
           CONCAT11((char)((uint)(*(int *)0x85a + 1) >> 8),*(undefined1 *)(*(int *)0x85a + 0x9b));
      DAT_1c79_4db4 = 0x5b5d;
      FUN_1ad9_075a();
      DAT_1c79_4db8 = *(int *)0x85a * 0x14 + 4;
      DAT_1c79_4db6 = 0x14e;
      DAT_1c79_4db4 = 0;
      DAT_1c79_4db2 = 0xd;
      DAT_1c79_4db0 = 8;
      DAT_1c79_4dae = 0xa000;
      DAT_1c79_4dac = 0;
      DAT_1c79_4daa = 0x5b85;
      pole_draw_font();
      if (*(int *)0x85a == 0x1f) break;
      *(int *)0x85a = *(int *)0x85a + 1;
      DAT_1c79_4db6 = 0x1ad9;
    }
    *(undefined2 *)0x970 = 0;
    DAT_1c79_4dbc = 0x5b94;
    pole_draw_wheel();
    DAT_1c79_4dbc = 0x5b97;
    pole_introduce_players();
    *(undefined2 *)0x96e = 0;
    while (*(undefined2 *)(*(int *)0x96e * 2 + 0x628) = 0, *(int *)0x96e != 0x1f) {
      *(int *)0x96e = *(int *)0x96e + 1;
    }
    *(undefined2 *)0x96e = 1;
    while( true ) {
      DAT_1c79_4dbc = *(undefined2 *)0x96e;
      DAT_1c79_4dba = 0x5bc8;
      pole_draw_score();
      if (*(int *)0x96e == 3) break;
      *(int *)0x96e = *(int *)0x96e + 1;
    }
    DAT_1c79_4dbc = 0x5bd2;
    pole_load_word_pair();
    DAT_1c79_4dbc = 1;
    DAT_1c79_4dba = 8;
    DAT_1c79_4db8 = 0x1ad9;
    DAT_1c79_4db6 = 0x5bdf;
    FUN_174b_0b9e();
    DAT_1c79_4ebc = (uint)*(byte *)0x67e;
    if (DAT_1c79_4ebc != 0) {
      *(undefined2 *)0x96e = 1;
      while (*(undefined2 *)(*(int *)0x96e * 2 + 0x5d6) = 0, *(uint *)0x96e != DAT_1c79_4ebc) {
        *(int *)0x96e = *(int *)0x96e + 1;
      }
    }
    DAT_1c79_4ebc = (uint)*(byte *)0x67e;
    if (DAT_1c79_4ebc != 0) {
      *(undefined2 *)0x96e = 1;
      while( true ) {
        DAT_1c79_4dbc = (*(int *)0x96e + 5) * 0x10 + 0x79;
        DAT_1c79_4dba = 0x24;
        DAT_1c79_4db8 = (*(int *)0x96e + 5) * 0x10 + 0x86;
        DAT_1c79_4db6 = 0x36;
        DAT_1c79_4db4 = 0x174b;
        DAT_1c79_4db2 = 0x5c50;
        FUN_174b_13aa();
        if (*(uint *)0x96e == DAT_1c79_4ebc) break;
        *(int *)0x96e = *(int *)0x96e + 1;
      }
    }
    uVar12 = 0x174b;
    DAT_1c79_4dbc = 9;
    DAT_1c79_4dba = 0x5c5f;
    pole_host_dialogue();
    DAT_1c79_4dbc = 0x32;
    DAT_1c79_4dba = 0x5c66;
    FUN_1000_0858();
    DAT_1c79_4dbc = 0x5c69;
    FUN_1000_0936();
    DAT_1c79_4dbc = 10;
    DAT_1c79_4dba = 0x5c70;
    pole_host_dialogue();
    DAT_1c79_4dbc = 0;
    DAT_1c79_4dba = 0x5c76;
    FUN_1000_0858();
    DAT_1c79_4dbc = 0x5c79;
    FUN_1000_0936();
    *(undefined2 *)0x856 = 3;
    *(undefined2 *)0x5d4 = 0;
    do {
      if (*(int *)0x5d4 == 3) {
        DAT_1c79_4dbc = 5;
        DAT_1c79_4dba = 0x5c92;
        pole_host_dialogue();
        DAT_1c79_4dbc = 0x5c95;
        pole_bonus_chests();
        *(undefined2 *)0x5d4 = 0;
      }
      *(undefined2 *)0x5d6 = 0;
      if (3 < *(int *)0x856) {
        *(undefined2 *)0x856 = 1;
      }
      DAT_1c79_4dbc = 1;
      DAT_1c79_4dba = 0x5cb3;
      pole_host_dialogue();
      *(undefined2 *)0x5d2 = 0;
      if (*(int *)0x856 == 3) {
        DAT_1c79_4dbc = 1;
        DAT_1c79_4dba = 0x5cc6;
        uVar6 = pole_choice_prompt();
        *(undefined2 *)0x5d2 = uVar6;
      }
      if (*(int *)0x5d2 == 0) {
        DAT_1c79_4dbc = 0x5cd6;
        pole_spin_wheel();
        if (*(int *)0x84e != 100) {
          *(int *)0x5d4 = *(int *)0x5d4 + 1;
        }
        DAT_1c79_4dbc = 2;
        DAT_1c79_4dba = 0x5ce8;
        pole_host_dialogue();
        if ((*(int *)0x84e == 300) && (*(int *)0x856 == 3)) {
          DAT_1c79_4dbc = 2;
          DAT_1c79_4dba = 0x5cfe;
          uVar6 = pole_choice_prompt();
          *(undefined2 *)0x5d2 = uVar6;
          if (*(int *)0x5d2 == 0) {
            DAT_1c79_4dbc = 0x5d0b;
            FUN_1000_0936();
            DAT_1c79_4dbc = 0xf;
            DAT_1c79_4dba = 0x5d12;
            pole_host_dialogue();
          }
        }
        if (*(int *)0x5d2 == 0) {
          DAT_1c79_4dbc = 0x28;
          DAT_1c79_4dba = 0x5d23;
          FUN_1000_0858();
          DAT_1c79_4dbc = 0x5d26;
          FUN_1000_0936();
          if (*(int *)0x84e < 0) {
            *(undefined2 *)(*(int *)0x856 * 2 + 0x84e) = 0;
            DAT_1c79_4dbc = *(undefined2 *)0x856;
            DAT_1c79_4dba = 0x5d40;
            pole_draw_score();
          }
          if (*(int *)0x84e < 1) {
            *(int *)0x856 = *(int *)0x856 + 1;
            *(undefined2 *)0x5d4 = 0;
          }
          else {
            if (*(int *)0x84e == 100) {
              DAT_1c79_4dbc = 0x5d5c;
              pole_plus_select_position();
            }
            else {
              DAT_1c79_4dbc = 0x5d61;
              pole_select_letter();
            }
            if (*(int *)0x5d6 < 1) {
              *(int *)0x856 = *(int *)0x856 + 1;
              *(undefined2 *)0x5d4 = 0;
            }
            else {
              DAT_1c79_4dbc = 0x5d6b;
              pole_reveal_and_award();
            }
          }
          *(undefined2 *)0x7b6 = 0;
          DAT_1c79_4ebc = (uint)*(byte *)0x67e;
          if (DAT_1c79_4ebc != 0) {
            *(undefined2 *)0x96e = 1;
            while( true ) {
              if (*(int *)(*(int *)0x96e * 2 + 0x5d6) == 0) {
                *(int *)0x7b6 = *(int *)0x7b6 + 1;
              }
              if (*(uint *)0x96e == DAT_1c79_4ebc) break;
              *(int *)0x96e = *(int *)0x96e + 1;
            }
          }
        }
      }
    } while ((*(int *)0x7b6 != 0) && (*(int *)0x5d2 < 1));
    if (*(int *)0x7b6 == 0) {
      DAT_1c79_4dbc = 4;
      DAT_1c79_4dba = 0x5dcc;
      pole_host_dialogue();
      DAT_1c79_4dbc = 0x32;
      DAT_1c79_4dba = 0x5dd3;
      FUN_1000_0858();
      DAT_1c79_4dbc = 0x5dd6;
      FUN_1000_0936();
      if (*(int *)0x856 == 3) {
        *(undefined2 *)0x5d2 = 0;
      }
      else {
        *(undefined2 *)0x5d2 = 1;
      }
    }
    else {
      DAT_1c79_4dbc = 0x5def;
      FUN_1000_0936();
      if (*(int *)0x5d2 == 2) {
        DAT_1c79_4dbc = 0x5df9;
        pole_prize_negotiation();
      }
      else if (0 < *(int *)0x5d2) {
        DAT_1c79_4dbc = 0x5e05;
        uVar6 = pole_guess_full_word();
        *(undefined2 *)0x5d2 = uVar6;
        if (*(int *)0x5d2 == 0) {
          DAT_1c79_4dbc = 0xb;
          DAT_1c79_4dba = 0x5e16;
          pole_host_dialogue();
        }
        else {
          DAT_1c79_4dbc = 0xc;
          DAT_1c79_4dba = 0x5e1f;
          pole_host_dialogue();
        }
      }
      DAT_1c79_4dbc = 0x32;
      DAT_1c79_4dba = 0x5e26;
      FUN_1000_0858();
      DAT_1c79_4dbc = 0x5e29;
      FUN_1000_0936();
    }
    if (*(int *)0x5d2 == 0) {
      *(int *)0x858 = *(int *)0x858 + 1;
      DAT_1c79_4dbc = 0x10;
      DAT_1c79_4dba = 0x5e3b;
      pole_host_dialogue();
      DAT_1c79_4dbc = 0;
      DAT_1c79_4dba = 0x5e41;
      FUN_1000_0858();
      DAT_1c79_4dbc = 0x5e44;
      FUN_1000_0936();
      DAT_1c79_4dbc = 0x5e47;
      pole_credits();
    }
  } while ((*(int *)0x5d2 < 1) && (*(int *)0x858 < 3));
  if (*(int *)0x858 < 3) {
    DAT_1c79_4dbc = 0xe;
    DAT_1c79_4dba = 0x5e6b;
    pole_host_dialogue();
    DAT_1c79_4dbc = 0;
    DAT_1c79_4dba = 0x5e71;
    FUN_1000_0858();
    DAT_1c79_4dbc = 0x5e74;
    FUN_1000_0936();
  }
  else {
    DAT_1c79_4dbc = 0x5e62;
    pole_final_highscores();
  }
  DAT_1c79_4dbc = 0x5e77;
  FUN_1000_0000();
  uVar12 = DAT_1c79_4ebe;
  DAT_1c79_4ebe = 0x174b;
  DAT_1c79_4ebc = 0x5e81;
  FUN_1ad9_00d8();
  uVar13 = (undefined2)((ulong)uRam0002165c >> 0x10);
  uVar6 = (undefined2)((ulong)uRam00021658 >> 0x10);
  DAT_1c79_4ebc = *(int *)((int)uRam0002165c + 2);
  piVar10 = (int *)((int)uRam0002165c + 6);
  pcVar11 = (char *)((int)uRam00021658 + iRam00021654 * 0x50 + (uRam00021656 >> 3));
  bRam00021646 = (byte)uRam00021656 & 7;
  out(0x3ce,0x205);
  out(0x3ce,8);
  uRam00021644 = unaff_DS;
  DAT_1c79_4ebe = uVar12;
  do {
    bRam00021648 = bRam00021646;
    piVar3 = piVar10 + 1;
    piRam0002164a = (int *)(*piVar10 + (int)piVar3);
    piVar10 = (int *)((int)piVar10 + 3);
    cVar8 = (char)*piVar3;
    pcRam00021642 = pcVar11;
    do {
      if (cVar8 < '\0') {
        bVar7 = 0xff >> (bRam00021648 & 0x1f);
        piVar1 = piVar10;
        piVar10 = (int *)((int)piVar10 + 1);
        cVar2 = (char)*piVar1;
        if (cVar2 == cRam00021652) {
          bVar7 = cVar8 + -0x80 + bRam00021648;
          bRam00021648 = bVar7;
          if ('\a' < (char)bVar7) {
            bRam00021648 = 0;
          }
          bVar7 = bVar7 - 8;
          if (-1 < (char)bVar7) {
            for (; pcVar11 = pcVar11 + 1, bRam00021648 = bVar7, '\a' < (char)bVar7;
                bVar7 = bVar7 - 8) {
            }
          }
        }
        else {
          bVar9 = cVar8 + -0x80 + bRam00021648;
          if (bVar9 < 8) {
            bVar7 = -2 << ((bVar9 ^ 7) & 0x1f) & bVar7;
            bRam00021648 = bVar9;
          }
          else {
            bRam00021648 = 0;
          }
          out(0x3cf,bVar7);
          *pcVar11 = cVar2;
          bVar9 = bVar9 - 8;
          if (-1 < (char)bVar9) {
            out(0x3cf,0xff);
            for (; pcVar11 = pcVar11 + 1, '\a' < (char)bVar9; bVar9 = bVar9 - 8) {
              *pcVar11 = cVar2;
            }
            out(0x3cf,-2 << ((bVar9 ^ 7) & 0x1f));
            *pcVar11 = cVar2;
            bRam00021648 = bVar9;
          }
        }
      }
      else {
        bVar7 = 0x80 >> (bRam00021648 & 0x1f);
        do {
          piVar1 = piVar10;
          piVar10 = (int *)((int)piVar10 + 1);
          if ((char)*piVar1 != cRam00021652) {
            out(0x3cf,bVar7);
            *pcVar11 = (char)*piVar1;
          }
          bRam00021648 = bRam00021648 + 1;
          bVar14 = (bool)(bVar7 & 1);
          bVar7 = bVar7 >> 1 | bVar7 << 7;
          if (bVar14) {
            pcVar11 = pcVar11 + 1;
            bRam00021648 = 0;
          }
          cVar8 = cVar8 + -1;
        } while (cVar8 != '\0');
      }
      piVar1 = piVar10;
      piVar10 = (int *)((int)piVar10 + 1);
      cVar8 = (char)*piVar1;
    } while (piRam0002164a != piVar10);
    pcVar11 = pcRam00021642 + 0x50;
    DAT_1c79_4ebc = DAT_1c79_4ebc + -1;
  } while (DAT_1c79_4ebc != 0);
  return;
}



/* 1000:5e81 pole_blit_rle */

void pole_blit_rle(char param_1,int param_2,uint param_3,undefined4 param_4,undefined4 param_5)

{
  int *piVar1;
  char cVar2;
  int *piVar3;
  int iVar4;
  byte bVar5;
  char cVar6;
  byte bVar7;
  int *piVar8;
  char *pcVar9;
  char *pcVar10;
  undefined2 uVar11;
  undefined2 uVar12;
  bool bVar13;
  byte local_8;
  int local_4;
  
  uVar12 = (undefined2)((ulong)param_5 >> 0x10);
  uVar11 = (undefined2)((ulong)param_4 >> 0x10);
  local_4 = *(int *)((int)param_5 + 2);
  piVar8 = (int *)((int)param_5 + 6);
  pcVar9 = (char *)((int)param_4 + param_2 * 0x50 + (param_3 >> 3));
  out(0x3ce,0x205);
  out(0x3ce,8);
  do {
    piVar3 = piVar8 + 1;
    iVar4 = *piVar8;
    piVar8 = (int *)((int)piVar8 + 3);
    cVar6 = (char)*piVar3;
    pcVar10 = pcVar9;
    local_8 = (byte)param_3 & 7;
    do {
      if (cVar6 < '\0') {
        bVar5 = 0xff >> (local_8 & 0x1f);
        piVar1 = piVar8;
        piVar8 = (int *)((int)piVar8 + 1);
        cVar2 = (char)*piVar1;
        if (cVar2 == param_1) {
          bVar5 = cVar6 + -0x80 + local_8;
          local_8 = bVar5;
          if ('\a' < (char)bVar5) {
            local_8 = 0;
          }
          bVar5 = bVar5 - 8;
          if (-1 < (char)bVar5) {
            for (; pcVar10 = pcVar10 + 1, local_8 = bVar5, '\a' < (char)bVar5; bVar5 = bVar5 - 8) {
            }
          }
        }
        else {
          bVar7 = cVar6 + -0x80 + local_8;
          if (bVar7 < 8) {
            bVar5 = -2 << ((bVar7 ^ 7) & 0x1f) & bVar5;
            local_8 = bVar7;
          }
          else {
            local_8 = 0;
          }
          out(0x3cf,bVar5);
          *pcVar10 = cVar2;
          bVar7 = bVar7 - 8;
          if (-1 < (char)bVar7) {
            out(0x3cf,0xff);
            for (; pcVar10 = pcVar10 + 1, '\a' < (char)bVar7; bVar7 = bVar7 - 8) {
              *pcVar10 = cVar2;
            }
            out(0x3cf,-2 << ((bVar7 ^ 7) & 0x1f));
            *pcVar10 = cVar2;
            local_8 = bVar7;
          }
        }
      }
      else {
        bVar5 = 0x80 >> (local_8 & 0x1f);
        do {
          piVar1 = piVar8;
          piVar8 = (int *)((int)piVar8 + 1);
          if ((char)*piVar1 != param_1) {
            out(0x3cf,bVar5);
            *pcVar10 = (char)*piVar1;
          }
          local_8 = local_8 + 1;
          bVar13 = (bool)(bVar5 & 1);
          bVar5 = bVar5 >> 1 | bVar5 << 7;
          if (bVar13) {
            pcVar10 = pcVar10 + 1;
            local_8 = 0;
          }
          cVar6 = cVar6 + -1;
        } while (cVar6 != '\0');
      }
      piVar1 = piVar8;
      piVar8 = (int *)((int)piVar8 + 1);
      cVar6 = (char)*piVar1;
    } while ((int *)(iVar4 + (int)piVar3) != piVar8);
    pcVar9 = pcVar9 + 0x50;
    local_4 = local_4 + -1;
  } while (local_4 != 0);
  return;
}



/* 1000:6630 FUN_1000_6630 */

undefined4 __cdecl16near FUN_1000_6630(void)

{
  undefined2 uVar1;
  undefined2 in_DX;
  
  uVar1 = 5;
  if (cRam000104e2 != '\0') {
    uVar1 = 0x1005;
  }
  out(0x3ce,uVar1);
  out(0x3ce,3);
  out(0x3ce,0xff08);
  out(0x3c4,0xf02);
  return CONCAT22(in_DX,0xf02);
}



/* 1000:6655 FUN_1000_6655 */

void __cdecl16near FUN_1000_6655(void)

{
  if (cRam00010258 != '\0') {
    out(0x3ce,0x1803);
  }
  return;
}



/* 1000:667f FUN_1000_667f */

long __cdecl16near
FUN_1000_667f(uint param_1,int param_2,uint param_3,int param_4,undefined1 param_5)

{
  undefined2 uVar1;
  int iVar2;
  uint uVar3;
  byte bVar4;
  byte bVar5;
  undefined1 extraout_AH;
  int iVar6;
  int extraout_DX;
  int iVar7;
  uint uVar8;
  int iVar9;
  byte *pbVar10;
  undefined2 unaff_DS;
  bool bVar11;
  byte bVar12;
  
  uVar3 = param_3;
  uVar1 = *(undefined2 *)0x4e3;
  FUN_1000_6655();
  out(0x3ce,0);
  out(0x3cf,param_5);
  out(0x3ce,1);
  out(0x3cf,0xff);
  uVar8 = param_4 - param_2;
  if ((int)uVar8 < 0) {
    LOCK();
    UNLOCK();
    param_2 = param_4;
    LOCK();
    param_3 = param_1;
    UNLOCK();
    param_1 = uVar3;
    uVar8 = -uVar8;
  }
  pbVar10 = (byte *)(param_2 * 0x50 + (param_1 >> 3));
  bVar5 = (byte)((uint)(param_2 * 0x40) >> 8);
  out(0x3ce,8);
  bVar4 = 0x80 >> ((byte)param_1 & 7);
  param_3 = param_3 - param_1;
  if ((int)param_3 < 0) {
    if (-param_3 < uVar8) {
      iVar6 = uVar8 + 1;
      iVar9 = param_3 * -2 - uVar8;
      iVar7 = param_3 * -2 + uVar8 * -2;
      out(0x3cf,bVar4);
      do {
        bVar11 = (uRam000104e0 & 1) != 0;
        uRam000104e0 = uRam000104e0 >> 1 | (uint)bVar11 << 0xf;
        if (bVar11) {
          LOCK();
          bVar12 = *pbVar10;
          *pbVar10 = bVar5;
          UNLOCK();
          bVar5 = bVar12;
        }
        iVar2 = uVar8 * 2 + iVar7;
        if (-1 < iVar9) {
          bVar11 = (char)bVar4 < '\0';
          bVar4 = bVar4 << 1 | bVar11;
          pbVar10 = pbVar10 + -(uint)bVar11;
          out(0x3cf,bVar4);
          iVar2 = iVar7;
        }
        iVar9 = iVar9 + iVar2;
        pbVar10 = pbVar10 + 0x50;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
    else {
      iVar6 = -param_3 + 1;
      iVar7 = uVar8 * 2 + param_3;
      iVar9 = uVar8 * 2 + param_3 * 2;
      bVar5 = 0;
      do {
        bVar11 = (uRam000104e0 & 1) != 0;
        uRam000104e0 = uRam000104e0 >> 1 | (uint)bVar11 << 0xf;
        if (bVar11) {
          bVar5 = bVar5 | bVar4;
        }
        if (iVar7 < 0) {
          iVar7 = iVar7 + param_3 * -2 + iVar9;
          bVar11 = (char)bVar4 < '\0';
          bVar4 = bVar4 << 1 | bVar11;
          if (bVar11) {
            out(0x3cf,bVar5);
            LOCK();
            *pbVar10 = bVar5;
            UNLOCK();
            pbVar10 = pbVar10 + -1;
            bVar5 = 0;
          }
        }
        else {
          out(0x3cf,bVar5);
          LOCK();
          *pbVar10 = bVar5;
          UNLOCK();
          iVar7 = iVar7 + iVar9;
          bVar11 = (char)bVar4 < '\0';
          bVar4 = bVar4 << 1 | bVar11;
          bVar5 = 0;
          pbVar10 = pbVar10 + (0x50 - (uint)bVar11);
        }
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
      out(0x3cf,bVar5);
      LOCK();
      *pbVar10 = bVar5;
      UNLOCK();
    }
  }
  else if (param_3 < uVar8) {
    iVar6 = uVar8 + 1;
    iVar9 = param_3 * 2 - uVar8;
    iVar7 = param_3 * 2 + uVar8 * -2;
    out(0x3cf,bVar4);
    do {
      bVar11 = (uRam000104e0 & 1) != 0;
      uRam000104e0 = uRam000104e0 >> 1 | (uint)bVar11 << 0xf;
      if (bVar11) {
        LOCK();
        bVar12 = *pbVar10;
        *pbVar10 = bVar5;
        UNLOCK();
        bVar5 = bVar12;
      }
      iVar2 = uVar8 * 2 + iVar7;
      if (-1 < iVar9) {
        bVar12 = bVar4 & 1;
        bVar4 = bVar4 >> 1 | bVar4 << 7;
        pbVar10 = pbVar10 + bVar12;
        out(0x3cf,bVar4);
        iVar2 = iVar7;
      }
      iVar9 = iVar9 + iVar2;
      pbVar10 = pbVar10 + 0x50;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
  }
  else {
    iVar6 = param_3 + 1;
    iVar7 = uVar8 * 2 - param_3;
    iVar9 = uVar8 * 2 + param_3 * -2;
    bVar5 = 0;
    do {
      bVar11 = (uRam000104e0 & 1) != 0;
      uRam000104e0 = uRam000104e0 >> 1 | (uint)bVar11 << 0xf;
      if (bVar11) {
        bVar5 = bVar5 | bVar4;
      }
      if (iVar7 < 0) {
        iVar7 = iVar7 + param_3 * 2 + iVar9;
        bVar11 = (bool)(bVar4 & 1);
        bVar4 = bVar4 >> 1 | bVar4 << 7;
        if (bVar11) {
          out(0x3cf,bVar5);
          LOCK();
          *pbVar10 = bVar5;
          UNLOCK();
          pbVar10 = pbVar10 + 1;
          bVar5 = 0;
        }
      }
      else {
        out(0x3cf,bVar5);
        LOCK();
        *pbVar10 = bVar5;
        UNLOCK();
        iVar7 = iVar7 + iVar9;
        bVar12 = bVar4 & 1;
        bVar4 = bVar4 >> 1 | bVar4 << 7;
        bVar5 = 0;
        pbVar10 = pbVar10 + bVar12 + 0x50;
      }
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    out(0x3cf,bVar5);
    LOCK();
    *pbVar10 = bVar5;
    UNLOCK();
  }
  FUN_1000_6630();
  out(extraout_DX,0xff);
  out(extraout_DX + -1,1);
  out(extraout_DX,0);
  return (ulong)CONCAT21(extraout_DX,extraout_AH) << 8;
}



/* 174b:0055 FUN_174b_0055 */

void __cdecl16far FUN_174b_0055(void)

{
  undefined2 unaff_DS;
  undefined2 uVar1;
  
  if (*(char *)0xd8c == '\0') {
    uVar1 = 0xef8;
    FUN_1ad9_173b(0,0,0x174b);
    FUN_1ad9_16be(uVar1,unaff_DS);
    FUN_1ad9_020e();
  }
  else {
    uVar1 = 0xef8;
    FUN_1ad9_173b(0,0x34,0x174b);
    FUN_1ad9_16be(uVar1,unaff_DS);
    FUN_1ad9_020e();
  }
  FUN_1ad9_00d8();
  return;
}



/* 174b:00a5 FUN_174b_00a5 */

undefined2 __stdcall16far FUN_174b_00a5(void)

{
  return 1;
}



/* 174b:00b9 FUN_174b_00b9 */

void __stdcall16far FUN_174b_00b9(undefined2 param_1,undefined2 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = FUN_1ad9_0329(param_1);
  *param_2 = (int)uVar1;
  ((undefined2 *)param_2)[1] = (int)((ulong)uVar1 >> 0x10);
  return;
}



/* 174b:00d4 FUN_174b_00d4 */

void __stdcall16far FUN_174b_00d4(undefined2 param_1,int *param_2)

{
  int *piVar1;
  undefined2 uVar2;
  
  uVar2 = (undefined2)((ulong)param_2 >> 0x10);
  piVar1 = (int *)param_2;
  if (*param_2 != 0 || piVar1[1] != 0) {
    FUN_1ad9_0341(param_1,*param_2,piVar1[1]);
  }
  *param_2 = 0;
  piVar1[1] = 0;
  return;
}



/* 174b:0107 FUN_174b_0107 */

long FUN_174b_0107(undefined2 *param_1,int *param_2,undefined4 param_3)

{
  uint uVar1;
  uint uVar2;
  undefined4 local_6;
  
  uVar1 = (int)param_3 + *param_2;
  uVar2 = (uVar1 >> 4) + param_3._2_2_;
  if ((uVar1 & 0xf) != 0) {
    FUN_1ad9_19b6(*param_1,0,uVar2,uVar1,param_3._2_2_);
    *param_2 = *param_2 - (uVar1 & 0xf);
  }
  local_6 = (ulong)uVar2 << 0x10;
  return local_6;
}



/* 174b:016f FUN_174b_016f */

uint __stdcall16far FUN_174b_016f(undefined4 param_1)

{
  int iVar1;
  undefined2 uVar2;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar3;
  bool bVar4;
  undefined4 uVar5;
  undefined1 *puVar6;
  undefined1 local_10a [250];
  uint local_10;
  int local_e;
  undefined2 uStack_c;
  uint local_a;
  int local_8;
  undefined2 uStack_6;
  uint local_4;
  
  uVar3 = *(char *)0xd8c == '\0';
  if ((bool)uVar3) {
    *(undefined2 *)0xd56 = 0xfffc;
    local_4 = 0xfffc;
    puVar6 = local_10a;
    uVar2 = (undefined2)((ulong)param_1 >> 0x10);
    iVar1 = (int)param_1;
    FUN_1ad9_076c(2,iVar1,uVar2);
    FUN_1ad9_072f(0x16c,0x1ad9,puVar6,unaff_SS);
    if ((bool)uVar3) {
      local_e = iVar1 + 0x80;
      _local_8 = CONCAT22(uVar2,local_e);
      if (((1 < *(byte *)(iVar1 + 0x86)) && (*(byte *)(iVar1 + 0x88) < 2)) &&
         (local_10 = *(uint *)0xcf6, local_10 < 0x8000)) {
        local_a = 0;
        uStack_c = uVar2;
        while( true ) {
          bVar4 = local_e + 10 == 0;
          FUN_1ad9_072f(local_e + 10,uStack_c,local_a * 0x1a + 0x2d8,unaff_DS);
          if (bVar4) break;
          if (local_a == local_10) {
            return local_4;
          }
          local_a = local_a + 1;
        }
        uVar5 = FUN_174b_0107(local_e + 4,uStack_c,local_e,uStack_c,iVar1,uVar2);
        *(undefined2 *)(local_a * 0x1a + 0x2ee) = (int)uVar5;
        *(undefined2 *)(local_a * 0x1a + 0x2f0) = (int)((ulong)uVar5 >> 0x10);
        local_4 = local_a;
        *(undefined2 *)0xd56 = 0;
      }
    }
  }
  else {
    *(undefined2 *)0xd56 = 0xfff5;
    local_4 = 0xfff5;
  }
  return local_4;
}



/* 174b:026a FUN_174b_026a */

int __stdcall16far FUN_174b_026a(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  undefined2 uVar3;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar4;
  undefined4 uVar5;
  undefined1 *puVar6;
  undefined2 uVar7;
  undefined2 uVar8;
  undefined2 *local_114;
  undefined1 local_110 [4];
  undefined1 local_10c [252];
  int local_10;
  undefined2 uStack_e;
  uint local_c;
  int local_a;
  int local_8;
  undefined2 uStack_6;
  int local_4;
  
  uVar4 = &stack0x0000 == (undefined1 *)0x114;
  *(undefined2 *)0xd56 = 0xfff3;
  local_4 = *(int *)0xd56;
  puVar6 = local_10c;
  uVar3 = (undefined2)((ulong)param_1 >> 0x10);
  iVar2 = (int)param_1;
  uVar7 = unaff_SS;
  FUN_1ad9_076c(2,iVar2,uVar3);
  FUN_1ad9_072f(0x267,0x1ad9,puVar6,uVar7);
  if ((bool)uVar4) {
    for (local_c = 0; (*(char *)(iVar2 + local_c) != '\x1a' && (local_c < 0x101));
        local_c = local_c + 1) {
    }
    if (local_c < 0x100) {
      iVar1 = iVar2 + local_c;
      local_10 = iVar1 + 1;
      _local_8 = CONCAT22(uVar3,local_10);
      if ((*(char *)(iVar1 + 9) != '\0') && (*(byte *)(iVar1 + 0xb) < 2)) {
        local_a = 1;
        uStack_e = uVar3;
        while( true ) {
          iVar1 = local_a * 0xf + 0x3f1;
          puVar6 = local_110;
          uVar4 = local_10 + 2 == 0;
          uVar7 = unaff_SS;
          uVar8 = unaff_DS;
          FUN_1ad9_076c(4,local_10 + 2,uStack_e);
          FUN_1ad9_072f(puVar6,uVar7,iVar1,uVar8);
          if ((bool)uVar4) break;
          if (local_a == 0x14) {
            return local_4;
          }
          local_a = local_a + 1;
        }
        iVar1 = local_a * 0xf;
        _local_114 = (undefined2 *)CONCAT22(unaff_DS,(undefined2 *)(iVar1 + 999));
        (*(code *)*(undefined2 *)0xc04)
                  (0x1ad9,*(undefined2 *)(iVar1 + 0x3ef),(undefined2 *)(iVar1 + 999),unaff_DS);
        *_local_114 = 0;
        *(undefined2 *)(iVar1 + 0x3e9) = 0;
        uVar5 = FUN_174b_0107(local_10 + 6,uStack_e,local_10,uStack_e,iVar2,uVar3);
        *(undefined2 *)(iVar1 + 0x3eb) = (int)uVar5;
        *(undefined2 *)(iVar1 + 0x3ed) = (int)((ulong)uVar5 >> 0x10);
        *(undefined2 *)(iVar1 + 0x3ef) = 0;
        local_4 = local_a;
        *(undefined2 *)0xd56 = 0;
      }
    }
  }
  return local_4;
}



/* 174b:03b9 FUN_174b_03b9 */

void __cdecl16near FUN_174b_03b9(void)

{
  undefined2 unaff_DS;
  
  *(undefined2 *)0xd5e = 0x55;
  *(undefined2 *)0xd60 = 0x174b;
  *(undefined2 *)0xd70 = 0x55;
  *(undefined2 *)0xd72 = 0x174b;
  *(undefined2 *)0xd62 = 0;
  *(undefined2 *)0xd64 = 0;
  *(undefined2 *)0xd74 = 0;
  *(undefined2 *)0xd76 = 0;
  *(undefined2 *)0xd66 = 0;
  *(undefined2 *)0xd68 = 0;
  *(undefined2 *)0xd6c = 0;
  *(undefined2 *)0xd6e = 0;
  *(undefined2 *)0xd1e = 0;
  *(undefined2 *)0xd20 = 0;
  *(undefined2 *)0xd22 = 0;
  *(undefined2 *)0xd38 = 0;
  *(undefined2 *)0xd3a = 0;
  *(undefined2 *)0xd3c = 0;
  *(undefined1 *)0xd28 = 0;
  *(undefined2 *)0xd88 = 1;
  *(undefined2 *)0xd8a = 1;
  *(undefined2 *)0xc88 = 0;
  *(undefined1 *)0xd8c = 0;
  return;
}



/* 174b:042f FUN_174b_042f */

undefined1 FUN_174b_042f(undefined2 param_1,uint *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  undefined1 local_304 [256];
  undefined1 local_204 [256];
  char local_104 [257];
  undefined1 local_3;
  
  FUN_1ad9_0644(0xff,local_104,unaff_SS,(int)param_4,(int)((ulong)param_4 >> 0x10));
  FUN_1ad9_0644(0xff,local_204,unaff_SS,(int)param_3,(int)((ulong)param_3 >> 0x10));
  local_3 = 0;
  *(undefined2 *)0xd56 = 0xfffd;
  *param_2 = 0;
  uVar5 = 0xc08;
  puVar3 = local_304;
  uVar4 = unaff_SS;
  uVar6 = unaff_DS;
  FUN_1ad9_062a(local_104,unaff_SS);
  FUN_1ad9_06b7(local_204,unaff_SS);
  FUN_1ad9_1779(puVar3,uVar4,uVar5,uVar6);
  FUN_1ad9_17a7(1,0xc08,unaff_DS);
  iVar1 = FUN_1ad9_0207();
  if (iVar1 != 0) {
    if (local_104[0] == '\0') {
      return local_3;
    }
    FUN_1ad9_1779(local_204,unaff_SS,0xc08,unaff_DS);
    FUN_1ad9_17a7(1,0xc08,unaff_DS);
    iVar1 = FUN_1ad9_0207();
    if (iVar1 != 0) {
      return local_3;
    }
  }
  *(undefined2 *)0xd56 = 0;
  uVar2 = FUN_1ad9_1941(0xc08,unaff_DS);
  *param_2 = uVar2;
  if (*param_2 < 0x3c01) {
    local_3 = 1;
  }
  else {
    *(undefined2 *)0xd56 = param_1;
    FUN_1ad9_1828(0xc08,unaff_DS);
  }
  return local_3;
}



/* 174b:0524 FUN_174b_0524 */

undefined1 FUN_174b_0524(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  char cVar2;
  int iVar3;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar4;
  undefined2 uVar5;
  undefined1 local_210 [260];
  int local_10c [4];
  undefined1 local_104 [257];
  undefined1 local_3;
  
  FUN_1ad9_0644(0xff,local_104,unaff_SS,(int)param_1,(int)((ulong)param_1 >> 0x10));
  local_3 = 0;
  puVar4 = local_210;
  uVar5 = unaff_SS;
  FUN_1ad9_062a(param_2 * 0x1a + 0x2d8,unaff_DS);
  FUN_1ad9_06b7(0x51f,0x1ad9);
  FUN_1ad9_0644(0xc,0xc94,unaff_DS,puVar4,uVar5);
  if (*(int *)(param_2 * 0x1a + 0x2ee) == 0 && *(int *)(param_2 * 0x1a + 0x2f0) == 0) {
    cVar2 = FUN_174b_042f(0xfffc,0xd6a,unaff_DS,0xc94,unaff_DS,local_104,unaff_SS);
    if (cVar2 != '\0') {
      uVar1 = *(undefined4 *)0x544;
      *(undefined2 *)0xcfa = (int)uVar1;
      *(undefined2 *)0xcfc = (int)((ulong)uVar1 >> 0x10);
      *(undefined2 *)0x544 = 0xa5;
      *(undefined2 *)0x546 = 0x174b;
      (*(code *)*(undefined2 *)0xc00)(0x1ad9,*(undefined2 *)0xd6a,0xd66);
      uVar1 = *(undefined4 *)0xcfa;
      *(undefined2 *)0x544 = (int)uVar1;
      *(undefined2 *)0x546 = (int)((ulong)uVar1 >> 0x10);
      if (*(int *)0xd66 == 0 && *(int *)0xd68 == 0) {
        *(undefined2 *)0xd56 = 0xfffb;
      }
      else {
        FUN_1ad9_1892(local_10c,unaff_SS,*(undefined2 *)0xd6a,(int)*(undefined4 *)0xd66,
                      (int)((ulong)*(undefined4 *)0xd66 >> 0x10),0xc08,unaff_DS);
        FUN_1ad9_1828(0xc08,unaff_DS);
        iVar3 = FUN_1ad9_0207();
        if (((iVar3 == 0) && (local_10c[0] == *(int *)0xd6a)) &&
           (iVar3 = FUN_174b_016f(*(undefined2 *)0xd66,*(undefined2 *)0xd68), iVar3 == param_2)) {
          uVar1 = *(undefined4 *)(param_2 * 0x1a + 0x2ee);
          *(undefined2 *)0xd70 = (int)uVar1;
          *(undefined2 *)0xd72 = (int)((ulong)uVar1 >> 0x10);
          local_3 = 1;
        }
        else {
          *(undefined2 *)0xd56 = 0xfffc;
          (*(code *)*(undefined2 *)0xc04)(0x1ad9,*(undefined2 *)0xd6a,0xd66);
        }
      }
    }
  }
  else {
    uVar1 = *(undefined4 *)(param_2 * 0x1a + 0x2ee);
    *(undefined2 *)0xd70 = (int)uVar1;
    *(undefined2 *)0xd72 = (int)((ulong)uVar1 >> 0x10);
    *(undefined2 *)0xd66 = 0;
    *(undefined2 *)0xd68 = 0;
    *(undefined2 *)0xd6a = 0;
    local_3 = 1;
  }
  return local_3;
}



/* 174b:0699 FUN_174b_0699 */

void __cdecl16far FUN_174b_0699(void)

{
  int iVar1;
  undefined2 uVar2;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar3;
  undefined2 uVar4;
  undefined1 local_a [8];
  
  if (*(char *)0xd8c == '\0') {
    FUN_174b_0055();
  }
  FUN_174b_0a63(1,*(undefined2 *)0xd02,*(undefined2 *)0xd00,0,0);
  FUN_174b_0d65(0xdb8,unaff_DS);
  FUN_174b_0c5d(0xdb8,unaff_DS);
  iVar1 = FUN_174b_14c6();
  if (iVar1 != 1) {
    FUN_174b_0c26(0);
  }
  *(undefined1 *)0xd7e = 0;
  uVar2 = FUN_174b_14b6();
  FUN_174b_149e(uVar2);
  FUN_1ad9_19d9(0xff,8,local_a,unaff_SS);
  puVar3 = local_a;
  uVar2 = FUN_174b_14b6(puVar3);
  FUN_174b_0bcb(uVar2,puVar3,unaff_SS);
  uVar4 = 1;
  uVar2 = FUN_174b_14b6(1);
  FUN_174b_0b9e(uVar2,uVar4);
  FUN_174b_0b19(1,0,0);
  FUN_174b_0dca(1,0,0);
  FUN_174b_0d86(2,0);
  FUN_174b_11c3(0x1ad9,0);
  FUN_174b_0afa(0,0);
  return;
}



/* 174b:0759 FUN_174b_0759 */

void __stdcall16far FUN_174b_0759(undefined4 param_1,int *param_2,int *param_3)

{
  char cVar1;
  undefined2 uVar2;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 local_20a [257];
  char local_109;
  int local_108;
  int local_106;
  char local_103;
  undefined1 local_102 [256];
  
  FUN_1ad9_0644(0xff,local_102,unaff_SS,(int)param_1,(int)((ulong)param_1 >> 0x10));
  *(undefined2 *)0xd5e = 0x18df;
  *(undefined2 *)0xd60 = 0x174b;
  uVar3 = FUN_174b_0107((int)*(undefined4 *)0xd5e + 2,(int)((ulong)*(undefined4 *)0xd5e >> 0x10),
                        (int)*(undefined4 *)0xd5e,(int)((ulong)*(undefined4 *)0xd5e >> 0x10),
                        *(undefined2 *)0xd5e,*(undefined2 *)0xd60);
  *(undefined2 *)0xd5e = (int)uVar3;
  *(undefined2 *)0xd60 = (int)((ulong)uVar3 >> 0x10);
  local_109 = '\0';
  if (*param_3 == 0) {
    local_106 = 0;
    local_108 = -1;
    while ((local_106 < *(int *)0xcf6 && (local_108 < 0))) {
      if (*(int *)(local_106 * 0x1a + 0x2ea) != 0 || *(int *)(local_106 * 0x1a + 0x2ec) != 0) {
        uVar3 = *(undefined4 *)(local_106 * 0x1a + 0x2ea);
        *(undefined2 *)0xdd4 = (int)uVar3;
        *(undefined2 *)0xdd6 = (int)((ulong)uVar3 >> 0x10);
        local_108 = (*(code *)*(undefined2 *)0xdd4)(0x1ad9);
        if (-1 < local_108) {
          *(int *)0xd52 = local_106;
          *param_3 = local_106;
          *param_2 = local_108;
          local_109 = '\x01';
        }
      }
      local_106 = local_106 + 1;
    }
  }
  uVar2 = (undefined2)((ulong)param_2 >> 0x10);
  if (local_109 == '\0') {
    FUN_174b_1264((int *)param_2,uVar2,(int *)param_3,(int)((ulong)param_3 >> 0x10),0xd52,unaff_DS);
  }
  else {
    local_106 = *(int *)0xd52;
    local_108 = *param_3 + 0x80;
    FUN_174b_1264((int *)param_2,uVar2,&local_108,unaff_SS,&local_106,unaff_SS);
  }
  if (*param_3 < 0) {
    *(undefined2 *)0xd56 = 0xfffe;
    *param_3 = -2;
    FUN_174b_03b9();
  }
  else {
    *(int *)0xd54 = *param_2;
    FUN_1ad9_0644(0x50,0xca2,unaff_DS,local_102,unaff_SS);
    if (((*(char *)0xca2 != '\0') &&
        (local_103 = *(char *)(*(byte *)0xca2 + 0xca2), local_103 != ':')) && (local_103 != '\\')) {
      puVar4 = local_20a;
      FUN_1ad9_062a(local_102,unaff_SS);
      FUN_1ad9_06b7(0x757,0x1ad9);
      FUN_1ad9_0644(0x50,0xca2,unaff_DS,puVar4,unaff_SS);
    }
    cVar1 = FUN_174b_0524(0xca2,unaff_DS,*(undefined2 *)0xd52);
    if (cVar1 == '\0') {
      *param_3 = *(int *)0xd56;
      FUN_174b_03b9();
    }
    else {
      FUN_1ad9_19d9(0,0x3f,0xd12,unaff_DS);
      uVar3 = *(undefined4 *)0x544;
      *(undefined2 *)0xcfa = (int)uVar3;
      *(undefined2 *)0xcfc = (int)((ulong)uVar3 >> 0x10);
      *(undefined2 *)0x544 = 0xa5;
      *(undefined2 *)0x546 = 0x174b;
      (*(code *)*(undefined2 *)0xc00)(0x1ad9,*(undefined2 *)0xcf4,0xd1e);
      uVar3 = *(undefined4 *)0xcfa;
      *(undefined2 *)0x544 = (int)uVar3;
      *(undefined2 *)0x546 = (int)((ulong)uVar3 >> 0x10);
      if (*(int *)0xd1e == 0 && *(int *)0xd20 == 0) {
        *(undefined2 *)0xd56 = 0xfffb;
        *param_3 = -5;
        (*(code *)*(undefined2 *)0xc04)(0x1ad9,*(undefined2 *)0xd6a,0xd66);
        FUN_174b_03b9();
      }
      else {
        *(undefined1 *)0xd13 = 0;
        *(undefined1 *)0xd28 = 0;
        uVar3 = *(undefined4 *)0xd1e;
        *(undefined2 *)0xd6c = (int)uVar3;
        *(undefined2 *)0xd6e = (int)((ulong)uVar3 >> 0x10);
        *(undefined2 *)0xd22 = *(undefined2 *)0xcf4;
        uVar3 = *(undefined4 *)0xd1e;
        *(undefined2 *)0xd38 = (int)uVar3;
        *(undefined2 *)0xd3a = (int)((ulong)uVar3 >> 0x10);
        *(undefined2 *)0xd3c = *(undefined2 *)0xcf4;
        *(undefined2 *)0xd2c = 0xd56;
        *(undefined2 *)0xd2e = unaff_DS;
        FUN_174b_10c8(0x1ad9,0xd12);
        FUN_1ad9_19b6(0x13,0xcfe,unaff_DS,*(undefined2 *)0xd78,*(undefined2 *)0xd7a);
        FUN_174b_1312(0xd12,unaff_DS);
        if (*(char *)0xcfe == '\0') {
          uVar2 = FUN_174b_14ff();
          *(undefined2 *)0xd86 = uVar2;
          *(undefined2 *)0xd88 = *(undefined2 *)0xd0c;
          *(undefined2 *)0xd8a = 10000;
          *(undefined1 *)0xd8c = 1;
          FUN_174b_0699();
          *(undefined2 *)0xd56 = 0;
        }
        else {
          *(uint *)0xd56 = (uint)*(byte *)0xcfe;
          FUN_174b_03b9();
        }
      }
    }
  }
  return;
}



/* 174b:0a35 FUN_174b_0a35 */

void __cdecl16far FUN_174b_0a35(void)

{
  undefined4 uVar1;
  undefined2 unaff_DS;
  
  FUN_174b_1157();
  if (*(int *)0xd62 == 0 && *(int *)0xd64 == 0) {
    uVar1 = *(undefined4 *)0xd5e;
    *(undefined2 *)0xd62 = (int)uVar1;
    *(undefined2 *)0xd64 = (int)((ulong)uVar1 >> 0x10);
    *(undefined2 *)0xd5e = 0x55;
    *(undefined2 *)0xd60 = 0x174b;
  }
  return;
}



/* 174b:0a63 FUN_174b_0a63 */

void __stdcall16far
FUN_174b_0a63(undefined1 param_1,uint param_2,uint param_3,int param_4,int param_5)

{
  undefined2 unaff_DS;
  bool bVar1;
  
  if ((-1 < param_5) && (-1 < param_4)) {
    bVar1 = (int)param_3 >> 0xf < 0;
    if ((-1 < (int)param_3 || bVar1) && ((bVar1 || (param_3 <= *(uint *)0xd00)))) {
      bVar1 = (int)param_2 >> 0xf < 0;
      if ((-1 < (int)param_2 || bVar1) &&
         ((((bVar1 || (param_2 <= *(uint *)0xd02)) && (param_5 <= (int)param_3)) &&
          (param_4 <= (int)param_2)))) {
        *(int *)0xd90 = param_5;
        *(int *)0xd92 = param_4;
        *(uint *)0xd94 = param_3;
        *(uint *)0xd96 = param_2;
        *(undefined1 *)0xd98 = param_1;
        FUN_174b_1108(param_1,param_2,param_3,param_4,param_5);
        FUN_174b_0afa(0,0);
        return;
      }
    }
  }
  *(undefined2 *)0xd56 = 0xfff5;
  return;
}



/* 174b:0afa FUN_174b_0afa */

void __stdcall16far FUN_174b_0afa(undefined2 param_1,undefined2 param_2)

{
  undefined2 unaff_DS;
  
  FUN_174b_133a(param_1,param_2);
  *(undefined2 *)0xd82 = param_2;
  *(undefined2 *)0xd84 = param_1;
  return;
}



/* 174b:0b19 FUN_174b_0b19 */

void __stdcall16far FUN_174b_0b19(uint param_1,undefined2 param_2,uint param_3)

{
  undefined2 unaff_DS;
  
  if ((param_3 < 5) && (param_1 < 4)) {
    *(uint *)0xd9a = param_3;
    *(undefined2 *)0xd9c = param_2;
    *(uint *)0xd9e = param_1;
    FUN_174b_156b(param_1,param_2,param_3);
  }
  else {
    *(undefined2 *)0xd56 = 0xfff5;
  }
  return;
}



/* 174b:0b55 FUN_174b_0b55 */

void __stdcall16far
FUN_174b_0b55(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4)

{
  FUN_174b_1362(param_3,param_2,param_3,param_4);
  FUN_174b_1362(param_1,param_2,param_3,param_2);
  FUN_174b_1362(param_1,param_4,param_1,param_2);
  FUN_174b_1362(param_3,param_4,param_1,param_4);
  return;
}



/* 174b:0b9e FUN_174b_0b9e */

void __stdcall16far FUN_174b_0b9e(undefined2 param_1,uint param_2)

{
  undefined2 unaff_DS;
  
  if (param_2 < 0xc) {
    *(uint *)0xda0 = param_2;
    *(undefined2 *)0xda2 = param_1;
    FUN_174b_15c7(param_1,param_2);
  }
  else {
    *(undefined2 *)0xd56 = 0xfff5;
  }
  return;
}



/* 174b:0bcb FUN_174b_0bcb */

void __stdcall16far FUN_174b_0bcb(uint param_1,undefined4 param_2)

{
  uint uVar1;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 local_a [8];
  
  FUN_1ad9_025d(8,local_a,unaff_SS,(int)param_2,(int)((ulong)param_2 >> 0x10));
  uVar1 = FUN_174b_14b6();
  if (uVar1 < param_1) {
    *(undefined2 *)0xd56 = 0xfff5;
  }
  else {
    *(undefined2 *)0xda0 = 0xc;
    *(uint *)0xda2 = param_1;
    FUN_1ad9_025d(8,0xda4,unaff_DS,local_a,unaff_SS);
    FUN_174b_11dd(param_1,local_a,unaff_SS);
  }
  return;
}



/* 174b:0c26 FUN_174b_0c26 */

void __stdcall16far FUN_174b_0c26(uint param_1)

{
  undefined2 unaff_DS;
  
  if (param_1 < 0x10) {
    *(undefined1 *)0xd7e = (undefined1)param_1;
    if (param_1 == 0) {
      *(undefined1 *)0xdb9 = 0;
    }
    else {
      *(undefined1 *)0xdb9 = *(undefined1 *)(param_1 + 0xdb9);
    }
    FUN_174b_1510((int)*(char *)0xdb9);
  }
  return;
}



/* 174b:0c5d FUN_174b_0c5d */

void __stdcall16far FUN_174b_0c5d(byte *param_1)

{
  byte *pbVar1;
  undefined2 uVar2;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 local_18 [17];
  undefined1 local_7;
  byte local_5;
  uint local_4;
  
  if (*(char *)0xd8c != '\0') {
    uVar2 = (undefined2)((ulong)param_1 >> 0x10);
    pbVar1 = (byte *)param_1;
    if (*param_1 < 0x11) {
      local_5 = *param_1;
    }
    else {
      local_5 = 0x10;
    }
    if (local_5 - 1 < 0x8000) {
      local_4 = 0;
      while( true ) {
        if (-1 < (char)pbVar1[local_4 + 1]) {
          *(byte *)(local_4 + 0xdb9) = pbVar1[local_4 + 1];
        }
        if (local_4 == local_5 - 1) break;
        local_4 = local_4 + 1;
      }
    }
    if (pbVar1[1] != 0xff) {
      *(undefined1 *)0xd7e = 0;
    }
    FUN_1ad9_19b6(0x11,local_18,unaff_SS,0xdb8,unaff_DS);
    local_7 = 0;
    FUN_174b_1559(local_18,unaff_SS);
  }
  return;
}



/* 174b:0d05 FUN_174b_0d05 */

void __stdcall16far FUN_174b_0d05(char param_1,uint param_2)

{
  undefined2 unaff_DS;
  
  if (((*(char *)0xd8c != '\0') && (param_2 <= *(byte *)0xdb8 - 1)) && (-1 < param_1)) {
    *(char *)(param_2 + 0xdb9) = param_1;
    if (param_2 == 0) {
      *(undefined1 *)0xd7e = 0;
    }
    FUN_174b_1543((int)param_1,param_2);
  }
  return;
}



/* 174b:0d49 FUN_174b_0d49 */

void __stdcall16far FUN_174b_0d49(undefined4 param_1)

{
  undefined2 unaff_DS;
  
  FUN_1ad9_025d(0x11,(int)param_1,(int)((ulong)param_1 >> 0x10),0xdb8,unaff_DS);
  return;
}



/* 174b:0d65 FUN_174b_0d65 */

void __stdcall16far FUN_174b_0d65(undefined4 param_1)

{
  undefined2 uVar1;
  undefined2 in_DX;
  
  uVar1 = FUN_174b_14d6();
  FUN_1ad9_025d(0x11,(int)param_1,(int)((ulong)param_1 >> 0x10),uVar1,in_DX);
  return;
}



/* 174b:0d86 FUN_174b_0d86 */

void __stdcall16far FUN_174b_0d86(uint param_1,uint param_2)

{
  undefined2 unaff_DS;
  
  if ((param_2 < 3) && (param_1 < 3)) {
    *(uint *)0xdd0 = param_2;
    *(uint *)0xdd2 = param_1;
    FUN_174b_1207(param_1,param_2);
  }
  else {
    *(undefined2 *)0xd56 = 0xfff5;
  }
  return;
}



/* 174b:0dca FUN_174b_0dca */

void __stdcall16far FUN_174b_0dca(undefined2 param_1,undefined2 param_2,uint param_3)

{
  undefined4 uVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  undefined2 *puVar5;
  undefined2 uVar6;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar7;
  undefined1 local_10c [256];
  undefined2 *local_c;
  int local_8;
  int iStack_6;
  undefined2 local_4;
  
  if ((0x14 < param_3) || ((param_3 != 0 && (*(char *)(param_3 * 0xf + 0x3f1) == '\0')))) {
    *(undefined2 *)0xd56 = 0xfff2;
    param_3 = 0;
    param_1 = 1;
    goto LAB_174b_0ff4;
  }
  if ((param_3 == 0) || (param_3 == *(uint *)0xdca)) goto LAB_174b_0ff4;
  if (param_3 != *(uint *)0xc88) {
    if (*(int *)0xc88 != 0) {
      iVar3 = *(int *)0xc88 * 0xf;
      _local_c = (undefined2 *)CONCAT22(unaff_DS,(undefined2 *)(iVar3 + 999));
      if (*(int *)(iVar3 + 0x3ef) != 0) {
        (*(code *)*(undefined2 *)0xc04)
                  (0x174b,*(undefined2 *)(iVar3 + 0x3ef),(undefined2 *)(iVar3 + 999),unaff_DS);
        uVar6 = (undefined2)((ulong)_local_c >> 0x10);
        puVar5 = (undefined2 *)_local_c;
        *_local_c = 0;
        puVar5[1] = 0;
        puVar5[2] = 0;
        puVar5[3] = 0;
        puVar5[4] = 0;
      }
    }
    iVar3 = param_3 * 0xf;
    _local_c = (undefined2 *)CONCAT22(unaff_DS,(undefined2 *)(iVar3 + 999));
    if (*(int *)(iVar3 + 0x3eb) == 0 && *(int *)(iVar3 + 0x3ed) == 0) {
      puVar7 = local_10c;
      uVar6 = unaff_SS;
      FUN_1ad9_062a(iVar3 + 0x3f1,unaff_DS);
      FUN_1ad9_06b7(0xdc5,0x1ad9);
      FUN_1ad9_0644(8,0xc8a,unaff_DS,puVar7,uVar6);
      cVar2 = FUN_174b_042f(0xfff3,&local_4,unaff_SS,0xc8a,unaff_DS,0xca2,unaff_DS);
      if (cVar2 == '\0') {
        if (*(int *)0xd56 == -3) {
          *(undefined2 *)0xd56 = 0xfff8;
        }
        param_3 = 0;
        param_1 = 1;
        goto LAB_174b_0ff4;
      }
      uVar1 = *(undefined4 *)0x544;
      *(undefined2 *)0xcfa = (int)uVar1;
      *(undefined2 *)0xcfc = (int)((ulong)uVar1 >> 0x10);
      *(undefined2 *)0x544 = 0xa5;
      *(undefined2 *)0x546 = 0x174b;
      (*(code *)*(undefined2 *)0xc00)(0x1ad9,local_4,&local_8);
      uVar1 = *(undefined4 *)0xcfa;
      *(undefined2 *)0x544 = (int)uVar1;
      *(undefined2 *)0x546 = (int)((ulong)uVar1 >> 0x10);
      if (local_8 == 0 && iStack_6 == 0) {
        FUN_1ad9_1828(0xc08,unaff_DS);
        *(undefined2 *)0xd56 = 0xfff7;
        param_3 = 0;
        param_1 = 1;
        goto LAB_174b_0ff4;
      }
      FUN_1ad9_1892(0,0,local_4,local_8,iStack_6,0xc08,unaff_DS);
      FUN_1ad9_1828(0xc08,unaff_DS);
      iVar3 = FUN_1ad9_0207();
      if (iVar3 == 0) {
        uVar4 = FUN_174b_026a(local_8,iStack_6);
        if ((-1 < (int)uVar4) && (param_3 == uVar4)) {
          uVar6 = (undefined2)((ulong)_local_c >> 0x10);
          ((undefined2 *)_local_c)[4] = local_4;
          *_local_c = (int)_local_8;
          ((undefined2 *)_local_c)[1] = (int)((ulong)_local_8 >> 0x10);
          goto LAB_174b_0fd7;
        }
      }
      *(undefined2 *)0xd56 = 0xfff3;
      (*(code *)*(undefined2 *)0xc04)(0x1ad9,local_4,&local_8);
      param_3 = 0;
      param_1 = 1;
      goto LAB_174b_0ff4;
    }
LAB_174b_0fd7:
    *(uint *)0xc88 = param_3;
  }
  uVar1 = *(undefined4 *)(param_3 * 0xf + 0x3eb);
  *(undefined2 *)0xd74 = (int)uVar1;
  *(undefined2 *)0xd76 = (int)((ulong)uVar1 >> 0x10);
LAB_174b_0ff4:
  *(uint *)0xdca = param_3;
  *(undefined2 *)0xdcc = param_2;
  *(undefined2 *)0xdce = param_1;
  FUN_174b_1612(param_1,param_2,param_3);
  return;
}



/* 174b:1019 FUN_174b_1019 */

void __cdecl16far FUN_174b_1019(void)

{
  undefined2 unaff_DS;
  
  *(undefined2 *)0xd56 = 0;
  *(undefined2 *)0x542 = 0x100;
  *(undefined2 *)0xcf4 = 0x1000;
  FUN_174b_12f0();
  FUN_174b_03b9();
  *(undefined2 *)0xc00 = 0xb9;
  *(undefined2 *)0xc02 = 0x174b;
  *(undefined2 *)0xc04 = 0xd4;
  *(undefined2 *)0xc06 = 0x174b;
  *(undefined1 *)0xc8a = 0;
  *(undefined1 *)0xc94 = 0;
  *(undefined2 *)0xcf6 = 6;
  *(undefined2 *)0xcf8 = 10;
  *(undefined2 *)0xd8e = 1;
  *(undefined2 *)0xd88 = 1;
  *(undefined2 *)0xd8a = 1;
  return;
}



/* 174b:107a FUN_174b_107a */

void __cdecl16far FUN_174b_107a(void)

{
  return;
}



/* 174b:107d FUN_174b_107d */

void __cdecl16near FUN_174b_107d(void)

{
  code *pcVar1;
  byte bVar2;
  undefined1 uVar3;
  undefined2 unaff_DS;
  
  if (*(char *)0xde1 == -1) {
    if (*(char *)0xd8e == -0x5b) {
      *(undefined1 *)0xde1 = 0;
      return;
    }
    pcVar1 = (code *)swi(0x10);
    uVar3 = (*pcVar1)();
    *(undefined1 *)0xde1 = uVar3;
    bVar2 = DAT_0000_0410;
    *(byte *)0xde2 = DAT_0000_0410;
    if ((*(char *)0xdda != '\x05') && (*(char *)0xdda != '\a')) {
      DAT_0000_0410 = bVar2 & 0xcf | 0x20;
    }
  }
  return;
}



/* 174b:10bc FUN_174b_10bc */

void __cdecl16far FUN_174b_10bc(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:10c8 FUN_174b_10c8 */

void FUN_174b_10c8(undefined2 param_1,undefined4 param_2)

{
  int iVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  
  *(undefined1 *)0xde1 = 0xff;
  uVar2 = (undefined2)((ulong)param_2 >> 0x10);
  iVar1 = (int)param_2;
  if (*(char *)(iVar1 + 0x16) == '\0') {
    uVar2 = (undefined2)((ulong)*(undefined4 *)0xd70 >> 0x10);
    iVar1 = (int)*(undefined4 *)0xd70;
  }
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  *(int *)0xd78 = iVar1;
  *(undefined2 *)0xd7a = uVar2;
  return;
}



/* 174b:10cd FUN_174b_10cd */

void __stdcall16far FUN_174b_10cd(undefined4 param_1)

{
  int iVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  
  uVar2 = (undefined2)((ulong)param_1 >> 0x10);
  iVar1 = (int)param_1;
  if (*(char *)(iVar1 + 0x16) == '\0') {
    uVar2 = (undefined2)((ulong)*(undefined4 *)0xd70 >> 0x10);
    iVar1 = (int)*(undefined4 *)0xd70;
  }
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  *(int *)0xd78 = iVar1;
  *(undefined2 *)0xd7a = uVar2;
  return;
}



/* 174b:1108 FUN_174b_1108 */

void __stdcall16far FUN_174b_1108(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:112b FUN_174b_112b */

void __stdcall16far FUN_174b_112b(byte param_1)

{
  undefined2 unaff_DS;
  
  FUN_174b_107d();
  if (param_1 < 10) {
    *(byte *)0xdd9 = param_1;
    FUN_174b_10cd(*(undefined2 *)0xddd,*(undefined2 *)0xddf);
  }
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:1157 FUN_174b_1157 */

void __cdecl16far FUN_174b_1157(void)

{
  code *pcVar1;
  undefined2 unaff_DS;
  
  if (*(char *)0xde1 != -1) {
    (*(code *)*(undefined2 *)0xd5e)(0x174b);
    if (*(char *)0xd8e != -0x5b) {
      DAT_0000_0410 = *(undefined1 *)0xde2;
      pcVar1 = (code *)swi(0x10);
      (*pcVar1)();
    }
  }
  *(undefined1 *)0xde1 = 0xff;
  return;
}



/* 174b:118b FUN_174b_118b */

void FUN_174b_118b(undefined2 param_1,undefined1 param_2)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b,param_2);
  FUN_174b_11b9();
  return;
}



/* 174b:11a5 FUN_174b_11a5 */

void FUN_174b_11a5(undefined2 param_1,undefined1 param_2)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b,param_2);
  FUN_174b_107a();
  return;
}



/* 174b:11b9 FUN_174b_11b9 */

void __stdcall16far FUN_174b_11b9(void)

{
  FUN_174b_107a();
  return;
}



/* 174b:11c3 FUN_174b_11c3 */

void FUN_174b_11c3(undefined2 param_1,undefined1 param_2)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b,param_2);
  FUN_174b_11b9();
  return;
}



/* 174b:11dd FUN_174b_11dd */

void __stdcall16far FUN_174b_11dd(undefined1 param_1)

{
  undefined2 unaff_DS;
  
  *(undefined1 *)0xd7d = param_1;
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  *(undefined1 *)0xd80 = 0xc;
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:1207 FUN_174b_1207 */

void __stdcall16far FUN_174b_1207(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:121b FUN_174b_121b */

void __stdcall16far FUN_174b_121b(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  FUN_174b_107a();
  return;
}



/* 174b:1264 FUN_174b_1264 */

void __stdcall16far FUN_174b_1264(undefined1 *param_1,byte *param_2,uint *param_3)

{
  byte bVar1;
  undefined2 unaff_DS;
  
  *(undefined1 *)0xdd8 = 0xff;
  *(undefined1 *)0xdd9 = 0;
  *(undefined1 *)0xddb = 10;
  bVar1 = *param_2;
  *(byte *)0xdda = bVar1;
  if (bVar1 == 0) {
    FUN_174b_12ce();
    bVar1 = *(byte *)0xdd8;
  }
  else {
    *(undefined1 *)0xdd9 = *param_1;
    bVar1 = *param_2;
    if ((char)bVar1 < '\0') {
      return;
    }
    *(undefined1 *)0xddb = *(undefined1 *)(bVar1 + 0x1741);
    bVar1 = *(byte *)(bVar1 + 0x1725);
    *(byte *)0xdd8 = bVar1;
  }
  *param_3 = (uint)bVar1;
  return;
}



/* 174b:12bc FUN_174b_12bc */

void __stdcall16far FUN_174b_12bc(void)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  
  uVar1 = *(undefined2 *)0xdd8;
  FUN_174b_12ce();
  *(undefined2 *)0xdd8 = uVar1;
  return;
}



/* 174b:12ce FUN_174b_12ce */

void __cdecl16near FUN_174b_12ce(void)

{
  uint uVar1;
  int unaff_BP;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  FUN_174b_174f();
  uVar1 = (uint)*(byte *)0xdda;
  if (*(byte *)0xdda == 0xff) {
    uVar1 = 0xffff;
  }
  *(uint *)*(undefined4 *)(unaff_BP + 10) = uVar1;
  *(uint *)*(undefined4 *)(unaff_BP + 6) = (uint)*(byte *)0xdd9;
  return;
}



/* 174b:12f0 FUN_174b_12f0 */

void __cdecl16far FUN_174b_12f0(void)

{
  undefined2 unaff_DS;
  
  *(undefined1 *)0xdd8 = 0xff;
  *(undefined1 *)0xdd9 = 0;
  *(undefined1 *)0xdda = 0;
  *(undefined1 *)0xddb = 0;
  *(undefined1 *)0xddc = 0;
  *(undefined2 *)0xddd = 0;
  *(undefined2 *)0xddf = 0;
  *(undefined1 *)0xde1 = 0xff;
  *(undefined1 *)0xde2 = 0;
  return;
}



/* 174b:1312 FUN_174b_1312 */

void __stdcall16far FUN_174b_1312(undefined4 param_1)

{
  undefined2 unaff_DS;
  
  FUN_174b_107d();
  *(undefined2 *)0xddd = (int)param_1;
  *(undefined2 *)0xddf = (int)((ulong)param_1 >> 0x10);
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:132e FUN_174b_132e */

void __cdecl16far FUN_174b_132e(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:133a FUN_174b_133a */

void __stdcall16far FUN_174b_133a(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:134e FUN_174b_134e */

void __stdcall16far FUN_174b_134e(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:1362 FUN_174b_1362 */

void __stdcall16far FUN_174b_1362(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:137c FUN_174b_137c */

void __stdcall16far FUN_174b_137c(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:1393 FUN_174b_1393 */

void __stdcall16far FUN_174b_1393(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:13aa FUN_174b_13aa */

void __stdcall16far FUN_174b_13aa(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:13c4 FUN_174b_13c4 */

void __stdcall16far
FUN_174b_13c4(undefined2 param_1,undefined2 param_2,uint param_3,uint param_4,uint param_5,
             uint param_6)

{
  undefined2 unaff_DS;
  
  if (param_4 <= param_6) {
    param_4 = param_6;
  }
  if (param_5 < param_3) {
    param_3 = param_5;
  }
  (*(code *)*(undefined2 *)0xd5e)(0x174b,param_3,param_4);
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:13fc FUN_174b_13fc */

void __stdcall16far FUN_174b_13fc(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:1423 FUN_174b_1423 */

void __stdcall16far FUN_174b_1423(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:1457 FUN_174b_1457 */

void __stdcall16far FUN_174b_1457(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:147e FUN_174b_147e */

void __stdcall16far FUN_174b_147e(undefined2 *param_1)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  int iVar3;
  undefined2 *in_BX;
  undefined2 *puVar4;
  undefined2 unaff_ES;
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  puVar4 = (undefined2 *)param_1;
  for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
    puVar2 = puVar4;
    puVar4 = puVar4 + 1;
    puVar1 = in_BX;
    in_BX = in_BX + 1;
    *puVar2 = *puVar1;
  }
  return;
}



/* 174b:149e FUN_174b_149e */

void __stdcall16far FUN_174b_149e(undefined1 param_1)

{
  undefined2 unaff_DS;
  
  *(undefined1 *)0xd7c = param_1;
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:14b6 FUN_174b_14b6 */

undefined2 __cdecl16far FUN_174b_14b6(void)

{
  undefined2 in_CX;
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return in_CX;
}



/* 174b:14c6 FUN_174b_14c6 */

undefined2 __cdecl16far FUN_174b_14c6(void)

{
  undefined2 in_BX;
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return in_BX;
}



/* 174b:14d6 FUN_174b_14d6 */

undefined2 __cdecl16far FUN_174b_14d6(void)

{
  undefined2 in_BX;
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return in_BX;
}



/* 174b:14e8 FUN_174b_14e8 */

undefined2 __stdcall16far FUN_174b_14e8(void)

{
  undefined2 in_BX;
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return in_BX;
}



/* 174b:14ff FUN_174b_14ff */

int __cdecl16far FUN_174b_14ff(void)

{
  int in_CX;
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return in_CX + -1;
}



/* 174b:1510 FUN_174b_1510 */

void __stdcall16far FUN_174b_1510(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:1526 FUN_174b_1526 */

void __stdcall16far FUN_174b_1526(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:1543 FUN_174b_1543 */

void __stdcall16far FUN_174b_1543(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:1559 FUN_174b_1559 */

void __stdcall16far FUN_174b_1559(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:156b FUN_174b_156b */

void __stdcall16far FUN_174b_156b(undefined1 param_1,undefined2 param_2,undefined1 param_3)

{
  undefined2 unaff_DS;
  
  *(undefined1 *)0xd7f = param_3;
  *(undefined1 *)0xddc = param_1;
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:158b FUN_174b_158b */

/* WARNING: Unable to track spacebase fully for stack */

void __stdcall16far FUN_174b_158b(void)

{
  undefined2 uVar1;
  code *pcVar2;
  int iVar3;
  undefined2 uVar4;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  uVar4 = (undefined2)((ulong)*(undefined4 *)0xddd >> 0x10);
  iVar3 = (int)*(undefined4 *)0xddd;
  uVar1 = *(undefined2 *)(iVar3 + 0xe);
  iVar3 = *(int *)(iVar3 + 0xc) + *(int *)(iVar3 + 0x10);
  *(undefined1 **)(iVar3 + -4) = &stack0xfffe;
  *(undefined2 *)(iVar3 + -6) = unaff_SS;
  uVar4 = ((undefined2 *)0xd5e)[1];
  pcVar2 = (code *)*(undefined2 *)0xd5e;
  *(undefined2 *)(iVar3 + -8) = 0x174b;
  *(undefined2 *)(iVar3 + -10) = 0x8a6b;
  (*pcVar2)();
  return;
}



/* 174b:15c7 FUN_174b_15c7 */

void __stdcall16far FUN_174b_15c7(undefined1 param_1,undefined1 param_2)

{
  undefined2 unaff_DS;
  
  *(undefined1 *)0xd7d = param_1;
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  *(undefined1 *)0xd80 = param_2;
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:15ee FUN_174b_15ee */

void __stdcall16far FUN_174b_15ee(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:1612 FUN_174b_1612 */

void __stdcall16far FUN_174b_1612(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:165a FUN_174b_165a */

void __stdcall16far FUN_174b_165a(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:1677 FUN_174b_1677 */

int __stdcall16far FUN_174b_1677(int param_1)

{
  undefined2 unaff_DS;
  
  param_1 = param_1 + 1;
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return param_1;
}



/* 174b:16a8 FUN_174b_16a8 */

undefined1 __stdcall16far FUN_174b_16a8(void)

{
  undefined1 extraout_DL;
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return extraout_DL;
}



/* 174b:16c0 FUN_174b_16c0 */

void __stdcall16far FUN_174b_16c0(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:16d7 FUN_174b_16d7 */

void __stdcall16far FUN_174b_16d7(int *param_1,uint param_2,uint param_3,uint param_4,uint param_5)

{
  uint uVar1;
  uint uVar2;
  undefined2 unaff_DS;
  
  uVar1 = param_5;
  if (param_3 <= param_5) {
    uVar1 = param_3;
    param_3 = param_5;
  }
  uVar2 = param_4;
  if (param_2 <= param_4) {
    uVar2 = param_2;
    param_2 = param_4;
  }
  *param_1 = param_3 - uVar1;
  ((int *)param_1)[1] = param_2 - uVar2;
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:170b FUN_174b_170b */

void __stdcall16far FUN_174b_170b(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xd5e)(0x174b);
  return;
}



/* 174b:174f FUN_174b_174f */

void __cdecl16near FUN_174b_174f(void)

{
  uint uVar1;
  undefined2 unaff_DS;
  
  *(undefined1 *)0xdd8 = 0xff;
  *(undefined1 *)0xdda = 0xff;
  *(undefined1 *)0xdd9 = 0;
  FUN_174b_1785();
  if (*(byte *)0xdda != 0xff) {
    uVar1 = (uint)*(byte *)0xdda;
    *(undefined1 *)0xdd8 = *(undefined1 *)(uVar1 + 0x1725);
    *(undefined1 *)0xdd9 = *(undefined1 *)(uVar1 + 0x1733);
    *(undefined1 *)0xddb = *(undefined1 *)(uVar1 + 0x1741);
  }
  return;
}



/* 174b:1785 FUN_174b_1785 */

void __cdecl16near FUN_174b_1785(void)

{
  code *pcVar1;
  byte bVar2;
  char cVar3;
  int iVar4;
  undefined2 unaff_DS;
  bool bVar5;
  
  pcVar1 = (code *)swi(0x10);
  bVar2 = (*pcVar1)();
  bVar5 = bVar2 < 7;
  if (bVar2 == 7) {
    FUN_174b_17ec();
    if (!bVar5) {
      cVar3 = FUN_174b_187d();
      if (cVar3 == '\0') {
        uRam000b8000 = ~uRam000b8000;
        *(undefined1 *)0xdda = 1;
        return;
      }
      *(undefined1 *)0xdda = 7;
      return;
    }
  }
  else {
    FUN_174b_187a();
    if (bVar5) {
      *(undefined1 *)0xdda = 6;
      return;
    }
    FUN_174b_17ec();
    if (!bVar5) {
      iVar4 = FUN_174b_18af();
      bVar5 = false;
      if (iVar4 == 0) {
        *(undefined1 *)0xdda = 1;
        FUN_174b_1859();
        if (bVar5) {
          *(undefined1 *)0xdda = 2;
        }
        return;
      }
      *(undefined1 *)0xdda = 10;
      return;
    }
  }
  FUN_174b_180a();
  return;
}



/* 174b:17ec FUN_174b_17ec */

void __cdecl16near FUN_174b_17ec(void)

{
  code *pcVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  
  cVar3 = '\x10';
  cVar4 = -1;
  cVar2 = '\x0f';
  pcVar1 = (code *)swi(0x10);
  (*pcVar1)();
  if (((cVar2 < '\f') && (cVar4 < '\x02')) && (cVar3 < '\x04')) {
    return;
  }
  return;
}



/* 174b:180a FUN_174b_180a */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl16near FUN_174b_180a(void)

{
  undefined2 in_BX;
  char cVar1;
  undefined2 unaff_DS;
  bool bVar2;
  
  *(undefined1 *)0xdda = 4;
  cVar1 = (char)((uint)in_BX >> 8);
  bVar2 = cVar1 == '\0';
  if (cVar1 != '\x01') {
    FUN_174b_184a();
    if ((!bVar2) && (bVar2 = false, (char)in_BX != '\0')) {
      *(undefined1 *)0xdda = 3;
      FUN_174b_1859();
      if ((bVar2) || ((_DAT_c000_0039 == 0x345a && (_DAT_c000_003b == 0x3934)))) {
        *(undefined1 *)0xdda = 9;
      }
    }
    return;
  }
  *(undefined1 *)0xdda = 5;
  return;
}



/* 174b:184a FUN_174b_184a */

void __cdecl16near FUN_174b_184a(void)

{
  return;
}



/* 174b:1859 FUN_174b_1859 */

void __cdecl16near FUN_174b_1859(void)

{
  code *pcVar1;
  char cVar2;
  byte in_BL;
  
  pcVar1 = (code *)swi(0x10);
  cVar2 = (*pcVar1)();
  if ((cVar2 == '\x1a') && (((in_BL == 7 || (in_BL == 8)) || ((10 < in_BL && (in_BL < 0xd)))))) {
    return;
  }
  return;
}



/* 174b:187a FUN_174b_187a */

undefined1 __cdecl16near FUN_174b_187a(void)

{
  return 0;
}



/* 174b:187d FUN_174b_187d */

undefined1 __cdecl16near FUN_174b_187d(void)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  byte bVar4;
  
  bVar4 = 0;
  bVar1 = in(0x3ba);
  iVar3 = -0x8000;
  while ((bVar2 = in(0x3ba), (bVar2 & 0x80) == (bVar1 & 0x80) || (bVar4 = bVar4 + 1, bVar4 < 10))) {
    iVar3 = iVar3 + -1;
    if (iVar3 == 0) {
      return 0;
    }
  }
  iVar3 = -0x8000;
  do {
    bVar1 = in(0x3ba);
    if ((bVar1 & 0x30) != 0x10) {
      return 1;
    }
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return 2;
}



/* 174b:18af FUN_174b_18af */

undefined2 __cdecl16near FUN_174b_18af(void)

{
  code *pcVar1;
  byte bVar2;
  int iVar3;
  int extraout_DX;
  
  iVar3 = 0;
  pcVar1 = (code *)swi(0x10);
  (*pcVar1)();
  if (iVar3 != 0 || extraout_DX != 0) {
    if (((*(char *)(extraout_DX + 2) == '\0') || (*(char *)(extraout_DX + 2) == '\x02')) &&
       (bVar2 = in(0x188), (bVar2 & 4) != 0)) {
      return 1;
    }
  }
  return 0;
}



/* 1a70:000b FUN_1a70_000b */

undefined2 __cdecl16far FUN_1a70_000b(undefined2 *param_1)

{
  return *param_1;
}



/* 1a77:0000 FUN_1a77_0000 */

void __cdecl16far FUN_1a77_0000(void)

{
  undefined2 unaff_DS;
  
  FUN_1a77_0030();
  FUN_1a77_032e(0xdf8,unaff_DS);
  FUN_1ad9_13e2(0x1a77,0xdf8);
  FUN_1a77_032e(0xef8,unaff_DS);
  FUN_1ad9_13e7(0x1ad9,0xef8);
  return;
}



/* 1a77:0030 FUN_1a77_0030 */

/* WARNING: Removing unreachable block (ram,0x0001a7e6) */

void __cdecl16near FUN_1a77_0030(void)

{
  byte bVar1;
  byte extraout_AH;
  undefined2 unaff_DS;
  
  bVar1 = FUN_1a77_0608();
  if ((bVar1 != 7) && (3 < bVar1)) {
    FUN_1a77_0099();
  }
  FUN_1a77_00e7();
  FUN_1a77_0608();
  *(byte *)0xdf4 = extraout_AH & 0x7f;
  *(byte *)0xdea = extraout_AH & 0x7f;
  *(undefined1 *)0xde5 = 0;
  *(undefined1 *)0xdf5 = 0;
  *(undefined1 *)0xdf6 = 0;
  *(undefined1 *)0xde4 = 1;
  do {
  } while( true );
}



/* 1a77:0099 FUN_1a77_0099 */

void __cdecl16near FUN_1a77_0099(void)

{
  undefined2 in_AX;
  char extraout_DL;
  
  DAT_0000_0487 = DAT_0000_0487 & 0xfe;
  if (((byte)in_AX != 7) && (3 < (byte)in_AX)) {
    in_AX = CONCAT11((char)((uint)in_AX >> 8),3);
  }
  FUN_1a77_0608();
  if ((char)((uint)in_AX >> 8) != '\0') {
    FUN_1a77_0608();
    FUN_1a77_0608();
    if (extraout_DL == '*') {
      DAT_0000_0487 = DAT_0000_0487 | 1;
      FUN_1a77_0608();
      FUN_1a77_0608();
    }
  }
  return;
}



/* 1a77:00e7 FUN_1a77_00e7 */

void __cdecl16near FUN_1a77_00e7(void)

{
  uint uVar1;
  uint uVar2;
  undefined1 uVar3;
  byte extraout_DL;
  byte bVar4;
  undefined2 uVar5;
  undefined2 unaff_DS;
  
  uVar1 = FUN_1a77_0608();
  FUN_1a77_0608();
  uVar3 = 0;
  bVar4 = extraout_DL;
  if ((extraout_DL == 0) && (bVar4 = 0x18, (byte)uVar1 < 4)) {
    uVar3 = 1;
  }
  uVar5 = CONCAT11(bVar4,(char)(uVar1 >> 8) + -1);
  uVar2 = uVar1 & 0xff;
  if (0x18 < bVar4) {
    uVar2 = CONCAT11(1,(byte)uVar1);
  }
  *(uint *)0xde8 = uVar2;
  *(undefined2 *)0xdf2 = uVar5;
  *(undefined1 *)0xde7 = uVar3;
  *(undefined1 *)0xde6 = 1;
  *(undefined2 *)0xdec = 0;
  *(undefined2 *)0xdee = uVar5;
  return;
}



/* 1a77:0145 FUN_1a77_0145 */

void __cdecl16near FUN_1a77_0145(void)

{
  code *pcVar1;
  undefined2 unaff_DS;
  undefined1 uVar2;
  
  if (*(char *)0xdf6 == '\0') {
    return;
  }
  *(undefined1 *)0xdf6 = 0;
  uVar2 = 0;
  while( true ) {
    pcVar1 = (code *)swi(0x16);
    (*pcVar1)();
    if ((bool)uVar2) break;
    pcVar1 = (code *)swi(0x16);
    (*pcVar1)();
  }
  FUN_1a77_047b();
  FUN_1a77_047b();
  FUN_1a77_0474();
  pcVar1 = (code *)swi(0x23);
  (*pcVar1)();
  FUN_1a77_0099();
  FUN_1a77_00e7();
  *(undefined1 *)0xdea = *(undefined1 *)0xdf4;
  return;
}



/* 1a77:029e pascal_delay_ms */

void __stdcall16far pascal_delay_ms(int param_1)

{
  int extraout_DX;
  
  if (param_1 != 0) {
    do {
      FUN_1a77_02be();
    } while (extraout_DX != 1);
  }
  return;
}



/* 1a77:02be FUN_1a77_02be */

void __cdecl16near FUN_1a77_02be(void)

{
  char in_AL;
  int in_CX;
  char *unaff_DI;
  undefined2 unaff_ES;
  
  do {
    if (in_AL != *unaff_DI) {
      return;
    }
    in_CX = in_CX + -1;
  } while (in_CX != 0);
  return;
}



/* 1a77:02c6 pc_speaker_sound_hz */

undefined2 __stdcall16far pc_speaker_sound_hz(uint param_1)

{
  byte bVar1;
  undefined2 uVar2;
  undefined1 uVar3;
  
  uVar2 = 0x34dd;
  if (0x12 < param_1) {
    uVar3 = (undefined1)(0x1234dd / (ulong)param_1 >> 8);
    bVar1 = in(0x61);
    if ((bVar1 & 3) == 0) {
      out(0x61,bVar1 | 3);
      out(0x43,0xb6);
    }
    out(0x42,(char)(0x1234dd / (ulong)param_1));
    uVar2 = CONCAT11(uVar3,uVar3);
    out(0x42,uVar3);
  }
  return uVar2;
}



/* 1a77:02f3 pc_speaker_no_sound */

byte __cdecl16far pc_speaker_no_sound(void)

{
  byte bVar1;
  
  bVar1 = in(0x61);
  out(0x61,bVar1 & 0xfc);
  return bVar1 & 0xfc;
}



/* 1a77:02fa FUN_1a77_02fa */

undefined1 __cdecl16far FUN_1a77_02fa(void)

{
  code *pcVar1;
  undefined2 unaff_DS;
  bool bVar2;
  
  bVar2 = *(char *)0xdf5 == '\0';
  if (bVar2) {
    pcVar1 = (code *)swi(0x16);
    (*pcVar1)();
    if (bVar2) {
      return 0;
    }
  }
  return 1;
}



/* 1a77:030c FUN_1a77_030c */

void __cdecl16far FUN_1a77_030c(void)

{
  code *pcVar1;
  char cVar2;
  undefined1 extraout_AH;
  undefined2 unaff_DS;
  
  cVar2 = *(char *)0xdf5;
  *(undefined1 *)0xdf5 = 0;
  if (cVar2 == '\0') {
    pcVar1 = (code *)swi(0x16);
    cVar2 = (*pcVar1)();
    if (cVar2 == '\0') {
      *(undefined1 *)0xdf5 = extraout_AH;
    }
  }
  FUN_1a77_0145();
  return;
}



/* 1a77:032e FUN_1a77_032e */

void __stdcall16far FUN_1a77_032e(undefined4 param_1)

{
  int iVar1;
  undefined2 uVar2;
  
  uVar2 = (undefined2)((ulong)param_1 >> 0x10);
  iVar1 = (int)param_1;
  *(undefined2 *)(iVar1 + 2) = 0xd7b0;
  *(undefined2 *)(iVar1 + 4) = 0x80;
  *(int *)(iVar1 + 0xc) = iVar1 + 0x80;
  *(undefined2 *)(iVar1 + 0xe) = uVar2;
  *(undefined2 *)(iVar1 + 0x10) = 0x359;
  *(undefined2 *)(iVar1 + 0x12) = 0x1a77;
  *(undefined1 *)(iVar1 + 0x30) = 0;
  return;
}



/* 1a77:0391 FUN_1a77_0391 */

void __stdcall16far FUN_1a77_0391(undefined4 param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  uint extraout_DX;
  uint extraout_DX_00;
  uint extraout_DX_01;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  undefined2 uVar8;
  undefined2 uVar9;
  undefined2 unaff_DS;
  
  uVar8 = (undefined2)((ulong)param_1 >> 0x10);
  iVar6 = (int)param_1;
  uVar3 = *(int *)(iVar6 + 4) - 2;
  uVar9 = (undefined2)((ulong)*(undefined4 *)(iVar6 + 0xc) >> 0x10);
  iVar7 = (int)*(undefined4 *)(iVar6 + 0xc);
  uVar4 = 0;
  uVar5 = *(uint *)(iVar6 + 8);
LAB_1a77_03a7:
  do {
    *(undefined1 *)0xdf5 = 0;
    bVar1 = FUN_1a77_030c();
    iVar2 = 1;
    if ((bVar1 == 8) || (bVar1 == 0x13)) {
LAB_1a77_03eb:
      do {
        if (uVar4 == 0) break;
        FUN_1a77_047b();
        FUN_1a77_047b();
        FUN_1a77_047b();
        uVar4 = uVar4 - 1;
        iVar2 = iVar2 + -1;
        uVar3 = extraout_DX_00;
      } while (iVar2 != 0);
      goto LAB_1a77_03a7;
    }
    if (bVar1 == 4) {
LAB_1a77_0403:
      do {
        if ((uVar4 == uVar5) || (*(byte *)(uVar4 + iVar7) < 0x20)) break;
        FUN_1a77_047b();
        uVar4 = uVar4 + 1;
        iVar2 = iVar2 + -1;
        uVar3 = extraout_DX_01;
      } while (iVar2 != 0);
    }
    else {
      iVar2 = 0;
      if ((bVar1 == 0x1b) || (bVar1 == 1)) goto LAB_1a77_03eb;
      if (bVar1 == 6) goto LAB_1a77_0403;
      if (bVar1 == 0x1a) {
        if (*(char *)0xde5 != '\0') {
          *(undefined1 *)(uVar4 + iVar7) = 0x1a;
          iVar7 = uVar4 + 1;
LAB_1a77_042d:
          *(undefined2 *)(iVar6 + 8) = 0;
          *(int *)(iVar6 + 10) = iVar7;
          return;
        }
      }
      else {
        if (bVar1 == 0xd) {
          FUN_1a77_0474();
          *(undefined2 *)(uVar4 + iVar7) = 0xa0d;
          iVar7 = uVar4 + 2;
          goto LAB_1a77_042d;
        }
        if ((0x1f < bVar1) && (uVar4 != uVar3)) {
          *(byte *)(uVar4 + iVar7) = bVar1;
          uVar4 = uVar4 + 1;
          FUN_1a77_047b();
          uVar3 = extraout_DX;
          if (uVar5 < uVar4) {
            uVar5 = uVar4;
          }
        }
      }
    }
  } while( true );
}



/* 1a77:0474 FUN_1a77_0474 */

/* WARNING: Removing unreachable block (ram,0x0001ac33) */
/* WARNING: Removing unreachable block (ram,0x0001ac29) */
/* WARNING: Removing unreachable block (ram,0x0001ac2f) */
/* WARNING: Removing unreachable block (ram,0x0001ac04) */
/* WARNING: Removing unreachable block (ram,0x0001ac1c) */
/* WARNING: Removing unreachable block (ram,0x0001ac22) */

void FUN_1a77_0474(void)

{
  FUN_1a77_047b();
  thunk_FUN_1a77_0608();
  FUN_1a77_04d4();
  thunk_FUN_1a77_0608();
  return;
}



/* 1a77:047b FUN_1a77_047b */

void __cdecl16near FUN_1a77_047b(void)

{
  char in_AL;
  char extraout_DL;
  undefined2 unaff_DS;
  
  thunk_FUN_1a77_0608();
  if (in_AL == '\a') {
    FUN_1a77_0608();
  }
  else if (((in_AL != '\b') && (in_AL != '\r')) &&
          ((in_AL == '\n' || (FUN_1a77_0608(), *(byte *)0xdee < (byte)(extraout_DL + 1U))))) {
    FUN_1a77_04d4();
  }
  thunk_FUN_1a77_0608();
  return;
}



/* 1a77:04d4 FUN_1a77_04d4 */

void __cdecl16near FUN_1a77_04d4(void)

{
  undefined2 in_DX;
  undefined2 unaff_DS;
  
  if (*(byte *)0xdef < (byte)((char)((uint)in_DX >> 8) + 1U)) {
    FUN_1a77_0608();
  }
  return;
}



/* 1a77:04f5 thunk_FUN_1a77_0608 */

void __cdecl16near thunk_FUN_1a77_0608(void)

{
  FUN_1a77_0608();
  return;
}



/* 1a77:04fc thunk_FUN_1a77_0608 */

void __cdecl16near thunk_FUN_1a77_0608(void)

{
  FUN_1a77_0608();
  return;
}



/* 1a77:0608 FUN_1a77_0608 */

void __cdecl16near FUN_1a77_0608(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x10);
  (*pcVar1)();
  return;
}



/* 1ad9:0000 FUN_1ad9_0000 */

void __cdecl16far FUN_1ad9_0000(void)

{
  code *pcVar1;
  int iVar2;
  undefined2 in_BX;
  undefined2 *puVar3;
  undefined2 unaff_ES;
  int unaff_SS;
  
  DAT_1c79_052a = ((uint)&stack0x0013 >> 4) + unaff_SS;
  DAT_1c79_052e = DAT_1c79_052a + DAT_1c79_0524;
  DAT_1c79_0540 = *(int *)0x2 + -0x1000;
  puVar3 = (undefined2 *)0xff8;
  iVar2 = 0x12;
  DAT_1c79_052c = DAT_1c79_052a;
  DAT_1c79_0538 = DAT_1c79_052e;
  DAT_1c79_053c = DAT_1c79_052e;
  DAT_1c79_0552 = unaff_ES;
  do {
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
    *puVar3 = in_BX;
    puVar3[1] = unaff_ES;
    puVar3 = puVar3 + 2;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  FUN_1ad9_1372();
  FUN_1ad9_13e2();
  FUN_1ad9_1372();
  FUN_1ad9_13e7();
  return;
}



/* 1ad9:00d1 FUN_1ad9_00d1 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: ram */

void __cdecl16far FUN_1ad9_00d1(void)

{
  code *pcVar1;
  undefined2 in_AX;
  int iVar2;
  int iVar3;
  char *pcVar4;
  int in_stack_00000000;
  int in_stack_00000002;
  
  DAT_1c79_054c = in_AX;
  iVar2 = DAT_1c79_0530;
  if (in_stack_00000000 != 0 || in_stack_00000002 != 0) {
    for (; (iVar3 = in_stack_00000002, iVar2 != 0 &&
           (iVar3 = iVar2, in_stack_00000002 != *(int *)0x10)); iVar2 = *(int *)0x14) {
    }
    in_stack_00000002 = (iVar3 - DAT_1c79_0552) + -0x10;
  }
  DAT_1c79_054e = in_stack_00000000;
  DAT_1c79_0550 = in_stack_00000002;
  pcVar4 = (char *)_DAT_1c79_0548;
  if ((int)((ulong)_DAT_1c79_0548 >> 0x10) == 0 && pcVar4 == (char *)0x0) {
    FUN_1ad9_143b();
    FUN_1ad9_143b();
    iVar2 = 0x12;
    do {
      pcVar1 = (code *)swi(0x21);
      (*pcVar1)();
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    if (DAT_1c79_054e != 0 || DAT_1c79_0550 != 0) {
      FUN_1ad9_0194();
      FUN_1ad9_01a2();
      FUN_1ad9_0194();
      FUN_1ad9_01bc();
      FUN_1ad9_01d6();
      FUN_1ad9_01bc();
      pcVar4 = (char *)0x203;
      FUN_1ad9_0194();
    }
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
    for (; *pcVar4 != '\0'; pcVar4 = pcVar4 + 1) {
      FUN_1ad9_01d6();
    }
    return;
  }
  _DAT_1c79_0548 = (char *)0x0;
  DAT_1c79_0556 = 0;
  return;
}



/* 1ad9:00d8 FUN_1ad9_00d8 */

/* WARNING: Removing unreachable block (ram,0x0001ae7b) */
/* WARNING: Removing unreachable block (ram,0x0001ae7e) */
/* WARNING: Removing unreachable block (ram,0x0001ae82) */
/* WARNING: Removing unreachable block (ram,0x0001ae91) */
/* WARNING: Removing unreachable block (ram,0x0001ae8b) */
/* WARNING: Removing unreachable block (ram,0x0001ae93) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl16far FUN_1ad9_00d8(void)

{
  code *pcVar1;
  undefined2 in_AX;
  int iVar2;
  char *pcVar3;
  undefined2 uVar4;
  
  uVar4 = 0x1c79;
  DAT_1c79_054c = in_AX;
  DAT_1c79_054e = 0;
  DAT_1c79_0550 = 0;
  pcVar3 = (char *)_DAT_1c79_0548;
  if ((int)((ulong)_DAT_1c79_0548 >> 0x10) == 0 && pcVar3 == (char *)0x0) {
    FUN_1ad9_143b(0xdf8,0x1c79);
    FUN_1ad9_143b(0xef8,0x1c79);
    iVar2 = 0x12;
    do {
      pcVar1 = (code *)swi(0x21);
      (*pcVar1)();
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    if (*(int *)0x54e != 0 || *(int *)0x550 != 0) {
      FUN_1ad9_0194();
      FUN_1ad9_01a2();
      FUN_1ad9_0194();
      FUN_1ad9_01bc();
      FUN_1ad9_01d6();
      FUN_1ad9_01bc();
      pcVar3 = (char *)0x203;
      FUN_1ad9_0194();
    }
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
    for (; *pcVar3 != '\0'; pcVar3 = pcVar3 + 1) {
      FUN_1ad9_01d6();
    }
    return;
  }
  _DAT_1c79_0548 = (char *)0x0;
  DAT_1c79_0556 = 0;
  return;
}



/* 1ad9:0194 FUN_1ad9_0194 */

void __cdecl16near FUN_1ad9_0194(void)

{
  char *in_BX;
  
  for (; *in_BX != '\0'; in_BX = in_BX + 1) {
    FUN_1ad9_01d6();
  }
  return;
}



/* 1ad9:01a2 FUN_1ad9_01a2 */

undefined2 __cdecl16near FUN_1ad9_01a2(void)

{
  undefined2 uVar1;
  undefined1 uVar2;
  
  FUN_1ad9_01ae();
  uVar1 = FUN_1ad9_01ae();
  uVar1 = CONCAT11((char)((uint)uVar1 >> 8),(char)uVar1 + '0');
  FUN_1ad9_01d6(uVar1);
  uVar2 = (undefined1)((uint)uVar1 >> 8);
  return CONCAT11(uVar2,uVar2);
}



/* 1ad9:01ae FUN_1ad9_01ae */

undefined2 __cdecl16near FUN_1ad9_01ae(void)

{
  uint in_AX;
  undefined2 uVar1;
  undefined1 uVar2;
  byte in_CL;
  
  uVar1 = CONCAT11((char)((in_AX & 0xff) % (uint)in_CL),(char)((in_AX & 0xff) / (uint)in_CL) + '0');
  FUN_1ad9_01d6(uVar1);
  uVar2 = (undefined1)((uint)uVar1 >> 8);
  return CONCAT11(uVar2,uVar2);
}



/* 1ad9:01bc FUN_1ad9_01bc */

void FUN_1ad9_01bc(void)

{
  code *pcVar1;
  
  FUN_1ad9_01c3();
  FUN_1ad9_01ce();
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  return;
}



/* 1ad9:01c3 FUN_1ad9_01c3 */

void FUN_1ad9_01c3(void)

{
  code *pcVar1;
  
  FUN_1ad9_01ce();
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  return;
}



/* 1ad9:01ce FUN_1ad9_01ce */

void FUN_1ad9_01ce(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  return;
}



/* 1ad9:01d6 FUN_1ad9_01d6 */

void __cdecl16near FUN_1ad9_01d6(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  return;
}



/* 1ad9:0207 FUN_1ad9_0207 */

undefined2 __cdecl16far FUN_1ad9_0207(void)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  
  LOCK();
  uVar1 = *(undefined2 *)0x556;
  *(undefined2 *)0x556 = 0;
  UNLOCK();
  return uVar1;
}



/* 1ad9:020e FUN_1ad9_020e */

void __cdecl16far FUN_1ad9_020e(void)

{
  undefined2 unaff_DS;
  
  if (*(int *)0x556 == 0) {
    return;
  }
  FUN_1ad9_00d1();
  return;
}



/* 1ad9:025d FUN_1ad9_025d */

void __stdcall16far FUN_1ad9_025d(int param_1,undefined1 *param_2,undefined1 *param_3)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  
  puVar3 = (undefined1 *)param_3;
  puVar4 = (undefined1 *)param_2;
  for (; param_1 != 0; param_1 = param_1 + -1) {
    puVar2 = puVar4;
    puVar4 = puVar4 + 1;
    puVar1 = puVar3;
    puVar3 = puVar3 + 1;
    *puVar2 = *puVar1;
  }
  return;
}



/* 1ad9:0279 FUN_1ad9_0279 */

int __cdecl16far FUN_1ad9_0279(void)

{
  int in_AX;
  int in_CX;
  
  return in_AX * in_CX;
}



/* 1ad9:0294 FUN_1ad9_0294 */

uint __cdecl16far FUN_1ad9_0294(void)

{
  uint uVar1;
  uint in_AX;
  uint in_CX;
  uint uVar2;
  uint uVar3;
  uint in_DX;
  uint in_BX;
  uint uVar4;
  uint uVar5;
  int iVar6;
  bool bVar7;
  bool bVar8;
  bool bVar9;
  bool bVar10;
  
  if (in_CX == 0 && in_BX == 0) {
    uVar2 = FUN_1ad9_00d1();
    return uVar2;
  }
  bVar9 = (int)in_BX < 0;
  if (bVar9) {
    uVar2 = ~in_CX;
    in_CX = uVar2 + 1;
    in_BX = ~in_BX + (uint)(0xfffe < uVar2);
  }
  bVar10 = (int)in_DX < 0;
  if (bVar10) {
    uVar2 = ~in_AX;
    in_AX = uVar2 + 1;
    in_DX = ~in_DX + (uint)(0xfffe < uVar2);
  }
  uVar2 = 0;
  bVar7 = false;
  uVar4 = 0;
  iVar6 = 0x21;
  do {
    uVar3 = uVar2 << 1 | (uint)bVar7;
    uVar5 = uVar4 << 1 | (uint)((int)uVar2 < 0);
    uVar2 = uVar3 - in_CX;
    uVar3 = (uint)(uVar3 < in_CX);
    uVar1 = uVar5 - in_BX;
    bVar7 = uVar5 < in_BX || uVar1 < uVar3;
    uVar4 = uVar1 - uVar3;
    if (uVar5 < in_BX || uVar1 < uVar3) {
      bVar8 = CARRY2(uVar2,in_CX);
      uVar2 = uVar2 + in_CX;
      bVar7 = CARRY2(uVar4,in_BX) || CARRY2(uVar4 + in_BX,(uint)bVar8);
      uVar4 = uVar4 + in_BX + (uint)bVar8;
    }
    bVar8 = (int)in_AX < 0;
    in_AX = in_AX << 1 | (uint)!bVar7;
    bVar7 = (int)in_DX < 0;
    in_DX = in_DX << 1 | (uint)bVar8;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  if (bVar10) {
    if (bVar9) {
      return in_AX;
    }
  }
  else if (!bVar9) {
    return in_AX;
  }
  return ~in_AX + 1;
}



/* 1ad9:0329 FUN_1ad9_0329 */

undefined4 __stdcall16far FUN_1ad9_0329(void)

{
  undefined2 uVar1;
  undefined2 in_CX;
  undefined2 extraout_DX;
  undefined2 uVar2;
  undefined1 in_CF;
  
  FUN_1ad9_041d();
  if (!(bool)in_CF) {
    return CONCAT22(register0x00000010,in_CX);
  }
  uVar2 = extraout_DX;
  uVar1 = FUN_1ad9_00d1();
  return CONCAT22(uVar2,uVar1);
}



/* 1ad9:0341 FUN_1ad9_0341 */

void __stdcall16far FUN_1ad9_0341(void)

{
  undefined1 in_CF;
  
  FUN_1ad9_04d8();
  if (!(bool)in_CF) {
    return;
  }
  FUN_1ad9_00d1();
  return;
}



/* 1ad9:041d FUN_1ad9_041d */

/* WARNING: Removing unreachable block (ram,0x0001b235) */
/* WARNING: Removing unreachable block (ram,0x0001b1e5) */

undefined2 __cdecl16near FUN_1ad9_041d(void)

{
  undefined2 in_AX;
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint unaff_SI;
  uint *puVar5;
  undefined2 uVar6;
  undefined2 unaff_DS;
  ulong uVar7;
  
  while( true ) {
    uVar7 = FUN_1ad9_060d();
    uVar1 = (uint)(uVar7 >> 0x10);
    uVar6 = (undefined2)((ulong)*(undefined4 *)0x53e >> 0x10);
    for (puVar5 = (uint *)(uint *)*(undefined4 *)0x53e; puVar5 != (uint *)0x0; puVar5 = puVar5 + 4)
    {
      uVar3 = puVar5[3] - puVar5[1];
      if (uVar1 <= uVar3) {
        iVar4 = puVar5[2] - *puVar5;
        if (puVar5[2] < *puVar5) {
          iVar4 = iVar4 + 0x10;
          uVar3 = uVar3 - 1;
        }
        if (uVar7 <= CONCAT22(uVar3,iVar4)) {
          uVar1 = uVar1 + puVar5[1];
          uVar3 = (int)uVar7 + *puVar5;
          if (0xf < uVar3) {
            uVar3 = uVar3 - 0x10;
            uVar1 = uVar1 + 1;
          }
          *puVar5 = uVar3;
          puVar5[1] = uVar1;
          if (uVar1 != puVar5[3]) {
            return in_AX;
          }
          if (uVar3 != puVar5[2]) {
            return in_AX;
          }
          FUN_1ad9_05af();
          return in_AX;
        }
      }
    }
    uVar7 = FUN_1ad9_05c4();
    iVar4 = -*(int *)0x53c;
    iVar2 = unaff_SI - *(uint *)0x53a;
    if (unaff_SI < *(uint *)0x53a) {
      iVar2 = iVar2 + 0x10;
      iVar4 = iVar4 + -1;
    }
    if (uVar7 <= CONCAT22(iVar4,iVar2)) break;
    if (*(int *)0x544 == 0 && *(int *)0x546 == 0) {
      return in_AX;
    }
    iVar4 = (*(code *)*(undefined2 *)0x544)(0x1ad9,in_AX);
    if (iVar4 == 0) {
      return in_AX;
    }
    if (iVar4 == 1) {
      return in_AX;
    }
  }
  iVar4 = (int)(uVar7 >> 0x10) + *(int *)0x53c;
  uVar1 = (int)uVar7 + *(int *)0x53a;
  if (0xf < uVar1) {
    uVar1 = uVar1 - 0x10;
    iVar4 = iVar4 + 1;
  }
  *(uint *)0x53a = uVar1;
  *(int *)0x53c = iVar4;
  return in_AX;
}



/* 1ad9:04d8 FUN_1ad9_04d8 */

void __cdecl16near FUN_1ad9_04d8(void)

{
  int in_AX;
  uint uVar1;
  uint in_CX;
  uint uVar2;
  uint in_BX;
  uint *puVar3;
  undefined2 uVar4;
  undefined2 unaff_DS;
  bool bVar5;
  undefined4 uVar6;
  
  if (in_AX != 0) {
    uVar6 = FUN_1ad9_060d();
    uVar2 = (int)((ulong)uVar6 >> 0x10) + in_BX;
    uVar1 = (int)uVar6 + in_CX;
    if (0xf < uVar1) {
      uVar1 = uVar1 - 0x10;
      uVar2 = uVar2 + 1;
    }
    uVar6 = CONCAT22(uVar2,uVar1);
    if ((*(uint *)0x538 <= in_BX) &&
       ((((*(uint *)0x538 < in_BX || (*(uint *)0x536 <= in_CX)) && (uVar2 <= *(uint *)0x53c)) &&
        ((uVar2 < *(uint *)0x53c || (uVar1 <= *(uint *)0x53a)))))) {
      uVar4 = (undefined2)((ulong)*(undefined4 *)0x53e >> 0x10);
      puVar3 = (uint *)(uint *)*(undefined4 *)0x53e;
      do {
        uVar2 = (uint)((ulong)uVar6 >> 0x10);
        uVar1 = (uint)uVar6;
        if (puVar3 == (uint *)0x0) {
          bVar5 = uVar2 < *(uint *)0x53c;
          if ((uVar2 == *(uint *)0x53c) && (bVar5 = uVar1 < *(uint *)0x53a, uVar1 == *(uint *)0x53a)
             ) {
            *(uint *)0x53a = in_CX;
            *(uint *)0x53c = in_BX;
            return;
          }
          uVar6 = FUN_1ad9_058b();
          if (!bVar5) {
            *(uint *)0x0 = in_CX;
            *(uint *)0x2 = in_BX;
            *(undefined2 *)0x4 = (int)uVar6;
            *(undefined2 *)0x6 = (int)((ulong)uVar6 >> 0x10);
          }
          return;
        }
        if ((in_BX < puVar3[1]) || ((in_BX <= puVar3[1] && (in_CX < *puVar3)))) {
          if ((puVar3[1] <= uVar2) && ((puVar3[1] < uVar2 || (*puVar3 <= uVar1))))
          goto LAB_1ad9_0541;
        }
        else if ((in_BX <= puVar3[3]) && ((in_BX < puVar3[3] || (in_CX <= puVar3[2])))) {
          in_CX = *puVar3;
          in_BX = puVar3[1];
LAB_1ad9_0541:
          uVar6 = FUN_1ad9_05af();
        }
        puVar3 = puVar3 + 4;
      } while( true );
    }
  }
  return;
}



/* 1ad9:058b FUN_1ad9_058b */

void __cdecl16near FUN_1ad9_058b(void)

{
  uint uVar1;
  undefined2 unaff_DS;
  
  uVar1 = *(int *)0x53e - 8;
  if ((uVar1 != 0) && (*(uint *)0x53c < (uVar1 >> 4) + *(int *)0x540)) {
    *(uint *)0x53e = uVar1;
    return;
  }
  return;
}



/* 1ad9:05af FUN_1ad9_05af */

void __cdecl16near FUN_1ad9_05af(void)

{
  undefined2 *puVar1;
  undefined2 *unaff_DI;
  undefined2 unaff_ES;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)*(undefined2 *)0x53e;
  *unaff_DI = *puVar1;
  unaff_DI[1] = puVar1[1];
  unaff_DI[2] = puVar1[2];
  unaff_DI[3] = puVar1[3];
  *(int *)0x53e = (int)(puVar1 + 4);
  return;
}



/* 1ad9:05c4 FUN_1ad9_05c4 */

void __cdecl16near FUN_1ad9_05c4(void)

{
  undefined2 unaff_DS;
  
  if ((*(int *)0x53e == 0) && (*(int *)0x542 == 0)) {
    return;
  }
  return;
}



/* 1ad9:060d FUN_1ad9_060d */

ulong __cdecl16near FUN_1ad9_060d(void)

{
  uint in_AX;
  
  return CONCAT22(in_AX >> 4,in_AX) & 0xffff000f;
}



/* 1ad9:062a FUN_1ad9_062a */

void __stdcall16far FUN_1ad9_062a(byte *param_1,byte *param_2)

{
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  byte *pbVar4;
  
  pbVar4 = (byte *)param_2;
  pbVar3 = (byte *)param_1;
  bVar1 = *param_1;
  *param_2 = bVar1;
  uVar2 = (uint)bVar1;
  while( true ) {
    pbVar4 = pbVar4 + 1;
    pbVar3 = pbVar3 + 1;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    *pbVar4 = *pbVar3;
  }
  return;
}



/* 1ad9:0644 FUN_1ad9_0644 */

void __stdcall16far FUN_1ad9_0644(byte param_1,byte *param_2,byte *param_3)

{
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  byte *pbVar4;
  
  pbVar3 = (byte *)param_3;
  pbVar4 = (byte *)param_2;
  bVar1 = *param_3;
  if (param_1 < *param_3) {
    bVar1 = param_1;
  }
  *param_2 = bVar1;
  uVar2 = (uint)bVar1;
  while( true ) {
    pbVar4 = pbVar4 + 1;
    pbVar3 = pbVar3 + 1;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    *pbVar4 = *pbVar3;
  }
  return;
}



/* 1ad9:0676 FUN_1ad9_0676 */

void __stdcall16far FUN_1ad9_0676(uint param_1,uint param_2,byte *param_3,byte *param_4)

{
  byte *pbVar1;
  uint uVar2;
  byte *pbVar3;
  byte *pbVar4;
  
  pbVar4 = (byte *)param_4;
  if ((int)param_2 < 1) {
    param_2 = 1;
  }
  pbVar3 = (byte *)param_3 + param_2;
  if (*param_3 < param_2) {
    uVar2 = 0;
  }
  else {
    uVar2 = (*param_3 - param_2) + 1;
    if ((int)param_1 < 0) {
      param_1 = 0;
    }
    if (param_1 < uVar2) {
      uVar2 = param_1;
    }
  }
  *param_4 = (byte)uVar2;
  for (; pbVar4 = pbVar4 + 1, uVar2 != 0; uVar2 = uVar2 - 1) {
    pbVar1 = pbVar3;
    pbVar3 = pbVar3 + 1;
    *pbVar4 = *pbVar1;
  }
  return;
}



/* 1ad9:06b7 FUN_1ad9_06b7 */

void __stdcall16far FUN_1ad9_06b7(byte *param_1,byte *param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  uint uVar4;
  byte *pbVar5;
  byte *pbVar6;
  
  pbVar5 = (byte *)param_1;
  bVar2 = *param_2;
  bVar3 = *param_1;
  bVar1 = *param_2;
  *param_2 = *param_2 + bVar3;
  if (CARRY1(bVar1,bVar3)) {
    *param_2 = 0xff;
    bVar3 = ~bVar2;
  }
  pbVar6 = (byte *)param_2 + bVar2;
  uVar4 = (uint)bVar3;
  while( true ) {
    pbVar6 = pbVar6 + 1;
    pbVar5 = pbVar5 + 1;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    *pbVar6 = *pbVar5;
  }
  return;
}



/* 1ad9:072f FUN_1ad9_072f */

void __stdcall16far FUN_1ad9_072f(byte *param_1,byte *param_2)

{
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  byte *pbVar4;
  
  pbVar3 = (byte *)param_2;
  pbVar4 = (byte *)param_1;
  bVar1 = *param_2;
  if (*param_1 < *param_2) {
    bVar1 = *param_1;
  }
  if (bVar1 != 0) {
    uVar2 = (uint)bVar1;
    do {
      pbVar4 = pbVar4 + 1;
      pbVar3 = pbVar3 + 1;
      if (uVar2 == 0) {
        return;
      }
      uVar2 = uVar2 - 1;
    } while (*pbVar3 == *pbVar4);
  }
  return;
}



/* 1ad9:075a FUN_1ad9_075a */

void __stdcall16far FUN_1ad9_075a(undefined1 param_1,undefined1 *param_2)

{
  *param_2 = 1;
  ((undefined1 *)param_2)[1] = param_1;
  return;
}



/* 1ad9:076c FUN_1ad9_076c */

void __stdcall16far FUN_1ad9_076c(int param_1,undefined1 *param_2,undefined1 *param_3)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  
  puVar3 = (undefined1 *)param_3;
  puVar2 = (undefined1 *)param_2;
  *param_3 = (char)param_1;
  for (; puVar3 = puVar3 + 1, param_1 != 0; param_1 = param_1 + -1) {
    puVar1 = puVar2;
    puVar2 = puVar2 + 1;
    *puVar3 = *puVar1;
  }
  return;
}



/* 1ad9:0787 FUN_1ad9_0787 */

void __stdcall16far
FUN_1ad9_0787(int param_1,undefined2 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 unaff_SS;
  undefined1 *puVar3;
  undefined1 *puVar4;
  undefined2 uVar5;
  undefined1 local_202 [256];
  undefined1 local_102 [256];
  
  puVar4 = local_102;
  uVar2 = (undefined2)((ulong)param_3 >> 0x10);
  uVar1 = (undefined2)param_3;
  uVar5 = unaff_SS;
  FUN_1ad9_0676(param_1 + -1,1,uVar1,uVar2);
  FUN_1ad9_06b7((int)param_4,(int)((ulong)param_4 >> 0x10));
  puVar3 = local_202;
  FUN_1ad9_0676(0xff,param_1,uVar1,uVar2);
  FUN_1ad9_06b7(puVar3,unaff_SS);
  FUN_1ad9_0644(param_2,uVar1,uVar2,puVar4,uVar5);
  return;
}



/* 1ad9:07db FUN_1ad9_07db */

void __stdcall16far FUN_1ad9_07db(int param_1,int param_2,undefined4 param_3)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 unaff_SS;
  undefined1 *puVar3;
  undefined1 *puVar4;
  undefined2 uVar5;
  undefined1 local_202 [256];
  undefined1 local_102 [256];
  
  if (0 < param_1) {
    puVar4 = local_102;
    uVar2 = (undefined2)((ulong)param_3 >> 0x10);
    uVar1 = (undefined2)param_3;
    uVar5 = unaff_SS;
    FUN_1ad9_0676(param_2 + -1,1,uVar1,uVar2);
    puVar3 = local_202;
    FUN_1ad9_0676(0xff,param_2 + param_1,uVar1,uVar2);
    FUN_1ad9_06b7(puVar3,unaff_SS);
    FUN_1ad9_0644(0xff,uVar1,uVar2,puVar4,uVar5);
  }
  return;
}



/* 1ad9:08df FUN_1ad9_08df */

char __stdcall16far FUN_1ad9_08df(undefined2 param_1,undefined2 param_2,byte param_3)

{
  return '\x01' << (param_3 & 7);
}



/* 1ad9:098b FUN_1ad9_098b */

undefined4 FUN_1ad9_098b(void)

{
  uint uVar1;
  byte bVar2;
  uint in_AX;
  uint uVar3;
  uint uVar4;
  char cVar5;
  uint in_CX;
  uint uVar6;
  uint in_DX;
  uint uVar7;
  uint in_BX;
  uint uVar8;
  uint uVar9;
  uint unaff_SI;
  uint unaff_DI;
  uint uVar10;
  uint uVar11;
  bool bVar12;
  bool bVar13;
  undefined4 uVar14;
  
  uVar10 = unaff_DI ^ 0x8000;
  if ((byte)in_CX != 0) {
    if ((byte)in_AX == 0) {
LAB_1ad9_0a0f:
      return CONCAT22(uVar10,in_CX);
    }
    uVar4 = in_AX;
    uVar7 = in_DX;
    uVar8 = in_BX;
    if ((byte)in_CX < (byte)in_AX) {
      uVar4 = in_CX;
      in_CX = in_AX;
      uVar7 = uVar10;
      uVar8 = unaff_SI;
      unaff_SI = in_BX;
      uVar10 = in_DX;
    }
    bVar2 = -((char)uVar4 - (char)in_CX);
    if (0x27 < bVar2) goto LAB_1ad9_0a0f;
    uVar3 = CONCAT11((char)(uVar7 >> 8),(char)in_CX) & 0x80ff;
    uVar4 = uVar4 & 0xff00;
    uVar7 = uVar7 | 0x8000;
    uVar11 = uVar10 | 0x8000;
    for (; 7 < bVar2; bVar2 = bVar2 - 8) {
      uVar4 = CONCAT11((char)uVar8,(char)(uVar4 >> 8));
      uVar8 = CONCAT11((char)uVar7,(char)(uVar8 >> 8));
      uVar7 = uVar7 >> 8;
    }
    uVar6 = CONCAT11((char)(in_CX >> 8),bVar2);
    while (bVar2 != 0) {
      uVar1 = uVar7 & 1;
      uVar7 = uVar7 >> 1;
      uVar9 = uVar8 & 1;
      uVar8 = uVar8 >> 1 | (uint)(uVar1 != 0) << 0xf;
      uVar4 = uVar4 >> 1 | (uint)(uVar9 != 0) << 0xf;
      bVar2 = (char)uVar6 - 1;
      uVar6 = CONCAT11((char)(uVar6 >> 8),bVar2);
    }
    if ((int)(uVar3 ^ uVar10) < 0) {
      in_AX = uVar4 - uVar6;
      uVar9 = (uVar8 - unaff_SI) - (uint)(uVar4 < uVar6);
      uVar10 = (uint)(uVar8 < unaff_SI || uVar8 - unaff_SI < (uint)(uVar4 < uVar6));
      in_DX = (uVar7 - uVar11) - uVar10;
      if (uVar7 < uVar11 || uVar7 - uVar11 < uVar10) {
        uVar10 = ~uVar9;
        bVar12 = in_AX == 0;
        in_AX = -in_AX;
        uVar9 = uVar10 + bVar12;
        in_DX = ~in_DX + (uint)CARRY2(uVar10,(uint)bVar12);
        uVar3 = uVar3 ^ 0x8000;
      }
      if ((in_DX == 0 && uVar9 == 0) && in_AX == 0) goto LAB_1ad9_0a0e;
      while (-1 < (int)in_DX) {
        bVar12 = (int)in_AX < 0;
        in_AX = in_AX << 1;
        bVar13 = (int)uVar9 < 0;
        uVar9 = uVar9 << 1 | (uint)bVar12;
        in_DX = in_DX << 1 | (uint)bVar13;
        cVar5 = (char)uVar3 + -1;
        uVar3 = CONCAT11((char)(uVar3 >> 8),cVar5);
        if (cVar5 == '\0') {
          uVar14 = FUN_1ad9_0b50();
          return uVar14;
        }
      }
    }
    else {
      in_AX = uVar4 + uVar6;
      uVar9 = uVar8 + unaff_SI + (uint)CARRY2(uVar4,uVar6);
      uVar10 = (uint)(CARRY2(uVar8,unaff_SI) || CARRY2(uVar8 + unaff_SI,(uint)CARRY2(uVar4,uVar6)));
      uVar4 = uVar7 + uVar11;
      in_DX = uVar4 + uVar10;
      if (CARRY2(uVar7,uVar11) || CARRY2(uVar4,uVar10)) {
        uVar8 = in_DX & 1;
        in_DX = in_DX >> 1 | (uint)(CARRY2(uVar7,uVar11) || CARRY2(uVar4,uVar10)) << 0xf;
        uVar10 = uVar9 & 1;
        uVar9 = uVar9 >> 1 | (uint)(uVar8 != 0) << 0xf;
        in_AX = in_AX >> 1 | (uint)(uVar10 != 0) << 0xf;
        cVar5 = (char)uVar3 + '\x01';
        uVar3 = CONCAT11((char)(uVar3 >> 8),cVar5);
        if (cVar5 == '\0') goto LAB_1ad9_0a1c;
      }
    }
    bVar12 = 0xff7f < in_AX;
    in_AX = in_AX + 0x80;
    uVar10 = (uint)CARRY2(uVar9,(uint)bVar12);
    bVar12 = CARRY2(in_DX,uVar10);
    in_DX = in_DX + uVar10;
    if (bVar12) {
      in_DX = in_DX >> 1 | 0x8000;
      cVar5 = (char)uVar3 + '\x01';
      uVar3 = CONCAT11((char)(uVar3 >> 8),cVar5);
      if (cVar5 == '\0') {
LAB_1ad9_0a1c:
        return CONCAT22(in_DX,in_AX);
      }
    }
    in_AX = CONCAT11((char)(in_AX >> 8),(char)uVar3);
    in_DX = CONCAT11((byte)((in_DX & 0x7fff) >> 8) | (byte)(uVar3 >> 8),(char)(in_DX & 0x7fff));
  }
LAB_1ad9_0a0e:
  return CONCAT22(in_DX,in_AX);
}



/* 1ad9:098f FUN_1ad9_098f */

undefined4 __cdecl16near FUN_1ad9_098f(void)

{
  uint uVar1;
  byte bVar2;
  uint in_AX;
  uint uVar3;
  uint uVar4;
  char cVar5;
  uint in_CX;
  uint uVar6;
  uint in_DX;
  uint uVar7;
  uint in_BX;
  uint uVar8;
  uint uVar9;
  uint unaff_SI;
  uint unaff_DI;
  uint uVar10;
  bool bVar11;
  bool bVar12;
  undefined4 uVar13;
  
  if ((byte)in_CX != 0) {
    if ((byte)in_AX == 0) {
LAB_1ad9_0a0f:
      return CONCAT22(unaff_DI,in_CX);
    }
    uVar4 = in_AX;
    uVar7 = in_DX;
    uVar8 = in_BX;
    if ((byte)in_CX < (byte)in_AX) {
      uVar4 = in_CX;
      in_CX = in_AX;
      uVar7 = unaff_DI;
      uVar8 = unaff_SI;
      unaff_SI = in_BX;
      unaff_DI = in_DX;
    }
    bVar2 = -((char)uVar4 - (char)in_CX);
    if (0x27 < bVar2) goto LAB_1ad9_0a0f;
    uVar3 = CONCAT11((char)(uVar7 >> 8),(char)in_CX) & 0x80ff;
    uVar4 = uVar4 & 0xff00;
    uVar7 = uVar7 | 0x8000;
    uVar10 = unaff_DI | 0x8000;
    for (; 7 < bVar2; bVar2 = bVar2 - 8) {
      uVar4 = CONCAT11((char)uVar8,(char)(uVar4 >> 8));
      uVar8 = CONCAT11((char)uVar7,(char)(uVar8 >> 8));
      uVar7 = uVar7 >> 8;
    }
    uVar6 = CONCAT11((char)(in_CX >> 8),bVar2);
    while (bVar2 != 0) {
      uVar1 = uVar7 & 1;
      uVar7 = uVar7 >> 1;
      uVar9 = uVar8 & 1;
      uVar8 = uVar8 >> 1 | (uint)(uVar1 != 0) << 0xf;
      uVar4 = uVar4 >> 1 | (uint)(uVar9 != 0) << 0xf;
      bVar2 = (char)uVar6 - 1;
      uVar6 = CONCAT11((char)(uVar6 >> 8),bVar2);
    }
    if ((int)(uVar3 ^ unaff_DI) < 0) {
      in_AX = uVar4 - uVar6;
      uVar9 = (uVar8 - unaff_SI) - (uint)(uVar4 < uVar6);
      uVar4 = (uint)(uVar8 < unaff_SI || uVar8 - unaff_SI < (uint)(uVar4 < uVar6));
      in_DX = (uVar7 - uVar10) - uVar4;
      if (uVar7 < uVar10 || uVar7 - uVar10 < uVar4) {
        uVar7 = ~uVar9;
        bVar11 = in_AX == 0;
        in_AX = -in_AX;
        uVar9 = uVar7 + bVar11;
        in_DX = ~in_DX + (uint)CARRY2(uVar7,(uint)bVar11);
        uVar3 = uVar3 ^ 0x8000;
      }
      if ((in_DX == 0 && uVar9 == 0) && in_AX == 0) goto LAB_1ad9_0a0e;
      while (-1 < (int)in_DX) {
        bVar11 = (int)in_AX < 0;
        in_AX = in_AX << 1;
        bVar12 = (int)uVar9 < 0;
        uVar9 = uVar9 << 1 | (uint)bVar11;
        in_DX = in_DX << 1 | (uint)bVar12;
        cVar5 = (char)uVar3 + -1;
        uVar3 = CONCAT11((char)(uVar3 >> 8),cVar5);
        if (cVar5 == '\0') {
          uVar13 = FUN_1ad9_0b50();
          return uVar13;
        }
      }
    }
    else {
      in_AX = uVar4 + uVar6;
      uVar9 = uVar8 + unaff_SI + (uint)CARRY2(uVar4,uVar6);
      uVar4 = (uint)(CARRY2(uVar8,unaff_SI) || CARRY2(uVar8 + unaff_SI,(uint)CARRY2(uVar4,uVar6)));
      uVar8 = uVar7 + uVar10;
      in_DX = uVar8 + uVar4;
      if (CARRY2(uVar7,uVar10) || CARRY2(uVar8,uVar4)) {
        uVar6 = in_DX & 1;
        in_DX = in_DX >> 1 | (uint)(CARRY2(uVar7,uVar10) || CARRY2(uVar8,uVar4)) << 0xf;
        uVar7 = uVar9 & 1;
        uVar9 = uVar9 >> 1 | (uint)(uVar6 != 0) << 0xf;
        in_AX = in_AX >> 1 | (uint)(uVar7 != 0) << 0xf;
        cVar5 = (char)uVar3 + '\x01';
        uVar3 = CONCAT11((char)(uVar3 >> 8),cVar5);
        if (cVar5 == '\0') goto LAB_1ad9_0a1c;
      }
    }
    bVar11 = 0xff7f < in_AX;
    in_AX = in_AX + 0x80;
    uVar7 = (uint)CARRY2(uVar9,(uint)bVar11);
    bVar11 = CARRY2(in_DX,uVar7);
    in_DX = in_DX + uVar7;
    if (bVar11) {
      in_DX = in_DX >> 1 | 0x8000;
      cVar5 = (char)uVar3 + '\x01';
      uVar3 = CONCAT11((char)(uVar3 >> 8),cVar5);
      if (cVar5 == '\0') {
LAB_1ad9_0a1c:
        return CONCAT22(in_DX,in_AX);
      }
    }
    in_AX = CONCAT11((char)(in_AX >> 8),(char)uVar3);
    in_DX = CONCAT11((byte)((in_DX & 0x7fff) >> 8) | (byte)(uVar3 >> 8),(char)(in_DX & 0x7fff));
  }
LAB_1ad9_0a0e:
  return CONCAT22(in_DX,in_AX);
}



/* 1ad9:0a52 FUN_1ad9_0a52 */

undefined4 __cdecl16near FUN_1ad9_0a52(void)

{
  long lVar1;
  long lVar2;
  ulong uVar3;
  long lVar4;
  byte bVar5;
  undefined2 in_AX;
  byte bVar7;
  uint uVar6;
  byte bVar8;
  uint in_CX;
  int iVar9;
  uint in_DX;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint in_BX;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  uint unaff_SI;
  uint unaff_DI;
  uint uVar21;
  uint uVar22;
  uint uVar23;
  bool bVar24;
  undefined4 uVar25;
  
  bVar5 = (byte)in_AX;
  bVar7 = (byte)((uint)in_AX >> 8);
  if ((bVar5 == 0) || (bVar8 = (byte)in_CX, bVar8 == 0)) {
    uVar25 = FUN_1ad9_0b50();
    return uVar25;
  }
  iVar9 = CONCAT11((((byte)(in_DX >> 8) ^ (byte)(unaff_DI >> 8)) & 0x80) + CARRY1(bVar5,bVar8),
                   bVar5 + bVar8);
  bVar5 = (byte)(in_CX >> 8);
  uVar20 = in_DX | 0x8000;
  uVar21 = unaff_DI | 0x8000;
  if (((bVar7 == 0) &&
      (uVar6 = in_CX & 0xff00, uVar14 = uVar20, uVar10 = unaff_SI, uVar22 = uVar21, in_BX == 0)) ||
     ((bVar5 == 0 &&
      (uVar6 = (uint)bVar7 << 8, uVar14 = uVar21, uVar10 = in_BX, uVar22 = uVar20, unaff_SI == 0))))
  {
    uVar3 = (ulong)uVar14 * (ulong)uVar10 + (ulong)((uVar14 >> 8) * (uVar6 >> 8));
    uVar15 = (uint)uVar3;
    lVar1 = (ulong)uVar14 * (ulong)uVar22 + (uVar3 >> 0x10);
  }
  else {
    lVar1 = (ulong)bVar7 * 0x100 * (ulong)unaff_SI;
    lVar4 = lVar1 + (ulong)((uint)bVar7 * (uint)bVar5);
    uVar22 = (uint)((ulong)lVar4 >> 0x10);
    lVar2 = (ulong)in_BX * (ulong)bVar5 * 0x100;
    uVar10 = (uint)((ulong)lVar2 >> 0x10);
    uVar6 = (uint)CARRY2((uint)lVar4,(uint)lVar2);
    uVar14 = uVar22 + uVar10;
    uVar15 = uVar14 + uVar6;
    uVar16 = (uint)CARRY2((uint)((ulong)lVar1 >> 0x10),
                          (uint)CARRY2((uint)bVar7 * (uint)bVar5,(uint)lVar1)) +
             (uint)(CARRY2(uVar22,uVar10) || CARRY2(uVar14,uVar6));
    lVar1 = (ulong)bVar7 * 0x100 * (ulong)uVar21;
    uVar11 = (uint)((ulong)lVar1 >> 0x10);
    uVar6 = (uint)lVar1;
    uVar23 = uVar15 + uVar6;
    uVar6 = (uint)CARRY2(uVar15,uVar6);
    uVar22 = uVar16 + uVar11;
    uVar17 = uVar22 + uVar6;
    uVar12 = (uint)((ulong)in_BX * (ulong)unaff_SI >> 0x10);
    uVar10 = (uint)((ulong)in_BX * (ulong)unaff_SI);
    uVar14 = (uint)CARRY2(uVar23,uVar10);
    uVar15 = uVar17 + uVar12;
    uVar18 = uVar15 + uVar14;
    lVar1 = (ulong)uVar20 * (ulong)bVar5 * 0x100;
    uVar13 = (uint)((ulong)lVar1 >> 0x10);
    uVar10 = (uint)CARRY2(uVar23 + uVar10,(uint)lVar1);
    uVar23 = uVar18 + uVar13;
    uVar19 = uVar23 + uVar10;
    uVar12 = (uint)(CARRY2(uVar16,uVar11) || CARRY2(uVar22,uVar6)) +
             (uint)(CARRY2(uVar17,uVar12) || CARRY2(uVar15,uVar14)) +
             (uint)(CARRY2(uVar18,uVar13) || CARRY2(uVar23,uVar10));
    uVar23 = (uint)((ulong)in_BX * (ulong)uVar21 >> 0x10);
    uVar6 = (uint)((ulong)in_BX * (ulong)uVar21);
    uVar22 = uVar19 + uVar6;
    uVar6 = (uint)CARRY2(uVar19,uVar6);
    uVar10 = uVar12 + uVar23;
    uVar13 = uVar10 + uVar6;
    uVar11 = (uint)((ulong)uVar20 * (ulong)unaff_SI >> 0x10);
    uVar14 = (uint)((ulong)uVar20 * (ulong)unaff_SI);
    uVar15 = uVar22 + uVar14;
    uVar14 = (uint)CARRY2(uVar22,uVar14);
    uVar22 = uVar13 + uVar11;
    lVar1 = (ulong)uVar20 * (ulong)uVar21 +
            CONCAT22((uint)(CARRY2(uVar12,uVar23) || CARRY2(uVar10,uVar6)) +
                     (uint)(CARRY2(uVar13,uVar11) || CARRY2(uVar22,uVar14)),uVar22 + uVar14);
  }
  if (-1 < lVar1) {
    bVar24 = (int)uVar15 < 0;
    uVar15 = uVar15 << 1;
    lVar1 = CONCAT22((int)((ulong)lVar1 >> 0x10) << 1 | (uint)((int)lVar1 < 0),
                     (int)lVar1 << 1 | (uint)bVar24);
    iVar9 = iVar9 + -1;
  }
  uVar6 = (uint)((ulong)lVar1 >> 0x10);
  uVar21 = iVar9 + 0x7f7f;
  uVar20 = (uint)CARRY2((uint)lVar1,(uint)(0xff7f < uVar15));
  uVar14 = uVar6 + uVar20;
  if (CARRY2(uVar6,uVar20)) {
    uVar14 = uVar14 >> 1 | 0x8000;
    uVar21 = iVar9 + 0x7f80;
  }
  if ((uVar21 & 0x4000) != 0) {
    return 0;
  }
  return CONCAT22(CONCAT11((byte)(uVar14 >> 8) ^ (byte)(uVar21 + 1 >> 8),(char)uVar14),
                  CONCAT11((char)(uVar15 + 0x80 >> 8),(char)(uVar21 + 1)));
}



/* 1ad9:0b50 FUN_1ad9_0b50 */

void __cdecl16near FUN_1ad9_0b50(void)

{
  return;
}



/* 1ad9:0b57 FUN_1ad9_0b57 */

undefined4 __cdecl16near FUN_1ad9_0b57(void)

{
  byte bVar1;
  undefined1 uVar2;
  char cVar3;
  undefined2 in_AX;
  int iVar4;
  byte bVar5;
  undefined2 in_CX;
  byte bVar7;
  uint uVar6;
  uint in_DX;
  char cVar9;
  uint uVar8;
  uint in_BX;
  uint uVar10;
  uint unaff_BP;
  uint uVar11;
  uint unaff_SI;
  uint unaff_DI;
  uint uVar12;
  bool bVar13;
  bool bVar14;
  int in_stack_00000000;
  
  bVar1 = (byte)in_AX;
  if (bVar1 == 0) {
    return 0;
  }
  uVar12 = unaff_DI | 0x8000;
  uVar11 = in_DX | 0x8000;
  cVar9 = (((byte)(in_DX >> 8) ^ (byte)(unaff_DI >> 8)) & 0x80) - (bVar1 < (byte)in_CX);
  iVar4 = CONCAT11((char)((uint)in_AX >> 8),2);
  uVar8 = 1;
  do {
    bVar13 = uVar11 < uVar12;
    bVar7 = (byte)((uint)in_CX >> 8);
    bVar5 = (byte)((uint)iVar4 >> 8);
    if ((uVar11 == uVar12) && (bVar13 = in_BX < unaff_SI, in_BX == unaff_SI)) {
      bVar13 = bVar5 < bVar7;
    }
    if (!bVar13) {
      iVar4 = CONCAT11(bVar5 - bVar7,(char)iVar4);
      bVar13 = in_BX < unaff_SI;
      uVar10 = in_BX - unaff_SI;
      in_BX = uVar10 - (bVar5 < bVar7);
      uVar10 = (uint)(bVar13 || uVar10 < (bVar5 < bVar7));
      bVar13 = uVar11 < uVar12 || uVar11 - uVar12 < uVar10;
      uVar11 = (uVar11 - uVar12) - uVar10;
    }
    while( true ) {
      bVar14 = (int)uVar8 < 0;
      uVar8 = uVar8 << 1 | (uint)bVar13;
      if (bVar14) {
        cVar3 = (char)iVar4 + -1;
        iVar4 = CONCAT11((char)((uint)iVar4 >> 8),cVar3);
        if (cVar3 < '\0') {
          uVar11 = ~(uVar8 << 6);
          uVar10 = ~CONCAT11(cVar9,bVar1 - (byte)in_CX);
          uVar12 = unaff_BP ^ 0xffff;
          if (-1 < (int)uVar12) {
            uVar11 = uVar11 << 1;
            uVar10 = uVar10 << 1 | (uint)(-1 < (int)(uVar8 << 6));
            uVar12 = uVar12 << 1 | (uint)(-1 < cVar9);
            in_stack_00000000 = in_stack_00000000 + -1;
          }
          uVar6 = in_stack_00000000 + 0x8080;
          uVar8 = (uint)CARRY2(uVar10,(uint)(0xff7f < uVar11));
          uVar10 = uVar12 + uVar8;
          if (CARRY2(uVar12,uVar8)) {
            uVar10 = uVar10 >> 1 | 0x8000;
            uVar6 = in_stack_00000000 + 0x8081;
          }
          if ((uVar6 & 0x4000) != 0) {
            return 0;
          }
          return CONCAT22(CONCAT11((byte)(uVar10 >> 8) ^ (byte)(uVar6 + 1 >> 8),(char)uVar10),
                          CONCAT11((char)(uVar11 + 0x80 >> 8),(char)(uVar6 + 1)));
        }
        uVar8 = 1;
        if (cVar3 == '\0') {
          uVar8 = 0x40;
        }
      }
      bVar13 = iVar4 < 0;
      uVar2 = (undefined1)iVar4;
      bVar5 = (char)((uint)iVar4 >> 8) * '\x02';
      iVar4 = CONCAT11(bVar5,uVar2);
      bVar14 = (int)in_BX < 0;
      in_BX = in_BX << 1 | (uint)bVar13;
      bVar13 = -1 < (int)uVar11;
      uVar11 = uVar11 << 1 | (uint)bVar14;
      if (bVar13) break;
      iVar4 = CONCAT11(bVar5 - bVar7,uVar2);
      bVar13 = in_BX < unaff_SI;
      uVar10 = in_BX - unaff_SI;
      in_BX = uVar10 - (bVar5 < bVar7);
      uVar11 = (uVar11 - uVar12) - (uint)(bVar13 || uVar10 < (bVar5 < bVar7));
      bVar13 = false;
    }
  } while( true );
}



/* 1ad9:0bce FUN_1ad9_0bce */

void __cdecl16near FUN_1ad9_0bce(void)

{
  uint in_DX;
  uint unaff_DI;
  bool bVar1;
  
  if ((int)(in_DX ^ unaff_DI) < 0) {
    return;
  }
  bVar1 = (in_DX & 0x8000) == 0;
  if ((!bVar1) && (FUN_1ad9_0be5(), !bVar1)) {
    return;
  }
  return;
}



/* 1ad9:0be5 FUN_1ad9_0be5 */

void __cdecl16near FUN_1ad9_0be5(void)

{
  return;
}



/* 1ad9:0bf8 FUN_1ad9_0bf8 */

void __cdecl16near FUN_1ad9_0bf8(void)

{
  uint in_AX;
  uint uVar1;
  uint in_DX;
  
  if (in_AX != 0 || in_DX != 0) {
    if ((int)in_DX < 0) {
      uVar1 = ~in_AX;
      in_AX = uVar1 + 1;
      in_DX = ~in_DX + (uint)(0xfffe < uVar1);
    }
    uVar1 = in_AX;
    if ((in_DX == 0) && (uVar1 = 0, in_DX = in_AX, (char)(in_AX >> 8) == '\0')) {
      in_DX = in_AX << 8;
    }
    while (-1 < (int)in_DX) {
      in_DX = in_DX * 2 + (uint)CARRY2(uVar1,uVar1);
      uVar1 = uVar1 * 2;
    }
  }
  return;
}



/* 1ad9:0c37 FUN_1ad9_0c37 */

undefined4 __cdecl16near FUN_1ad9_0c37(void)

{
  uint uVar1;
  char cVar2;
  byte in_AL;
  uint uVar3;
  byte bVar4;
  char in_CH;
  uint in_DX;
  uint uVar5;
  uint in_BX;
  bool bVar6;
  
  cVar2 = -in_AL;
  uVar5 = in_DX;
  if (in_AL < 0xa0) {
    if (0x1f < (byte)(cVar2 + 0x9fU)) {
      return 0;
    }
    bVar4 = cVar2 + 0xa0;
    uVar5 = in_DX | 0x8000;
    if (0x10 < bVar4) {
      uVar5 = 0;
      bVar4 = cVar2 + 0x90;
      in_BX = in_DX | 0x8000;
    }
    if (8 < bVar4) {
      in_BX = CONCAT11((char)uVar5,(char)(in_BX >> 8));
      uVar5 = uVar5 >> 8;
      bVar4 = bVar4 - 8;
    }
    do {
      uVar1 = uVar5 & 1;
      uVar5 = uVar5 >> 1;
      uVar3 = in_BX & 1;
      in_BX = in_BX >> 1 | (uint)(uVar1 != 0) << 0xf;
      bVar4 = bVar4 - 1;
    } while (bVar4 != 0);
    if ((uVar3 != 0) && (in_CH != '\0')) {
      bVar6 = 0xfffe < in_BX;
      in_BX = in_BX + 1;
      uVar5 = uVar5 + bVar6;
      if ((int)uVar5 < 0) goto LAB_1ad9_0c8c;
    }
    if ((int)in_DX < 0) {
      uVar3 = ~in_BX;
      in_BX = uVar3 + 1;
      uVar5 = ~uVar5 + (uint)(0xfffe < uVar3);
    }
    return CONCAT22(uVar5,in_BX);
  }
LAB_1ad9_0c8c:
  return CONCAT22(uVar5,in_BX);
}



/* 1ad9:0ca5 FUN_1ad9_0ca5 */

void __cdecl16far FUN_1ad9_0ca5(void)

{
  undefined1 in_CF;
  
  FUN_1ad9_0a52();
  if (!(bool)in_CF) {
    return;
  }
  FUN_1ad9_00d1();
  return;
}



/* 1ad9:0cab FUN_1ad9_0cab */

void __cdecl16far FUN_1ad9_0cab(void)

{
  char in_CL;
  bool bVar1;
  
  bVar1 = false;
  if (in_CL == '\0') {
    FUN_1ad9_00d1();
    return;
  }
  FUN_1ad9_0b57();
  if (!bVar1) {
    return;
  }
  FUN_1ad9_00d1();
  return;
}



/* 1ad9:0cb9 FUN_1ad9_0cb9 */

void __cdecl16far FUN_1ad9_0cb9(void)

{
  FUN_1ad9_0bf8();
  return;
}



/* 1ad9:0cc5 FUN_1ad9_0cc5 */

void __cdecl16far FUN_1ad9_0cc5(void)

{
  undefined1 in_CF;
  
  FUN_1ad9_0c37();
  if (!(bool)in_CF) {
    return;
  }
  FUN_1ad9_00d1();
  return;
}



/* 1ad9:0cdf FUN_1ad9_0cdf */

void __cdecl16near FUN_1ad9_0cdf(void)

{
  FUN_1ad9_098f();
  return;
}



/* 1ad9:0ce9 FUN_1ad9_0ce9 */

void __cdecl16near FUN_1ad9_0ce9(void)

{
  FUN_1ad9_098b();
  return;
}



/* 1ad9:0cf3 FUN_1ad9_0cf3 */

void __cdecl16near FUN_1ad9_0cf3(void)

{
  FUN_1ad9_0a52();
  return;
}



/* 1ad9:0cfd FUN_1ad9_0cfd */

void __cdecl16near FUN_1ad9_0cfd(void)

{
  FUN_1ad9_0b57();
  return;
}



/* 1ad9:0d07 FUN_1ad9_0d07 */

uint __cdecl16far FUN_1ad9_0d07(void)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  uint in_AX;
  uint uVar4;
  byte bVar5;
  uint uVar6;
  undefined1 uVar8;
  uint uVar7;
  
  bVar3 = (byte)in_AX;
  if (bVar3 < 0xa8) {
    uVar4 = in_AX & 0xff;
    bVar5 = bVar3 + 0x80;
    uVar1 = 0;
    uVar7 = 0;
    if (bVar3 < 0x80 || bVar5 == 0) {
      return 0;
    }
    while( true ) {
      uVar6 = uVar1;
      uVar8 = (undefined1)(uVar7 >> 8);
      if (bVar5 < 0x10) break;
      uVar4 = CONCAT11(uVar8,(char)uVar4);
      bVar5 = bVar5 - 0x10;
      uVar1 = 0xffff;
      uVar7 = uVar6;
    }
    if (7 < bVar5) {
      uVar4 = CONCAT11((char)uVar7,(char)uVar4);
      uVar7 = CONCAT11((char)uVar6,uVar8);
      uVar6 = CONCAT11(0xff,(char)(uVar6 >> 8));
      bVar5 = bVar5 - 8;
    }
    while( true ) {
      bVar3 = (byte)(uVar4 >> 8);
      if (bVar5 == 0) break;
      uVar1 = uVar6 & 1;
      uVar6 = uVar6 >> 1 | 0x8000;
      uVar2 = uVar7 & 1;
      uVar7 = uVar7 >> 1 | (uint)(uVar1 != 0) << 0xf;
      uVar4 = CONCAT11(bVar3 >> 1 | (uVar2 != 0) << 7,(char)uVar4);
      bVar5 = bVar5 - 1;
    }
    in_AX = CONCAT11(bVar3 & (byte)(in_AX >> 8),(char)uVar4);
  }
  return in_AX;
}



/* 1ad9:0d58 FUN_1ad9_0d58 */

void __cdecl16far FUN_1ad9_0d58(void)

{
  FUN_1ad9_0d07();
  FUN_1ad9_098b();
  return;
}



/* 1ad9:0dc9 FUN_1ad9_0dc9 */

void FUN_1ad9_0dc9(void)

{
  byte bVar1;
  undefined2 uVar2;
  uint extraout_DX;
  uint uVar3;
  uint extraout_DX_00;
  bool bVar4;
  undefined1 uVar5;
  
  bVar1 = FUN_1ad9_098f();
  uVar3 = extraout_DX;
  if (bVar1 != 0) {
    uVar3 = extraout_DX ^ 0x8000;
  }
  if (0x6b < bVar1) {
    uVar2 = 0x2183;
    bVar4 = false;
    FUN_1ad9_0bce();
    if (!bVar4) {
      FUN_1ad9_0cfd();
      FUN_1ad9_0d58(uVar2,0xdaa2,0x490f);
      FUN_1ad9_0cf3();
      uVar3 = extraout_DX_00;
    }
    uVar5 = 0;
    if ((uVar3 & 0x8000) != 0) {
      FUN_1ad9_0cdf();
    }
    FUN_1ad9_0bce();
    if (!(bool)uVar5) {
      FUN_1ad9_0ce9();
    }
    bVar1 = FUN_1ad9_0bce();
    if (!(bool)uVar5) {
      bVar1 = FUN_1ad9_098f();
    }
    if (0x6b < bVar1) {
      FUN_1ad9_10e8();
    }
  }
  return;
}



/* 1ad9:0ddc FUN_1ad9_0ddc */

void __cdecl16far FUN_1ad9_0ddc(void)

{
  byte in_AL;
  byte bVar1;
  undefined2 uVar2;
  uint in_DX;
  uint extraout_DX;
  bool bVar3;
  undefined1 uVar4;
  
  if (0x6b < in_AL) {
    uVar2 = 0x2183;
    bVar3 = false;
    FUN_1ad9_0bce();
    if (!bVar3) {
      FUN_1ad9_0cfd();
      FUN_1ad9_0d58(uVar2,0xdaa2,0x490f);
      FUN_1ad9_0cf3();
      in_DX = extraout_DX;
    }
    uVar4 = 0;
    if ((in_DX & 0x8000) != 0) {
      FUN_1ad9_0cdf();
    }
    FUN_1ad9_0bce();
    if (!(bool)uVar4) {
      FUN_1ad9_0ce9();
    }
    bVar1 = FUN_1ad9_0bce();
    if (!(bool)uVar4) {
      bVar1 = FUN_1ad9_098f();
    }
    if (0x6b < bVar1) {
      FUN_1ad9_10e8();
    }
  }
  return;
}



/* 1ad9:10e8 FUN_1ad9_10e8 */

void FUN_1ad9_10e8(void)

{
  FUN_1ad9_0a52();
  FUN_1ad9_1101();
  FUN_1ad9_0a52();
  return;
}



/* 1ad9:1101 FUN_1ad9_1101 */

void __cdecl16near FUN_1ad9_1101(void)

{
  int in_CX;
  int unaff_DI;
  undefined2 uStack_a;
  
  uStack_a = in_CX;
  while( true ) {
    FUN_1ad9_0a52();
    unaff_DI = unaff_DI + 6;
    uStack_a = uStack_a + -1;
    if (uStack_a == 0) break;
    FUN_1ad9_098f(unaff_DI);
  }
  FUN_1ad9_098f();
  return;
}



/* 1ad9:1150 pascal_random_bound */

uint __stdcall16far pascal_random_bound(uint param_1)

{
  uint uVar1;
  uint extraout_DX;
  
  pascal_random_next();
  uVar1 = 0;
  if (param_1 != 0) {
    uVar1 = extraout_DX % param_1;
  }
  return uVar1;
}



/* 1ad9:119f pascal_random_next */

void __cdecl16near pascal_random_next(void)

{
  int iVar1;
  long lVar2;
  uint uVar3;
  char cVar4;
  int iVar5;
  undefined2 unaff_DS;
  
  iVar1 = *(int *)0x55a;
  lVar2 = (ulong)*(uint *)0x558 * (ulong)uRam000111d5;
  uVar3 = (uint)lVar2;
  iVar5 = *(uint *)0x558 << 3;
  cVar4 = (char)iVar5;
  iVar5 = (int)((ulong)lVar2 >> 0x10) + CONCAT11((char)((uint)iVar5 >> 8) + cVar4,cVar4) + iVar1 * 5
  ;
  *(int *)0x558 = uVar3 + 1;
  *(int *)0x55a =
       CONCAT11((char)((uint)iVar5 >> 8) + (char)iVar1 * '\x04' + (char)(iVar1 << 7),(char)iVar5) +
       (uint)(0xfffe < uVar3);
  return;
}



/* 1ad9:11d7 FUN_1ad9_11d7 */

void __cdecl16far FUN_1ad9_11d7(void)

{
  code *pcVar1;
  undefined2 in_CX;
  undefined2 extraout_DX;
  undefined2 unaff_DS;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  *(undefined2 *)0x558 = in_CX;
  *(undefined2 *)0x55a = extraout_DX;
  return;
}



/* 1ad9:11e4 FUN_1ad9_11e4 */

void __cdecl16near FUN_1ad9_11e4(void)

{
  char *pcVar1;
  uint uVar2;
  char cVar3;
  uint in_AX;
  char cVar4;
  uint in_DX;
  uint uVar5;
  uint *puVar6;
  char *unaff_DI;
  undefined2 unaff_ES;
  bool bVar7;
  
  if ((int)in_DX < 0) {
    uVar5 = ~in_AX;
    in_AX = uVar5 + 1;
    in_DX = ~in_DX + (uint)(0xfffe < uVar5);
    pcVar1 = unaff_DI;
    unaff_DI = unaff_DI + 1;
    *pcVar1 = '-';
  }
  puVar6 = (uint *)0x1236;
  cVar4 = '\t';
  do {
    if ((puVar6[1] <= in_DX) && ((puVar6[1] < in_DX || (*puVar6 <= in_AX)))) break;
    puVar6 = puVar6 + 2;
    cVar4 = cVar4 + -1;
  } while (cVar4 != '\0');
  cVar4 = cVar4 + '\x01';
  do {
    cVar3 = '/';
    do {
      cVar3 = cVar3 + '\x01';
      bVar7 = in_AX < *puVar6;
      in_AX = in_AX - *puVar6;
      uVar5 = (uint)bVar7;
      bVar7 = puVar6[1] <= in_DX;
      uVar2 = in_DX - puVar6[1];
      in_DX = uVar2 - uVar5;
    } while (bVar7 && uVar5 <= uVar2);
    bVar7 = CARRY2(in_AX,*puVar6);
    in_AX = in_AX + *puVar6;
    in_DX = in_DX + puVar6[1] + (uint)bVar7;
    puVar6 = puVar6 + 2;
    pcVar1 = unaff_DI;
    unaff_DI = unaff_DI + 1;
    *pcVar1 = cVar3;
    cVar4 = cVar4 + -1;
  } while (cVar4 != '\0');
  return;
}



/* 1ad9:125e FUN_1ad9_125e */

undefined4 __cdecl16near FUN_1ad9_125e(void)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int in_CX;
  uint uVar7;
  uint uVar8;
  byte bVar9;
  byte bVar10;
  char cVar11;
  byte *unaff_DI;
  undefined2 unaff_ES;
  bool bVar12;
  bool bVar13;
  
  uVar2 = 0;
  uVar7 = 0;
  bVar1 = false;
  if (in_CX == 0) goto LAB_1ad9_12bf;
  if (*unaff_DI == 0x2b) {
LAB_1ad9_1273:
    unaff_DI = unaff_DI + 1;
    in_CX = in_CX + -1;
    if (in_CX == 0) goto LAB_1ad9_12bf;
  }
  else if (*unaff_DI == 0x2d) {
    bVar1 = true;
    goto LAB_1ad9_1273;
  }
  if (*unaff_DI == 0x24) {
    iVar4 = in_CX + -1;
    if (iVar4 == 0) {
LAB_1ad9_12bf:
      return CONCAT22(uVar7,uVar2);
    }
    do {
      unaff_DI = unaff_DI + 1;
      bVar9 = *unaff_DI;
      if (0x60 < bVar9) {
        bVar9 = bVar9 - 0x20;
      }
      bVar10 = bVar9 - 0x30;
      if ((byte)(bVar9 - 0x3a) < 0xf6) {
        if ((byte)(bVar9 + 0xb9) < 0xfa) break;
        bVar10 = bVar9 - 0x37;
      }
      cVar11 = '\x04';
      do {
        bVar12 = (int)uVar2 < 0;
        uVar2 = uVar2 << 1;
        bVar13 = (int)uVar7 < 0;
        uVar7 = uVar7 << 1 | (uint)bVar12;
        if (bVar13) goto LAB_1ad9_12bf;
        cVar11 = cVar11 + -1;
      } while (cVar11 != '\0');
      uVar2 = CONCAT11((char)(uVar2 >> 8),(byte)uVar2 | bVar10);
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  else {
    do {
      uVar6 = (uint)(byte)(*unaff_DI - 0x30);
      if ((byte)(*unaff_DI - 0x3a) < 0xf6) break;
      if ((uVar7 & 0xf000) != 0) goto LAB_1ad9_12bf;
      uVar3 = uVar2 * 2;
      uVar8 = uVar7 << 1 | (uint)((int)uVar2 < 0);
      iVar4 = uVar2 << 2;
      uVar5 = uVar2 * 8;
      uVar7 = uVar2 * 10;
      uVar2 = uVar7 + uVar6;
      uVar7 = ((uVar8 << 1 | (uint)((int)uVar3 < 0)) << 1 | (uint)(iVar4 < 0)) + uVar8 +
              (uint)CARRY2(uVar5,uVar3) + (uint)CARRY2(uVar7,uVar6);
      if ((int)uVar7 < 0) goto LAB_1ad9_12bf;
      unaff_DI = unaff_DI + 1;
      in_CX = in_CX + -1;
    } while (in_CX != 0);
  }
  if (bVar1) {
    uVar6 = ~uVar2;
    uVar2 = uVar6 + 1;
    uVar7 = ~uVar7 + (uint)(0xfffe < uVar6);
  }
  return CONCAT22(uVar7,uVar2);
}



/* 1ad9:12f6 FUN_1ad9_12f6 */

void __stdcall16far FUN_1ad9_12f6(int param_1,undefined1 *param_2,int param_3)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  int in_CX;
  undefined1 *puVar3;
  undefined1 *puVar4;
  undefined2 uVar5;
  undefined2 unaff_SS;
  undefined1 local_22 [32];
  
  puVar3 = local_22;
  FUN_1ad9_11e4();
  uVar5 = (undefined2)((ulong)param_2 >> 0x10);
  if (param_1 < param_3) {
    param_3 = param_1;
  }
  if (param_1 < in_CX) {
    in_CX = param_1;
  }
  if (param_3 < in_CX) {
    param_3 = in_CX;
  }
  puVar4 = (undefined1 *)param_2 + 1;
  *param_2 = (char)param_3;
  param_3 = param_3 - in_CX;
  if (param_3 != 0) {
    for (; param_3 != 0; param_3 = param_3 + -1) {
      puVar1 = puVar4;
      puVar4 = puVar4 + 1;
      *puVar1 = 0x20;
    }
  }
  for (; in_CX != 0; in_CX = in_CX + -1) {
    puVar2 = puVar4;
    puVar4 = puVar4 + 1;
    puVar1 = puVar3;
    puVar3 = puVar3 + 1;
    *puVar2 = *puVar1;
  }
  return;
}



/* 1ad9:1341 FUN_1ad9_1341 */

undefined2 __stdcall16far FUN_1ad9_1341(int *param_1,byte *param_2)

{
  undefined2 uVar1;
  uint uVar2;
  int iVar3;
  byte *pbVar4;
  bool bVar5;
  
  bVar5 = false;
  uVar2 = (uint)*param_2;
  pbVar4 = (byte *)param_2;
  while ((pbVar4 = pbVar4 + 1, uVar2 != 0 && (bVar5 = *pbVar4 < 0x20, *pbVar4 == 0x20))) {
    uVar2 = uVar2 - 1;
  }
  uVar1 = FUN_1ad9_125e();
  if ((bVar5) || (iVar3 = 0, uVar2 != 0)) {
    iVar3 = (int)pbVar4 - (int)(byte *)param_2;
    uVar1 = 0;
  }
  *param_1 = iVar3;
  return uVar1;
}



/* 1ad9:1372 FUN_1ad9_1372 */

void __stdcall16far FUN_1ad9_1372(byte *param_1,undefined2 *param_2)

{
  byte *pbVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  byte *pbVar5;
  undefined2 *puVar6;
  byte *pbVar7;
  undefined2 uVar8;
  
  uVar8 = (undefined2)((ulong)param_2 >> 0x10);
  puVar6 = (undefined2 *)param_2;
  pbVar5 = (byte *)param_1;
  *param_2 = 0;
  puVar6[1] = 0xd7b0;
  puVar6[2] = 0x80;
  puVar6[3] = 0;
  puVar6[4] = 0;
  puVar6[5] = 0;
  puVar6[6] = puVar6 + 0x40;
  puVar6[7] = uVar8;
  pbVar7 = (byte *)(puVar6 + 9);
  puVar6[8] = 0x1487;
  pbVar7[0] = 0xd9;
  pbVar7[1] = 0x1a;
  for (iVar3 = 0xe; pbVar7 = pbVar7 + 2, iVar3 != 0; iVar3 = iVar3 + -1) {
    pbVar7[0] = 0;
    pbVar7[1] = 0;
  }
  bVar2 = *param_1;
  if (0x4f < bVar2) {
    bVar2 = 0x4f;
  }
  for (uVar4 = (uint)bVar2; pbVar5 = pbVar5 + 1, uVar4 != 0; uVar4 = uVar4 - 1) {
    pbVar1 = pbVar7;
    pbVar7 = pbVar7 + 1;
    *pbVar1 = *pbVar5;
  }
  *pbVar7 = 0;
  return;
}



/* 1ad9:13e2 FUN_1ad9_13e2 */

void FUN_1ad9_13e2(void)

{
  FUN_1ad9_13ef();
  return;
}



/* 1ad9:13e7 FUN_1ad9_13e7 */

void FUN_1ad9_13e7(void)

{
  FUN_1ad9_13ef();
  return;
}



/* 1ad9:13ef FUN_1ad9_13ef */

void __stdcall16far FUN_1ad9_13ef(undefined4 param_1)

{
  int iVar1;
  undefined2 in_DX;
  int iVar2;
  undefined2 uVar3;
  undefined2 unaff_DS;
  bool bVar4;
  
  uVar3 = (undefined2)((ulong)param_1 >> 0x10);
  iVar2 = (int)param_1;
  iVar1 = *(int *)(iVar2 + 2);
  if ((iVar1 == -0x284f) || (iVar1 == -0x284e)) {
    FUN_1ad9_143b(iVar2,uVar3);
  }
  else if (iVar1 != -0x2850) {
    *(undefined2 *)0x556 = 0x66;
    return;
  }
  bVar4 = true;
  *(undefined2 *)(iVar2 + 2) = in_DX;
  *(undefined2 *)(iVar2 + 8) = 0;
  *(undefined2 *)(iVar2 + 10) = 0;
  FUN_1ad9_1476();
  if (!bVar4) {
    *(undefined2 *)(iVar2 + 2) = 0xd7b0;
  }
  return;
}



/* 1ad9:143b FUN_1ad9_143b */

void __stdcall16far FUN_1ad9_143b(undefined4 param_1)

{
  int iVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  
  uVar2 = (undefined2)((ulong)param_1 >> 0x10);
  iVar1 = (int)param_1;
  if (*(int *)(iVar1 + 2) != -0x284f) {
    if (*(int *)(iVar1 + 2) != -0x284e) {
      *(undefined2 *)0x556 = 0x67;
      return;
    }
    FUN_1ad9_1476();
  }
  FUN_1ad9_1476();
  *(undefined2 *)(iVar1 + 2) = 0xd7b0;
  return;
}



/* 1ad9:1476 FUN_1ad9_1476 */

void __cdecl16near FUN_1ad9_1476(void)

{
  int iVar1;
  int in_BX;
  int unaff_DI;
  undefined2 unaff_DS;
  
  iVar1 = (*(code *)*(undefined2 *)(in_BX + unaff_DI))(0x1ad9);
  if (iVar1 != 0) {
    *(int *)0x556 = iVar1;
  }
  return;
}



/* 1ad9:1631 FUN_1ad9_1631 */

void __cdecl16near FUN_1ad9_1631(void)

{
  int unaff_DI;
  undefined2 unaff_ES;
  undefined2 unaff_DS;
  
  if ((*(int *)0x556 == 0) && (*(int *)(unaff_DI + 2) != -0x284e)) {
    *(undefined2 *)0x556 = 0x69;
  }
  return;
}



/* 1ad9:1655 FUN_1ad9_1655 */

undefined4 __cdecl16near FUN_1ad9_1655(undefined4 param_1)

{
  undefined2 in_AX;
  int iVar1;
  int in_DX;
  int in_BX;
  int unaff_DI;
  int iVar2;
  undefined2 unaff_ES;
  undefined2 uVar3;
  
  *(undefined1 *)(in_BX + unaff_DI) = (char)in_AX;
  if (in_BX + 1 != in_DX) {
    return CONCAT22(in_DX,in_AX);
  }
  uVar3 = (undefined2)((ulong)param_1 >> 0x10);
  iVar2 = (int)param_1;
  *(int *)(iVar2 + 8) = in_BX + 1;
  iVar1 = (*(code *)*(undefined2 *)(iVar2 + 0x14))(0x1ad9,iVar2,uVar3,iVar2,uVar3);
  if (iVar1 != 0) {
    DAT_1c79_0556 = iVar1;
  }
  return CONCAT22(*(undefined2 *)(iVar2 + 4),*(undefined2 *)(iVar2 + 10));
}



/* 1ad9:16be FUN_1ad9_16be */

void __stdcall16far FUN_1ad9_16be(undefined4 param_1)

{
  int iVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  undefined1 in_ZF;
  
  uVar2 = (undefined2)((ulong)param_1 >> 0x10);
  iVar1 = (int)param_1;
  FUN_1ad9_1631();
  if ((bool)in_ZF) {
    FUN_1ad9_1655();
    FUN_1ad9_1655();
  }
  *(undefined2 *)(iVar1 + 8) = register0x00000010;
  if ((*(int *)(iVar1 + 0x1a) != 0) && (*(int *)0x556 == 0)) {
    iVar1 = (*(code *)*(undefined2 *)(iVar1 + 0x18))(0x1ad9,iVar1,uVar2);
    if (iVar1 != 0) {
      *(int *)0x556 = iVar1;
    }
  }
  return;
}



/* 1ad9:173b FUN_1ad9_173b */

void __stdcall16far FUN_1ad9_173b(int param_1,byte *param_2,undefined4 param_3)

{
  int iVar1;
  uint uVar2;
  undefined2 in_BX;
  undefined1 in_ZF;
  
  FUN_1ad9_1631();
  if ((bool)in_ZF) {
    uVar2 = (uint)*param_2;
    iVar1 = param_1 - uVar2;
    if (iVar1 != 0 && (int)uVar2 <= param_1) {
      do {
        FUN_1ad9_1655();
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
      uVar2 = (uint)*param_2;
    }
    for (; uVar2 != 0; uVar2 = uVar2 - 1) {
      FUN_1ad9_1655();
    }
  }
  *(undefined2 *)((int)param_3 + 8) = in_BX;
  return;
}



/* 1ad9:1779 FUN_1ad9_1779 */

void __stdcall16far FUN_1ad9_1779(byte *param_1,undefined2 *param_2)

{
  byte *pbVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  byte *pbVar5;
  byte *pbVar6;
  undefined2 uVar7;
  
  uVar7 = (undefined2)((ulong)param_2 >> 0x10);
  pbVar5 = (byte *)param_1;
  pbVar6 = (byte *)((undefined2 *)param_2 + 1);
  *param_2 = 0;
  pbVar6[0] = 0xb0;
  pbVar6[1] = 0xd7;
  for (iVar3 = 0x16; pbVar6 = pbVar6 + 2, iVar3 != 0; iVar3 = iVar3 + -1) {
    pbVar6[0] = 0;
    pbVar6[1] = 0;
  }
  bVar2 = *param_1;
  if (0x4f < bVar2) {
    bVar2 = 0x4f;
  }
  for (uVar4 = (uint)bVar2; pbVar5 = pbVar5 + 1, uVar4 != 0; uVar4 = uVar4 - 1) {
    pbVar1 = pbVar6;
    pbVar6 = pbVar6 + 1;
    *pbVar1 = *pbVar5;
  }
  *pbVar6 = 0;
  return;
}



/* 1ad9:17a7 FUN_1ad9_17a7 */

void __stdcall16far FUN_1ad9_17a7(undefined2 param_1,undefined2 *param_2)

{
  code *pcVar1;
  undefined2 uVar2;
  undefined2 *puVar3;
  undefined2 uVar4;
  undefined2 unaff_DS;
  bool bVar5;
  undefined2 in_stack_00000000;
  
  uVar4 = (undefined2)((ulong)param_2 >> 0x10);
  puVar3 = (undefined2 *)param_2;
  if (puVar3[1] != -0x2850) {
    if (puVar3[1] != -0x284d) {
      *(undefined2 *)0x556 = 0x66;
      return;
    }
    FUN_1ad9_1828(puVar3,uVar4);
  }
  uVar2 = 0;
  if (*(char *)(puVar3 + 0x18) != '\0') {
    bVar5 = false;
    pcVar1 = (code *)swi(0x21);
    uVar2 = (*pcVar1)();
    if (bVar5) {
      *(undefined2 *)0x556 = uVar2;
      return;
    }
  }
  puVar3[1] = 0xd7b3;
  *param_2 = uVar2;
  puVar3[2] = param_1;
  return;
}



/* 1ad9:17b0 FUN_1ad9_17b0 */

void __stdcall16far FUN_1ad9_17b0(undefined2 param_1,undefined2 *param_2)

{
  code *pcVar1;
  undefined2 uVar2;
  undefined2 *puVar3;
  undefined2 uVar4;
  undefined2 unaff_DS;
  bool bVar5;
  undefined2 in_stack_00000000;
  
  uVar4 = (undefined2)((ulong)param_2 >> 0x10);
  puVar3 = (undefined2 *)param_2;
  if (puVar3[1] != -0x2850) {
    if (puVar3[1] != -0x284d) {
      *(undefined2 *)0x556 = 0x66;
      return;
    }
    FUN_1ad9_1828(puVar3,uVar4);
  }
  uVar2 = 1;
  if (*(char *)(puVar3 + 0x18) != '\0') {
    bVar5 = false;
    pcVar1 = (code *)swi(0x21);
    uVar2 = (*pcVar1)();
    if (bVar5) {
      *(undefined2 *)0x556 = uVar2;
      return;
    }
  }
  puVar3[1] = 0xd7b3;
  *param_2 = uVar2;
  puVar3[2] = param_1;
  return;
}



/* 1ad9:1828 FUN_1ad9_1828 */

void __stdcall16far FUN_1ad9_1828(uint *param_1)

{
  code *pcVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  bool bVar3;
  undefined1 in_ZF;
  
  FUN_1ad9_184d();
  if ((bool)in_ZF) {
    bVar3 = *param_1 < 4;
    if (4 < *param_1) {
      pcVar1 = (code *)swi(0x21);
      uVar2 = (*pcVar1)();
      if (bVar3) {
        *(undefined2 *)0x556 = uVar2;
      }
    }
    ((uint *)param_1)[1] = 0xd7b0;
  }
  return;
}



/* 1ad9:184d FUN_1ad9_184d */

void __cdecl16near FUN_1ad9_184d(void)

{
  int unaff_DI;
  undefined2 unaff_ES;
  undefined2 unaff_DS;
  
  if (*(int *)(unaff_DI + 2) != -0x284d) {
    *(undefined2 *)0x556 = 0x67;
  }
  return;
}



/* 1ad9:185c FUN_1ad9_185c */

void __stdcall16far FUN_1ad9_185c(undefined2 param_1,undefined2 param_2,undefined4 param_3)

{
  code *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int unaff_BP;
  undefined1 in_CF;
  undefined1 in_ZF;
  undefined2 in_stack_00000000;
  
  FUN_1ad9_184d();
  if ((bool)in_ZF) {
    iVar4 = *(int *)((int)param_3 + 4);
    pcVar1 = (code *)swi(0x21);
    iVar2 = (*pcVar1)();
    iVar3 = iVar2;
    if (((bool)in_CF) || (iVar3 = unaff_BP, iVar2 != iVar4)) {
      *(int *)0x556 = iVar3;
    }
  }
  return;
}



/* 1ad9:1863 FUN_1ad9_1863 */

void __stdcall16far FUN_1ad9_1863(undefined2 param_1,undefined2 param_2,undefined4 param_3)

{
  code *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int unaff_BP;
  undefined1 in_CF;
  undefined1 in_ZF;
  undefined2 in_stack_00000000;
  
  FUN_1ad9_184d();
  if ((bool)in_ZF) {
    iVar4 = *(int *)((int)param_3 + 4);
    pcVar1 = (code *)swi(0x21);
    iVar2 = (*pcVar1)();
    iVar3 = iVar2;
    if (((bool)in_CF) || (iVar3 = unaff_BP, iVar2 != iVar4)) {
      *(int *)0x556 = iVar3;
    }
  }
  return;
}



/* 1ad9:1892 FUN_1ad9_1892 */

void __stdcall16far
FUN_1ad9_1892(uint *param_1,uint param_2,undefined2 param_3,undefined2 param_4,undefined4 param_5)

{
  code *pcVar1;
  uint uVar2;
  undefined2 uVar3;
  undefined2 unaff_BP;
  undefined2 uVar4;
  int iVar5;
  undefined2 unaff_DS;
  bool bVar6;
  undefined1 in_ZF;
  undefined2 in_stack_00000000;
  
  uVar3 = 100;
  uVar4 = (undefined2)((ulong)param_5 >> 0x10);
  FUN_1ad9_184d();
  iVar5 = (int)((ulong)param_1 >> 0x10);
  if ((bool)in_ZF) {
    uVar2 = 0;
    if (param_2 != 0) {
      bVar6 = (int)((ulong)param_2 * (ulong)*(uint *)((int)param_5 + 4) >> 0x10) != 0;
      pcVar1 = (code *)swi(0x21);
      uVar2 = (*pcVar1)();
      if (bVar6) {
        *(uint *)0x556 = uVar2;
        goto LAB_1ad9_18e8;
      }
      uVar2 = uVar2 / *(uint *)((int)param_5 + 4);
      uVar3 = unaff_BP;
      unaff_DS = in_stack_00000000;
    }
    if (iVar5 == 0 && (uint *)param_1 == (uint *)0x0) {
      if (uVar2 != param_2) {
        *(undefined2 *)0x556 = uVar3;
      }
    }
    else {
      *param_1 = uVar2;
    }
  }
  else {
LAB_1ad9_18e8:
    if (iVar5 != 0 || (uint *)param_1 != (uint *)0x0) {
      *param_1 = 0;
    }
  }
  return;
}



/* 1ad9:18fa FUN_1ad9_18fa */

void __stdcall16far FUN_1ad9_18fa(uint param_1,int param_2,undefined4 param_3)

{
  code *pcVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  bool bVar3;
  undefined1 in_ZF;
  
  uVar2 = (undefined2)((ulong)param_3 >> 0x10);
  FUN_1ad9_184d();
  if ((bool)in_ZF) {
    bVar3 = CARRY2(param_2 * *(int *)((int)param_3 + 4),
                   (uint)((ulong)param_1 * (ulong)*(uint *)((int)param_3 + 4) >> 0x10));
    pcVar1 = (code *)swi(0x21);
    uVar2 = (*pcVar1)();
    if (bVar3) {
      *(undefined2 *)0x556 = uVar2;
    }
  }
  return;
}



/* 1ad9:1941 FUN_1ad9_1941 */

undefined2 __stdcall16far FUN_1ad9_1941(void)

{
  undefined2 uVar1;
  undefined2 in_CX;
  int unaff_DI;
  undefined2 unaff_ES;
  undefined1 in_CF;
  
  uVar1 = FUN_1ad9_1971();
  if ((!(bool)in_CF) && (uVar1 = in_CX, *(int *)(unaff_DI + 4) != 1)) {
    uVar1 = FUN_1ad9_0294();
  }
  return uVar1;
}



/* 1ad9:1971 FUN_1ad9_1971 */

undefined2 __cdecl16near FUN_1ad9_1971(undefined2 param_1,undefined2 param_2,undefined4 param_3)

{
  code *pcVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  
  if (*(int *)((int)param_3 + 2) == -0x284d) {
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
    pcVar1 = (code *)swi(0x21);
    uVar2 = (*pcVar1)();
    return uVar2;
  }
  *(undefined2 *)0x556 = 0x67;
  return 0;
}



/* 1ad9:19b6 FUN_1ad9_19b6 */

void __stdcall16far FUN_1ad9_19b6(int param_1,undefined1 *param_2,undefined1 *param_3)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  byte bVar5;
  
  puVar3 = (undefined1 *)param_3;
  puVar4 = (undefined1 *)param_2;
  bVar5 = 0;
  if (puVar3 < puVar4) {
    puVar3 = puVar3 + param_1 + -1;
    puVar4 = puVar4 + param_1 + -1;
    bVar5 = 1;
  }
  for (; param_1 != 0; param_1 = param_1 + -1) {
    puVar2 = puVar4;
    puVar4 = puVar4 + (uint)bVar5 * -2 + 1;
    puVar1 = puVar3;
    puVar3 = puVar3 + (uint)bVar5 * -2 + 1;
    *puVar2 = *puVar1;
  }
  return;
}



/* 1ad9:19d9 FUN_1ad9_19d9 */

void __stdcall16far FUN_1ad9_19d9(undefined1 param_1,int param_2,undefined1 *param_3)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  
  puVar2 = (undefined1 *)param_3;
  for (; param_2 != 0; param_2 = param_2 + -1) {
    puVar1 = puVar2;
    puVar2 = puVar2 + 1;
    *puVar1 = param_1;
  }
  return;
}



/* 1ad9:19ed FUN_1ad9_19ed */

byte __stdcall16far FUN_1ad9_19ed(byte param_1)

{
  if ((0x60 < param_1) && (param_1 < 0x7b)) {
    param_1 = param_1 - 0x20;
  }
  return param_1;
}


