/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 15:55:43 by ldutriez          #+#    #+#             */
/*   Updated: 2022/07/23 15:58:14 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "retromfa.h"

void	quit_mlx(t_mlx *mlx, int exit_code)
{
	mlx_destroy_image(mlx->mlx, mlx->img.img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	mlx->mlx = NULL;
	exit(exit_code);
}