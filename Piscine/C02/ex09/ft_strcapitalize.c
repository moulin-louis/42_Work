/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:14:34 by loumouli          #+#    #+#             */
/*   Updated: 2022/02/08 15:53:47 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_alpha(char str)
{
	if (str >= '0' && (str <= '9' || str >= 'A')
		&& (str <= 'Z' || str >= 'a') && str <= 'z')
		return (1);
	return (0);
}

char	*ft_strcapitalize(char *str)
{
	int	i;

	i = 1;
	if (str[i - 1] >= 'a' && str[i - 1] <= 'z')
		str[i - 1] = str[i - 1] - 32;
	while (str [i])
	{
		if (ft_str_is_alpha(str[i - 1]))
		{
			if (str[i] >= 'A' && str[i] <= 'Z')
				str[i] = str[i] + 32;
		}
		else if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
		i++;
	}
	return (str);
}
