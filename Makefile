# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/24 09:38:52 by hibenouk          #+#    #+#              #
#    Updated: 2024/08/13 09:11:44 by zkotbi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME        = cub3D

CC          = cc

INC         = -Iinclude -I$(HOME)/.brew/include       

CFLAGS      = -Wall -Wextra -Werror $(INC)  #-fsanitize=address  -O3 -Ofast

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
		./mlx_hooks/draw_utils.c \
		./mlx_hooks/keybord.c \
		./parsing/error.c \
		./parsing/error_handle_utils.c \
		./parsing/allocate_file.c \
		./parsing/free.c \
		./parsing/free_utils.c \
		./parsing/get_param.c \
		./parsing/init_textures.c \
		./parsing/map_verification.c \
		./parsing/map_verification_utils.c \
		./parsing/parser_error_handle.c \
		./parsing/parser_map.c \
		./raycasting/raycasting.c \
		./src/game.c \
		./src/init.c \
		./src/main.c 

OBJS        = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) include/cub3d.h
	$(CC) $(CFLAGS) $(LIB) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o:  $(SRC_DIR)%.c include/cub3d.h
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
