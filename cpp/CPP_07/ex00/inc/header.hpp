/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:45:49 by loumouli          #+#    #+#             */
/*   Updated: 2023/01/27 18:01:30 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef HEAD_H
#define HEAD_H
template <typename T>
T	min(T a, T b)
{
	return ((a < b) ? a : b);
}
template <typename T>
T	max(T a, T b)
{
	return ((a > b) ? a : b);
}
template <typename T>
void	swap(T& a, T& b)
{
	T c;
	c = b;
	b = a;
	a = c;
}
#endif