/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_rotate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 19:48:48 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/28 14:47:00 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_stack **lst_a)
{
	t_stack	*temp;
	t_stack	*temp2;

	temp = *lst_a;
	while (temp->next->next)
	{
		if (temp->next->next == NULL)
			break ;
		temp = temp->next;
	}
	temp2 = temp->next;
	lstadd_front(lst_a, temp2);
	temp->next = NULL;
	ft_putstr_fd("rra\n", 1);
}

void	rrb(t_stack **lst_b)
{
	t_stack	*temp;
	t_stack	*temp2;

	temp = *lst_b;
	while (temp->next->next)
	{
		if (temp->next->next == NULL)
			break ;
		temp = temp->next;
	}
	temp2 = temp->next;
	lstadd_front(lst_b, temp2);
	temp->next = NULL;
	ft_putstr_fd("rrb\n", 1);
}

void	rrr(t_stack **lst_a, t_stack **lst_b)
{
	rra(lst_a);
	rrb(lst_b);
}
