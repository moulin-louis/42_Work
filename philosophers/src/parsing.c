/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:28:07 by loumouli          #+#    #+#             */
/*   Updated: 2022/11/16 15:46:00 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	nbr;
	int	sign;

	nbr = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = sign * -1;
		str++;
	}
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + *str - 48;
		str++;
	}
	nbr = nbr * sign;
	return (nbr);
}

void	parse_input(int ac, char **av, t_philo *data)
{
	if (ac < 4 || ac > 5)
		exit (1);
	data->nbr_philo = ft_atoi(av[0]);
	data->nbr_fork = data->nbr_philo;
	data->ttd = ft_atoi(av[1]);
	data->tte = ft_atoi(av[2]);
	data->tts = ft_atoi(av[3]);
	if (av[4])
		data->nbr_eat = ft_atoi(av[4]);
	if (data->nbr_philo < 0 || data->ttd < 0 || data->tte <  0 || data->tts< 0)
	{
		printf("error parsing, use positive number pls\n");
		exit(1);
	}
	if (av[4] && data->nbr_eat < 0)
	{
		printf("error parsing, use positive number pls\n");
		exit(1);
	}
}
