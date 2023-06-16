section .text
	global ft_remove_if ;export ft_remove_if
ft_remove_if:
	push rbp ; push the stack
	mov rbp, rsp ; update the base stack ptr
	pop rbp ; pop the stack
	ret ; exiting the function

 section .note.GNU-stack noalloc noexec nowrite progbits ;use to silence some warning