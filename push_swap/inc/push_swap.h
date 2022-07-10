/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 21:00:06 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/07 21:01:16 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct s_stack
{
	int				nbr;
	struct s_stack	*next;
}					t_stack;

typedef struct s_data
{
	t_stack	*lst_a;
	t_stack	*lst_b;

	t_stack	*end_lst_a;
	t_stack	*end_lst_b;

}					t_data;

t_stack	*lstnew(int nbr);
void	lstadd_back(t_stack **lst, t_stack *new);
t_stack	*lstlast(t_stack *lst);
void	lstclear(t_stack **lst);

t_stack	*init(char **av);
int		ft_check_arg(int ac, char **av);

void	sa(t_stack **lst_a);
void	sb(t_stack **lst_b);
void	ss(t_stack **lst_a, t_stack **lst_b);
#endif
