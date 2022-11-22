/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:28:07 by loumouli          #+#    #+#             */
/*   Updated: 2022/11/22 16:47:50 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	chr_error(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			printf("error parsing, gib :\n./philo number_of_philosophers");
			printf("time_to_die time_to_eat time_to_sleep [number_of_times_each");
			printf("_philosopher_must_eat]\n");
			return (1);
		}
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	nbr;

	nbr = 0;
	if (chr_error((char *)str))
		exit (2);
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + *str - 48;
		str++;
	}
	return (nbr);
}

void	parse_input(int ac, char **av, t_philo *data)
{
	if (ac < 5 || ac > 6)
		exit (1);
	data->nbr_philo = ft_atoi(av[1]);
	data->nbr_fork = data->nbr_philo;
	data->ttd = ft_atoi(av[2]);
	data->tte = ft_atoi(av[3]);
	data->tts = ft_atoi(av[4]);
	if (av[5])
		data->nbr_eat = ft_atoi(av[5]);
	if (data->nbr_philo < 0 || data->ttd < 0 || data->tte < 0 || data->tts < 0)
	{
		printf("error parsing, use positive number pls\n");
		exit(1);
	}
	if (av[5] && data->nbr_eat < 0)
	{
		printf("error parsing, use positive number pls\n");
		exit(1);
	}
}

void	sleep_philo(int time)
{
	time_t	end_time;

	end_time = gettime() + time;
	while (gettime() < end_time)
		usleep(100);
}

time_t	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
