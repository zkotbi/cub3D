# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/24 09:38:52 by hibenouk          #+#    #+#              #
#    Updated: 2024/06/24 10:26:15 by hibenouk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME		= cub3D
# CC			= cc
# CFLAGS		= -Wall -Wextra -Werror -fsanitize=address -g3 -ggdb
# INC			= ./include

# OBJ_DIR = ./obj/
# SRC_DIR = ./


# SRCS = $(shell find . -type f -name "*.c"  | cut -c3-)

# OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))


# all: $(NAME)


# $(NAME): $(OBJS) 
# 	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# $(OBJ_DIR)%.o: $(SRC_DIR)%.c
# 	@echo $< $@
# 	$(CC) -c $(CFLAGS) $< -o $@


NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -fsanitize=address -g3 -ggdb -I$(INC)
INC         = ./include

OBJ_DIR     = ./obj/
SRC_DIR     = ./

SRCS        = $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS        = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))


all: dir $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
dir :
	mkdir -p obj

.PHONY: all clean fclean re
