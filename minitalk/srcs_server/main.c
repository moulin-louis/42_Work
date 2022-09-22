/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:36:43 by loumouli          #+#    #+#             */
/*   Updated: 2022/09/22 15:09:06 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/server.h"

t_char temp;

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	handle_sig(int sig)
{
	(void)sig;
	if (sig == SIGUSR2)
		temp.input |= 1 << temp.index;
	temp.index++;
	if (temp.index == 8)
	{
		ft_putchar(temp.input);
		temp.index = 0;
		temp.input = 0;
	}
}

void	ft_do_nothing(pid_t pid_prgm)
{
	(void)pid_prgm;
}

int	main(void)
{
	pid_t				pid_prgm;
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handle_sig;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid_prgm = getpid();
	ft_printf("pid of server is = %d\n", pid_prgm);
	while (1)
	{
		ft_do_nothing(pid_prgm);
	}
	return (0);
}
