/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rra.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:33:19 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/08 20:39:45 by loumouli         ###   ########.fr       */
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