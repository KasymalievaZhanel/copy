.text
  .global main


main:
//push
  push {r4, lr}

  ldr r4, args
 
//  sub r1, sp, #4
//  sub r2, sp, #8
  sub sp, sp, #8
  mov r0, r4
  bl scanf
//summ
  ldr r2, [sp]
  ldr r1, [sp, #4]
  add r1, r1, r2
//printf
  ldr r4, args + 4
  mov r0, r4
  bl printf
//go back
  mov r0, #0
  add sp, sp, #8
//pop
  pop {r4, pc}



// pointers
args:
  .word scan
  .word print
// values
scan:
  .ascii "%d %d\0"
print:
  .ascii "%d\0"
