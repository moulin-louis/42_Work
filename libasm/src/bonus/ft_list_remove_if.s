section .text
	global ft_list_remove_if ;export ft_remove_if
    extern free
ft_list_remove_if: ; void ft_list_remove_if(t_list **begin_list[rdi], void *data_ref[rsi], int (*cmp)()[rdx], void (*free_fct)(void *)[rcx])
    push rbp ; save base stack pointer
    mov rbp, rsp ;update base pointer
    push rbx
    sub rsp, 8 * 6 ; allocate 3 * 8 bytes to save 3 64 bits pointer
    test rdi, rdi
    je .end_loop
    test rdx, rdx
    je .end_loop
    test rcx, rcx
    je .end_loop
    mov rbx, rdi
    mov rdi, QWORD [rdi] ; deref begin_list
    test rdi, rdi
    je .end_loop
    mov QWORD [rsp], rdi ; t_list *node = *begin_List
    mov QWORD [rsp + 8], 0x0 ; t_list *prev = NULL
    mov QWORD [rsp + 16], rbx ; save begin_list
    mov QWORD [rsp + 24], rsi ; save data_ref
    mov QWORD [rsp + 32], rdx ; save cmp fn
    mov QWORD [rsp + 40], rcx ; save free_fct fn
.start_loop_1:
    mov rdi, QWORD [rsp + 16]
    mov rdi, QWORD [rdi]
    mov QWORD [rsp], rdi
    mov QWORD [rsp + 8], 0x0
.start_loop_2:
    cmp QWORD [rsp], 0x0
    je .end_loop_1
    mov rdi, QWORD [rsp] ; load node
    mov rdi, QWORD [rdi] ; load node->content
    mov rsi, QWORD [rsp + 24] ; load data_ref
    call QWORD [rsp + 32] ; call cmp, data_ref is already on rsi
    cmp eax, 0x0 ; compare int return value with 0
    jne .end_loop_2
    cmp QWORD [rsp + 8], 0x0 ; check if prev is null
    je .prev_null ; jump if its is
    mov rdi, QWORD [rsp] ; load node
    mov rdi, QWORD [rdi+8] ; load value of node->next
    mov rsi, QWORD [rsp + 8] ; load prev
    mov QWORD [rsi + 8], rdi ; prev->next = node->next
    mov rdi, QWORD [rsp] ; load node
    mov rdi, QWORD [rdi] ; load value of node->content
    call QWORD [rsp + 40] ; call free_fct on node->content
    mov rdi, QWORD [rsp] ; load node
    call free wrt ..plt
    jmp .end_loop_1
.prev_null:
    mov rax, QWORD [rsp + 16] ; load begin_list
    mov rbx, QWORD [rsp] ; load node
    mov rbx, QWORD [rbx + 8] ; load value of node->next
    mov QWORD [rax], rbx ; *begin_list = node->next
    mov rdi, QWORD [rsp] ; load node
    mov rdi, QWORD [rdi] ; load node->content
    call QWORD [rsp + 40] ; call free_fct on node->content
    mov rdi, QWORD [rsp] ; load node
    call free wrt ..plt
    jmp .end_loop_1
.end_loop_2:
    mov rax, QWORD [rsp] ; load node
    mov QWORD [rsp + 8], rax ; prev = node
    mov rbx, QWORD [rax+8] ; load node->next
    mov QWORD [rsp], rbx ; node = node->next
    jmp .start_loop_2
.end_loop_1:
    cmp QWORD [rsp], 0x0
    jne .start_loop_1
.end_loop:
    add rsp, 8 * 6 ;clean the stack
    pop rbx
    pop rbp ;update base pointer to the old one saved
    ret ; end the loop
