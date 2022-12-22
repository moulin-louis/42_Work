/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 19:35:11 by loumouli          #+#    #+#             */
/*   Updated: 2022/12/22 13:14:33 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

/*Check if all thread has launched*/

int	check_start(t_rules *rules)
{
	pthread_mutex_lock(&rules->lock_nbr_thread);
	if (rules->nbr_thread_launched == rules->nbr_philo)
		return (pthread_mutex_unlock(&rules->lock_nbr_thread), 1);
	if (rules->nbr_thread_launched == -1)
		return (pthread_mutex_unlock(&rules->lock_nbr_thread), 2);
	pthread_mutex_unlock(&rules->lock_nbr_thread);
	return (0);
}

/*Printf with a mutex to avoid overlaping*/

void	printf_mutex(t_rules *rules, char *action, long int actuel_time,
		int id_philo)
{
	pthread_mutex_lock(&rules->print_mutex);
	if (check_stop(rules))
		printf("%ld %d %s\n", actuel_time - rules->start_timestamp,
			id_philo, action);
	pthread_mutex_unlock(&rules->print_mutex);
}
