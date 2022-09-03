/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 22:10:29 by loumouli          #+#    #+#             */
/*   Updated: 2022/09/03 18:54:25 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_pos(t_stack *lst, int nbr)
{
	t_stack	*temp;
	int		result;

	temp = lst;
	result = 0;
	while (temp)
	{
		if (temp->nbr < nbr)
			result++;
		temp = temp->next;
	}
	return (result);
}

t_stack	*simplify_nbr(t_stack *lst)
{
	t_stack	*temp;
	t_stack	*result;

	temp = lst;
	result = lstnew(find_pos(lst, temp->nbr));
	if (result == NULL)
		return (lstclear(&result), NULL);
	temp = temp->next;
	while (temp)
	{
		lstadd_back(&result, lstnew(find_pos(lst, temp->nbr)));
		if (lstlast(lst) == NULL)
			return (lstclear(&result), NULL);
		temp = temp->next;
	}
	lstclear(&lst);
	return (result);
}

void	ft_destroy_split(char **av)
{
	int	x;

	x = -1;
	if (ft_strncmp(av[0], "place holder", ft_strlen(av[0])) != 0)
		return ;
	while (av[++x])
		free(av[x]);
	free(av);
}

int	ft_check_dbl_nbr(t_stack *lst)
{
	t_stack	*temp;
	int		x;

	while (lst)
	{
		temp = lst->next;
		x = lst->nbr;
		while (temp)
		{
			if (temp->nbr == x)
				return (1);
			temp = temp->next;
		}
		lst = lst->next;
	}
	return (0);
}

t_stack	*init( char **av)
{
	int		x;
	t_stack	*lst;
	long	temp;

	x = 1;
	temp = ft_atoi_no_overflow(av[1]);
	lst = lstnew(temp);
	if (!lst || temp == 9999999999)
		return (lstclear(&lst), NULL);
	while (av[++x])
	{
		temp = ft_atoi_no_overflow(av[x]);
		lstadd_back(&lst, lstnew(temp));
		if (lstlast(lst) == NULL || temp == 9999999999)
			return (lstclear(&lst), NULL);
	}
	if (ft_check_dbl_nbr(lst) == 1)
		return (lstclear(&lst), ft_putstr_fd("nbr multiple time\n", 1), NULL);
	lst = simplify_nbr(lst);
	if (lst == NULL)
		return (lstclear(&lst), NULL);
	ft_destroy_split(av);
	return (lst);
}
