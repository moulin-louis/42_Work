# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/13 11:42:25 by bschoeff          #+#    #+#              #
#    Updated: 2022/12/02 18:16:35 by loumouli         ###   ########.fr        #
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

NAME		= philo

# ################################## #
#               SOURCES              #
# ################################## #

C_DIR		= src
C_FILES		= main.c	\
			  parsing.c \
			  utils.c   \
			  clean.c	\

SRCS		= $(patsubst %, $(C_DIR)/%, $(C_FILES))

# ################################## #
#               OBJECTS              #
# ################################## #

O_DIR		= objs
O_FILES		= $(C_FILES:.c=.o)
OBJS		= $(patsubst %, $(O_DIR)/%, $(O_FILES))
DEPS 		= $ $(C_FILES:.c=.d)

# ################################## #
#                FLAGS               #
# ################################## #

CFLAGS		= -Wall -Wextra -Werror -g

# ################################## #
#                INCLUDES            #
# ################################## #

CINCLUDES	=	-I ./inc

# ################################## #
#                RULES               #
# ################################## #

all:	$(NAME)

$(NAME):	$(O_DIR) $(OBJS)
			$(CC) $(OBJS) $(CFLAGS) -o $@

$(O_DIR)/%.o: $(C_DIR)/%.c
			$(CC) $(CFLAGS) $(CINCLUDES) -c $< -o $@

$(O_DIR):
			$(MKDIR) $(O_DIR)

# ################################## #
#                CLEAN               #
# ################################## #

clean:
			$(RM) $(O_DIR)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

-include	$(OBJS:.o=.d)

.PHONY: all check clean fclean re
