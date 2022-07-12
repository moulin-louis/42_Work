/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 19:39:24 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/12 16:46:45 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_stack **lst_a)
{
	t_stack	*temp;
	t_stack	*temp2;

	if (*lst_a == NULL || (*lst_a)->next == NULL)
		return ;
	else
	{
		temp = *lst_a;
		temp2 = (*lst_a)->next->next;
		*lst_a = (*lst_a)->next;
		(*lst_a)->next = temp;
		(*lst_a)->next->next = temp2;
	}
}

void	sb(t_stack **lst_b)
{
	t_stack	*temp;
	t_stack	*temp2;

	if (*lst_b == NULL || (*lst_b)->next == NULL)
		return ;
	else
	{
		temp = *lst_b;
		temp2 = (*lst_b)->next->next;
		*lst_b = (*lst_b)->next;
		(*lst_b)->next = temp;
		(*lst_b)->next->next = temp2;
	}
}

void	ss(t_stack **lst_a, t_stack **lst_b)
{
	sa(lst_a);
	sb(lst_b);
}
