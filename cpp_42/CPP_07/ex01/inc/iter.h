/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:04:31 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/27 18:16:29 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef ITER_H
#define ITER_H

#include <iostream>
template<typename T, typename G, typename H>
void	iter(T* ptr_arr, G len_arr, H ptr_fn)
{
	G temp = 0;
	while(temp < len_arr)
	{
		ptr_fn(ptr_arr[temp]);
		temp++;
	}
}
#endif