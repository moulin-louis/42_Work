# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/13 11:42:25 by bschoeff          #+#    #+#              #
#    Updated: 2022/11/14 14:48:27 by loumouli         ###   ########.fr        #
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
C_FILES		= main.c

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

CFLAGS		= -Wall -Wextra -Werror -g3 -MMD

LFLAGS		=

# ################################## #
#                INCLUDES            #
# ################################## #

CINCLUDES	=	-I ./inc

CLIBS		=

# ################################## #
#                RULES               #
# ################################## #

all:	$(NAME)

$(NAME):	$(O_DIR) $(OBJS)
			$(CC) $(OBJS) $(CFLAGS) $(LFLAGS) $(CLIBS) -o $@

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
