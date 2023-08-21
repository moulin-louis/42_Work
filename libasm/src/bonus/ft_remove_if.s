;struct s_list {
;   void    *content;
;   s_list  *next;
;} t_list;
; Clean node based of cmp function return value using free_fct
section .text
	global ft_remove_if ;export ft_remove_if
ft_remove_if: ; void ft_list_remove_if(t_list **begin_list[rdi], void *data_ref[rsi], int (*cmp)()[rdx], void (*free_fct)(void *)[rcx])
    push rbp ; save base stack pointer
    mov rbp, rsp ;update base pointer
    sub rsp, 8 * 6 ; allocate 6 * 8 bytes to save 6 64 bits pointer
    cmp rdi, 0x0
    je .end_loop
    mov [rsp], rdi ; head save in the stack
    mov [rsp+8], rsi ; data_ref save in the stack
    mov [rsp+16], rdx ; cmp save in the stack
    mov [rsp+24], rcx ; free_fct save in the stack
    mov rdi, [rdi] ; load *head
    mov [rsp+32], rdi ; t_list *tmp; tmp = *head;
    mov QWORD [rsp+40], 0 ; t_list *prev; prev = NULL;
.start_loop:
    cmp QWORD [rsp+32], 0x0 ; compare tmp with NULL
    je .end_loop ; jump if equal
    mov rdi, QWORD [rsp+32] ; load tmp->content
    mov rdi, [rdi]
    mov rsi, QWORD [rsp+8] ; load data_ref
    mov rax, QWORD [rsp+16] ; load cmp fn
    call rax ; call cmp
    cmp rax, 0x0 ; check return value if 0
    jne .data_not_equal ; jump if return value is not equal to 0
    mov rax, QWORD [rsp+40] ; load prev
    cmp rax, 0x0 ; check if prev is null
    je .first_node ; jump if its null
    ;prev->next = tmp->next
    mov rax, QWORD [rsp+40] ; load prev into rax
    add rax, 8 ; load prev->next
    mov rdi, QWORD [rsp+32] ; load tmp into rdi
    add rdi, 8 ; load tmp->next
    mov rdi, [rdi] ; load value of tmp->next
    mov [rax], rdi ;prev->next = tmp->next, write rdi value inside memory location stored inside rax
    mov rdi, QWORD [rsp+32] ; load tmp into rdi
    ;free_fct(tmp)
    call QWORD [rsp+24] ; call free_fct on tmp loaded in rdi
    ;tmp = prev->next
    mov rax, QWORD [rsp+40] ; load prev into rax
    mov rax, [rax+8] ; load prev->next into rax
    mov QWORD [rsp+32], rax
    jmp .start_loop ; start over the loop
.first_node:
    ;*head = tmp->next
    mov rax, QWORD [rsp] ; load head into rax
    mov rdi, QWORD [rsp+32] ; load tmp into rdi
;    add rdi, 8
    mov rdi, QWORD [rdi + 8]
    mov QWORD [rax], rdi ; *head = tmp->next
    ;free_fct(tmp)
    mov rdi, QWORD [rsp+32] ; load tmp into rdi
    call QWORD [rsp+24] ;call free_fct
    ;tmp = *head
    mov rax, QWORD [rsp] ; load head into rax
    mov rax, QWORD [rax] ; load *head into rax
    mov QWORD [rsp+32], rax ; tmp = *head
    jmp .start_loop ; start over the loop
.data_not_equal:
    ;prev = tmp
    mov rax, QWORD [rsp+32] ; load tmp into rax
    mov QWORD [rsp+40], rax ; prev = tmp
    ;tmp = tmp->next
    mov rax, [rax+8] ; load tmp->next
    mov QWORD [rsp+32], rax ; tmp = tmp->next
    jmp .start_loop ; start over the loop
.end_loop:
    add rsp, 8 * 6 ;clean the stack
    pop rbp ;update base pointer to the old one saved
    ret ; end the loop

 section .note.GNU-stack noalloc noexec nowrite progbits ;use to silence some warning