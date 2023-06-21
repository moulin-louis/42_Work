/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 14:48:11 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/07 17:06:17 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
/*Check if all philo are all alive based on their last meal*/

int	check_death(t_group *groups)
{
	int	i;

	i = -1;
	while (++i < groups->rules->nbr_philo)
	{
		if (gettime() > groups->philo_grp[i].last_meal + groups->rules->ttd)
		{	
			printf_mutex(groups->rules, "died", gettime(), i + 1);
			return (1);
		}
	}
	return (0);
}

/*Check if all philo have eaten at least the minimun ammount of meal */

int	check_nbr_meal(t_group *groups)
{
	int	i;

	i = -1;
	while (++i < groups->rules->nbr_philo)
	{
		if (groups->rules->max_eat == -1)
		{
			return (0);
		}
		if (groups->philo_grp[i].nbr_eat >= groups->rules->max_eat)
		{
			continue ;
		}
		else
		{
			return (0);
		}
	}
	return (1);
}

void	trigger_stop(t_rules *rules)
{
	rules->trigger_stop = 1;
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
		groups->rules->trigger_stop = 1;
		return (NULL);
	}
	while (check_stop(groups->rules))
	{
		if (check_death(groups))
		{
			trigger_stop(groups->rules);
			return (NULL);
		}
		if (check_nbr_meal(groups))
		{
			trigger_stop(groups->rules);
			return (NULL);
		}
		usleep(50);
	}
	return (NULL);
}
