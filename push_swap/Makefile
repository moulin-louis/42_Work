NAME = push_swap

SRCS	= 	./srcs/main.c

OBJS	= ${SRCS:.c=.o}

CFLAGS	= -Wall -Werror -Wextra -g

CC		= gcc

RM		= rm -f

LIBFT = ./lib/libft/libft.a

LIBFTPRINTF = ./lib/ft_printf/libftprintf.a

all:	${NAME}

.c.o:
		@$(CC) -Wall -Wextra -Werror -I . -O3 -c $< -o $@

${NAME}:	${OBJS} ${LIBFT} ${LIBFTPRINTF}
		@${CC} ${CFLAGS} ${OBJS} ${LIBFT} ${LIBFTPRINTF} -o push_swap
		# @printf "%s\e[0;32m push_swap : Compiling object file into executable\n\e[0m" "-"

${LIBFT}:
		@make -C lib/libft --no-print-directory

${LIBFTPRINTF}:
		@make -C lib/ft_printf --no-print-directory

clean:
		@${RM} ${OBJS}
		# @printf "%s\e[0;31m push_swap : Delete all object files\n\e[0m" "-"
		@make clean -C lib/libft --no-print-directory
		@make clean -C lib/ft_printf --no-print-directory
		

fclean:	
		@${RM} ${OBJS}
		# @printf "%s\e[0;31m push_swap : Delete all object files\n\e[0m" "-"
		@${RM} ${NAME}
		# @printf "%s\e[0;31m push_swap : Delete executable\n\e[0m" "-"
		@make fclean -C lib/libft --no-print-directory
		@make fclean -C lib/ft_printf --no-print-directory
		

re: fclean ${NAME}

.PHONY: all clean fclean re
