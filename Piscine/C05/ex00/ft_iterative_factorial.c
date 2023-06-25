/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:26:30 by loumouli          #+#    #+#             */
/*   Updated: 2022/02/10 16:44:12 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_factorial(int nb)
{
	int	j;
	int	f;

	if (nb < 0)
		return (0);
	j = 1;
	f = 1;
	while (j <= nb)
	{
		f = f * j;
		j++;
	}
	return (f);
}
