/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 03:57:57 by user42            #+#    #+#             */
/*   Updated: 2022/05/26 17:28:44 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_lists.h"

t_list	ft_list_map(t_list list, void *(*function)(void *),
void (*destructor)(void *))
{
	t_list		result;
	t_list_node	*new_node;

	if (list == NULL)
		return (NULL);
	result = ft_malloc_node((*function)(list->data));
	if (result == NULL)
		return (NULL);
	list = list->next;
	while (list != NULL)
	{
		new_node = ft_malloc_node((*function)(list->data));
		if (new_node == NULL)
		{
			ft_list_clear(&result, destructor);
			return (NULL);
		}
		ft_list_add_back(&result, new_node);
		list = list->next;
	}
	return (result);
}

t_d_list	ft_d_list_map(t_d_list list, void *(*function)(void *),
void (*destructor)(void *))
{
	t_d_list		result;
	t_d_list_node	*new_node;

	if (list == NULL)
		return (NULL);
	result = ft_malloc_d_node((*function)(list->data));
	if (result == NULL)
		return (NULL);
	list = list->next;
	while (list != NULL)
	{
		new_node = ft_malloc_d_node((*function)(list->data));
		if (new_node == NULL)
		{
			ft_d_list_clear(&result, destructor);
			return (NULL);
		}
		ft_d_list_add_back(&result, new_node);
		list = list->next;
	}
	return (result);
}
