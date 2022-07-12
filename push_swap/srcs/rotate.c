/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 19:45:18 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/12 16:25:49 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void	ra(t_stack **lst_a)
{
	t_stack	*temp;

	temp = *lst_a;
	*lst_a = (*lst_a)->next;
	lstadd_back(lst_a, temp);
	temp->next = NULL;
}

void	rb(t_stack **lst_b)
{
	t_stack	*temp;

	temp = *lst_b;
	*lst_b = (*lst_b)->next;
	lstadd_back(lst_b, temp);
	temp->next = NULL;
}

void	rr(t_stack **lst_a, t_stack **lst_b)
{
	ra(lst_a);
	rb(lst_b);
}
