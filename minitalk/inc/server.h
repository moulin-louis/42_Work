/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:30:36 by loumouli          #+#    #+#             */
/*   Updated: 2022/09/24 19:13:21 by loumouli         ###   ########.fr       */
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

//struc to build the string
typedef struct s_char {
	unsigned char	temp_char;
	char			*str;
	unsigned int	index;
	unsigned int	len_str;
}			t_char;

//malloc new size, copy old ptr to the new \0 included, free old ptr
char	*ft_realloc_str(char *str, int len);

#endif
