/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 22:10:29 by loumouli          #+#    #+#             */
/*   Updated: 2022/08/25 17:26:55 by loumouli         ###   ########.fr       */
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

	x = -1;
	if (ft_strncmp(av[0], "place holder", ft_strlen(av[0])) != 0)
		return ;
	while (av[++x])
		free(av[x]);
	free(av);
}

t_stack	*init( char **av)
{
	int		x;
	t_stack	*lst;
	long long temp;

	x = 2;
	temp = ft_atoi_no_overflow(av[1]);
	if (temp == 9999999999)
		return	(ft_putstr_fd("Over/underflow", 1), NULL);
	lst = lstnew(temp);
	if (!lst)
		return (ft_putstr_fd("Error lstnew", 1), NULL);
	while (av[x])
	{
		temp = ft_atoi(av[x]);
		if (temp == 9999999999)
			return	(ft_putstr_fd("Over/underflow", 1), NULL);
		lstadd_back(&lst, lstnew(ft_atoi_no_overflow(av[x])));
		if (lstlast(lst) == NULL)
		{
			lstclear(&lst);
			return (ft_putstr_fd("Error on creating linked list\n", 1), NULL);
		}
		x++;
	}
	lst = simplify_nbr(lst);
	ft_destroy_split(av);
	return (lst);
}
