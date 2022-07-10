/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:56:50 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/08 15:57:22 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/push_swap.h"

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