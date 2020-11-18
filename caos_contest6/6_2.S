.intel_syntax noprefix
  .global dot_product
  .text


dot_product:
  subss xmm0, xmm0
  mov rcx, -4

Loop1:
  add   rcx, 4
  cmp   rdi, 4
  jb   Loop2
  movaps   xmm1, [rsi + 4*rcx]
  movaps   xmm2, [rdx + 4*rcx]
  dpps   xmm1, xmm2, 0xFF
  addps   xmm0, xmm1
  sub   rdi, 4
  jmp   Loop1

Loop2:
  cmp   rdi, 0
  jz   end
  movss   xmm1, [rsi + 4*rcx]
  movss   xmm2, [rdx + 4*rcx]
  mulss   xmm1, xmm2
  addss   xmm0, xmm1
  sub   rdi, 1
  add   rcx, 1
  jmp   Loop2

end:
      ret
