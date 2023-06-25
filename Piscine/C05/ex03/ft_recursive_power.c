/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:25:52 by loumouli          #+#    #+#             */
/*   Updated: 2022/02/13 12:41:42 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_power(int nb, int power, int n)
{
	if (!(power == 2))
	{
		nb = nb * n;
		power--;
		return (ft_power(nb, power, n));
	}
	nb = nb * n;
	return (nb);
}

int	ft_recursive_power(int nb, int power)
{
	int	n;

	n = nb;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	if (power == 1)
		return (nb);
	return (ft_power(nb, power, n));
}
