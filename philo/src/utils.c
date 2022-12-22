/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:31:15 by loumouli          #+#    #+#             */
/*   Updated: 2022/12/22 13:14:25 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>

/*Calculate time to think for each philo*/

time_t	get_tthk(t_rules *rules, t_philo *philo)
{
	time_t	result;

	result = (rules->ttd - (gettime() - philo->last_meal) - rules->tte) / 2;
	if (rules->tts == 0)
		result = (rules->ttd -(gettime() - philo->last_meal))
			- rules->tte - 10 ;
	if (result > 500)
		return (500);
	if (result < 0)
		return (0);
	return (result);
}

/*Convert string input into int*/

int	ft_atoi(const char *str)
{
	int	nbr;
	int	i;

	nbr = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
	}
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + *str - 48;
		str++;
	}
	return (nbr);
}

/*custom sleep fn to avoid usleep delay*/

void	sleep_philo(int time, t_rules *rules)
{
	time_t	end_time;

	end_time = gettime() + time;
	while (gettime() < end_time)
	{
		if (!check_stop(rules))
			break ;
		usleep(1);
	}
}

/*get current timestamp*/

time_t	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
