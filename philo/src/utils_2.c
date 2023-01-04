/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 19:35:11 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/03 18:04:25 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

/*Printf with a mutex to avoid overlaping*/

void	printf_mutex(t_rules *rules, char *action, long int actuel_time,
		int id_philo)
{
	if (check_stop(rules))
	{
		pthread_mutex_lock(&rules->print_mutex);
		if (check_stop(rules))
			printf("%ld %d %s\n", actuel_time - rules->start_timestamp,
				id_philo, action);
		pthread_mutex_unlock(&rules->print_mutex);
	}
}
