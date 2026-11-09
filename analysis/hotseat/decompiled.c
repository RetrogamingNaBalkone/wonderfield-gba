
/* 1000:0000 FUN_1000_0000 */

void __cdecl16near FUN_1000_0000(void)

{
  FUN_17cc_0a35();
  FUN_1b5a_00d8();
  return;
}



/* 1000:0055 FUN_1000_0055 */

void __cdecl16near FUN_1000_0055(void)

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
  
  FUN_1b5a_0644(0xff,local_182,unaff_SS,0x16,0x1000);
  FUN_1b5a_161f(local_182,unaff_SS,local_202,unaff_SS);
  FUN_1b5a_164d(0x80,local_202,unaff_SS);
  iVar4 = FUN_1b5a_0207();
  if (iVar4 != 0) {
    uVar9 = 0xf46;
    puVar7 = local_306;
    uVar8 = unaff_SS;
    uVar10 = unaff_DS;
    FUN_1b5a_062a(0x20,0x1b5a);
    FUN_1b5a_06b7(local_182,unaff_SS);
    FUN_1b5a_06b7(0x26,0x1b5a);
    FUN_1b5a_15e1(0,puVar7,uVar8);
    FUN_1b5a_1564(uVar9,uVar10);
    FUN_1b5a_020e();
    FUN_1b5a_00d8();
  }
  FUN_1b5a_1738(0,0,1,local_82,unaff_SS,local_202,unaff_SS);
  FUN_1b5a_020e();
  _local_20a = (ulong)CONCAT12(local_82[0],local_20a);
  if (local_82[0] != 0) {
    local_204 = 1;
    while( true ) {
      bVar1 = local_82[local_204];
      uVar6 = FUN_1b5a_0329((uint)bVar1 << 7);
      iVar4 = (local_204 + -1) * 4;
      *(undefined2 *)(iVar4 + 0xa56) = (int)uVar6;
      *(undefined2 *)(iVar4 + 0xa58) = (int)((ulong)uVar6 >> 0x10);
      uVar6 = *(undefined4 *)((local_204 + -1) * 4 + 0xa56);
      FUN_1b5a_1738(0,0,(uint)bVar1,(int)uVar6,(int)((ulong)uVar6 >> 0x10),local_202,unaff_SS);
      FUN_1b5a_020e();
      uVar3 = _local_20a;
      uVar2 = _local_20a >> 0x10;
      bVar5 = local_204 == (int)uVar2;
      _local_20a = uVar3;
      if (bVar5) break;
      local_204 = local_204 + 1;
    }
  }
  FUN_1b5a_16ce(local_202,unaff_SS);
  FUN_1b5a_020e();
  FUN_1b5a_0644(0xff,local_182,unaff_SS,0x31,0x1b5a);
  FUN_1b5a_161f(local_182,unaff_SS,local_202,unaff_SS);
  FUN_1b5a_164d(0x80,local_202,unaff_SS);
  iVar4 = FUN_1b5a_0207();
  if (iVar4 != 0) {
    uVar9 = 0xf46;
    puVar7 = local_306;
    uVar8 = unaff_SS;
    uVar10 = unaff_DS;
    FUN_1b5a_062a(0x20,0x1b5a);
    FUN_1b5a_06b7(local_182,unaff_SS);
    FUN_1b5a_06b7(0x26,0x1b5a);
    FUN_1b5a_15e1(0,puVar7,uVar8);
    FUN_1b5a_1564(uVar9,uVar10);
    FUN_1b5a_020e();
    FUN_1b5a_00d8();
  }
  uVar6 = FUN_1b5a_0329(0x800);
  *(undefined2 *)0xc42 = (int)uVar6;
  *(undefined2 *)0xc44 = (int)((ulong)uVar6 >> 0x10);
  FUN_1b5a_1738(&local_204,unaff_SS,0xc,(int)*(undefined4 *)0xc42,
                (int)((ulong)*(undefined4 *)0xc42 >> 0x10),local_202,unaff_SS);
  FUN_1b5a_020e();
  uVar6 = FUN_1b5a_0329(0x800);
  *(undefined2 *)0xc46 = (int)uVar6;
  *(undefined2 *)0xc48 = (int)((ulong)uVar6 >> 0x10);
  FUN_1b5a_1738(&local_204,unaff_SS,0x10,(int)*(undefined4 *)0xc46,
                (int)((ulong)*(undefined4 *)0xc46 >> 0x10),local_202,unaff_SS);
  FUN_1b5a_020e();
  uVar6 = FUN_1b5a_0329(0xe00);
  *(undefined2 *)0xc4a = (int)uVar6;
  *(undefined2 *)0xc4c = (int)((ulong)uVar6 >> 0x10);
  FUN_1b5a_1738(&local_204,unaff_SS,0x1c,(int)*(undefined4 *)0xc4a,
                (int)((ulong)*(undefined4 *)0xc4a >> 0x10),local_202,unaff_SS);
  FUN_1b5a_020e();
  FUN_1b5a_16ce(local_202,unaff_SS);
  FUN_1b5a_020e();
  FUN_1b5a_0644(0xff,local_182,unaff_SS,0x3a,0x1b5a);
  FUN_1b5a_161f(local_182,unaff_SS,0x814,unaff_DS);
  FUN_1b5a_164d(0xd,0x814,unaff_DS);
  iVar4 = FUN_1b5a_0207();
  if (iVar4 == 0) {
    local_204 = 1;
    while( true ) {
      FUN_1b5a_1702(local_204 * 0xd + 0x583,unaff_DS);
      FUN_1b5a_020e();
      if (local_204 == 8) break;
      local_204 = local_204 + 1;
    }
    FUN_1b5a_16ce(0x814,unaff_DS);
    FUN_1b5a_020e();
  }
  else {
    local_204 = 1;
    while( true ) {
      iVar4 = local_204 * 0xd + 0x583;
      _local_20a = CONCAT22(unaff_DS,iVar4);
      if ((bool)((byte)local_204 & 1)) {
        FUN_1b5a_0644(10,iVar4,unaff_DS,0x44,0x1b5a);
      }
      else {
        FUN_1b5a_0644(10,iVar4,unaff_DS,0x4c,0x1b5a);
      }
      *(int *)((int)_local_20a + 0xb) = local_204 * -0xf + 0x87;
      if (local_204 == 8) break;
      local_204 = local_204 + 1;
    }
  }
  return;
}



/* 1000:03a7 FUN_1000_03a7 */

/* WARNING: Removing unreachable block (ram,0x00010491) */

