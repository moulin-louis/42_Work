# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/04 17:15:05 by marnaudy          #+#    #+#              #
#    Updated: 2022/06/11 18:20:54 by marnaudy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	connect4

LIBFT	=	libft/libft.a

SRCS	=	srcs/get_move_player.c \
			srcs/get_move_ai.c \
			srcs/display.c \
			srcs/ft_atoi_no_overflow.c \
			srcs/init.c \
			srcs/check_win.c \
			srcs/play_game.c \
			srcs/main.c

HEADERS	=	connect4.h

OBJS	=	${SRCS:.c=.o}

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -f

all:		${NAME}

${NAME}:	${OBJS} ${LIBFT}
			${CC} ${OBJS} ${LIBFT} -o ${NAME}

${LIBFT}:
			make -C libft

%.o:		%.c	${HEADERS}
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
			${RM} ${OBJS}
			make -C libft clean

fclean:		clean
			${RM} ${NAME} ${LIBFT}

re:			fclean all

.PHONY:		all clean fclean re
