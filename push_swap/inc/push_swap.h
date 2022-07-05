#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"



typedef struct s_stack
{
	int nbr;
	struct s_stack	*next;
}					t_stack;

t_stack	*lstnew(int nbr);
void	lstadd_back(t_stack **lst, t_stack *new);
t_stack	*lstlast(t_stack *lst);
void	lstclear(t_stack **lst);
t_stack	*init(char **av);
int	ft_check_arg(int ac, char **av);
#endif
