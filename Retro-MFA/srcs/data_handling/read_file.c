/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 17:02:28 by ldutriez          #+#    #+#             */
/*   Updated: 2022/07/24 15:31:10 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "retromfa.h"
#include <sys/types.h> //Needed for ssite_t
#include <fcntl.h>	   //Needed for open
#include <unistd.h>	   // Needed by file management functions

t_list extract_0x06_images_from_file(t_b_data *binary_file, t_int2 *max_size)
{
	t_list img_list = NULL;
	t_list start = NULL;

	for (long i = 0; i + 3 < binary_file->size; i++)
	{
		if (i > 6 && binary_file->data[i] == 0x00 && binary_file->data[i + 1] == 0x06 && binary_file->data[i + 2] == 0x10 &&
			binary_file->data[i + 3] == 0x00)
		{
			void *addr;

			addr = &binary_file->data[i - 3];
			int width = *(short int *)addr;
			addr = &binary_file->data[i - 6];
			int height = *(short int *)addr;
			t_b_data *img_data = malloc(sizeof(t_b_data));
			img_data->data = &binary_file->data[i];
			img_data->size = width * height * 2;
			img_data->width = width;
			img_data->height = height;
			if (img_data->size + i > binary_file->size || img_data->size <= 0 || img_data->width <= 0 || img_data->height <= 0)
			{
				free(img_data);
				continue;
			}
			img_data->type = 6;
			if (img_data->width > max_size->x)
				max_size->x = img_data->width;
			if (img_data->height > max_size->y)
				max_size->y = img_data->height;
			if (img_list == NULL)
				start = img_list = ft_malloc_node(img_data);
			else
				ft_list_add_back(&img_list, ft_malloc_node(img_data));
			i += img_data->size - 1;
		}
	}
	return (start);
}


t_list extract_0x04_images_from_file(t_b_data *binary_file, t_int2 *max_size)
{
	t_list img_list = NULL;
	t_list start = NULL;

	for (int i = 0; i < binary_file->size; i++)
	{
		if (binary_file->data[i] == 0x00 && binary_file->data[i + 1] == 0x04 && binary_file->data[i + 2] == 0x10 &&
			binary_file->data[i + 3] == 0x00)
		{
			void *addr;

			addr = &binary_file->data[i - 3];
			int width = *(short int *)addr;
			addr = &binary_file->data[i - 6];
			int height = *(short int *)addr;
			t_b_data *img_data = malloc(sizeof(t_b_data));
			img_data->data = &binary_file->data[i];
			img_data->size = width * height * 3;
			img_data->width = width;
			if (width % 2 == 1)
				img_data->width++;
			img_data->height = height;
			img_data->type = 4;
			if (img_data->width > max_size->x)
				max_size->x = img_data->width;
			if (img_data->height > max_size->y)
				max_size->y = img_data->height;
			if (img_data->size + i > binary_file->size || img_data->size < 0)
			{
				free(img_data);
				break;
			}
			if (img_list == NULL)
				start = img_list = ft_malloc_node(img_data);
			else
				ft_list_add_back(&img_list, ft_malloc_node(img_data));
			i += img_data->size - 1;
		}
	}
	return (start);
}

t_list extract_bmps_from_binary_file(t_b_data *binary_file)
{
	t_list bmp_list = NULL;
	t_list start = NULL;

	for (int i = 0; i < binary_file->size; i++)
	{
		if (i + 1 < binary_file->size && binary_file->data[i] == 'B' && binary_file->data[i + 1] == 'M')
		{
			t_b_data *bmp_file = malloc(sizeof(t_b_data));

			bmp_file->data = binary_file->data + i;
			void *addr = bmp_file->data + 2;
			bmp_file->size = *(int *)addr;
			if (bmp_file->size + i > binary_file->size || bmp_file->size < 0)
			{
				free(bmp_file);
				break;
			}
			if (bmp_list == NULL)
				start = bmp_list = ft_malloc_node(bmp_file);
			else
				ft_list_add_back(&bmp_list, ft_malloc_node(bmp_file));
			i += bmp_file->size - 1;
		}
	}
	return (start);
}

t_b_data extract_bmp_from_binary_file(t_b_data *binary_file)
{
	t_b_data bmp_file;
	int i;

	i = 0;
	while (i < binary_file->size)
	{
		if (binary_file->data[i] == 'B' && binary_file->data[i + 1] == 'M')
		{
			bmp_file.data = &binary_file->data[i];
			bmp_file.size = binary_file->data[i + 2] + (binary_file->data[i + 3] << 8) + (binary_file->data[i + 4] << 16) + (binary_file->data[i + 5] << 24);
			return (bmp_file);
		}
		++i;
	}
	bmp_file.data = NULL;
	bmp_file.size = 0;
	return (bmp_file);
}

t_b_data read_file(char *file_name)
{
	t_b_data result;
	char *file;
	int fd;
	__off_t size;
	ssize_t b_read;

	if ((fd = open(file_name, O_RDONLY)) == -1)
	{
		dprintf(2, "Error\nUnable to open file %s\n", file_name);
		exit(1);
	}
	size = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	if ((file = malloc(sizeof(char) * size)) == NULL)
	{
		dprintf(2, "Error\nUnable to allocate memory\n");
		exit(1);
	}
	b_read = read(fd, file, size);
	if (b_read == -1)
	{
		dprintf(2, "Error\nUnable to read file %s\n", file_name);
		exit(1);
	}
	close(fd);
	result.data = file;
	result.size = b_read;
	return (result);
}
