section .text
	global ft_atoi_base ;export ft_atoi_base
	extern ft_strlen
base_error: ; int[eax]		base_error(const char *base[rdi])
    push rdi
    call ft_strlen
    pop rdi
    ret
; PLEASE DONT TOUCH RDI AND RSI IN HERE

base_test: ;int[eax]     base_test(char c[dil], const char *base[rsi])
    xor eax, eax ; int i = 0
    push rsi
.start_loop:
    mov al, BYTE [rsi] ; base[i]
    cmp al, 0x0 ; while(base[i])
    je .end_bt ; end loop if base[i] = '\0'
    cmp dil, al ; check if base[i] == c
    je .char_found ; jump if its equal
    inc rsi
    jmp .start_loop ; start over
.char_found:
    mov rax, rsi
    pop rsi
    sub rax, rsi
    ret ; end fn with result in eax
.end_bt:
    mov rax, rsi
    pop rsi
    sub rax, rsi
    mov eax, -1 ; return value will be -1
    ret ; end fn
; PLEASE DONT TOUCH RDI AND RSI IN HERE

base_search: ;int[eax]		base_search(const char *str[rdi], int *i[rsi])
    push rdi
    mov r9d, 1
.start_loop_bs_1:
    mov ah, BYTE [rdi] ; load one byte of rdi
    cmp ah, 9 ; cmp ah with \t
    je .one_more ; jump if equal
    cmp ah, 10 ; cmp ah with \n
    je .one_more ; jump if equal
    cmp ah, 11 ; cmp ah with \v
    je .one_more ; jump if equal
    cmp ah, 12 ; cmp ah with \f
    je .one_more ; jump if equal
    cmp ah, 13 ; cmp ah with \r
    je .one_more ; jump if equal
    cmp ah, 32 ; cmp ah with char ' '
    je .one_more ; jump if equal
    jmp .start_loop_bs_2 ; jump if char is none of above
.one_more:
    inc rdi ; inc rdi by one
    jmp .start_loop_bs_1 ; start over loop
.start_loop_bs_2:
    mov ah, BYTE [rdi] ; load one byte of rdi
    cmp ah, 43 ; cmp ah with '+'
    je .plus_case_bs ; jump if equal
    cmp ah, 45 ; cmp ah with '-'
    je .minus_case_bs ; jump if equal
    jmp .end_loop_bs_2 ; jump if char is none of above
.plus_case_bs:
    inc rdi ; inc rdi by one (str++)
    jmp .start_loop_bs_2 ; start over the loop
.minus_case_bs:
    inc rdi ; inc rdi by one (str++)
    mov eax, -1 ; load -1 into eax
    mul r9d ; multiply r9d by eax so -1
    jmp .start_loop_bs_2 ; start over the loop
.end_loop_bs_2:
    mov rdx, rdi ; save rdi into rdx
    pop rdi ; restore of value of rdi
    sub rdx, rdi ; rdx = rdx - rdi
    add [rsi], rdx ; *i += rdx
    mov eax, r9d ; mov r9d to eax
    ret ; return value of mult sign inside eax

ft_atoi_base: ;int[rax] ft_atoi_base(const char *str[rdi], const char *base[rsi])
    push rbp ; save base stack pointer
    mov rbp, rsp ;update base pointer
    sub rsp, 5 * 4 ; allocate 5 * 32 bits to save 5 int
    mov r8, rdi ; save rsi into r8
    mov rdi, rsi ; move rdi into rsi
    call base_error ; call base_error
    mov rdi, r8 ; restore value of rsi
    mov DWORD [rsp], eax ; int len = base_error(base);
    cmp eax, 0x0 ; compare return value with 0
    jl .end_fn ; jump if less than 0
    mov DWORD [rsp+4], 0x0 ; int i = 0;
    mov r8, rsi ; save rsi inside r8
    mov rsi, rsp ; load value of rsp into rsi
    add rsi, 4 ; add 4 t rsi to have the address of i into rsi
    call base_search ; call base_search function
    mov DWORD [rsp+8], eax;int mult = base_search(str, &i);
    mov rsi, r8 ; restore value of rsi stored inside r8
    mov DWORD [rsp+12], 0x0 ; int nb = 0;
    mov r8, rdi ; save rdi into r8
    mov eax, DWORD [rsp+4] ; move value of rsp+4 into eax
    mov dil, BYTE [rdi+rax] ; load rdi + rax or str[i]
    call base_test ; call fn base_test
    mov rdi, r8 ; restore value of rdi
    cmp eax, -1 ; compare return value with -1
    je .end_fn ; jump if equal
    mov DWORD [rsp+16], eax ; int tmp = base_test(str[i], base);
    cmp DWORD [rsp+16], -1 ; cmp tmp with -1
    je .end_fn ; jump if equal

.end_fn:
    add rsp, 5 * 4 ; clean the stack
    pop rbp ;update base pointer to the old one saved
    mov eax, DWORD [rsp+8]
    mul DWORD [rsp+12]
    mov eax, DWORD [rsp+12]
	ret ; exiting the function

 section .note.GNU-stack noalloc noexec nowrite progbits ;use to silence some warning