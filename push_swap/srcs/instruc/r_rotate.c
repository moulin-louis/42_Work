/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_rotate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 19:48:48 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/11 19:49:37 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/push_swap.h"

void	rra(t_stack **lst_a)
{
	t_stack	*temp;
	t_stack	*temp2;

	temp = *lst_a;
	while (temp)
	{
		if (temp->next->next == NULL)
			break ;
		temp = temp->next;
	}
	temp2 = temp->next;
	temp->next = NULL;
	temp = *lst_a;
	*lst_a = temp2;
	(*lst_a)->next = temp;
}

void	rrb(t_stack **lst_b)
{
	t_stack	*temp;
	t_stack	*temp2;

	temp = *lst_b;
	while (temp)
	{
		if (temp->next->next == NULL)
			break ;
		temp = temp->next;
	}
	temp2 = temp->next;
	temp->next = NULL;
	temp = *lst_b;
	*lst_b = temp2;
	(*lst_b)->next = temp;
}

void	rrr(t_stack **lst_a, t_stack **lst_b)
{
	rra(lst_a);
	rrb(lst_b);
}