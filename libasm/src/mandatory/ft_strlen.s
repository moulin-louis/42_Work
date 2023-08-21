section .text
	global ft_strlen ;export ft_strlen
ft_strlen: ;unsigned long[$rax] ft_strlen(const char *str[$rdi])
    mov eax, -1 ; set eax to -1
.loop:
    inc eax ; increment eax by one
    cmp BYTE [rdi], 0x0 ; compare the first byte of rdi with 0
    lea rdi, [rdi + 1] ; load the next byte of rdi
    jne .loop ; jump if the cmp was not equal to 0
    ret ; return

section .note.GNU-stack noalloc noexec nowrite progbits ;use to silence some warning