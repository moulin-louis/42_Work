SRCS	= srcs/ft_putchar.c srcs/ft_putstr.c srcs/ft_strcmp.c srcs/ft_strlen.c srcs/ft_swap.c

OBJS	= ${SRCS:.c=.o}

NAME	= libft.a

HEADERS	= includes

CFLAGS	= -Wall -Werror -Wextra

CC		= gcc

RM		= rm -f

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ${HEADERS}

${NAME}:	${OBJS}
		ar -rc ${NAME} ${OBJS}

all:	${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}
		

re: fclean all

.PHONY: all clean fclean re
