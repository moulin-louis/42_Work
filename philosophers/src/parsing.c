/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:28:07 by loumouli          #+#    #+#             */
/*   Updated: 2022/11/30 18:26:04 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_fork(t_rules *rules)
{
	int	x;	

	rules->arr_fork = malloc(sizeof(t_fork) * rules->nbr_fork);
	if (!rules->arr_fork)
	{
		printf("Malloc failed\n");
		exit(1);
	}
	x = -1;
	while (++x < rules->nbr_philo)
	{
		if (pthread_mutex_init(&(rules->arr_fork[x].lock), NULL))
		{
			free(rules->arr_fork);
			exit (1);
		}
		rules->arr_fork[x].taken = 0;
	}
}

void	init_philo(t_group *result, t_rules *rules)
{
	int	x;

	result->philo_grp = malloc(sizeof(t_philo) * rules->nbr_philo);
	if (!result->philo_grp)
	{
		printf("Malloc failed\n");
		exit (1);
	}
	x = -1;
	while (++x < rules->nbr_philo)
	{
		result->philo_grp[x].id = x + 1;
		result->philo_grp[x].rules = rules;
	}
	x = -1;
	while (++x < rules->nbr_fork)
	{
		if (x == 0)
		{
			result->philo_grp[x].left_fork = rules->nbr_fork - 1;
			result->philo_grp[x].right_fork = x;
		}
		else if (x == rules->nbr_fork)
		{
			result->philo_grp[x].left_fork = x - 1;
			result->philo_grp[x].right_fork = 0;
		}
		else
		{
			result->philo_grp[x].left_fork = x - 1;
			result->philo_grp[x].right_fork = x;
		}
	}
}


t_group	parsing(int ac, char **av)
{
	t_group	result;
	t_rules	*rules;

	rules = malloc(sizeof(t_rules));
	if (!rules)
		exit(1);
	if (ac < 5 | ac > 6)
		exit (1);
	memset(&result, 0, sizeof(result));
	memset(&rules, 0, sizeof(rules));

	rules->nbr_philo = ft_atoi(av[1]);
	rules->nbr_fork = rules->nbr_philo;
	rules->ttd = ft_atoi(av[2]);
	rules->tte = ft_atoi(av[3]);
	rules->tts = ft_atoi(av[4]);
	if (av[5])
		rules->max_eat = ft_atoi(av[5]);
	if (rules->nbr_philo <= 0 || rules->ttd <= 0 || rules->tte <= 0
		|| rules->tts <= 0 || (av[5] && rules->max_eat <= 0))
		exit(1);
		
	init_fork(rules);
	init_philo(&result, rules);

	printf("in parsing\n");
	print_groups(result);
	
	return (result);
}