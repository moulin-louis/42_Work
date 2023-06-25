/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:04:19 by loumouli          #+#    #+#             */
/*   Updated: 2022/02/15 11:14:37 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_whitespace(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	else
		return (0);
}

int	ft_is_minus_or_plus(char c, int *ptrminus)
{
	if (c == '+' || c == '-')
	{
		if (c == '-')
			*ptrminus = *ptrminus + 1;
		return (1);
	}
	else
		return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	digit;
	int	*ptrminus;
	int	minus;

	digit = 0;
	i = 0;
	minus = 0;
	ptrminus = &minus;
	while (ft_is_whitespace(str[i]))
		i++;
	while (ft_is_minus_or_plus(str[i], ptrminus))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = digit * 10 + (str[i] - '0' );
		i++;
	}
	if (*ptrminus % 2 != 0)
		digit = digit * -1;
	return (digit);
}
