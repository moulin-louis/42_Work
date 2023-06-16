section .text
	global ft_strcmp ;export ft_strcmp
ft_strcmp: ;int($eax) strcmp( char *s1($rdi), char *s2($rsi))
	push rbp ; push the stack
	mov rbp, rsp ; update the base stack ptr
.start_loop:
	mov ah, byte [rdi] ; load one char of rdi
	mov al, byte [rsi] ; load one char of rsi
	cmp ah, al ; compare both chars
	jne .end_loop ; if not equal, end the loop
	cmp ah, 0x0 ; compare the first char loaded to 0
	je .end_loop ; if equal , end the loop
	cmp al, 0x0 ; compare the 2nd char loaded to 0
	je .end_loop ; if equal, end the loop
	inc rdi ; increment rsi ptr
	inc rsi ; increment rdi ptr
	jmp .start_loop ; start over the loop
.end_loop:
	; return division of last two digits
	sub ah, al ; substract to return the wright value
	movsx eax, ah ; move the result inside eax but keeping the sign bytes
	pop rbp ; pop the stack
	ret ; return 

section .note.GNU-stack noalloc noexec nowrite progbits ;use to silence some warning