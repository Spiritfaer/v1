#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: istalevs <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/12 13:33:32 by istalevs          #+#    #+#              #
#    Updated: 2018/05/12 13:33:34 by istalevs         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

.PHONY: clean fclean re norm all b1 build bclean allclean

SRC_PATH	= ./src/
OBJ_PATH	= ./obj/
INC_PATH	= ./include/
BUILD_PATH	= ./build/

NAME		= libvmth.a
CC			= gcc
CFLAG		= -Wall -Wextra -Werror

SRC_NAME	= vec_2d.c vec_2i.c vec_2add.c vec_2sub.c \
				vec_2mul.c vec_2fmul.c vec_2magnitude.c \
				vec_2norm.c vec_2normalize.c vec_2dot.c \
				vec_2drot.c vec_2dscale.c \
				vec_3d.c vec_3i.c vec_3add.c vec_3sub.c \
				vec_3mul.c vec_3fmul.c vec_3magnitude.c \
				vec_3norm.c vec_3normalize.c vec_3dot.c \
				vec_3drot.c vec_3drotate.c vec_3dscale.c \
				vec_3dreflect.c vec_inters.c \
				vec_1zero.c vec_1right.c vec_1back.c vec_1up.c

OBJ_NAME	= $(SRC_NAME:.c=.o)

SRC			= $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ			= $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC			= $(addprefix -I,$(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAG) $(INC) -o $@ -c $<

norm:
	@norminette $(SRC) $(INC_PATH)vmth.h

clean:
	@rm -rf $(OBJ_PATH)
	@echo "clean was done"

fclean: clean
	@rm -Rf $(NAME)
	@echo "fclean was done"

bclean:
	@rm -rf $(BUILD_PATH)
	@echo "bclean was done"

tclean:
	@rm -rf test
	@echo "tclean was done"

allclean: fclean bclean
	@echo "allclean was done"

cl: allclean tclean

re: fclean all

test: main.c $(NAME)
	@$(CC) $(CFLAG) -L. -l vmth -I ./include/ main.c -o test
	@echo "test.exe is ready"

b1: $(NAME)
	@mkdir -p $(BUILD_PATH)
	@cp $(NAME) $(BUILD_PATH)
	@cp $(INC_PATH)*.h $(BUILD_PATH)

build: b1 fclean
	@echo "build is ready"
