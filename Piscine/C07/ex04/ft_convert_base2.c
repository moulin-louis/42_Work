/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 08:53:08 by loumouli          #+#    #+#             */
/*   Updated: 2022/02/21 10:26:46 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_nbr_len(int nbr, char *base, int len)
{
	int				base_len;
	unsigned int	nb;

	base_len = ft_strlen(base);
	if (nbr < 0)
	{
		nb = nbr * -1;
		len++;
	}
	else
		nb = nbr;
	while (nb >= (unsigned)base_len)
	{
		nb /= base_len;
		len++;
	}
	len++;
	return (len);
}

void	ft_putnbr_base(int nbr, char *base, char *nbrf)
{
	int		len_base;
	int		i;
	int		len_nbrf;
	long	nb;

	len_base = ft_strlen(base);
	len_nbrf = ft_nbr_len(nbr, base, 0);
	nb = nbr;
	i = 0;
	if (nb < 0)
	{
		nbrf[0] = '-';
		nb *= -1;
		i = 1;
	}
	len_nbrf--;
	while (nb >= len_base)
	{
		nbrf[len_nbrf] = base[nb % len_base];
		nb /= len_base;
		len_nbrf--;
	}
	if (nb < len_base)
		nbrf[i] = base[nb];
}

int	ft_is_minus_or_plus(char *str)
{
	int	i;
	int	minus;

	i = 0;
	minus = 1;
	while ((str[i] >= 't' && str[i] <= '\r') || str[i] == ' ')
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus *= -1;
		i++;
	}
	return (minus);
}
