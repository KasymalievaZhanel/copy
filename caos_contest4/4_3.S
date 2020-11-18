.text
	.global main
main: 
	push {r4, r5, r6, r7, r8, lr}
	ldr r4, .args
	ldr r4, [r4]
	ldr r5, .args+4
	ldr r5, [r5]
	mov r8, #4 	//array_size = 4
        //malloc 
	mov r1, r8
	mov r0, #0
	bl realloc
	mov r6, r0	//r6 = pointer to array
	mov r7, #0	//r7 = index = 0

.loop:
	mov r0, r4
	bl fgetc	//r0 = input
	mov r3, r0	//r3 = r0
	cmp r3, #0	//end of the input
	ble .end
	str r3, [r6,r7]	
	add r7, r7, #4	
	add r8, r8, #4	
	mov r1, r8	
	mov r0, r6	
	bl realloc	//realloc(array, array_size)
	mov r6, r0	//r6 = pointer to array
	b .loop
.end:
	sub r7, r7, #4
	mov r1, r5
	ldr r0, [r6, r7]
	bl fputc
	cmp r7, #0	//index == 0
	bne .end	
	mov r0, r6
	bl free		
	pop {r4, r5, r6, r7, r8, lr}
	bx lr
.args:
	.word stdin
	.word stdout
