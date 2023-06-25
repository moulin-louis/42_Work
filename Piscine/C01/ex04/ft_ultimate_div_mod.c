/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_div_mod.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 11:21:58 by loumouli          #+#    #+#             */
/*   Updated: 2022/02/05 14:06:39 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>

void	ft_ultimate_div_mod(int *aptr, int *bptr)
{
	int	x;
	int	z;
	int	swap;

	x = *aptr;
	z = *bptr;
	swap = x;
	*aptr = x / z;
	*bptr = swap % z;
}
