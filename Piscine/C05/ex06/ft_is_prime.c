/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 17:39:49 by loumouli          #+#    #+#             */
/*   Updated: 2022/02/14 09:38:18 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_prime(int nb)
{
	int		i;

	if (nb <= 0)
		return (0);
	if (nb == 1)
		return (0);
	if (nb == 2)
		return (1);
	if (nb % 2 == 0)
		return (0);
	i = 2;
	while (i <= (nb / i))
	{
		if (nb % i == 0)
			return (0);
		i ++;
	}
	return (1);
}
/*
int main (void)
{
	int a = 1;
	while(a)
	{
	if(ft_is_prime(a))
		printf("%d : \e[0;32mPrime\e[0m\n", a);	
	else
		printf("%d : \e[0;31mNot Prime\e[0m\n", a);
	a++;
	}
}*/
