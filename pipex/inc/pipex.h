/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 14:42:42 by loumouli          #+#    #+#             */
/*   Updated: 2022/09/09 15:45:28 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib/ft_printf/inc/ft_printf.h"
# include "../lib/libft/inc/libft.h"
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

typedef struct s_data
{
	int		pid1;
	int		pid2;
	int		fd_infile;
	int		fd_outfile;
	int		io_pipe[2];
	char	**env;
}	t_data;

void	ft_close_stuff(int fd_in, int fd_out, int io_pipe[2]);
int		ft_open(t_data *data, char **av);
int		ft_init_data(t_data *data, char **av, char **env);

char	**ft_get_path(char **env);
char	*ft_check_access(char **path, char *command);

#endif
