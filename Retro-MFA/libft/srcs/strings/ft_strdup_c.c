/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strduc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoudsi <ncoudsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 13:57:19 by ncoudsi           #+#    #+#             */
/*   Updated: 2019/12/02 18:03:36 by ncoudsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_strings.h"

char	*ft_strdup_c(char c)
{
	char	*result;

	result = ft_strnew(1);
	if (result == NULL)
		return (NULL);
	result[0] = c;
	return (result);
}
