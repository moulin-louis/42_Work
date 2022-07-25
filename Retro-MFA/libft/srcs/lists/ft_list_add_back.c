/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_add_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 03:58:30 by user42            #+#    #+#             */
/*   Updated: 2022/05/26 16:07:25 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_lists.h"

void	ft_list_add_back(t_list *list, t_list_node *node)
{
	if (node == NULL || list == NULL)
		return ;
	if (*list == NULL)
	{
		*list = node;
		return ;
	}
	while ((*list)->next != NULL)
		(*list) = (*list)->next;
	(*list)->next = node;
}

void	ft_d_list_add_back(t_d_list *list, t_d_list_node *node)
{
	if (node == NULL || list == NULL)
		return ;
	if (*list == NULL)
	{
		*list = node;
		return ;
	}
	while ((*list)->next != NULL)
		(*list) = (*list)->next;
	(*list)->next = node;
	node->prev = *list;
}
