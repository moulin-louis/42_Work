section .text
	global ft_list_size ;export ft_list_size
ft_list_size:
	push rbp ; push the stack
	mov rbp, rsp ; update the base stack ptr
	pop rbp ; pop the stack
	ret ; exiting the function

 section .note.GNU-stack noalloc noexec nowrite progbits ;use to silence some warning