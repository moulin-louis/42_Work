/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:28:07 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/07 16:34:55 by loumouli         ###   ########.fr       */
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
		return (rules->nbr_fork = 0, printf("malloc arr fork failed\n"), 1);
	x = -1;
	while (++x < rules->nbr_philo)
	{
		rules->arr_fork[x].taken = 0;
	}
	return (0);
}

/*fill t_rules stuct with user input*/

int	set_rules(t_rules *rules, char **av)
{
	(*rules).nbr_philo = ft_atoi(av[1]);
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
	{
		printf("Gib valid argument for philo pls\n");
		exit (6);
	}
	if (init_fork(rules))
		return (1);
	return (0);
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

int	init_philo(t_group *groups, t_rules *rules)
{
	int		x;

	groups->rules = rules;
	groups->philo_grp = malloc(sizeof(t_philo) * rules->nbr_philo);
	if (!groups->philo_grp)
		return (printf("Malloc philo grp failed\n"), 1);
	memset(groups->philo_grp, 0, sizeof(t_philo) * rules->nbr_philo);
	x = -1;
	while (++x < rules->nbr_philo)
	{
		groups->philo_grp[x].id = x + 1;
		groups->philo_grp[x].rules = rules;
	}
	init_fork_id_in_philo(groups, rules);
	return (0);
}
