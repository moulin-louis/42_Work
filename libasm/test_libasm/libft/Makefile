###############
## Variables ##
###############

NAME		=	libft.a
## add library here (minilibx, ncurses, libft, ...)
INCLDIR		=	$(addsuffix /inc,$(LIBDIR) .)
BUILDIR		=	build
DEPDIR		=	$(BUILDIR)/.deps
SRCS_DIR	=	$(sort $(dir $(wildcard src/*/)))
SRC			=	$(addprefix src/,			\
						ft_atoi.c 			\
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
						$(addprefix DO_NOT_DELETE/,	\
                        )					\
				)

OBJ			=	$(SRC:%.c=$(BUILDIR)/%.o)
DEP			=	$(SRC:%.c=$(DEPDIR)/%.d)
CXX			=	gcc
CXXFLAGS	=	-g -Wall -Werror -Wextra
CPPFLAGS	=	$(addprefix -I, $(INCLDIR))
DEPFLAGS	=	-MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
RM			=	/bin/rm -rf

# FG COLORS
DEFAULT		=	\033[0m
BLACK		=	\033[1;30m
RED			=	\033[1;31m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
MAGENTA 	=	\033[1;35m
CYAN 		=	\033[1;36m
WHITE 		=	\033[1;107m

# TERMCAPS
UP			=	\033[1A
DELETE		=	\033[2K
DELPREV		=	$(UP)$(DELETE)\r

# EMOJI
CHECK		=	\xE2\x9C\x94
CROSS		=	\xE2\x9D\x8C

# DISPLAY
HEAD_SIZE	=	32
BODY_WIDTH	=	$(shell printf "$$(($(HEAD_SIZE) - 1))")

###########
## Rules ##
###########

.PHONY:			all bonus clean fclean header lib re verbose

all:
				@$(MAKE) -s $(NAME)

$(BUILDIR)/%.o:	%.c | $(DEPDIR)
				@mkdir -p build/ $(addprefix build/, $(SRCS_DIR))
				@mkdir -p build/.deps/ $(addprefix build/.deps/, $(SRCS_DIR))
				@printf "$(YELLOW)Compiling $(BLUE)$@$(DEFAULT)$(YELLOW) and generating/checking make dependency file...$(DEFAULT)\n"
				@$(CXX) $(DEPFLAGS) $(CXXFLAGS) -c $< -o $@
				@printf '$(DELPREV)%-*s$(GREEN)$(CHECK)$(DEFAULT)\n' $(BODY_WIDTH) $(notdir $@)

$(NAME):		$(OBJ)
				@printf "$(YELLOW)Linking source files and generating $(CYAN)$@$(DEFAULT) $(YELLOW)library...\n$(DEFAULT)"
				@ar -rcs $@ $(OBJ)
				@printf "$(DELPREV)$(GREEN)Library generated$(DEFAULT)\n"

$(DEPDIR):
				@printf "$(YELLOW)Creating $(BLUE)$@$(DEFAULT)$(YELLOW) folder...$(DEFAULT)\n"
				@mkdir -p $@
				@printf "$(DELPREV)"
$(DEP):
-include $(wildcard $(DEP))

clean:
				@printf "$(YELLOW)Deleting object and dependency files...$(DEFAULT)\n"
				@$(RM) $(OBJ)
				@printf "$(DELPREV)Build files deleted\n"

fclean:			clean
				@printf "$(YELLOW)Deleting build directory...$(DEFAULT)\n"
				@$(RM) $(BUILDIR) $(NAME) temp
				@printf "$(DELPREV)Build directory and library deleted\n"

re:				fclean
				@$(MAKE) -s all

