/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:15:32 by loumouli          #+#    #+#             */
/*   Updated: 2022/12/19 17:05:15 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Clean the rules struct*/

void	clean_rules(t_rules *rls)
{
	int	x;

	x = rls->nbr_fork;
	while (x)
	{
		x--;
		pthread_mutex_destroy(&(rls->arr_fork[x].lock));
	}
	pthread_mutex_destroy(&rls->lock_nbr_meal);
	pthread_mutex_destroy(&rls->lock_stop_1);
	pthread_mutex_destroy(&rls->print_mutex);
	free(rls->arr_fork);
	free(rls);
}

/*Clean all of my struct*/

void	clean_groups(t_group *groups)
{
	if (!groups)
		return ;
	if (groups->philo_grp)
		clean_rules(groups->philo_grp[0].rules);
	free(groups->philo_grp);
	free(groups->id_thread);
}
