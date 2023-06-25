/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fibonacci.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:57:25 by loumouli          #+#    #+#             */
/*   Updated: 2022/02/11 14:30:39 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_recurfibo(int index, int nbr)
{
	if (index > 2)
		return (nbr = ft_recurfibo(index - 1, nbr)
			+ ft_recurfibo(index - 2, nbr));
	return (nbr);
}

int	ft_fibonacci(int index)
{
	int	nbr;

	nbr = 1;
	if (index < 0)
		return (-1);
	if (index == 0)
		return (0);
	return (ft_recurfibo(index, nbr));
}
