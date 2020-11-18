.text
.global main

main:

push  {r4,r5,r6,r7,r8,lr}
ldr   r4, .args
ldr   r5, .args+4
.Loopbegin:
ldr   r0, [r4]
bl    fgetc
cmp   r0, #0
ble   .LoopEnd
cmp   r0, #48
blt   .Loopbegin
cmp   r0, #57
bgt   .Loopbegin
ldr   r1, [r5]
bl    fputc
b     .Loopbegin
.LoopEnd:
pop {r4,r5,r6,r7,r8,lr}
bx lr
.args:
.word stdin
.word stdout
