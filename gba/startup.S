.syntax unified
.cpu arm7tdmi
.arm
.section .header,"ax",%progbits
.global _rom_entry
_rom_entry:
 b _start
 .space 188
.section .text.startup,"ax",%progbits
.global _start
_start:
 msr cpsr_c, #0xd2
 ldr sp, =0x03007fa0
 msr cpsr_c, #0xdf
 ldr sp, =0x03007f00
 ldr r0, =__data_load
 ldr r1, =__data_start
 ldr r2, =__data_end
1: cmp r1,r2
 ldrlo r3,[r0],#4
 strlo r3,[r1],#4
 blo 1b
 ldr r1,=__bss_start
 ldr r2,=__bss_end
 mov r3,#0
2: cmp r1,r2
 strlo r3,[r1],#4
 blo 2b
 msr cpsr_c,#0x5f
 ldr r0,=gba_main
 mov lr,pc
 bx r0
3: b 3b
.ltorg
.align 2
.global gba_irq
.type gba_irq,%function
gba_irq:
 mov r0,#0x04000000
 add r0,r0,#0x200
 ldrh r1,[r0]
 ldrh r2,[r0,#2]
 and r1,r1,r2
 strh r1,[r0,#2]
 ldr r0,=0x03007ff8
 ldrh r2,[r0]
 orr r2,r2,r1
 strh r2,[r0]
 push {r4,lr}
 mov r0,r1
 ldr r3,=game_irq
 mov lr,pc
 bx r3
 pop {r4,lr}
 bx lr
.ltorg

