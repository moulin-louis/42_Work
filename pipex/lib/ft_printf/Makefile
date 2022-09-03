# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/11 12:36:33 by anclarma          #+#    #+#              #
#    Updated: 2022/09/03 14:47:50 by loumouli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED=\033[0;91m
GREEN=\033[0;92m
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
NAME		= ft_printf

# ################################## #
#               SOURCES              #
# ################################## #
C_DIR		= srcs
C_FILES		= 	ft_printf.c \
				ft_printf_adress_printf.c \
				ft_putnbr_base_printf.c \
				ft_putnbr_printf.c \
				ft_putunbr_printf.c

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

CINCLUDES	= -I ./inc


# ################################## #
#                RULES               #
# ################################## #

$(O_DIR)/%.o: $(C_DIR)/%.c
			@$(CC) $(CFLAGS) $(CINCLUDES) -c $< -o $@

all:		$(NAME)

$(NAME):	$(O_DIR) $(LIBFT) $(OBJS)
			@ar -rcs ft_printf.a ${OBJS}
			@echo "${GREEN}- compiling ft_printf library${RESET}"

$(O_DIR):
			@$(MKDIR) $(O_DIR)
			@echo "${GREEN}- creating ft_printf objects directory${RESET}"

$(LIBFT):
			@make -C ./libft --no-print-directory

clean:
			@$(RM) $(O_DIR)
			@echo "${RED}- deleting ft_printf objects${RESET}"

fclean:		clean
			@$(RM) $(NAME)
			@echo "${RED}- delete ft_printf library${RESET}"

re:			fclean all

.PHONY: all check clean fclean re
