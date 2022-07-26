/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 22:10:29 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/25 16:10:42 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	return (result);
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
	return (lst);
}
