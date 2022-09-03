/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_no_overflow.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 12:39:51 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/03 18:05:13 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	ft_atoi_no_overflow(char *s)
{
	long		res;
	unsigned int	i;
	int				sign;

	res = 0;
	i = 0;
	sign = 1;
	while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + s[i] - '0';
		i++;
	}
	if (res < -2147483648 || res > 2147483647 )
		return (9999999999);
	return (res * sign);
}
