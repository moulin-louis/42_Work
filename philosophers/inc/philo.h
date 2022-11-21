/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:49:01 by loumouli          #+#    #+#             */
/*   Updated: 2022/11/16 17:55:56 by loumouli         ###   ########.fr       */
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
	struct timeval	tv;
	pthread_mutex_t	lock;
}			t_philo;

void	parse_input(int ac, char **av, t_philo *data);

#endif
