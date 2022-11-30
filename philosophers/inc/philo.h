/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:49:01 by loumouli          #+#    #+#             */
/*   Updated: 2022/11/30 18:03:49 by loumouli         ###   ########.fr       */
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

typedef struct	s_fork
{
	pthread_mutex_t	lock;
	int				taken;
}				t_fork;

typedef struct	s_rules
{
	int		nbr_philo;
	int		nbr_fork;
	int		ttd;
	int		tte;
	int		tts;
	int		max_eat;
	t_fork	*arr_fork;
}				t_rules;

typedef struct s_philo
{
	int		id;
	t_rules	*rules;
	int		left_fork;
	int		right_fork;
	time_t	last_meal;
	int		nbr_eat;
}				t_philo;

typedef struct	s_group
{
	t_philo		*philo_grp;
	pthread_t	*id_thread;
}				t_group;

t_group	parsing(int ac, char **av);
time_t	gettime(void);
void	sleep_philo(int time);
int	ft_atoi(const char *str);
void	print_groups(t_group groups);
#endif
