NAME = so_long

SRCS	= 	./srcs/main.c \
			./srcs/hook.c \
			./srcs/graphic.c \
			./srcs/fill_and_check_map.c \
			./srcs/destroy_and_clean.c \
			./srcs/init.c \
			./srcs/modify_position.c \

SRCS_B = ./srcs/display_score.c

OBJS	= ${SRCS:.c=.o}

CFLAGS	= -Wall -Werror -Wextra -g

CC		= gcc

RM		= rm -f

LIBFT = ./lib/libft/libft.a

LIBFTPRINTF = ./lib/ft_printf/libftprintf.a

MLX = ./lib/mlx_linux/libmlx.a

all:	${NAME}

%.o: %.c
		@$(CC) -Wall -Wextra -Werror -I . -O3 -c $< -o $@

${NAME}:	${OBJS} ${LIBFT} ${MLX} ${LIBFTPRINTF}
		@${CC} ${CFLAGS} ${SRCS} ${LIBFT} ${MLX} ${LIBFTPRINTF} -lX11 -lXext -o so_long
		@printf "%s\e[0;32m so_long : Compiling object file into executable\n\e[0m" "-"

${LIBFT}:
		@make -C lib/libft --no-print-directory

${LIBFTPRINTF}:
		@make -C lib/ft_printf --no-print-directory

${MLX}:
		@make -C lib/mlx_linux --no-print-directory

clean:
		@${RM} ${OBJS}
		@printf "%s \e[0;31m so_long : Delete all object files\n\e[0m" "-"
		@make clean -C lib/libft --no-print-directory
		@make clean -C lib/ft_printf --no-print-directory

fclean:	clean
		@${RM} ${NAME}
		@${RM} ${LIBFT}
		@${RM} ${LIBFTPRINTF}
		@${RM} ${MLX}
		@make clean -C lib/mlx_linux --no-print-directory
		@printf "%s\e[0;31m so_long : Delete executable\n\e[0m" "-"

re: fclean ${NAME}

.PHONY: all clean fclean re