void FUN_1000_03a7(undefined4 param_1,int param_2,int param_3,undefined1 param_4,int param_5,
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
  
  FUN_1b5a_0644(0xff,local_102,unaff_SS,(int)param_7,(int)((ulong)param_7 >> 0x10));
  out(0x3ce,5);
  out(0x3cf,2);
  if (local_102[0] != 0) {
    local_10a = 1;
    while( true ) {
      bVar1 = (byte)param_6 & 7;
      bVar2 = 8 - bVar1;
      iVar3 = param_5 * 0x50 + (param_6 >> 3);
      iVar4 = FUN_1b5a_0279();
      local_10c = 0;
      while( true ) {
        if (param_3 == 5) {
          local_111 = *(byte *)((int)*(undefined4 *)0xc42 + iVar4 + local_10c);
        }
        else if (param_3 == 7) {
          local_111 = *(byte *)((int)*(undefined4 *)0xc46 + iVar4 + local_10c);
        }
        else {
          local_111 = *(byte *)((int)*(undefined4 *)0xc4a + iVar4 + local_10c);
        }
        out(0x3ce,8);
        out(0x3cf,local_111 >> bVar1);
        uVar5 = (undefined2)((ulong)param_1 >> 0x10);
        FUN_1b5a_187f(param_4,1,(int)param_1 + local_10c * 0x50 + iVar3,uVar5);
        if (bVar2 != 8) {
          out(0x3ce,8);
          out(0x3cf,local_111 << (bVar2 & 0x1f));
          FUN_1b5a_187f(param_4,1,(int)param_1 + local_10c * 0x50 + iVar3 + 1,uVar5);
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



/* 1000:05cc FUN_1000_05cc */

void __cdecl16near FUN_1000_05cc(void)

{
  int iVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  
  uVar2 = 0x17cc;
  iVar1 = FUN_17cc_016f(0x67ca,0x1000);
  if (iVar1 < 0) {
    uVar2 = 0x1b5a;
    FUN_1b5a_00d8();
  }
  *(undefined2 *)0x9ba = 3;
  *(undefined2 *)0x9b8 = 1;
  FUN_17cc_0759(0x5cb,uVar2,0x9b8,unaff_DS,0x9ba,unaff_DS);
  FUN_17cc_0d05(0x2e,6);
  FUN_17cc_0d05(0x14,4);
  FUN_17cc_0d05(0x27,5);
  *(undefined2 *)0xa42 = 0;
  FUN_1af1_000b(0xa42);
  if (*(int *)0xa42 == 0) {
    *(undefined2 *)0x7fc = 0;
  }
  else {
    *(undefined2 *)0x7fc = 1;
  }
  if (0 < *(int *)0x7fc) {
    *(undefined2 *)0xa42 = 2;
    FUN_1af1_000b(0xa42);
    *(undefined2 *)0xa42 = 7;
    *(undefined2 *)0xa46 = 0;
    *(undefined2 *)0xa48 = 0x27f;
    FUN_1af1_000b(0xa42);
  }
  return;
}



/* 1000:068d FUN_1000_068d */

void FUN_1000_068d(undefined1 param_1,undefined2 param_2,int param_3,int param_4)

{
  int iVar1;
  undefined2 local_4;
  
  out(0x3ce,5);
  out(0x3cf,2);
  out(0x3ce,8);
  out(0x3cf,0xff);
  FUN_1b5a_187f(param_1,1,param_4,0xa000);
  out(0x3ce,5);
  out(0x3cf,1);
  FUN_1b5a_185c(1,param_4,0xa000,param_4,0xa000);
  if (-1 < param_3) {
    local_4 = 0;
    iVar1 = 0;
    while( true ) {
      FUN_1b5a_187f(CONCAT11((char)((uint)iVar1 >> 8),1),param_2,param_4,0xa000);
      param_4 = param_4 + 0x50;
      if (local_4 == param_3) break;
      iVar1 = local_4;
      local_4 = local_4 + 1;
    }
  }
  return;
}



/* 1000:0727 FUN_1000_0727 */

void FUN_1000_0727(undefined2 param_1,int param_2,int param_3,int param_4)

{
  undefined2 local_4;
  
  out(0x3ce,5);
  out(0x3cf,1);
  if (-1 < param_2) {
    local_4 = 0;
    while( true ) {
      FUN_1b5a_185c(param_1,param_3,0xa000,param_4,0xa000);
      param_4 = param_4 + 0x50;
      param_3 = param_3 + 0x50;
      if (local_4 == param_2) break;
      local_4 = local_4 + 1;
    }
  }
  return;
}



/* 1000:0780 FUN_1000_0780 */

void FUN_1000_0780(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 unaff_DS;
  undefined2 local_6;
  undefined2 local_4;
  
  iVar2 = *(int *)(*(int *)0x8a4 * 2 + 0xb4) * 0x50 + *(int *)(*(int *)0x8a4 * 2 + 0xb0) / 8;
  local_4 = 1;
  while( true ) {
    if (local_4 == 1) {
      local_6 = 0x3b;
    }
    else if (local_4 == 2) {
      if (param_1 == 1) {
        local_6 = 0x3a;
      }
      else {
        local_6 = 0x16;
      }
    }
    else if (local_4 == 3) {
      if (param_1 == 1) {
        local_6 = 0x39;
      }
      else {
        local_6 = 0x15;
      }
    }
    FUN_1000_068d(7,0x10,0x4f,iVar2 + 31999);
    uVar1 = *(undefined4 *)(local_6 * 4 + 0xa56);
    FUN_1000_6696(2,*(undefined2 *)(*(int *)0x8a4 * 2 + 0xb4),
                  *(undefined2 *)(*(int *)0x8a4 * 2 + 0xb0),32000,0xa000,(int)uVar1,
                  (int)((ulong)uVar1 >> 0x10));
    FUN_1000_0727(0x10,0x4f,iVar2 + -1,iVar2 + 31999);
    FUN_1af8_029e(100);
    if (local_4 == 3) break;
    local_4 = local_4 + 1;
  }
  return;
}



/* 1000:086b FUN_1000_086b */

void FUN_1000_086b(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined2 unaff_DS;
  undefined2 local_4;
  
  iVar2 = *(int *)(*(int *)0x8a4 * 2 + 0xb4) * 0x50 + *(int *)(*(int *)0x8a4 * 2 + 0xb0) / 8;
  iVar3 = iVar2 + -1;
  if (param_1 == 1) {
    local_4 = 0;
    while( true ) {
      FUN_1000_068d(7,0x10,0x4f,iVar2 + 31999);
      uVar1 = *(undefined4 *)((local_4 + 0x3a) * 4 + 0xa56);
      FUN_1000_6696(2,*(undefined2 *)(*(int *)0x8a4 * 2 + 0xb4),
                    *(undefined2 *)(*(int *)0x8a4 * 2 + 0xb0),32000,0xa000,(int)uVar1,
                    (int)((ulong)uVar1 >> 0x10));
      FUN_1000_0727(0x10,0x4f,iVar3,iVar2 + 31999);
      FUN_1af8_029e(100);
      if (local_4 == 1) break;
      local_4 = local_4 + 1;
    }
  }
  else {
    FUN_1000_068d(7,0x10,0x4f,iVar2 + 31999);
    FUN_1000_6696(2,*(undefined2 *)(*(int *)0x8a4 * 2 + 0xb4),
                  *(undefined2 *)(*(int *)0x8a4 * 2 + 0xb0),32000,0xa000,(int)*(undefined4 *)0xaae,
                  (int)((ulong)*(undefined4 *)0xaae >> 0x10));
    FUN_1000_0727(0x10,0x4f,iVar3,iVar2 + 31999);
    FUN_1af8_029e(100);
    FUN_1000_068d(7,0x10,0x4f,iVar2 + 31999);
    FUN_1000_6696(2,*(undefined2 *)(*(int *)0x8a4 * 2 + 0xb4),
                  *(undefined2 *)(*(int *)0x8a4 * 2 + 0xb0),32000,0xa000,(int)*(undefined4 *)0xb42,
                  (int)((ulong)*(undefined4 *)0xb42 >> 0x10));
    FUN_1000_0727(0x10,0x4f,iVar3,iVar2 + 31999);
  }
  return;
}



/* 1000:09da FUN_1000_09da */

void __cdecl16near FUN_1000_09da(void)

{
  char cVar1;
  undefined1 uVar2;
  undefined2 unaff_DS;
  
  while( true ) {
    cVar1 = FUN_1af8_02fa();
    if (cVar1 == '\0') break;
    uVar2 = FUN_1af8_030c();
    *(undefined1 *)0x9b2 = uVar2;
  }
  if (0 < *(int *)0x7fc) {
    do {
      *(undefined2 *)0xa42 = 3;
      FUN_1af1_000b(0xa42);
    } while (*(int *)0xa44 != 0);
  }
  return;
}



/* 1000:0a15 FUN_1000_0a15 */

void __cdecl16near FUN_1000_0a15(void)

{
  char cVar1;
  undefined1 uVar2;
  uint uVar3;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  int local_16;
  undefined1 local_14 [18];
  
  FUN_17cc_0d49(local_14,unaff_SS);
  uVar3 = 0;
  local_16 = 0;
  while( true ) {
    uVar3 = FUN_17cc_0d05(uVar3 & 0xff00,local_16);
    if (local_16 == 0xf) break;
    local_16 = local_16 + 1;
  }
  FUN_1000_09da();
  do {
    *(undefined2 *)0xa44 = 0;
    if (0 < *(int *)0x7fc) {
      *(undefined2 *)0xa42 = 3;
      FUN_1af1_000b(0xa42);
    }
    *(undefined1 *)0x9b2 = 7;
    cVar1 = FUN_1af8_02fa();
    if (cVar1 != '\0') {
      uVar2 = FUN_1af8_030c();
      *(undefined1 *)0x9b2 = uVar2;
    }
    if (*(char *)0x9b2 == '\x1b') {
      FUN_1000_0000();
    }
    if (*(char *)0x9b2 == '\x13') {
      *(int *)0x8b0 = 1 - *(int *)0x8b0;
    }
  } while ((*(char *)0x9b2 != ' ') && (*(int *)0xa44 != 1));
  *(undefined1 *)0x9b2 = 7;
  FUN_17cc_0c5d(local_14,unaff_SS);
  return;
}



/* 1000:0ab4 FUN_1000_0ab4 */

void FUN_1000_0ab4(int param_1)

{
  char cVar1;
  undefined1 uVar2;
  undefined2 unaff_DS;
  
  FUN_1000_09da();
  do {
    if (0 < param_1) {
      param_1 = param_1 + -1;
    }
    FUN_1af8_029e(0x32);
    *(undefined2 *)0xa44 = 0;
    if (0 < *(int *)0x7fc) {
      *(undefined2 *)0xa42 = 3;
      FUN_1af1_000b(0xa42);
    }
    *(undefined1 *)0x9b2 = 7;
    cVar1 = FUN_1af8_02fa();
    if (cVar1 != '\0') {
      uVar2 = FUN_1af8_030c();
      *(undefined1 *)0x9b2 = uVar2;
    }
    if (*(char *)0x9b2 == '\x1b') {
      FUN_1000_0000();
    }
    if (*(char *)0x9b2 == '\x13') {
      *(int *)0x8b0 = 1 - *(int *)0x8b0;
    }
    if (*(char *)0x9b2 == '\t') {
      FUN_1000_0a15();
    }
  } while (((*(char *)0x9b2 != ' ') && (*(int *)0xa44 != 1)) && (param_1 != 1));
  return;
}



/* 1000:0b40 FUN_1000_0b40 */

void __cdecl16near FUN_1000_0b40(void)

{
  undefined2 uVar1;
  undefined2 local_4;
  
  local_4 = 1;
  while( true ) {
    FUN_1b5a_0ff6(100);
    uVar1 = FUN_1b5a_0279();
    FUN_1af8_02c6(uVar1);
    FUN_1af8_029e(6 - local_4);
    FUN_1af8_02f3();
    FUN_1af8_029e(1);
    if (local_4 == 6) break;
    local_4 = local_4 + 1;
  }
  return;
}



/* 1000:0b92 FUN_1000_0b92 */

void __cdecl16near FUN_1000_0b92(void)

{
  undefined2 unaff_DS;
  
  FUN_1000_0727(0x14,0xbe,0x2bfc,0xa8fc);
  FUN_1000_0b40();
  FUN_1000_6696(0x10,0xad,0x1ff,0,0xa000,(int)*(undefined4 *)0xb0a,
                (int)((ulong)*(undefined4 *)0xb0a >> 0x10));
  FUN_1af8_029e(0x1e);
  FUN_1000_6696(0x10,0xd1,0x214,0,0xa000,(int)*(undefined4 *)0xb02,
                (int)((ulong)*(undefined4 *)0xb02 >> 0x10));
  return;
}



/* 1000:0c00 FUN_1000_0c00 */

void FUN_1000_0c00(int param_1)

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
  
  FUN_1000_068d(7,0xc,0x1d,
                (*(int *)(param_1 * 2 + 0xa6) + -1) * 0x50 + (*(int *)(param_1 * 2 + 0xa0) + -4) / 8
               );
  iVar1 = *(int *)(param_1 * 2 + 0x89c);
  if (0 < iVar1) {
    local_4 = 1;
    while( true ) {
      FUN_1b5a_0ff6(10);
      uVar2 = FUN_1b5a_0279();
      FUN_1af8_02c6(uVar2);
      uVar5 = (undefined2)((ulong)*(undefined4 *)0xace >> 0x10);
      uVar2 = (undefined2)*(undefined4 *)0xace;
      uVar7 = 0xa000;
      uVar6 = 0;
      iVar3 = FUN_1b5a_0ff6(0xc);
      iVar3 = *(int *)(param_1 * 2 + 0xa0) + -4 + iVar3;
      iVar4 = FUN_1b5a_0ff6(7);
      FUN_1000_6696(1,*(int *)(param_1 * 2 + 0xa6) + -1 + iVar4,iVar3,uVar6,uVar7,uVar2,uVar5);
      FUN_1af8_02f3();
      if (local_4 == iVar1) break;
      local_4 = local_4 + 1;
    }
  }
  if (*(int *)(param_1 * 2 + 0x89c) < 1) {
    FUN_1000_6696(2,*(int *)(param_1 * 2 + 0xa6) + 10,*(int *)(param_1 * 2 + 0xa0) + 4,0,0xa000,
                  (int)*(undefined4 *)0xac6,(int)((ulong)*(undefined4 *)0xac6 >> 0x10));
  }
  else {
    FUN_1000_6696(1,*(undefined2 *)(param_1 * 2 + 0xa6),*(undefined2 *)(param_1 * 2 + 0xa0),0,0xa000
                  ,(int)*(undefined4 *)0xace,(int)((ulong)*(undefined4 *)0xace >> 0x10));
    iVar1 = *(int *)(param_1 * 2 + 0x89c);
    FUN_1b5a_119c(0xff,local_106,unaff_SS,0,iVar1,iVar1 >> 0xf);
    local_4 = -1;
    while( true ) {
      local_6 = -1;
      while (FUN_1000_03a7(0,0xa000,8,0xd,0,*(int *)(param_1 * 2 + 0xa6) + 4 + local_6,
                           *(int *)(param_1 * 2 + 0xa0) + 0x22 + (uint)local_106[0] * -4 + local_4,
                           local_106,unaff_SS), local_6 != 1) {
        local_6 = local_6 + 1;
      }
      if (local_4 == 1) break;
      local_4 = local_4 + 1;
    }
    FUN_1000_03a7(0,0xa000,8,0xd,0xf,*(int *)(param_1 * 2 + 0xa6) + 4,
                  *(int *)(param_1 * 2 + 0xa0) + 0x22 + (uint)local_106[0] * -4,local_106,unaff_SS);
  }
  return;
}



/* 1000:0e2a FUN_1000_0e2a */

void __cdecl16near FUN_1000_0e2a(void)

{
  undefined2 unaff_DS;
  
  FUN_1000_0b40();
  FUN_1000_6696(0x10,0xc9,0x214,0,0xa000,(int)*(undefined4 *)0xb02,
                (int)((ulong)*(undefined4 *)0xb02 >> 0x10));
  FUN_1af8_029e(100);
  FUN_1000_6696(0x10,0xc9,0x214,0,0xa000,(int)*(undefined4 *)0xb06,
                (int)((ulong)*(undefined4 *)0xb06 >> 0x10));
  FUN_1af8_029e(100);
  return;
}



/* 1000:0e84 FUN_1000_0e84 */

void __cdecl16near FUN_1000_0e84(void)

{
  int iVar1;
  undefined2 unaff_DS;
  undefined2 local_4;
  
  FUN_1000_0b40();
  FUN_1000_6696(0x10,0xd1,0x214,0,0xa000,(int)*(undefined4 *)0xb06,
                (int)((ulong)*(undefined4 *)0xb06 >> 0x10));
  FUN_1af8_029e(200);
  FUN_1000_6696(0x10,0xd1,0x214,0,0xa000,(int)*(undefined4 *)0xb02,
                (int)((ulong)*(undefined4 *)0xb02 >> 0x10));
  FUN_1af8_029e(0x96);
  FUN_1000_6696(0x10,0xd1,0x214,0,0xa000,(int)*(undefined4 *)0xb06,
                (int)((ulong)*(undefined4 *)0xb06 >> 0x10));
  FUN_1af8_029e(0x96);
  FUN_1000_6696(0x10,0xad,0x1ff,0,0xa000,(int)*(undefined4 *)0xafe,
                (int)((ulong)*(undefined4 *)0xafe >> 0x10));
  FUN_1000_6696(0x10,0xc9,0x214,0,0xa000,(int)*(undefined4 *)0xb06,
                (int)((ulong)*(undefined4 *)0xb06 >> 0x10));
  local_4 = 1;
  while( true ) {
    FUN_1000_0b40();
    FUN_1000_6696(0x10,0xad,0x1ff,0,0xa000,(int)*(undefined4 *)0xb0a,
                  (int)((ulong)*(undefined4 *)0xb0a >> 0x10));
    FUN_1000_6696(0x10,0xd1,0x214,0,0xa000,(int)*(undefined4 *)0xb02,
                  (int)((ulong)*(undefined4 *)0xb02 >> 0x10));
    iVar1 = FUN_1b5a_0ff6(2);
    FUN_1af8_029e(iVar1 * 200 + 100);
    FUN_1000_6696(0x10,0xad,0x1ff,0,0xa000,(int)*(undefined4 *)0xafe,
                  (int)((ulong)*(undefined4 *)0xafe >> 0x10));
    iVar1 = FUN_1b5a_0ff6(2);
    FUN_1af8_029e(iVar1 * 0x32 + 100);
    if (local_4 == 3) break;
    local_4 = local_4 + 1;
  }
  return;
}



/* 1000:12aa FUN_1000_12aa */

void FUN_1000_12aa(int param_1)

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
  FUN_1000_0e84();
  local_4 = 0x2bfc;
  FUN_1000_0727(0x14,0xbe,0xa8fc,0x2bfc);
  FUN_1000_6696(1,0x8e,0x1e0,0,0xa000,(int)*(undefined4 *)0xae2,
                (int)((ulong)*(undefined4 *)0xae2 >> 0x10));
  if (param_1 == 1) {
    iVar1 = *(int *)0x8a4;
    if (iVar1 == 1) {
      FUN_1b5a_0644(0x14,local_1a,unaff_SS,0xfe8,0x1000);
    }
    else if (iVar1 == 2) {
      FUN_1b5a_0644(0x14,local_1a,unaff_SS,0xfef,0x1000);
    }
    else if (iVar1 == 3) {
      FUN_1b5a_0644(0x14,local_1a,unaff_SS,0xff6,0x1000);
    }
    puVar3 = local_146;
    uVar2 = unaff_SS;
    FUN_1b5a_062a(local_1a,unaff_SS);
    FUN_1b5a_06b7(0xffd,0x1b5a);
    FUN_1b5a_0644(0x14,local_30,unaff_SS,puVar3,uVar2);
    uVar2 = 0x1b5a;
    FUN_1b5a_0644(0x14,local_46,unaff_SS,0x1005,0x1b5a);
  }
  if (param_1 == 2) {
    if ((0 < *(int *)0x896) && (*(int *)0x896 < 100)) {
      FUN_1b5a_119c(0x14,local_1a,unaff_SS,0,*(int *)0x896,*(int *)0x896 >> 0xf);
      puVar3 = local_146;
      uVar2 = unaff_SS;
      FUN_1b5a_062a(0x1017,0x1b5a);
      FUN_1b5a_06b7(local_1a,unaff_SS);
      FUN_1b5a_06b7(0x101e,0x1b5a);
      FUN_1b5a_0644(0x14,local_30,unaff_SS,puVar3,uVar2);
      uVar2 = 0x1b5a;
      FUN_1b5a_0644(0x14,local_46,unaff_SS,0x1026,0x1b5a);
    }
    if (*(int *)0x896 == 0) {
      FUN_1b5a_0644(0x14,local_30,unaff_SS,0x1036,uVar2);
      uVar2 = 0x1b5a;
      FUN_1b5a_0644(0x14,local_46,unaff_SS,0x1046,0x1b5a);
    }
    if (*(int *)0x896 < 0) {
      FUN_1b5a_0644(0x14,local_30,unaff_SS,0x105a,uVar2);
      uVar2 = 0x1b5a;
      FUN_1b5a_0644(0x14,local_46,unaff_SS,0x1046,0x1b5a);
    }
    if (*(int *)0x896 / 100 == 2) {
      FUN_1b5a_0644(0x14,local_30,unaff_SS,0x106e,uVar2);
      uVar2 = 0x1b5a;
      FUN_1b5a_0644(0x14,local_46,unaff_SS,0x1026,0x1b5a);
    }
    if (*(int *)0x896 == 100) {
      FUN_1b5a_0644(0x14,local_30,unaff_SS,0x1082,uVar2);
      uVar2 = 0x1b5a;
      FUN_1b5a_0644(0x14,local_46,unaff_SS,0x108f,0x1b5a);
    }
    if (*(int *)0x896 == 300) {
      FUN_1b5a_0644(0x14,local_30,unaff_SS,0x10a3,uVar2);
      uVar2 = 0x1b5a;
      FUN_1b5a_0644(0x14,local_46,unaff_SS,0x10b0,0x1b5a);
    }
  }
  if (param_1 == 3) {
    if (*(int *)0x5fc < 1) {
      FUN_1b5a_0644(0x14,local_30,unaff_SS,0x10db,uVar2);
      uVar2 = 0x1b5a;
      FUN_1b5a_0644(0x14,local_46,unaff_SS,0x10ec,0x1b5a);
    }
    else {
      FUN_1b5a_0644(0x14,local_46,unaff_SS,0x10c1,uVar2);
      uVar2 = 0x1b5a;
      FUN_1b5a_0644(0x14,local_30,unaff_SS,0x10d3,0x1b5a);
    }
  }
  if (param_1 == 4) {
    iVar1 = *(int *)0x8a4;
    if (iVar1 == 1) {
      FUN_1b5a_0644(0x14,local_1a,unaff_SS,0xfe8,uVar2);
    }
    else if (iVar1 == 2) {
      FUN_1b5a_0644(0x14,local_1a,unaff_SS,0xfef,uVar2);
    }
    else if (iVar1 == 3) {
      FUN_1b5a_0644(0x14,local_1a,unaff_SS,0xff6,uVar2);
    }
    puVar3 = local_146;
    uVar2 = unaff_SS;
    FUN_1b5a_062a(local_1a,unaff_SS);
    FUN_1b5a_06b7(0x10fb,0x1b5a);
    FUN_1b5a_0644(0x14,local_30,unaff_SS,puVar3,uVar2);
    uVar2 = 0x1b5a;
    FUN_1b5a_0644(0x14,local_46,unaff_SS,0x1102,0x1b5a);
  }
  if (param_1 == 5) {
    FUN_1b5a_0644(0x14,local_30,unaff_SS,0x1111,uVar2);
    uVar2 = 0x1b5a;
    FUN_1b5a_0644(0x14,local_46,unaff_SS,0x1124,0x1b5a);
  }
  if (param_1 == 6) {
    FUN_1b5a_0644(0x14,local_30,unaff_SS,0x1136,uVar2);
    uVar2 = 0x1b5a;
    FUN_1b5a_0644(0x14,local_46,unaff_SS,0x1142,0x1b5a);
  }
  if (param_1 == 7) {
    FUN_1b5a_0644(0x14,local_30,unaff_SS,0x114d,uVar2);
    uVar2 = 0x1b5a;
    FUN_1b5a_0644(0x14,local_46,unaff_SS,0x1156,0x1b5a);
  }
  if (param_1 == 8) {
    FUN_1b5a_0644(0x14,local_30,unaff_SS,0x1163,uVar2);
    uVar2 = 0x1b5a;
    FUN_1b5a_0644(0x14,local_46,unaff_SS,0x116c,0x1b5a);
  }
  if (param_1 == 9) {
    FUN_1b5a_0644(0x14,local_46,unaff_SS,0x117c,uVar2);
    uVar2 = 0x1b5a;
    FUN_1b5a_0644(0x14,local_30,unaff_SS,0x118c,0x1b5a);
  }
  if (param_1 == 10) {
    FUN_1b5a_0644(0x14,local_30,unaff_SS,0x119b,uVar2);
    uVar2 = 0x1b5a;
    FUN_1b5a_0644(0x14,local_46,unaff_SS,0x6ba,unaff_DS);
  }
  if (param_1 == 0xb) {
    FUN_1b5a_0644(0x14,local_30,unaff_SS,0x11a1,uVar2);
    uVar2 = 0x1b5a;
    FUN_1b5a_0644(0x14,local_46,unaff_SS,0x11af,0x1b5a);
  }
  if (param_1 == 0xc) {
    FUN_1b5a_0644(0x14,local_30,unaff_SS,0x11b7,uVar2);
    uVar2 = 0x1b5a;
    FUN_1b5a_0644(0x14,local_46,unaff_SS,0x11c7,0x1b5a);
  }
  if (param_1 == 0xd) {
    FUN_1b5a_0644(0x14,local_30,unaff_SS,0x11d7,uVar2);
    uVar2 = 0x1b5a;
    FUN_1b5a_0644(0x14,local_46,unaff_SS,0x11e6,0x1b5a);
  }
  if (param_1 == 0xe) {
    FUN_1b5a_0644(0x14,local_30,unaff_SS,0x11f6,uVar2);
    uVar2 = 0x1b5a;
    FUN_1b5a_0644(0x14,local_46,unaff_SS,0x1205,0x1b5a);
  }
  if (param_1 == 0xf) {
    FUN_1b5a_0644(0x14,local_30,unaff_SS,0x1216,uVar2);
    uVar2 = 0x1b5a;
    FUN_1b5a_0644(0x14,local_46,unaff_SS,0x1223,0x1b5a);
  }
  if (param_1 == 0x10) {
    FUN_1b5a_0644(0x14,local_30,unaff_SS,0x1233,uVar2);
    uVar2 = 0x1b5a;
    FUN_1b5a_0644(0x14,local_46,unaff_SS,0x123d,0x1b5a);
  }
  if (param_1 == 0x11) {
    FUN_1b5a_0644(0x14,local_30,unaff_SS,0x1244,uVar2);
    puVar3 = local_146;
    uVar4 = unaff_SS;
    FUN_1b5a_062a(0x8b2,unaff_DS);
    FUN_1b5a_06b7(0x124d,0x1b5a);
    uVar2 = 0x1b5a;
    FUN_1b5a_0644(0x14,local_46,unaff_SS,puVar3,uVar4);
  }
  if (param_1 == 0x12) {
    FUN_1b5a_0644(0x14,local_30,unaff_SS,0x1256,uVar2);
    uVar2 = 0x1b5a;
    FUN_1b5a_0644(0x14,local_46,unaff_SS,0x1260,0x1b5a);
  }
  if (param_1 == 0x13) {
    FUN_1b5a_0644(0x14,local_30,unaff_SS,0x126d,uVar2);
    uVar2 = 0x1b5a;
    FUN_1b5a_0644(0x14,local_46,unaff_SS,0x1279,0x1b5a);
  }
  if (param_1 == 0x14) {
    FUN_1b5a_0644(0x14,local_30,unaff_SS,0x1256,uVar2);
    uVar2 = 0x1b5a;
    FUN_1b5a_0644(0x14,local_46,unaff_SS,0x1285,0x1b5a);
  }
  if (param_1 == 0x15) {
    FUN_1b5a_0644(0x14,local_30,unaff_SS,0x1290,uVar2);
    FUN_1b5a_0644(0x14,local_46,unaff_SS,0x129c,0x1b5a);
  }
  FUN_1000_03a7(0,0xa000,8,0xd,0,0x91,(uint)local_30[0] * -4 + 0x22e,local_30,unaff_SS);
  FUN_1000_03a7(0,0xa000,8,0xd,0,0x9e,(uint)local_46[0] * -4 + 0x22e,local_46,unaff_SS);
  FUN_1000_0e2a();
  return;
}



/* 1000:193a FUN_1000_193a */

void __cdecl16near FUN_1000_193a(void)

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
  
  FUN_1af8_02f3();
  local_1a = 1;
  local_1c = (*(int *)0x626 + 5) * 0x10 + 0x6e;
  FUN_1000_0727(0x50,0x78,32000,0);
  local_6 = 48000;
  local_e = 0x28;
  local_10 = 0x19;
  local_16 = 0;
  local_14 = 0;
  local_a = 0x7d5;
  local_12 = 0x14;
  local_8 = local_a;
  while( true ) {
    FUN_1af8_02c6(*(int *)0x8b0 * local_12);
    FUN_1af8_029e(1);
    FUN_1af8_02f3();
    FUN_1af8_029e((100 - local_12) / 5);
    if (local_12 == 100) break;
    local_12 = local_12 + 1;
  }
  do {
    local_8 = (local_e >> 3) + local_10 * 0x50;
    local_14 = local_14 + 1;
    if (local_16 == 10) {
      FUN_1000_0727(2,0x13,local_4 + 0x640,local_4);
      puVar6 = local_11c;
      uVar4 = unaff_SS;
      FUN_1b5a_075a(CONCAT11(extraout_AH,*(undefined1 *)0x7f8));
      FUN_1000_03a7(32000,0xa000,8,0xd,0,0x26,local_c,puVar6,uVar4);
    }
    FUN_1000_0727(6,0x5a,local_6,local_8 + 32000);
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
    uVar1 = *(undefined4 *)(local_18 * 4 + 0xa56);
    FUN_1000_6696(2,local_10,local_e,32000,0xa000,(int)uVar1,(int)((ulong)uVar1 >> 0x10));
    FUN_1000_0727(6,0x5a,local_8,local_8 + 32000);
    FUN_1000_0727(6,0x5a,local_a,local_a + 32000);
    local_a = local_8;
    if (local_16 == 0) {
      FUN_1b5a_0ff6(100);
      uVar4 = FUN_1b5a_0279();
      FUN_1af8_02c6(uVar4);
    }
    FUN_1000_0727(6,0x5a,local_a + 32000,local_6);
    FUN_1af8_02f3();
    if (local_16 == 0) {
      local_e = local_e + local_12;
    }
    if (local_1c < (int)local_e) {
      local_4 = *(int *)(local_1a * 2 + 0x624) * 2 + -0x7e37;
      local_c = (*(int *)(local_1a * 2 + 0x624) + 5) * 0x10 + 0x7d;
      local_1a = local_1a + 1;
      if (*(int *)0x5fc < local_1a) {
        local_1c = 1000;
      }
      else {
        local_1c = (*(int *)(local_1a * 2 + 0x624) + 5) * 0x10 + 0x6e;
      }
      local_16 = 1;
    }
    FUN_1af8_029e(0x32);
    *(undefined1 *)0x9b2 = 7;
    cVar2 = FUN_1af8_02fa();
    if (cVar2 != '\0') {
      uVar3 = FUN_1af8_030c();
      *(undefined1 *)0x9b2 = uVar3;
    }
    if (*(char *)0x9b2 == '\x13') {
      *(int *)0x8b0 = 1 - *(int *)0x8b0;
    }
    if (*(char *)0x9b2 == '\t') {
      FUN_1000_0a15();
    }
    if (*(char *)0x9b2 == '\x1b') {
      FUN_1000_0000();
    }
  } while ((int)local_e < 0x247);
  FUN_1000_0727(8,0x5b,local_8,local_8 + 32000);
  local_12 = 100;
  while( true ) {
    FUN_1af8_02c6(*(int *)0x8b0 * local_12);
    FUN_1af8_029e((100 - local_12) / 10);
    FUN_1af8_02f3();
    FUN_1af8_029e(1);
    if (local_12 == 0x14) break;
    local_12 = local_12 + -1;
  }
  if (*(int *)0x896 < 100) {
    *(int *)(*(int *)0x8a4 * 2 + 0x89c) =
         *(int *)0x896 * *(int *)0x5fc + *(int *)(*(int *)0x8a4 * 2 + 0x89c);
  }
  else if (*(int *)0x896 / 100 == 2) {
    *(int *)(*(int *)0x8a4 * 2 + 0x89c) =
         (*(int *)0x896 % 100) * *(int *)(*(int *)0x8a4 * 2 + 0x89c);
  }
  FUN_1000_0c00(*(undefined2 *)0x8a4);
  return;
}



/* 1000:1cd2 FUN_1000_1cd2 */

void FUN_1000_1cd2(int param_1)

{
  undefined4 uVar1;
  undefined2 unaff_DS;
  undefined2 local_a;
  undefined2 local_8;
  
  *(undefined2 *)(param_1 * 2 + 0x64e) = 1;
  param_1 = param_1 * 0x14;
  local_8 = 0;
  while( true ) {
    if (local_8 < 3) {
      uVar1 = *(undefined4 *)((local_8 + 0x12) * 4 + 0xa56);
      FUN_1000_6696(0x10,0x14c,param_1,0,0xa000,(int)uVar1,(int)((ulong)uVar1 >> 0x10));
    }
    else {
      out(0x3ce,5);
      out(0x3cf,0);
      FUN_17cc_0b9e(7,1);
      FUN_17cc_13aa(0x15e,param_1 + 0x13,0x14c,param_1);
    }
    local_a = 1;
    while( true ) {
      FUN_1af8_02c6((local_a * 10 + local_8 * 100 + 0x32) * *(int *)0x8b0);
      FUN_1af8_029e(1);
      FUN_1af8_02f3();
      FUN_1af8_029e(local_8 * 4 + local_a / 5);
      if (local_a == 10) break;
      local_a = local_a + 1;
    }
    if (local_8 == 3) break;
    local_8 = local_8 + 1;
  }
  return;
}



/* 1000:1dd3 FUN_1000_1dd3 */

void __cdecl16near FUN_1000_1dd3(void)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar4;
  undefined1 *puVar5;
  undefined2 uVar6;
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
  
  if (*(int *)0x8a4 < 2) {
    local_10 = 0;
    local_18 = (uint)*(byte *)0x6a4;
    if (local_18 != 0) {
      local_e = 1;
      while( true ) {
        if (*(int *)(local_e * 2 + 0x5fc) == 0) {
          local_10 = local_10 + 1;
        }
        if (local_e == local_18) break;
        local_e = local_e + 1;
      }
    }
    local_12 = local_18;
    if ((local_10 * 2 - local_18 == 0 || local_10 * 2 < (int)local_18) || (local_10 < 2)) {
      iVar3 = FUN_1b5a_0ff6(*(int *)0x8a6 + 2);
      if (iVar3 == 0) {
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
        local_14 = FUN_1b5a_0ff6(0x20);
      } while (*(int *)(local_14 * 2 + 0x64e) != 0);
    }
    else {
      do {
        iVar3 = FUN_1b5a_0ff6(local_12);
        local_10 = iVar3 + 1;
      } while (*(int *)(local_10 * 2 + 0x5fc) != 0);
      *(undefined1 *)0x9b2 = *(undefined1 *)(iVar3 + 0x6a5);
      for (local_14 = 0; *(char *)(local_14 + 0xbd) != *(char *)0x9b2; local_14 = local_14 + 1) {
      }
    }
    iVar3 = *(int *)(*(int *)0x8a4 * 2 + 0xac) / 8;
    local_6 = iVar3 + 0x1c20;
    FUN_1000_0727(0x14,0x28,iVar3 + -0x66e0,local_6);
    FUN_1000_6696(2,0x5a,*(undefined2 *)(*(int *)0x8a4 * 2 + 0xac),0,0xa000,
                  (int)*(undefined4 *)0xaf2,(int)((ulong)*(undefined4 *)0xaf2 >> 0x10));
    puVar5 = local_216;
    uVar6 = unaff_SS;
    FUN_1b5a_062a(0x1dc9,0x1b5a);
    puVar4 = local_116;
    FUN_1b5a_075a(CONCAT11((char)((uint)(local_14 + 1) >> 8),*(undefined1 *)(local_14 + 0xbd)));
    FUN_1b5a_06b7(puVar4,unaff_SS);
    FUN_1b5a_06b7(0x1dd1,0x1b5a);
    FUN_1000_03a7(0,0xa000,8,0xd,0,0x62,*(int *)(*(int *)0x8a4 * 2 + 0xac) + 6,puVar5,uVar6);
    FUN_1000_0ab4(0x28);
    FUN_1000_0727(0x14,0x28,local_6,local_6 + 32000);
  }
  else {
    FUN_1000_0780(*(int *)0x8a4 + -1);
    local_6 = 0x59b0;
    FUN_1000_0727(0x50,0x3c,0xd6b0,0x59b0);
    if (0 < *(int *)0x7fc) {
      *(undefined2 *)0xa42 = 4;
      *(undefined2 *)0xa46 = 0x140;
      *(undefined2 *)0xa48 = 100;
      FUN_1af1_000b(0xa42);
    }
    local_14 = 0;
    local_16 = 0;
    FUN_1000_09da();
    local_4 = 48000;
    local_a = local_14 * 0x14;
    local_c = 0x13a;
    local_8 = (local_a >> 3) + 0x6220;
    do {
      local_6 = (local_a >> 3) + local_c * 0x50;
      FUN_1000_0727(3,0x1a,local_4,local_6 + 32000);
      FUN_1000_6696(2,local_c,local_a,32000,0xa000,(int)*(undefined4 *)0xaca,
                    (int)((ulong)*(undefined4 *)0xaca >> 0x10));
      FUN_1000_0727(3,0x1a,local_6,local_6 + 32000);
      FUN_1000_0727(3,0x1a,local_8,local_8 + 32000);
      local_8 = local_6;
      FUN_1000_0727(3,0x1a,local_6 + 32000,local_4);
      *(undefined1 *)0x9b2 = 7;
      cVar1 = FUN_1af8_02fa();
      if (cVar1 != '\0') {
        uVar2 = FUN_1af8_030c();
        *(undefined1 *)0x9b2 = uVar2;
      }
      if (*(char *)0x9b2 == '\x13') {
        *(int *)0x8b0 = 1 - *(int *)0x8b0;
      }
      if (*(char *)0x9b2 == '\t') {
        FUN_1000_0a15();
      }
      if (*(char *)0x9b2 == '\0') {
        uVar2 = FUN_1af8_030c();
        *(undefined1 *)0x9b2 = uVar2;
        if (*(char *)0x9b2 == 'K') {
          local_14 = local_14 + -1;
        }
        if (*(char *)0x9b2 == 'M') {
          local_14 = local_14 + 1;
        }
      }
      if (0 < *(int *)0x7fc) {
        *(undefined2 *)0xa42 = 3;
        FUN_1af1_000b(0xa42);
        if (*(uint *)0xa46 < 0x131) {
          local_14 = local_14 + -1;
          *(undefined2 *)0xa42 = 4;
          *(undefined2 *)0xa46 = 0x140;
          *(undefined2 *)0xa48 = 100;
          FUN_1af1_000b(0xa42);
        }
        if (0x14f < *(uint *)0xa46) {
          local_14 = local_14 + 1;
          *(undefined2 *)0xa42 = 4;
          *(undefined2 *)0xa46 = 0x140;
          *(undefined2 *)0xa48 = 100;
          FUN_1af1_000b(0xa42);
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
      if (*(char *)0x9b2 == '\x1b') {
        FUN_1000_0000();
      }
      if ((*(char *)0x9b2 == ' ') || ((0 < *(int *)0x7fc && (*(int *)0xa44 == 1)))) {
        if (*(int *)(local_14 * 2 + 0x64e) == 0) {
          local_16 = 1;
        }
        else {
          FUN_1af8_02c6(*(int *)0x8b0 * 1000);
          FUN_1af8_029e(0x32);
          FUN_1af8_02f3();
        }
      }
      FUN_1af8_029e(0x1e);
    } while (local_16 < 1);
    FUN_1af8_02c6(*(int *)0x8b0 * 100);
    FUN_1000_0727(3,0x1a,local_6,local_6 + 32000);
    FUN_1af8_02f3();
  }
  FUN_1000_1cd2(local_14);
  *(undefined1 *)0x7f8 = *(undefined1 *)(local_14 + 0xbd);
  *(undefined2 *)0x5fc = 0;
  local_18 = (uint)*(byte *)0x6a4;
  if (local_18 != 0) {
    local_e = 1;
    while( true ) {
      if ((*(char *)(local_e + 0x6a4) == *(char *)0x7f8) && (*(int *)(local_e * 2 + 0x5fc) == 0)) {
        *(int *)0x5fc = *(int *)0x5fc + 1;
        *(uint *)(*(int *)0x5fc * 2 + 0x624) = local_e;
        *(undefined2 *)(local_e * 2 + 0x5fc) = 1;
      }
      if (local_e == local_18) break;
      local_e = local_e + 1;
    }
  }
  if (1 < *(int *)0x8a4) {
    FUN_1000_086b(*(int *)0x8a4 + -1);
  }
  FUN_1000_12aa(3);
  FUN_1000_0ab4(0x28);
  FUN_1000_0b92();
  return;
}



/* 1000:229a FUN_1000_229a */

void __cdecl16near FUN_1000_229a(void)

{
  uint uVar1;
  char cVar2;
  undefined1 uVar3;
  int iVar4;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar5;
  undefined1 local_11a [254];
  uint local_1c;
  undefined1 local_1a [4];
  int local_16;
  uint local_14;
  uint local_e;
  int local_c;
  uint local_a;
  int local_8;
  int local_6;
  undefined2 local_4;
  
  if (*(int *)0x8a4 < 2) {
    do {
      iVar4 = FUN_1b5a_0ff6(*(undefined1 *)0x6a4);
      local_14 = iVar4 + 1;
    } while (*(int *)(local_14 * 2 + 0x5fc) != 0);
    if (1 < *(int *)0x8a4) {
      FUN_1000_086b(*(int *)0x8a4 + -1);
    }
    iVar4 = *(int *)(*(int *)0x8a4 * 2 + 0xac) / 8;
    local_6 = iVar4 + 0x1c20;
    FUN_1000_0727(0x14,0x28,iVar4 + -0x66e0,local_6);
    FUN_1000_6696(2,0x5a,*(undefined2 *)(*(int *)0x8a4 * 2 + 0xac),0,0xa000,
                  (int)*(undefined4 *)0xaf2,(int)((ulong)*(undefined4 *)0xaf2 >> 0x10));
    FUN_1b5a_119c(2,local_1a,unaff_SS,0,local_14,(int)local_14 >> 0xf);
    puVar5 = local_11a;
    FUN_1b5a_062a(local_1a,unaff_SS);
    FUN_1b5a_06b7(0x2291,0x1b5a);
    FUN_1000_03a7(0,0xa000,8,0xd,0,0x62,*(int *)(*(int *)0x8a4 * 2 + 0xac) + 6,puVar5,unaff_SS);
    FUN_1000_0ab4(0x28);
    FUN_1000_0727(0x14,0x28,local_6,local_6 + 32000);
  }
  else {
    FUN_1000_0780(*(int *)0x8a4 + -1);
    local_6 = 800;
    FUN_1000_0727(0x50,0x3c,0x8020,800);
    if (0 < *(int *)0x7fc) {
      *(undefined2 *)0xa42 = 4;
      *(undefined2 *)0xa46 = 0x140;
      *(undefined2 *)0xa48 = 100;
      FUN_1af1_000b(0xa42);
    }
    local_14 = 1;
    local_16 = 0;
    FUN_1000_09da();
    local_4 = 48000;
    local_a = local_14 * 0x10 + 200;
    local_c = 0xc;
    local_8 = (local_a >> 3) + 0x3c0;
    do {
      local_6 = (local_a >> 3) + local_c * 0x50;
      FUN_1000_0727(3,0x1a,local_4,local_6 + 32000);
      FUN_1000_6696(2,local_c,local_a,32000,0xa000,(int)*(undefined4 *)0xaca,
                    (int)((ulong)*(undefined4 *)0xaca >> 0x10));
      FUN_1000_0727(3,0x1a,local_6,local_6 + 32000);
      FUN_1000_0727(3,0x1a,local_8,local_8 + 32000);
      local_8 = local_6;
      FUN_1000_0727(3,0x1a,local_6 + 32000,local_4);
      *(undefined1 *)0x9b2 = 7;
      cVar2 = FUN_1af8_02fa();
      if (cVar2 != '\0') {
        uVar3 = FUN_1af8_030c();
        *(undefined1 *)0x9b2 = uVar3;
      }
      if (*(char *)0x9b2 == '\x13') {
        *(int *)0x8b0 = 1 - *(int *)0x8b0;
      }
      if (*(char *)0x9b2 == '\t') {
        FUN_1000_0a15();
      }
      if (*(char *)0x9b2 == '\0') {
        uVar3 = FUN_1af8_030c();
        *(undefined1 *)0x9b2 = uVar3;
        if (*(char *)0x9b2 == 'K') {
          local_14 = local_14 - 1;
        }
        if (*(char *)0x9b2 == 'M') {
          local_14 = local_14 + 1;
        }
      }
      if (0 < *(int *)0x7fc) {
        *(undefined2 *)0xa42 = 3;
        FUN_1af1_000b(0xa42);
        if (*(uint *)0xa46 < 0x131) {
          local_14 = local_14 - 1;
          *(undefined2 *)0xa42 = 4;
          *(undefined2 *)0xa46 = 0x140;
          *(undefined2 *)0xa48 = 100;
          FUN_1af1_000b(0xa42);
        }
        if (0x14f < *(uint *)0xa46) {
          local_14 = local_14 + 1;
          *(undefined2 *)0xa42 = 4;
          *(undefined2 *)0xa46 = 0x140;
          *(undefined2 *)0xa48 = 100;
          FUN_1af1_000b(0xa42);
        }
      }
      if ((int)local_14 < 1) {
        local_14 = 1;
      }
      if ((int)(uint)*(byte *)0x6a4 < (int)local_14) {
        local_14 = (uint)*(byte *)0x6a4;
      }
      local_a = local_14 * 0x10 + 200;
      local_c = 0xc;
      if (*(char *)0x9b2 == '\x1b') {
        FUN_1000_0000();
      }
      if ((*(char *)0x9b2 == ' ') || ((0 < *(int *)0x7fc && (*(int *)0xa44 == 1)))) {
        if (*(int *)(local_14 * 2 + 0x5fc) == 0) {
          local_16 = 1;
        }
        else {
          FUN_1af8_02c6(*(int *)0x8b0 * 1000);
          FUN_1af8_029e(0x32);
          FUN_1af8_02f3();
        }
      }
      FUN_1af8_029e(0x1e);
    } while (local_16 < 1);
    FUN_1af8_02c6(*(int *)0x8b0 * 100);
    FUN_1000_0727(3,0x1a,local_6,local_6 + 32000);
    FUN_1af8_02f3();
  }
  *(undefined1 *)0x7f8 = *(undefined1 *)(local_14 + 0x6a4);
  *(undefined2 *)0x5fc = 0;
  local_1c = (uint)*(byte *)0x6a4;
  if (local_1c != 0) {
    local_e = 1;
    while( true ) {
      if ((*(char *)(local_e + 0x6a4) == *(char *)0x7f8) && (*(int *)(local_e * 2 + 0x5fc) == 0)) {
        *(int *)0x5fc = *(int *)0x5fc + 1;
        *(uint *)(*(int *)0x5fc * 2 + 0x624) = local_e;
        *(undefined2 *)(local_e * 2 + 0x5fc) = 1;
      }
      if (local_e == local_1c) break;
      local_e = local_e + 1;
    }
  }
  local_e = 0;
  uVar1 = local_e;
  do {
    local_e = uVar1;
    uVar1 = local_e + 1;
  } while (*(char *)0x7f8 != *(char *)(local_e + 0xbd));
  FUN_1000_1cd2(local_e);
  return;
}



/* 1000:26ba FUN_1000_26ba */

byte FUN_1000_26ba(undefined1 param_1)

{
  byte bVar1;
  undefined2 unaff_DS;
  int local_6;
  byte local_4;
  
  local_4 = 0x20;
  bVar1 = FUN_1b5a_1893(param_1);
  if (bVar1 < 0x80) {
    local_6 = 1;
    while( true ) {
      if (*(byte *)(local_6 + 0x2b6) == bVar1) {
        local_4 = *(byte *)(local_6 + 0x2d8);
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



/* 1000:274b FUN_1000_274b */

undefined1 __cdecl16near FUN_1000_274b(void)

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
  undefined1 local_312 [256];
  undefined1 local_212 [254];
  int local_114;
  undefined1 local_110 [256];
  int local_10;
  int local_e;
  int local_c;
  uint local_a;
  int local_8;
  int local_6;
  
  local_6 = (*(int *)(*(int *)0x8a4 * 2 + 0xb0) + -1) / 8 +
            (*(int *)(*(int *)0x8a4 * 2 + 0xb4) + -0x1f) * 0x50;
  FUN_1000_0727(0x10,0x1e,0x6da0,local_6);
  FUN_1000_068d(7,0x10,0x1e,local_6);
  out(0x3ce,5);
  out(0x3cf,0);
  FUN_17cc_149e(0);
  local_c = *(int *)(*(int *)0x8a4 * 2 + 0xb0) + -8;
  local_e = *(int *)(*(int *)0x8a4 * 2 + 0xb4) + -0x1c;
  local_114 = *(byte *)0x6a4 + 1;
  local_a = 0;
  while (FUN_17cc_0b55(local_e + 0x1a,local_c + 8 + local_a * 8,local_e,local_a * 8 + local_c),
        local_a != local_114) {
    local_a = local_a + 1;
  }
  FUN_1000_068d(7,*(byte *)0x6a4 + 1,0xf,local_6 + 0x2d1);
  local_10 = local_e + 7;
  local_8 = local_10 * 0x50 + *(int *)(*(int *)0x8a4 * 2 + 0xb0) / 8;
  local_a = 0;
  local_e = 0;
  local_110[0] = 0;
  do {
    *(undefined1 *)0x9b2 = 7;
    iVar2 = FUN_1af8_02fa();
    if ((char)iVar2 != '\0') {
      iVar2 = FUN_1af8_030c();
      *(undefined1 *)0x9b2 = (char)iVar2;
    }
    if (*(char *)0x9b2 == '\x13') {
      iVar2 = 1 - *(int *)0x8b0;
      *(int *)0x8b0 = iVar2;
    }
    uVar1 = (undefined1)((uint)iVar2 >> 8);
    if (*(char *)0x9b2 == '\t') {
      FUN_1000_0a15();
      uVar1 = extraout_AH;
    }
    if (*(char *)0x9b2 == '\x1b') {
      FUN_1000_0000();
      uVar1 = extraout_AH_00;
    }
    if ((*(char *)0x9b2 == '\b') && (0 < local_e)) {
      FUN_1b5a_07db(1,local_e,local_110,unaff_SS);
      FUN_1000_068d(7,1,0xd,local_8 + local_e);
      local_e = local_e + -1;
      FUN_1000_068d(7,1,0xd,local_8 + local_e);
      uVar1 = extraout_AH_01;
    }
    if (0x20 < *(byte *)0x9b2) {
      uVar1 = FUN_1000_26ba(CONCAT11(uVar1,*(undefined1 *)0x9b2));
      *(undefined1 *)0x9b2 = uVar1;
    }
    if ((0x20 < *(byte *)0x9b2) && (local_e < (int)(uint)*(byte *)0x6a4)) {
      FUN_1000_068d(7,1,0xd,local_8 + local_e);
      puVar5 = local_212;
      uVar4 = unaff_SS;
      FUN_1b5a_075a(CONCAT11(extraout_AH_02,*(undefined1 *)0x9b2));
      FUN_1000_03a7(0,0xa000,8,0xd,0,local_10,local_e * 8 + *(int *)(*(int *)0x8a4 * 2 + 0xb0),
                    puVar5,uVar4);
      puVar5 = local_312;
      uVar6 = unaff_SS;
      FUN_1b5a_062a(local_110,unaff_SS);
      puVar3 = local_212;
      uVar4 = unaff_SS;
      FUN_1b5a_075a(CONCAT11(extraout_AH_03,*(undefined1 *)0x9b2));
      FUN_1b5a_06b7(puVar3,uVar4);
      FUN_1b5a_0644(0xff,local_110,unaff_SS,puVar5,uVar6);
      local_e = local_e + 1;
    }
    FUN_1af8_029e(0x19);
    local_a = local_a + 1;
    if (0x27 < (int)local_a) {
      local_a = 0;
    }
    FUN_1000_068d(((int)local_a / 0x14) * 7,1,2,local_8 + local_e + 800);
  } while (*(char *)0x9b2 != '\r');
  FUN_1b5a_0644(0x14,0x68e,unaff_DS,local_110,unaff_SS);
  FUN_1000_0727(0x10,0x1e,local_6,0x6da0);
  uVar1 = 0;
  if (*(char *)0x68e == *(char *)0x6a4) {
    if (*(byte *)0x6a4 != 0) {
      local_a = 1;
      while( true ) {
        if (*(char *)(local_a + 0x68e) != *(char *)(local_a + 0x6a4)) {
          uVar1 = 1;
        }
        if (local_a == *(byte *)0x6a4) break;
        local_a = local_a + 1;
      }
    }
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}



/* 1000:2a82 FUN_1000_2a82 */

void FUN_1000_2a82(int param_1)

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
  undefined1 local_20e [258];
  undefined1 local_10c [256];
  int local_c;
  int local_a;
  int local_6;
  int local_4;
  
  local_a = 0;
  local_10c[0] = 0;
  local_c = *(int *)(param_1 * 2 + 0xb0) + 8;
  local_4 = local_c / 8 + (*(int *)(param_1 * 2 + 0xb4) + 0x5e) * 0x50;
  local_6 = 0;
  do {
    *(undefined1 *)0x9b2 = 7;
    iVar2 = FUN_1af8_02fa();
    if ((char)iVar2 != '\0') {
      iVar2 = FUN_1af8_030c();
      *(undefined1 *)0x9b2 = (char)iVar2;
    }
    if (*(char *)0x9b2 == '\x13') {
      iVar2 = 1 - *(int *)0x8b0;
      *(int *)0x8b0 = iVar2;
    }
    uVar1 = (undefined1)((uint)iVar2 >> 8);
    if (*(char *)0x9b2 == '\t') {
      FUN_1000_0a15();
      uVar1 = extraout_AH;
    }
    if (*(char *)0x9b2 == '\x1b') {
      FUN_1000_0000();
      uVar1 = extraout_AH_00;
    }
    if ((*(char *)0x9b2 == '\b') && (0 < local_a)) {
      FUN_1b5a_07db(1,local_a,local_10c,unaff_SS);
      FUN_1000_068d(7,1,0xd,local_4 + local_a);
      local_a = local_a + -1;
      FUN_1000_068d(7,1,0xd,local_4 + local_a);
      uVar1 = extraout_AH_01;
    }
    if (0x20 < *(byte *)0x9b2) {
      uVar1 = FUN_1000_26ba(CONCAT11(uVar1,*(undefined1 *)0x9b2));
      *(undefined1 *)0x9b2 = uVar1;
    }
    if ((0x1f < *(byte *)0x9b2) && (local_a < 10)) {
      FUN_1000_068d(7,1,0xd,local_4 + local_a);
      puVar5 = local_20e;
      uVar4 = unaff_SS;
      FUN_1b5a_075a(CONCAT11(extraout_AH_02,*(undefined1 *)0x9b2));
      FUN_1000_03a7(0,0xa000,8,0xd,0,*(int *)(param_1 * 2 + 0xb4) + 0x5e,local_a * 8 + local_c,
                    puVar5,uVar4);
      puVar5 = local_30e;
      uVar6 = unaff_SS;
      FUN_1b5a_062a(local_10c,unaff_SS);
      puVar3 = local_20e;
      uVar4 = unaff_SS;
      FUN_1b5a_075a(CONCAT11(extraout_AH_03,*(undefined1 *)0x9b2));
      FUN_1b5a_06b7(puVar3,uVar4);
      FUN_1b5a_0644(0xff,local_10c,unaff_SS,puVar5,uVar6);
      local_a = local_a + 1;
    }
    FUN_1af8_029e(0x19);
    local_6 = local_6 + 1;
    if (0x27 < local_6) {
      local_6 = 0;
    }
    FUN_1000_068d((local_6 / 0x14) * 7,1,2,local_4 + local_a + 800);
  } while (*(char *)0x9b2 != '\r');
  FUN_1000_068d(7,1,2,local_4 + local_a + 800);
  FUN_1b5a_0644(10,param_1 * 0xb + 0x6cb,unaff_DS,local_10c,unaff_SS);
  return;
}



/* 1000:2c8e FUN_1000_2c8e */

void __cdecl16near FUN_1000_2c8e(void)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 local_86 [128];
  uint local_6;
  uint local_4;
  
  FUN_1b5a_161f(0x2c85,0x1000,local_86,unaff_SS);
  FUN_1b5a_164d(0x15,local_86,unaff_SS);
  FUN_1b5a_020e();
  FUN_1b5a_1702(0x6ba,unaff_DS);
  FUN_1b5a_020e();
  local_6 = FUN_1b5a_11e7(&local_4,unaff_SS,0x6ba,unaff_DS);
  do {
    do {
      iVar2 = FUN_1b5a_0ff6(local_6);
      uVar3 = iVar2 + 1;
      local_4 = uVar3;
    } while (*(uint *)0x6d0 == uVar3);
  } while ((*(uint *)0x6d2 == uVar3) || (*(uint *)0x6d4 == uVar3));
  *(uint *)(*(int *)0x8a6 * 2 + 0x6d0) = uVar3;
  local_6 = uVar3;
  if (0 < (int)uVar3) {
    local_4 = 1;
    while( true ) {
      FUN_1b5a_1702(0x6a4,unaff_DS);
      FUN_1b5a_020e();
      FUN_1b5a_1702(0x6ba,unaff_DS);
      FUN_1b5a_020e();
      if (local_4 == uVar3) break;
      local_4 = local_4 + 1;
    }
  }
  FUN_1b5a_16ce(local_86,unaff_SS);
  FUN_1b5a_020e();
  bVar1 = *(byte *)0x6a4;
  if (bVar1 != 0) {
    for (local_4 = 1; *(char *)(local_4 + 0x6a4) = *(char *)(local_4 + 0x6a4) + -0x20,
        local_4 != bVar1; local_4 = local_4 + 1) {
    }
  }
  bVar1 = *(byte *)0x6ba;
  if (bVar1 != 0) {
    for (local_4 = 1; *(char *)(local_4 + 0x6ba) = *(char *)(local_4 + 0x6ba) + -0x20,
        local_4 != bVar1; local_4 = local_4 + 1) {
    }
  }
  return;
}



/* 1000:2deb FUN_1000_2deb */

void __cdecl16near FUN_1000_2deb(void)

{
  undefined4 uVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  undefined2 in_BX;
  undefined2 unaff_DS;
  undefined2 local_4;
  
  uVar1 = *(undefined4 *)(((*(int *)0x9be + 3) % 4) * 4 + 0xa56);
  FUN_1000_6696(3,0x9a,0x80,0,0xa000,(int)uVar1,(int)((ulong)uVar1 >> 0x10));
  local_4 = 0;
  while( true ) {
    iVar4 = local_4 * 2 + *(int *)0x9be >> 0xf;
    FUN_1b5a_0b5f();
    FUN_1b5a_0b4b();
    uVar2 = FUN_1b5a_0b51();
    FUN_1b5a_0c6f(0x1b5a,uVar2,in_BX,iVar4);
    FUN_1b5a_0b4b();
    iVar4 = FUN_1b5a_0b6b();
    FUN_1b5a_0c82();
    FUN_1b5a_0b4b();
    iVar3 = FUN_1b5a_0b6b();
    uVar1 = *(undefined4 *)(*(int *)(local_4 * 2 + 0x6a) * 4 + 0xa56);
    FUN_1000_6696(7,iVar3 + 0xeb,iVar4 + 0xe5,0,0xa000,(int)uVar1,(int)((ulong)uVar1 >> 0x10));
    if (local_4 == 0xf) break;
    local_4 = local_4 + 1;
  }
  FUN_1000_6696(7,0xbf,0xeb,0,0xa000,(int)*(undefined4 *)0xa96,
                (int)((ulong)*(undefined4 *)0xa96 >> 0x10));
  return;
}



/* 1000:2f07 FUN_1000_2f07 */

void __cdecl16near FUN_1000_2f07(void)

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
        *(int *)0x9be = *(int *)0x9be + 1;
        bVar8 = true;
      }
      else if (local_c == 3) {
        bVar8 = local_8 % 2 == 0;
        if (bVar8) {
          *(int *)0x9be = *(int *)0x9be + 1;
        }
      }
      else if (local_c == 2) {
        bVar8 = local_8 % 3 == 0;
        if (bVar8) {
          *(int *)0x9be = *(int *)0x9be + 1;
        }
      }
      else if ((local_c == 1) && (local_8 % 4 == 0)) {
        bVar8 = true;
        *(int *)0x9be = *(int *)0x9be + 1;
      }
    }
    if (((local_c == 0) && (local_a != 0)) && (*(int *)0x9be % 2 == 1)) {
      *(int *)0x9be = *(int *)0x9be + 1;
    }
    if (0x1f < *(int *)0x9be) {
      *(int *)0x9be = *(int *)0x9be + -0x20;
    }
    FUN_1000_0727(0x1c,0x27,0xad30,28000);
    FUN_1000_068d(7,0x1c,0x84,0xb9b0);
    uVar1 = *(undefined4 *)(((*(int *)0x9be + 3) % 4) * 4 + 0xa56);
    FUN_1000_6696(3,0x9a,0x80,32000,0xa000,(int)uVar1,(int)((ulong)uVar1 >> 0x10));
    if (bVar8) {
      uVar4 = FUN_1b5a_0279();
      FUN_1af8_02c6(uVar4);
    }
    local_4 = 0;
    while( true ) {
      uVar7 = 0;
      iVar6 = ((int)*(uint *)0x9be >> 0xf) + (uint)CARRY2(*(uint *)0x9be,local_4 << 1);
      FUN_1b5a_0b5f();
      FUN_1b5a_0b4b();
      uVar4 = FUN_1b5a_0b51();
      FUN_1b5a_0c6f(0x1b5a,uVar4,uVar7,iVar6);
      FUN_1b5a_0b4b();
      iVar6 = FUN_1b5a_0b6b();
      FUN_1b5a_0c82();
      FUN_1b5a_0b4b();
      iVar5 = FUN_1b5a_0b6b();
      uVar1 = *(undefined4 *)(*(int *)(local_4 * 2 + 0x6a) * 4 + 0xa56);
      FUN_1000_6696(7,iVar5 + 0xeb,iVar6 + 0xe5,32000,0xa000,(int)uVar1,(int)((ulong)uVar1 >> 0x10))
      ;
      FUN_1af8_02f3();
      if (local_4 == 0xf) break;
      local_4 = local_4 + 1;
    }
    FUN_1af8_02f3();
    if (local_c != 0) {
      local_8 = local_8 + 1;
    }
    if (local_a < local_8) {
      iVar6 = FUN_1b5a_0ff6(10);
      local_a = iVar6 + 5;
      if (local_c != 0) {
        local_c = local_c + -1;
      }
      local_8 = 0;
    }
    FUN_1000_6696(7,0xbf,0xeb,32000,0xa000,(int)*(undefined4 *)0xa96,
                  (int)((ulong)*(undefined4 *)0xa96 >> 0x10));
    FUN_1000_0727(0x1c,0xac,0x3030,0xad30);
    *(undefined1 *)0x9b2 = 7;
    cVar2 = FUN_1af8_02fa();
    if (cVar2 != '\0') {
      uVar3 = FUN_1af8_030c();
      *(undefined1 *)0x9b2 = uVar3;
    }
    if (*(char *)0x9b2 == '\x13') {
      *(int *)0x8b0 = 1 - *(int *)0x8b0;
    }
    if (*(char *)0x9b2 == '\t') {
      FUN_1000_0a15();
    }
    if (0 < *(int *)0x7fc) {
      *(undefined2 *)0xa42 = 3;
      FUN_1af1_000b(0xa42);
    }
    if ((local_c == 0) && (local_a == 0)) {
      if (*(int *)0x8a4 < 2) {
        FUN_1000_0ab4(0x32);
      }
      FUN_1000_0b92();
      local_c = 4;
      iVar6 = FUN_1b5a_0ff6(0x14);
      local_a = iVar6 + 10;
    }
    if (*(char *)0x9b2 == '\x1b') {
      FUN_1000_0000();
    }
  } while (((local_c != 0) || (local_a == 0)) || (*(int *)0x9be % 2 != 0));
  *(int *)0x9c0 = (0x1c - *(int *)0x9be / 2) % 0x10;
  *(undefined2 *)0x896 = *(undefined2 *)((*(int *)(*(int *)0x9c0 * 2 + 0x6a) + -4) * 2 + 0x8a);
  local_e = 1;
  while( true ) {
    FUN_1af8_02c6((local_e * -0x1e + 1000) * *(int *)0x8b0);
    FUN_1af8_029e(local_e / 5);
    FUN_1af8_029e(local_e / 3);
    FUN_1af8_02f3();
    if (local_e == 0x1e) break;
    local_e = local_e + 1;
  }
  return;
}



/* 1000:32bd FUN_1000_32bd */

void FUN_1000_32bd(int param_1)

{
  undefined4 uVar1;
  bool bVar2;
  char cVar3;
  undefined1 uVar4;
  int iVar5;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  int local_c;
  int local_a;
  int local_4;
  
  iVar5 = *(int *)(*(int *)0x8a4 * 2 + 0xb4) * 0x50 + (*(int *)(*(int *)0x8a4 * 2 + 0xb0) + -1) / 8;
  bVar2 = false;
  local_a = 1;
  if (0 < *(int *)0x7fc) {
    *(undefined2 *)0xa42 = 4;
    *(undefined2 *)0xa46 = 0x140;
    *(undefined2 *)0xa48 = 100;
    FUN_1af1_000b(0xa42);
  }
  FUN_1000_09da();
  do {
    *(undefined1 *)0x9b2 = 7;
    cVar3 = FUN_1af8_02fa();
    if (cVar3 != '\0') {
      uVar4 = FUN_1af8_030c();
      *(undefined1 *)0x9b2 = uVar4;
    }
    if (*(char *)0x9b2 == '\t') {
      FUN_1000_0a15();
    }
    if (*(char *)0x9b2 == '\x13') {
      *(int *)0x8b0 = 1 - *(int *)0x8b0;
    }
    if (*(char *)0x9b2 == '\0') {
      uVar4 = FUN_1af8_030c();
      *(undefined1 *)0x9b2 = uVar4;
      if (*(char *)0x9b2 == 'K') {
        local_c = local_a + -1;
      }
      if (*(char *)0x9b2 == 'M') {
        local_c = local_a + 1;
      }
    }
    if (0 < *(int *)0x7fc) {
      *(undefined2 *)0xa42 = 3;
      FUN_1af1_000b(0xa42);
      if (*(uint *)0xa46 < 300) {
        local_c = local_a + -1;
        *(undefined2 *)0xa42 = 4;
        *(undefined2 *)0xa46 = 0x140;
        *(undefined2 *)0xa48 = 100;
        FUN_1af1_000b(0xa42);
      }
      if (0x154 < *(uint *)0xa46) {
        local_c = local_a + 1;
        *(undefined2 *)0xa42 = 4;
        *(undefined2 *)0xa46 = 0x140;
        *(undefined2 *)0xa48 = 100;
        FUN_1af1_000b(0xa42);
      }
    }
    if (1 < local_c) {
      local_c = 1;
    }
    if (local_c < 0) {
      local_c = 0;
    }
    if (local_c != local_a) {
      if (local_a == 0) {
        local_4 = 1;
        while( true ) {
          if (local_4 == 1) {
            *(undefined2 *)(param_1 + -6) = 0x15;
          }
          else if (local_4 == 2) {
            *(undefined2 *)(param_1 + -6) = 0x16;
          }
          else if (local_4 == 3) {
            *(undefined2 *)(param_1 + -6) = 0x3b;
          }
          else if (local_4 == 4) {
            *(undefined2 *)(param_1 + -6) = 0x3a;
          }
          else if (local_4 == 5) {
            *(undefined2 *)(param_1 + -6) = 0x39;
          }
          FUN_1000_068d(7,0x10,0x4f,iVar5 + 32000);
          uVar1 = *(undefined4 *)(*(int *)(param_1 + -6) * 4 + 0xa56);
          FUN_1000_6696(2,*(undefined2 *)(*(int *)0x8a4 * 2 + 0xb4),
                        *(undefined2 *)(*(int *)0x8a4 * 2 + 0xb0),32000,0xa000,(int)uVar1,
                        (int)((ulong)uVar1 >> 0x10));
          FUN_1000_0727(0x10,0x4f,iVar5,iVar5 + 32000);
          FUN_1af8_029e(100);
          if (local_4 == 5) break;
          local_4 = local_4 + 1;
        }
      }
      else {
        local_4 = 1;
        while( true ) {
          if (local_4 == 1) {
            *(undefined2 *)(param_1 + -6) = 0x39;
          }
          else if (local_4 == 2) {
            *(undefined2 *)(param_1 + -6) = 0x3a;
          }
          else if (local_4 == 3) {
            *(undefined2 *)(param_1 + -6) = 0x3b;
          }
          else if (local_4 == 4) {
            *(undefined2 *)(param_1 + -6) = 0x16;
          }
          else if (local_4 == 5) {
            *(undefined2 *)(param_1 + -6) = 0x15;
          }
          FUN_1000_068d(7,0x10,0x4f,iVar5 + 32000);
          uVar1 = *(undefined4 *)(*(int *)(param_1 + -6) * 4 + 0xa56);
          FUN_1000_6696(2,*(undefined2 *)(*(int *)0x8a4 * 2 + 0xb4),
                        *(undefined2 *)(*(int *)0x8a4 * 2 + 0xb0),32000,0xa000,(int)uVar1,
                        (int)((ulong)uVar1 >> 0x10));
          FUN_1000_0727(0x10,0x4f,iVar5,iVar5 + 32000);
          FUN_1af8_029e(100);
          if (local_4 == 5) break;
          local_4 = local_4 + 1;
        }
      }
    }
    if (*(char *)0x9b2 == '\x1b') {
      FUN_1000_0000();
    }
    if ((*(char *)0x9b2 == ' ') || ((0 < *(int *)0x7fc && (*(int *)0xa44 == 1)))) {
      bVar2 = true;
    }
    FUN_1af8_029e(0x1e);
    local_a = local_c;
  } while (!bVar2);
  *(int *)(param_1 + -0xc) = local_c;
  return;
}



/* 1000:3655 FUN_1000_3655 */

int FUN_1000_3655(int param_1)

{
  int iVar1;
  undefined2 uVar2;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar3;
  undefined2 uVar4;
  undefined1 local_20 [2];
  undefined1 local_1e [2];
  undefined1 local_1c [10];
  int local_12;
  int local_10;
  int local_e;
  int local_c;
  int local_8;
  int local_6;
  int local_4;
  
  uVar2 = 0x1000;
  local_c = (*(int *)(*(int *)0x8a4 * 2 + 0xb0) + -8) / 8 +
            (*(int *)(*(int *)0x8a4 * 2 + 0xb4) + -0x3c) * 0x50;
  FUN_1000_0727(0x10,0x3c,0x6d7e,local_c);
  FUN_1000_068d(7,0x10,0x50,local_c + 32000);
  if (param_1 < 4) {
    FUN_1000_6696(2,*(int *)(*(int *)0x8a4 * 2 + 0xb4) + -0x12,
                  *(int *)(*(int *)0x8a4 * 2 + 0xb0) + -8,32000,0xa000,(int)*(undefined4 *)0xac6,
                  (int)((ulong)*(undefined4 *)0xac6 >> 0x10));
    FUN_1000_6696(2,*(int *)(*(int *)0x8a4 * 2 + 0xb4) + -0x12,
                  *(int *)(*(int *)0x8a4 * 2 + 0xb0) + 0x38,32000,0xa000,(int)*(undefined4 *)0xac6,
                  (int)((ulong)*(undefined4 *)0xac6 >> 0x10));
    if (param_1 == 1) {
      puVar3 = local_1e;
      uVar2 = unaff_SS;
      FUN_1b5a_062a(0x3604,0x1000);
      FUN_1000_03a7(32000,0xa000,8,0xd,0,*(int *)(*(int *)0x8a4 * 2 + 0xb4) + -0x2e,
                    *(int *)(*(int *)0x8a4 * 2 + 0xb0) + 4,puVar3,uVar2);
      puVar3 = local_20;
      uVar2 = 0x1b5a;
      uVar4 = unaff_SS;
      FUN_1b5a_062a(0x3612,0x1b5a);
      FUN_1000_03a7(32000,0xa000,8,0xd,0,*(int *)(*(int *)0x8a4 * 2 + 0xb4) + -0x20,
                    *(int *)(*(int *)0x8a4 * 2 + 0xb0) + 4,puVar3,uVar4);
    }
    if (param_1 == 2) {
      puVar3 = local_1c;
      uVar4 = unaff_SS;
      FUN_1b5a_062a(0x3621,uVar2);
      FUN_1000_03a7(32000,0xa000,8,0xd,0,*(int *)(*(int *)0x8a4 * 2 + 0xb4) + -0x2e,
                    *(int *)(*(int *)0x8a4 * 2 + 0xb0) + 10,puVar3,uVar4);
      puVar3 = local_1e;
      uVar2 = 0x1b5a;
      uVar4 = unaff_SS;
      FUN_1b5a_062a(0x362d,0x1b5a);
      FUN_1000_03a7(32000,0xa000,8,0xd,0,*(int *)(*(int *)0x8a4 * 2 + 0xb4) + -0x20,
                    *(int *)(*(int *)0x8a4 * 2 + 0xb0) + 10,puVar3,uVar4);
    }
    if (param_1 == 3) {
      puVar3 = local_1e;
      uVar4 = unaff_SS;
      FUN_1b5a_062a(0x363a,uVar2);
      FUN_1000_03a7(32000,0xa000,8,0xd,0,*(int *)(*(int *)0x8a4 * 2 + 0xb4) + -0x2e,
                    *(int *)(*(int *)0x8a4 * 2 + 0xb0) + 10,puVar3,uVar4);
      puVar3 = local_1e;
      FUN_1b5a_062a(0x3647,0x1b5a);
      FUN_1000_03a7(32000,0xa000,8,0xd,0,*(int *)(*(int *)0x8a4 * 2 + 0xb4) + -0x20,
                    *(int *)(*(int *)0x8a4 * 2 + 0xb0) + 10,puVar3,unaff_SS);
    }
  }
  else {
    FUN_1000_6696(7,*(int *)(*(int *)0x8a4 * 2 + 0xb4) + -0x2e,
                  *(undefined2 *)(*(int *)0x8a4 * 2 + 0xb0),32000,0xa000,(int)*(undefined4 *)0xaea,
                  (int)((ulong)*(undefined4 *)0xaea >> 0x10));
    FUN_1000_6696(7,*(int *)(*(int *)0x8a4 * 2 + 0xb4) + -0x2e,
                  *(int *)(*(int *)0x8a4 * 2 + 0xb0) + 0x38,32000,0xa000,(int)*(undefined4 *)0xaea,
                  (int)((ulong)*(undefined4 *)0xaea >> 0x10));
    FUN_1000_6696(7,*(int *)(*(int *)0x8a4 * 2 + 0xb4) + -0x3c,
                  *(int *)(*(int *)0x8a4 * 2 + 0xb0) + 0x3a,32000,0xa000,(int)*(undefined4 *)0xaee,
                  (int)((ulong)*(undefined4 *)0xaee >> 0x10));
  }
  local_6 = 0x1e;
  while( true ) {
    FUN_1af8_02c6((local_6 * -0x14 + 1000) * *(int *)0x8b0);
    FUN_1000_0727(0x10,local_6 * -2 + 0x3c,local_6 * 0xa0 + local_c,local_c + 32000);
    FUN_1af8_02f3();
    FUN_1af8_029e(local_6);
    if (local_6 == 0) break;
    local_6 = local_6 + -1;
  }
  if (param_1 == 4) {
    FUN_1000_0ab4(100);
    FUN_1000_068d(7,0x10,0x3c,local_c + 32000);
    FUN_1af8_02c6(*(int *)0x8b0 * 1000);
    FUN_1000_6696(7,*(int *)(*(int *)0x8a4 * 2 + 0xb4) + -0x29,
                  *(undefined2 *)(*(int *)0x8a4 * 2 + 0xb0),32000,0xa000,(int)*(undefined4 *)0xae6,
                  (int)((ulong)*(undefined4 *)0xae6 >> 0x10));
    FUN_1af8_02f3();
    FUN_1af8_02c6(*(int *)0x8b0 * 100);
    FUN_1000_6696(7,*(int *)(*(int *)0x8a4 * 2 + 0xb4) + -0x29,
                  *(int *)(*(int *)0x8a4 * 2 + 0xb0) + 0x38,32000,0xa000,(int)*(undefined4 *)0xae6,
                  (int)((ulong)*(undefined4 *)0xae6 >> 0x10));
    FUN_1af8_02f3();
    FUN_1af8_02c6(*(int *)0x8b0 * 500);
    FUN_1000_0727(0x10,0x3c,local_c,local_c + 32000);
    FUN_1af8_02f3();
    FUN_1000_0ab4(0x28);
    iVar1 = FUN_1b5a_0ff6(0x14);
    local_12 = (iVar1 + 10) * 2;
    local_10 = 1;
    local_8 = local_12;
    if (0 < local_12) {
      local_6 = 1;
      while( true ) {
        FUN_1b5a_0ff6(100);
        uVar2 = FUN_1b5a_0279();
        FUN_1af8_02c6(uVar2);
        FUN_1af8_029e(10);
        FUN_1af8_02f3();
        FUN_1af8_029e(0x32);
        if (local_6 % 2 == 0) {
          local_10 = 1 - local_10;
        }
        FUN_1000_068d(7,0x10,0x3c,local_c + 32000);
        if ((bool)((byte)local_6 & 1)) {
          FUN_1000_6696(7,*(int *)(*(int *)0x8a4 * 2 + 0xb4) + -0x24,
                        *(int *)(*(int *)0x8a4 * 2 + 0xb0) + 0x1a,32000,0xa000,
                        (int)*(undefined4 *)0xae6,(int)((ulong)*(undefined4 *)0xae6 >> 0x10));
          FUN_1000_6696(7,*(int *)(*(int *)0x8a4 * 2 + 0xb4) + -0x2e,
                        *(int *)(*(int *)0x8a4 * 2 + 0xb0) + 0x24,32000,0xa000,
                        (int)*(undefined4 *)0xae6,(int)((ulong)*(undefined4 *)0xae6 >> 0x10));
        }
        else {
          FUN_1000_6696(7,*(int *)(*(int *)0x8a4 * 2 + 0xb4) + -0x29,
                        *(undefined2 *)(*(int *)0x8a4 * 2 + 0xb0),32000,0xa000,
                        (int)*(undefined4 *)0xae6,(int)((ulong)*(undefined4 *)0xae6 >> 0x10));
          FUN_1000_6696(7,*(int *)(*(int *)0x8a4 * 2 + 0xb4) + -0x29,
                        *(int *)(*(int *)0x8a4 * 2 + 0xb0) + 0x38,32000,0xa000,
                        (int)*(undefined4 *)0xae6,(int)((ulong)*(undefined4 *)0xae6 >> 0x10));
        }
        FUN_1000_0727(0x10,0x3c,local_c,local_c + 32000);
        if (local_6 == local_12) break;
        local_6 = local_6 + 1;
      }
    }
    FUN_1000_0b92();
    FUN_1000_12aa(6);
  }
  FUN_1000_0780(1);
  FUN_1000_32bd(&stack0xfffe);
  local_c = (*(int *)(*(int *)0x8a4 * 2 + 0xb0) + -8) / 8 +
            (*(int *)(*(int *)0x8a4 * 2 + 0xb4) + -0x3c) * 0x50;
  if (param_1 < 4) {
    FUN_1000_0727(0x10,0x3c,local_c,0x6d7e);
  }
  else {
    FUN_1000_0b92();
    FUN_1000_068d(7,0x10,0x3c,local_c + 32000);
    FUN_1000_6696(7,*(int *)(*(int *)0x8a4 * 2 + 0xb4) + -0x2e,
                  *(undefined2 *)(*(int *)0x8a4 * 2 + 0xb0),32000,0xa000,(int)*(undefined4 *)0xaea,
                  (int)((ulong)*(undefined4 *)0xaea >> 0x10));
    FUN_1000_6696(7,*(int *)(*(int *)0x8a4 * 2 + 0xb4) + -0x2e,
                  *(int *)(*(int *)0x8a4 * 2 + 0xb0) + 0x38,32000,0xa000,(int)*(undefined4 *)0xaea,
                  (int)((ulong)*(undefined4 *)0xaea >> 0x10));
    if (local_10 == 1) {
      FUN_1000_6696(7,*(int *)(*(int *)0x8a4 * 2 + 0xb4) + -0x3c,
                    *(int *)(*(int *)0x8a4 * 2 + 0xb0) + 0x3a,32000,0xa000,(int)*(undefined4 *)0xaee
                    ,(int)((ulong)*(undefined4 *)0xaee >> 0x10));
    }
    else {
      FUN_1000_6696(7,*(int *)(*(int *)0x8a4 * 2 + 0xb4) + -0x3c,
                    *(int *)(*(int *)0x8a4 * 2 + 0xb0) + 2,32000,0xa000,(int)*(undefined4 *)0xaee,
                    (int)((ulong)*(undefined4 *)0xaee >> 0x10));
    }
    FUN_1000_0727(0x10,0x3c,local_c,local_c + 32000);
    if (local_10 == local_e) {
      *(int *)(*(int *)0x8a4 * 2 + 0x89c) = *(int *)(*(int *)0x8a4 * 2 + 0x89c) + 100;
      FUN_1000_12aa(7);
    }
    else {
      FUN_1000_12aa(8);
    }
    FUN_1000_0ab4(0);
    FUN_1000_0727(0x10,0x3c,local_c,0x6d7e);
    FUN_1000_0c00(*(undefined2 *)0x8a4);
  }
  FUN_1000_086b(local_e);
  if (local_e == 1) {
    local_4 = 0;
  }
  else {
    local_4 = param_1;
  }
  return local_4;
}



/* 1000:3f7b FUN_1000_3f7b */

void __cdecl16near FUN_1000_3f7b(void)

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
  
  FUN_17cc_0b9e(7,1);
  FUN_17cc_149e(7);
  FUN_17cc_0b19(3,0,0);
  local_4 = 0;
  while( true ) {
    FUN_17cc_13aa(0x159 - local_4,0x26c - local_4,0x159 - local_4,local_4 + 0x14);
    FUN_1af8_029e(10);
    if (local_4 == 0xa0) break;
    local_4 = local_4 + 1;
  }
  FUN_1000_0ab4(0x28);
  local_4 = 0;
  while( true ) {
    FUN_17cc_1362(0xb9 - local_4,0xb4 - local_4,0x159,0x14);
    FUN_17cc_13aa(0xb9 - local_4,local_4 + 0x1cc,0xb9 - local_4,0xb4 - local_4);
    FUN_17cc_1362(0x159,0x26c,0xb9 - local_4,local_4 + 0x1cc);
    FUN_1af8_029e(5);
    if (local_4 == 0xa0) break;
    local_4 = local_4 + 1;
  }
  FUN_17cc_0b19(0,0,0);
  FUN_17cc_0b9e(7,1);
  FUN_17cc_13aa(0x159,0x26c,0x19,0x14);
  FUN_17cc_0b9e(4,1);
  local_6 = 1;
  while( true ) {
    local_4 = 0;
    while (FUN_17cc_13aa(local_4 * 0x28 + 0x1b,local_6 * 10 + 0x14,local_4 * 0x28 + 0x19,
                         (local_6 + -1) * 10 + 0x14), local_4 != 8) {
      local_4 = local_4 + 1;
    }
    FUN_1af8_029e(10);
    if (local_6 == 0x3c) break;
    local_6 = local_6 + 1;
  }
  local_6 = 1;
  while( true ) {
    local_4 = 0;
    while (FUN_17cc_13aa(local_6 * 8 + 0x19,local_4 * 0x32 + 0x15,(local_6 + -1) * 8 + 0x19,
                         local_4 * 0x32 + 0x13), local_4 != 0xc) {
      local_4 = local_4 + 1;
    }
    FUN_1af8_029e(10);
    if (local_6 == 0x28) break;
    local_6 = local_6 + 1;
  }
  FUN_1000_0ab4(0x32);
  FUN_1000_6696(7,0x3c,0x5a,0,0xa000,(int)*(undefined4 *)0xb0e,
                (int)((ulong)*(undefined4 *)0xb0e >> 0x10));
  FUN_1000_6696(7,0x3c,0x118,0,0xa000,(int)*(undefined4 *)0xb12,
                (int)((ulong)*(undefined4 *)0xb12 >> 0x10));
  FUN_1000_0ab4(0x32);
  uVar1 = 0x1b5a;
  FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x3dee,0x1af8);
  local_c = (uint)*(byte *)0x8b2;
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
          FUN_1b5a_075a(*(undefined1 *)(local_8 + 0x8b2));
          FUN_1000_03a7(0,0xa000,8,0xd,0,local_6 + 0xee,local_8 * 0x32 + local_4 + local_a,puVar2,
                        uVar1);
          if (local_6 == 2) break;
          local_6 = local_6 + 1;
        }
        if (local_4 == 1) break;
        local_4 = local_4 + 1;
      }
      FUN_1af8_02c6(*(int *)0x8b0 * local_8 * 100);
      local_4 = 0;
      while( true ) {
        puVar2 = local_10c;
        uVar1 = unaff_SS;
        FUN_1b5a_075a(*(undefined1 *)(local_8 + 0x8b2));
        FUN_1000_03a7(0,0xa000,8,0xd,0xf,local_4 + 0xee,local_8 * 0x32 + local_a,puVar2,uVar1);
        if (local_4 == 1) break;
        local_4 = local_4 + 1;
      }
      FUN_1af8_02f3();
      uVar1 = 0x1af8;
      FUN_1af8_029e(0xfa);
      if (local_8 == local_c) break;
      local_8 = local_8 + 1;
    }
  }
  FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x3dfb,uVar1);
  FUN_1000_03a7(0,0xa000,8,7,7,2,0x44,0x8b2,unaff_DS);
  FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x3e3b,0x1b5a);
  FUN_1000_03a7(0,0xa000,8,7,7,0xc,0xb0,0x8b2,unaff_DS);
  FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x3e62,0x1b5a);
  FUN_1000_03a7(0,0xa000,0x19,0xd,0,0x1b,0x50,0x8b2,unaff_DS);
  FUN_1000_03a7(0,0xa000,0x19,0xd,0,0x1c,0x50,0x8b2,unaff_DS);
  FUN_1000_068d(0,0x50,0x46,0x6040);
  FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x3e76,0x1b5a);
  FUN_1000_03a7(0,0xa000,8,7,7,0x136,0x1b,0x8b2,unaff_DS);
  FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x3ebe,0x1b5a);
  FUN_1000_03a7(0,0xa000,8,7,7,0x140,99,0x8b2,unaff_DS);
  FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x3efd,0x1b5a);
  FUN_1000_03a7(0,0xa000,8,7,7,0x14a,99,0x8b2,unaff_DS);
  FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x3f3c,0x1b5a);
  FUN_1000_03a7(0,0xa000,8,7,7,0x154,99,0x8b2,unaff_DS);
  FUN_1000_0ab4(0);
  return;
}



