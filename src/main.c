/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:12:51 by zkotbi            #+#    #+#             */
/*   Updated: 2024/07/02 22:06:15 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include "MLX42/MLX42.h"
#include "cub3D.h"

// // -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

// -----------------------------------------------------------------------------
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
				put_pixels(data->image, vec2d(j * GRID_X, i * GRID_Y), vec2d(GRID_X - 1, GRID_Y - 1), 0xFFFFFFFF);
			else if (map[i][j] == 'W')
			{
				pos = vec2d(j * GRID_X, i * GRID_Y);
				put_pixels(data->image, vec2d(j * GRID_X, i * GRID_Y), vec2d(GRID_X - 1, GRID_Y - 1), 0xFF8F00ff);
			}
			else if (map[i][j] == '0')
				put_pixels(data->image, vec2d(j * GRID_X, i * GRID_Y), vec2d(GRID_X - 1, GRID_Y - 1), 0xFF8F00ff);
		}
	}
	return (pos);
}

bool cmp_float(double x, double y)
{
	if (fabs(x - y) < 1e-4)
		return (1);
	return (0);
}

// take a point in grid coord;
// this may sig fault if vec + size is out of boundary
void put_point(t_data *data, t_vec2d vec)
{
	put_pixels(data->image, vec, vec2d(8, 8), 0xFF0000FF);
}

double sign(double n)
{
	return ((n >= 0) - (n < 0));
}

double snap(double x, double dx)
{
	if (dx > 0)
		return (ceil(x + sign(dx) * eps));
	else if (dx < 0)
		return (floor(x + sign(dx) * eps));
	return x;
}

// start and end are grid coord
t_vec2d ray_casting(t_vec2f p1, t_vec2f d)
{
	double x3 = 0, y3 = 0;

	if (d.x != 0)
	{
		double m = d.y / d.x;
		double c = p1.y - p1.x * m;
		double x2 = snap(p1.x, d.x);
		double y2 = x2 * m + c;
		if (m != 0)
		{
			y3 = snap(p1.y, d.y);
			x3 = (y3 - c) / m;
		}
		t_vec2f a = vec2f(x2, y2);
		t_vec2f b = vec2f(x3, y3);
		t_vec2f p2 = min_distance(a, b, p1);
		t_vec2d p = vec2d(p2.x * GRID_X, p2.y * GRID_Y);
		return (p);
	}
	else
	{
		y3 = snap(p1.y, d.y);
		x3 = p1.x;
		t_vec2d dv = vec2d(x3 * GRID_X, y3 * GRID_Y);
		return (dv);
	}
	exit(1);
	return (vec2d(0, 0));
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
	t_data data;
	t_param *param;

	param = parser_and_error_check("./maps/map2.cub");
	print_map(param);

	data = init_screen();
	data.param = param;
	t_vec2d pos = mini_map_render(&data, data.param->map_data);
	// // f(&data, 1023, 511);

	put_pixels(data.image, pos, vec2d(GRID_X / 3, GRID_Y / 3), 0x050C9CFF);
	t_vec2d pos2 = {.x = 64 * 2, .y = 4 * GRID_Y};
	data.pos = pos2;
	// data.pos = pos2;
	// // data.map = map;
	// put_point(&data, pos2);
	// t_vec2d point = pos;
	// for (int i = 0; i < 6; i++)
	// {
	// 	point = ray_casting(grid(point), grid(pos2));
	// 	put_point(&data, point);
	// }

	// // ray_casting(&data, grid(pos), grid(pos3));;
	// // for(double m = 0.5f; m < 100.0f;m += 0.5f){
	// // put_player_ray(player, p);
	// // }

	mlx_key_hook(data.mlx, keybord, &data);
	// // mlx_loop_hook(data.mlx, ft_hook, &data);

	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
// int main(int argc, char *argv[])
// {
// 	t_param *param;

// 	param = parser_and_error_check(argv[1]);
// 	t_map *data = param->map_data;
// 	return EXIT_SUCCESS;
// }
