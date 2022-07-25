/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_octa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:36:45 by ncoudsi           #+#    #+#             */
/*   Updated: 2021/05/27 17:25:24 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_converts.h"

char	*ft_itoa_octa(long long int nbr)
{
	char	*base;
	char	*result;

	base = "01234567";
	result = ft_itoa_base(nbr, base);
	return (result);
}
