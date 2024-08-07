# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/24 09:38:52 by hibenouk          #+#    #+#              #
#    Updated: 2024/08/07 09:43:36 by hibenouk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME        = cub3D

CC          = cc

INC         = -Iinclude -I$(HOME)/.brew/include       

CFLAGS      = -Wall -Wextra -Werror   -g -ggdb3 $(INC)    
# -fsanitize=address
OBJ_DIR     = ./obj/

SRC_DIR     = ./

LIB =  -L$(HOME)/.brew/lib/ -lmlx42 -lglfw

SRCS =  ./libft/ft_atoi.c \
		./libft/ft_putstr.c \
		./libft/ft_split.c \
		./libft/ft_strtrim.c \
		./libft/get_next_line.c \
		./libft/get_next_line_utils.c \
		./math/vec.c \
		./math/vec2.c \
		./mlx_hooks/draw_textures.c \
		./mlx_hooks/keybord.c \
		./parsing/error.c \
		./parsing/error_handle_utils.c \
		./parsing/free.c \
		./parsing/get_param.c \
		./parsing/init_textures.c \
		./parsing/map_verification.c \
		./parsing/parser_error_handle.c \
		./parsing/parser_map.c \
		./parsing/parsing.c \
		./raycasting/raycasting.c \
		./src/game.c \
		./src/init.c \
		./src/main.c 

OBJS        = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))


all: $(NAME) run

$(NAME): $(OBJS) include/cub3d.h
	$(CC) $(CFLAGS) $(LIB) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o:  $(SRC_DIR)%.c include/cub3d.h
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
	./$(NAME) maps/map.cub


.PHONY: all clean fclean re
