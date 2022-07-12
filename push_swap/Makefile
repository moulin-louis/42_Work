NAME	= push_swap

SRCS	= srcs/main.c \
		srcs/utility.c \
		srcs/utility2.c \
		srcs/init.c \
		srcs/check_input.c \
		srcs/instruc/swap.c \
		srcs/instruc/push.c \
		srcs/instruc/rotate.c \
		srcs/instruc/r_rotate.c

OBJS	= ${SRCS:.c=.o}

LIBFT = libft/libft.a

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra -g

RM		= rm -f

all: 		${NAME}

.c.o:
		${CC} ${CFLAGS} -I . -c $< -o $@

${NAME}:	${LIBFT} ${OBJS}
		@echo "compiling so_long"
		${CC} ${CFLAGS} ${OBJS} -o ${NAME} ${LIBFT}

${LIBFT}:
		make -C libft all --no-print-directory

clean:
		${RM} ${OBJS}
		make -C libft clean --no-print-directory

fclean: 	clean
		${RM} ${NAME}
		make -C libft fclean --no-print-directory

re:			fclean ${NAME}

.PHONY: all clean fclean re bonus
