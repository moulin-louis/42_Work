/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:20:58 by loumouli          #+#    #+#             */
/*   Updated: 2022/12/16 15:40:14 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*try to lock the fork in the id position*/

int	lock_all_fork(t_philo *philo, int id_left, int id_right)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&rules->arr_fork[id_left].lock);
	if (rules->arr_fork[id_left].taken == 0)
	{
		pthread_mutex_lock(&rules->arr_fork[id_right].lock);
		if (rules->arr_fork[id_right].taken == 0)
		{
			rules->arr_fork[id_left].taken = 1;
			printf_mutex(rules, "has taken a fork", gettime(), philo->id);
			rules->arr_fork[id_right].taken = 1;
			printf_mutex(rules, "has taken a fork", gettime(), philo->id);
			pthread_mutex_unlock(&rules->arr_fork[id_right].lock);
			pthread_mutex_unlock(&rules->arr_fork[id_left].lock);
			return (1);
		}
		pthread_mutex_unlock(&rules->arr_fork[id_right].lock);
		pthread_mutex_unlock(&rules->arr_fork[id_left].lock);
		return (0);
	}
	pthread_mutex_unlock(&rules->arr_fork[id_left].lock);
	return (0);
}

/*unlock id fork*/

void	unlock_fork(t_philo *philo, int id)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&rules->arr_fork[id].lock);
	rules->arr_fork[id].taken = 0;
	pthread_mutex_unlock(&rules->arr_fork[id].lock);
}

/*will eat and unlock all fork after that*/

void	trigger_eat_n_unlock(t_philo *philo)
{
	t_rules	*rules;

	if (check_stop(philo->rules))
	{
		rules = philo->rules;
		if (check_stop(philo->rules))
			printf_mutex(rules, "is eating", gettime(), philo->id);
		if (check_stop(rules))
			sleep_philo(rules->tte, rules);
		philo->last_meal = gettime();
		pthread_mutex_lock(&rules->lock_nbr_meal);
		philo->nbr_eat++;
		pthread_mutex_unlock(&rules->lock_nbr_meal);
		unlock_fork(philo, philo->left_fork);
		unlock_fork(philo, philo->right_fork);
	}
}

void	go_eat(t_philo *philo)
{
	while (check_stop(philo->rules))
	{
		if (check_stop(philo->rules)
			&& lock_all_fork(philo, philo->left_fork, philo->right_fork))
		{
			trigger_eat_n_unlock(philo);
			return ;
		}
		else
			usleep(10);
	}
}