/* 1000:4512 FUN_1000_4512 */

void __cdecl16near FUN_1000_4512(void)

{
  undefined2 unaff_SS;
  byte local_102 [256];
  
  FUN_1b5a_0644(0xff,local_102,unaff_SS,0x448a,0x1000);
  FUN_1000_03a7(0,0xa000,8,7,0,0x14c,(uint)local_102[0] * -4 + 0x140,local_102,unaff_SS);
  FUN_1b5a_0644(0xff,local_102,unaff_SS,0x44c9,0x1b5a);
  FUN_1000_03a7(0,0xa000,8,7,0,0x155,(uint)local_102[0] * -4 + 0x140,local_102,unaff_SS);
  return;
}



/* 1000:46a5 FUN_1000_46a5 */

void __cdecl16near FUN_1000_46a5(void)

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
  
  FUN_1000_0727(0x50,0x15d,32000,0);
  FUN_1000_068d(7,0x50,0x15d,0);
  FUN_1000_6696(7,10,10,0,0xa000,(int)*(undefined4 *)0xb0e,
                (int)((ulong)*(undefined4 *)0xb0e >> 0x10));
  FUN_1000_6696(7,10,200,0,0xa000,(int)*(undefined4 *)0xb12,
                (int)((ulong)*(undefined4 *)0xb12 >> 0x10));
  FUN_1000_6696(7,0xac,0x1e0,0,0xa000,(int)*(undefined4 *)0xac2,
                (int)((ulong)*(undefined4 *)0xac2 >> 0x10));
  FUN_1000_6696(0x10,0xad,0x1ff,0,0xa000,(int)*(undefined4 *)0xb0a,
                (int)((ulong)*(undefined4 *)0xb0a >> 0x10));
  FUN_1000_6696(0x10,0xd1,0x214,0,0xa000,(int)*(undefined4 *)0xb02,
                (int)((ulong)*(undefined4 *)0xb02 >> 0x10));
  local_6 = *(int *)(*(int *)0x8a4 * 2 + 0xb0) / 8 + -1 + *(int *)(*(int *)0x8a4 * 2 + 0xb4) * 0x50;
  FUN_1000_0727(0x10,0x6b,local_6,local_6 + 32000);
  local_6 = 0;
  uVar1 = 0x1000;
  do {
    if (local_6 == 0) {
      FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x45af,uVar1);
      local_e = 10;
      uVar2 = 0x1b5a;
    }
    else if (local_6 == 1) {
      FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x45b3,uVar1);
      local_e = 100;
      uVar2 = 0x1b5a;
    }
    else if (local_6 == 2) {
      FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x45b8,uVar1);
      local_e = 10000;
      uVar2 = 0x1b5a;
    }
    else {
      uVar2 = uVar1;
      if (local_6 == 3) {
        uVar2 = 0x1b5a;
        FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x45c0,uVar1);
        local_e = 100000;
      }
    }
    FUN_1000_12aa(0x11);
    local_4 = FUN_1000_3655(3);
    FUN_1000_0b92();
    local_6 = local_6 + 1;
  } while ((local_6 < 4) && (uVar1 = uVar2, local_4 != 0));
  if (local_4 == 0) {
    FUN_1000_12aa(0x12);
    do {
      local_e = CONCAT22((int)((ulong)local_e >> 0x10) - (uint)((int)local_e == 0),(int)local_e + -1
                        );
      FUN_1b5a_0ff6(0x32);
      uVar1 = FUN_1b5a_0279();
      FUN_1af8_02c6(uVar1);
      uVar5 = (undefined2)((ulong)*(undefined4 *)0xb46 >> 0x10);
      uVar4 = (undefined2)*(undefined4 *)0xb46;
      uVar7 = 0xa000;
      uVar6 = 0;
      uVar1 = FUN_1b5a_0ff6(400);
      uVar2 = FUN_1b5a_0ff6(0x127);
      FUN_1000_6696(2,uVar2,uVar1,uVar6,uVar7,uVar4,uVar5);
      FUN_1af8_02f3();
      if (local_e < 0) break;
    } while ((0 < local_e._2_2_) || ((int)local_e != 0));
  }
  else {
    FUN_1000_12aa(0x14);
    local_8 = 0xbe;
    FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x45c8,uVar2);
    local_8 = local_8 + 0x12;
    FUN_1000_03a7(0,0xa000,8,0xd,0,local_8,(uint)*(byte *)0x8b2 * -4 + 0xf0,0x8b2,unaff_DS);
    FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x45ee,0x1b5a);
    local_8 = local_8 + 0x12;
    FUN_1000_03a7(0,0xa000,8,0xd,0,local_8,(uint)*(byte *)0x8b2 * -4 + 0xf0,0x8b2,unaff_DS);
    puVar8 = local_10e;
    iVar3 = FUN_1b5a_0ff6(10);
    FUN_1b5a_062a(iVar3 * 0x19 + 0x1bc,unaff_DS);
    FUN_1b5a_06b7(0x4615,0x1b5a);
    FUN_1b5a_0644(0xff,0x8b2,unaff_DS,puVar8,unaff_SS);
    local_8 = local_8 + 0x12;
    FUN_1000_03a7(0,0xa000,8,0xd,0xf,local_8,(uint)*(byte *)0x8b2 * -4 + 0xf0,0x8b2,unaff_DS);
    FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x4631,0x1b5a);
    local_8 = local_8 + 0x12;
    FUN_1000_03a7(0,0xa000,8,0xd,0,local_8,(uint)*(byte *)0x8b2 * -4 + 0xf0,0x8b2,unaff_DS);
    FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x4652,0x1b5a);
    local_8 = local_8 + 0x12;
    FUN_1000_03a7(0,0xa000,8,0xd,0xf,local_8,(uint)*(byte *)0x8b2 * -4 + 0xf0,0x8b2,unaff_DS);
    FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x4676,0x1b5a);
    local_8 = local_8 + 0x12;
    FUN_1000_03a7(0,0xa000,8,0xd,0,local_8,(uint)*(byte *)0x8b2 * -4 + 0xf0,0x8b2,unaff_DS);
  }
  FUN_1000_4512();
  FUN_1000_0ab4(0);
  FUN_1000_0b92();
  FUN_1000_0727(0x50,0x15d,0,32000);
  FUN_1000_068d(7,0x10,0xa7,
                *(int *)(*(int *)0x8a4 * 2 + 0xb0) / 8 + -1 +
                (*(int *)(*(int *)0x8a4 * 2 + 0xb4) + -0x3c) * 0x50);
  *(undefined2 *)(*(int *)0x8a4 * 2 + 0x896) = 2;
  *(int *)0x8a4 = *(int *)0x8a4 + 1;
  *(undefined2 *)0x5fa = 0;
  return;
}



