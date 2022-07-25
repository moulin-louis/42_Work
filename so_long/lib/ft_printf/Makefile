NAME    	= libftprintf.a

SRCS    	=  ./srcs/ft_printf.c ./srcs/ft_putchar_printf.c ./srcs/ft_putstr_printf.c ./srcs/ft_putnbr_base_printf.c ./srcs/ft_putnbr_printf.c ./srcs/ft_putunbr_printf.c ./srcs/ft_print_adress_printf.c

OBJS		= ${SRCS:.c=.o}

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -g

RM			= rm -rf

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:${OBJS}
		ar -rcs ${NAME} ${OBJS}

all:    ${NAME}

clean:
		${RM} ${OBJS}

fclean:    clean
		${RM} ${NAME}

re:     fclean all

.PHONY: all clean fclean re
