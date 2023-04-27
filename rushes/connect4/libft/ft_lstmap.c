/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:07:15 by marnaudy          #+#    #+#             */
/*   Updated: 2021/11/25 06:20:34 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_elem;

	if (lst)
		new_list = ft_lstnew((*f)(lst->content));
	if (!lst || !new_list)
		return (0);
	lst = lst->next;
	new_elem = new_list;
	while (lst)
	{
		new_elem->next = ft_lstnew((*f)(lst->content));
		if (!new_elem->next)
		{
			ft_lstclear(&new_list, (*del));
			return (new_list);
		}
		new_elem = new_elem->next;
		lst = lst->next;
	}
	return (new_list);
}
