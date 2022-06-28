NAME    	= libftprintf.a

SRCS    	=  ./srcs/ft_printf.c ./srcs/ft_putchar_printf.c ./srcs/ft_putstr_printf.c ./srcs/ft_putnbr_base_printf.c ./srcs/ft_putnbr_printf.c ./srcs/ft_putunbr_printf.c ./srcs/ft_print_adress_printf.c

OBJS		= ${SRCS:.c=.o}

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -g

RM			= rm -rf

.c.o:
		@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:${OBJS}
		@ar -rcs ${NAME} ${OBJS}
		@printf "%s \e[0;32m ft_printf : Compiling object file into executable\n\e[0m" "-"

all:    ${NAME}

clean:
		@${RM} ${OBJS}
		@printf "%s \e[0;31m ft_printf : Delete all object files\n\e[0m" "-"

fclean:    clean
		@${RM} ${NAME}
		@printf "%s\e[0;31m ft_printf : Delete executable\n\e[0m" "-"

re:     fclean all

.PHONY: all clean fclean re
