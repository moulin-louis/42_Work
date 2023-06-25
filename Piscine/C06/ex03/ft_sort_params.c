/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 09:46:36 by loumouli          #+#    #+#             */
/*   Updated: 2022/02/13 09:56:39 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

int	ft_strlen(char *str)
{
	int	a;

	a = 0;
	while (str[a] != '\0')
	{
		a++;
	}
	return (a);
}

void	ft_print(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		write(1, argv[i], ft_strlen(argv[i]));
		write(1, "\n", 1);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		i;
	int		j;
	char	*temp;

	i = 1;
	if (argc == 1)
		return (0);
	while (argv[i])
	{
		j = i + 1;
		while (j < argc)
		{
			if (ft_strcmp(argv[i], argv[j]) > 0)
			{
				temp = argv[i];
				argv[i] = argv[j];
				argv[j] = temp;
			}
			j++;
		}
		i++;
	}
	ft_print(argc, argv);
	return (0);
}
