.syntax unified
.cpu arm7tdmi
.arm
.text
.align 2
.global __aeabi_uidiv
.global __aeabi_uidivmod
.type __aeabi_uidiv,%function
.type __aeabi_uidivmod,%function
__aeabi_uidiv:
__aeabi_uidivmod:
 push {r4-r6,lr}
 mov r4,r0
 mov r5,r1
 ldr r6,=pole_udiv
 mov lr,pc
 bx r6
 mul r1,r0,r5
 sub r1,r4,r1
 pop {r4-r6,lr}
 bx lr
.global __aeabi_idiv
.global __aeabi_idivmod
.type __aeabi_idiv,%function
.type __aeabi_idivmod,%function
__aeabi_idiv:
__aeabi_idivmod:
 push {r4-r8,lr}
 mov r4,r0
 mov r5,r1
 eor r6,r0,r1
 cmp r0,#0
 rsblt r0,r0,#0
 cmp r1,#0
 rsblt r1,r1,#0
 ldr r7,=pole_udiv
 mov lr,pc
 bx r7
 cmp r6,#0
 rsblt r0,r0,#0
 mul r1,r0,r5
 sub r1,r4,r1
 pop {r4-r8,lr}
 bx lr
.ltorg
