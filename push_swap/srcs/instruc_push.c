/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 19:41:03 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/14 14:42:05 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_stack **lst_a, t_stack **lst_b)
{
	t_stack	*temp;

	if (*lst_b)
	{
		temp = *lst_b;
		*lst_b = (*lst_b)->next;
		temp->next = *lst_a;
		*lst_a = temp;
	}
	ft_putstr_fd("pa\n", 1);
}

void	pb(t_stack **lst_a, t_stack **lst_b)
{
	t_stack	*temp;

	if (*lst_a)
	{
		temp = *lst_a;
		*lst_a = (*lst_a)->next;
		temp->next = *lst_b;
		*lst_b = temp;
	}
	ft_putstr_fd("pb\n", 1);
}
