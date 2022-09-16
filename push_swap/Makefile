# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: loumouli <loumouli@>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/11 12:36:33 by anclarma          #+#    #+#              #
#    Updated: 2022/09/10 21:08:41 by loumouli         ###   ########.fr        #
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
NAME		= push_swap

# ################################## #
#               SOURCES              #
# ################################## #
C_DIR		= srcs
C_FILES		= main.c		\
			check_input.c \
			init.c \
			utility.c \
			utility2.c \
			instruc_push.c \
			instruc_r_rotate.c \
			instruc_rotate.c \
			instruc_swap.c \
			sort_3.c \
			sort_4_5.c \
			sort_big_list.c \
			ft_split_custom.c

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

CINCLUDES	= -I ./inc	\
			  -I ./libft \

LIBFT		= ./libft/libft.a
CLIBS		= -L./libft -lft

# ################################## #
#                RULES               #
# ################################## #

all:		$(NAME)

$(NAME):	$(O_DIR) $(LIBFT) $(OBJS)
			@$(CC) $(OBJS) $(LFLAGS) $(CLIBS) -o $@
			@echo "${GREEN}- compiling push_swap executable${RESET}"

$(O_DIR)/%.o: $(C_DIR)/%.c
			$(CC) $(CFLAGS) $(CINCLUDES) -c $< -o $@

$(O_DIR):
			@$(MKDIR) $(O_DIR)
			@echo "${GREEN}- creating push_swap objects directory${RESET}"

# ################################## #
#             DEPENDECIES...         #
# ################################## #

$(LIBFT):
			@make -C ./libft --no-print-directory

# ################################## #
#                CLEAN               #
# ################################## #

clean:
			@$(RM) $(O_DIR)
			@make -C ./libft fclean --no-print-directory
			@echo "${RED}- deleting push_swap objects${RESET}"

fclean:		clean
			@$(RM) $(NAME)
			@echo "${RED}- delete push_swap executable${RESET}"

re:			fclean all

malloc_test: $(O_DIR) $(LIBFT) $(OBJS)
			$(CC) $(CFLAGS) -fsanitize=undefined -rdynamic -o $@ ${OBJS} -L./libft -lft -L. -lmallocator

.PHONY: all check clean fclean re
