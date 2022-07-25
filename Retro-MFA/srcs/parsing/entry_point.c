/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:57:31 by ldutriez          #+#    #+#             */
/*   Updated: 2022/07/23 12:37:42 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "retromfa.h"
#include <sys/stat.h>
#include <fcntl.h>

int display_usage(const char *binary_name)
{
	dprintf(2, "Usage: %s mfa_file\n", binary_name);
	return EXIT_FAILURE;
}

static inline bool file_is_readable(const char *name)
{
	struct stat buffer;
	if (stat(name, &buffer) == 0)
	{
		mode_t perm = buffer.st_mode;
		if ((perm & S_IRUSR) != 0)
			return true;
	}
	return false;
}

int is_correct_usage(int ac, char *av[])
{
	if (ac != 2)
	{
		dprintf(2, "Invalid number of arguments.\n");
		return display_usage(av[0]);
	}
	if (file_is_readable(av[1]) == false)
	{
		dprintf(2, "Unable to open and read `%s`\n", av[1]);
		return display_usage(av[0]);
	}
	return EXIT_SUCCESS;
}