SRCS	= ft_atoi.c ft_calloc.c ft_isascii.c  ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_strdup.c ft_memmove.c ft_memset.c ft_strchr.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

OBJS	= ${SRCS:.c=.o}

SRCS_B	= ft_lstadd_back.c ft_lstiter.c ft_lstadd_front.c ft_lstlast.c ft_lstnew.c ft_lstsize.c ft_lstdelone.c ft_lstclear.c ft_lstmap.c

OBJS_B	= ${SRCS_B:.c=.o}

NAME	= libft.a

CFLAGS	= -Wall -Werror -Wextra -g

CC		= gcc

RM		= rm -f

.c.o:
		@${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I .

${NAME}:	${OBJS}
		@ar -rc ${NAME} ${OBJS}
		@printf "%s\e[0;32m libft : Compiling object file into executable\n\e[0m" "-"

all:	${NAME}

clean:
		@${RM} *.o
		@printf "%s\e[0;31m libft : Delete all object files\n\e[0m" "-"

fclean:	clean
		@${RM} ${NAME}
		@printf "%s\e[0;31m libft : Delete executable\n\e[0m" "-"

re: fclean all

bonus: ${OBJS_B}
	@ar -rc ${NAME} ${OBJS_B}
	@printf "%s\e[0;32m libft : Compiling bonus object file\n\e[0m" "-"

.PHONY: all clean fclean re ${NAME} .c.o bonus
