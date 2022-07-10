/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 22:10:29 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/07 20:56:00 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"
#include "libft/libft.h"

t_stack	*init(char **av)
{
	int		x;
	t_stack	*lst;

	x = 2;
	lst = lstnew(ft_atoi(av[1]));
	if (!lst)
		return (NULL);
	while (av[x])
	{
		lstadd_back(&lst, lstnew(ft_atoi(av[x])));
		x++;
	}
	return (lst);
}
