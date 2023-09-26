section .text
	global ft_atoi_base ;export ft_atoi_base
	extern ft_strlen ; import libasm ft_strlen implementation

base_error_1: ; int[eax]		base_error_1(const char *base[rdi])
    xor eax, eax ; set eax to 0
.tmp_1:
    mov sil, BYTE [rdi+rax] ; load base[rax] to sil
    mov ecx, eax ; mov eax to ecx
    mov r8d, eax ; mov eax to r8d
    test sil, sil ; test sil
    je .tmp_4 ; jump if 0
    or rdx, 0xffffffffffffffff ; rdx = -1
    dec ecx ; decrement ecx by one
.tmp_2:
    mov r8b, BYTE [rdi+rdx+1] ; load base[rdx+1] to r8b
    test r8b, r8b ; test r8b
    je .tmp_3 ; jump if r8b == 0
    cmp ecx, edx ; compare ecx and edx
    setne r9b ; set r9b to 1 if ecx != edx
    cmp r8b, sil ; compare r8b to sil
    sete r8b ; set r8b to 1 if r8b == sil
    inc rdx ; increment rdx by one
    test r9b, r8b ; r9b AND r8b
    je .tmp_2 ; jump if (r9b AND r8b) == 0
    xor r8d, r8d ; r8d = 0
    jmp .tmp_4 ; jump
.tmp_3:
    inc rax ; increment rax by one
    jmp .tmp_1 ; start over
.tmp_4:
    mov eax, r8d ; mov r8d inside eax
    ret ; return

base_error_2: ; int[eax]		base_error_2(const char *base[rdi])
    call ft_strlen ; call ft_strlen on base
    push rdi ; save rdi into the stack
.start_loop_error:
    mov ah, BYTE [rdi] ; load one byte of rdi
    cmp ah, 0x0
    je .end_loop_error
    cmp ah, 9 ; cmp ah with \t
    je .error_found
    cmp ah, 10 ; cmp ah with \n
    je .error_found
    cmp ah, 11 ; cmp ah with \v
    je .error_found
    cmp ah, 12 ; cmp ah with \f
    je .error_found
    cmp ah, 13 ; cmp ah with \r
    je .error_found
    cmp ah, 32 ; cmp ah with char ' '
    je .error_found
    cmp ah, 43 ; cmp ah with char '+'
    je .error_found
    cmp ah, 45 ; cmp ah with char '-'
    je .error_found
    inc rdi ; increment rdi ptr
    jmp .start_loop_error
.error_found:
    pop rdi ; restore rdi old value
    mov eax, -1 ; return value is -1
    ret ; end fn
.end_loop_error:
    pop rdi ; restore rdi old value
    ret ; return return value of ft_strlen
    ; WIP, NEED TO CHECK FOR BASE ERROR

base_test: ;int[eax]     base_test(char c[dil], const char *base[rsi])
    xor eax, eax ; int i = 0
    push rsi ; save rsi into the stack
.start_loop:
    mov al, BYTE [rsi] ; base[i]
    cmp al, 0x0 ; while(base[i])
    je .end_bt ; end loop if base[i] = '\0'
    cmp dil, al ; check if base[i] == c
    je .char_found ; jump if its equal
    inc rsi ; increment rsi
    jmp .start_loop ; start over
.char_found:
    mov rax, rsi ; save rsi to rax
    pop rsi ; restore rsi old value
    sub rax, rsi ; check the diff between rax and rsi
    ret ; end fn with result in eax
.end_bt:
    pop rsi ; restore rsi old value
    mov eax, -1 ; return value will be -1
    ret ; end fn

base_search: ;int[eax]		base_search(const char *str[rdi], int *i[rsi])
    push rdi
    mov r9d, 0
.start_loop_bs_1: ; increment while whitespace
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
.start_loop_bs_2: ; increment while '+' or '-'
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
    inc r9d ; increment number of - by 1
    jmp .start_loop_bs_2 ; start over the loop
