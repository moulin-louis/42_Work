/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:20:58 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/04 16:35:10 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

/*Try to lock two forks
Lock fork if and only if we can lock all two fork*/

int	lock_all_fork(t_philo *philo, int id_1, int id_2)
{
	t_rules	*rules;

	if ((id_1 == id_2) || !check_stop(philo->rules))
		return (0);
	rules = philo->rules;
	if (rules->arr_fork[id_1].taken == 0)
	{
		if (rules->arr_fork[id_2].taken == 0)
		{
			rules->arr_fork[id_1].taken = 1;
			rules->arr_fork[id_2].taken = 1;
			printf_mutex(rules, "has taken a fork", gettime(), philo->id);
			printf_mutex(rules, "has taken a fork", gettime(), philo->id);
			return (1);
		}
		return (0);
	}
	return (0);
}

/*Unlock id fork*/

void	unlock_fork(t_philo *philo, int id)
{
	philo->rules->arr_fork[id].taken = 0;
}

/*Will eat, update last meal and nbr meal
Unlock two fork*/

void	trigger_eat_n_unlock(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	printf_mutex(rules, "is eating", gettime(), philo->id);
	philo->last_meal = gettime();
	sleep_philo(rules->tte, rules);
	philo->nbr_eat++;
	if (philo->id % 2)
	{
		unlock_fork(philo, philo->left_fork);
		unlock_fork(philo, philo->right_fork);
	}
	else
	{
		unlock_fork(philo, philo->right_fork);
		unlock_fork(philo, philo->left_fork);
	}
}

/*Wont stop till philo has eat
To prevent potential mutex dead lock :
- Left fork first for even philo id
- Right fork first for odd philo id
*/

void	go_eat(t_philo *philo)
{
	if (philo->id % 2)
	{
		while (check_stop(philo->rules))
		{
			if (lock_all_fork(philo, philo->left_fork, philo->right_fork))
			{
				trigger_eat_n_unlock(philo);
				return ;
			}
			usleep(50);
		}
	}
	else
	{
		while (check_stop(philo->rules))
		{
			if (lock_all_fork(philo, philo->right_fork, philo->left_fork))
			{
				trigger_eat_n_unlock(philo);
				return ;
			}
			usleep(50);
		}
	}
}
