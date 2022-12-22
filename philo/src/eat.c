/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:20:58 by loumouli          #+#    #+#             */
/*   Updated: 2022/12/22 14:00:42 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*try to lock the fork in the id position*/

int	lock_all_fork(t_philo *philo, int id_1, int id_2)
{
	t_rules	*rules;

	if (id_1 == id_2)
		return (0);
	rules = philo->rules;
	pthread_mutex_lock(&rules->arr_fork[id_1].lock);
	if (rules->arr_fork[id_1].taken == 0)
	{
		pthread_mutex_lock(&rules->arr_fork[id_2].lock);
		if (rules->arr_fork[id_2].taken == 0)
		{
			rules->arr_fork[id_1].taken = 1;
			printf_mutex(rules, "has taken a fork", gettime(), philo->id);
			rules->arr_fork[id_2].taken = 1;
			printf_mutex(rules, "has taken a fork", gettime(), philo->id);
			pthread_mutex_unlock(&rules->arr_fork[id_2].lock);
			pthread_mutex_unlock(&rules->arr_fork[id_1].lock);
			return (1);
		}
		pthread_mutex_unlock(&rules->arr_fork[id_2].lock);
		pthread_mutex_unlock(&rules->arr_fork[id_1].lock);
		return (0);
	}
	pthread_mutex_unlock(&rules->arr_fork[id_1].lock);
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
		pthread_mutex_lock(&rules->lock_nbr_meal);
		philo->last_meal = gettime();
		pthread_mutex_unlock(&rules->lock_nbr_meal);
		if (check_stop(rules))
			sleep_philo(rules->tte, rules);
		pthread_mutex_lock(&rules->lock_nbr_meal);
		philo->nbr_eat++;
		pthread_mutex_unlock(&rules->lock_nbr_meal);
		unlock_fork(philo, philo->left_fork);
		unlock_fork(philo, philo->right_fork);
	}
}

/*Wont stop till philo has eat
Left fork first for even philo id
Right fork first for odd philo id
*/

void	go_eat(t_philo *philo)
{
	while (check_stop(philo->rules))
	{
		if ((philo->id % 2)
			&& lock_all_fork(philo, philo->left_fork, philo->right_fork))
		{
			trigger_eat_n_unlock(philo);
			return ;
		}
		else if (!(philo->id % 2)
			&& lock_all_fork(philo, philo->right_fork, philo->left_fork))
		{
			trigger_eat_n_unlock(philo);
			return ;
		}
	}
}
