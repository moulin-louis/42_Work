/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:36:43 by loumouli          #+#    #+#             */
/*   Updated: 2022/09/24 22:36:00 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/server.h"

t_char	g_data;

unsigned char	reverse_bits(unsigned char b)
{
	unsigned char	r;
	unsigned int	byte_len;

	byte_len = 8;
	r = 0;
	while (byte_len--)
	{
		r = (r << 1) | (b & 1);
		b >>= 1;
	}
	return (r);
}

void	ft_add_char(void)
{
	int	i;

	i = 0;
	while (g_data.str[i])
		i++;
	g_data.str[i] = g_data.temp_char;
	g_data.str[i + 1] = '\0';
}

void	handle_sig(int sig)
{
	if (g_data.index < 8)
	{
		if (sig == SIGUSR2)
			g_data.temp_char |= 1 << g_data.index;
		g_data.index++;
	}
	if (g_data.index == 8)
	{
		g_data.str = ft_realloc_str(g_data.str, g_data.len_str);
		g_data.temp_char = reverse_bits(g_data.temp_char);
		ft_add_char();
		g_data.index = 0;
		if (g_data.temp_char)
			g_data.len_str++;
		else if (g_data.temp_char == '\0')
		{
			ft_printf("%s", g_data.str);
			free(g_data.str);
			g_data.len_str = 1;
			g_data.str = NULL;
		}
		g_data.temp_char = 0;
	}
}

int	main(void)
{
	pid_t				pid_prgm;
	struct sigaction	sa;

	g_data.len_str = 1;
	g_data.str = NULL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handle_sig;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid_prgm = getpid();
	ft_printf("pid of server is = %d\n", pid_prgm);
	while (1)
		pause();
	return (0);
}