/* 1000:4c74 FUN_1000_4c74 */

void __cdecl16near FUN_1000_4c74(void)

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
  
  FUN_1000_068d(7,0x50,0x15e,0);
  FUN_1000_6696(7,10,10,0,0xa000,(int)*(undefined4 *)0xb0e,
                (int)((ulong)*(undefined4 *)0xb0e >> 0x10));
  FUN_1000_6696(7,10,200,0,0xa000,(int)*(undefined4 *)0xb12,
                (int)((ulong)*(undefined4 *)0xb12 >> 0x10));
  FUN_1000_6696(7,0xac,0x1e0,0,0xa000,(int)*(undefined4 *)0xac2,
                (int)((ulong)*(undefined4 *)0xac2 >> 0x10));
  FUN_1000_6696(0x10,0xad,0x1ff,0,0xa000,(int)*(undefined4 *)0xb0a,
                (int)((ulong)*(undefined4 *)0xb0a >> 0x10));
  FUN_1000_6696(0x10,0xd1,0x214,0,0xa000,(int)*(undefined4 *)0xb02,
                (int)((ulong)*(undefined4 *)0xb02 >> 0x10));
  puVar6 = local_108;
  uVar7 = unaff_SS;
  FUN_1b5a_062a(0x4b56,0x1000);
  FUN_1b5a_06b7(*(int *)0x8a4 * 0xb + 0x6cb,unaff_DS);
  FUN_1b5a_06b7(0x4b5f,0x1b5a);
  FUN_1b5a_0644(0xff,0x8b2,unaff_DS,puVar6,uVar7);
  FUN_1000_03a7(0,0xa000,8,0xd,0,0xbe,(uint)*(byte *)0x8b2 * -4 + 0xf0,0x8b2,unaff_DS);
  iVar4 = *(int *)(*(int *)0x8a4 * 2 + 0x89c);
  FUN_1b5a_119c(0xff,0x8b2,unaff_DS,0,iVar4,iVar4 >> 0xf);
  puVar6 = local_108;
  uVar7 = unaff_SS;
  FUN_1b5a_062a(0x4b61,0x1b5a);
  FUN_1b5a_06b7(0x8b2,unaff_DS);
  FUN_1b5a_06b7(0x4b81,0x1b5a);
  FUN_1b5a_0644(0xff,0x8b2,unaff_DS,puVar6,uVar7);
  FUN_1000_03a7(0,0xa000,8,0xd,0,0xd0,(uint)*(byte *)0x8b2 * -4 + 0xf0,0x8b2,unaff_DS);
  FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x4b89,0x1b5a);
  FUN_1000_03a7(0,0xa000,8,0xd,0,0xe2,(uint)*(byte *)0x8b2 * -4 + 0xf0,0x8b2,unaff_DS);
  puVar6 = local_108;
  uVar7 = unaff_SS;
  iVar4 = FUN_1b5a_0ff6(10);
  FUN_1b5a_062a(iVar4 * 0x19 + 0x1bc,unaff_DS);
  FUN_1b5a_06b7(0x4bb3,0x1b5a);
  FUN_1b5a_0644(0xff,0x8b2,unaff_DS,puVar6,uVar7);
  FUN_1000_03a7(0,0xa000,8,0xd,0xf,0xf4,(uint)*(byte *)0x8b2 * -4 + 0xf0,0x8b2,unaff_DS);
  FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x4bcf,0x1b5a);
  FUN_1000_03a7(0,0xa000,8,0xd,0,0x106,(uint)*(byte *)0x8b2 * -4 + 0xf0,0x8b2,unaff_DS);
  FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x4bf0,0x1b5a);
  FUN_1000_03a7(0,0xa000,8,0xd,0xf,0x118,(uint)*(byte *)0x8b2 * -4 + 0xf0,0x8b2,unaff_DS);
  FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x4c14,0x1b5a);
  FUN_1000_03a7(0,0xa000,8,0xd,0,0x12a,(uint)*(byte *)0x8b2 * -4 + 0xf0,0x8b2,unaff_DS);
  FUN_1000_4512();
  FUN_1000_12aa(0xd);
  FUN_1000_0ab4(0);
  FUN_1000_0b92();
  local_8 = 0;
  uVar1 = *(uint *)(*(int *)0x8a4 * 2 + 0x89c);
  bVar5 = -1 < (int)uVar1 >> 0xf;
  if (((int)uVar1 < 0 && bVar5) || ((bVar5 && (*(uint *)0x5f6 < uVar1)))) {
    for (local_6 = 8; 1 < local_6; local_6 = local_6 + -1) {
      uVar1 = *(uint *)(*(int *)0x8a4 * 2 + 0x89c);
      bVar5 = (int)uVar1 >> 0xf < 0;
      if ((-1 < (int)uVar1 || bVar5) &&
         ((bVar5 || (uVar1 <= *(uint *)((local_6 + -1) * 0xd + 0x58e))))) break;
    }
    _local_c = CONCAT22(local_6 + 1,local_c);
    if (local_6 + 1 < 9) {
      for (local_4 = 8;
          FUN_1b5a_025d(0xd,local_4 * 0xd + 0x583,unaff_DS,(local_4 + -1) * 0xd + 0x583,unaff_DS),
          uVar3 = _local_c, uVar2 = (ulong)_local_c >> 0x10, bVar5 = local_4 != (int)uVar2,
          _local_c = uVar3, bVar5; local_4 = local_4 + -1) {
      }
    }
    *(undefined2 *)(local_6 * 0xd + 0x58e) = *(undefined2 *)(*(int *)0x8a4 * 2 + 0x89c);
    FUN_1b5a_0644(10,local_6 * 0xd + 0x583,unaff_DS,*(int *)0x8a4 * 0xb + 0x6cb,unaff_DS);
    local_8 = local_6;
  }
  FUN_1000_068d(0,0x14,0xa0,0xb25c);
  FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x4c43,0x1b5a);
  FUN_1000_03a7(32000,0xa000,8,0xd,0xf,0xaa,0x1e9,0x8b2,unaff_DS);
  FUN_1000_03a7(32000,0xa000,8,0xd,7,0xaa,0x1e8,0x8b2,unaff_DS);
  FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x4c55,0x1b5a);
  FUN_1000_03a7(32000,0xa000,8,0xd,0xf,0xb8,0x1e9,0x8b2,unaff_DS);
  FUN_1000_03a7(32000,0xa000,8,0xd,7,0xb8,0x1e8,0x8b2,unaff_DS);
  local_4 = 1;
  while( true ) {
    local_c = local_4 * 0xd + 0x583;
    if (local_4 == local_8) {
      local_6 = 0xf;
    }
    else {
      local_6 = 0xb;
    }
    FUN_1b5a_119c(0xff,0x8b2,unaff_DS,0,local_4,local_4 >> 0xf);
    puVar6 = local_10c;
    uVar7 = unaff_SS;
    FUN_1b5a_062a(0x8b2,unaff_DS);
    FUN_1b5a_06b7(0x4c67,0x1b5a);
    FUN_1b5a_06b7(local_c,unaff_DS);
    FUN_1b5a_0644(0xff,0x8b2,unaff_DS,puVar6,uVar7);
    FUN_1000_03a7(32000,0xa000,8,0xd,local_6 + -8,local_4 * 0xe + 0xc3,0x1e1,0x8b2,unaff_DS);
    FUN_1000_03a7(32000,0xa000,8,0xd,local_6,local_4 * 0xe + 0xc3,0x1e0,0x8b2,unaff_DS);
    FUN_1b5a_119c(0xff,0x8b2,unaff_DS,4,*(undefined2 *)(local_c + 0xb),0);
    puVar6 = local_10c;
    uVar7 = unaff_SS;
    FUN_1b5a_062a(0x8b2,unaff_DS);
    FUN_1b5a_06b7(0x4c69,0x1b5a);
    FUN_1b5a_0644(0xff,0x8b2,unaff_DS,puVar6,uVar7);
    FUN_1000_03a7(32000,0xa000,8,0xd,local_6 + -8,local_4 * 0xe + 0xc3,0x24f,0x8b2,unaff_DS);
    FUN_1000_03a7(32000,0xa000,8,0xd,local_6,local_4 * 0xe + 0xc3,0x24e,0x8b2,unaff_DS);
    if (local_4 == 8) break;
    local_4 = local_4 + 1;
  }
  local_4 = 0x50;
  while( true ) {
    FUN_1af8_02c6((local_4 * -0x14 + 0x640) * *(int *)0x8b0);
    FUN_1000_0727(0x13,local_4 * -2 + 0xa0,local_4 * 0xa0 + 0x33cc,0xb0cc);
    FUN_1af8_02f3();
    FUN_1af8_029e(local_4);
    if (local_4 == 0) break;
    local_4 = local_4 + -1;
  }
  if (0 < local_8) {
    FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x4c6b,0x1af8);
    FUN_1b5a_161f(0x8b2,unaff_DS,0x814,unaff_DS);
    FUN_1b5a_1656(0xd,0x814,unaff_DS);
    FUN_1b5a_020e();
    local_4 = 1;
    while( true ) {
      FUN_1b5a_1709(local_4 * 0xd + 0x583,unaff_DS);
      FUN_1b5a_020e();
      if (local_4 == 8) break;
      local_4 = local_4 + 1;
    }
    FUN_1b5a_16ce(0x814,unaff_DS);
    FUN_1b5a_020e();
  }
  FUN_1000_0ab4(0);
  return;
}



/* 1000:54bb FUN_1000_54bb */

void __cdecl16near FUN_1000_54bb(void)

{
  undefined2 unaff_DS;
  undefined2 local_4;
  
  FUN_1000_0727(0x15,0xaa,0xb2fb,0x35fb);
  FUN_1000_6696(0x10,0xad,0x1e1,32000,0xa000,(int)*(undefined4 *)0xb26,
                (int)((ulong)*(undefined4 *)0xb26 >> 0x10));
  FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x5412,0x1000);
  FUN_1000_03a7(32000,0xa000,8,7,0xe,0xae,(uint)*(byte *)0x8b2 * -4 + 0x22d,0x8b2,unaff_DS);
  FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x5424,0x1b5a);
  FUN_1000_03a7(32000,0xa000,8,7,0xe,0xf8,(uint)*(byte *)0x8b2 * -4 + 0x22d,0x8b2,unaff_DS);
  FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x5438,0x1b5a);
  FUN_1000_03a7(32000,0xa000,8,7,0xe,0x100,(uint)*(byte *)0x8b2 * -4 + 0x22d,0x8b2,unaff_DS);
  FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x544a,0x1b5a);
  FUN_1000_03a7(32000,0xa000,8,7,0xe,0x108,(uint)*(byte *)0x8b2 * -4 + 0x22d,0x8b2,unaff_DS);
  FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x545d,0x1b5a);
  FUN_1000_03a7(32000,0xa000,8,7,0xe,0x110,(uint)*(byte *)0x8b2 * -4 + 0x22d,0x8b2,unaff_DS);
  FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x546d,0x1b5a);
  FUN_1000_03a7(32000,0xa000,8,7,0xe,0x118,(uint)*(byte *)0x8b2 * -4 + 0x22d,0x8b2,unaff_DS);
  FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x547f,0x1b5a);
  FUN_1000_03a7(32000,0xa000,8,7,0xe,0x120,(uint)*(byte *)0x8b2 * -4 + 0x22d,0x8b2,unaff_DS);
  FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x548d,0x1b5a);
  FUN_1000_03a7(32000,0xa000,8,7,0xe,0x128,(uint)*(byte *)0x8b2 * -4 + 0x22d,0x8b2,unaff_DS);
  FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x549c,0x1b5a);
  FUN_1000_03a7(32000,0xa000,8,7,0xe,0x130,(uint)*(byte *)0x8b2 * -4 + 0x22d,0x8b2,unaff_DS);
  FUN_1b5a_0644(0xff,0x8b2,unaff_DS,0x54af,0x1b5a);
  FUN_1000_03a7(32000,0xa000,8,7,0xe,0x13a,(uint)*(byte *)0x8b2 * -4 + 0x22d,0x8b2,unaff_DS);
  local_4 = 0x50;
  while( true ) {
    FUN_1af8_02c6((local_4 * -0x14 + 0x6a4) * *(int *)0x8b0);
    FUN_1000_0727(0x15,local_4 * -2 + 0xa0,local_4 * 0xa0 + 0x364b,0xb34b);
    FUN_1af8_02f3();
    FUN_1af8_029e(local_4 / 2);
    if (local_4 == 0) break;
    local_4 = local_4 + -1;
  }
  FUN_1000_0ab4(0);
  FUN_1000_6696(7,0xac,0x1e0,0,0xa000,(int)*(undefined4 *)0xac2,
                (int)((ulong)*(undefined4 *)0xac2 >> 0x10));
  FUN_1000_6696(0x10,0xad,0x1ff,0,0xa000,(int)*(undefined4 *)0xb0a,
                (int)((ulong)*(undefined4 *)0xb0a >> 0x10));
  FUN_1000_6696(0x10,0xd1,0x214,0,0xa000,(int)*(undefined4 *)0xb02,
                (int)((ulong)*(undefined4 *)0xb02 >> 0x10));
  return;
}



