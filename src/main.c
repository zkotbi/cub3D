/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:12:51 by zkotbi            #+#    #+#             */
/*   Updated: 2024/07/04 14:59:10 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include "MLX42/MLX42.h"
#include "cub3D.h"




mlx_image_t *new_image_to_window(t_data *data, t_vec2d pos, t_vec2d size)
{
	mlx_image_t *image;
	if (!(image = mlx_new_image(data->mlx, size.x, size.y)))
	{
		mlx_close_window(data->mlx);
		fd_putstr(mlx_strerror(mlx_errno), 2);
		exit(1);
	}

	if (mlx_image_to_window(data->mlx, image, pos.x, pos.y) == -1)
	{
		mlx_close_window(data->mlx);
		fd_putstr(mlx_strerror(mlx_errno), 2);
		exit(1);
	}
	return (image);
}

t_data init_screen(void)
{
	t_data data;
	// Gotta error check this stuff
	if (!(data.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		exit(1);
	}
	data.image = new_image_to_window(&data, vec2d(0, 0), vec2d(WIDTH, HEIGHT));
	data.player_angle  = 90.0f;
	return (data);
}

void put_pixels(mlx_image_t *image, t_vec2d coord, t_vec2d size, int color)
{
	for (int i = coord.x; i < coord.x + size.x; i++)
	{
		for (int j = coord.y; j < coord.y + size.y; j++)
			mlx_put_pixel(image, i, j, color);
	}
}

// refactor this later from mini map
t_vec2d mini_map_render(t_data *data, t_map *map_data)
{
	t_vec2d pos = {0};
	char **map;

	map = map_data->map;
	for (int i = 0; i < map_data->sizes->y; i++)
	{
		for (int j = 0; j < map_data->sizes->x; j++)
		{
			if (map[i][j] == '1')
				put_pixels(
					data->image, vec2d(j * CELLSIZE, i * CELLSIZE), vec2d(CELLSIZE - 1, CELLSIZE - 1), 0xFFFFFFFF);
			else if (map[i][j] == 'W')
			{
				pos = vec2d(j * CELLSIZE, i * CELLSIZE);
				put_pixels(
					data->image, vec2d(j * CELLSIZE, i * CELLSIZE), vec2d(CELLSIZE - 1, CELLSIZE - 1), 0xFF8F00ff);
			}
			else if (map[i][j] == '0')
				put_pixels(
					data->image, vec2d(j * CELLSIZE, i * CELLSIZE), vec2d(CELLSIZE - 1, CELLSIZE - 1), 0xFF8F00ff);
		}
	}
	return (pos);
}


void print_map(t_param *param)
{
	t_map *map_data = param->map_data;

	char **map = map_data->map;
	for (int i = 0; i < map_data->sizes->y; i++)
	{
		printf("|");
		for (int j = 0; j < map_data->sizes->x; j++)
			printf("%c", map[i][j]);
		printf("|\n");
	}
}

int main(int ac, char **argv)
{
	(void)ac;
	t_data data;
	t_param *param;

	param = parser_and_error_check("./maps/map2.cub");
	print_map(param);

	data = init_screen();
	data.param = param;
	mini_map_render(&data, data.param->map_data);
	mlx_key_hook(data.mlx, keybord, &data);

	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
