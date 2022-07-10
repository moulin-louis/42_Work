/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:31:24 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/07 20:56:29 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"
#include <stdio.h>

void	ft_print_lst(t_stack *lst)
{
	t_stack	*tmp;

	tmp = lst;
	while (tmp)
	{
		printf("%d ", tmp->nbr);
		tmp = tmp->next;
	}
	printf("\n");
}

int	ft_check_list(t_stack *lst)
{
	t_stack	*temp;

	temp = lst;
	while (temp)
	{
		if (temp->next != NULL && temp->nbr > temp->next->nbr)
			return (0);
		temp = temp->next;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 2)
		return (-1);
	if (ft_check_arg(ac, av) == -1)
		return (-1);
	lst_a = init(av);
	if (lst_a == NULL)
		return (ft_putstr_fd("Error\n", 1), -1);
	if (ft_check_list(lst_a) == 1)
		return (ft_putstr_fd("args already list\n", 1), -1);
	ft_print_lst(lst_a);
	sa(&lst_a);
	ft_print_lst(lst_a);
	lstclear(&lst_a);
}
