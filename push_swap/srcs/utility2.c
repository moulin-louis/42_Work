/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:31:24 by loumouli          #+#    #+#             */
/*   Updated: 2022/05/11 12:08:26 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void    ft_lstclear(t_stack **lst)
{
    t_stack *temp;

    while(*lst)
    {
        temp = (*lst)->next;
        free(*lst);
        *lst = temp;
    }
}

void    ft_putstr(char *str)
{
    int x;

    x = 0;
    while (str[x])
    {
        write(1, &str[x], 1);
        x++;
    }
}