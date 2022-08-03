/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_4_5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 09:31:51 by loumouli          #+#    #+#             */
/*   Updated: 2022/08/03 19:02:30 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_min_pos(t_stack **lst_a)
{
	t_stack	*temp;
	int		result;
	int		min_nbr;

	temp = *lst_a;
	result = 0;
	min_nbr = temp->nbr;
	while (temp)
	{
		if (min_nbr > temp->nbr)
			min_nbr = temp->nbr;
		temp = temp->next;
	}
	temp = *lst_a;
	while (temp)
	{
		if (temp->nbr == min_nbr)
		{
			result++;
			break ;
		}
		result++;
		temp = temp->next;
	}	
	return (result);
}

void	push_min_5(t_stack **lst_a, t_stack **lst_b)
{
	int	pos_min_nbr;

	pos_min_nbr = find_min_pos(lst_a);
	if (pos_min_nbr == lstsize(*lst_a))
		rra(lst_a);
	else if (pos_min_nbr == lstsize(*lst_a) - 1)
	{
		rra(lst_a);
		rra(lst_a);
	}
	else if (pos_min_nbr <= 3)
	{
		while (pos_min_nbr > 1)
		{
			ra(lst_a);
			pos_min_nbr--;
		}
	}
	pb(lst_a, lst_b);
}

void	push_min_4(t_stack **lst_a, t_stack **lst_b)
{
	int	pos_min_nbr;

	pos_min_nbr = find_min_pos(lst_a);
	if (pos_min_nbr == lstsize(*lst_a))
		rra(lst_a);
	else if (pos_min_nbr == 2)
		ra(lst_a);
	else if (pos_min_nbr == 3)
	{
		rra(lst_a);
		rra(lst_a);
	}
	pb(lst_a, lst_b);
}

void	sort_4(t_stack **lst_a)
{
	t_stack	*lst_b;

	lst_b = NULL;
	push_min_4(lst_a, &lst_b);
	push_min_4(lst_a, &lst_b);
	sort_3(lst_a, 2);
	pa(lst_a, &lst_b);
	pa(lst_a, &lst_b);
}

void	sort_5(t_stack **lst_a)
{
	t_stack	*lst_b;

	lst_b = NULL;
	push_min_5(lst_a, &lst_b);
	push_min_5(lst_a, &lst_b);
	sort_3(lst_a, lstsize(*lst_a));
	pa(lst_a, &lst_b);
	pa(lst_a, &lst_b);
}
