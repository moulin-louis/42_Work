/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:25:16 by marnaudy          #+#    #+#             */
/*   Updated: 2022/06/11 09:55:55 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atol(const char *nptr, long int *res)
{
	int		i;
	int		sign;

	*res = 0;
	i = 0;
	sign = 1;
	while (nptr[i] && (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13)))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (*res >= 922337203685477581
			|| (*res == 922337203685477580 && nptr[i] > '7' + (sign == -1)))
			return (-1);
		*res = *res * 10 + nptr[i] - '0';
		i++;
	}
	*res *= sign;
	return (0);
}
