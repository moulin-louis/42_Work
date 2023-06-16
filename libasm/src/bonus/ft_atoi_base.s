section .text
	global ft_atoi_base ;export ft_atoi_base
ft_atoi_base: 
	push rbp ; push the stack
	mov rbp, rsp ; update the base stack ptr
	pop rbp ; pop the stack
	ret ; exiting the function

 section .note.GNU-stack noalloc noexec nowrite progbits ;use to silence some warning