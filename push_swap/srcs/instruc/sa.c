/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sa.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:01:08 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/07 20:59:28 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/push_swap.h"

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
