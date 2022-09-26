/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:36:43 by loumouli          #+#    #+#             */
/*   Updated: 2022/09/25 17:10:01 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/client.h"

void	get_binary_string(char *s, int pid)
{
	int		j;
	int		i;

	if (s == NULL)
		return ;
	i = -1;
	while (s[++i])
	{
		j = -1;
		while (++j < 8)
		{
			if (s[i] & (1 << j))
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(300);
		}
	}
	i = 0;
	while (i < 8)
	{
		kill(pid, SIGUSR1);
		usleep(300);
		i++;
	}
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		minus;
	long	result;

	i = 0;
	minus = 1;
	result = 0;
	if (nptr[i] == '-')
		minus = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	result = result * minus;
	return ((int)result);
}

int	main(int ac, char **av)
{
	int		pid;

	if (ac != 3)
		return (ft_printf("gib ./minitalk_client pid string\n"), -1);
	pid = ft_atoi(av[1]);
	if (pid <= 0)
		return (1);
	get_binary_string(av[2], pid);
}
