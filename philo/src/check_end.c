/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 14:48:11 by loumouli          #+#    #+#             */
/*   Updated: 2022/12/17 00:29:58 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Check if all philo are all alive based on their last meal*/

int	check_death(t_group *groups)
{
	int	i;

	i = -1;
	while (++i < groups->rules->nbr_philo)
	{
		pthread_mutex_lock(&groups->rules->lock_nbr_meal);
		if (gettime() >= groups->philo_grp[i].last_meal + groups->rules->ttd)
		{
			printf_mutex(groups->rules, "died", gettime(), i + 1),
			pthread_mutex_unlock(&groups->rules->lock_nbr_meal);
			return (1);
		}
		pthread_mutex_unlock(&groups->rules->lock_nbr_meal);
	}
	return (0);
}

/*Check if all philo have eaten the minimun ammount of meal */

int	check_nbr_meal(t_group *groups)
{
	int	i;
	int	nbr_of_philo_fullfill;

	i = -1;
	nbr_of_philo_fullfill = 0;
	while (check_stop(groups->rules) && (i++ < groups->rules->nbr_philo))
	{
		pthread_mutex_lock(&groups->rules->lock_nbr_meal);
		if (groups->philo_grp[i].nbr_eat == groups->rules->max_eat)
			nbr_of_philo_fullfill++;
		pthread_mutex_unlock(&groups->rules->lock_nbr_meal);
	}
	if (nbr_of_philo_fullfill == groups->rules->nbr_philo)
		return (1);
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
