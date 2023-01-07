/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:31:15 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/07 15:48:56 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>

/*Check if we need to stop tht simulation
- Return 0 if simulation need to stop
- Return 1 if simulation can continue*/

int	check_stop(t_rules *rules)
{
	pthread_mutex_lock(&rules->lock_nbr_thread);
	if (rules->nbr_thread_launched == -1)
		return (pthread_mutex_unlock(&rules->lock_nbr_thread), 0);
	pthread_mutex_unlock(&rules->lock_nbr_thread);
	pthread_mutex_lock(&rules->lock_stop_1);
	if (rules->trigger_stop == 1)
	{
		pthread_mutex_unlock(&rules->lock_stop_1);
		return (0);
	}
	pthread_mutex_unlock(&rules->lock_stop_1);
	return (1);
}

int	check_str(const char *str)
{
	int	i;

	i = 0;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
	}
	return (0);
}

/*Convert string input into int
Check if there is only number in it*/

int	ft_atoi(const char *str)
{
	int	nbr;
	int	nbr_tmp;
	int	nbr_tmp2;
	int	i;

	nbr = 0;
	if (check_str(str))
		return (-1);
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		i = 0;
		nbr_tmp2 = nbr;
		while (i++ < 9)
		{
			nbr_tmp = nbr;
			nbr += nbr_tmp2;
			if (nbr < nbr_tmp)
				return (-1);
		}
		nbr = nbr + (*str - 48);
		str++;
	}
	return (nbr);
}

/*custom sleep fn to avoid usleep delgtay*/

void	sleep_philo(int time, t_rules *rules)
{
	time_t	end_time;

	if (time == 0)
		return ;
	end_time = gettime() + time;
	while (gettime() < end_time)
	{
		if (!check_stop(rules))
			break ;
		usleep(5);
	}
}

/*get current timestamp*/

time_t	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
