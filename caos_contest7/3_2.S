#include <asm/unistd_32.h>

    .intel_syntax noprefix
    .text
    .global _start
_start:
        mov eax, __NR_brk
        mov ebx, 0
        int 0x80

        mov edi, eax

        add edi, 4096

        mov eax, __NR_brk
        mov ebx, edi
        int 0x80

        sub edi, 4096
        mov esi, edi
        mov ebp, 4096
        jmp .loop
.loop:
        //проверить есть ли свободное место для записи
        mov eax, 0
        cmp ebp, eax
        jbe .add_memory_to_heap
        jmp .read_text

	.read_text:
	        mov eax, __NR_read
	        mov ebx, 0
	        mov ecx, esi
	        mov edx, 4096
	        int 0x80

	        // total read
	        add esi, eax
	        sub ebp, eax

	        cmp eax, ebx
	        jz .end_of_loop

        	jmp .loop
.add_memory_to_heap:
        mov eax, __NR_brk
        mov ebx, 0
        int 0x80

        mov ecx, eax

        add ecx, 4096

        mov eax, __NR_brk
        mov ebx, ecx
        int 0x80

        add ebp, 4096
        jmp .read_text

.end_of_loop:

	.find_symbol:
	        push edi
	        sub esi, 1
	        mov edi, esi
	        mov al, '\n'
	        cld
	        repne scasb
	        je .found

	        add esi, 1
	        movb [esi], '\n'
	        add esi, 1
	        jmp .end
	.found:
	        sub esi, 1
	        mov eax, __NR_write
	        mov ebx, 1
	        mov ecx, esi
	        mov edx, 1
	        int 0x80

	        add esi, 2
	        jmp .end
	.end:
	        pop edi
	       //
                sub esi, edi
                push esi
                
        .write_text:
                mov ecx, esi
                mov al, '\n'
                .find:
                mov ebx, 0
                cmp ecx, ebx
                jbe .end_of_find
                scasb

//                push eax
                sub esi, eax
                jmp .write_text
                .end_of_find:
                pop esi
                mov ebp, esi
               /* .cycle_of_writing:
                pop eax
                sub ebp, eax
                mov ebx, 0
                cmp ebp, ebx
                jbe .exit
	        mov eax, __NR_write
	        mov ebx, 1
	        mov ecx, eax
	        mov edx, ebp
         	 int 0x80
                sub ebp, eax
                jmp .cycle_of_writing*/
	.exit:
        // free
                mov eax, __NR_brk
                mov ebx, 0
                int 0x80
                
              //  sub eax, edi
	      //  sub edi, eax
	        mov eax, __NR_brk
	        mov ebx, edi
	        int 0x80


        //exit
        mov eax, __NR_exit
        mov ebx, 0
        int 0x80




