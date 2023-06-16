section .text
	global ft_strlen ;export ft_strlen
ft_strlen: ;unsigned long($rax) ft_strlen(const char *str($rdi))
	push rbp ; push the stack
	mov rbp, rsp ; update the base stack ptr
	mov r11, rdi ; copy rdi to 411
.start_loop:
	cmp byte [r11], 0 ; compare deref ptr store in 411 with 0
	jz .end_loop ;jump to end loop if ptr is 0
	inc r11 ; increment the pointer inside 411
	jmp .start_loop ; jump to start loop, if ptr unequal to 0
.end_loop:
	sub r11, rdi ; substract the save ptr in r11 to the new one in 411
	mov rax, r11 ; store it in rax
	pop rbp ; pop the stack
	ret ; exiting the function

 section .note.GNU-stack noalloc noexec nowrite progbits ;use to silence some warning