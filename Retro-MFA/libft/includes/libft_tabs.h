/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_tabs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 16:31:56 by ldutriez          #+#    #+#             */
/*   Updated: 2021/05/27 17:47:42 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_TABS_H
# define LIBFT_TABS_H

/*
**	Needed to use malloc/free | size_t
*/
# include <stdlib.h>

/*
**	Creating a new 2 dimensions array of size entries. Heap allocated.
*/
void			**ft_tab_new(int size);

/*
**	Calculating the number of entries in a 2 dimensions array.
*/
int				ft_tab_len(void	**tab);

/*
**	Free every entity in a 2 dimensions array and free the array itself.
*/
void			ft_free_tab(void **tab);

/*
**	Copy the entries of a 2 dimensions array in another one.
*/
void			ft_tab_cpy(void **dst, void **src);

/*
**	Adding a an entry at the end of an 2 dimension array. Heap allocated.
*/
void			ft_add_to_tab(void *to_add, void ***tab);

#endif
