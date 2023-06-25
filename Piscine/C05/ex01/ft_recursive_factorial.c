/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:32:08 by loumouli          #+#    #+#             */
/*   Updated: 2022/02/10 17:11:34 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_fact(int n, int nb)
{
	n = nb * n;
	nb--;
	if (nb > 0)
		return (ft_fact(n, nb));
	return (n);
}

int	ft_recursive_factorial(int nb)
{
	if (nb == 1 || nb == 0)
		return (1);
	if (nb < 0)
		return (0);
	return (ft_fact(1, nb));
}
