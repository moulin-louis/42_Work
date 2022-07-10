/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:12:38 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/08 14:24:37 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/push_swap.h"

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
}