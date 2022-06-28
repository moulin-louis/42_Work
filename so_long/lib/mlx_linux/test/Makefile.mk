MAKEFLAGS += --silent

INC=%%%%

INCLIB=$(INC)/../lib

UNAME := $(shell uname)

CFLAGS= -I$(INC) -O3 -I.. -g

NAME= mlx-test
SRC = main.c
OBJ = $(SRC:%.c=%.o)

LFLAGS = -L.. -lmlx -L$(INCLIB) -lXext -lX11 -lm

ifeq ($(UNAME), Darwin)
	# mac
	CC = clang
else ifeq ($(UNAME), FreeBSD)
	# FreeBSD
	CC = clang
else
	#Linux and others...
	CC	= gcc
	LFLAGS += -lbsd
endif

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(LFLAGS)

clean:
	@rm -f $(NAME) $(OBJ) *~ core *.core

re: clean all
