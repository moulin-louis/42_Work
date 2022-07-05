NAME	= push_swap

SRCS	= srcs/main.c \
		srcs/utility.c \
		srcs/utility2.c \
		srcs/init.c

OBJS	= ${SRCS:.c=.o}

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra -g

RM		= rm -f

all: 		${NAME}

.c.o:
		${CC} ${CFLAGS} -I . -c $< -o $@

${NAME}:	${OBJS} 
		@echo "compiling so_long"
		${CC} ${CFLAGS} ${OBJS} -o ${NAME}

${LIBFT}:
		echo "libft compiling"

clean:
		${RM} ${OBJS}

fclean: 	clean
		${RM} ${NAME}

re:			fclean ${NAME}

.PHONY: all clean fclean re bonus