section .text
	global ft_strdup ;export ft_strdup
	extern __errno_location
	extern malloc
	extern ft_strlen
	extern ft_strcpy
ft_strdup: ;char *[$rax]ft_strdup(const char *src[$rdi])
    push rdi
;	mov r8, rdi ; save src pointer into r8
	call ft_strlen ; call ft_strlen on src
	mov rdi, rax ; mov the result into rdi
	inc rdi ; increment rdi by one
	call malloc wrt ..plt; call malloc -> void *($rax)malloc(unsigned long size($edi))
	cmp rax, 0x0 ; check if malloc fail
	je .end_loop ; if it fail, jump
	mov rdi, rax ; mov the result of malloc into rdi
;	mov rsi, r8 ; move src pointer into rsi
	pop rsi
	call ft_strcpy ; call ft_strcpy
.end_loop:
	ret ; return

section .note.GNU-stack noalloc noexec nowrite progbits ;use to silence some warning