/* 1000:5953 entry */

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
  
  DAT_1ce5_4f0e = 0x1000;
  DAT_1ce5_4f0c = 0x5958;
  FUN_1b5a_0000();
  DAT_1ce5_4f0e = 0x1b5a;
  DAT_1ce5_4f0c = 0x595d;
  FUN_1af8_0000();
  DAT_1ce5_4f0e = 0x1af8;
  DAT_1ce5_4f0c = 0x5962;
  FUN_17cc_1019();
  DAT_1ce5_4e0c = 0x17cc;
  DAT_1ce5_4e0a = 0x596e;
  DAT_1ce5_4f0e = unaff_BP;
  FUN_1b5a_107d();
  DAT_1ce5_4e0c = 0x5971;
  FUN_1000_0055();
  DAT_1ce5_4e0c = 0x5974;
  FUN_1000_05cc();
  *(undefined2 *)0x8b0 = 0;
  *(undefined2 *)0x9bc = 1;
  while (*(undefined2 *)(*(int *)0x9bc * 2 + 0x57e) = *(undefined2 *)0x9bc, *(int *)0x9bc != 8) {
    *(int *)0x9bc = *(int *)0x9bc + 1;
  }
  *(undefined2 *)0x8a8 = 1;
  while( true ) {
    DAT_1ce5_4e0c = 8;
    DAT_1ce5_4e0a = 0x1b5a;
    DAT_1ce5_4e08 = 0x59ae;
    iVar5 = FUN_1b5a_0ff6();
    *(int *)0x9bc = iVar5 + 1;
    DAT_1ce5_4e0c = 8;
    DAT_1ce5_4e0a = 0x1b5a;
    uVar12 = 0x1b5a;
    DAT_1ce5_4e08 = 0x59bb;
    iVar5 = FUN_1b5a_0ff6();
    *(int *)0x7fe = iVar5 + 1;
    *(undefined2 *)0x8aa = *(undefined2 *)(*(int *)0x9bc * 2 + 0x57e);
    *(undefined2 *)(*(int *)0x9bc * 2 + 0x57e) = *(undefined2 *)(*(int *)0x7fe * 2 + 0x57e);
    *(undefined2 *)(*(int *)0x7fe * 2 + 0x57e) = *(undefined2 *)0x8aa;
    if (*(int *)0x8a8 == 100) break;
    *(int *)0x8a8 = *(int *)0x8a8 + 1;
  }
  DAT_1ce5_4e0c = 0x59f7;
  FUN_1000_3f7b();
  *(undefined2 *)0x8a6 = 0;
  *(undefined2 *)0x9bc = 1;
  while (*(undefined2 *)(*(int *)0x9bc * 2 + 0x89c) = 0, *(int *)0x9bc != 3) {
    *(int *)0x9bc = *(int *)0x9bc + 1;
  }
  *(undefined2 *)0x9bc = 2;
  while (*(undefined2 *)(*(int *)0x9bc * 2 + 0x896) = 1, *(int *)0x9bc != 3) {
    *(int *)0x9bc = *(int *)0x9bc + 1;
  }
  *(undefined2 *)0x898 = 0;
  *(undefined2 *)0x9bc = 0;
  while (*(undefined2 *)(*(int *)0x9bc * 2 + 0x6d0) = 0, *(int *)0x9bc != 2) {
    *(int *)0x9bc = *(int *)0x9bc + 1;
  }
  *(undefined1 *)0x6e1 = 0;
  *(undefined1 *)0x6ec = 0;
  do {
    DAT_1ce5_4e0c = *(int *)0x8a6 + 1;
    DAT_1ce5_4e08 = 0x5a71;
    DAT_1ce5_4e0a = uVar12;
    iVar5 = FUN_1b5a_0ff6();
    *(int *)0x89e = iVar5 * 0xf;
    DAT_1ce5_4e0c = 0;
    DAT_1ce5_4e0a = 10;
    DAT_1ce5_4e08 = 0x50;
    DAT_1ce5_4e06 = 3;
    DAT_1ce5_4e04 = 0x5a8b;
    FUN_1000_068d();
    DAT_1ce5_4e0c = 800;
    DAT_1ce5_4e0a = 2;
    DAT_1ce5_4e08 = 0x50;
    DAT_1ce5_4e06 = 8;
    DAT_1ce5_4e04 = 0x5a9e;
    FUN_1000_068d();
    DAT_1ce5_4e0c = 0x410;
    DAT_1ce5_4e0a = 0x5e;
    DAT_1ce5_4e08 = 0x50;
    DAT_1ce5_4e06 = 1;
    DAT_1ce5_4e04 = 0x5ab1;
    FUN_1000_068d();
    DAT_1ce5_4e0c = 0x21c0;
    DAT_1ce5_4e0a = 2;
    DAT_1ce5_4e08 = 0x50;
    DAT_1ce5_4e06 = 8;
    DAT_1ce5_4e04 = 0x5ac4;
    FUN_1000_068d();
    DAT_1ce5_4e0c = 0x22b0;
    DAT_1ce5_4e0a = 0xee;
    DAT_1ce5_4e08 = 0x50;
    DAT_1ce5_4e06 = 7;
    DAT_1ce5_4e04 = 0x5ad7;
    FUN_1000_068d();
    DAT_1ce5_4e0c = 0x6770;
    DAT_1ce5_4e0a = 1;
    DAT_1ce5_4e08 = 0x50;
    DAT_1ce5_4e06 = 8;
    DAT_1ce5_4e04 = 0x5aea;
    FUN_1000_068d();
    *(undefined2 *)0x8a8 = 0;
    while( true ) {
      DAT_1ce5_4e0c = 3;
      DAT_1ce5_4e0a = 0x1b5a;
      DAT_1ce5_4e08 = 0x5afe;
      iVar5 = FUN_1b5a_0ff6();
      uVar4 = *(undefined4 *)((iVar5 + 0x1f) * 4 + 0xa56);
      DAT_1ce5_4e0c = (int)((ulong)uVar4 >> 0x10);
      DAT_1ce5_4e0a = (int)uVar4;
      DAT_1ce5_4e08 = 0xa000;
      DAT_1ce5_4e06 = 0;
      DAT_1ce5_4e04 = (int)(((ulong)*(uint *)0x8a8 % 0xc) * 0x34) + 5;
      DAT_1ce5_4e02 = (*(uint *)0x8a8 / 0xc) * 0x1f + 0xf;
      DAT_1ce5_4e00 = 1;
      DAT_1ce5_4dfe = 0x5b45;
      FUN_1000_6696();
      if (*(int *)0x8a8 == 0x23) break;
      *(int *)0x8a8 = *(int *)0x8a8 + 1;
    }
    DAT_1ce5_4e0c = (int)((ulong)*(undefined4 *)0xaf6 >> 0x10);
    DAT_1ce5_4e0a = (int)*(undefined4 *)0xaf6;
    DAT_1ce5_4e08 = 0xa000;
    DAT_1ce5_4e06 = 0;
    DAT_1ce5_4e04 = 0;
    DAT_1ce5_4e02 = 0x19;
    DAT_1ce5_4e00 = 7;
    DAT_1ce5_4dfe = 0x5b6a;
    FUN_1000_6696();
    DAT_1ce5_4e0c = (int)((ulong)*(undefined4 *)0xafa >> 0x10);
    DAT_1ce5_4e0a = (int)*(undefined4 *)0xafa;
    DAT_1ce5_4e08 = 0xa000;
    DAT_1ce5_4e06 = 0;
    DAT_1ce5_4e04 = 600;
    DAT_1ce5_4e02 = 0x19;
    DAT_1ce5_4e00 = 7;
    DAT_1ce5_4dfe = 0x5b89;
    FUN_1000_6696();
    DAT_1ce5_4e0c = (int)((ulong)*(undefined4 *)0xade >> 0x10);
    DAT_1ce5_4e0a = (int)*(undefined4 *)0xade;
    DAT_1ce5_4e08 = 0xa000;
    DAT_1ce5_4e06 = 0;
    DAT_1ce5_4e04 = 0x45;
    DAT_1ce5_4e02 = 3;
    DAT_1ce5_4e00 = 1;
    DAT_1ce5_4dfe = 0x5ba8;
    FUN_1000_6696();
    DAT_1ce5_4e0c = (int)((ulong)*(undefined4 *)0xade >> 0x10);
    DAT_1ce5_4e0a = (int)*(undefined4 *)0xade;
    DAT_1ce5_4e08 = 0xa000;
    DAT_1ce5_4e06 = 0;
    DAT_1ce5_4e04 = 0x22f;
    DAT_1ce5_4e02 = 3;
    DAT_1ce5_4e00 = 1;
    DAT_1ce5_4dfe = 0x5bc7;
    FUN_1000_6696();
    out(0x3ce,5);
    out(0x3cf,0);
    DAT_1ce5_4e0c = 0;
    DAT_1ce5_4e0a = 0x1b5a;
    DAT_1ce5_4e08 = 0x5bdb;
    FUN_17cc_149e();
    DAT_1ce5_4e0c = 1;
    DAT_1ce5_4e0a = 7;
    DAT_1ce5_4e08 = 0x17cc;
    DAT_1ce5_4e06 = 0x5be8;
    FUN_17cc_0b9e();
    DAT_1ce5_4e0c = 0x78;
    DAT_1ce5_4e0a = 0xf;
    DAT_1ce5_4e08 = 0x208;
    DAT_1ce5_4e06 = 0x5f;
    DAT_1ce5_4e04 = 0x17cc;
    DAT_1ce5_4e02 = 0x5bfd;
    FUN_17cc_13aa();
    *(undefined2 *)0x9bc = 0;
    while( true ) {
      DAT_1ce5_4e0c = 0x78;
      DAT_1ce5_4e0a = *(int *)0x9bc * 0x14 + 0xf;
      DAT_1ce5_4e08 = 0x208;
      DAT_1ce5_4e06 = *(int *)0x9bc * 0x14 + 0xf;
      DAT_1ce5_4e04 = 0x17cc;
      DAT_1ce5_4e02 = 0x5c2d;
      FUN_17cc_1362();
      if (*(int *)0x9bc == 4) break;
      *(int *)0x9bc = *(int *)0x9bc + 1;
    }
    *(undefined2 *)0x9bc = 0;
    while( true ) {
      DAT_1ce5_4e0c = *(int *)0x9bc * 0x10 + 0x78;
      DAT_1ce5_4e0a = 0x5f;
      DAT_1ce5_4e08 = *(int *)0x9bc * 0x10 + 0x78;
      DAT_1ce5_4e06 = 0xf;
      DAT_1ce5_4e04 = 0x17cc;
      uVar12 = 0x17cc;
      DAT_1ce5_4e02 = 0x5c64;
      FUN_17cc_1362();
      if (*(int *)0x9bc == 0x19) break;
      *(int *)0x9bc = *(int *)0x9bc + 1;
    }
    iVar5 = *(int *)0x8a6;
    if (iVar5 == 0) {
      DAT_1ce5_4e0c = 0x17cc;
      DAT_1ce5_4e0a = 0x58d9;
      DAT_1ce5_4e06 = 0x8b2;
      DAT_1ce5_4e04 = 0xff;
      DAT_1ce5_4e02 = 0x17cc;
      uVar12 = 0x1b5a;
      DAT_1ce5_4e00 = 0x5c86;
      FUN_1b5a_0644();
    }
    else if (iVar5 == 1) {
      DAT_1ce5_4e0c = 0x17cc;
      DAT_1ce5_4e0a = 0x58e5;
      DAT_1ce5_4e06 = 0x8b2;
      DAT_1ce5_4e04 = 0xff;
      DAT_1ce5_4e02 = 0x17cc;
      uVar12 = 0x1b5a;
      DAT_1ce5_4e00 = 0x5ca1;
      FUN_1b5a_0644();
    }
    else if (iVar5 == 2) {
      DAT_1ce5_4e0c = 0x17cc;
      DAT_1ce5_4e0a = 0x58f1;
      DAT_1ce5_4e06 = 0x8b2;
      DAT_1ce5_4e04 = 0xff;
      DAT_1ce5_4e02 = 0x17cc;
      uVar12 = 0x1b5a;
      DAT_1ce5_4e00 = 0x5cbc;
      FUN_1b5a_0644();
    }
    else if (iVar5 == 3) {
      DAT_1ce5_4e0c = 0x17cc;
      DAT_1ce5_4e0a = 0x58fd;
      DAT_1ce5_4e06 = 0x8b2;
      DAT_1ce5_4e04 = 0xff;
      DAT_1ce5_4e02 = 0x17cc;
      uVar12 = 0x1b5a;
      DAT_1ce5_4e00 = 0x5cd7;
      FUN_1b5a_0644();
    }
    else if (iVar5 == 4) {
      DAT_1ce5_4e0c = 0x17cc;
      DAT_1ce5_4e0a = 0x5908;
      DAT_1ce5_4e06 = 0x8b2;
      DAT_1ce5_4e04 = 0xff;
      DAT_1ce5_4e02 = 0x17cc;
      uVar12 = 0x1b5a;
      DAT_1ce5_4e00 = 0x5cf1;
      FUN_1b5a_0644();
    }
    else if (iVar5 == 5) {
      DAT_1ce5_4e0c = 0x17cc;
      DAT_1ce5_4e0a = 0x5913;
      DAT_1ce5_4e06 = 0x8b2;
      DAT_1ce5_4e04 = 0xff;
      DAT_1ce5_4e02 = 0x17cc;
      uVar12 = 0x1b5a;
      DAT_1ce5_4e00 = 0x5d0b;
      FUN_1b5a_0644();
    }
    else if (iVar5 == 6) {
      DAT_1ce5_4e0c = 0x17cc;
      DAT_1ce5_4e0a = 0x591e;
      DAT_1ce5_4e06 = 0x8b2;
      DAT_1ce5_4e04 = 0xff;
      DAT_1ce5_4e02 = 0x17cc;
      uVar12 = 0x1b5a;
      DAT_1ce5_4e00 = 0x5d25;
      FUN_1b5a_0644();
    }
    else if (iVar5 == 7) {
      DAT_1ce5_4e0c = 0x17cc;
      DAT_1ce5_4e0a = 0x5927;
      DAT_1ce5_4e06 = 0x8b2;
      DAT_1ce5_4e04 = 0xff;
      DAT_1ce5_4e02 = 0x17cc;
      uVar12 = 0x1b5a;
      DAT_1ce5_4e00 = 0x5d3f;
      FUN_1b5a_0644();
    }
    DAT_1ce5_4e0a = 0x8b2;
    DAT_1ce5_4e08 = 0xcc;
    DAT_1ce5_4e06 = 0x4e;
    DAT_1ce5_4e04 = 0;
    DAT_1ce5_4e02 = 0xd;
    DAT_1ce5_4e00 = 0x10;
    DAT_1ce5_4dfe = 0xa000;
    DAT_1ce5_4dfc = 0;
    DAT_1ce5_4dfa = 0x5d64;
    FUN_1000_03a7();
    DAT_1ce5_4e0c = (int)((ulong)*(undefined4 *)0xac2 >> 0x10);
    DAT_1ce5_4e0a = (int)*(undefined4 *)0xac2;
    DAT_1ce5_4e08 = 0xa000;
    DAT_1ce5_4e06 = 0;
    DAT_1ce5_4e04 = 0x1e0;
    DAT_1ce5_4e02 = 0xac;
    DAT_1ce5_4e00 = 7;
    DAT_1ce5_4dfe = 0x5d83;
    FUN_1000_6696();
    DAT_1ce5_4e0c = (int)((ulong)*(undefined4 *)0xb0a >> 0x10);
    DAT_1ce5_4e0a = (int)*(undefined4 *)0xb0a;
    DAT_1ce5_4e08 = 0xa000;
    DAT_1ce5_4e06 = 0;
    DAT_1ce5_4e04 = 0x1ff;
    DAT_1ce5_4e02 = 0xad;
    DAT_1ce5_4e00 = 0x10;
    DAT_1ce5_4dfe = 0x5da2;
    FUN_1000_6696();
    DAT_1ce5_4e0c = (int)((ulong)*(undefined4 *)0xb02 >> 0x10);
    DAT_1ce5_4e0a = (int)*(undefined4 *)0xb02;
    DAT_1ce5_4e08 = 0xa000;
    DAT_1ce5_4e06 = 0;
    DAT_1ce5_4e04 = 0x214;
    DAT_1ce5_4e02 = 0xd1;
    DAT_1ce5_4e00 = 0x10;
    DAT_1ce5_4dfe = 0x5dc1;
    FUN_1000_6696();
    *(undefined2 *)0x8a8 = 0;
    while( true ) {
      DAT_1ce5_4e0c = (int)((ulong)*(undefined4 *)0xa9a >> 0x10);
      DAT_1ce5_4e0a = (int)*(undefined4 *)0xa9a;
      DAT_1ce5_4e08 = 0xa000;
      DAT_1ce5_4e06 = 0;
      DAT_1ce5_4e04 = *(int *)0x8a8 * 0x14;
      DAT_1ce5_4e02 = 0x14c;
      DAT_1ce5_4e00 = 8;
      DAT_1ce5_4dfe = 0x5df0;
      FUN_1000_6696();
      if (*(int *)0x8a8 == 0x1f) break;
      *(int *)0x8a8 = *(int *)0x8a8 + 1;
    }
    *(undefined2 *)0x8a8 = 0;
    DAT_1ce5_4e06 = uVar12;
    while( true ) {
      DAT_1ce5_4e0c = 0x1dee;
      DAT_1ce5_4e0a = 0x3d7e;
      DAT_1ce5_4e08 =
           CONCAT11((char)((uint)(*(int *)0x8a8 + 1) >> 8),*(undefined1 *)(*(int *)0x8a8 + 0xbd));
      DAT_1ce5_4e04 = 0x5e18;
      FUN_1b5a_075a();
      DAT_1ce5_4e08 = *(int *)0x8a8 * 0x14 + 4;
      DAT_1ce5_4e06 = 0x14e;
      DAT_1ce5_4e04 = 0;
      DAT_1ce5_4e02 = 0xd;
      DAT_1ce5_4e00 = 8;
      DAT_1ce5_4dfe = 0xa000;
      DAT_1ce5_4dfc = 0;
      DAT_1ce5_4dfa = 0x5e40;
      FUN_1000_03a7();
      if (*(int *)0x8a8 == 0x1f) break;
      *(int *)0x8a8 = *(int *)0x8a8 + 1;
      DAT_1ce5_4e06 = 0x1b5a;
    }
    DAT_1ce5_4e0c = 0x13;
    DAT_1ce5_4e0a = 0x5e4e;
    FUN_1000_12aa();
    *(undefined2 *)0x9bc = *(undefined2 *)(*(int *)((*(int *)0x8a6 + 1) * 2 + 0x57e) * 0xd + -0xb);
    uVar4 = *(undefined4 *)(*(int *)0x9bc * 4 + 0xa56);
    DAT_1ce5_4e0c = (int)((ulong)uVar4 >> 0x10);
    DAT_1ce5_4e0a = (int)uVar4;
    DAT_1ce5_4e08 = 0xa000;
    DAT_1ce5_4e06 = 0;
    DAT_1ce5_4e04 = 0xd0;
    DAT_1ce5_4e02 = 0x76;
    DAT_1ce5_4e00 = 2;
    DAT_1ce5_4dfe = 0x5e8f;
    FUN_1000_6696();
    out(0x3ce,5);
    out(0x3cf,0);
    DAT_1ce5_4e0c = 8;
    DAT_1ce5_4e0a = 0x1b5a;
    DAT_1ce5_4e08 = 0x5ea4;
    FUN_17cc_149e();
    DAT_1ce5_4e0c = 1;
    DAT_1ce5_4e0a = 7;
    DAT_1ce5_4e08 = 0x17cc;
    DAT_1ce5_4e06 = 0x5eb1;
    FUN_17cc_0b9e();
    DAT_1ce5_4e0c = 0x122;
    DAT_1ce5_4e0a = 0x78;
    DAT_1ce5_4e08 = 0x192;
    DAT_1ce5_4e06 = 0x94;
    DAT_1ce5_4e04 = 0;
    DAT_1ce5_4e02 = 1;
    DAT_1ce5_4e00 = 0x17cc;
    DAT_1ce5_4dfe = 0x5ecc;
    FUN_17cc_13c4();
    DAT_1ce5_4e0c = 0x3030;
    DAT_1ce5_4e0a = 28000;
    DAT_1ce5_4e08 = 0x27;
    DAT_1ce5_4e06 = 0x1c;
    DAT_1ce5_4e04 = 0x5edf;
    FUN_1000_0727();
    *(undefined2 *)0x9be = 0;
    DAT_1ce5_4e0c = 0x5ee7;
    FUN_1000_2deb();
    DAT_1ce5_4e0a = *(int *)((*(int *)0x8a6 + 1) * 2 + 0x57e) * 0xd + -9;
    DAT_1ce5_4e06 = 0x6d6;
    DAT_1ce5_4e04 = 10;
    DAT_1ce5_4e02 = 0x17cc;
    DAT_1ce5_4e00 = 0x5f0e;
    FUN_1b5a_0644();
    DAT_1ce5_4e0c = 0x1b5a;
    DAT_1ce5_4e0a = 0x5932;
    DAT_1ce5_4e06 = 0x8b2;
    DAT_1ce5_4e04 = 0xff;
    DAT_1ce5_4e02 = 0x1b5a;
    uVar12 = 0x1b5a;
    DAT_1ce5_4e00 = 0x5f21;
    FUN_1b5a_0644();
    *(undefined2 *)0x9bc = 1;
    while( true ) {
      *(int *)0x7fe = (*(int *)0x9bc % 2) * 7;
      DAT_1ce5_4e0a = 0x8b2;
      DAT_1ce5_4e08 = (uint)*(byte *)0x8b2 * -4 + 0x15a;
      DAT_1ce5_4e06 = 0x79;
      DAT_1ce5_4e04 = *(undefined2 *)0x7fe;
      DAT_1ce5_4e02 = 0xd;
      DAT_1ce5_4e00 = 8;
      DAT_1ce5_4dfe = 0xa000;
      DAT_1ce5_4dfc = 0;
      DAT_1ce5_4dfa = 0x5f73;
      FUN_1000_03a7();
      DAT_1ce5_4e0c = (*(int *)0x9bc * 10 + 100) * *(int *)0x8b0;
      DAT_1ce5_4e08 = 0x5f88;
      DAT_1ce5_4e0a = uVar12;
      FUN_1af8_02c6();
      DAT_1ce5_4e0c = 0x14;
      DAT_1ce5_4e0a = 0x1af8;
      DAT_1ce5_4e08 = 0x5f91;
      FUN_1af8_029e();
      DAT_1ce5_4e0c = 0x1af8;
      DAT_1ce5_4e0a = 0x5f96;
      FUN_1af8_02f3();
      DAT_1ce5_4e0c = 0x78;
      DAT_1ce5_4e0a = 0x1af8;
      uVar12 = 0x1af8;
      DAT_1ce5_4e08 = 0x5f9f;
      FUN_1af8_029e();
      if (*(int *)0x9bc == 4) break;
      *(int *)0x9bc = *(int *)0x9bc + 1;
    }
    DAT_1ce5_4e0c = *(int *)0x8b0 * 0x32;
    DAT_1ce5_4e0a = 0x1af8;
    DAT_1ce5_4e08 = 0x5fb4;
    FUN_1af8_02c6();
    DAT_1ce5_4e0a = 0x6d6;
    DAT_1ce5_4e08 = (uint)*(byte *)0x6d6 * -4 + 0x15a;
    DAT_1ce5_4e06 = 0x86;
    DAT_1ce5_4e04 = 0;
    DAT_1ce5_4e02 = 0xd;
    DAT_1ce5_4e00 = 8;
    DAT_1ce5_4dfe = 0xa000;
    DAT_1ce5_4dfc = 0;
    DAT_1ce5_4dfa = 0x5fe7;
    FUN_1000_03a7();
    DAT_1ce5_4e0c = 100;
    DAT_1ce5_4e0a = 0x1af8;
    DAT_1ce5_4e08 = 0x5ff0;
    FUN_1af8_029e();
    DAT_1ce5_4e0c = 0x1af8;
    DAT_1ce5_4e0a = 0x5ff5;
    FUN_1af8_02f3();
    DAT_1ce5_4e0c = 500;
    DAT_1ce5_4e0a = 0x1af8;
    DAT_1ce5_4e08 = 0x5ffe;
    FUN_1af8_029e();
    DAT_1ce5_4e0c = (int)((ulong)*(undefined4 *)0xb42 >> 0x10);
    DAT_1ce5_4e0a = (int)*(undefined4 *)0xb42;
    DAT_1ce5_4e08 = 0xa000;
    DAT_1ce5_4e06 = 0;
    DAT_1ce5_4e04 = *(undefined2 *)0xb4;
    DAT_1ce5_4e02 = *(undefined2 *)0xb8;
    DAT_1ce5_4e00 = 2;
    DAT_1ce5_4dfe = 0x601d;
    FUN_1000_6696();
    out(0x3ce,5);
    out(0x3cf,0);
    DAT_1ce5_4e0c = 8;
    DAT_1ce5_4e0a = 0x1af8;
    DAT_1ce5_4e08 = 0x6032;
    FUN_17cc_149e();
    DAT_1ce5_4e0c = 1;
    DAT_1ce5_4e0a = 7;
    DAT_1ce5_4e08 = 0x17cc;
    DAT_1ce5_4e06 = 0x603f;
    FUN_17cc_0b9e();
    DAT_1ce5_4e0c = *(int *)0xb4 + -4;
    DAT_1ce5_4e0a = *(int *)0xb8 + 0x50;
    DAT_1ce5_4e08 = *(int *)0xb4 + 0x70;
    DAT_1ce5_4e06 = *(int *)0xb8 + 0x6c;
    DAT_1ce5_4e04 = 0;
    DAT_1ce5_4e02 = 1;
    DAT_1ce5_4e00 = 0x17cc;
    DAT_1ce5_4dfe = 0x6066;
    FUN_17cc_13c4();
    DAT_1ce5_4e0c = 0x17cc;
    DAT_1ce5_4e0a = 0x593d;
    DAT_1ce5_4e06 = 0x8b2;
    DAT_1ce5_4e04 = 0xff;
    DAT_1ce5_4e02 = 0x17cc;
    uVar12 = 0x1b5a;
    DAT_1ce5_4e00 = 0x6079;
    FUN_1b5a_0644();
    *(undefined2 *)0x9bc = 1;
    while( true ) {
      *(int *)0x7fe = (*(int *)0x9bc % 2) * 7;
      DAT_1ce5_4e0a = 0x8b2;
      DAT_1ce5_4e08 = *(int *)0xb4 + 0x38 + (uint)*(byte *)0x8b2 * -4;
      DAT_1ce5_4e06 = *(int *)0xb8 + 0x51;
      DAT_1ce5_4e04 = *(undefined2 *)0x7fe;
      DAT_1ce5_4e02 = 0xd;
      DAT_1ce5_4e00 = 8;
      DAT_1ce5_4dfe = 0xa000;
      DAT_1ce5_4dfc = 0;
      DAT_1ce5_4dfa = 0x60d1;
      FUN_1000_03a7();
      DAT_1ce5_4e0c = (*(int *)0x9bc * 10 + 100) * *(int *)0x8b0;
      DAT_1ce5_4e08 = 0x60e6;
      DAT_1ce5_4e0a = uVar12;
      FUN_1af8_02c6();
      DAT_1ce5_4e0c = 0x14;
      DAT_1ce5_4e0a = 0x1af8;
      DAT_1ce5_4e08 = 0x60ef;
      FUN_1af8_029e();
      DAT_1ce5_4e0c = 0x1af8;
      DAT_1ce5_4e0a = 0x60f4;
      FUN_1af8_02f3();
      DAT_1ce5_4e0c = 0x78;
      DAT_1ce5_4e0a = 0x1af8;
      uVar12 = 0x1af8;
      DAT_1ce5_4e08 = 0x60fd;
      FUN_1af8_029e();
      if (*(int *)0x9bc == 4) break;
      *(int *)0x9bc = *(int *)0x9bc + 1;
    }
    if (*(int *)0x89a == 0) {
      DAT_1ce5_4e0a = 0x6e1;
      DAT_1ce5_4e08 = *(int *)0xb4 + 0x38 + (uint)*(byte *)0x6e1 * -4;
      DAT_1ce5_4e06 = *(int *)0xb8 + 0x5e;
      DAT_1ce5_4e04 = 0;
      DAT_1ce5_4e02 = 0xd;
      DAT_1ce5_4e00 = 8;
      DAT_1ce5_4dfe = 0xa000;
      DAT_1ce5_4dfc = 0;
      DAT_1ce5_4dfa = 0x6147;
      FUN_1000_03a7();
    }
    else {
      DAT_1ce5_4e0c = 0x614c;
      FUN_1000_0b92();
      DAT_1ce5_4e0c = 0x15;
      DAT_1ce5_4e0a = 0x6153;
      FUN_1000_12aa();
      DAT_1ce5_4e0c = 2;
      DAT_1ce5_4e0a = 0x615a;
      FUN_1000_2a82();
      if (*(char *)0x6e1 == '\0') {
        DAT_1ce5_4e0c = *(int *)0xb4 / 8 + -1 + (*(int *)0xb8 + -0x3c) * 0x50;
        DAT_1ce5_4e0a = 0xa7;
        DAT_1ce5_4e08 = 0x10;
        DAT_1ce5_4e06 = 7;
        DAT_1ce5_4e04 = 0x6191;
        FUN_1000_068d();
      }
      else {
        *(undefined2 *)0x89a = 0;
      }
    }
    DAT_1ce5_4e0c = (int)((ulong)*(undefined4 *)0xb42 >> 0x10);
    DAT_1ce5_4e0a = (int)*(undefined4 *)0xb42;
    DAT_1ce5_4e08 = 0xa000;
    DAT_1ce5_4e06 = 0;
    DAT_1ce5_4e04 = *(undefined2 *)0xb6;
    DAT_1ce5_4e02 = *(undefined2 *)0xba;
    DAT_1ce5_4e00 = 2;
    DAT_1ce5_4dfe = 0x61b0;
    FUN_1000_6696();
    out(0x3ce,5);
    out(0x3cf,0);
    DAT_1ce5_4e0c = 0x1af8;
    DAT_1ce5_4e0a = 0x5948;
    DAT_1ce5_4e06 = 0x8b2;
    DAT_1ce5_4e04 = 0xff;
    DAT_1ce5_4e02 = 0x1af8;
    DAT_1ce5_4e00 = 0x61cf;
    FUN_1b5a_0644();
    DAT_1ce5_4e0c = *(int *)0xb6 + -4;
    DAT_1ce5_4e0a = *(int *)0xba + 0x50;
    DAT_1ce5_4e08 = *(int *)0xb6 + 0x70;
    DAT_1ce5_4e06 = *(int *)0xba + 0x6c;
    DAT_1ce5_4e04 = 0;
    DAT_1ce5_4e02 = 1;
    DAT_1ce5_4e00 = 0x1b5a;
    uVar12 = 0x17cc;
    DAT_1ce5_4dfe = 0x61f6;
    FUN_17cc_13c4();
    *(undefined2 *)0x9bc = 1;
    while( true ) {
      *(int *)0x7fe = (*(int *)0x9bc % 2) * 7;
      DAT_1ce5_4e0a = 0x8b2;
      DAT_1ce5_4e08 = *(int *)0xb6 + 0x38 + (uint)*(byte *)0x8b2 * -4;
      DAT_1ce5_4e06 = *(int *)0xba + 0x51;
      DAT_1ce5_4e04 = *(undefined2 *)0x7fe;
      DAT_1ce5_4e02 = 0xd;
      DAT_1ce5_4e00 = 8;
      DAT_1ce5_4dfe = 0xa000;
      DAT_1ce5_4dfc = 0;
      DAT_1ce5_4dfa = 0x624e;
      FUN_1000_03a7();
      DAT_1ce5_4e0c = (*(int *)0x9bc * 10 + 100) * *(int *)0x8b0;
      DAT_1ce5_4e08 = 0x6263;
      DAT_1ce5_4e0a = uVar12;
      FUN_1af8_02c6();
      DAT_1ce5_4e0c = 0x14;
      DAT_1ce5_4e0a = 0x1af8;
      DAT_1ce5_4e08 = 0x626c;
      FUN_1af8_029e();
      DAT_1ce5_4e0c = 0x1af8;
      DAT_1ce5_4e0a = 0x6271;
      FUN_1af8_02f3();
      DAT_1ce5_4e0c = 0x78;
      DAT_1ce5_4e0a = 0x1af8;
      uVar12 = 0x1af8;
      DAT_1ce5_4e08 = 0x627a;
      FUN_1af8_029e();
      if (*(int *)0x9bc == 4) break;
      *(int *)0x9bc = *(int *)0x9bc + 1;
    }
    if (*(int *)0x89c == 0) {
      DAT_1ce5_4e0a = 0x6ec;
      DAT_1ce5_4e08 = *(int *)0xb6 + 0x38 + (uint)*(byte *)0x6ec * -4;
      DAT_1ce5_4e06 = *(int *)0xba + 0x5e;
      DAT_1ce5_4e04 = 0;
      DAT_1ce5_4e02 = 0xd;
      DAT_1ce5_4e00 = 8;
      DAT_1ce5_4dfe = 0xa000;
      DAT_1ce5_4dfc = 0;
      DAT_1ce5_4dfa = 0x62c4;
      FUN_1000_03a7();
    }
    else {
      DAT_1ce5_4e0c = 0x62c9;
      FUN_1000_0b92();
      DAT_1ce5_4e0c = 0x15;
      DAT_1ce5_4e0a = 0x62d0;
      FUN_1000_12aa();
      DAT_1ce5_4e0c = 3;
      DAT_1ce5_4e0a = 0x62d7;
      FUN_1000_2a82();
      if (*(char *)0x6ec == '\0') {
        DAT_1ce5_4e0c = *(int *)0xb6 / 8 + -1 + (*(int *)0xba + -0x3c) * 0x50;
        DAT_1ce5_4e0a = 0xa7;
        DAT_1ce5_4e08 = 0x10;
        DAT_1ce5_4e06 = 7;
        DAT_1ce5_4e04 = 0x630e;
        FUN_1000_068d();
      }
      else {
        *(undefined2 *)0x89c = 0;
      }
    }
    DAT_1ce5_4e0c = 10;
    DAT_1ce5_4e0a = 0x6315;
    FUN_1000_0ab4();
    DAT_1ce5_4e0c = 0x6318;
    FUN_1000_0b92();
    *(undefined2 *)0x9bc = 0;
    while (*(undefined2 *)(*(int *)0x9bc * 2 + 0x64e) = 0, *(int *)0x9bc != 0x1f) {
      *(int *)0x9bc = *(int *)0x9bc + 1;
    }
    *(undefined2 *)0x9bc = 1;
    while( true ) {
      DAT_1ce5_4e0c = *(undefined2 *)0x9bc;
      DAT_1ce5_4e0a = 0x6349;
      FUN_1000_0c00();
      if (*(int *)0x9bc == 3) break;
      *(int *)0x9bc = *(int *)0x9bc + 1;
    }
    DAT_1ce5_4e0c = 0x6353;
    FUN_1000_2c8e();
    out(0x3ce,5);
    out(0x3cf,0);
    DAT_1ce5_4e0c = 1;
    DAT_1ce5_4e0a = 8;
    DAT_1ce5_4e08 = 0x1af8;
    DAT_1ce5_4e06 = 0x636c;
    FUN_17cc_0b9e();
    DAT_1ce5_4f0c = (uint)*(byte *)0x6a4;
    if (DAT_1ce5_4f0c != 0) {
      *(undefined2 *)0x9bc = 1;
      while (*(undefined2 *)(*(int *)0x9bc * 2 + 0x5fc) = 0, *(uint *)0x9bc != DAT_1ce5_4f0c) {
        *(int *)0x9bc = *(int *)0x9bc + 1;
      }
    }
    DAT_1ce5_4f0c = (uint)*(byte *)0x6a4;
    if (DAT_1ce5_4f0c != 0) {
      *(undefined2 *)0x9bc = 1;
      while( true ) {
        DAT_1ce5_4e0c = (*(int *)0x9bc + 5) * 0x10 + 0x79;
        DAT_1ce5_4e0a = 0x24;
        DAT_1ce5_4e08 = (*(int *)0x9bc + 5) * 0x10 + 0x86;
        DAT_1ce5_4e06 = 0x36;
        DAT_1ce5_4e04 = 0x17cc;
        DAT_1ce5_4e02 = 0x63dd;
        FUN_17cc_13aa();
        if (*(uint *)0x9bc == DAT_1ce5_4f0c) break;
        *(int *)0x9bc = *(int *)0x9bc + 1;
      }
    }
    uVar12 = 0x17cc;
    DAT_1ce5_4e0c = 9;
    DAT_1ce5_4e0a = 0x63ec;
    FUN_1000_12aa();
    DAT_1ce5_4e0c = 0x32;
    DAT_1ce5_4e0a = 0x63f3;
    FUN_1000_0ab4();
    DAT_1ce5_4e0c = 0x63f6;
    FUN_1000_0b92();
    DAT_1ce5_4e0c = 10;
    DAT_1ce5_4e0a = 0x63fd;
    FUN_1000_12aa();
    DAT_1ce5_4e0c = 0;
    DAT_1ce5_4e0a = 0x6403;
    FUN_1000_0ab4();
    DAT_1ce5_4e0c = 0x6406;
    FUN_1000_0b92();
    *(undefined2 *)0x8a4 = 1;
    *(undefined2 *)0x5fa = 0;
    do {
      if ((*(int *)0x5fa == 3) && (1 < *(int *)0x8a4)) {
        DAT_1ce5_4e0c = 5;
        DAT_1ce5_4e0a = 0x6426;
        FUN_1000_12aa();
        DAT_1ce5_4e0c = 4;
        DAT_1ce5_4e0a = 0x642d;
        uVar6 = FUN_1000_3655();
        *(undefined2 *)0x9bc = uVar6;
        *(undefined2 *)0x5fa = 0;
      }
      *(int *)0x5fa = *(int *)0x5fa + 1;
      *(undefined2 *)0x5fc = 0;
      if (3 < *(int *)0x8a4) {
        *(undefined2 *)0x8a4 = 1;
      }
      while (0 < *(int *)(*(int *)0x8a4 * 2 + 0x896)) {
        *(int *)0x8a4 = *(int *)0x8a4 + 1;
        if (3 < *(int *)0x8a4) {
          *(undefined2 *)0x8a4 = 1;
        }
      }
      DAT_1ce5_4e0c = 1;
      DAT_1ce5_4e0a = 0x6472;
      FUN_1000_12aa();
      *(undefined2 *)0x5f8 = 0;
      if (1 < *(int *)0x8a4) {
        DAT_1ce5_4e0c = 1;
        DAT_1ce5_4e0a = 0x6485;
        uVar6 = FUN_1000_3655();
        *(undefined2 *)0x5f8 = uVar6;
      }
      if (*(int *)0x5f8 == 0) {
        DAT_1ce5_4e0c = 0x6495;
        FUN_1000_2f07();
        DAT_1ce5_4e0c = 2;
        DAT_1ce5_4e0a = 0x649c;
        FUN_1000_12aa();
        if ((*(int *)0x896 == 300) && (1 < *(int *)0x8a4)) {
          DAT_1ce5_4e0c = 2;
          DAT_1ce5_4e0a = 0x64b2;
          uVar6 = FUN_1000_3655();
          *(undefined2 *)0x5f8 = uVar6;
          if (*(int *)0x5f8 == 0) {
            DAT_1ce5_4e0c = 0x64bf;
            FUN_1000_0b92();
            DAT_1ce5_4e0c = 0xf;
            DAT_1ce5_4e0a = 0x64c6;
            FUN_1000_12aa();
          }
          else {
            DAT_1ce5_4e0c = 0x64cb;
            FUN_1000_46a5();
          }
        }
        if (*(int *)0x5f8 == 0) {
          DAT_1ce5_4e0c = 0x28;
          DAT_1ce5_4e0a = 0x64d9;
          FUN_1000_0ab4();
          DAT_1ce5_4e0c = 0x64dc;
          FUN_1000_0b92();
          if (*(int *)0x896 < 0) {
            *(undefined2 *)(*(int *)0x8a4 * 2 + 0x89c) = 0;
            DAT_1ce5_4e0c = *(undefined2 *)0x8a4;
            DAT_1ce5_4e0a = 0x64f6;
            FUN_1000_0c00();
          }
          if (*(int *)0x896 < 1) {
            *(undefined2 *)0x5f8 = 0;
            *(int *)0x8a4 = *(int *)0x8a4 + 1;
            *(undefined2 *)0x5fa = 0;
          }
          else {
            if (*(int *)0x896 == 100) {
              DAT_1ce5_4e0c = 0x6517;
              FUN_1000_229a();
            }
            else {
              DAT_1ce5_4e0c = 0x651c;
              FUN_1000_1dd3();
            }
            if (*(int *)0x5fc < 1) {
              *(int *)0x8a4 = *(int *)0x8a4 + 1;
              *(undefined2 *)0x5fa = 0;
            }
            else {
              DAT_1ce5_4e0c = 0x6526;
              FUN_1000_193a();
            }
          }
        }
      }
      *(undefined2 *)0x7fe = 0;
      DAT_1ce5_4f0c = (uint)*(byte *)0x6a4;
      if (DAT_1ce5_4f0c != 0) {
        *(undefined2 *)0x9bc = 1;
        while( true ) {
          if (*(int *)(*(int *)0x9bc * 2 + 0x5fc) == 0) {
            *(int *)0x7fe = *(int *)0x7fe + 1;
          }
          if (*(uint *)0x9bc == DAT_1ce5_4f0c) break;
          *(int *)0x9bc = *(int *)0x9bc + 1;
        }
      }
      if (*(int *)0x7fe == 0) {
        DAT_1ce5_4e0c = 0x6572;
        FUN_1000_0b92();
      }
      if (*(int *)0x5f8 == 1) {
        DAT_1ce5_4e0c = 0x657f;
        FUN_1000_0b92();
        DAT_1ce5_4e0c = 0x6582;
        uVar6 = FUN_1000_274b();
        *(undefined2 *)0x5f8 = uVar6;
        if (*(int *)0x5f8 == 0) {
          DAT_1ce5_4e0c = 0xb;
          DAT_1ce5_4e0a = 0x6593;
          FUN_1000_12aa();
        }
        else {
          DAT_1ce5_4e0c = 0xc;
          DAT_1ce5_4e0a = 0x659c;
          FUN_1000_12aa();
        }
        if (*(int *)0x5f8 == 0) {
          *(undefined2 *)0x7fe = 0;
        }
        else {
          *(undefined2 *)0x7fe = 1;
          *(undefined2 *)(*(int *)0x8a4 * 2 + 0x896) = 2;
          DAT_1ce5_4e0c =
               *(int *)(*(int *)0x8a4 * 2 + 0xb0) / 8 + -1 +
               (*(int *)(*(int *)0x8a4 * 2 + 0xb4) + -0x3c) * 0x50;
          DAT_1ce5_4e0a = 0xa7;
          DAT_1ce5_4e08 = 0x10;
          DAT_1ce5_4e06 = 7;
          DAT_1ce5_4e04 = 0x65f3;
          FUN_1000_068d();
          *(int *)0x8a4 = *(int *)0x8a4 + 1;
          *(undefined2 *)0x5fa = 0;
        }
        DAT_1ce5_4e0c = 0x32;
        DAT_1ce5_4e0a = 0x6603;
        FUN_1000_0ab4();
        DAT_1ce5_4e0c = 0x6606;
        FUN_1000_0b92();
      }
    } while (*(int *)0x7fe != 0);
    DAT_1ce5_4e0c = 4;
    DAT_1ce5_4e0a = 0x6617;
    FUN_1000_12aa();
    DAT_1ce5_4e0c = 0x14;
    DAT_1ce5_4e0a = 0x661e;
    FUN_1000_0ab4();
    iVar5 = *(int *)0x8a4;
    if (iVar5 == 1) {
      *(undefined2 *)0x89a = 2;
      *(undefined2 *)0x89c = 2;
      *(undefined2 *)((*(int *)0x8a6 + 1) * 2 + 0x57e) = *(undefined2 *)(*(int *)0x8a6 * 2 + 0x57e);
    }
    else if (iVar5 == 2) {
      *(undefined2 *)0x89c = 2;
    }
    else if (iVar5 == 3) {
      *(undefined2 *)0x89a = 2;
    }
    *(int *)0x8a6 = *(int *)0x8a6 + 1;
    DAT_1ce5_4e0c = 0x6669;
    FUN_1000_0b92();
    DAT_1ce5_4e0c = 0x10;
    DAT_1ce5_4e0a = 0x6670;
    FUN_1000_12aa();
    DAT_1ce5_4e0c = 0;
    DAT_1ce5_4e0a = 0x6676;
    FUN_1000_0ab4();
    DAT_1ce5_4e0c = 0x6679;
    FUN_1000_0b92();
    DAT_1ce5_4e0c = 0x667c;
    FUN_1000_54bb();
  } while (*(int *)0x8a6 < 8);
  DAT_1ce5_4e0c = 0x6689;
  FUN_1000_4c74();
  DAT_1ce5_4e0c = 0x668c;
  FUN_1000_0000();
  uVar12 = DAT_1ce5_4f0e;
  DAT_1ce5_4f0e = 0x17cc;
  DAT_1ce5_4f0c = 0x6696;
  FUN_1b5a_00d8();
  uVar13 = (undefined2)((ulong)uRam00021d6c >> 0x10);
  uVar6 = (undefined2)((ulong)uRam00021d68 >> 0x10);
  DAT_1ce5_4f0c = *(int *)((int)uRam00021d6c + 2);
  piVar10 = (int *)((int)uRam00021d6c + 6);
  pcVar11 = (char *)((int)uRam00021d68 + iRam00021d64 * 0x50 + (uRam00021d66 >> 3));
  bRam00021d56 = (byte)uRam00021d66 & 7;
  out(0x3ce,0x205);
  out(0x3ce,8);
  uRam00021d54 = unaff_DS;
  DAT_1ce5_4f0e = uVar12;
  do {
    bRam00021d58 = bRam00021d56;
    piVar3 = piVar10 + 1;
    piRam00021d5a = (int *)(*piVar10 + (int)piVar3);
    piVar10 = (int *)((int)piVar10 + 3);
    cVar8 = (char)*piVar3;
    pcRam00021d52 = pcVar11;
    do {
      if (cVar8 < '\0') {
        bVar7 = 0xff >> (bRam00021d58 & 0x1f);
        piVar1 = piVar10;
        piVar10 = (int *)((int)piVar10 + 1);
        cVar2 = (char)*piVar1;
        if (cVar2 == cRam00021d62) {
          bVar7 = cVar8 + -0x80 + bRam00021d58;
          bRam00021d58 = bVar7;
          if ('\a' < (char)bVar7) {
            bRam00021d58 = 0;
          }
          bVar7 = bVar7 - 8;
          if (-1 < (char)bVar7) {
            for (; pcVar11 = pcVar11 + 1, bRam00021d58 = bVar7, '\a' < (char)bVar7;
                bVar7 = bVar7 - 8) {
            }
          }
        }
        else {
          bVar9 = cVar8 + -0x80 + bRam00021d58;
          if (bVar9 < 8) {
            bVar7 = -2 << ((bVar9 ^ 7) & 0x1f) & bVar7;
            bRam00021d58 = bVar9;
          }
          else {
            bRam00021d58 = 0;
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
            bRam00021d58 = bVar9;
          }
        }
      }
      else {
        bVar7 = 0x80 >> (bRam00021d58 & 0x1f);
        do {
          piVar1 = piVar10;
          piVar10 = (int *)((int)piVar10 + 1);
          if ((char)*piVar1 != cRam00021d62) {
            out(0x3cf,bVar7);
            *pcVar11 = (char)*piVar1;
          }
          bRam00021d58 = bRam00021d58 + 1;
          bVar14 = (bool)(bVar7 & 1);
          bVar7 = bVar7 >> 1 | bVar14 << 7;
          if (bVar14) {
            pcVar11 = pcVar11 + 1;
            bRam00021d58 = 0;
          }
          cVar8 = cVar8 + -1;
        } while (cVar8 != '\0');
      }
      piVar1 = piVar10;
      piVar10 = (int *)((int)piVar10 + 1);
      cVar8 = (char)*piVar1;
    } while (piRam00021d5a != piVar10);
    pcVar11 = pcRam00021d52 + 0x50;
    DAT_1ce5_4f0c = DAT_1ce5_4f0c + -1;
  } while (DAT_1ce5_4f0c != 0);
  return;
}



/* 1000:6696 FUN_1000_6696 */

void FUN_1000_6696(char param_1,int param_2,uint param_3,undefined4 param_4,undefined4 param_5)

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
          bVar5 = bVar5 >> 1 | bVar13 << 7;
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



/* 1000:6e45 FUN_1000_6e45 */

undefined4 __cdecl16near FUN_1000_6e45(void)

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



/* 1000:6e6a FUN_1000_6e6a */

void __cdecl16near FUN_1000_6e6a(void)

{
  if (cRam00010258 != '\0') {
    out(0x3ce,0x1803);
  }
  return;
}



/* 1000:6e94 FUN_1000_6e94 */

long __cdecl16near
FUN_1000_6e94(uint param_1,int param_2,uint param_3,int param_4,undefined1 param_5)

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
  FUN_1000_6e6a();
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
        bVar4 = bVar4 >> 1 | bVar12 << 7;
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
        bVar4 = bVar4 >> 1 | bVar11 << 7;
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
        bVar4 = bVar4 >> 1 | bVar12 << 7;
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
  FUN_1000_6e45();
  out(extraout_DX,0xff);
  out(extraout_DX + -1,1);
  out(extraout_DX,0);
  return (ulong)CONCAT21(extraout_DX,extraout_AH) << 8;
}



/* 17cc:0055 FUN_17cc_0055 */

void __cdecl16far FUN_17cc_0055(void)

{
  undefined2 unaff_DS;
  undefined2 uVar1;
  
  if (*(char *)0xdda == '\0') {
    uVar1 = 0xf46;
    FUN_1b5a_15e1(0,0,0x17cc);
    FUN_1b5a_1564(uVar1,unaff_DS);
    FUN_1b5a_020e();
  }
  else {
    uVar1 = 0xf46;
    FUN_1b5a_15e1(0,0x34,0x17cc);
    FUN_1b5a_1564(uVar1,unaff_DS);
    FUN_1b5a_020e();
  }
  FUN_1b5a_00d8();
  return;
}



/* 17cc:00a5 FUN_17cc_00a5 */

undefined2 __stdcall16far FUN_17cc_00a5(void)

{
  return 1;
}



/* 17cc:00b9 FUN_17cc_00b9 */

void __stdcall16far FUN_17cc_00b9(undefined2 param_1,undefined2 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = FUN_1b5a_0329(param_1);
  *param_2 = (int)uVar1;
  ((undefined2 *)param_2)[1] = (int)((ulong)uVar1 >> 0x10);
  return;
}



/* 17cc:00d4 FUN_17cc_00d4 */

void __stdcall16far FUN_17cc_00d4(undefined2 param_1,int *param_2)

{
  int *piVar1;
  undefined2 uVar2;
  
  uVar2 = (undefined2)((ulong)param_2 >> 0x10);
  piVar1 = (int *)param_2;
  if (*param_2 != 0 || piVar1[1] != 0) {
    FUN_1b5a_0341(param_1,*param_2,piVar1[1]);
  }
  *param_2 = 0;
  piVar1[1] = 0;
  return;
}



/* 17cc:0107 FUN_17cc_0107 */

long FUN_17cc_0107(undefined2 *param_1,int *param_2,undefined4 param_3)

{
  uint uVar1;
  uint uVar2;
  undefined4 local_6;
  
  uVar1 = (int)param_3 + *param_2;
  uVar2 = (uVar1 >> 4) + param_3._2_2_;
  if ((uVar1 & 0xf) != 0) {
    FUN_1b5a_185c(*param_1,0,uVar2,uVar1,param_3._2_2_);
    *param_2 = *param_2 - (uVar1 & 0xf);
  }
  local_6 = (ulong)uVar2 << 0x10;
  return local_6;
}



/* 17cc:016f FUN_17cc_016f */

int __stdcall16far FUN_17cc_016f(undefined4 param_1)

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
  int local_10;
  int local_e;
  undefined2 local_c;
  int local_a;
  int local_8;
  undefined2 local_6;
  int local_4;
  
  uVar3 = *(char *)0xdda == '\0';
  if ((bool)uVar3) {
    *(undefined2 *)0xda4 = 0xfffc;
    local_4 = -4;
    puVar6 = local_10a;
    uVar2 = (undefined2)((ulong)param_1 >> 0x10);
    iVar1 = (int)param_1;
    FUN_1b5a_076c(2,iVar1,uVar2);
    FUN_1b5a_072f(0x16c,0x1b5a,puVar6,unaff_SS);
    if ((bool)uVar3) {
      local_e = iVar1 + 0x80;
      _local_8 = CONCAT22(uVar2,local_e);
      if (((1 < *(byte *)(iVar1 + 0x86)) && (*(byte *)(iVar1 + 0x88) < 2)) &&
         (local_10 = *(int *)0xd44, -1 < local_10)) {
        local_a = 0;
        local_c = uVar2;
        while( true ) {
          bVar4 = local_e + 10 == 0;
          FUN_1b5a_072f(local_e + 10,local_c,local_a * 0x1a + 0x2fa,unaff_DS);
          if (bVar4) break;
          if (local_a == local_10) {
            return local_4;
          }
          local_a = local_a + 1;
        }
        uVar5 = FUN_17cc_0107(local_e + 4,local_c,local_e,local_c,iVar1,uVar2);
        *(undefined2 *)(local_a * 0x1a + 0x310) = (int)uVar5;
        *(undefined2 *)(local_a * 0x1a + 0x312) = (int)((ulong)uVar5 >> 0x10);
        local_4 = local_a;
        *(undefined2 *)0xda4 = 0;
      }
    }
  }
  else {
    *(undefined2 *)0xda4 = 0xfff5;
    local_4 = -0xb;
  }
  return local_4;
}



/* 17cc:026a FUN_17cc_026a */

