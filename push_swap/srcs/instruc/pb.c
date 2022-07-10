/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pb.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:03:36 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/08 15:04:13 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/push_swap.h"

void	pb(t_stack **lst_a, t_stack **lst_b)
{
	t_stack	*temp;

	if (*lst_a)
	{
		temp = *lst_a;
		*lst_a = (*lst_a)->next;
		temp->next = *lst_b;
		*lst_b = temp;
	}
}