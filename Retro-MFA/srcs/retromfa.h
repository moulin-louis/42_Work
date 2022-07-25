/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retromfa.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 12:25:30 by ldutriez          #+#    #+#             */
/*   Updated: 2022/07/24 12:46:58 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RETROMFA_RETROMFA_H
#define RETROMFA_RETROMFA_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "mlx.h"
#include "libft_lists.h"

typedef struct s_int2
{
	int	x;
	int	y;
}			t_int2;

//? PARSING

/**
 * @brief Display a usage message in stderr.
 * @param binary_name The name of the binary. (av[0])
 * @return EXIT_FAILURE
 */
int display_usage(const char *binary_name);

/**
 * @brief Check if the arguments are valid.
 * @param ac The number of arguments.
 * @param av The arguments value.
 * @return EXIT_FAILURE on error, EXIT_SUCCESS on otherwise.
 */
int is_correct_usage(int ac, char *av[]);

//? DATA HANDLING

typedef struct s_b_data
{
	char *data;
	__off_t size;
	int	width;
	int	height;
	int	type;
} t_b_data;

/**
 * @brief Reads the file and returns the data and the size
 * 
 * @param file_name The path to the file
 * @return t_b_data struct with the data and the size
 */
t_b_data read_file(char *file_name);

/**
 * @brief Extracts the image from the mfa file
 * 
 * @param b_file The mfa file
 * @return t_list The list of images
 */
t_list extract_0x06_images_from_file(t_b_data *binary_file, t_int2 *max_size);

/**
 * @brief Extracts the image from the mfa file
 * 
 * @param b_file The mfa file
 * @return t_list The list of images
 */
t_list extract_0x04_images_from_file(t_b_data *binary_file, t_int2 *max_size);

/**
 * @brief Extracts the bmps from the binary file
 * 
 * @param b_file The binary file
 * @return t_list The list of bmps
 */
t_list extract_bmps_from_binary_file(t_b_data *binary_file);

/**
 * @brief Search for the bmp header in the binary file.
 * 
 * @param binary_file binary file to search in.
 * @return t_b_data The bmp file extracted from the binary file.
 */
t_b_data extract_bmp_from_binary_file(t_b_data *binary_file);

//? RENDERING

#define W_WIDTH 1920
#define W_HEIGHT 1080
#define ESC 65307

/**
 * @brief Create a new t_int2 with the given value.
 * 
 * @return t_int2 The new created struct.
 */
t_int2	make_int2(int y, int x);

typedef struct s_color
{
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned int	code;
}					t_color;

typedef struct s_img
{
	void *img;
	char *addr;
	int bits_pxl;
	int line_len;
	int endian;
	// t_int2	size;
} t_img;

typedef struct s_mlx
{
	void *mlx;
	void *win;
	t_img img;
} t_mlx;

/**
 * @brief Create a new t_color struct with the given value.
 * 
 * @return t_color The new created struct.
 */
t_color make_color(unsigned char a,
						  unsigned char r, unsigned char g, unsigned char b);

/**
 * @brief Put a color in mlx->img.addr at pos.y * W_WIDTH + pos.x.
 * 
 * @param mlx The rendering target.
 * @param pos Where to put the color.
 * @param color The color to put.
 */
void draw_pxl(t_mlx *mlx, t_int2 pos, t_color color);

/**
 * @brief Draw the given bmp file in mlx->img.
 * 
 * @param mlx The rendering target.
 * @param bmp_file The bmp stored in a t_b_data struct.
 */
void draw_bmp(t_mlx *mlx, t_b_data *bmp_file);

/**
 * @brief Draw the given mfa file in mlx->img.
 * 
 * @param mlx The rendering target.
 * @param bmp_file The mfa image stored in a t_b_data struct.
 */
void draw_mfa_image(t_mlx *mlx, t_b_data *bmp_file, t_int2 *max_size);

/**
 * @brief Init the mlx [window|rander|image].
 *
 * @param window_name The name that will be displayed on the window.
 * @return t_mlx A copy of the initialized structure.
 */
t_mlx init_mlx(char window_name[10]);

/**
 * @brief Quit properly the mlx.
 *
 * @param mlx The structure to free.
 * @param exit_code What will be given to exit.
 */
void quit_mlx(t_mlx *mlx, int exit_code);

/**
 * @brief What will handle the update, events and such.
 *
 * @param mlx The structure to update.
 * @param bmp_file The bmp file to render.
 */
void	mlx_routine(t_mlx *mlx, t_list bmp_file, t_int2 *max_size);

#endif // RETROMFA_RETROMFA_H