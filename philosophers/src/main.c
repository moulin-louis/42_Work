/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:45:55 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/07 15:50:18 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*Init all philo last meal to current timestamp
Return -1 to init x in start_philo*/

int	init_last_meal_n_x(t_group *groups)
{
	int	x;

	x = -1;
	while (++x < groups->rules->nbr_philo)
		groups->philo_grp[x].last_meal = gettime();
	groups->rules->start_timestamp = gettime();
	return (-1);
}

void	wait_start(t_rules *rules)
{
	while (1)
	{
		if (rules->nbr_thread_launched)
		{
			return ;
		}
	}
}

/*Main routine for a philo
Say that he has launched
Wait for all philo to launch
Start his routine (eat sleep think)*/

void	*handle_philo(void	*ptr)
{
	t_philo	*philo;
	t_rules	*rules;
	time_t	tthk;

	philo = (t_philo *)ptr;
	rules = philo->rules;
	while (check_stop(rules))
	{
		go_eat(philo);
		printf_mutex(rules, "is sleeping", gettime(), philo->id);
		sleep_philo(rules->tts, rules);
		tthk = get_tthk(rules, philo);
		printf_mutex(rules, "is thinking", gettime(), philo->id);
		sleep_philo(tthk, rules);
	}
	return (ptr);
}

/*Launch all philo and the superviser,
wait for each thread to end*/

void	start_philo(t_group *groups)
{
	int	x;
	int	i;

	x = init_last_meal_n_x(groups);
	pthread_create(&groups->id_superviser, NULL, &check_end, groups);
	while (++x < groups->rules->nbr_philo)
	{
		if (pthread_create(&groups->id_thread[x], NULL, &handle_philo,
				&groups->philo_grp[x]))
		{
			groups->rules->nbr_thread_launched = -1;
			printf_mutex(groups->rules, "failed to start thread", gettime(), x);
			break ;
		}
	}
	i = -1;
	while (++i < x)
	{
		if (pthread_join(groups->id_thread[i], NULL))
			printf("pthread join failed\n");
	}
	if (pthread_join(groups->id_superviser, NULL))
		printf("pthread_join failed\n");
}

/*Main fn, parse the user input into each struct*/

int	main(int ac, char **av)
{
	t_rules	rules;
	t_group	groups;	

	if (ac < 5 || ac > 6)
		return (printf("Wrong numbers of arguements pls\n"), 2);
	memset(&rules, 0, sizeof(t_rules));
	if (set_rules(&rules, av))
		return (clean_rules(&rules), printf("failed to parse rules\n"), 1);
	memset(&groups, 0, sizeof(t_group));
	if (init_philo(&groups, &rules))
	{
		clean_rules(&rules);
		printf("Failed to init philo struct\n");
		return (3);
	}
	groups.id_thread = malloc(sizeof(pthread_t) * groups.rules->nbr_philo);
	if (!groups.id_thread)
	{
		printf("Malloc id thread failed\n");
		clean_groups(&groups);
		return (4);
	}
	start_philo(&groups);
	clean_groups(&groups);
	return (0);
}
