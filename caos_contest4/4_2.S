    .text
    .global main

main:

    push  {r4,r5,r6,r7,lr}
    ldr   r4, .args
    ldr   r5, .args+4

.Loopbegin:
    ldr   r0, [r4]
    bl    fgets
    sub   r3, r0, #48
    and   r3, r0, #255
    cmp   r3, #9
    bhi   .Loopbegin
    b     .Loopend

.Loopend:
    ldr   r1,[r5]
    and   r0,r0,#255
    bl    fputs

.args:
    .word stdin
    .word stdout

