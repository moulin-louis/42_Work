SRCS	= ./srcs/main.c ./srcs/hook.c ./srcs/graphic.c ./srcs/setup_map.c

OBJS	= ${SRCS:.c=.o}

CFLAGS	= -Wall -Werror -Wextra -g

CC		= gcc

NAME = a.out

RM		= rm -f

%.o: %.c
	@$(CC) -Wall -Wextra -Werror -I . -O3 -c $< -o $@
	@printf "%s\e[0;32m Converting C files to object files\n\e[0m" "-"

${NAME}:	${OBJS}
		@${CC} ${CFLAGS} ${SRCS} ./lib/mlx_linux/libmlx.a ./lib/libft/libft.a ./lib/ft_printf/libftprintf.a -lX11 -lXext
		@printf "%s\e[0;32m Compiling object file into executable\n\e[0m" "-"

all:	${NAME}

clean:
		@${RM} ${OBJS}
		@printf "%s \e[0;31mDelete all object files\n\e[0m" "-"


fclean:	clean
		@${RM} ${NAME}
		@printf "%s\e[0;31m Delete executable\n\e[0m" "-"

re: fclean ${NAME}

.PHONY: all clean fclean re
