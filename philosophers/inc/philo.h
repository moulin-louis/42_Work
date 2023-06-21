/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:49:01 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/04 13:17:58 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

/*struc for fork, contain a mutex to lock the fork and a bool to tell
if the fork is taken*/

typedef struct s_fork {
	_Atomic int				taken;
}				t_fork;

/*Conain the rules input by the user and an array of struct of fork*/

typedef struct s_rules
{
	int				nbr_philo;
	int				nbr_fork;
	time_t			ttd;
	int				tte;
	int				tts;
	int				max_eat;
	int				nbr_thread_launched;
	_Atomic int				trigger_stop;
	long int		start_timestamp;
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
	_Atomic time_t	last_meal;
	_Atomic int		nbr_eat;
}				t_philo;

/*main struc, contain an array of philo struct and an array of thread id*/

typedef struct s_group
{
	t_philo		*philo_grp;
	pthread_t	*id_thread;
	t_rules		*rules;
	pthread_t	id_superviser;
}				t_group;

void	start_philo(t_group *groups);

/*Parsing*/
void	parsing_n_init(int ac, char **av);
int		set_rules(t_rules *rules, char **av);
int		init_philo(t_group *groups, t_rules *rules);

/*Eating fn*/
void	go_eat(t_philo *philo);

/*Supervisor */
int		check_stop(t_rules *rules);
void	*check_end(void *ptr);

/*Utils*/
time_t	gettime(void);
void	sleep_philo(int time, t_rules *rules);
time_t	get_tthk(t_rules *rules, t_philo *philo);
int		ft_atoi(const char *str);
void	printf_mutex(t_rules *rules, char *action, long int actuel_time,
			int id_philo);

/*Clean*/
void	clean_groups(t_group *groups);
void	clean_rules(t_rules *rls);
#endif
