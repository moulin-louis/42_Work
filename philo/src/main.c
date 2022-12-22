/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:45:55 by loumouli          #+#    #+#             */
/*   Updated: 2022/12/22 13:16:48 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

/*Start all routine for the given thread*/

int	check_stop(t_rules *rules)
{
	pthread_mutex_lock(&rules->lock_stop_1);
	if (rules->trigger_stop == 1)
	{
		pthread_mutex_unlock(&rules->lock_stop_1);
		return (0);
	}
	pthread_mutex_unlock(&rules->lock_stop_1);
	return (1);
}

/*Init all philo last meal to current timestamp*/

void	init_last_meal(t_group *groups)
{
	int	x;

	x = -1;
	while (++x < groups->rules->nbr_philo)
		groups->philo_grp[x].last_meal = gettime();
	groups->rules->start_timestamp = gettime();
}

/*
TO DO : 
WAIT FOR ALL THREAD TO BE LAUNCHED TO START THE SIMU
IF A THREAD FAILED TO LAUNCHED WE DONT WANT TO START THE SIMU
AND QUIT ALL THREAD
*/

void	*handle_philo(void	*ptr)
{
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)ptr;
	rules = philo->rules;
	pthread_mutex_lock(&rules->lock_nbr_thread);
	rules->nbr_thread_launched++;
	pthread_mutex_unlock(&rules->lock_nbr_thread);
	while (1)
	{
		if (check_start(rules) == 1)
			break ;
		if (check_start(rules) == 2)
			return (NULL);
	}
	while (check_stop(rules))
	{
		if (check_stop(rules))
			go_eat(philo);
		printf_mutex(rules, "is sleeping", gettime(), philo->id);
		sleep_philo(rules->tts, rules);
		printf_mutex(rules, "is thinking", gettime(), philo->id);
		sleep_philo(get_tthk(rules, philo), rules);
	}
	return (ptr);
}

/*Launch all philo thread and the superviser one, wait for each thread to end*/

void	start_philo(t_group *groups)
{
	int	x;

	x = -1;
	init_last_meal(groups);
	pthread_create(&groups->id_superviser, NULL, &check_end, groups);
	while (++x < groups->rules->nbr_philo)
	{
		if (pthread_create(&groups->id_thread[x], NULL,
				&handle_philo, &groups->philo_grp[x]))
		{
			pthread_mutex_lock(&groups->rules->lock_nbr_thread);
			groups->rules->nbr_thread_launched = -2;
			pthread_mutex_lock(&groups->rules->lock_nbr_thread);
			break ;
		}
	}
	pthread_join(groups->id_superviser, NULL);
	while (x--)
		pthread_join(groups->id_thread[x], NULL);
}

/*Main fn, call parsing fn and start the simulation*/

int	main(int ac, char **av)
{
	t_group	groups;

	groups = parsing_n_init(ac, av);
	start_philo(&groups);
	clean_groups(&groups);
	return (0);
}
