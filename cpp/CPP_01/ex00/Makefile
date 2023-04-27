# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/13 13:30:11 by loumouli          #+#    #+#              #
#    Updated: 2023/01/15 12:23:30 by loumouli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ################################## #
#               COMMAND              #
# ################################## #
CC			= c++
MKDIR		= mkdir -p
RM			= rm -rf

# ################################## #
#              EXEC NAME             #
# ################################## #
NAME		= brainz		

# ################################## #
#               SOURCES              #
# ################################## #
C_DIR		= src
C_FILES		=	main.cpp		\
				Zombie.cpp		\
				newZombie.cpp	\
				randomChump.cpp	\
				
SRCS		= $(patsubst %, $(C_DIR)/%, $(C_FILES))

# ################################## #
#               OBJECTS              #
# ################################## #
O_DIR		= objs
O_FILES		= $(C_FILES:.cpp=.o)
OBJS		= $(patsubst %, $(O_DIR)/%, $(O_FILES))
DEPS		= $ $(C_FILES:.c=.d)

# ################################## #
#                FLAGS               #
# ################################## #

CFLAGS		= -Wall -Wextra -Werror -g -MMD -std=c++98

# ################################## #
#                INCLUDES            #
# ################################## #
CINCLUDES	=	-I ./inc

# ################################## #
#                RULES               #
# ################################## #

all:	$(NAME)

$(O_DIR):
			$(MKDIR) $(O_DIR)

$(O_DIR)/%.o: $(C_DIR)/%.cpp
			$(CC) $(CFLAGS) $(CINCLUDES) -c $< -o $@


$(NAME): $(O_DIR) $(OBJS)
			$(CC) $(OBJS) $(CFLAGS) -o $@
test:
	echo test

# ################################## #
#                CLEAN               #
# ################################## #

clean:
			$(RM) $(O_DIR)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re
-include ./objs/*.d

.NOTPARALLEL:fclean