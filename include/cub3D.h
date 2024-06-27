/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 23:29:00 by zkotbi            #+#    #+#             */
/*   Updated: 2024/06/27 15:48:49 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <MLX42/MLX42.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 800

typedef struct s_data
{
	mlx_t *mlx;
	mlx_image_t *image;
}t_data;

typedef struct s_vec2d
{
	int x;
	int y;
}t_vec2d;

/*-----error_handle-----*/
void	error_check(char *argv);
int		extension_check(char *argv);

/*-----LIBFT-----*/
void	fd_putstr(const char *str, int fd);


//math
t_vec2d vec2d(int x, int y);
#endif
