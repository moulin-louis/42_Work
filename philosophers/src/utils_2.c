/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 19:35:11 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/07 13:21:49 by loumouli         ###   ########.fr       */
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
		if (check_stop(rules))
			printf("%ld %d %s\n", actuel_time - rules->start_timestamp, id_philo, action);
	}
}

/*Calculate time to think for each philo
Mean to avoid egoist philo*/

time_t	get_tthk(t_rules *rules, t_philo *philo)
{
	time_t	result_ms;

	result_ms = (rules->ttd - (gettime() - philo->last_meal) - rules->tte) / 2;
	if (result_ms > 500)
		result_ms = 500;
	if (result_ms <= 0)
		result_ms = 1;
	return (result_ms);
}
