/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:48:45 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/27 17:42:00 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_io.h"

void	ft_putstr(char *str)
{
	if (str == NULL)
		return ;
	write(1, str, ft_strlen(str));
}
