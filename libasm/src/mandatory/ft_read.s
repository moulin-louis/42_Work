section .text
	global ft_read ;export ft_read
	extern __errno_location
ft_read: ; long ft_read(int fd($edi), char *buff($rsi), unsigned long buff_size($edx))
	push rbp ; push the stack
	mov rbp, rsp ; update the base stack ptr
	mov rax, 0x00 ;load up syscall code 0 (read) into rax
	movsxd rdi, edi ; move edi arg into rdi (load fd into rdi registser)
	; buff is already where it should be, inside $rsi register
	movsxd rdx, edx ;find register to load (load buff_size into rdx register)
	syscall ; calling the syscall (here read)
	cmp eax, 0x00 ; compare the return value with 0
	jl .error_handle ; jump to error_handle if the previous compare was less than 0
	pop rbp ; pop the stack
	ret ; return 
.error_handle:
	neg eax ; make value in eax positive
	mov edx, eax ; save eax inside edx
	call __errno_location wrt ..plt; save errno location inside eax
	mov [rax], edx ; change the value pointer by eax by edx
	mov rax, -0x01 ; change the return value with -1
	pop rbp ; pop the stack
	ret ; return 

section .note.GNU-stack noalloc noexec nowrite progbits ;use to silence some warning