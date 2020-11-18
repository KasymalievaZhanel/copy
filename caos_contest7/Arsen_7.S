#include <asm/unistd_32.h>

.intel_syntax noprefix

.global _start
.text
.data

    buffer:
        .long 0

    space:
        .long 8192

    endline:
        .byte 10


_start:
    mov eax, __NR_brk
    mov ebx, 0
    int 0x80
    mov [buffer], eax

    mov eax, __NR_brk
    mov ebx, space
    add ebx, [buffer]
    int 0x80
    mov edi, 0//текущий указатель на св. память
    
read:
    mov eax,  __NR_read
    mov ecx, [buffer]
    add ecx, edi
    mov ebx, 0
    mov edx, 8192
    int 0x80

    cmp eax, 0
    je start_write//je

    add edi, eax

    cmp edi, space
    jne read//jne
    mov eax, __NR_brk
    mov ebx, space
    add ebx, space
    mov space, ebx
    add ebx, [buffer]
    int 0x80
    jmp read

start_write:
    cmp edi, 0
    jz end
    sub edi, 1
    mov eax, edi
    add eax, [buffer]
    mov eax, [eax]
    cmpb al, endline
    je write
    add edi, 1

write:
    cmp edi, 0
    jle end
    mov esi, edi

loop:
    dec esi
    cmp esi, 0
    je print
    mov eax, [buffer]
    add eax, esi
    mov eax, [eax]
    cmpb al, endline
    jne loop
    add esi, 1
    jmp print

print:
    mov al, endline
    mov ebx, 1
    mov ecx, [buffer]
    add ecx, esi
    mov edx, edi
    sub edx, esi
    movb [ecx + edx], al
    mov eax, __NR_write
    inc edx
    mov edi, esi
    dec edi
    int 0x80
    jmp write

end:
    mov eax, 1
    mov ebx, 0 
    int 0x80
