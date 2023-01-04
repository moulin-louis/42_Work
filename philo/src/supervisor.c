/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 14:48:11 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/03 19:42:39 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

/*Check if all philo are all alive based on their last meal*/

int	check_death(t_group *groups)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&groups->rules->lock_nbr_meal);
	while (++i < groups->rules->nbr_philo)
	{
		if (gettime() > groups->philo_grp[i].last_meal + groups->rules->ttd)
		{	
			printf_mutex(groups->rules, "died", gettime(), i + 1);
			pthread_mutex_lock(&groups->rules->print_mutex);
			return (pthread_mutex_unlock(&groups->rules->lock_nbr_meal), 1);
		}
	}
	pthread_mutex_unlock(&groups->rules->lock_nbr_meal);
	return (0);
}

/*Check if all philo have eaten at least the minimun ammount of meal */

int	check_nbr_meal(t_group *groups)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&groups->rules->lock_nbr_meal);
	while (++i < groups->rules->nbr_philo)
	{
		if (groups->rules->max_eat == -1)
		{
			pthread_mutex_unlock(&groups->rules->lock_nbr_meal);
			return (0);
		}
		if (groups->philo_grp[i].nbr_eat >= groups->rules->max_eat)
			continue ;
		else
		{
			pthread_mutex_unlock(&groups->rules->lock_nbr_meal);
			return (0);
		}
	}
	pthread_mutex_unlock(&groups->rules->lock_nbr_meal);
	return (1);
}

/*THis is the main routines of the supervisor thread
It will check for two end conditions :
- if a philo is dead
- if all philo has eaten at least X time*/

void	*check_end(void *ptr)
{
	t_group	*groups;

	groups = (void *)ptr;
	if (groups->rules->max_eat == 0)
	{
		pthread_mutex_lock(&groups->rules->lock_stop_1);
		groups->rules->trigger_stop = 1;
		return (pthread_mutex_unlock(&groups->rules->lock_stop_1), NULL);
	}
	while (check_stop(groups->rules))
	{
		if (check_death(groups))
		{
			pthread_mutex_lock(&groups->rules->lock_stop_1);
			groups->rules->trigger_stop = 1;
			pthread_mutex_unlock(&groups->rules->print_mutex);
			return (pthread_mutex_unlock(&groups->rules->lock_stop_1), NULL);
		}
		if (check_nbr_meal(groups))
		{
			pthread_mutex_lock(&groups->rules->lock_stop_1);
			groups->rules->trigger_stop = 1;
			return (pthread_mutex_unlock(&groups->rules->lock_stop_1), NULL);

		}
		//usleep(10);
	}
	return (NULL);
}
