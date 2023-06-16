/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:20:59 by loumouli          #+#    #+#             */
/*   Updated: 2022/05/11 11:44:21 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

#ifdef __cplusplus
extern "C" {
#endif

// Function declarations here

t_list	*libft_ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	libft_ft_lstiter(t_list *lst, void (*f)(void *));
void	libft_ft_lstclear(t_list **lst, void (*del)(void *));
void	libft_ft_lstdelone(t_list *lst, void (*del)(void *));
char	*libft_ft_substr(char const *s, unsigned int start, size_t len);
int		libft_ft_tolower(int c);
int		libft_ft_toupper(int c);
char	*libft_ft_strrchr(const char *s, int c);
char	*libft_ft_strnstr(const char *big, const char *little, size_t len);
int		libft_ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	libft_ft_strlen(const char *s);
size_t	libft_ft_strlcpy(char *dest, const char *src, size_t size);
size_t	libft_ft_strlcat(char *dst, const char *src, size_t size);
char	*libft_ft_strdup(const char *s);
char	*libft_ft_strchr(const char *s, int c);
void	*libft_ft_memset(void *s, int c, size_t n);
void	*libft_ft_memmove(void *dest, const void *src, size_t n);
void	*libft_ft_memcpy(void *dest, const void *src, size_t n);
int		libft_ft_memcmp(const void *s1, const void *s2, size_t n);
void	*libft_ft_memchr(const void *s, int c, size_t n);
int		libft_ft_isprint(int c);
int		libft_ft_isdigit(int c);
int		libft_ft_isascii(int c);
int		libft_ft_isalpha(int c);
int		libft_ft_isalnum(int c);
void	*libft_ft_calloc(size_t nmemb, size_t size);
void	libft_ft_bzero(void *s, size_t n);
int		libft_ft_atoi(const char *nptr);
char	*libft_ft_strjoin(char const *s1, char const *s2);
char	*libft_ft_strtrim(char const*s1, char const *set);
char	**libft_ft_split(char const *s, char c);
char	*libft_ft_itoa(int n);
char	*libft_ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	libft_ft_striteri(char *s, void (*f)(unsigned int, char*));
void	libft_ft_putchar_fd(char c, int fd);
void	libft_ft_putstr_fd(char *s, int fd);
void	libft_ft_putendl_fd(char *s, int fd);
void	libft_ft_putnbr_fd(int n, int fd);
void	libft_ft_lstadd_back(t_list **lst, t_list *new_node);
t_list	*libft_ft_lstlast(t_list *lst);
int		libft_ft_lstsize(t_list *lst);
t_list	*libft_ft_lstnew(void *content);
void	libft_ft_lstadd_front(t_list **lst, t_list *new_node);
void	libft_ft_lstdelone(t_list *lst, void (*del)(void*));
void	clean_array(char **arr);
#ifdef __cplusplus
}
#endif



#endif
