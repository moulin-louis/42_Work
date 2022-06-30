#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include "../lib/ft_printf/inc/ft_printf.h"
# include "../lib/libft/libft.h"

typedef struct s_stack
{
	int nbr;
	struct s_stack	*next;
}					t_stack;

#endif