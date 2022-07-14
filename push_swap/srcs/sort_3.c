/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 14:24:08 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/14 15:26:20 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	choose_order(t_stack *lst)
{
	int	x;
	int	y;
	int	z;

	x = lst->nbr;
	y = lst->next->nbr;
	z = lst->next->next->nbr;
	if (x > y && x > z && y > z)
		return (1);
	else if (x > y && x > z && y < z)
		return (2);
	else if (x < y && x > z && y > z)
		return (3);
	else if (x > y && x < z && y < z)
		return (4);
	else if (x < y && x < z && y > z)
		return (5);
	return (0);
}

void	sort_3(t_stack **lst_a, int size)
{
	int	order;

	if (size == 2)
		sa(lst_a);
	else
	{
		order = choose_order(*lst_a);
		if (order == 1)
		{
			sa(lst_a);
			rra(lst_a);
		}
		else if (order == 2)
			ra(lst_a);
		else if (order == 3)
			rra(lst_a);
		else if (order == 4)
			sa(lst_a);
		else if (order == 5)
		{
			rra(lst_a);
			sa(lst_a);
		}
	}
}
