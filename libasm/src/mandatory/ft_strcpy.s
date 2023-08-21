section .text
	global ft_strcpy ;export ft_strcpy
ft_strcpy: ; char *[$rax] ft_strpcy(char *dest[$rdi], const char *src[$rsi]);
    mov rax, 0x0
    cmp rsi, 0x0
    je .error
	mov r8, rdi ;save dest ptr to r8
.start_loop:
	mov al, byte [rsi] ; load one char of src
	cmp al, 0x0 ; cmp loaded char of src with 0
	je .end_loop ; if equal to 0, jump to end_loop
	mov [rdi], al ; change the value pointed by rdi to value inside al
	inc rdi ; increment rdi ptr
	inc rsi ; increment rsi ptr
	jmp .start_loop ; start over the loop
.end_loop:
    mov [rdi], al ; zero terminate the string because al is equal to 0 in this situation
	mov rax, r8 ; move the save dest ptr to rax
.error:
	ret ; return

section .note.GNU-stack noalloc noexec nowrite progbits ;use to silence some warning