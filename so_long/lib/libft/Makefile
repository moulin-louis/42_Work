SRCS	= ft_atoi.c ft_calloc.c ft_isascii.c  ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_strdup.c ft_memmove.c ft_memset.c ft_strchr.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstadd_back.c ft_lstiter.c ft_lstadd_front.c ft_lstlast.c ft_lstnew.c ft_lstsize.c ft_lstdelone.c ft_lstclear.c ft_lstmap.c ./ft_printf/srcs/ft_print_adress_printf.c ./ft_printf/srcs/ft_printf.c ./ft_printf/srcs/ft_putchar_printf.c ./ft_printf/srcs/ft_putnbr_base_printf.c ./ft_printf/srcs/ft_putnbr_printf.c ./ft_printf/srcs/ft_putstr_printf.c ./ft_printf/srcs/ft_putunbr_printf.c

OBJS	= ${SRCS:.c=.o}

NAME	= libft.a

CFLAGS	= -Wall -Werror -Wextra -g

CC		= gcc

RM		= rm -f

.c.o:
		@${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I .

${NAME}:	${OBJS}
		@ar -rc ${NAME} ${OBJS}

all:	${NAME}

clean:
		@${RM} ${OBJS}

fclean:	clean
		@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
