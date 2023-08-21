section .text
	global ft_strcmp ;export ft_strcmp
ft_strcmp: ;int[$eax] strcmp(const char *s1[$rdi], const char *s2[$rsi])
.start_loop:
	mov ah, byte [rdi] ; load one char of rdi into ah
	mov al, byte [rsi] ; load one char of rsi into al
	cmp ah, al ; compare both chars
	jne .end_loop ; if not equal, end the loop
	cmp ah, 0x0 ; compare ah to 0
	je .end_loop ; if equal , end the loop
	cmp al, 0x0 ; compare al to 0
	je .end_loop ; if equal, end the loop
	inc rdi ; increment rdi ptr
	inc rsi ; increment rsi ptr
	jmp .start_loop ; start over the loop
.end_loop:
	sub ah, al ;    subtract to return the right value
	movsx eax, ah ; move the result inside eax but keeping the sign bytes
	ret ; return

section .note.GNU-stack noalloc noexec nowrite progbits ;use to silence some warning