int __stdcall16far FUN_17cc_026a(undefined4 param_1)

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
  undefined2 local_e;
  uint local_c;
  int local_a;
  int local_8;
  undefined2 local_6;
  int local_4;
  
  uVar4 = &stack0x0000 == (undefined1 *)0x114;
  *(undefined2 *)0xda4 = 0xfff3;
  local_4 = *(int *)0xda4;
  puVar6 = local_10c;
  uVar3 = (undefined2)((ulong)param_1 >> 0x10);
  iVar2 = (int)param_1;
  uVar7 = unaff_SS;
  FUN_1b5a_076c(2,iVar2,uVar3);
  FUN_1b5a_072f(0x267,0x1b5a,puVar6,uVar7);
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
        local_e = uVar3;
        while( true ) {
          iVar1 = local_a * 0xf + 0x413;
          puVar6 = local_110;
          uVar4 = local_10 + 2 == 0;
          uVar7 = unaff_SS;
          uVar8 = unaff_DS;
          FUN_1b5a_076c(4,local_10 + 2,local_e);
          FUN_1b5a_072f(puVar6,uVar7,iVar1,uVar8);
          if ((bool)uVar4) break;
          if (local_a == 0x14) {
            return local_4;
          }
          local_a = local_a + 1;
        }
        iVar1 = local_a * 0xf;
        _local_114 = (undefined2 *)CONCAT22(unaff_DS,(undefined2 *)(iVar1 + 0x409));
        (*(code *)*(undefined2 *)0xc52)
                  (0x1b5a,*(undefined2 *)(iVar1 + 0x411),(undefined2 *)(iVar1 + 0x409),unaff_DS);
        *_local_114 = 0;
        *(undefined2 *)(iVar1 + 0x40b) = 0;
        uVar5 = FUN_17cc_0107(local_10 + 6,local_e,local_10,local_e,iVar2,uVar3);
        *(undefined2 *)(iVar1 + 0x40d) = (int)uVar5;
        *(undefined2 *)(iVar1 + 0x40f) = (int)((ulong)uVar5 >> 0x10);
        *(undefined2 *)(iVar1 + 0x411) = 0;
        local_4 = local_a;
        *(undefined2 *)0xda4 = 0;
      }
    }
  }
  return local_4;
}



/* 17cc:03b9 FUN_17cc_03b9 */

void __cdecl16near FUN_17cc_03b9(void)

{
  undefined2 unaff_DS;
  
  *(undefined2 *)0xdac = 0x55;
  *(undefined2 *)0xdae = 0x17cc;
  *(undefined2 *)0xdbe = 0x55;
  *(undefined2 *)0xdc0 = 0x17cc;
  *(undefined2 *)0xdb0 = 0;
  *(undefined2 *)0xdb2 = 0;
  *(undefined2 *)0xdc2 = 0;
  *(undefined2 *)0xdc4 = 0;
  *(undefined2 *)0xdb4 = 0;
  *(undefined2 *)0xdb6 = 0;
  *(undefined2 *)0xdba = 0;
  *(undefined2 *)0xdbc = 0;
  *(undefined2 *)0xd6c = 0;
  *(undefined2 *)0xd6e = 0;
  *(undefined2 *)0xd70 = 0;
  *(undefined2 *)0xd86 = 0;
  *(undefined2 *)0xd88 = 0;
  *(undefined2 *)0xd8a = 0;
  *(undefined1 *)0xd76 = 0;
  *(undefined2 *)0xdd6 = 1;
  *(undefined2 *)0xdd8 = 1;
  *(undefined2 *)0xcd6 = 0;
  *(undefined1 *)0xdda = 0;
  return;
}



/* 17cc:042f FUN_17cc_042f */

undefined1 FUN_17cc_042f(undefined2 param_1,uint *param_2,undefined4 param_3,undefined4 param_4)

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
  
  FUN_1b5a_0644(0xff,local_104,unaff_SS,(int)param_4,(int)((ulong)param_4 >> 0x10));
  FUN_1b5a_0644(0xff,local_204,unaff_SS,(int)param_3,(int)((ulong)param_3 >> 0x10));
  local_3 = 0;
  *(undefined2 *)0xda4 = 0xfffd;
  *param_2 = 0;
  uVar5 = 0xc56;
  puVar3 = local_304;
  uVar4 = unaff_SS;
  uVar6 = unaff_DS;
  FUN_1b5a_062a(local_104,unaff_SS);
  FUN_1b5a_06b7(local_204,unaff_SS);
  FUN_1b5a_161f(puVar3,uVar4,uVar5,uVar6);
  FUN_1b5a_164d(1,0xc56,unaff_DS);
  iVar1 = FUN_1b5a_0207();
  if (iVar1 != 0) {
    if (local_104[0] == '\0') {
      return local_3;
    }
    FUN_1b5a_161f(local_204,unaff_SS,0xc56,unaff_DS);
    FUN_1b5a_164d(1,0xc56,unaff_DS);
    iVar1 = FUN_1b5a_0207();
    if (iVar1 != 0) {
      return local_3;
    }
  }
  *(undefined2 *)0xda4 = 0;
  uVar2 = FUN_1b5a_17e7(0xc56,unaff_DS);
  *param_2 = uVar2;
  if (*param_2 < 0x3c01) {
    local_3 = 1;
  }
  else {
    *(undefined2 *)0xda4 = param_1;
    FUN_1b5a_16ce(0xc56,unaff_DS);
  }
  return local_3;
}



/* 17cc:0524 FUN_17cc_0524 */

undefined1 FUN_17cc_0524(undefined4 param_1,int param_2)

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
  
  FUN_1b5a_0644(0xff,local_104,unaff_SS,(int)param_1,(int)((ulong)param_1 >> 0x10));
  local_3 = 0;
  puVar4 = local_210;
  uVar5 = unaff_SS;
  FUN_1b5a_062a(param_2 * 0x1a + 0x2fa,unaff_DS);
  FUN_1b5a_06b7(0x51f,0x1b5a);
  FUN_1b5a_0644(0xc,0xce2,unaff_DS,puVar4,uVar5);
  if (*(int *)(param_2 * 0x1a + 0x310) == 0 && *(int *)(param_2 * 0x1a + 0x312) == 0) {
    cVar2 = FUN_17cc_042f(0xfffc,0xdb8,unaff_DS,0xce2,unaff_DS,local_104,unaff_SS);
    if (cVar2 != '\0') {
      uVar1 = *(undefined4 *)0x566;
      *(undefined2 *)0xd48 = (int)uVar1;
      *(undefined2 *)0xd4a = (int)((ulong)uVar1 >> 0x10);
      *(undefined2 *)0x566 = 0xa5;
      *(undefined2 *)0x568 = 0x17cc;
      (*(code *)*(undefined2 *)0xc4e)(0x1b5a,*(undefined2 *)0xdb8,0xdb4);
      uVar1 = *(undefined4 *)0xd48;
      *(undefined2 *)0x566 = (int)uVar1;
      *(undefined2 *)0x568 = (int)((ulong)uVar1 >> 0x10);
      if (*(int *)0xdb4 == 0 && *(int *)0xdb6 == 0) {
        *(undefined2 *)0xda4 = 0xfffb;
      }
      else {
        FUN_1b5a_1738(local_10c,unaff_SS,*(undefined2 *)0xdb8,(int)*(undefined4 *)0xdb4,
                      (int)((ulong)*(undefined4 *)0xdb4 >> 0x10),0xc56,unaff_DS);
        FUN_1b5a_16ce(0xc56,unaff_DS);
        iVar3 = FUN_1b5a_0207();
        if (((iVar3 == 0) && (local_10c[0] == *(int *)0xdb8)) &&
           (iVar3 = FUN_17cc_016f(*(undefined2 *)0xdb4,*(undefined2 *)0xdb6), iVar3 == param_2)) {
          uVar1 = *(undefined4 *)(param_2 * 0x1a + 0x310);
          *(undefined2 *)0xdbe = (int)uVar1;
          *(undefined2 *)0xdc0 = (int)((ulong)uVar1 >> 0x10);
          local_3 = 1;
        }
        else {
          *(undefined2 *)0xda4 = 0xfffc;
          (*(code *)*(undefined2 *)0xc52)(0x1b5a,*(undefined2 *)0xdb8,0xdb4);
        }
      }
    }
  }
  else {
    uVar1 = *(undefined4 *)(param_2 * 0x1a + 0x310);
    *(undefined2 *)0xdbe = (int)uVar1;
    *(undefined2 *)0xdc0 = (int)((ulong)uVar1 >> 0x10);
    *(undefined2 *)0xdb4 = 0;
    *(undefined2 *)0xdb6 = 0;
    *(undefined2 *)0xdb8 = 0;
    local_3 = 1;
  }
  return local_3;
}



/* 17cc:0699 FUN_17cc_0699 */

void __cdecl16far FUN_17cc_0699(void)

{
  int iVar1;
  undefined2 uVar2;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar3;
  undefined2 uVar4;
  undefined1 local_a [8];
  
  if (*(char *)0xdda == '\0') {
    FUN_17cc_0055();
  }
  FUN_17cc_0a63(1,*(undefined2 *)0xd50,*(undefined2 *)0xd4e,0,0);
  FUN_17cc_0d65(0xe06,unaff_DS);
  FUN_17cc_0c5d(0xe06,unaff_DS);
  iVar1 = FUN_17cc_14c6();
  if (iVar1 != 1) {
    FUN_17cc_0c26(0);
  }
  *(undefined1 *)0xdcc = 0;
  uVar2 = FUN_17cc_14b6();
  FUN_17cc_149e(uVar2);
  FUN_1b5a_187f(0xff,8,local_a,unaff_SS);
  puVar3 = local_a;
  uVar2 = FUN_17cc_14b6(puVar3);
  FUN_17cc_0bcb(uVar2,puVar3,unaff_SS);
  uVar4 = 1;
  uVar2 = FUN_17cc_14b6(1);
  FUN_17cc_0b9e(uVar2,uVar4);
  FUN_17cc_0b19(1,0,0);
  FUN_17cc_0dca(1,0,0);
  FUN_17cc_0d86(2,0);
  FUN_17cc_11c3(0x1b5a,0);
  FUN_17cc_0afa(0,0);
  return;
}



/* 17cc:0759 FUN_17cc_0759 */

void __stdcall16far FUN_17cc_0759(undefined4 param_1,int *param_2,int *param_3)

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
  
  FUN_1b5a_0644(0xff,local_102,unaff_SS,(int)param_1,(int)((ulong)param_1 >> 0x10));
  *(undefined2 *)0xdac = 0x18df;
  *(undefined2 *)0xdae = 0x17cc;
  uVar3 = FUN_17cc_0107((int)*(undefined4 *)0xdac + 2,(int)((ulong)*(undefined4 *)0xdac >> 0x10),
                        (int)*(undefined4 *)0xdac,(int)((ulong)*(undefined4 *)0xdac >> 0x10),
                        *(undefined2 *)0xdac,*(undefined2 *)0xdae);
  *(undefined2 *)0xdac = (int)uVar3;
  *(undefined2 *)0xdae = (int)((ulong)uVar3 >> 0x10);
  local_109 = '\0';
  if (*param_3 == 0) {
    local_106 = 0;
    local_108 = -1;
    while ((local_106 < *(int *)0xd44 && (local_108 < 0))) {
      if (*(int *)(local_106 * 0x1a + 0x30c) != 0 || *(int *)(local_106 * 0x1a + 0x30e) != 0) {
        uVar3 = *(undefined4 *)(local_106 * 0x1a + 0x30c);
        *(undefined2 *)0xe22 = (int)uVar3;
        *(undefined2 *)0xe24 = (int)((ulong)uVar3 >> 0x10);
        local_108 = (*(code *)*(undefined2 *)0xe22)(0x1b5a);
        if (-1 < local_108) {
          *(int *)0xda0 = local_106;
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
    FUN_17cc_1264((int *)param_2,uVar2,(int *)param_3,(int)((ulong)param_3 >> 0x10),0xda0,unaff_DS);
  }
  else {
    local_106 = *(int *)0xda0;
    local_108 = *param_3 + 0x80;
    FUN_17cc_1264((int *)param_2,uVar2,&local_108,unaff_SS,&local_106,unaff_SS);
  }
  if (*param_3 < 0) {
    *(undefined2 *)0xda4 = 0xfffe;
    *param_3 = -2;
    FUN_17cc_03b9();
  }
  else {
    *(int *)0xda2 = *param_2;
    FUN_1b5a_0644(0x50,0xcf0,unaff_DS,local_102,unaff_SS);
    if (((*(char *)0xcf0 != '\0') &&
        (local_103 = *(char *)(*(byte *)0xcf0 + 0xcf0), local_103 != ':')) && (local_103 != '\\')) {
      puVar4 = local_20a;
      FUN_1b5a_062a(local_102,unaff_SS);
      FUN_1b5a_06b7(0x757,0x1b5a);
      FUN_1b5a_0644(0x50,0xcf0,unaff_DS,puVar4,unaff_SS);
    }
    cVar1 = FUN_17cc_0524(0xcf0,unaff_DS,*(undefined2 *)0xda0);
    if (cVar1 == '\0') {
      *param_3 = *(int *)0xda4;
      FUN_17cc_03b9();
    }
    else {
      FUN_1b5a_187f(0,0x3f,0xd60,unaff_DS);
      uVar3 = *(undefined4 *)0x566;
      *(undefined2 *)0xd48 = (int)uVar3;
      *(undefined2 *)0xd4a = (int)((ulong)uVar3 >> 0x10);
      *(undefined2 *)0x566 = 0xa5;
      *(undefined2 *)0x568 = 0x17cc;
      (*(code *)*(undefined2 *)0xc4e)(0x1b5a,*(undefined2 *)0xd42,0xd6c);
      uVar3 = *(undefined4 *)0xd48;
      *(undefined2 *)0x566 = (int)uVar3;
      *(undefined2 *)0x568 = (int)((ulong)uVar3 >> 0x10);
      if (*(int *)0xd6c == 0 && *(int *)0xd6e == 0) {
        *(undefined2 *)0xda4 = 0xfffb;
        *param_3 = -5;
        (*(code *)*(undefined2 *)0xc52)(0x1b5a,*(undefined2 *)0xdb8,0xdb4);
        FUN_17cc_03b9();
      }
      else {
        *(undefined1 *)0xd61 = 0;
        *(undefined1 *)0xd76 = 0;
        uVar3 = *(undefined4 *)0xd6c;
        *(undefined2 *)0xdba = (int)uVar3;
        *(undefined2 *)0xdbc = (int)((ulong)uVar3 >> 0x10);
        *(undefined2 *)0xd70 = *(undefined2 *)0xd42;
        uVar3 = *(undefined4 *)0xd6c;
        *(undefined2 *)0xd86 = (int)uVar3;
        *(undefined2 *)0xd88 = (int)((ulong)uVar3 >> 0x10);
        *(undefined2 *)0xd8a = *(undefined2 *)0xd42;
        *(undefined2 *)0xd7a = 0xda4;
        *(undefined2 *)0xd7c = unaff_DS;
        FUN_17cc_10c8(0x1b5a,0xd60);
        FUN_1b5a_185c(0x13,0xd4c,unaff_DS,*(undefined2 *)0xdc6,*(undefined2 *)0xdc8);
        FUN_17cc_1312(0xd60,unaff_DS);
        if (*(char *)0xd4c == '\0') {
          uVar2 = FUN_17cc_14ff();
          *(undefined2 *)0xdd4 = uVar2;
          *(undefined2 *)0xdd6 = *(undefined2 *)0xd5a;
          *(undefined2 *)0xdd8 = 10000;
          *(undefined1 *)0xdda = 1;
          FUN_17cc_0699();
          *(undefined2 *)0xda4 = 0;
        }
        else {
          *(uint *)0xda4 = (uint)*(byte *)0xd4c;
          FUN_17cc_03b9();
        }
      }
    }
  }
  return;
}



/* 17cc:0a35 FUN_17cc_0a35 */

void __cdecl16far FUN_17cc_0a35(void)

{
  undefined4 uVar1;
  undefined2 unaff_DS;
  
  FUN_17cc_1157();
  if (*(int *)0xdb0 == 0 && *(int *)0xdb2 == 0) {
    uVar1 = *(undefined4 *)0xdac;
    *(undefined2 *)0xdb0 = (int)uVar1;
    *(undefined2 *)0xdb2 = (int)((ulong)uVar1 >> 0x10);
    *(undefined2 *)0xdac = 0x55;
    *(undefined2 *)0xdae = 0x17cc;
  }
  return;
}



/* 17cc:0a63 FUN_17cc_0a63 */

void __stdcall16far
FUN_17cc_0a63(undefined1 param_1,uint param_2,uint param_3,int param_4,int param_5)

{
  undefined2 unaff_DS;
  bool bVar1;
  
  if ((-1 < param_5) && (-1 < param_4)) {
    bVar1 = (int)param_3 >> 0xf < 0;
    if ((-1 < (int)param_3 || bVar1) && ((bVar1 || (param_3 <= *(uint *)0xd4e)))) {
      bVar1 = (int)param_2 >> 0xf < 0;
      if ((-1 < (int)param_2 || bVar1) &&
         ((((bVar1 || (param_2 <= *(uint *)0xd50)) && (param_5 <= (int)param_3)) &&
          (param_4 <= (int)param_2)))) {
        *(int *)0xdde = param_5;
        *(int *)0xde0 = param_4;
        *(uint *)0xde2 = param_3;
        *(uint *)0xde4 = param_2;
        *(undefined1 *)0xde6 = param_1;
        FUN_17cc_1108(param_1,param_2,param_3,param_4,param_5);
        FUN_17cc_0afa(0,0);
        return;
      }
    }
  }
  *(undefined2 *)0xda4 = 0xfff5;
  return;
}



/* 17cc:0afa FUN_17cc_0afa */

void __stdcall16far FUN_17cc_0afa(undefined2 param_1,undefined2 param_2)

{
  undefined2 unaff_DS;
  
  FUN_17cc_133a(param_1,param_2);
  *(undefined2 *)0xdd0 = param_2;
  *(undefined2 *)0xdd2 = param_1;
  return;
}



/* 17cc:0b19 FUN_17cc_0b19 */

void __stdcall16far FUN_17cc_0b19(uint param_1,undefined2 param_2,uint param_3)

{
  undefined2 unaff_DS;
  
  if ((param_3 < 5) && (param_1 < 4)) {
    *(uint *)0xde8 = param_3;
    *(undefined2 *)0xdea = param_2;
    *(uint *)0xdec = param_1;
    FUN_17cc_156b(param_1,param_2,param_3);
  }
  else {
    *(undefined2 *)0xda4 = 0xfff5;
  }
  return;
}



/* 17cc:0b55 FUN_17cc_0b55 */

void __stdcall16far
FUN_17cc_0b55(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4)

{
  FUN_17cc_1362(param_3,param_2,param_3,param_4);
  FUN_17cc_1362(param_1,param_2,param_3,param_2);
  FUN_17cc_1362(param_1,param_4,param_1,param_2);
  FUN_17cc_1362(param_3,param_4,param_1,param_4);
  return;
}



/* 17cc:0b9e FUN_17cc_0b9e */

void __stdcall16far FUN_17cc_0b9e(undefined2 param_1,uint param_2)

{
  undefined2 unaff_DS;
  
  if (param_2 < 0xc) {
    *(uint *)0xdee = param_2;
    *(undefined2 *)0xdf0 = param_1;
    FUN_17cc_15c7(param_1,param_2);
  }
  else {
    *(undefined2 *)0xda4 = 0xfff5;
  }
  return;
}



/* 17cc:0bcb FUN_17cc_0bcb */

void __stdcall16far FUN_17cc_0bcb(uint param_1,undefined4 param_2)

{
  uint uVar1;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 local_a [8];
  
  FUN_1b5a_025d(8,local_a,unaff_SS,(int)param_2,(int)((ulong)param_2 >> 0x10));
  uVar1 = FUN_17cc_14b6();
  if (uVar1 < param_1) {
    *(undefined2 *)0xda4 = 0xfff5;
  }
  else {
    *(undefined2 *)0xdee = 0xc;
    *(uint *)0xdf0 = param_1;
    FUN_1b5a_025d(8,0xdf2,unaff_DS,local_a,unaff_SS);
    FUN_17cc_11dd(param_1,local_a,unaff_SS);
  }
  return;
}



/* 17cc:0c26 FUN_17cc_0c26 */

void __stdcall16far FUN_17cc_0c26(uint param_1)

{
  undefined2 unaff_DS;
  
  if (param_1 < 0x10) {
    *(undefined1 *)0xdcc = (undefined1)param_1;
    if (param_1 == 0) {
      *(undefined1 *)0xe07 = 0;
    }
    else {
      *(undefined1 *)0xe07 = *(undefined1 *)(param_1 + 0xe07);
    }
    FUN_17cc_1510((int)*(char *)0xe07);
  }
  return;
}



/* 17cc:0c5d FUN_17cc_0c5d */

void __stdcall16far FUN_17cc_0c5d(byte *param_1)

{
  byte *pbVar1;
  undefined2 uVar2;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 local_18 [17];
  undefined1 local_7;
  byte local_5;
  int local_4;
  
  if (*(char *)0xdda != '\0') {
    uVar2 = (undefined2)((ulong)param_1 >> 0x10);
    pbVar1 = (byte *)param_1;
    if (*param_1 < 0x11) {
      local_5 = *param_1;
    }
    else {
      local_5 = 0x10;
    }
    if (-1 < (int)(local_5 - 1)) {
      local_4 = 0;
      while( true ) {
        if (-1 < (char)pbVar1[local_4 + 1]) {
          *(byte *)(local_4 + 0xe07) = pbVar1[local_4 + 1];
        }
        if (local_4 == local_5 - 1) break;
        local_4 = local_4 + 1;
      }
    }
    if (pbVar1[1] != 0xff) {
      *(undefined1 *)0xdcc = 0;
    }
    FUN_1b5a_185c(0x11,local_18,unaff_SS,0xe06,unaff_DS);
    local_7 = 0;
    FUN_17cc_1559(local_18,unaff_SS);
  }
  return;
}



/* 17cc:0d05 FUN_17cc_0d05 */

void __stdcall16far FUN_17cc_0d05(char param_1,uint param_2)

{
  undefined2 unaff_DS;
  
  if (((*(char *)0xdda != '\0') && (param_2 <= *(byte *)0xe06 - 1)) && (-1 < param_1)) {
    *(char *)(param_2 + 0xe07) = param_1;
    if (param_2 == 0) {
      *(undefined1 *)0xdcc = 0;
    }
    FUN_17cc_1543((int)param_1,param_2);
  }
  return;
}



/* 17cc:0d49 FUN_17cc_0d49 */

void __stdcall16far FUN_17cc_0d49(undefined4 param_1)

{
  undefined2 unaff_DS;
  
  FUN_1b5a_025d(0x11,(int)param_1,(int)((ulong)param_1 >> 0x10),0xe06,unaff_DS);
  return;
}



/* 17cc:0d65 FUN_17cc_0d65 */

void __stdcall16far FUN_17cc_0d65(undefined4 param_1)

{
  undefined2 uVar1;
  undefined2 in_DX;
  
  uVar1 = FUN_17cc_14d6();
  FUN_1b5a_025d(0x11,(int)param_1,(int)((ulong)param_1 >> 0x10),uVar1,in_DX);
  return;
}



/* 17cc:0d86 FUN_17cc_0d86 */

void __stdcall16far FUN_17cc_0d86(uint param_1,uint param_2)

{
  undefined2 unaff_DS;
  
  if ((param_2 < 3) && (param_1 < 3)) {
    *(uint *)0xe1e = param_2;
    *(uint *)0xe20 = param_1;
    FUN_17cc_1207(param_1,param_2);
  }
  else {
    *(undefined2 *)0xda4 = 0xfff5;
  }
  return;
}



/* 17cc:0dca FUN_17cc_0dca */

void __stdcall16far FUN_17cc_0dca(undefined2 param_1,undefined2 param_2,uint param_3)

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
  int local_6;
  undefined2 local_4;
  
  if ((0x14 < param_3) || ((param_3 != 0 && (*(char *)(param_3 * 0xf + 0x413) == '\0')))) {
    *(undefined2 *)0xda4 = 0xfff2;
    param_3 = 0;
    param_1 = 1;
    goto LAB_17cc_0ff4;
  }
  if ((param_3 == 0) || (param_3 == *(uint *)0xe18)) goto LAB_17cc_0ff4;
  if (param_3 != *(uint *)0xcd6) {
    if (*(int *)0xcd6 != 0) {
      iVar3 = *(int *)0xcd6 * 0xf;
      _local_c = (undefined2 *)CONCAT22(unaff_DS,(undefined2 *)(iVar3 + 0x409));
      if (*(int *)(iVar3 + 0x411) != 0) {
        (*(code *)*(undefined2 *)0xc52)
                  (0x17cc,*(undefined2 *)(iVar3 + 0x411),(undefined2 *)(iVar3 + 0x409),unaff_DS);
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
    _local_c = (undefined2 *)CONCAT22(unaff_DS,(undefined2 *)(iVar3 + 0x409));
    if (*(int *)(iVar3 + 0x40d) == 0 && *(int *)(iVar3 + 0x40f) == 0) {
      puVar7 = local_10c;
      uVar6 = unaff_SS;
      FUN_1b5a_062a(iVar3 + 0x413,unaff_DS);
      FUN_1b5a_06b7(0xdc5,0x1b5a);
      FUN_1b5a_0644(8,0xcd8,unaff_DS,puVar7,uVar6);
      cVar2 = FUN_17cc_042f(0xfff3,&local_4,unaff_SS,0xcd8,unaff_DS,0xcf0,unaff_DS);
      if (cVar2 == '\0') {
        if (*(int *)0xda4 == -3) {
          *(undefined2 *)0xda4 = 0xfff8;
        }
        param_3 = 0;
        param_1 = 1;
        goto LAB_17cc_0ff4;
      }
      uVar1 = *(undefined4 *)0x566;
      *(undefined2 *)0xd48 = (int)uVar1;
      *(undefined2 *)0xd4a = (int)((ulong)uVar1 >> 0x10);
      *(undefined2 *)0x566 = 0xa5;
      *(undefined2 *)0x568 = 0x17cc;
      (*(code *)*(undefined2 *)0xc4e)(0x1b5a,local_4,&local_8);
      uVar1 = *(undefined4 *)0xd48;
      *(undefined2 *)0x566 = (int)uVar1;
      *(undefined2 *)0x568 = (int)((ulong)uVar1 >> 0x10);
      if (local_8 == 0 && local_6 == 0) {
        FUN_1b5a_16ce(0xc56,unaff_DS);
        *(undefined2 *)0xda4 = 0xfff7;
        param_3 = 0;
        param_1 = 1;
        goto LAB_17cc_0ff4;
      }
      FUN_1b5a_1738(0,0,local_4,local_8,local_6,0xc56,unaff_DS);
      FUN_1b5a_16ce(0xc56,unaff_DS);
      iVar3 = FUN_1b5a_0207();
      if (iVar3 == 0) {
        uVar4 = FUN_17cc_026a(local_8,local_6);
        if ((-1 < (int)uVar4) && (param_3 == uVar4)) {
          uVar6 = (undefined2)((ulong)_local_c >> 0x10);
          ((undefined2 *)_local_c)[4] = local_4;
          *_local_c = (int)_local_8;
          ((undefined2 *)_local_c)[1] = (int)((ulong)_local_8 >> 0x10);
          goto LAB_17cc_0fd7;
        }
      }
      *(undefined2 *)0xda4 = 0xfff3;
      (*(code *)*(undefined2 *)0xc52)(0x1b5a,local_4,&local_8);
      param_3 = 0;
      param_1 = 1;
      goto LAB_17cc_0ff4;
    }
LAB_17cc_0fd7:
    *(uint *)0xcd6 = param_3;
  }
  uVar1 = *(undefined4 *)(param_3 * 0xf + 0x40d);
  *(undefined2 *)0xdc2 = (int)uVar1;
  *(undefined2 *)0xdc4 = (int)((ulong)uVar1 >> 0x10);
LAB_17cc_0ff4:
  *(uint *)0xe18 = param_3;
  *(undefined2 *)0xe1a = param_2;
  *(undefined2 *)0xe1c = param_1;
  FUN_17cc_1612(param_1,param_2,param_3);
  return;
}



/* 17cc:1019 FUN_17cc_1019 */

void __cdecl16far FUN_17cc_1019(void)

{
  undefined2 unaff_DS;
  
  *(undefined2 *)0xda4 = 0;
  *(undefined2 *)0x564 = 0x100;
  *(undefined2 *)0xd42 = 0x1000;
  FUN_17cc_12f0();
  FUN_17cc_03b9();
  *(undefined2 *)0xc4e = 0xb9;
  *(undefined2 *)0xc50 = 0x17cc;
  *(undefined2 *)0xc52 = 0xd4;
  *(undefined2 *)0xc54 = 0x17cc;
  *(undefined1 *)0xcd8 = 0;
  *(undefined1 *)0xce2 = 0;
  *(undefined2 *)0xd44 = 6;
  *(undefined2 *)0xd46 = 10;
  *(undefined2 *)0xddc = 1;
  *(undefined2 *)0xdd6 = 1;
  *(undefined2 *)0xdd8 = 1;
  return;
}



/* 17cc:107a FUN_17cc_107a */

void __cdecl16far FUN_17cc_107a(void)

{
  return;
}



/* 17cc:107d FUN_17cc_107d */

void __cdecl16near FUN_17cc_107d(void)

{
  code *pcVar1;
  byte bVar2;
  undefined1 uVar3;
  undefined2 unaff_DS;
  
  if (*(char *)0xe2f == -1) {
    if (*(char *)0xddc == -0x5b) {
      *(undefined1 *)0xe2f = 0;
      return;
    }
    pcVar1 = (code *)swi(0x10);
    uVar3 = (*pcVar1)();
    *(undefined1 *)0xe2f = uVar3;
    bVar2 = DAT_0000_0410;
    *(byte *)0xe30 = DAT_0000_0410;
    if ((*(char *)0xe28 != '\x05') && (*(char *)0xe28 != '\a')) {
      DAT_0000_0410 = bVar2 & 0xcf | 0x20;
    }
  }
  return;
}



/* 17cc:10bc FUN_17cc_10bc */

void __cdecl16far FUN_17cc_10bc(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:10c8 FUN_17cc_10c8 */

void FUN_17cc_10c8(undefined2 param_1,undefined4 param_2)

{
  int iVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  
  *(undefined1 *)0xe2f = 0xff;
  uVar2 = (undefined2)((ulong)param_2 >> 0x10);
  iVar1 = (int)param_2;
  if (*(char *)(iVar1 + 0x16) == '\0') {
    uVar2 = (undefined2)((ulong)*(undefined4 *)0xdbe >> 0x10);
    iVar1 = (int)*(undefined4 *)0xdbe;
  }
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  *(int *)0xdc6 = iVar1;
  *(undefined2 *)0xdc8 = uVar2;
  return;
}



/* 17cc:10cd FUN_17cc_10cd */

void __stdcall16far FUN_17cc_10cd(undefined4 param_1)

{
  int iVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  
  uVar2 = (undefined2)((ulong)param_1 >> 0x10);
  iVar1 = (int)param_1;
  if (*(char *)(iVar1 + 0x16) == '\0') {
    uVar2 = (undefined2)((ulong)*(undefined4 *)0xdbe >> 0x10);
    iVar1 = (int)*(undefined4 *)0xdbe;
  }
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  *(int *)0xdc6 = iVar1;
  *(undefined2 *)0xdc8 = uVar2;
  return;
}



/* 17cc:1108 FUN_17cc_1108 */

void __stdcall16far FUN_17cc_1108(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:112b FUN_17cc_112b */

void __stdcall16far FUN_17cc_112b(byte param_1)

{
  undefined2 unaff_DS;
  
  FUN_17cc_107d();
  if (param_1 < 10) {
    *(byte *)0xe27 = param_1;
    FUN_17cc_10cd(*(undefined2 *)0xe2b,*(undefined2 *)0xe2d);
  }
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:1157 FUN_17cc_1157 */

void __cdecl16far FUN_17cc_1157(void)

{
  code *pcVar1;
  undefined2 unaff_DS;
  
  if (*(char *)0xe2f != -1) {
    (*(code *)*(undefined2 *)0xdac)(0x17cc);
    if (*(char *)0xddc != -0x5b) {
      DAT_0000_0410 = *(undefined1 *)0xe30;
      pcVar1 = (code *)swi(0x10);
      (*pcVar1)();
    }
  }
  *(undefined1 *)0xe2f = 0xff;
  return;
}



/* 17cc:118b FUN_17cc_118b */

void FUN_17cc_118b(undefined2 param_1,undefined1 param_2)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc,param_2);
  FUN_17cc_11b9();
  return;
}



/* 17cc:11a5 FUN_17cc_11a5 */

void FUN_17cc_11a5(undefined2 param_1,undefined1 param_2)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc,param_2);
  FUN_17cc_107a();
  return;
}



/* 17cc:11b9 FUN_17cc_11b9 */

void __stdcall16far FUN_17cc_11b9(void)

{
  FUN_17cc_107a();
  return;
}



/* 17cc:11c3 FUN_17cc_11c3 */

void FUN_17cc_11c3(undefined2 param_1,undefined1 param_2)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc,param_2);
  FUN_17cc_11b9();
  return;
}



/* 17cc:11dd FUN_17cc_11dd */

void __stdcall16far FUN_17cc_11dd(undefined1 param_1)

