/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:45:55 by loumouli          #+#    #+#             */
/*   Updated: 2022/12/02 19:48:52 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*handle_philo(void	*ptr)
{
	return (ptr);
}

/*print all my struct*/

void	print_groups(t_group groups)
{
	int	x;
	printf("T_GROUP :\n");
	printf("philo_grp = %p\n", groups.philo_grp);
	printf("id_thread = %p\n", groups.id_thread);
	printf("\n");
	printf("\nT_PHILO :\n");
	x = -1;
	if (groups.philo_grp)
	{
		while (++x < groups.philo_grp[0].rules->nbr_philo)
		{
			printf("Philo %d :\n", groups.philo_grp[x].id);
			printf("rules = %p\n", groups.philo_grp[x].rules);
			printf("left_fork = %d\n", groups.philo_grp[x].left_fork);
			printf("right_fork = %d\n", groups.philo_grp[x].right_fork);
			printf("last_meal = %ld\n", groups.philo_grp[x].last_meal);
			printf("nbr_eat = %d\n", groups.philo_grp[x].nbr_eat);
			printf("\n");
		}
		printf("\nT_RULES :\n");
		printf("nbr_philo = %d\n", groups.philo_grp[0].rules->nbr_philo);
		printf("nbr_fork = %d\n", groups.philo_grp[0].rules->nbr_fork);
		printf("ttd = %d\n", groups.philo_grp[0].rules->ttd);
		printf("tte = %d\n", groups.philo_grp[0].rules->tte);
		printf("tts = %d\n", groups.philo_grp[0].rules->tts);
		printf("max_eat = %d\n", groups.philo_grp[0].rules->max_eat);
		printf("arr_fork = %p\n", groups.philo_grp[0].rules->arr_fork);
	}
	x = -1;
	//while (++x < groups.philo_grp[0].rules->nbr_fork)
	//	printf("arr_fork[%d] : taken = %d\n", x, groups.philo_grp[0].rules->arr_fork[x].taken);
	printf("\n");
}

int	main(int ac, char **av)
{
	t_group	groups;

	groups = parsing(ac, av);
	//printf("nbr philo = %d\n", groups.philo_grp[0].rules->nbr_philo);
	(void)groups;
	//print_groups(groups);
	return (0);
}
