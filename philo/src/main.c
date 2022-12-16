/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:45:55 by loumouli          #+#    #+#             */
/*   Updated: 2022/12/16 16:10:13 by loumouli         ###   ########.fr       */
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
}

void	*handle_philo(void	*ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2)
		usleep(10);
	while (check_stop(philo->rules))
	{
		if (check_stop(philo->rules))
			go_eat(philo);
		if (check_stop(philo->rules))
			sleep_philo(philo->rules->tts, philo->rules);
		if (check_stop(philo->rules))
			printf_mutex(philo->rules, "is thinking", gettime(), philo->id);
	}
	return (ptr);
}

/*Launch all philo thread and the superviser one, wait for each thread to end*/

void	start_philo(t_group *groups)
{
	int	x;

	x = -1;
	init_last_meal(groups);
	while (++x < groups->rules->nbr_philo)
		pthread_create(&groups->id_thread[x], NULL, &handle_philo,
			&groups->philo_grp[x]);
	pthread_create(&groups->id_superviser, NULL, &check_end, groups);
	x = -1;
	while (++x < groups->rules->nbr_philo)
		pthread_join(groups->id_thread[x], NULL);
	pthread_join(groups->id_superviser, NULL);
}

/*Main fn, call parsing fn and start the simulation*/

int	main(int ac, char **av)
{
	t_group	groups;

	groups = parsing_n_init(ac, av);
	//printf("start at :\n%ld\n", gettime());
	start_philo(&groups);
	clean_groups(&groups);
	return (0);
}
