/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:55:45 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/30 10:58:38 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_max_nbr(t_stack *lst_a)
{
	t_stack	*temp;
	int		result;

	temp = lst_a;
	result = temp->nbr;
	while (temp)
	{
		if (temp->next != NULL && result < temp->next->nbr)
			result = temp->next->nbr;
		temp = temp->next;
	}
	return (result);
}

void	raddix_for_i(t_stack **lst_a, int index)
{
	t_stack	*temp;
	t_stack	*lst_b;
	int		i;

	lst_b = NULL;
	temp = *lst_a;
	i = lstsize(*lst_a);
	while (i != 0)
	{
		if (((temp->nbr >> index) & 1) == 1)
			ra(lst_a);
		else
			pb(lst_a, &lst_b);
		temp = *lst_a;
		i--;
	}
	while (lst_b)
		pa(lst_a, &lst_b);
	lstclear(&lst_b);
}

void	sort_big_list(t_stack **lst_a)
{
	int	max_bits;
	int	max_nbr;
	int	i;

	max_bits = 0;
	max_nbr = find_max_nbr(*lst_a);
	while (max_nbr >> max_bits != 0)
		max_bits++;
	i = 0;
	while (i < max_bits)
	{
		raddix_for_i(lst_a, i);
		i++;
	}
}
