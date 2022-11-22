/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:45:55 by loumouli          #+#    #+#             */
/*   Updated: 2022/11/22 17:23:33 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*handle_philo(void	*ptr)
{

}


int	main(int ac, char **av)
{
	t_philo			data;
	int				x;

	x = 0;
	memset(&data, 0, sizeof(data));
	parse_input(ac, av, &data);
	printf("nbr of philo = %d\nnbr of fork = %d\ntime_to_die = %d\ntime_to_eat = %d\ntime_to_sleep = %d\nnbr_to_eat = %d\n", data.nbr_philo, data.nbr_fork, data.ttd, data.tte, data.tts, data.nbr_eat);
	data.id_philos = malloc(sizeof(pthread_t *) * (data.nbr_philo + 1));
	if (!data.id_philos)
		return (perror("Malloc "), 2);
	while (x < data.nbr_philo)
	{
		pthread_create(&data.id_philos[x], NULL, &handle_philo, &data);
		x++;
	}
	return (0);
}
