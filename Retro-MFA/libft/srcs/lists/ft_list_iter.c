/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_iter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 03:57:49 by user42            #+#    #+#             */
/*   Updated: 2022/05/26 16:32:02 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_lists.h"

void	ft_list_iter(t_list list, void (*function)(void *))
{
	if (list == NULL)
		return ;
	while (list->next != NULL)
	{
		(*function)(list->data);
		list = list->next;
	}
	(*function)(list->data);
}

void	ft_d_list_iter(t_d_list list, void (*function)(void *))
{
	if (list == NULL)
		return ;
	while (list->next != NULL)
	{
		(*function)(list->data);
		list = list->next;
	}
	(*function)(list->data);
}
