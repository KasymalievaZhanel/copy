.global mergesort
.intel_syntax noprefix
        .text

mergesort:
    push    ebp
    mov     ebp, esp
//    push    ebx

    sub     ebp, 4//temp
    mov     eax, ebp//
    add     eax, 4//где лежит переменная
//    mov     [ebp], eax//где лежит ее адресс
    //индексы
    mov     eax, ebp
    add     eax, 12
    mov     eax, [eax]
    mov     edx, ebp
    add     edx, 16
    mov     edx, [edx]

    cmp     eax, edx//from < to
    jb      .Curcle
    jae     .EndOfLoop
.EndOfLoop:
    pop     ebp
    ret
.Curcle:
    mov     eax, [ebp + 12]//положить ноль
    mov     ecx, [ebp]//положить адр темп
    add     eax, [ebp + 16]//положить 10
    sar     eax,  1//разделить на 2
    mov     [ebp], eax//положить по адрессу темп значение

//    mov     eax, [ebp]//проверка done
//    pop ebp
//    ret
    mov   ecx,  [ebp+20]
    mov eax,    [ecx]
//  mov   eax   ebp + 24
    push [ebp + 24]
    pop   [ebp + 24]
/*    push [ebp + 20]
    push [ebp + 0]
    push [ebp + 12]
    call    mergesort
    pop   [ebp + 24]
    pop   [ebp + 20]
    pop   [ebp + 0]
    pop   [ebp + 12]*/
//    call  push
    //epiloque
    pop     ebp
    ret
