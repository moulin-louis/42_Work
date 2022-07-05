#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
#include <stdlib.h>

typedef struct s_stack
{
	int nbr;
	struct s_stack	*next;
}					t_stack;

int	ft_atoi(char *nptr);
t_stack *ft_lstnew(int nbr);
void    ft_lstadd_back(t_stack **lst, t_stack *new);
t_stack *ft_lstlast(t_stack *lst);
void    ft_lstclear(t_stack **lst);
void    ft_putstr(char *str);
t_stack *ft_init(char **av);
#endif