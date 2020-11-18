.text
.global summ


temp .req r4

summ:
 push {r4}
 mov r3, #0    // i = 0
for:
  cmp r3, r1     // i < N
  bge end_for    // -> endfor
  ldr temp, [r2, r3, LSL #2]  // temp = X[i]
  add r0, r0, temp   // x0+=temp
  add r3, r3, #1    // ++i
  b for
end_for:
  mov r1, r0
  pop {r4}

 bx lr