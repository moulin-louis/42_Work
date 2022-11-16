/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:45:55 by loumouli          #+#    #+#             */
/*   Updated: 2022/11/16 16:30:06 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int				counter = 5;
pthread_mutex_t	lock;


void	*thread_stuff(void *ptr)
{
	pthread_mutex_lock(&lock);
	printf("counter = %d\n", counter);
	counter--;
	pthread_mutex_unlock(&lock);
	return ptr;
}

int	main(int ac, char **av)
{
	//t_philo		data;
	pthread_t			id[50];

	(void)ac;
	(void)av;
	// memset(&data, 0, sizeof(data));
	// parse_input(ac, av, &data);
	memset(id, 0, sizeof(id));
	pthread_mutex_init(&lock, NULL);
	int x = -1;
	while (++x < 5)
		pthread_create(&(id[x]), NULL, &thread_stuff, NULL);
	void **temp = NULL;
	pthread_join(id[0], temp);
	pthread_join(id[1], temp);
	pthread_join(id[2], temp);
	pthread_join(id[3], temp);
	pthread_join(id[4], temp);
	(void)temp;
	pthread_mutex_destroy(&lock);
	return 0;
}
