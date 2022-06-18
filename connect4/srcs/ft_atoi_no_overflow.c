/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_no_overflow.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 12:39:51 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/11 12:46:42 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi_no_overflow(char *s)
{
	unsigned int	res;
	unsigned int	i;

	res = 0;
	i = 0;
	while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
		i++;
	if (s[i] == '-')
		return (-1);
	if (s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		if (res > 214748364 || (res == 214748364 && s[i] > '7'))
			return (-1);
		res = res * 10 + s[i] - '0';
		i++;
	}
	return ((int) res);
}
