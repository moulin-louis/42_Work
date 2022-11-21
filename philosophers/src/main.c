/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:45:55 by loumouli          #+#    #+#             */
/*   Updated: 2022/11/21 15:16:46 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*day_of_philo(void *ptr)
{
	t_philo	*data;
	time_t	end_time;
	time_t	start_time;
	//time_t	timestamp;

	data = (t_philo *)ptr;
	end_time = gettime() + data->ttd;
	start_time = gettime();

	// timestamp = gettime();
	// printf("%ld : philo has taken a fork\n", timestamp);
	// timestamp = gettime();
	// printf("%ld : philo is eating\n", timestamp);
	// usleep(data->tte);
	// timestamp = gettime();
	// printf("%ld : philo is sleaping\n", timestamp);
	// usleep(data->tts);

	while (gettime() < end_time)
	{
		printf("%ld has passed\n", gettime() - start_time);
		sleep_philo(2000);
	}
	return NULL;
}

int	main(int ac, char **av)
{
	t_philo			data;

	memset(&data, 0, sizeof(data));
	parse_input(ac, av, &data);
	printf("nbr of philo = %d\nnbr of fork = %d\ntime_to_die = %d\ntime_to_eat = %d\ntime_to_sleep = %d\n", data.nbr_philo, data.nbr_fork, data.ttd, data.tte, data.tts);
	pthread_create(&data.id, NULL, &day_of_philo, (void *)&data);
	pthread_join(data.id, NULL);
	return 0;
}
