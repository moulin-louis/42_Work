/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:45:55 by loumouli          #+#    #+#             */
/*   Updated: 2022/11/16 18:00:36 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*day_of_philo(void *ptr)
{
	t_philo	*data;

	data = (t_philo *)ptr;

	pthread_mutex_lock(&data->lock);
	gettimeofday(&data->tv, NULL);
	printf("%ld : philo has taken a fork", data->tv.tv_usec);
	pthread_mutex_unlock(&data->lock);
	return NULL;
}

int	main(int ac, char **av)
{
	t_philo			data;
	pthread_t		id;

	gettimeofday(&data.tv, NULL);
	memset(&data, 0, sizeof(data));
	parse_input(ac, av, &data);
	pthread_create(&id, NULL, &day_of_philo, (void *)&data);
	return 0;
}
