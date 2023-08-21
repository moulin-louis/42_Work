;struct s_list {
;   void    *content;
;   s_list  *next;
;} t_list;
; return the size of the linked list starting from head
section .text
	global ft_list_size ;export ft_list_size
ft_list_size: ; unsigned int[$rax] ft_list_size(t_list *head[$rdi])
	xor eax, eax ; set eax to 0
	test rdi, rdi ; test if rdi is non-null
	je	.end_loop ; jump if null
.start_loop:
	mov rdi, QWORD [rdi+0x8] ; load the *next* value
	inc eax ; add one to the result
	test rdi, rdi ; test if rdi is non-null
	jne .start_loop ; jump back if non-null
.end_loop:
	ret ; end the loop
 section .note.GNU-stack noalloc noexec nowrite progbits ;use to silence some warning