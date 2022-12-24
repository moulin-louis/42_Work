/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:28:07 by loumouli          #+#    #+#             */
/*   Updated: 2022/12/22 13:38:51 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

/*Malloc an array of x fork and init mutex for each fork*/
int	init_fork(t_rules *rules)
{
	int	x;	

	rules->arr_fork = malloc(sizeof(t_fork) * rules->nbr_fork);
	if (!rules->arr_fork)
		return (rules->nbr_fork = 0, ("malloc arr fork failed\n"), 0);
	x = -1;
	while (++x < rules->nbr_philo)
	{
		if (pthread_mutex_init(&(rules->arr_fork[x].lock), NULL))
		{
			rules->nbr_fork = x;
			return (printf("mutex init failed for fork\n"), 0);
		}
		rules->arr_fork[x].taken = 0;
	}
	return (1);
}

int	mutex_init(t_rules *rules)
{
	if (pthread_mutex_init(&rules->print_mutex, NULL))
	{
		printf("mutex print init failed\n");
		return (1);
	}
	if (pthread_mutex_init(&rules->lock_nbr_meal, NULL))
	{
		printf("mutex nbr meal init failed\n");
		pthread_mutex_destroy(&rules->print_mutex);
		return (1);
	}
	if (pthread_mutex_init(&rules->lock_stop_1, NULL))
	{
		printf("mutex print lock stop failed\n");
		pthread_mutex_destroy(&rules->print_mutex);
		pthread_mutex_destroy(&rules->lock_nbr_meal);
		return (1);
	}
	if (pthread_mutex_init(&rules->lock_nbr_thread, NULL))
	{
		printf("mutex nbr thread launched init failed\n");
		pthread_mutex_destroy(&rules->print_mutex);
		pthread_mutex_destroy(&rules->lock_nbr_meal);
		pthread_mutex_destroy(&rules->lock_nbr_meal);
		return (1);
	}
	return (0);
}

/*fill t_rules stuct with user input*/
int	set_rules(t_rules *rules, char **av)
{
	rules->nbr_philo = ft_atoi(av[1]);
	rules->nbr_fork = rules->nbr_philo;
	rules->ttd = ft_atoi(av[2]);
	rules->tte = ft_atoi(av[3]);
	rules->tts = ft_atoi(av[4]);
	if (av[5])
		rules->max_eat = ft_atoi(av[5]);
	else
		rules->max_eat = -1;
	if (rules->nbr_philo <= 0 || rules->ttd < 0 || rules->tte < 0
		|| rules->tts < 0 || (av[5] && rules->max_eat <= 0)
		||rules->nbr_philo > 200)
		return (printf("Gib valid argument for philo pls\n"), 0);
	if (mutex_init(rules))
	{
		free(rules);
		exit (errno);
	}
	
	if (!init_fork(rules))
		return (0);
	return (1);
}

/*Init fork id*/
void	init_fork_id_in_philo(t_group *groups, t_rules *rules)
{
	int	x;

	x = -1;
	while (++x < rules->nbr_fork)
	{
		if (x == rules->nbr_fork - 1)
		{
			groups->philo_grp[x].left_fork = x;
			groups->philo_grp[x].right_fork = 0;
		}
		else
		{
			groups->philo_grp[x].left_fork = x;
			groups->philo_grp[x].right_fork = x + 1;
		}
	}
}

/*malloc an array of x t_philos and init each of them : fill forks id and 
point to the right t_rules struct*/

int	init_philo(t_group *groups, char **av)
{
	int		x;
	t_rules	rules;
	t_rules	*rls_ptr;

	memset(&rules, 0, sizeof(rules));
	rls_ptr = malloc(sizeof(t_rules));
	if (!rls_ptr)
		return (1);
	*rls_ptr = rules;
	groups->rules = rls_ptr;
	if (!set_rules(rls_ptr, av))
		return (2);
	groups->philo_grp = malloc(sizeof(t_philo) * rules.nbr_philo);
	if (!groups->philo_grp)
		return (3);
	memset(groups->philo_grp, 0, sizeof(t_philo) * rules.nbr_philo);
	x = -1;
	while (++x < rules.nbr_philo)
	{
		groups->philo_grp[x].id = x + 1;
		groups->philo_grp[x].rules = rls_ptr;
	}
	init_fork_id_in_philo(groups, &rules);
	return (0);
}

/*check compliance and call init fn*/

t_group	parsing_n_init(int ac, char **av)
{
	t_group	groups;
	int		status;

	memset(&groups, 0, sizeof(t_group));
	if (ac < 5 || ac > 6)
	{
		printf("Wrong numbers of arguements pls\n");
		exit (1);
	}
	status = init_philo(&groups, av);
	if (status == 1)
		exit(status);
	if (status == 2)
	{
		clean_rules(groups.rules);
		free(groups.rules);
	}
	if (status == 3)
		clean_groups(&groups);
	if (status)
		exit(status);
	groups.id_thread = malloc(sizeof(t_philo) * groups.rules->nbr_philo);
	if (!groups.id_thread)
	{
		clean_groups(&groups);
		exit (1);
	}
	return (groups);
}
