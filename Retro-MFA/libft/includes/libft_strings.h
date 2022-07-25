/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_strings.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 16:25:02 by ldutriez          #+#    #+#             */
/*   Updated: 2022/05/31 20:25:08 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STRINGS_H
# define LIBFT_STRINGS_H

/*
**	Needed to use malloc/free | size_t
*/
# include <stdlib.h>

/*
**	Allocating memory for a new string of len lenght and filling it with '\0'.
*/
char			*ft_strnew(size_t len);

/*
**	Copying the characters of src string in a new string. Note that we allocate
**	memory for the new string before copying.
*/
char			*ft_strdup(char *src);

/*
**	Allocating memory for a new string containing only c character.
**	Then returns the string.
*/
char			*ft_strdup_c(char c);

/*
**	Counting the lenght of a string and returning it.
*/
size_t			ft_strlen(char	*src);

/*
**	Copying the characters of src string in dest string. Returns dest after the
**	copy. Note that we do not proceed to any memory allocation.
*/
char			*ft_strcpy(char *src, char *dest);

/*
**	Troncating a string from the start index of src until len characters
**	are copied. Returns a heap allocated string. Note that we do not free src.
*/
char			*ft_strsub(char *src, size_t start, size_t len);

/*
**	Merging 2 strings in one. Then returns the new string. Note that we
**	allocate memory for the new string, but we do not free str1 and str2.
*/
char			*ft_strjoin(char *str1, char *str2);

/*
**	Searching for the full needle string is found in the haystack string.
**	If needle is found, returns a pointer on haystack string, starting at
**	the first character of needle. If needle is not found, returns NULL.
*/
char			*ft_strstr(char *haystack, char *needle);

/*
**	Splitting a string into multiple ones depending on sep character.
**	Returns a pointer to the first string of the multiple new ones.
*/
char			**ft_split(char *src, char sep);

/*
**	Adding a prefixe to a string. Free the old string, re-allocate the new one.
*/
void			ft_str_add_prefixe(char *prefixe, char **str);

/*
**	Adding a suffix to a string. Free the old string, re-allocate the new one.
*/
void			ft_str_add_suffix(char **str, char *suffix);

/*
**	Counting the number of itterations of c character in str string.
*/
int				ft_str_count_c(char *str, char c);

/*
**	Searching for the full needle string is found in the haystack string, but
**	only checking len characters. If needle is found, returns a pointer on
**	haystack string, starting at the first character of needle. If needle is
**	not found, returns NULL.
*/
char			*ft_strnstr(char *haystack, char *needle, size_t len);

/*
**	Removing all characters of a charset of a string and returning
**	the cleaned string.
*/
char			*ft_rm_charset(char *str, char *charset);

/*
**	The ft_bzero() function erases the data in the n bytes of the memory
**	starting at the location pointed to by addr, by writing zeros to that area.
*/
void			ft_bzero(void *addr, size_t n);

/*
**	The ft_memset() function fills the first n bytes of the memory area
**	pointed to by s with the constant byte c.
*/
void			*ft_memset(void *s, int c, size_t n);

#endif
