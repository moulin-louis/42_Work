/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 19:45:18 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/11 19:48:16 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/push_swap.h"

void	ra(t_stack **lst_a)
{
	t_stack	*temp;
	t_stack *temp_ptr;

	temp = *lst_a;
	*lst_a = (*lst_a)->next;
	temp_ptr = *lst_a;
	while(temp_ptr)
	{
		if (temp_ptr->next == NULL)
				break ;
		temp_ptr = temp_ptr->next;
	}
	temp_ptr->next = temp;
}

void	rb(t_stack **lst_b)
{
	t_stack	*temp;
	t_stack *temp_ptr;

	temp = *lst_b;
	*lst_b = (*lst_b)->next;
	temp_ptr = *lst_b;
	while(temp_ptr)
	{
		if (temp_ptr->next == NULL)
				break ;
		temp_ptr = temp_ptr->next;
	}
	temp_ptr->next = temp;
}

void	rr(t_stack **lst_a, t_stack **lst_b)
{
	ra(lst_a);
	rb(lst_b);
}
