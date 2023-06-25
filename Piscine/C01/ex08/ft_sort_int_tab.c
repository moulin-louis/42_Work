/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 16:57:05 by loumouli          #+#    #+#             */
/*   Updated: 2022/02/06 15:28:26 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_swap(int j, int i, int *tab)
{
	int	swap;

	swap = tab[j];
	tab[j] = tab[i];
	tab[i] = swap;
}

void	ft_sort_int_tab(int *tab, int size)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	if (size == 1)
		return ;
	while (j < size -1)
	{
		while (i < size)
		{
			if (tab[j] > tab[i])
			{
				ft_swap(j, i, tab);
				i = j +1;
			}
			else
				i++;
		}
		j++;
		i = j + 1;
	}
}
