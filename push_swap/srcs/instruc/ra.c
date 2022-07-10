/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ra.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:07:07 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/08 15:13:25 by loumouli         ###   ########.fr       */
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