NAME	=		retromfa

CC 		=		cc

SRC_DIR = 		$(shell find srcs -type d)

INC_DIR =		$(shell find srcs -type d) \
				$(shell find libft -type d) \
				$(shell find minilibx-linux -type d)

LIB_DIR = 		./libft \
				./minilibx-linux

LIB = 			ft \
				mlx \
				m \
				bsd \
				X11 \
				Xext

LIBFT = 		./libft/libft.a
LIBMLX = 		./minilibx-linux/libmlx_Linux.a

OBJ_DIR = 			objs

vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)
vpath %.a $(foreach dir, $(LIB_DIR), $(dir):)

PARSING_FILES = entry_point.c

RENDER_FILES = init_mlx.c quit_mlx.c routine.c

RENDERING_TOOLS = draw_mfa_image.c draw_bmp.c draw_pxl.c

CONSTRUCTORS = make_color.c make_int2.c

DATA_HANDLING = read_file.c

SRC 	=	main.c \
			${PARSING_FILES} \
			${RENDER_FILES} \
			${RENDERING_TOOLS} \
			${CONSTRUCTORS} \
			${DATA_HANDLING}

OBJ	=				$(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

CFLAGS	=		-Wall -Wextra -Werror

IFLAGS	=		$(foreach dir, $(INC_DIR), -I$(dir))

LFLAGS	=		$(foreach dir, $(LIB_DIR), -L $(dir)) \
				$(foreach lib, $(LIB), -l $(lib))

BUILD_LOG = logs/Makefile.log

# Colors
_GREY=	$'\033[30m
_RED=	$'\033[31m
_GREEN=	$'\033[32m
_YELLOW=$'\033[33m
_BLUE=	$'\033[34m
_PURPLE=$'\033[35m
_CYAN=	$'\033[36m
_WHITE=	$'\033[37m

DEBUG =
ifeq ($(DEBUG), fs)
	CFLAGS += -fsanitize=address
	CFLAGS += -g3
	CFLAGS += -O0
	msg = $(shell echo "$(_PURPLE)fsanitize and debug flags are added.$(_WHITE)")
	useless := $(info $(msg))
else ifeq ($(DEBUG), vl)
	CFLAGS += -g3
	CFLAGS += -O0
	msg = $(shell echo "$(_PURPLE)Valgrind and debug flags are added. Take care to rebuild the program entirely if you already used valgrind.$(_WHITE)")
	useless := $(info $(msg))
else ifeq ($(DEBUG), gdb)
	CFLAGS += -g3
	CFLAGS += -O0
	msg = $(shell echo "$(_PURPLE)gdb and debug flags are added.$(_WHITE)")
	useless := $(info $(msg))
else
	CFLAGS += -O3
	msg = $(shell echo "$(_PURPLE)Debug mode not enabled. Optimization flags are added.$(_WHITE)")
	useless := $(info $(msg))
endif

msg = $(shell echo "$(_PURPLE)A file named $(_YELLOW)$(BUILD_LOG)$(_PURPLE) contain the current build informations.$(_WHITE)")
useless := $(info $(msg))

# Make sure the logs directory exists.
useless := $(shell mkdir -p logs)

# Split the log file between each run.
useless := $(shell echo "________________________________________________________________________________" >> $(BUILD_LOG); \
				echo "$(shell date) : \c" >> $(BUILD_LOG); \
				echo "building with : [$(MAKECMDGOALS)]" >> $(BUILD_LOG))

all:			$(NAME)
				@echo "$(_PURPLE)Usage:"
				@echo "Type $(_BLUE)make$(_PURPLE) to create one binary $(_BLUE)${NAME}${_PURPLE}"
				@echo "Add $(_BLUE)DEBUG=fs$(_PURPLE) to compile with fsanitize and debug flags."
				@echo "Add $(_BLUE)DEBUG=vl$(_PURPLE) to compile with valgrind and debug flags."
				@echo "Add $(_BLUE)DEBUG=gdb$(_PURPLE) to compile with gdb and debug flags.$(_WHITE)"

# Compile every library.
%.a:
				@echo "-----\nBuilding $(_YELLOW)$@$(_WHITE) ... \c"
				$(shell echo "$(shell date) : \c" >> $(BUILD_LOG) 2>&1 ; echo "building submodules">> $(BUILD_LOG) 2>&1)
				$(eval ret_status := $(shell ./verif_submodules.sh >> $(BUILD_LOG) 2>&1; echo $$?))
				@if [ $(ret_status) -eq 0 ]; then \
					echo "$(_GREEN)DONE$(_WHITE)\n-----"; \
				else \
					echo "$(_RED)FAILED$(_WHITE)\n-----"; \
					exit $(ret_status); \
				fi
				@echo "\n$(_BLUE)___$(notdir $@) Setting___\n$(_WHITE)"
				@make --no-print-directory -C $(dir $@) DEBUG=$(DEBUG)

re-install:
				@$(foreach dir, $(LIB_DIR), make --no-print-directory -C $(dir) DEBUG=$(DEBUG) re ; )

$(NAME):		$(LIBFT) $(LIBMLX) $(OBJ)
				@echo "-----\nCompiling $(_YELLOW)$@$(_WHITE) ... \c"
				$(shell echo "$(shell date) : \c" >> $(BUILD_LOG) 2>&1 ; echo "$(CC) $(CFLAGS) $(IFLAGS) $(OBJ) $(LFLAGS) -o $@" >> $(BUILD_LOG) 2>&1)
				$(eval ret_status := $(shell $(CC) $(CFLAGS) $(IFLAGS) $(OBJ) $(LFLAGS) -o $@ >> $(BUILD_LOG) 2>&1; echo $$?))
				@if [ $(ret_status) -eq 0 ]; then \
					echo "$(_GREEN)DONE$(_WHITE)\n-----"; \
				else \
					echo "$(_RED)FAILED$(_WHITE)\n-----"; \
					exit $(ret_status); \
				fi

show:
				@echo "\nSRC :\n$(SRC)\n"
				@echo "OBJ :\n$(OBJ)\n"
				@echo "CFLAGS :\n$(CFLAGS)\n"
				@echo "IFLAGS :\n$(IFLAGS)\n"
				@echo "LIB_DIR :\n$(LIB_DIR)\n"
				@echo "LFLAGS :\n$(LFLAGS)\n"

$(OBJ_DIR)/%.o : 	%.c
				@echo "Compiling $(_YELLOW)$@$(_WHITE) ... \c"
				$(shell mkdir -p $(OBJ_DIR))
				$(shell echo "$(shell date) : \c" >> $(BUILD_LOG) 2>&1 ;\
				echo "$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<" >> $(BUILD_LOG) 2>&1)
				$(eval ret_status := $(shell $(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $< >> $(BUILD_LOG) 2>&1; echo $$?))
				@if [ $(ret_status) -eq 0 ]; then \
					echo "$(_GREEN)DONE$(_WHITE)\n-----"; \
				else \
					echo "$(_RED)FAILED$(_WHITE)\n-----"; \
					exit $(ret_status); \
				fi

re:				fclean all

clean_log:
				@echo "Cleaning $(_YELLOW)$(BUILD_LOG)$(_WHITE) ... \c"
				@cp /dev/null $(BUILD_LOG)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----";

clean:
				@echo "Deleting Objects Directory $(_YELLOW)$(OBJ_DIR)$(_WHITE) and $(_YELLOW)$(GAME_OBJ_DIR)$(_WHITE) ... \c"
				@rm -rf $(OBJ_DIR)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

fclean:			clean clean_log
				@echo "Deleting binaries $(_YELLOW)$(NAME)$(_WHITE) and $(_YELLOW)$(GAME_NAME)$(_WHITE)... \c"
				@rm -f $(NAME)
				@echo "$(_GREEN)DONE$(_WHITE)\n-----"

.PHONY:			all show re clean fclean clean_log