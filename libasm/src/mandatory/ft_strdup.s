section .text
	global ft_strdup ;export ft_strdup
	extern __errno_location
	extern malloc
	extern ft_strlen
	extern ft_strcpy
ft_strdup: ;char *($rax)ft_strdup(const char *src($rdi))
	push rbp ; push the stack
	mov rbp, rsp ; update the base stack ptr
	mov r12, rdi
	call ft_strlen
	mov rdi, rax
	inc rdi
	call malloc wrt ..plt; call malloc -> void *($rax)malloc(unsigned long size($edi))
	mov rdi, rax
	mov rsi, r12
	call ft_strcpy
	jmp .end_loop ; start over the loop
.end_loop:
	pop rbp ; pop the stack
	ret ; return 

section .note.GNU-stack noalloc noexec nowrite progbits ;use to silence some warning