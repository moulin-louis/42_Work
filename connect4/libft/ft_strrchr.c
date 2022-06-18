/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:33:11 by marnaudy          #+#    #+#             */
/*   Updated: 2021/11/24 12:19:42 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	char			*found;

	found = 0;
	i = 0;
	while (1)
	{
		if (s[i] == (char) c)
			found = (char *) s + i;
		if (s[i] == 0)
			return (found);
		i++;
	}
}
