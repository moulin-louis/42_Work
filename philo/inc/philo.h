/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:49:01 by loumouli          #+#    #+#             */
/*   Updated: 2022/12/17 00:33:19 by loumouli         ###   ########.fr       */
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

/*struc for fork, contain a mutex to lock the fork and a bool to tell
if the fork is taken*/

typedef struct s_fork
{
	pthread_mutex_t	lock;
	int				taken;
}				t_fork;

/*Conain the rules input by the user and an array of struct of fork*/

typedef struct s_rules
{
	int				nbr_philo;
	int				nbr_fork;
	int				ttd;
	int				tte;
	int				tts;
	int				max_eat;
	int				trigger_stop;
	long int		start_timestamp;
	pthread_mutex_t	lock_nbr_meal;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	lock_stop_1;
	t_fork			*arr_fork;
}				t_rules;

/*A struct for each philo, contain a ptr to the rules, its own id, id for
their fork and the timestamp of the last meal taken*/

typedef struct s_philo
{
	int		id;
	t_rules	*rules;
	int		left_fork;
	int		right_fork;
	time_t	last_meal;
	int		nbr_eat;
}				t_philo;

/*main struc, contain an array of philo struct and an array of thread id*/

typedef struct s_group
{
	t_philo		*philo_grp;
	pthread_t	*id_thread;
	t_rules		*rules;
	pthread_t	id_superviser;
}				t_group;

/*Parsing*/
t_group	parsing_n_init(int ac, char **av);

/*Eating fn*/
void	go_eat(t_philo *philo);

/*Fn to check end of simulation*/
void	*check_end(void *ptr);

/*Utils*/
time_t	gettime(void);
void	sleep_philo(int time, t_rules *rules);
int		ft_atoi(const char *str);
void	print_groups(t_group groups);
int		print_clean_n_quit(char *str, t_group *groups, int error_code);
void	printf_mutex(t_rules *rules, char *action, long int actuel_time,
			int id_philo);
int		check_stop(t_rules *rules);

/*Clean*/
void	clean_groups(t_group *groups);
#endif
