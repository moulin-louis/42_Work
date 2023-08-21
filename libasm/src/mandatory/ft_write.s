section .text
	global ft_write ;export ft_write
	extern __errno_location
ft_write: ; long[$rax] ft_write(int fd[$edi], void *buff[$rsi], unsigned long buff_size[$edx])
	mov rax, 1 ;load up syscall code 1 (write) into rax
	syscall ; calling the syscall
	cmp eax, 0x0 ; compare the return value with 0
	jl .error_handle ; jump to error_handle if the previous compare was less than 0
	ret ; return
.error_handle:
	neg eax ; make value in eax positive
	mov edx, eax ; save eax inside edx
	call __errno_location wrt ..plt; save errno location inside eax
	mov [rax], edx ; change the value of eax by edx
	mov rax, -1 ; change the return value with -1
	ret ; return

section .note.GNU-stack noalloc noexec nowrite progbits ;use to silence some warning