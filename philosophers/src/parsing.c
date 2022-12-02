/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:28:07 by loumouli          #+#    #+#             */
/*   Updated: 2022/12/02 23:31:13 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <errno.h>

/*Malloc an array of x fork and init mutex for each fork*/
void	init_fork(t_rules *rules, t_group *groups)
{
	int	x;	

	rules->arr_fork = malloc(sizeof(t_fork) * rules->nbr_fork);
	if (!rules->arr_fork)
		print_clean_n_quit("Malloc failed\n", groups, errno);
	x = -1;
	while (++x < rules->nbr_philo)
	{
		if (pthread_mutex_init(&(rules->arr_fork[x].lock), NULL))
			print_clean_n_quit("Mutex init failed\n", groups, errno);
		rules->arr_fork[x].taken = 0;
	}
}

/*fill t_rules stuct with user input*/
void	set_rules(t_rules *rules, t_group *groups, char **av)
{
	rules->nbr_philo = ft_atoi(av[1]);
	rules->nbr_fork = rules->nbr_philo;
	rules->tte = ft_atoi(av[2]);
	rules->tts = ft_atoi(av[3]);
	rules->ttd = ft_atoi(av[4]);
	if (av[5])
		rules->max_eat = ft_atoi(av[5]);
	if (av[5])
		rules->max_eat = ft_atoi(av[5]);
	if (rules->nbr_philo <= 0 || rules->ttd <= 0 || rules->tte <= 0
		|| rules->tts <= 0 || (av[5] && rules->max_eat <= 0))
		print_clean_n_quit("Gib valid nbr", groups, 1);
	init_fork(rules, groups);
}

/*Init fork id*/
void	init_fork_id_in_philo(t_group *groups, t_rules *rules)
{
	int	x;

	x = -1;
	while (++x < rules->nbr_fork)
	{
		if (x == 0)
		{
			groups->philo_grp[x].left_fork = rules->nbr_fork - 1;
			groups->philo_grp[x].right_fork = x;
		}
		else if (x == rules->nbr_fork)
		{
			groups->philo_grp[x].left_fork = x - 1;
			groups->philo_grp[x].right_fork = 0;
		}
		else
		{
			groups->philo_grp[x].left_fork = x - 1;
			groups->philo_grp[x].right_fork = x;
		}
	}
}

/*malloc an array of x t_philos and init each of them : fill forks id and point to
the right t_rules struct*/
void	init_philo(t_group *groups, char **av)
{
	int		x;
	t_rules	rules;

	memset(&rules, 0, sizeof(rules));
	set_rules(&rules, groups, av);

	groups->philo_grp = malloc(sizeof(t_philo) * rules.nbr_philo);
	if (!groups->philo_grp)
		print_clean_n_quit("Malloc failed\n", groups, errno);
	memset(groups->philo_grp, 0, sizeof(t_philo) * rules.nbr_philo);

	x = -1;
	while (++x < rules.nbr_philo)
	{
		groups->philo_grp[x].id = x + 1;
		groups->philo_grp[x].rules = &rules;
	}

	init_fork_id_in_philo(groups, &rules);
}

/*check compliance and call init fn*/

t_group	parsing(int ac, char **av)
{
	t_group	groups;

	if (ac < 5 || ac > 6)
		print_clean_n_quit("Wrong nbr of args\n", NULL, 1);
	memset(&groups, 0, sizeof(groups));	
	init_philo(&groups, av);
	printf("nbr philo = %d\n", groups.philo_grp[0].rules->nbr_philo);
	return (groups);
}
