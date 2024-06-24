# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/24 09:38:52 by hibenouk          #+#    #+#              #
#    Updated: 2024/06/24 09:43:20 by hibenouk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -fsanitize=address -g3 -ggdb
INC			= ./include/
RM			= rm -rf

all: $(NAME)

$(LIBFT):
	@make -C $(LIBRAIRIE)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) -o $(NAME) $(OBJS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C $(LIBRAIRIE)
	@$(RM) $(OBJS)

fclean: clean
	@make fclean -C $(LIBRAIRIE)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
