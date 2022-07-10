/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sb.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:56:23 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/07 20:58:21 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/push_swap.h"

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
