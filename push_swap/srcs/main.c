/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:31:24 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/12 15:02:40 by loumouli         ###   ########.fr       */
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


int	main(void)
{
	t_stack *lst_a;
	t_stack	*lst_b;

	lst_b = malloc(sizeof(t_stack));
	
	lstadd_back(&lst_a, lstnew(5));
	lstadd_back(&lst_a, lstnew(3));
	lstadd_back(&lst_a, lstnew(2));
	lstadd_back(&lst_a, lstnew(4));
	lstadd_back(&lst_a, lstnew(1));

	
	rra(&lst_a); //1 5 3 2 4 | NULL
	ft_print_lst(lst_a);
	sleep(3);
	
	pb(&lst_a, &lst_b); // 5 3 2 4 | 1
	ft_print_lst(lst_a);
	sleep(3);
	



	ft_print_lst(lst_a);
	sleep(3);
	
	sa(&lst_a); // 2 3 4 5 | 1f
	ft_print_lst(lst_a);
	sleep(3);
	
	pb(&lst_a, &lst_b); // 1 2 3 4 5 | NULL
	ft_print_lst(lst_a);
	sleep(3);
	
	ft_print_lst(lst_a);
	ft_print_lst(lst_a);
	sleep(3);
	
}

/*int	main(int ac, char **av)
{
	t_stack	*lst_a;

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
}*/
