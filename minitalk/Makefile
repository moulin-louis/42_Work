# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/11 12:36:33 by anclarma          #+#    #+#              #
#    Updated: 2022/09/26 16:36:47 by loumouli         ###   ########.fr        #
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
NAME_CLIENT		= client
NAME_SERVER		= server

# ################################## #
#               SOURCES              #
# ################################## #
C_DIR_CLIENT		= srcs_client
C_FILES_CLIENT		=	main.c
SRCS_CLIENT		= $(patsubst %, $(C_DIR_CLIENT)/%, $(C_FILES_CLIENT))

C_DIR_SERVER		= srcs_server
C_FILES_SERVER		=	main.c \
						ft_realloc_str.c
SRCS_SERVER		= $(patsubst %, $(C_DIR_SERVER)/%, $(C_FILES_SERVER))

# ################################## #
#               OBJECTS              #
# ################################## #
O_DIR_CLIENT		= objs_client
O_FILES_CLIENT		= $(C_FILES_CLIENT:.c=.o)
OBJS_CLIENT		= $(patsubst %, $(O_DIR_CLIENT)/%, $(O_FILES_CLIENT))

O_DIR_SERVER		= objs_server
O_FILES_SERVER		= $(C_FILES_SERVER:.c=.o)
OBJS_SERVER		= $(patsubst %, $(O_DIR_SERVER)/%, $(O_FILES_SERVER))

# ################################## #
#                FLAGS               #
# ################################## #
CFLAGS		= -Wall -Wextra -Werror -g -O2

CINCLUDES	= -I ./inc	\
			  -I ./lib

FT_PRINTF	= ./ft_printf/ft_printf.a

CLIBS		= -L./ft_printf/ftprintf

# ################################## #
#                RULES               #
# ################################## #

all:		$(NAME_CLIENT) $(NAME_SERVER)


#compiling client


$(NAME_CLIENT):	$(O_DIR_CLIENT) $(OBJS_CLIENT)  $(FT_PRINTF)
			@$(CC) $(CFLAGS) $(OBJS_CLIENT) $(FT_PRINTF) -o $(NAME_CLIENT)

#compiling objs in folder
$(O_DIR_CLIENT)/%.o: $(C_DIR_CLIENT)/%.c
			@$(CC) $(CFLAGS) $(CINCLUDES) -c $< -o $@

#creating folder for objs
$(O_DIR_CLIENT):
			@$(MKDIR) $(O_DIR_CLIENT)
			@echo "${GREEN}- creating minitalk_client objects directory${RESET}"


#compiling server


$(NAME_SERVER): $(O_DIR_SERVER) $(OBJS_SERVER) $(FT_PRINTF)
			@$(CC) $(CFLAGS) $(OBJS_SERVER) $(FT_PRINTF) -o $(NAME_SERVER)

#compiling objs in folder
$(O_DIR_SERVER)/%.o: $(C_DIR_SERVER)/%.c
			@$(CC) $(CFLAGS) $(CINCLUDES) -c $< -o $@

#creating folder for objs
$(O_DIR_SERVER):
			@$(MKDIR) $(O_DIR_SERVER)
			@echo "${GREEN}- creating minitalk_server objects directory${RESET}"

# ################################## #
#             DEPENDECIES...         #
# ################################## #

$(FT_PRINTF):
			@make -C ./lib/ft_printf --no-print-directory

# ################################## #
#                CLEAN               #
# ################################## #

clean:
			@$(RM) $(O_DIR_CLIENT)
			@$(RM) $(O_DIR_SERVER)
			@make -C ./ft_printf clean --no-print-directory
			@echo "${RED}- deleting minitalk objects${RESET}"

fclean:		clean
			@$(RM) $(NAME_CLIENT)
			@$(RM) $(NAME_SERVER)
			@make -C ./ft_printf fclean --no-print-directory
			@echo "${RED}- delete minitalk executable${RESET}"

re:			fclean all

.PHONY: all check clean fclean re
