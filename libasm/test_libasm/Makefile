###############
## Variables ##
###############

NAME		=	test_lib
## add library here (minilibx, ncurses, libft, ...)
INCLDIR		=	$(addsuffix /inc,$(LIBDIR) .)
BUILDIR		=	build
DEPDIR		=	$(BUILDIR)/.deps
SRCS_DIR	=	$(sort $(dir $(wildcard src/*/)))
SRC			=	$(addprefix src/,			\
						main.cpp			\
						$(addprefix test/,	\
							test_read.cpp	\
							test_strcmp.cpp	\
							test_strcpy.cpp	\
							test_strdup.cpp	\
							test_strlen.cpp	\
							test_write.cpp	\
                        )					\
				)

OBJ			=	$(SRC:%.cpp=$(BUILDIR)/%.o)
DEP			=	$(SRC:%.cpp=$(DEPDIR)/%.d)
CXX			=	g++
CXXFLAGS	=	-g -O0 -Wall -Werror -Wextra
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
				@printf "$(YELLOW)Compiling LIBFT...$(DEFAULT)\n"
				@$(MAKE) -C libft --no-print-directory all
				@$(MAKE) -sk $(NAME)

$(BUILDIR)/%.o:	%.cpp | $(DEPDIR)
				@mkdir -p build/ $(addprefix build/, $(SRCS_DIR))
				@mkdir -p build/.deps/ $(addprefix build/.deps/, $(SRCS_DIR))
				@printf "$(YELLOW)Compiling $(BLUE)$@$(DEFAULT)$(YELLOW) and generating/checking make dependency file...$(DEFAULT)\n"
				$(CXX) $(DEPFLAGS) $(CXXFLAGS) -I ./inc -c $< -o $@
				@printf '$(DELPREV)%-*s$(GREEN)$(CHECK)$(DEFAULT)\n' $(BODY_WIDTH) $(notdir $@)

$(NAME):		$(OBJ)
				@printf "$(YELLOW)Linking source files and generating $(CYAN)$@$(DEFAULT) $(YELLOW)binary...\n$(DEFAULT)"
				$(CXX) $(CXXFLAGS) -I ./inc -o $@ $^ -L.. -Llibft -lasm -lft
				@printf "$(DELPREV)$(GREEN)Binary generated$(DEFAULT)\n"

$(DEPDIR):
				@printf "$(YELLOW)Creating $(BLUE)$@$(DEFAULT)$(YELLOW) folder...$(DEFAULT)\n"
				@mkdir -p $@
				@printf "$(DELPREV)"
$(DEP):
-include $(wildcard $(DEP))

clean:
				@printf "$(YELLOW)Deleting object and dependency files...$(DEFAULT)\n"
				@$(RM) $(OBJ)
				@$(RM) libasm.a libft.a
				@printf "$(DELPREV)Build files deleted\n"
				@$(MAKE) -C libft --no-print-directory clean

fclean:			clean
				@printf "$(YELLOW)Deleting build directory...$(DEFAULT)\n"
				@$(RM) $(BUILDIR) $(NAME) temp
				@printf "$(DELPREV)Build directory and binary deleted\n"
				@$(MAKE) -C libft --no-print-directory fclean

re:				fclean
				@$(MAKE) -s all

