# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/24 09:38:52 by hibenouk          #+#    #+#              #
#    Updated: 2024/07/02 12:05:25 by hibenouk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME        = cub3D

CC          = cc

INC         = -Iinclude -I$(HOME)/.brew/include

CFLAGS      = -Wall -Wextra -g3 -ggdb -fsanitize=address $(INC) 

OBJ_DIR     = ./obj/

SRC_DIR     = ./

LIB =  -L$(HOME)/.brew/lib/ -lmlx42 -lglfw

SRCS        = $(shell find $(SRC_DIR) -type f -name "*.c" | grep -v test)

OBJS        = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))


all: $(NAME) run

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LIB) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o:  $(SRC_DIR)%.c | $(OBJ_DIR) 
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
run :
	./$(NAME)


.PHONY: all clean fclean re
