/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:06:47 by loumouli          #+#    #+#             */
/*   Updated: 2022/05/11 14:53:06 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	flibft_t_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*temp;

	if (!*lst)
		*lst = new_node;
	else
	{
		temp = libft_ft_lstlast(*lst);
		temp->next = new_node;
	}
}
