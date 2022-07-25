/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 12:22:50 by ldutriez          #+#    #+#             */
/*   Updated: 2022/07/24 12:47:29 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "retromfa.h"
#include "libft_files.h"
#include <strings.h>

static void log_file(t_b_data *b_file)
{
	FILE *log_file = fopen("retromfa.log", "w+");
	if (log_file == NULL)
	{
		dprintf(2, "Error\nUnable to open the mfa file\n");
		exit(1);
	}
	fwrite(b_file->data, sizeof(char), b_file->size, log_file);
}

int main(int ac, char *av[])
{
	t_mlx mlx;
	t_b_data binary_file;
	t_list img_list;
	t_int2 max_size;

	if (is_correct_usage(ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	bzero(&max_size, sizeof(t_int2));
	binary_file = read_file(av[1]);
	img_list = extract_0x06_images_from_file(&binary_file, &max_size);
	if (img_list == NULL)
	{
		bzero(&max_size, sizeof(t_int2));
		img_list = extract_0x04_images_from_file(&binary_file, &max_size);
	}
	if (img_list == NULL)
	{
		free(binary_file.data);
		dprintf(2, "Error\nNo image found in the mfa file\n");
		return (EXIT_FAILURE);
	}
	log_file((t_b_data *)img_list->data);

	mlx = init_mlx("Retro-MFA");
	mlx_routine(&mlx, img_list, &max_size);
	free(binary_file.data);
	quit_mlx(&mlx, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}