# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/13 13:30:11 by loumouli          #+#    #+#              #
#    Updated: 2023/02/15 12:03:03 by loumouli         ###   ########.fr        #
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
NAME		= pipex_bonus

# ################################## #
#               SOURCES              #
# ################################## #
C_DIR		= src
C_FILES		=	main_bonus.c				\
				parsing_bonus.c				\
				utils_lst_bonus.c			\
				path_bonus.c				\
				

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
CINCLUDES	=	-I ./inc -I ./libft/inc
LIBFT 		= 	./libft/libft.a

# ################################## #
#                RULES               #
# ################################## #

all:	$(NAME)

$(O_DIR):
			$(MKDIR) $(O_DIR)

$(O_DIR)/%.o: $(C_DIR)/%.c
			$(CC)  $(CFLAGS) $(CINCLUDES) -c $< -o $@

$(LIBFT):
		make -C ./libft all


$(NAME): $(LIBFT) $(O_DIR) $(OBJS)
			$(CC)  $(OBJS) $(CFLAGS) $(LIBFT) -o $@
			cp $(NAME) ../$(NAME)

# ################################## #
#                CLEAN               #
# ################################## #

clean:
			make -C ./libft clean
			$(RM) $(O_DIR)

fclean:
			$(RM) $(O_DIR)
			make -C ./libft fclean
			$(RM) $(NAME)
			(rm ../$(NAME))&

re:			fclean all

.PHONY: all clean fclean re

-include ./objs/*.d

.NOTPARALLEL:fclean