/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 18:30:54 by ldutriez          #+#    #+#             */
/*   Updated: 2022/07/23 19:26:08 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "retromfa.h"

void draw_bmp(t_mlx *mlx, t_b_data *bmp_file)
{
	int start;
	int width;
	int height;
	void *addr = bmp_file->data + 18;

	start = bmp_file->data[10];
	width = *(int *)addr;
	addr += 4;
	height = *(int *)addr;
	for (int y = 0; y < height; ++y)
		for (int x = 0; x < width; ++x)
		{
			int index = start + ((height - y) * width + x) * 4;
			t_color color = make_color(bmp_file->data[index + 3],
									  bmp_file->data[index + 2],
									  bmp_file->data[index + 1],
									  bmp_file->data[index]);
			draw_pxl(mlx, make_int2(y, x), color);
		}
}