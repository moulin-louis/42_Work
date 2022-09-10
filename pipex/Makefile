# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: loumouli <loumouli@>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/11 12:36:33 by anclarma          #+#    #+#              #
#    Updated: 2022/09/10 20:03:43 by loumouli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED=\033[0;91m
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
NAME		= pipex

# ################################## #
#               SOURCES              #
# ################################## #
C_DIR		= srcs
C_FILES		=	main.c \
				ft_utils.c \
				path_utils.c

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
			  -I ./ft_printf \

FT_PRINTF	= ./lib/ft_printf/ft_printf.a
LIBFT		= ./lib/libft/libft.a
CLIBS		= -L ./ft_printf

# ################################## #
#                RULES               #
# ################################## #

all:		$(NAME)

$(NAME):	$(O_DIR) $(FT_PRINTF) $(LIBFT) $(OBJS)
			@$(CC) $(OBJS) $(LFLAGS) $(CLIBS) $(FT_PRINTF) $(LIBFT) -o $@
			@echo "${GREEN}- compiling pipex executable${RESET}"

$(O_DIR)/%.o: $(C_DIR)/%.c
			@$(CC) $(CFLAGS) $(CINCLUDES) -c $< -o $@

$(O_DIR):
			@$(MKDIR) $(O_DIR)
			@echo "${GREEN}- creating pipex objects directory${RESET}"

# ################################## #
#             DEPENDECIES...         #
# ################################## #

$(LIBFT):
			@make -C ./lib/libft --no-print-directory

$(FT_PRINTF):
			@make -C ./lib/ft_printf --no-print-directory

# ################################## #
#                CLEAN               #
# ################################## #

clean:
			@$(RM) $(O_DIR)
			@make -C ./lib/ft_printf clean --no-print-directory
			@make -C ./lib/libft clean --no-print-directory
			@echo "${RED}- deleting pipex objects${RESET}"

fclean:		clean
			@$(RM) $(NAME)
			@make -C ./lib/ft_printf fclean --no-print-directory
			@make -C ./lib/libft fclean --no-print-directory
			@echo "${RED}- delete pipex executable${RESET}"

malloc_test: $(O_DIR) $(FT_PRINTF) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -fsanitize=undefined -rdynamic -o $@ ${OBJS} ${CLIBS} $(FT_PRINTF) $(LIBFT) -L. -lmallocator

re:			fclean all

.PHONY: all check clean fclean re
