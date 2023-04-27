SRCS	=

OBJS	= ${SRCS:.c=.o}

SRCS_B	=

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/13 13:30:11 by loumouli          #+#    #+#              #
#    Updated: 2023/02/12 11:30:19 by loumouli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ################################## #
#               COMMAND              #
# ################################## #
CC			= cc
MKDIR		= mkdir -p
RM			= rm -rf

# ################################## #
#              EXEC NAME             #
# ################################## #
NAME		= libft.a

# ################################## #
#               SOURCES              #
# ################################## #
C_DIR		= src
C_FILES =	ft_atoi.c 			\
			ft_calloc.c 		\
			ft_isascii.c  		\
			ft_bzero.c 			\
			ft_isalnum.c 		\
			ft_isalpha.c 		\
			ft_isdigit.c 		\
			ft_isprint.c 		\
			ft_memchr.c 		\
			ft_memcmp.c 		\
			ft_memcpy.c 		\
			ft_strdup.c 		\
			ft_memmove.c 		\
			ft_memset.c 		\
			ft_strchr.c 		\
			ft_strlcat.c 		\
			ft_strlcpy.c 		\
			ft_strlen.c 		\
			ft_strncmp.c 		\
			ft_strnstr.c 		\
			ft_strrchr.c 		\
			ft_tolower.c 		\
			ft_toupper.c 		\
			ft_substr.c 		\
			ft_strjoin.c 		\
			ft_strtrim.c 		\
			ft_split.c 			\
			ft_itoa.c 			\
			ft_strmapi.c 		\
			ft_striteri.c		\
			ft_putchar_fd.c		\
			ft_putstr_fd.c 		\
			ft_putendl_fd.c 	\
			ft_putnbr_fd.c		\
			ft_lstadd_back.c	\
			ft_lstadd_front.c	\
			ft_lstclear.c		\
			ft_lstdelone.c		\
			ft_lstiter.c		\
			ft_lstlast.c		\
			ft_lstmap.c			\
			ft_lstnew.c			\
			ft_lstsize.c		\
			clean_split.c		\

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
CFLAGS		= -Wall -Wextra -Werror -g -MMD

# ################################## #
#                INCLUDES            #
# ################################## #
CINCLUDES = -I ./inc
# ################################## #
#                RULES               #
# ################################## #

all:	$(NAME)

$(O_DIR):
		$(MKDIR) $(O_DIR)

$(O_DIR)/%.o: $(C_DIR)/%.c
		$(CC)  $(CFLAGS) $(CINCLUDES) -c $< -o $@



$(NAME): $(O_DIR) $(OBJS)
			ar rcs ${NAME} ${OBJS}

# ################################## #
#                CLEAN               #
# ################################## #

clean:
			$(RM) $(O_DIR)

fclean: clean
			$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re

-include ./objs/*.d

.NOTPARALLEL:fclean