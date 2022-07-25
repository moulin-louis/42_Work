/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pxl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 18:28:46 by ldutriez          #+#    #+#             */
/*   Updated: 2022/07/23 18:28:57 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "retromfa.h"

void draw_pxl(t_mlx *mlx, t_int2 pos, t_color color)
{
	int *tmp;

	if (pos.x < 0 || pos.x > W_WIDTH || pos.y < 0 || pos.y > W_HEIGHT)
		return;
	tmp = (int *)mlx->img.addr;
	tmp[(pos.y * W_WIDTH) + pos.x] = color.code;
}
