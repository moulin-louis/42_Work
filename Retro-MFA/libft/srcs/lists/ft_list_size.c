/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 03:58:57 by user42            #+#    #+#             */
/*   Updated: 2022/05/26 16:49:12 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_lists.h"

int	ft_list_size(t_list list)
{
	int		result;

	if (list == NULL)
		return (0);
	result = 1;
	while (list->next != NULL)
	{
		list = list->next;
		result++;
	}
	return (result);
}

int	ft_d_list_size(t_d_list list)
{
	int			result;
	t_d_list	tmp;

	if (list == NULL)
		return (0);
	result = 1;
	tmp = list;
	while (tmp->prev != NULL)
	{
		tmp = tmp->prev;
		result++;
	}
	while (list->next != NULL)
	{
		list = list->next;
		result++;
	}
	return (result);
}