.end_loop_bs_2:
    mov rdx, rdi ; save rdi into rdx
    pop rdi ; restore of value of rdi
    sub rdx, rdi ; offset = rdx - rdi
    add DWORD [rsi], edx ; *i += offset
    and r9d, 1 ; AND bitwise r9d with 1 == check odd/even nbr of '-' char
    cmp r9d, 1 ; if r9d == 1 its odd else its even
    je .odd_case ; jump to odd case
    mov eax, 1
    ret ; return value of mult sign inside eax
.odd_case:
    mov eax, -1 ; need to multiply final result with -1
    ret ; return value of mult sign inside eax

ft_atoi_base: ;int[rax] ft_atoi_base(const char *str[rdi], const char *base[rsi])
    push rbp ; save base stack pointer
    mov rbp, rsp ;update base pointer
    sub rsp, 32 ; allocate enough space for 5 int
    cmp rdi, 0x0
    je .error_handling
    cmp rsi, 0x0
    je .error_handling
    push rdi
    push rsi
    mov rdi, rsi ; move rsi into rdi
    call base_error_1 ; call base_error_1
    pop rsi
    pop rdi
    cmp eax, 1 ; compare return value with 0
    jl .error_handling ; jump if less than 0
    mov r8, rdi ; save rdi into r8
    mov rdi, rsi ; move rsi into rdi
    call base_error_2 ; call base_error_2
    mov rdi, r8 ; restore value of rdi
    cmp eax, 2 ; compare return value with 2
    jl .error_handling ; jump if less than 2, check base_error_2 (eax == -1) and length base (eax < 2)
    mov DWORD [rsp], eax ; int len = return value of base_error_2(base);
    mov DWORD [rsp+4], 0x0 ; int i = 0;
    mov r8, rsi ; save rsi inside r8
    mov rsi, rsp ; load value of rsp into rsi
    add rsi, 4 ; load address of i located at rsp + 4
    call base_search ; call base_search function
    mov DWORD [rsp+8], eax;int mult = return value of base_search(str, &i);
    mov rsi, r8 ; restore value of rsi stored inside r8
    mov DWORD [rsp+12], 0x0 ; int nb = 0;
    mov r8, rdi ; save rdi into r8
    mov eax, DWORD [rsp+4] ; move value pointed by rsp+4 into eax
    mov dil, BYTE [rdi+rax] ; load rdi + rax == str[i]
    call base_test ; call fn base_test
    mov DWORD [rsp+16], eax ; tmp = return value of base_test(str[i], base);
    mov rdi, r8 ; restore value of rdi
.start_loop_final:
    cmp eax, -1 ; compare return value with -1
    je .end_fn ; jump if equal
    mov eax, DWORD [rsp+12] ; load value of nb
    mov r9d, DWORD [rsp] ; load len
    mul r9d ; multiply nb by len
    add eax, DWORD [rsp+16] ; add tmp to nb
    mov DWORD [rsp+12], eax ; save result
    mov eax, DWORD [rsp+4] ; move value pointed by rsp+4 into eax
    inc eax ; increment i
    mov DWORD [rsp+4], eax ; save result
    mov r8, rdi ; save rdi into r8
    mov dil, BYTE [rdi+rax] ; load rdi + rax == str[i]
    call base_test ; call fn base_test
    mov DWORD [rsp+16], eax ; tmp = return value of base_test(str[i], base);
    mov rdi, r8 ; restore rdi ptr
    jmp .start_loop_final
.end_fn:
    mov r9d, DWORD [rsp+8] ; load sign of result
    mov eax, DWORD [rsp+12] ; load nb
    mul r9d ; mult result by sign
    add rsp, 32 ; clean the stack
    pop rbp ;update base pointer to the old one saved
	ret ; exiting the function
.error_handling:
    mov eax, 0
    add rsp, 32 ; clean the stack
    pop rbp ;update base pointer to the old one saved
    ret
 section .note.GNU-stack noalloc noexec nowrite progbits ;use to silence some warning