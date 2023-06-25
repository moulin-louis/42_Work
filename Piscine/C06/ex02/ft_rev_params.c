/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 09:29:41 by loumouli          #+#    #+#             */
/*   Updated: 2022/02/12 17:21:37 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr(char *str)
{
	unsigned int	a;

	a = 0;
	while (str[a])
	{
		write(1, &str[a], 1);
		a++;
	}
}

int	main(int argc, char **argv)
{
	int	i;

	i = argc - 1;
	while (i != 0)
	{
		ft_putstr(argv[i]);
		i--;
		write(1, "\n", 1);
	}
	return (argc);
}
