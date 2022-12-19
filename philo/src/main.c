/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:45:55 by loumouli          #+#    #+#             */
/*   Updated: 2022/12/19 17:15:52 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

	x = 0;
	while (x < groups->rules->nbr_philo)
	{
		groups->philo_grp[x].last_meal = gettime();
		x++;
	}
	groups->rules->start_timestamp = gettime();
}

void	*handle_philo(void	*ptr)
{
	t_philo	*philo;
	t_rules	*rules;
	time_t tt_think;

	philo = (t_philo *)ptr;
	rules = philo->rules;
	while (check_stop(rules))
	{
		if (check_stop(rules))
			go_eat(philo);
		if (check_stop(rules))
		{
			printf_mutex(rules, "is sleeping", gettime(), philo->id);
			sleep_philo(rules->tts, rules);
		}
		printf_mutex(rules, "is thinking", gettime(), philo->id);
		tt_think = get_tthk(rules, philo);
		sleep_philo(tt_think, rules);
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
		pthread_create(&groups->id_thread[x], NULL, &handle_philo,
			&groups->philo_grp[x]);
	x = -1;
	pthread_join(groups->id_superviser, NULL);
	while (++x < groups->rules->nbr_philo)
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

