section .text
	global ft_read ;export ft_read
	extern __errno_location
ft_read: ; long[$rax] ft_read(int fd[$edi], char *buff[$rsi], unsigned long buff_size[$edx])
	mov rax, 0 ;load up syscall code 0 (read) into rax
	syscall ; calling syscall
	cmp eax, 0 ; compare the return value with 0
	jl .error_handle ; jump to error_handle if the previous compare was less than 0
	ret ; return
.error_handle: ; if an error occur during read syscall
	neg eax ; make value in eax positive
	mov edx, eax ; save eax inside edx
	call __errno_location wrt ..plt; save errno location inside eax
	mov [rax], edx ; change the value pointer by eax by edx
	mov rax, -0x01 ; change the return value with -1
	ret ; return

section .note.GNU-stack noalloc noexec nowrite progbits ;use to silence some warning