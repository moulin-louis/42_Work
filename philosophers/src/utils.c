/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:31:15 by loumouli          #+#    #+#             */
/*   Updated: 2022/11/30 17:32:57 by loumouli         ###   ########.fr       */
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
			printf("time_to_die time_to_eat time_to_sleep [number_of_times");
			printf("_each_philosopher_must_eat]\n");
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
