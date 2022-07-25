/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_add_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 03:58:21 by user42            #+#    #+#             */
/*   Updated: 2022/05/26 16:20:48 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_lists.h"

void	ft_list_add_front(t_list *list, t_list_node *node)
{
	if (list == NULL || node == NULL)
		return ;
	node->next = *list;
	*list = node;
}

void	ft_d_list_add_front(t_d_list *list, t_d_list_node *node)
{
	if (list == NULL || node == NULL)
		return ;
	node->next = *list;
	node->next->prev = node;
	*list = node;
}
