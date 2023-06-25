# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    libft_creator.sh                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/21 15:59:57 by loumouli          #+#    #+#              #
#    Updated: 2022/02/22 19:14:49 by loumouli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

gcc -c ft_putchar.c ft_swap.c ft_putstr.c ft_strlen.c ft_strcmp.c && ar -rc libft.a ft_putchar.o ft_swap.o ft_putstr.o ft_strlen.o ft_strcmp.o
