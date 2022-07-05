/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:31:24 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/05 15:08:06 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"
#include <stdio.h>

void	ft_print_lst(t_stack *lst)
{
	t_stack *tmp;

	tmp = lst;
	while (tmp)
	{
		printf("%d ", tmp->nbr);
		tmp = tmp->next;
	}
	printf("\n");
}

int	main(int ac, char **av)
{
	t_stack *lst;

	if (ac < 2)
		return(-1);
	if (ft_check_arg(ac, av) == -1)
		return(-1);
	lst = init(av);
	if (lst == NULL)
		return (ft_putstr_fd("Error\n", 1), -1);
	ft_print_lst(lst);
	lstclear(&lst);
}
