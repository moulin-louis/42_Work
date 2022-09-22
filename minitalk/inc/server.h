/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:30:36 by loumouli          #+#    #+#             */
/*   Updated: 2022/09/22 14:23:09 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include<stdio.h>
# include<unistd.h>
# include <sys/types.h>
# include <signal.h>
# include "../ft_printf/inc/ft_printf.h"
# include <stdlib.h>

typedef struct s_char {
	unsigned char	input;
	int		index;
}			t_char;

#endif
