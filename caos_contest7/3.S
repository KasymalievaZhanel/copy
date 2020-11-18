#include <asm/unistd_32.h>

    .intel_syntax noprefix
    .text
    .global _start
_start:
//текущий указатель на кучу
	mov eax, __NR_brk
	mov ebx, 0
	int 0x80

	mov esi, eax
	add esi, 4096
//увеличили кучу
	mov eax, __NR_brk
	mov ebx, esi
	int 0x80

	sub esi, 4096//Начало кучи

        mov ebp, 4096//Доступная память
        mov edi, esi//Текущий указатель на свободную память
        push esi

.loop:
        mov edx, 0
        cmp ebp, edx
        ja .Cycle
        jmp .heap_memory
.Cycle:
	mov eax, __NR_read
	mov ebx, 0
	mov ecx, edi
	mov edx, ebp
	int 0x80
        
        mov ecx, eax
        mov eax , '\n'
        cld
        repne scasb
        je .found
        
        jmp .End_of_Cycle
.found:
        push edi
        jmp ._Cycle
._Cycle:

.End_of_Cycle:
        // total read
        add edi, ecx

        cmp ecx, ebx
        jz .end_of_loop
        //free pamyat
        sub ebp, ecx
        jmp .loop


.heap_memory:
        mov eax, __NR_brk
        mov ebx, 0
        int 0x80

        mov ecx, eax
        add ecx, 4096

        add ebp, 4096

        mov eax, __NR_brk
        mov ebx, ecx
        int 0x80
        jmp .loop

.end_of_loop:
       // sub edi, esi//сколько памяти занято
        mov ebp, edi


.Circle:
        pop edi
        cmp edi, esi
        jz .END_Circle
        sub ebp, edi
	mov eax, __NR_write
	mov ebx, 1
	mov ecx, edi
	mov edx, ebp
	int 0x80
        mov ebp, edi
//        sub esi, edi
        jmp .Circle

.END_Circle:
        sub ebp, edi
        mov eax, __NR_write
        mov ebx, 1
        mov ecx, edi
        mov edx, ebp
        int 0x80
        mov ebp, edi
        jmp .END
.END:
        mov eax, __NR_brk
        mov ebx, 0
        int 0x80
        mov ecx, eax
	// free
	sub esi, ecx
	mov eax, __NR_brk
	mov ebx, esi
	int 0x80

	mov eax, __NR_exit
	mov ebx, 0
	int 0x80

