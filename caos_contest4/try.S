.text


.global main

main:
    push {r4,r5,r6,r7,r8}
    ldr r0, =string_1
    ldr r1, [sp]
    sub sp, sp, #4
    ldr r2, [sp]
    sub sp, sp, #4
    bl scanf
    pop {r4, r5, r6,r7,r8} 
    bx lr
.data
string_1:
        .string "%d "
