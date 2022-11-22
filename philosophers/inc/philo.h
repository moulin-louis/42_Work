/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:49:01 by loumouli          #+#    #+#             */
/*   Updated: 2022/11/22 17:18:15 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_philo
{
	int				nbr_philo;
	int				nbr_fork;
	int				ttd;
	int				tte;
	int				tts;
	int				nbr_eat;
	pthread_t		*id_philos;
	time_t			c_time;
	time_t			s_time;
	pthread_mutex_t	lock;
	pthread_t		id;
}				t_philo;

typedef struct s_fork
{
	int		is_fork;
}				t_fork;

void	parse_input(int ac, char **av, t_philo *data);
time_t	gettime(void);
void	sleep_philo(int time);

#endif
