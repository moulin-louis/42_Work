/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:31:15 by loumouli          #+#    #+#             */
/*   Updated: 2022/12/17 00:33:13 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*printf the error, clean the heap and exit program with the error_code */

int	print_clean_n_quit(char *str, t_group *groups, int error_code)
{
	printf("%s", str);
	clean_groups(groups);
	exit (error_code);
}

/*Convert string input into int*/

int	ft_atoi(const char *str)
{
	int	nbr;
	int	i;

	nbr = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
	}
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + *str - 48;
		str++;
	}
	return (nbr);
}

/*custom sleep fn to avoid usleep delay*/

void	sleep_philo(int time, t_rules *rules)
{
	time_t	end_time;

	end_time = gettime() + time;
	while (check_stop(rules) && gettime() < end_time)
		usleep(100);
}

/*get current timestamp*/

time_t	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/*Printf with a mutex to avoid overlaping*/

void	printf_mutex(t_rules *rules, char *action, long int actuel_time,
		int id_philo)
{
	pthread_mutex_lock(&rules->print_mutex);
	if (check_stop(rules))
		printf("%ld %d %s\n", actuel_time - rules->start_timestamp, id_philo, action);
	pthread_mutex_unlock(&rules->print_mutex);
}
