/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:41:10 by loumouli          #+#    #+#             */
/*   Updated: 2022/06/03 13:16:19 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>

char	*ft_fill_save(char *buffer_saved, int fd);
char	*ft_del_line(char *buffer_saved);
char	*ft_fill_result(char *buffer_saved);
char	*get_next_line(int fd);

char	*ft_strchr(const char *s, int c);
int		ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);

#endif
