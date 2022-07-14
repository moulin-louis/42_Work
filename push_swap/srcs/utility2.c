/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:31:24 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/14 14:20:04 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	lstclear(t_stack **lst)
{
	t_stack	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		free(*lst);
		*lst = temp;
	}
}

void	lstadd_front(t_stack **lst, t_stack *new)
{
	new->next = *lst;
	*lst = new;
}

int	lstsize(t_stack *lst)
{
	int		size;
	t_stack	*temp;

	temp = lst;
	size = 0;
	while (temp)
	{
		temp = temp->next;
		size++;
	}
	return (size);
}
