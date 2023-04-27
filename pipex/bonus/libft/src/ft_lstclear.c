/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:58:54 by loumouli          #+#    #+#             */
/*   Updated: 2022/05/11 15:22:25 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
}

/*
#include <stdio.h>

void	ft_del(void *content)
{
	*(char *)content = 0;
}

int	main(void)
{
	t_list	*test1;
	t_list	*test2;
	t_list	*test3;
	t_list	*test4;

	char	*str1 = ft_strdup("je test");
	char	*str2 = ft_strdup(" un truc");
	char	*str3 = ft_strdup(" vraiment");
	char	*str4 = ft_strdup(" long.");

	test1 = ft_lstnew(str1);
	test2 = ft_lstnew(str2);
	test3 = ft_lstnew(str3);
	test4 = ft_lstnew(str4);

	ft_lstadd_back(&test1, test2);
	ft_lstadd_back(&test2, test3);
	ft_lstadd_back(&test3, test4);

	printf("%s\n", (char *)ft_lstlast(test1)->content);
	ft_lstclear(&test1->next->next, ft_del);
	printf("%s\n", (char *)ft_lstlast(test1)->content);
} */
