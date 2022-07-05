/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 22:10:29 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/04 22:27:21 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

int ft_check_input(t_stack *lst)
{
    t_stack *temp;

    temp = lst;
    while (temp)
    {
        
    }
    return (1);
}

t_stack *ft_init(char **av)
{
    int x;
    t_stack *lst;
    
    x = 2;
    lst = ft_lstnew(ft_atoi(av[1]));
    if (!lst)
        return (NULL);
    while (av[x])
    {
        ft_lstadd_back(&lst, ft_lstnew(ft_atoi(av[x])));
        x++;
    }
    if (ft_check_input(lst) == -1)
        return (-1);
    return (lst);
}