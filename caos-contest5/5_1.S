.global summ
.intel_syntax noprefix
        .text

summ:
        // prologue
        push    ebp
        mov     ebp, esp
        push    ebx
        mov     ecx, [ebp + 8]
.Loop:
        // R[N-1] = A[N-1] + B[N-1]
        mov     ebx, ecx
        dec     ebx  // ebx = N-1
        mov     edx, [ebp + 12]
        mov     eax, [edx + 4*ebx]
        mov     edx, [ebp + 16]
        add     eax, [edx + 4*ebx]  // += B[N-1]
        mov     edx, [ebp + 20]
        mov     [edx + 4*ebx], eax // R[N-1] = %eax
        loop    .Loop
        
        // epilogue
        pop     ebx
        pop     ebp
        ret
