;struct s_list {
;   void    *content;
;   s_list  *next;
;} t_list;
; push a new node containing data to the front of the linked list started by beg_list
section .text
	global ft_list_push_front ;export ft_list_push_front
	extern malloc
ft_list_push_front: ;void	ft_list_push_front(t_list **beg_list($rdi), void *data($rsi))
    push rdi
    push rsi
    mov edi, 0x10 ; load size with a value of 16
    call malloc wrt ..plt ; void *calloc(size_t nmenb, size_t size); alloc 1x16 so 16 octets
    pop r8 ; r8 = old value of rsi
    pop r9 ; r9 = old value of rdi
    mov QWORD [rax], r8 ; result->content = data;
    mov rdi, [r9] ; load the deref of head inside rdi
    mov QWORD [rax+8], rdi ; result->next = *head
    mov [r9], rax ; *head = result
	ret ; return

     section .note.GNU-stack noalloc noexec nowrite progbits ;use to silence some warning