{
  undefined2 unaff_DS;
  
  *(undefined1 *)0xdcb = param_1;
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  *(undefined1 *)0xdce = 0xc;
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:1207 FUN_17cc_1207 */

void __stdcall16far FUN_17cc_1207(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:121b FUN_17cc_121b */

void __stdcall16far FUN_17cc_121b(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  FUN_17cc_107a();
  return;
}



/* 17cc:1264 FUN_17cc_1264 */

void __stdcall16far FUN_17cc_1264(undefined1 *param_1,byte *param_2,uint *param_3)

{
  byte bVar1;
  undefined2 unaff_DS;
  
  *(undefined1 *)0xe26 = 0xff;
  *(undefined1 *)0xe27 = 0;
  *(undefined1 *)0xe29 = 10;
  bVar1 = *param_2;
  *(byte *)0xe28 = bVar1;
  if (bVar1 == 0) {
    FUN_17cc_12ce();
    bVar1 = *(byte *)0xe26;
  }
  else {
    *(undefined1 *)0xe27 = *param_1;
    bVar1 = *param_2;
    if ((char)bVar1 < '\0') {
      return;
    }
    *(undefined1 *)0xe29 = *(undefined1 *)(bVar1 + 0x1741);
    bVar1 = *(byte *)(bVar1 + 0x1725);
    *(byte *)0xe26 = bVar1;
  }
  *param_3 = (uint)bVar1;
  return;
}



/* 17cc:12bc FUN_17cc_12bc */

void __stdcall16far FUN_17cc_12bc(void)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  
  uVar1 = *(undefined2 *)0xe26;
  FUN_17cc_12ce();
  *(undefined2 *)0xe26 = uVar1;
  return;
}



/* 17cc:12ce FUN_17cc_12ce */

void __cdecl16near FUN_17cc_12ce(void)

{
  uint uVar1;
  int unaff_BP;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  FUN_17cc_174f();
  uVar1 = (uint)*(byte *)0xe28;
  if (*(byte *)0xe28 == 0xff) {
    uVar1 = 0xffff;
  }
  *(uint *)*(undefined4 *)(unaff_BP + 10) = uVar1;
  *(uint *)*(undefined4 *)(unaff_BP + 6) = (uint)*(byte *)0xe27;
  return;
}



/* 17cc:12f0 FUN_17cc_12f0 */

void __cdecl16far FUN_17cc_12f0(void)

{
  undefined2 unaff_DS;
  
  *(undefined1 *)0xe26 = 0xff;
  *(undefined1 *)0xe27 = 0;
  *(undefined1 *)0xe28 = 0;
  *(undefined1 *)0xe29 = 0;
  *(undefined1 *)0xe2a = 0;
  *(undefined2 *)0xe2b = 0;
  *(undefined2 *)0xe2d = 0;
  *(undefined1 *)0xe2f = 0xff;
  *(undefined1 *)0xe30 = 0;
  return;
}



/* 17cc:1312 FUN_17cc_1312 */

void __stdcall16far FUN_17cc_1312(undefined4 param_1)

{
  undefined2 unaff_DS;
  
  FUN_17cc_107d();
  *(undefined2 *)0xe2b = (int)param_1;
  *(undefined2 *)0xe2d = (int)((ulong)param_1 >> 0x10);
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:132e FUN_17cc_132e */

void __cdecl16far FUN_17cc_132e(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:133a FUN_17cc_133a */

void __stdcall16far FUN_17cc_133a(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:134e FUN_17cc_134e */

void __stdcall16far FUN_17cc_134e(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:1362 FUN_17cc_1362 */

void __stdcall16far FUN_17cc_1362(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:137c FUN_17cc_137c */

void __stdcall16far FUN_17cc_137c(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:1393 FUN_17cc_1393 */

void __stdcall16far FUN_17cc_1393(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:13aa FUN_17cc_13aa */

void __stdcall16far FUN_17cc_13aa(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:13c4 FUN_17cc_13c4 */

void __stdcall16far
FUN_17cc_13c4(undefined2 param_1,undefined2 param_2,uint param_3,uint param_4,uint param_5,
             uint param_6)

{
  undefined2 unaff_DS;
  
  if (param_4 <= param_6) {
    param_4 = param_6;
  }
  if (param_5 < param_3) {
    param_3 = param_5;
  }
  (*(code *)*(undefined2 *)0xdac)(0x17cc,param_3,param_4);
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:13fc FUN_17cc_13fc */

void __stdcall16far FUN_17cc_13fc(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:1423 FUN_17cc_1423 */

void __stdcall16far FUN_17cc_1423(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:1457 FUN_17cc_1457 */

void __stdcall16far FUN_17cc_1457(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:147e FUN_17cc_147e */

void __stdcall16far FUN_17cc_147e(undefined2 *param_1)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  int iVar3;
  undefined2 *in_BX;
  undefined2 *puVar4;
  undefined2 unaff_ES;
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
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



/* 17cc:149e FUN_17cc_149e */

void __stdcall16far FUN_17cc_149e(undefined1 param_1)

{
  undefined2 unaff_DS;
  
  *(undefined1 *)0xdca = param_1;
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:14b6 FUN_17cc_14b6 */

undefined2 __cdecl16far FUN_17cc_14b6(void)

{
  undefined2 in_CX;
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return in_CX;
}



/* 17cc:14c6 FUN_17cc_14c6 */

undefined2 __cdecl16far FUN_17cc_14c6(void)

{
  undefined2 in_BX;
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return in_BX;
}



/* 17cc:14d6 FUN_17cc_14d6 */

undefined2 __cdecl16far FUN_17cc_14d6(void)

{
  undefined2 in_BX;
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return in_BX;
}



/* 17cc:14e8 FUN_17cc_14e8 */

undefined2 __stdcall16far FUN_17cc_14e8(void)

{
  undefined2 in_BX;
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return in_BX;
}



/* 17cc:14ff FUN_17cc_14ff */

int __cdecl16far FUN_17cc_14ff(void)

{
  int in_CX;
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return in_CX + -1;
}



/* 17cc:1510 FUN_17cc_1510 */

void __stdcall16far FUN_17cc_1510(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:1526 FUN_17cc_1526 */

void __stdcall16far FUN_17cc_1526(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:1543 FUN_17cc_1543 */

void __stdcall16far FUN_17cc_1543(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:1559 FUN_17cc_1559 */

void __stdcall16far FUN_17cc_1559(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:156b FUN_17cc_156b */

void __stdcall16far FUN_17cc_156b(undefined1 param_1,undefined2 param_2,undefined1 param_3)

{
  undefined2 unaff_DS;
  
  *(undefined1 *)0xdcd = param_3;
  *(undefined1 *)0xe2a = param_1;
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:158b FUN_17cc_158b */

/* WARNING: Unable to track spacebase fully for stack */

void __stdcall16far FUN_17cc_158b(void)

{
  undefined2 uVar1;
  code *pcVar2;
  int iVar3;
  undefined2 uVar4;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  uVar4 = (undefined2)((ulong)*(undefined4 *)0xe2b >> 0x10);
  iVar3 = (int)*(undefined4 *)0xe2b;
  uVar1 = *(undefined2 *)(iVar3 + 0xe);
  iVar3 = *(int *)(iVar3 + 0xc) + *(int *)(iVar3 + 0x10);
  *(undefined1 **)(iVar3 + -4) = &stack0xfffe;
  *(undefined2 *)(iVar3 + -6) = unaff_SS;
  uVar4 = ((undefined2 *)0xdac)[1];
  pcVar2 = (code *)*(undefined2 *)0xdac;
  *(undefined2 *)(iVar3 + -8) = 0x17cc;
  *(undefined2 *)(iVar3 + -10) = 0x927b;
  (*pcVar2)();
  return;
}



/* 17cc:15c7 FUN_17cc_15c7 */

void __stdcall16far FUN_17cc_15c7(undefined1 param_1,undefined1 param_2)

{
  undefined2 unaff_DS;
  
  *(undefined1 *)0xdcb = param_1;
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  *(undefined1 *)0xdce = param_2;
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:15ee FUN_17cc_15ee */

void __stdcall16far FUN_17cc_15ee(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:1612 FUN_17cc_1612 */

void __stdcall16far FUN_17cc_1612(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:165a FUN_17cc_165a */

void __stdcall16far FUN_17cc_165a(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:1677 FUN_17cc_1677 */

int __stdcall16far FUN_17cc_1677(int param_1)

{
  undefined2 unaff_DS;
  
  param_1 = param_1 + 1;
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return param_1;
}



/* 17cc:16a8 FUN_17cc_16a8 */

undefined1 __stdcall16far FUN_17cc_16a8(void)

{
  undefined1 extraout_DL;
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return extraout_DL;
}



/* 17cc:16c0 FUN_17cc_16c0 */

void __stdcall16far FUN_17cc_16c0(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:16d7 FUN_17cc_16d7 */

void __stdcall16far FUN_17cc_16d7(int *param_1,uint param_2,uint param_3,uint param_4,uint param_5)

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
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:170b FUN_17cc_170b */

void __stdcall16far FUN_17cc_170b(void)

{
  undefined2 unaff_DS;
  
  (*(code *)*(undefined2 *)0xdac)(0x17cc);
  return;
}



/* 17cc:174f FUN_17cc_174f */

void __cdecl16near FUN_17cc_174f(void)

{
  uint uVar1;
  undefined2 unaff_DS;
  
  *(undefined1 *)0xe26 = 0xff;
  *(undefined1 *)0xe28 = 0xff;
  *(undefined1 *)0xe27 = 0;
  FUN_17cc_1785();
  if (*(byte *)0xe28 != 0xff) {
    uVar1 = (uint)*(byte *)0xe28;
    *(undefined1 *)0xe26 = *(undefined1 *)(uVar1 + 0x1725);
    *(undefined1 *)0xe27 = *(undefined1 *)(uVar1 + 0x1733);
    *(undefined1 *)0xe29 = *(undefined1 *)(uVar1 + 0x1741);
  }
  return;
}



/* 17cc:1785 FUN_17cc_1785 */

void __cdecl16near FUN_17cc_1785(void)

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
    FUN_17cc_17ec();
    if (!bVar5) {
      cVar3 = FUN_17cc_187d();
      if (cVar3 == '\0') {
        uRam000b8000 = ~uRam000b8000;
        *(undefined1 *)0xe28 = 1;
        return;
      }
      *(undefined1 *)0xe28 = 7;
      return;
    }
  }
  else {
    FUN_17cc_187a();
    if (bVar5) {
      *(undefined1 *)0xe28 = 6;
      return;
    }
    FUN_17cc_17ec();
    if (!bVar5) {
      iVar4 = FUN_17cc_18af();
      bVar5 = false;
      if (iVar4 == 0) {
        *(undefined1 *)0xe28 = 1;
        FUN_17cc_1859();
        if (bVar5) {
          *(undefined1 *)0xe28 = 2;
        }
        return;
      }
      *(undefined1 *)0xe28 = 10;
      return;
    }
  }
  FUN_17cc_180a();
  return;
}



/* 17cc:17ec FUN_17cc_17ec */

void __cdecl16near FUN_17cc_17ec(void)

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



/* 17cc:180a FUN_17cc_180a */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl16near FUN_17cc_180a(void)

{
  undefined2 in_BX;
  char cVar1;
  undefined2 unaff_DS;
  bool bVar2;
  
  *(undefined1 *)0xe28 = 4;
  cVar1 = (char)((uint)in_BX >> 8);
  bVar2 = cVar1 == '\0';
  if (cVar1 != '\x01') {
    FUN_17cc_184a();
    if ((!bVar2) && (bVar2 = false, (char)in_BX != '\0')) {
      *(undefined1 *)0xe28 = 3;
      FUN_17cc_1859();
      if ((bVar2) || ((_DAT_c000_0039 == 0x345a && (_DAT_c000_003b == 0x3934)))) {
        *(undefined1 *)0xe28 = 9;
      }
    }
    return;
  }
  *(undefined1 *)0xe28 = 5;
  return;
}



/* 17cc:184a FUN_17cc_184a */

void __cdecl16near FUN_17cc_184a(void)

{
  return;
}



/* 17cc:1859 FUN_17cc_1859 */

void __cdecl16near FUN_17cc_1859(void)

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



/* 17cc:187a FUN_17cc_187a */

undefined1 __cdecl16near FUN_17cc_187a(void)

{
  return 0;
}



/* 17cc:187d FUN_17cc_187d */

undefined1 __cdecl16near FUN_17cc_187d(void)

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



/* 17cc:18af FUN_17cc_18af */

undefined2 __cdecl16near FUN_17cc_18af(void)

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



/* 1af1:000b FUN_1af1_000b */

undefined2 __cdecl16far FUN_1af1_000b(undefined2 *param_1)

{
  return *param_1;
}



/* 1af8:0000 FUN_1af8_0000 */

void __cdecl16far FUN_1af8_0000(void)

{
  undefined2 unaff_DS;
  
  FUN_1af8_0030();
  FUN_1af8_032e(0xe46,unaff_DS);
  FUN_1b5a_1288(0x1af8,0xe46);
  FUN_1af8_032e(0xf46,unaff_DS);
  FUN_1b5a_128d(0x1b5a,0xf46);
  return;
}



/* 1af8:0030 FUN_1af8_0030 */

/* WARNING: Removing unreachable block (ram,0x0001aff6) */

void __cdecl16near FUN_1af8_0030(void)

{
  byte bVar1;
  byte extraout_AH;
  undefined2 unaff_DS;
  
  bVar1 = FUN_1af8_0608();
  if ((bVar1 != 7) && (3 < bVar1)) {
    FUN_1af8_0099();
  }
  FUN_1af8_00e7();
  FUN_1af8_0608();
  *(byte *)0xe42 = extraout_AH & 0x7f;
  *(byte *)0xe38 = extraout_AH & 0x7f;
  *(undefined1 *)0xe33 = 0;
  *(undefined1 *)0xe43 = 0;
  *(undefined1 *)0xe44 = 0;
  *(undefined1 *)0xe32 = 1;
  do {
  } while( true );
}



/* 1af8:0099 FUN_1af8_0099 */

void __cdecl16near FUN_1af8_0099(void)

{
  undefined2 in_AX;
  char extraout_DL;
  
  DAT_0000_0487 = DAT_0000_0487 & 0xfe;
  if (((byte)in_AX != 7) && (3 < (byte)in_AX)) {
    in_AX = CONCAT11((char)((uint)in_AX >> 8),3);
  }
  FUN_1af8_0608();
  if ((char)((uint)in_AX >> 8) != '\0') {
    FUN_1af8_0608();
    FUN_1af8_0608();
    if (extraout_DL == '*') {
      DAT_0000_0487 = DAT_0000_0487 | 1;
      FUN_1af8_0608();
      FUN_1af8_0608();
    }
  }
  return;
}



/* 1af8:00e7 FUN_1af8_00e7 */

void __cdecl16near FUN_1af8_00e7(void)

{
  uint uVar1;
  uint uVar2;
  undefined1 uVar3;
  byte extraout_DL;
  byte bVar4;
  undefined2 uVar5;
  undefined2 unaff_DS;
  
  uVar1 = FUN_1af8_0608();
  FUN_1af8_0608();
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
  *(uint *)0xe36 = uVar2;
  *(undefined2 *)0xe40 = uVar5;
  *(undefined1 *)0xe35 = uVar3;
  *(undefined1 *)0xe34 = 1;
  *(undefined2 *)0xe3a = 0;
  *(undefined2 *)0xe3c = uVar5;
  return;
}



/* 1af8:0145 FUN_1af8_0145 */

void __cdecl16near FUN_1af8_0145(void)

{
  code *pcVar1;
  undefined2 unaff_DS;
  undefined1 uVar2;
  
  uVar2 = *(char *)0xe44 == '\0';
  if ((bool)uVar2) {
    return;
  }
  *(undefined1 *)0xe44 = 0;
  while( true ) {
    pcVar1 = (code *)swi(0x16);
    (*pcVar1)();
    if ((bool)uVar2) break;
    pcVar1 = (code *)swi(0x16);
    (*pcVar1)();
  }
  FUN_1af8_047b();
  FUN_1af8_047b();
  FUN_1af8_0474();
  pcVar1 = (code *)swi(0x23);
  (*pcVar1)();
  FUN_1af8_0099();
  FUN_1af8_00e7();
  *(undefined1 *)0xe38 = *(undefined1 *)0xe42;
  return;
}



/* 1af8:029e FUN_1af8_029e */

void __stdcall16far FUN_1af8_029e(int param_1)

{
  int extraout_DX;
  
  if (param_1 != 0) {
    do {
      FUN_1af8_02be();
    } while (extraout_DX != 1);
  }
  return;
}



/* 1af8:02be FUN_1af8_02be */

void __cdecl16near FUN_1af8_02be(void)

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



/* 1af8:02c6 FUN_1af8_02c6 */

undefined2 __stdcall16far FUN_1af8_02c6(uint param_1)

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



/* 1af8:02f3 FUN_1af8_02f3 */

byte __cdecl16far FUN_1af8_02f3(void)

{
  byte bVar1;
  
  bVar1 = in(0x61);
  out(0x61,bVar1 & 0xfc);
  return bVar1 & 0xfc;
}



/* 1af8:02fa FUN_1af8_02fa */

undefined1 __cdecl16far FUN_1af8_02fa(void)

{
  code *pcVar1;
  undefined2 unaff_DS;
  bool bVar2;
  
  bVar2 = *(char *)0xe43 == '\0';
  if (bVar2) {
    pcVar1 = (code *)swi(0x16);
    (*pcVar1)();
    if (bVar2) {
      return 0;
    }
  }
  return 1;
}



/* 1af8:030c FUN_1af8_030c */

void __cdecl16far FUN_1af8_030c(void)

{
  code *pcVar1;
  char cVar2;
  undefined1 extraout_AH;
  undefined2 unaff_DS;
  
  cVar2 = *(char *)0xe43;
  *(undefined1 *)0xe43 = 0;
  if (cVar2 == '\0') {
    pcVar1 = (code *)swi(0x16);
    cVar2 = (*pcVar1)();
    if (cVar2 == '\0') {
      *(undefined1 *)0xe43 = extraout_AH;
    }
  }
  FUN_1af8_0145();
  return;
}



/* 1af8:032e FUN_1af8_032e */

void __stdcall16far FUN_1af8_032e(undefined4 param_1)

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
  *(undefined2 *)(iVar1 + 0x12) = 0x1af8;
  *(undefined1 *)(iVar1 + 0x30) = 0;
  return;
}



/* 1af8:0391 FUN_1af8_0391 */

void __stdcall16far FUN_1af8_0391(undefined4 param_1)

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
LAB_1af8_03a7:
  do {
    *(undefined1 *)0xe43 = 0;
    bVar1 = FUN_1af8_030c();
    iVar2 = 1;
    if ((bVar1 == 8) || (bVar1 == 0x13)) {
LAB_1af8_03eb:
      do {
        if (uVar4 == 0) break;
        FUN_1af8_047b();
        FUN_1af8_047b();
        FUN_1af8_047b();
        uVar4 = uVar4 - 1;
        iVar2 = iVar2 + -1;
        uVar3 = extraout_DX_00;
      } while (iVar2 != 0);
      goto LAB_1af8_03a7;
    }
    if (bVar1 == 4) {
LAB_1af8_0403:
      do {
        if ((uVar4 == uVar5) || (*(byte *)(uVar4 + iVar7) < 0x20)) break;
        FUN_1af8_047b();
        uVar4 = uVar4 + 1;
        iVar2 = iVar2 + -1;
        uVar3 = extraout_DX_01;
      } while (iVar2 != 0);
    }
    else {
      iVar2 = 0;
      if ((bVar1 == 0x1b) || (bVar1 == 1)) goto LAB_1af8_03eb;
      if (bVar1 == 6) goto LAB_1af8_0403;
      if (bVar1 == 0x1a) {
        if (*(char *)0xe33 != '\0') {
          *(undefined1 *)(uVar4 + iVar7) = 0x1a;
          iVar7 = uVar4 + 1;
LAB_1af8_042d:
          *(undefined2 *)(iVar6 + 8) = 0;
          *(int *)(iVar6 + 10) = iVar7;
          return;
        }
      }
      else {
        if (bVar1 == 0xd) {
          FUN_1af8_0474();
          *(undefined2 *)(uVar4 + iVar7) = 0xa0d;
          iVar7 = uVar4 + 2;
          goto LAB_1af8_042d;
        }
        if ((0x1f < bVar1) && (uVar4 != uVar3)) {
          *(byte *)(uVar4 + iVar7) = bVar1;
          uVar4 = uVar4 + 1;
          FUN_1af8_047b();
          uVar3 = extraout_DX;
          if (uVar5 < uVar4) {
            uVar5 = uVar4;
          }
        }
      }
    }
  } while( true );
}



/* 1af8:0474 FUN_1af8_0474 */

/* WARNING: Removing unreachable block (ram,0x0001b443) */
/* WARNING: Removing unreachable block (ram,0x0001b439) */
/* WARNING: Removing unreachable block (ram,0x0001b43f) */
/* WARNING: Removing unreachable block (ram,0x0001b414) */
/* WARNING: Removing unreachable block (ram,0x0001b42c) */
/* WARNING: Removing unreachable block (ram,0x0001b432) */

void FUN_1af8_0474(void)

{
  FUN_1af8_047b();
  thunk_FUN_1af8_0608();
  FUN_1af8_04d4();
  thunk_FUN_1af8_0608();
  return;
}



/* 1af8:047b FUN_1af8_047b */

void __cdecl16near FUN_1af8_047b(void)

{
  char in_AL;
  char extraout_DL;
  undefined2 unaff_DS;
  
  thunk_FUN_1af8_0608();
  if (in_AL == '\a') {
    FUN_1af8_0608();
  }
  else if (((in_AL != '\b') && (in_AL != '\r')) &&
          ((in_AL == '\n' || (FUN_1af8_0608(), *(byte *)0xe3c < (byte)(extraout_DL + 1U))))) {
    FUN_1af8_04d4();
  }
  thunk_FUN_1af8_0608();
  return;
}



/* 1af8:04d4 FUN_1af8_04d4 */

void __cdecl16near FUN_1af8_04d4(void)

{
  undefined2 in_DX;
  undefined2 unaff_DS;
  
  if (*(byte *)0xe3d < (byte)((char)((uint)in_DX >> 8) + 1U)) {
    FUN_1af8_0608();
  }
  return;
}



/* 1af8:04f5 thunk_FUN_1af8_0608 */

void __cdecl16near thunk_FUN_1af8_0608(void)

{
  FUN_1af8_0608();
  return;
}



/* 1af8:04fc thunk_FUN_1af8_0608 */

void __cdecl16near thunk_FUN_1af8_0608(void)

{
  FUN_1af8_0608();
  return;
}



/* 1af8:0608 FUN_1af8_0608 */

void __cdecl16near FUN_1af8_0608(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x10);
  (*pcVar1)();
  return;
}



/* 1b5a:0000 FUN_1b5a_0000 */

void __cdecl16far FUN_1b5a_0000(void)

{
  code *pcVar1;
  int iVar2;
  undefined2 in_BX;
  undefined2 *puVar3;
  undefined2 unaff_ES;
  int unaff_SS;
  
  DAT_1ce5_054c = ((uint)&stack0x0013 >> 4) + unaff_SS;
  DAT_1ce5_0550 = DAT_1ce5_054c + DAT_1ce5_0546;
  DAT_1ce5_0562 = *(int *)0x2 + -0x1000;
  puVar3 = (undefined2 *)0x1046;
  iVar2 = 0x12;
  DAT_1ce5_054e = DAT_1ce5_054c;
  DAT_1ce5_055a = DAT_1ce5_0550;
  DAT_1ce5_055e = DAT_1ce5_0550;
  DAT_1ce5_0574 = unaff_ES;
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
  FUN_1b5a_1218();
  FUN_1b5a_1288();
  FUN_1b5a_1218();
  FUN_1b5a_128d();
  return;
}



/* 1b5a:00d1 FUN_1b5a_00d1 */

/* WARNING: Restarted to delay deadcode elimination for space: ram */

void __cdecl16far FUN_1b5a_00d1(void)

{
  code *pcVar1;
  undefined2 in_AX;
  int iVar2;
  int iVar3;
  char *pcVar4;
  int in_stack_00000000;
  int in_stack_00000002;
  
  DAT_1ce5_056e = in_AX;
  iVar2 = DAT_1ce5_0552;
  if (in_stack_00000000 != 0 || in_stack_00000002 != 0) {
    for (; (iVar3 = in_stack_00000002, iVar2 != 0 &&
           (iVar3 = iVar2, in_stack_00000002 != *(int *)0x10)); iVar2 = *(int *)0x14) {
    }
    in_stack_00000002 = (iVar3 - DAT_1ce5_0574) + -0x10;
  }
  DAT_1ce5_0570 = in_stack_00000000;
  DAT_1ce5_0572 = in_stack_00000002;
  pcVar4 = (char *)DAT_1ce5_056a;
  if (DAT_1ce5_056a == (char *)0x0) {
    FUN_1b5a_12e1();
    FUN_1b5a_12e1();
    iVar2 = 0x12;
    do {
      pcVar1 = (code *)swi(0x21);
      (*pcVar1)();
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    if (DAT_1ce5_0570 != 0 || DAT_1ce5_0572 != 0) {
      FUN_1b5a_0194();
      FUN_1b5a_01a2();
      FUN_1b5a_0194();
      FUN_1b5a_01bc();
      FUN_1b5a_01d6();
      FUN_1b5a_01bc();
      pcVar4 = (char *)0x203;
      FUN_1b5a_0194();
    }
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
    for (; *pcVar4 != '\0'; pcVar4 = pcVar4 + 1) {
      FUN_1b5a_01d6();
    }
    return;
  }
  DAT_1ce5_056a = (char *)0x0;
  DAT_1ce5_0578 = 0;
  return;
}



/* 1b5a:00d8 FUN_1b5a_00d8 */

/* WARNING: Removing unreachable block (ram,0x0001b68b) */
/* WARNING: Removing unreachable block (ram,0x0001b68e) */
/* WARNING: Removing unreachable block (ram,0x0001b692) */
/* WARNING: Removing unreachable block (ram,0x0001b6a1) */
/* WARNING: Removing unreachable block (ram,0x0001b69b) */
/* WARNING: Removing unreachable block (ram,0x0001b6a3) */

void __cdecl16far FUN_1b5a_00d8(void)

{
  code *pcVar1;
  undefined2 in_AX;
  int iVar2;
  char *pcVar3;
  undefined2 uVar4;
  
  uVar4 = 0x1ce5;
  DAT_1ce5_056e = in_AX;
  DAT_1ce5_0570 = 0;
  DAT_1ce5_0572 = 0;
  pcVar3 = (char *)DAT_1ce5_056a;
  if ((int)((ulong)DAT_1ce5_056a >> 0x10) == 0 && pcVar3 == (char *)0x0) {
    FUN_1b5a_12e1(0xe46,0x1ce5);
    FUN_1b5a_12e1(0xf46,0x1ce5);
    iVar2 = 0x12;
    do {
      pcVar1 = (code *)swi(0x21);
      (*pcVar1)();
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    if (*(int *)0x570 != 0 || *(int *)0x572 != 0) {
      FUN_1b5a_0194();
      FUN_1b5a_01a2();
      FUN_1b5a_0194();
      FUN_1b5a_01bc();
      FUN_1b5a_01d6();
      FUN_1b5a_01bc();
      pcVar3 = (char *)0x203;
      FUN_1b5a_0194();
    }
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
    for (; *pcVar3 != '\0'; pcVar3 = pcVar3 + 1) {
      FUN_1b5a_01d6();
    }
    return;
  }
  DAT_1ce5_056a = (char *)0x0;
  DAT_1ce5_0578 = 0;
  return;
}



/* 1b5a:0194 FUN_1b5a_0194 */

void __cdecl16near FUN_1b5a_0194(void)

{
  char *in_BX;
  
  for (; *in_BX != '\0'; in_BX = in_BX + 1) {
    FUN_1b5a_01d6();
  }
  return;
}



/* 1b5a:01a2 FUN_1b5a_01a2 */

undefined2 __cdecl16near FUN_1b5a_01a2(void)

{
  undefined2 uVar1;
  undefined1 uVar2;
  
  FUN_1b5a_01ae();
  uVar1 = FUN_1b5a_01ae();
  uVar1 = CONCAT11((char)((uint)uVar1 >> 8),(char)uVar1 + '0');
  FUN_1b5a_01d6(uVar1);
  uVar2 = (undefined1)((uint)uVar1 >> 8);
  return CONCAT11(uVar2,uVar2);
}



/* 1b5a:01ae FUN_1b5a_01ae */

undefined2 __cdecl16near FUN_1b5a_01ae(void)

{
  uint in_AX;
  undefined2 uVar1;
  undefined1 uVar2;
  byte in_CL;
  
  uVar1 = CONCAT11((char)((in_AX & 0xff) % (uint)in_CL),(char)((in_AX & 0xff) / (uint)in_CL) + '0');
  FUN_1b5a_01d6(uVar1);
  uVar2 = (undefined1)((uint)uVar1 >> 8);
  return CONCAT11(uVar2,uVar2);
}



/* 1b5a:01bc FUN_1b5a_01bc */

void FUN_1b5a_01bc(void)

{
  code *pcVar1;
  
  FUN_1b5a_01c3();
  FUN_1b5a_01ce();
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  return;
}



/* 1b5a:01c3 FUN_1b5a_01c3 */

void FUN_1b5a_01c3(void)

{
  code *pcVar1;
  
  FUN_1b5a_01ce();
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  return;
}



/* 1b5a:01ce FUN_1b5a_01ce */

void FUN_1b5a_01ce(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  return;
}



/* 1b5a:01d6 FUN_1b5a_01d6 */

void __cdecl16near FUN_1b5a_01d6(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  return;
}



/* 1b5a:0207 FUN_1b5a_0207 */

undefined2 __cdecl16far FUN_1b5a_0207(void)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  
  LOCK();
  uVar1 = *(undefined2 *)0x578;
  *(undefined2 *)0x578 = 0;
  UNLOCK();
  return uVar1;
}



/* 1b5a:020e FUN_1b5a_020e */

void __cdecl16far FUN_1b5a_020e(void)

{
  undefined2 unaff_DS;
  
  if (*(int *)0x578 == 0) {
    return;
  }
  FUN_1b5a_00d1();
  return;
}



/* 1b5a:025d FUN_1b5a_025d */

void __stdcall16far FUN_1b5a_025d(int param_1,undefined1 *param_2,undefined1 *param_3)

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



/* 1b5a:0279 FUN_1b5a_0279 */

int __cdecl16far FUN_1b5a_0279(void)

{
  int in_AX;
  int in_CX;
  
  return in_AX * in_CX;
}



/* 1b5a:0294 FUN_1b5a_0294 */

uint __cdecl16far FUN_1b5a_0294(void)

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
    uVar2 = FUN_1b5a_00d1();
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



/* 1b5a:0329 FUN_1b5a_0329 */

undefined4 __stdcall16far FUN_1b5a_0329(void)

{
  undefined2 uVar1;
  undefined2 in_CX;
  undefined2 extraout_DX;
  undefined2 uVar2;
  undefined1 in_CF;
  
  FUN_1b5a_041d();
  if (!(bool)in_CF) {
    return CONCAT22(register0x00000010,in_CX);
  }
  uVar2 = extraout_DX;
  uVar1 = FUN_1b5a_00d1();
  return CONCAT22(uVar2,uVar1);
}



/* 1b5a:0341 FUN_1b5a_0341 */

void __stdcall16far FUN_1b5a_0341(void)

{
  undefined1 in_CF;
  
  FUN_1b5a_04d8();
  if (!(bool)in_CF) {
    return;
  }
  FUN_1b5a_00d1();
  return;
}



/* 1b5a:041d FUN_1b5a_041d */

/* WARNING: Removing unreachable block (ram,0x0001ba45) */
/* WARNING: Removing unreachable block (ram,0x0001b9f5) */

undefined2 __cdecl16near FUN_1b5a_041d(void)

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
    uVar7 = FUN_1b5a_060d();
    uVar1 = (uint)(uVar7 >> 0x10);
    uVar6 = (undefined2)((ulong)*(undefined4 *)0x560 >> 0x10);
    for (puVar5 = (uint *)(uint *)*(undefined4 *)0x560; puVar5 != (uint *)0x0; puVar5 = puVar5 + 4)
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
          FUN_1b5a_05af();
          return in_AX;
        }
      }
    }
    uVar7 = FUN_1b5a_05c4();
    iVar4 = -*(int *)0x55e;
    iVar2 = unaff_SI - *(uint *)0x55c;
    if (unaff_SI < *(uint *)0x55c) {
      iVar2 = iVar2 + 0x10;
      iVar4 = iVar4 + -1;
    }
    if (uVar7 <= CONCAT22(iVar4,iVar2)) break;
    if (*(int *)0x566 == 0 && *(int *)0x568 == 0) {
      return in_AX;
    }
    iVar4 = (*(code *)*(undefined2 *)0x566)(0x1b5a,in_AX);
    if (iVar4 == 0) {
      return in_AX;
    }
    if (iVar4 == 1) {
      return in_AX;
    }
  }
  iVar4 = (int)(uVar7 >> 0x10) + *(int *)0x55e;
  uVar1 = (int)uVar7 + *(int *)0x55c;
  if (0xf < uVar1) {
    uVar1 = uVar1 - 0x10;
    iVar4 = iVar4 + 1;
  }
  *(uint *)0x55c = uVar1;
  *(int *)0x55e = iVar4;
  return in_AX;
}



/* 1b5a:04d8 FUN_1b5a_04d8 */

void __cdecl16near FUN_1b5a_04d8(void)

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
    uVar6 = FUN_1b5a_060d();
    uVar2 = (int)((ulong)uVar6 >> 0x10) + in_BX;
    uVar1 = (int)uVar6 + in_CX;
    if (0xf < uVar1) {
      uVar1 = uVar1 - 0x10;
      uVar2 = uVar2 + 1;
    }
    uVar6 = CONCAT22(uVar2,uVar1);
    if ((*(uint *)0x55a <= in_BX) &&
       ((((*(uint *)0x55a < in_BX || (*(uint *)0x558 <= in_CX)) && (uVar2 <= *(uint *)0x55e)) &&
        ((uVar2 < *(uint *)0x55e || (uVar1 <= *(uint *)0x55c)))))) {
      uVar4 = (undefined2)((ulong)*(undefined4 *)0x560 >> 0x10);
      puVar3 = (uint *)(uint *)*(undefined4 *)0x560;
      do {
        uVar2 = (uint)((ulong)uVar6 >> 0x10);
        uVar1 = (uint)uVar6;
        if (puVar3 == (uint *)0x0) {
          bVar5 = uVar2 < *(uint *)0x55e;
          if ((uVar2 == *(uint *)0x55e) && (bVar5 = uVar1 < *(uint *)0x55c, uVar1 == *(uint *)0x55c)
             ) {
            *(uint *)0x55c = in_CX;
            *(uint *)0x55e = in_BX;
            return;
          }
          uVar6 = FUN_1b5a_058b();
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
          goto LAB_1b5a_0541;
        }
        else if ((in_BX <= puVar3[3]) && ((in_BX < puVar3[3] || (in_CX <= puVar3[2])))) {
          in_CX = *puVar3;
          in_BX = puVar3[1];
LAB_1b5a_0541:
          uVar6 = FUN_1b5a_05af();
        }
        puVar3 = puVar3 + 4;
      } while( true );
    }
  }
  return;
}



/* 1b5a:058b FUN_1b5a_058b */

void __cdecl16near FUN_1b5a_058b(void)

{
  uint uVar1;
  undefined2 unaff_DS;
  
  uVar1 = *(int *)0x560 - 8;
  if ((uVar1 != 0) && (*(uint *)0x55e < (uVar1 >> 4) + *(int *)0x562)) {
    *(uint *)0x560 = uVar1;
    return;
  }
  return;
}



/* 1b5a:05af FUN_1b5a_05af */

void __cdecl16near FUN_1b5a_05af(void)

{
  undefined2 *puVar1;
  undefined2 *unaff_DI;
  undefined2 unaff_ES;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)*(undefined2 *)0x560;
  *unaff_DI = *puVar1;
  unaff_DI[1] = puVar1[1];
  unaff_DI[2] = puVar1[2];
  unaff_DI[3] = puVar1[3];
  *(int *)0x560 = (int)(puVar1 + 4);
  return;
}



/* 1b5a:05c4 FUN_1b5a_05c4 */

void __cdecl16near FUN_1b5a_05c4(void)

{
  undefined2 unaff_DS;
  
  if ((*(int *)0x560 == 0) && (*(int *)0x564 == 0)) {
    return;
  }
  return;
}



/* 1b5a:060d FUN_1b5a_060d */

ulong __cdecl16near FUN_1b5a_060d(void)

{
  uint in_AX;
  
  return CONCAT22(in_AX >> 4,in_AX) & 0xffff000f;
}



/* 1b5a:062a FUN_1b5a_062a */

void __stdcall16far FUN_1b5a_062a(byte *param_1,byte *param_2)

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



/* 1b5a:0644 FUN_1b5a_0644 */

void __stdcall16far FUN_1b5a_0644(byte param_1,byte *param_2,byte *param_3)

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



/* 1b5a:0676 FUN_1b5a_0676 */

void __stdcall16far FUN_1b5a_0676(uint param_1,uint param_2,byte *param_3,byte *param_4)

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



/* 1b5a:06b7 FUN_1b5a_06b7 */

void __stdcall16far FUN_1b5a_06b7(byte *param_1,byte *param_2)

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



/* 1b5a:072f FUN_1b5a_072f */

void __stdcall16far FUN_1b5a_072f(byte *param_1,byte *param_2)

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



/* 1b5a:075a FUN_1b5a_075a */

void __stdcall16far FUN_1b5a_075a(undefined1 param_1,undefined1 *param_2)

{
  *param_2 = 1;
  ((undefined1 *)param_2)[1] = param_1;
  return;
}



/* 1b5a:076c FUN_1b5a_076c */

void __stdcall16far FUN_1b5a_076c(int param_1,undefined1 *param_2,undefined1 *param_3)

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



/* 1b5a:0787 FUN_1b5a_0787 */

void __stdcall16far
FUN_1b5a_0787(int param_1,undefined2 param_2,undefined4 param_3,undefined4 param_4)

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
  FUN_1b5a_0676(param_1 + -1,1,uVar1,uVar2);
  FUN_1b5a_06b7((int)param_4,(int)((ulong)param_4 >> 0x10));
  puVar3 = local_202;
  FUN_1b5a_0676(0xff,param_1,uVar1,uVar2);
  FUN_1b5a_06b7(puVar3,unaff_SS);
  FUN_1b5a_0644(param_2,uVar1,uVar2,puVar4,uVar5);
  return;
}



/* 1b5a:07db FUN_1b5a_07db */

void __stdcall16far FUN_1b5a_07db(int param_1,int param_2,undefined4 param_3)

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
    FUN_1b5a_0676(param_2 + -1,1,uVar1,uVar2);
    puVar3 = local_202;
    FUN_1b5a_0676(0xff,param_2 + param_1,uVar1,uVar2);
    FUN_1b5a_06b7(puVar3,unaff_SS);
    FUN_1b5a_0644(0xff,uVar1,uVar2,puVar4,uVar5);
  }
  return;
}



/* 1b5a:0831 FUN_1b5a_0831 */

undefined4 FUN_1b5a_0831(void)

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
LAB_1b5a_08b5:
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
    if (0x27 < bVar2) goto LAB_1b5a_08b5;
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
      if ((in_DX == 0 && uVar9 == 0) && in_AX == 0) goto LAB_1b5a_08b4;
      while (-1 < (int)in_DX) {
        bVar12 = (int)in_AX < 0;
        in_AX = in_AX << 1;
        bVar13 = (int)uVar9 < 0;
        uVar9 = uVar9 << 1 | (uint)bVar12;
        in_DX = in_DX << 1 | (uint)bVar13;
        cVar5 = (char)uVar3 + -1;
        uVar3 = CONCAT11((char)(uVar3 >> 8),cVar5);
        if (cVar5 == '\0') {
          uVar14 = FUN_1b5a_09f6();
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
        if (cVar5 == '\0') goto LAB_1b5a_08c2;
      }
    }
    bVar12 = 0xff7f < in_AX;
    in_AX = in_AX + 0x80;
    uVar10 = (uint)CARRY2(uVar9,(uint)bVar12);
    bVar12 = CARRY2(in_DX,uVar10);
    in_DX = in_DX + uVar10;
    if (bVar12) {
      in_DX = in_DX >> 1 | (uint)bVar12 << 0xf;
      cVar5 = (char)uVar3 + '\x01';
      uVar3 = CONCAT11((char)(uVar3 >> 8),cVar5);
      if (cVar5 == '\0') {
LAB_1b5a_08c2:
        return CONCAT22(in_DX,in_AX);
      }
    }
    in_AX = CONCAT11((char)(in_AX >> 8),(char)uVar3);
    in_DX = CONCAT11((byte)((in_DX & 0x7fff) >> 8) | (byte)(uVar3 >> 8),(char)(in_DX & 0x7fff));
  }
LAB_1b5a_08b4:
  return CONCAT22(in_DX,in_AX);
}



/* 1b5a:0835 FUN_1b5a_0835 */

undefined4 __cdecl16near FUN_1b5a_0835(void)

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
LAB_1b5a_08b5:
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
    if (0x27 < bVar2) goto LAB_1b5a_08b5;
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
      if ((in_DX == 0 && uVar9 == 0) && in_AX == 0) goto LAB_1b5a_08b4;
      while (-1 < (int)in_DX) {
        bVar11 = (int)in_AX < 0;
        in_AX = in_AX << 1;
        bVar12 = (int)uVar9 < 0;
        uVar9 = uVar9 << 1 | (uint)bVar11;
        in_DX = in_DX << 1 | (uint)bVar12;
        cVar5 = (char)uVar3 + -1;
        uVar3 = CONCAT11((char)(uVar3 >> 8),cVar5);
        if (cVar5 == '\0') {
          uVar13 = FUN_1b5a_09f6();
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
        if (cVar5 == '\0') goto LAB_1b5a_08c2;
      }
    }
    bVar11 = 0xff7f < in_AX;
    in_AX = in_AX + 0x80;
    uVar7 = (uint)CARRY2(uVar9,(uint)bVar11);
    bVar11 = CARRY2(in_DX,uVar7);
    in_DX = in_DX + uVar7;
    if (bVar11) {
      in_DX = in_DX >> 1 | (uint)bVar11 << 0xf;
      cVar5 = (char)uVar3 + '\x01';
      uVar3 = CONCAT11((char)(uVar3 >> 8),cVar5);
      if (cVar5 == '\0') {
LAB_1b5a_08c2:
        return CONCAT22(in_DX,in_AX);
      }
    }
    in_AX = CONCAT11((char)(in_AX >> 8),(char)uVar3);
    in_DX = CONCAT11((byte)((in_DX & 0x7fff) >> 8) | (byte)(uVar3 >> 8),(char)(in_DX & 0x7fff));
  }
LAB_1b5a_08b4:
  return CONCAT22(in_DX,in_AX);
}



/* 1b5a:08f8 FUN_1b5a_08f8 */

undefined4 __cdecl16near FUN_1b5a_08f8(void)

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
    uVar25 = FUN_1b5a_09f6();
    return uVar25;
  }
  iVar9 = CONCAT11((((byte)(in_DX >> 8) ^ (byte)(unaff_DI >> 8)) & 0x80) + CARRY1(bVar5,bVar8),
                   bVar5 + bVar8);
  uVar20 = in_DX | 0x8000;
  uVar21 = unaff_DI | 0x8000;
  if (((bVar7 == 0) &&
      (uVar6 = in_CX & 0xff00, uVar14 = uVar20, uVar10 = unaff_SI, uVar22 = uVar21, in_BX == 0)) ||
     ((bVar5 = (byte)(in_CX >> 8), bVar5 == 0 &&
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
    uVar14 = uVar14 >> 1 | (uint)CARRY2(uVar6,uVar20) << 0xf;
    uVar21 = iVar9 + 0x7f80;
  }
  if ((uVar21 & 0x4000) != 0) {
    return 0;
  }
  return CONCAT22(CONCAT11((byte)(uVar14 >> 8) ^ (byte)(uVar21 + 1 >> 8),(char)uVar14),
                  CONCAT11((char)(uVar15 + 0x80 >> 8),(char)(uVar21 + 1)));
}



/* 1b5a:09f6 FUN_1b5a_09f6 */

void __cdecl16near FUN_1b5a_09f6(void)

{
  return;
}



/* 1b5a:09fd FUN_1b5a_09fd */

undefined4 __cdecl16near FUN_1b5a_09fd(void)

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
            uVar10 = uVar10 >> 1 | (uint)CARRY2(uVar12,uVar8) << 0xf;
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



/* 1b5a:0a74 FUN_1b5a_0a74 */

void __cdecl16near FUN_1b5a_0a74(void)

{
  uint in_DX;
  uint unaff_DI;
  bool bVar1;
  
  if ((int)(in_DX ^ unaff_DI) < 0) {
    return;
  }
  bVar1 = (in_DX & 0x8000) == 0;
  if ((!bVar1) && (FUN_1b5a_0a8b(), !bVar1)) {
    return;
  }
  return;
}



/* 1b5a:0a8b FUN_1b5a_0a8b */

void __cdecl16near FUN_1b5a_0a8b(void)

{
  return;
}



/* 1b5a:0a9e FUN_1b5a_0a9e */

void __cdecl16near FUN_1b5a_0a9e(void)

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



/* 1b5a:0add FUN_1b5a_0add */

undefined4 __cdecl16near FUN_1b5a_0add(void)

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
      if ((int)uVar5 < 0) goto LAB_1b5a_0b32;
    }
    if ((int)in_DX < 0) {
      uVar3 = ~in_BX;
      in_BX = uVar3 + 1;
      uVar5 = ~uVar5 + (uint)(0xfffe < uVar3);
    }
    return CONCAT22(uVar5,in_BX);
  }
LAB_1b5a_0b32:
  return CONCAT22(uVar5,in_BX);
}



/* 1b5a:0b4b FUN_1b5a_0b4b */

void __cdecl16far FUN_1b5a_0b4b(void)

{
  undefined1 in_CF;
  
  FUN_1b5a_08f8();
  if (!(bool)in_CF) {
    return;
  }
  FUN_1b5a_00d1();
  return;
}



/* 1b5a:0b51 FUN_1b5a_0b51 */

void __cdecl16far FUN_1b5a_0b51(void)

{
  char in_CL;
  bool bVar1;
  
  bVar1 = false;
  if (in_CL == '\0') {
    FUN_1b5a_00d1();
    return;
  }
  FUN_1b5a_09fd();
  if (!bVar1) {
    return;
  }
  FUN_1b5a_00d1();
  return;
}



/* 1b5a:0b5f FUN_1b5a_0b5f */

void __cdecl16far FUN_1b5a_0b5f(void)

{
  FUN_1b5a_0a9e();
  return;
}



/* 1b5a:0b6b FUN_1b5a_0b6b */

void __cdecl16far FUN_1b5a_0b6b(void)

{
  undefined1 in_CF;
  
  FUN_1b5a_0add();
  if (!(bool)in_CF) {
    return;
  }
  FUN_1b5a_00d1();
  return;
}



/* 1b5a:0b85 FUN_1b5a_0b85 */

void __cdecl16near FUN_1b5a_0b85(void)

{
  FUN_1b5a_0835();
  return;
}



/* 1b5a:0b8f FUN_1b5a_0b8f */

void __cdecl16near FUN_1b5a_0b8f(void)

{
  FUN_1b5a_0831();
  return;
}



/* 1b5a:0b99 FUN_1b5a_0b99 */

void __cdecl16near FUN_1b5a_0b99(void)

{
  FUN_1b5a_08f8();
  return;
}



/* 1b5a:0ba3 FUN_1b5a_0ba3 */

void __cdecl16near FUN_1b5a_0ba3(void)

{
  FUN_1b5a_09fd();
  return;
}



/* 1b5a:0bad FUN_1b5a_0bad */

uint __cdecl16far FUN_1b5a_0bad(void)

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



/* 1b5a:0bfe FUN_1b5a_0bfe */

void __cdecl16far FUN_1b5a_0bfe(void)

{
  FUN_1b5a_0bad();
  FUN_1b5a_0831();
  return;
}



/* 1b5a:0c6f FUN_1b5a_0c6f */

void FUN_1b5a_0c6f(void)

{
  byte bVar1;
  undefined2 uVar2;
  uint extraout_DX;
  uint uVar3;
  uint extraout_DX_00;
  bool bVar4;
  undefined1 uVar5;
  
  bVar1 = FUN_1b5a_0835();
  uVar3 = extraout_DX;
  if (bVar1 != 0) {
    uVar3 = extraout_DX ^ 0x8000;
  }
  if (0x6b < bVar1) {
    uVar2 = 0x2183;
    bVar4 = false;
    FUN_1b5a_0a74();
    if (!bVar4) {
      FUN_1b5a_0ba3();
      FUN_1b5a_0bfe(uVar2,0xdaa2,0x490f);
      FUN_1b5a_0b99();
      uVar3 = extraout_DX_00;
    }
    uVar5 = 0;
    if ((uVar3 & 0x8000) != 0) {
      FUN_1b5a_0b85();
    }
    FUN_1b5a_0a74();
    if (!(bool)uVar5) {
      FUN_1b5a_0b8f();
    }
    bVar1 = FUN_1b5a_0a74();
    if (!(bool)uVar5) {
      bVar1 = FUN_1b5a_0835();
    }
    if (0x6b < bVar1) {
      FUN_1b5a_0f8e();
    }
  }
  return;
}



/* 1b5a:0c82 FUN_1b5a_0c82 */

void __cdecl16far FUN_1b5a_0c82(void)

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
    FUN_1b5a_0a74();
    if (!bVar3) {
      FUN_1b5a_0ba3();
      FUN_1b5a_0bfe(uVar2,0xdaa2,0x490f);
      FUN_1b5a_0b99();
      in_DX = extraout_DX;
    }
    uVar4 = 0;
    if ((in_DX & 0x8000) != 0) {
      FUN_1b5a_0b85();
    }
    FUN_1b5a_0a74();
    if (!(bool)uVar4) {
      FUN_1b5a_0b8f();
    }
    bVar1 = FUN_1b5a_0a74();
    if (!(bool)uVar4) {
      bVar1 = FUN_1b5a_0835();
    }
    if (0x6b < bVar1) {
      FUN_1b5a_0f8e();
    }
  }
  return;
}



