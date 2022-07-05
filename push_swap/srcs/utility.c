/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:31:24 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/04 22:16:17 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

int	ft_atoi(char *nptr)
{
	int		i;
	int		minus;
	long	result;

	i = 0;
	minus = 1;
	result = 0;
	if (nptr[i] == '-')
		minus = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	result = result * minus;
	return ((int)result);
}

t_stack *ft_lstnew(int nbr)
{
    t_stack *result;
    
    result = malloc(sizeof(t_stack));
    if (!result)
        return (NULL);
    result->nbr = nbr;
    result->next = NULL;
    return (result);
}

t_stack *ft_lstlast(t_stack *lst)
{
    if (lst->next == NULL)
        return (lst);
    while (lst)
	{
		if (lst->next == NULL)
			return (lst);
        lst = lst->next;
	}
    return (lst);
}

void    ft_lstadd_back(t_stack **lst, t_stack *new)
{
    t_stack *temp;

    if (!*lst)
	{
        *lst = new;
	}
    else
    {
        temp = ft_lstlast(*lst);
        temp->next = new;
    }
}