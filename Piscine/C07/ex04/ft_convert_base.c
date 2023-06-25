/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:15:45 by loumouli          #+#    #+#             */
/*   Updated: 2022/02/21 15:11:56 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_strlen(char *str);
int		ft_is_minus_or_plus(char *str);
void	ft_putnbr_base(int nbr, char *base, char *nbrf);
int		ft_nbr_len(int nbr, char *base, int len);

int	ft_basecheck(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		j = 1 + i;
		if (base[i] == '+' || base[i] == '-')
			return (0);
		if (base[i] < 33 || base[i] > 126)
			return (0);
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_is_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_is_whitespace(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi_base(char *str, char *base)
{
	int	digit;
	int	i;
	int	base_len;

	base_len = 0;
	i = 0;
	digit = 0;
	if (!(ft_basecheck(base)))
		return (0);
	while (base[base_len])
		base_len++;
	while ((str[i] >= 't' && str[i] <= '\r') || str[i] == ' ')
		i++;
	while (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ft_is_base(str[i], base) >= 0)
	{
		digit = (digit * base_len) + ft_is_base(str[i], base);
		i++;
	}
	digit *= ft_is_minus_or_plus(str);
	return (digit);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	char	*final_number;
	int		tempnbr;
	int		len_nbr;

	if (ft_basecheck(base_from) == 0 || ft_basecheck(base_to) == 0)
		return (0);
	tempnbr = ft_atoi_base(nbr, base_from);
	len_nbr = ft_nbr_len(tempnbr, base_to, 0);
	final_number = (char *)malloc(sizeof(char) * (len_nbr + 1));
	if (!final_number)
		return (0);
	ft_putnbr_base(tempnbr, base_to, final_number);
	final_number[len_nbr] = '\0';
	return (final_number);
}
