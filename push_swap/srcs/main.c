/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:31:24 by loumouli          #+#    #+#             */
/*   Updated: 2022/07/04 22:24:22 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"
#include <stdio.h>
int main(int ac, char **av)
{
    t_stack *lst;

    if (ac < 2)
        return(-1);
    lst = ft_init(av);
    ft_lstclear(&lst);
}