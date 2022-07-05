NAME = so_long

SRCS	= 	./srcs/main.c \
			./srcs/hook.c \
			./srcs/graphic.c \
			./srcs/fill_and_check_map.c \
			./srcs/destroy_and_clean.c \
			./srcs/init.c \
			./srcs/modify_position.c \

SRCS_B = ./srcs/bonus/main_bonus.c \
			./srcs/bonus/hook_bonus.c \
			./srcs/bonus/graphic_bonus.c \
			./srcs/bonus/fill_and_check_map_bonus.c \
			./srcs/bonus/destroy_and_clean_bonus.c \
			./srcs/bonus/init_bonus.c \
			./srcs/bonus/modify_position_bonus.c \
			./srcs/bonus/display_score_bonus.c

OBJS	= ${SRCS:.c=.o}

OBJS_B	= ${SRCS_B:.c=.o}

CFLAGS	= -Wall -Werror -Wextra -g

CC		= gcc

RM		= rm -f

LIBFT = ./lib/libft/libft.a

LIBFTPRINTF = ./lib/ft_printf/libftprintf.a

MLX = ./lib/mlx_linux/libmlx.a

all:	${NAME}

.c.o:
		@$(CC) ${CFLAGS} -I . -O3 -c $< -o $@

${NAME}:	${OBJS} ${LIBFT} ${MLX} ${LIBFTPRINTF}
		@${CC} ${CFLAGS} ${OBJS} ${LIBFT} ${MLX} ${LIBFTPRINTF} -lX11 -lXext -o so_long
		@printf "%s\e[0;32m so_long : Compiling object file into executable\n\e[0m" "-"

${LIBFT}:
		@make -C lib/libft all --no-print-directory

${LIBFTPRINTF}:
		@make -C lib/ft_printf all --no-print-directory

${MLX}:
		@make -C lib/mlx_linux --no-print-directory

bonus: ${OBJS_B} ${LIBFT} ${MLX} ${LIBFTPRINTF}
		${CC} ${CFLAGS} ${OBJS_B} ${LIBFT} ${MLX} ${LIBFTPRINTF} -lX11 -lXext -o so_long
		@printf "%s\e[0;32m so_long : Compiling bonus object file into executable\n\e[0m" "-"

clean:
		@${RM} ${OBJS}
		@${RM} ${OBJS_B}
		@printf "%s\e[0;31m so_long : Delete all object files\n\e[0m" "-"
		@make clean -C lib/libft --no-print-directory
		@make clean -C lib/ft_printf --no-print-directory


fclean:
		@${RM} ${OBJS}
		@${RM} ${OBJS_B}
		@printf "%s\e[0;31m so_long : Delete all object files\n\e[0m" "-"
		@${RM} ${NAME}
		@printf "%s\e[0;31m so_long : Delete executable\n\e[0m" "-"
		@make fclean -C lib/libft --no-print-directory
		@make fclean -C lib/ft_printf --no-print-directory
		@make clean -C lib/mlx_linux --no-print-directory


re: fclean ${NAME}

.PHONY: all clean fclean re bonus
