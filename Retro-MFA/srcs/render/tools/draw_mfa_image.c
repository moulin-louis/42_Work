/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mfa_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 03:22:52 by ldutriez          #+#    #+#             */
/*   Updated: 2022/07/24 16:00:47 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "retromfa.h"

void draw_mfa_image(t_mlx *mlx, t_b_data *bmp_file, t_int2 *max_size)
{
	static int offset_x = 0;
	static int offset_y = 0;
	int start;
	int width;
	int height;
	int color_offset;

	if (bmp_file == NULL)
	{
		offset_x = 0;
		offset_y = 0;
		return;
	}
	color_offset = (bmp_file->type == 6) ? 2 : 3;
	if (offset_x + bmp_file->width >= W_WIDTH)
	{
		offset_x = 0;
		offset_y = (max_size->y > 200) ? offset_y + 200 : offset_y + max_size->y;
		// offset_y += max_size->y;
	}
	start = (bmp_file->type == 6) ? 15 : 14;
	width = bmp_file->width;
	height = bmp_file->height;
	for (int y = 0; y < height; ++y)
		for (int x = 0; x < width; ++x)
		{
			int index = start + ((y * width + x) * color_offset);
			void *addr = bmp_file->data + index;
			if (bmp_file->type == 6)
			{
				short int color_c = *(short int *)addr;
				char r = (color_c >> 10) & 0xFF;
				char g = (color_c >> 5) & 0xFF;
				char b = (color_c >> 0) & 0xFF;
				r *= 8;
				g *= 8;
				b *= 8;
				t_color color = make_color(0, r, g, b);
				if (color.code == 0)
					continue;
				draw_pxl(mlx, make_int2(y + offset_y, x + offset_x), color);
			}
			else
			{
				int color_c = *(int *)addr;
				color_c = (color_c << 8) & 0xFFFFFF00;
				char r = (color_c >> 24) & 0xFF;
				char g = (color_c >> 16) & 0xFF;
				char b = (color_c >> 8) & 0xFF;
				t_color color = make_color(0, r, g, b);
				if (color.code == 0)
					continue;
				draw_pxl(mlx, make_int2(y + offset_y, x + offset_x), color);
			}
		}
	// offset_x += max_size->x;
	offset_x = (max_size->x > 200) ? offset_x + 200 : offset_x + max_size->x;
}
