section .text
	global ft_list_sort ;export ft_list_sort
ft_list_sort: ; void ft_list_sort(t_list **head($rdi), int(*cmp)($rsi))
    push rbp ; save base stack pointer
    mov rbp, rsp ;update base pointer
    sub rsp, 32 ; allocate 24 bytes for local variables
    test rdi, rdi ; test if rdi is non-null
	je	.end_fn ; jump if null
    test rsi, rsi ; test if rsi is non-null
	je	.end_fn ; jump if null
    mov QWORD [rsp], rdi ;  t_list **save = head;
    mov rdi, QWORD [rdi] ; deref head
    test rdi, rdi
    je .end_fn
    mov QWORD [rsp + 8], rdi ; t_list *head_save = *head
    mov QWORD [rsp + 16], 0x0 ; uint64_t data = 0
    mov QWORD [rsp + 24], rsi ; save cmp into the stack
.start_loop:
    mov rdi, QWORD [rsp] ; load head
    mov rdi, QWORD [rdi] ; deref head
    mov rdi, QWORD [rdi + 8] ; load value of (*head)->next
    cmp rdi, 0x0 ; check if null
    jle .end_loop ; jump if null
    mov rdi, QWORD [rsp] ; load head
    mov rdi, QWORD [rdi] ; deref head
    mov rdi, QWORD [rdi]
    mov rsi, QWORD [rsp] ; load head
    mov rsi, QWORD [rsi] ; deref head
    mov rsi, QWORD [rsi + 8] ; load value of (*head)->next->value
    mov rsi, QWORD [rsi]
    call QWORD [rsp + 24] ; call cmp((*head)->data, (*head)->next->data)
    cmp eax, 0 ; compare rax with 0
    jg .swap_data ; jump if cmp return value above 0
    mov rdi, QWORD [rsp] ; load head
    mov rsi, QWORD [rsp] ; load head
    mov rsi, QWORD [rsi]
    mov rsi, QWORD [rsi+8]
    mov QWORD [rdi], rsi ; *head = (*head)->next
    jmp .start_loop ; start over the loop
.swap_data:
    ; 1/4
    mov rdi, QWORD [rsp] ; load head
    mov rdi, QWORD [rdi] ; deref head
    mov rdi, QWORD [rdi] ; load value of (*head)->data
    mov QWORD [rsp + 16], rdi ; data = (*head)->data
    ; 2/4
    mov rdi, QWORD [rsp] ; load head
    mov rdi, QWORD [rdi] ; deref head
    mov rsi, QWORD [rsp]
    mov rsi, QWORD [rsi]
    mov rsi, QWORD [rsi+8]
    mov rsi, QWORD [rsi]
    mov QWORD [rdi], rsi
    ; 3/4
    mov rdi, QWORD [rsp] ; load head
    mov rdi, QWORD [rdi] ; deref head
    mov rdi, QWORD [rdi+8]
    mov rsi, QWORD [rsp + 16] ; load value of data
    mov QWORD [rdi], rsi ; (*head)->next->data = data;
    ; 4/4
    mov rdi, QWORD [rsp] ; load head
    mov rsi, QWORD [rsp + 8] ; load head_save
    mov QWORD [rdi], rsi ; *head = head_save
    jmp .start_loop ; start over the loop
.end_loop:
    mov rdi, QWORD [rsp] ; load head
    mov rsi, QWORD [rsp + 8] ; load head_save
    mov QWORD [rdi], rsi ; *head = head_save
.end_fn:
    add rsp, 32 ; clean the stack
    pop rbp ;update base pointer to the old one saved
	ret ; exiting the function

 section .note.GNU-stack noalloc noexec nowrite progbits ;use to silence some warning
