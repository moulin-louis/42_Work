/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:31:24 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/05 14:39:14 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

t_stack	*lstnew(int nbr)
{
	t_stack	*result;

	result = malloc(sizeof(t_stack));
	if (!result)
		return (NULL);
	result->nbr = nbr;
	result->next = NULL;
	return (result);
}

t_stack	*lstlast(t_stack *lst)
{
	if (lst->next == NULL)
		return (lst);
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	lstadd_back(t_stack **lst, t_stack *new)
{
	t_stack *temp;

	if (!*lst)
	{
		*lst = new;
	}
	else
	{
		temp = lstlast(*lst);
		temp->next = new;
	}
}
