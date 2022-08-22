/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 22:10:29 by loumouli          #+#    #+#             */
/*   Updated: 2022/08/22 20:18:37 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	find_pos(t_stack *lst, int nbr)
{
	t_stack	*temp;
	int		result;

	temp = lst;
	result = 0;
	while (temp)
	{
		if (temp->nbr < nbr)
			result++;
		temp = temp->next;
	}
	return (result);
}

t_stack	*simplify_nbr(t_stack *lst)
{
	t_stack	*temp;
	t_stack	*result;

	temp = lst;
	result = lstnew(find_pos(lst, temp->nbr));
	temp = temp->next;
	while (temp)
	{
		lstadd_back(&result, lstnew(find_pos(lst, temp->nbr)));
		temp = temp->next;
	}
	lstclear(&lst);
	return (result);
}

void	ft_destroy_split(char **av)
{
	int	x;

	x = 1;
	while (av[x])
	{
		// ft_putstr_fd("x = ", 1);
		// ft_putnbr_fd(x, 1);
		// ft_putstr_fd("\n", 1);
		free(av[x]);
		x++;
	}
	free(av);
}

t_stack	*init( char **av)
{
	int		x;
	t_stack	*lst;

	x = 2;
	lst = lstnew(ft_atoi(av[1]));
	if (!lst)
		return (NULL);
	while (av[x])
	{
		lstadd_back(&lst, lstnew(ft_atoi(av[x])));
		x++;
	}
	lst = simplify_nbr(lst);
	if (ft_strncmp(av[0], "place holder", ft_strlen(av[0])) == 0)
	{
		ft_destroy_split(av);
	}
	return (lst);
}
