# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: loumouli < loumouli@student.42.fr >        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/11 12:36:33 by anclarma          #+#    #+#              #
#    Updated: 2022/07/29 19:31:16 by loumouli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED=\033[0;31m
GREEN=\033[0;32m
RESET=\033[0m

# ################################## #
#               COMMAND              #
# ################################## #
CC			= gcc
MKDIR		= mkdir -p
RM			= rm -rf

# ################################## #
#              EXEC NAME             #
# ################################## #
NAME		= libft.a

# ################################## #
#               SOURCES              #
# ################################## #
C_DIR		= ./
C_FILES		= ft_atoi.c \
			ft_calloc.c \
			ft_isascii.c \
			ft_bzero.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_strdup.c \
			ft_memmove.c \
			ft_memset.c \
			ft_strchr.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_lstadd_back.c \
			ft_lstiter.c \
			ft_lstadd_front.c \
			ft_lstlast.c \
			ft_lstnew.c \
			ft_lstsize.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstmap.c


SRCS		= $(patsubst %, $(C_DIR)/%, $(C_FILES))

# ################################## #
#               OBJECTS              #
# ################################## #
O_DIR		= objs
O_FILES		= $(C_FILES:.c=.o)
OBJS		= $(patsubst %, $(O_DIR)/%, $(O_FILES))

# ################################## #
#                FLAGS               #
# ################################## #
CFLAGS		= -Wall -Wextra -Werror -g

# ################################## #
#                RULES               #
# ################################## #

$(O_DIR)/%.o: $(C_DIR)/%.c
			@$(CC) $(CFLAGS) $(CINCLUDES) -c $< -o $@

all:		$(NAME)

check:	fclean
check:	CFLAGS		+=  -pedantic -ansi
check:	CFLAGS		+=  -fsanitize=address
check:	CFLAGS		+=  -fsanitize=leak
check:	CFLAGS		+=  -fsanitize=undefined
check:	CFLAGS		+=  -g3
check:	LFLAGS		+=  -fsanitize=address
check:	LFLAGS		+=  -fsanitize=leak
check:	LFLAGS		+=  -fsanitize=undefined
check:	LFLAGS		+=  -g3
check:	${NAME}

$(NAME):	$(O_DIR) $(LIBFT) $(OBJS)
			@ar -rc ${NAME} ${OBJS}
			@echo "${GREEN}- compiling library libft.a ${RESET}"

$(O_DIR):
			@$(MKDIR) $(O_DIR)
			@echo "${GREEN}- creating libft directory objs${RESET}"


clean:
			@$(RM) $(O_DIR)
			@echo "${RED}- deleting libft objects${RESET}"

fclean:		clean
			@$(RM) $(NAME)
			@echo "${RED}- delete libft library${RESET}"

re:			fclean all

-include	$(OBJS:.o=.d)

.PHONY: all check clean fclean re
