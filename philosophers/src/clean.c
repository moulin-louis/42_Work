/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:15:32 by loumouli          #+#    #+#             */
/*   Updated: 2022/12/22 13:12:39 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

/*Clean the rules struct*/

void	clean_rules(t_rules *rls, int code)
{
	int	x;

	x = rls->nbr_fork;
	while (x)
	{
		x--;
		pthread_mutex_destroy(&(rls->arr_fork[x].lock));
	}
	free(rls->arr_fork);
	if (code == 1)
	{
		pthread_mutex_destroy(&rls->lock_nbr_meal);
		pthread_mutex_destroy(&rls->lock_stop_1);
		pthread_mutex_destroy(&rls->print_mutex);
	}
}

/*Clean all of my struct*/

void	clean_groups(t_group *groups)
{
	if (!groups)
		return ;
	clean_rules(groups->rules, 1);
	free(groups->philo_grp);
	free(groups->id_thread);
}
