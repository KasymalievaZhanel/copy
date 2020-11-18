#include <asm/unistd_32.h>

    .intel_syntax noprefix
    .text
    .global _start
_start:
	mov eax, __NR_brk
	mov ebx, 0
	int 0x80
	
	mov edi, eax
	
	add edi, 96
	
	mov eax, __NR_brk
	mov ebx, edi
	int 0x80

	sub edi, 96
        jmp .loop
.loop:
	mov eax, __NR_read
	mov ebx, 0
	mov ecx, edi
	mov edx, 96
	int 0x80

	// total read
	mov esi, eax

        cmp esi, ebx
        jz .end_of_loop

	mov eax, __NR_write
	mov ebx, 1
	mov ecx, edi
	mov edx, esi
	int 0x80
        jmp .loop

.end_of_loop:
	// free
	sub edi, 96
	mov eax, __NR_brk
	mov ebx, edi
	int 0x80


        //exit
	mov eax, __NR_exit
	mov ebx, 0
	int 0x80
	

