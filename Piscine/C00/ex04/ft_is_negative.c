/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_negative.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:34:52 by loumouli          #+#    #+#             */
/*   Updated: 2022/02/03 12:51:06 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_is_negative(int n)
{
	char	nbetat;

	if (n >= 0)
	{
		nbetat = 80;
		write(1, &nbetat, 1);
	}
	else
	{
		nbetat = 78;
		write(1, &nbetat, 1);
	}
}
