/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 14:48:11 by loumouli          #+#    #+#             */
/*   Updated: 2022/12/19 12:04:34 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Check if all philo are all alive based on their last meal*/

int	check_death(t_group *groups)
{
	int	i;

	i = -1;
	time_t current_time = gettime();
	while (++i < groups->rules->nbr_philo)
	{
		pthread_mutex_lock(&groups->rules->lock_nbr_meal);
		if (current_time >= groups->philo_grp[i].last_meal + groups->rules->ttd)
		{
			printf_mutex(groups->rules, "died", gettime(), i + 1);
			return (pthread_mutex_unlock(&groups->rules->lock_nbr_meal), 1);
		}
		pthread_mutex_unlock(&groups->rules->lock_nbr_meal);
	}
	return (0);
}

/*Check if all philo have eaten the minimun ammount of meal */

int	check_nbr_meal(t_group *groups)
{
	int	i;

	i = -1;
	while (++i < groups->rules->nbr_philo)
	{
		pthread_mutex_lock(&groups->rules->lock_nbr_meal);
		if (groups->philo_grp[i].nbr_eat == groups->rules->max_eat)
		{
			pthread_mutex_unlock(&groups->rules->lock_nbr_meal);
			continue ;
		}
		else
		{
			pthread_mutex_unlock(&groups->rules->lock_nbr_meal);
			break ;
		}
	}	
	return (0);
}

/*Check if we need to end the simulation*/

void	*check_end(void *ptr)
{
	t_group	*groups;

	groups = (void *)ptr;
	if (groups->rules->max_eat == 0)
	{
		pthread_mutex_lock(&groups->rules->lock_stop_1);
		groups->rules->trigger_stop = 1;
		pthread_mutex_unlock(&groups->rules->lock_stop_1);
		return (NULL);
	}
	while (1)
	{
		if (check_death(groups) || check_nbr_meal(groups))
		{
			pthread_mutex_lock(&groups->rules->lock_stop_1);
			groups->rules->trigger_stop = 1;
			pthread_mutex_unlock(&groups->rules->lock_stop_1);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