/* 1b5a:0f8e FUN_1b5a_0f8e */

void FUN_1b5a_0f8e(void)

{
  FUN_1b5a_08f8();
  FUN_1b5a_0fa7();
  FUN_1b5a_08f8();
  return;
}



/* 1b5a:0fa7 FUN_1b5a_0fa7 */

void __cdecl16near FUN_1b5a_0fa7(void)

{
  int in_CX;
  int unaff_DI;
  undefined2 uStack_a;
  
  uStack_a = in_CX;
  while( true ) {
    FUN_1b5a_08f8();
    unaff_DI = unaff_DI + 6;
    uStack_a = uStack_a + -1;
    if (uStack_a == 0) break;
    FUN_1b5a_0835(unaff_DI);
  }
  FUN_1b5a_0835();
  return;
}



/* 1b5a:0ff6 FUN_1b5a_0ff6 */

uint __stdcall16far FUN_1b5a_0ff6(uint param_1)

{
  uint uVar1;
  uint extraout_DX;
  
  FUN_1b5a_1045();
  uVar1 = 0;
  if (param_1 != 0) {
    uVar1 = extraout_DX % param_1;
  }
  return uVar1;
}



/* 1b5a:1045 FUN_1b5a_1045 */

void __cdecl16near FUN_1b5a_1045(void)

{
  int iVar1;
  long lVar2;
  uint uVar3;
  char cVar4;
  int iVar5;
  undefined2 unaff_DS;
  
  iVar1 = *(int *)0x57c;
  lVar2 = (ulong)*(uint *)0x57a * (ulong)DAT_1000_107b;
  uVar3 = (uint)lVar2;
  iVar5 = *(uint *)0x57a << 3;
  cVar4 = (char)iVar5;
  iVar5 = (int)((ulong)lVar2 >> 0x10) + CONCAT11((char)((uint)iVar5 >> 8) + cVar4,cVar4) + iVar1 * 5
  ;
  *(int *)0x57a = uVar3 + 1;
  *(int *)0x57c =
       CONCAT11((char)((uint)iVar5 >> 8) + (char)iVar1 * '\x04' + (char)(iVar1 << 7),(char)iVar5) +
       (uint)(0xfffe < uVar3);
  return;
}



/* 1b5a:107d FUN_1b5a_107d */

void __cdecl16far FUN_1b5a_107d(void)

{
  code *pcVar1;
  undefined2 in_CX;
  undefined2 extraout_DX;
  undefined2 unaff_DS;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  *(undefined2 *)0x57a = in_CX;
  *(undefined2 *)0x57c = extraout_DX;
  return;
}



/* 1b5a:108a FUN_1b5a_108a */

void __cdecl16near FUN_1b5a_108a(void)

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
  puVar6 = (uint *)0x10dc;
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



/* 1b5a:1104 FUN_1b5a_1104 */

undefined4 __cdecl16near FUN_1b5a_1104(void)

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
  if (in_CX == 0) goto LAB_1b5a_1165;
  if (*unaff_DI == 0x2b) {
LAB_1b5a_1119:
    unaff_DI = unaff_DI + 1;
    in_CX = in_CX + -1;
    if (in_CX == 0) goto LAB_1b5a_1165;
  }
  else if (*unaff_DI == 0x2d) {
    bVar1 = true;
    goto LAB_1b5a_1119;
  }
  if (*unaff_DI == 0x24) {
    iVar4 = in_CX + -1;
    if (iVar4 == 0) {
LAB_1b5a_1165:
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
        if (bVar13) goto LAB_1b5a_1165;
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
      if ((uVar7 & 0xf000) != 0) goto LAB_1b5a_1165;
      uVar3 = uVar2 * 2;
      uVar8 = uVar7 << 1 | (uint)((int)uVar2 < 0);
      iVar4 = uVar2 << 2;
      uVar5 = uVar2 * 8;
      uVar7 = uVar2 * 10;
      uVar2 = uVar7 + uVar6;
      uVar7 = ((uVar8 << 1 | (uint)((int)uVar3 < 0)) << 1 | (uint)(iVar4 < 0)) + uVar8 +
              (uint)CARRY2(uVar5,uVar3) + (uint)CARRY2(uVar7,uVar6);
      if ((int)uVar7 < 0) goto LAB_1b5a_1165;
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



/* 1b5a:119c FUN_1b5a_119c */

void __stdcall16far FUN_1b5a_119c(int param_1,undefined1 *param_2,int param_3)

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
  FUN_1b5a_108a();
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



/* 1b5a:11e7 FUN_1b5a_11e7 */

undefined2 __stdcall16far FUN_1b5a_11e7(uint *param_1,byte *param_2)

{
  undefined2 uVar1;
  uint uVar2;
  byte *pbVar3;
  bool bVar4;
  
  bVar4 = false;
  uVar2 = (uint)*param_2;
  pbVar3 = (byte *)param_2;
  while ((pbVar3 = pbVar3 + 1, uVar2 != 0 && (bVar4 = *pbVar3 < 0x20, *pbVar3 == 0x20))) {
    uVar2 = uVar2 - 1;
  }
  uVar1 = FUN_1b5a_1104();
  if ((bVar4) || (uVar2 != 0)) {
    uVar2 = (int)pbVar3 - (int)(byte *)param_2;
    uVar1 = 0;
  }
  *param_1 = uVar2;
  return uVar1;
}



/* 1b5a:1218 FUN_1b5a_1218 */

void __stdcall16far FUN_1b5a_1218(byte *param_1,undefined2 *param_2)

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
  puVar6[8] = 0x132d;
  pbVar7[0] = 0x5a;
  pbVar7[1] = 0x1b;
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



/* 1b5a:1288 FUN_1b5a_1288 */

void FUN_1b5a_1288(void)

{
  FUN_1b5a_1295();
  return;
}



/* 1b5a:128d FUN_1b5a_128d */

void FUN_1b5a_128d(void)

{
  FUN_1b5a_1295();
  return;
}



/* 1b5a:1295 FUN_1b5a_1295 */

void __stdcall16far FUN_1b5a_1295(undefined4 param_1)

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
    FUN_1b5a_12e1(iVar2,uVar3);
  }
  else if (iVar1 != -0x2850) {
    *(undefined2 *)0x578 = 0x66;
    return;
  }
  bVar4 = true;
  *(undefined2 *)(iVar2 + 2) = in_DX;
  *(undefined2 *)(iVar2 + 8) = 0;
  *(undefined2 *)(iVar2 + 10) = 0;
  FUN_1b5a_131c();
  if (!bVar4) {
    *(undefined2 *)(iVar2 + 2) = 0xd7b0;
  }
  return;
}



/* 1b5a:12e1 FUN_1b5a_12e1 */

void __stdcall16far FUN_1b5a_12e1(undefined4 param_1)

{
  int iVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  
  uVar2 = (undefined2)((ulong)param_1 >> 0x10);
  iVar1 = (int)param_1;
  if (*(int *)(iVar1 + 2) != -0x284f) {
    if (*(int *)(iVar1 + 2) != -0x284e) {
      *(undefined2 *)0x578 = 0x67;
      return;
    }
    FUN_1b5a_131c();
  }
  FUN_1b5a_131c();
  *(undefined2 *)(iVar1 + 2) = 0xd7b0;
  return;
}



/* 1b5a:131c FUN_1b5a_131c */

void __cdecl16near FUN_1b5a_131c(void)

{
  int iVar1;
  int in_BX;
  int unaff_DI;
  undefined2 unaff_DS;
  
  iVar1 = (*(code *)*(undefined2 *)(in_BX + unaff_DI))(0x1b5a);
  if (iVar1 != 0) {
    *(int *)0x578 = iVar1;
  }
  return;
}



/* 1b5a:14d7 FUN_1b5a_14d7 */

void __cdecl16near FUN_1b5a_14d7(void)

{
  int unaff_DI;
  undefined2 unaff_ES;
  undefined2 unaff_DS;
  
  if ((*(int *)0x578 == 0) && (*(int *)(unaff_DI + 2) != -0x284e)) {
    *(undefined2 *)0x578 = 0x69;
  }
  return;
}



/* 1b5a:14fb FUN_1b5a_14fb */

undefined4 __cdecl16near FUN_1b5a_14fb(undefined4 param_1)

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
  iVar1 = (*(code *)*(undefined2 *)(iVar2 + 0x14))(0x1b5a,iVar2,uVar3,iVar2,uVar3);
  if (iVar1 != 0) {
    DAT_1ce5_0578 = iVar1;
  }
  return CONCAT22(*(undefined2 *)(iVar2 + 4),*(undefined2 *)(iVar2 + 10));
}



/* 1b5a:1564 FUN_1b5a_1564 */

void __stdcall16far FUN_1b5a_1564(undefined4 param_1)

{
  int iVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  undefined1 in_ZF;
  
  uVar2 = (undefined2)((ulong)param_1 >> 0x10);
  iVar1 = (int)param_1;
  FUN_1b5a_14d7();
  if ((bool)in_ZF) {
    FUN_1b5a_14fb();
    FUN_1b5a_14fb();
  }
  *(undefined2 *)(iVar1 + 8) = register0x00000010;
  if ((*(int *)(iVar1 + 0x1a) != 0) && (*(int *)0x578 == 0)) {
    iVar1 = (*(code *)*(undefined2 *)(iVar1 + 0x18))(0x1b5a,iVar1,uVar2);
    if (iVar1 != 0) {
      *(int *)0x578 = iVar1;
    }
  }
  return;
}



/* 1b5a:15e1 FUN_1b5a_15e1 */

void __stdcall16far FUN_1b5a_15e1(int param_1,byte *param_2,undefined4 param_3)

{
  int iVar1;
  uint uVar2;
  undefined2 in_BX;
  undefined1 in_ZF;
  
  FUN_1b5a_14d7();
  if ((bool)in_ZF) {
    uVar2 = (uint)*param_2;
    iVar1 = param_1 - uVar2;
    if (iVar1 != 0 && (int)uVar2 <= param_1) {
      do {
        FUN_1b5a_14fb();
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
      uVar2 = (uint)*param_2;
    }
    for (; uVar2 != 0; uVar2 = uVar2 - 1) {
      FUN_1b5a_14fb();
    }
  }
  *(undefined2 *)((int)param_3 + 8) = in_BX;
  return;
}



/* 1b5a:161f FUN_1b5a_161f */

void __stdcall16far FUN_1b5a_161f(byte *param_1,undefined2 *param_2)

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



/* 1b5a:164d FUN_1b5a_164d */

void __stdcall16far FUN_1b5a_164d(undefined2 param_1,undefined2 *param_2)

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
      *(undefined2 *)0x578 = 0x66;
      return;
    }
    FUN_1b5a_16ce(puVar3,uVar4);
  }
  uVar2 = 0;
  if (*(char *)(puVar3 + 0x18) != '\0') {
    bVar5 = false;
    pcVar1 = (code *)swi(0x21);
    uVar2 = (*pcVar1)();
    if (bVar5) {
      *(undefined2 *)0x578 = uVar2;
      return;
    }
  }
  puVar3[1] = 0xd7b3;
  *param_2 = uVar2;
  puVar3[2] = param_1;
  return;
}



/* 1b5a:1656 FUN_1b5a_1656 */

void __stdcall16far FUN_1b5a_1656(undefined2 param_1,undefined2 *param_2)

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
      *(undefined2 *)0x578 = 0x66;
      return;
    }
    FUN_1b5a_16ce(puVar3,uVar4);
  }
  uVar2 = 1;
  if (*(char *)(puVar3 + 0x18) != '\0') {
    bVar5 = false;
    pcVar1 = (code *)swi(0x21);
    uVar2 = (*pcVar1)();
    if (bVar5) {
      *(undefined2 *)0x578 = uVar2;
      return;
    }
  }
  puVar3[1] = 0xd7b3;
  *param_2 = uVar2;
  puVar3[2] = param_1;
  return;
}



/* 1b5a:16ce FUN_1b5a_16ce */

void __stdcall16far FUN_1b5a_16ce(uint *param_1)

{
  code *pcVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  bool bVar3;
  undefined1 in_ZF;
  
  FUN_1b5a_16f3();
  if ((bool)in_ZF) {
    bVar3 = *param_1 < 4;
    if (4 < *param_1) {
      pcVar1 = (code *)swi(0x21);
      uVar2 = (*pcVar1)();
      if (bVar3) {
        *(undefined2 *)0x578 = uVar2;
      }
    }
    ((uint *)param_1)[1] = 0xd7b0;
  }
  return;
}



/* 1b5a:16f3 FUN_1b5a_16f3 */

void __cdecl16near FUN_1b5a_16f3(void)

{
  int unaff_DI;
  undefined2 unaff_ES;
  undefined2 unaff_DS;
  
  if (*(int *)(unaff_DI + 2) != -0x284d) {
    *(undefined2 *)0x578 = 0x67;
  }
  return;
}



/* 1b5a:1702 FUN_1b5a_1702 */

void __stdcall16far FUN_1b5a_1702(undefined2 param_1,undefined2 param_2,undefined4 param_3)

{
  code *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int unaff_BP;
  undefined1 in_CF;
  undefined1 in_ZF;
  undefined2 in_stack_00000000;
  
  FUN_1b5a_16f3();
  if ((bool)in_ZF) {
    iVar4 = *(int *)((int)param_3 + 4);
    pcVar1 = (code *)swi(0x21);
    iVar2 = (*pcVar1)();
    iVar3 = iVar2;
    if (((bool)in_CF) || (iVar3 = unaff_BP, iVar2 != iVar4)) {
      *(int *)0x578 = iVar3;
    }
  }
  return;
}



/* 1b5a:1709 FUN_1b5a_1709 */

void __stdcall16far FUN_1b5a_1709(undefined2 param_1,undefined2 param_2,undefined4 param_3)

{
  code *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int unaff_BP;
  undefined1 in_CF;
  undefined1 in_ZF;
  undefined2 in_stack_00000000;
  
  FUN_1b5a_16f3();
  if ((bool)in_ZF) {
    iVar4 = *(int *)((int)param_3 + 4);
    pcVar1 = (code *)swi(0x21);
    iVar2 = (*pcVar1)();
    iVar3 = iVar2;
    if (((bool)in_CF) || (iVar3 = unaff_BP, iVar2 != iVar4)) {
      *(int *)0x578 = iVar3;
    }
  }
  return;
}



/* 1b5a:1738 FUN_1b5a_1738 */

void __stdcall16far
FUN_1b5a_1738(uint *param_1,uint param_2,undefined2 param_3,undefined2 param_4,undefined4 param_5)

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
  FUN_1b5a_16f3();
  iVar5 = (int)((ulong)param_1 >> 0x10);
  if ((bool)in_ZF) {
    uVar2 = param_2;
    if (param_2 != 0) {
      bVar6 = (int)((ulong)param_2 * (ulong)*(uint *)((int)param_5 + 4) >> 0x10) != 0;
      pcVar1 = (code *)swi(0x21);
      uVar2 = (*pcVar1)();
      if (bVar6) {
        *(uint *)0x578 = uVar2;
        goto LAB_1b5a_178e;
      }
      uVar2 = uVar2 / *(uint *)((int)param_5 + 4);
      uVar3 = unaff_BP;
      unaff_DS = in_stack_00000000;
    }
    if (iVar5 == 0 && (uint *)param_1 == (uint *)0x0) {
      if (uVar2 != param_2) {
        *(undefined2 *)0x578 = uVar3;
      }
    }
    else {
      *param_1 = uVar2;
    }
  }
  else {
LAB_1b5a_178e:
    if (iVar5 != 0 || (uint *)param_1 != (uint *)0x0) {
      *param_1 = 0;
    }
  }
  return;
}



/* 1b5a:17a0 FUN_1b5a_17a0 */

void __stdcall16far FUN_1b5a_17a0(uint param_1,int param_2,undefined4 param_3)

{
  code *pcVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  bool bVar3;
  undefined1 in_ZF;
  
  uVar2 = (undefined2)((ulong)param_3 >> 0x10);
  FUN_1b5a_16f3();
  if ((bool)in_ZF) {
    bVar3 = CARRY2(param_2 * *(int *)((int)param_3 + 4),
                   (uint)((ulong)param_1 * (ulong)*(uint *)((int)param_3 + 4) >> 0x10));
    pcVar1 = (code *)swi(0x21);
    uVar2 = (*pcVar1)();
    if (bVar3) {
      *(undefined2 *)0x578 = uVar2;
    }
  }
  return;
}



/* 1b5a:17e7 FUN_1b5a_17e7 */

undefined2 __stdcall16far FUN_1b5a_17e7(void)

{
  undefined2 uVar1;
  undefined2 in_CX;
  int unaff_DI;
  undefined2 unaff_ES;
  undefined1 in_CF;
  
  uVar1 = FUN_1b5a_1817();
  if ((!(bool)in_CF) && (uVar1 = in_CX, *(int *)(unaff_DI + 4) != 1)) {
    uVar1 = FUN_1b5a_0294();
  }
  return uVar1;
}



/* 1b5a:1817 FUN_1b5a_1817 */

undefined2 __cdecl16near FUN_1b5a_1817(undefined2 param_1,undefined2 param_2,undefined4 param_3)

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
  *(undefined2 *)0x578 = 0x67;
  return 0;
}



/* 1b5a:185c FUN_1b5a_185c */

void __stdcall16far FUN_1b5a_185c(int param_1,undefined1 *param_2,undefined1 *param_3)

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



/* 1b5a:187f FUN_1b5a_187f */

void __stdcall16far FUN_1b5a_187f(undefined1 param_1,int param_2,undefined1 *param_3)

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



/* 1b5a:1893 FUN_1b5a_1893 */

byte __stdcall16far FUN_1b5a_1893(byte param_1)

{
  if ((0x60 < param_1) && (param_1 < 0x7b)) {
    param_1 = param_1 - 0x20;
  }
  return param_1;
}


