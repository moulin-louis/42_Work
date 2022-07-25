/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 03:58:39 by user42            #+#    #+#             */
/*   Updated: 2022/05/26 16:31:56 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_lists.h"

void	ft_list_clear(t_list *list, void (*destructor)(void*))
{
	t_list	tmp;

	if (*list == NULL)
		return ;
	while (*list != NULL)
	{
		tmp = *list;
		(*destructor)(tmp->data);
		*list = tmp->next;
		free(tmp);
	}
}

void	ft_d_list_clear(t_d_list *list, void (*destructor)(void*))
{
	t_d_list	tmp;

	if (*list == NULL)
		return ;
	while (*list != NULL)
	{
		tmp = *list;
		(*destructor)(tmp->data);
		*list = tmp->next;
		free(tmp);
	}
}
