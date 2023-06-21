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

void	clean_rules(t_rules *rls)
{
	free(rls->arr_fork);
}

/*Clean all of my struct*/

void	clean_groups(t_group *groups)
{
	if (!groups)
		return ;
	clean_rules(groups->rules);
	free(groups->philo_grp);
	free(groups->id_thread);
}
