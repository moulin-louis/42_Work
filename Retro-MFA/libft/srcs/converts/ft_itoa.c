/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:30:21 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/28 03:53:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_converts.h"

char	*ft_itoa(long long int nbr)
{
	char	*base;
	char	*result;

	base = "0123456789";
	result = ft_itoa_base(nbr, base);
	return (result);
}
