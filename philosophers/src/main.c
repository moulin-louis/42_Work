/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:45:55 by loumouli          #+#    #+#             */
/*   Updated: 2022/12/15 15:33:14 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Start all routine for the given thread*/

void	*handle_philo(void	*ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (!philo->rules->trigger_stop)
	{
		go_eat(philo);
		sleep_philo(philo->rules->tts, philo->rules);
		printf("%ld philo %d is thinking\n", gettime(), philo->id);
	}
	return (ptr);
}

/*Launch all philo thread and the superviser one, wait for each thread to end*/

void	start_philo(t_group *groups)
{
	int	x;

	x = -1;
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
	start_philo(&groups);
	clean_groups(&groups);
	return (0);
}
