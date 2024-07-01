/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:12:51 by zkotbi            #+#    #+#             */
/*   Updated: 2024/07/01 16:58:38 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_vec2d mini_map_render(t_data *data, char map[][16])
{
	t_vec2d pos = {0};
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (map[i][j] == '1')
				put_pixels(data->image, vec2d(j * GRID_X, i * GRID_Y), vec2d(GRID_X - 1, GRID_Y - 1), 0xFFFFFFFF);
			else if (map[i][j] == 'W')
			{
				pos = vec2d(j * GRID_X, i * GRID_Y);
				put_pixels(data->image, vec2d(j * GRID_X, i * GRID_Y), vec2d(GRID_X - 1, GRID_Y - 1), 0xFF8F00ff);
			}
			else
				put_pixels(data->image, vec2d(j * GRID_X, i * GRID_Y), vec2d(GRID_X - 1, GRID_Y - 1), 0xFF8F00ff);
		}
	}
	return (pos);
}

/*
 *
	OldRange = (OldMax - OldMin)
	NewRange = (NewMax - NewMin)
	NewValue = (((OldValue - OldMin) * NewRange) / OldRange) + NewMin
*/

// scale(c.a, 2, -2, param->width)

double scale(double a, double n_max, double n_min, double o_max)
{
	return ((a * (n_max - n_min)) / o_max + n_min);
}

bool cmp_float(double x, double y)
{
	if (fabs(x - y) < 1e-4)
		return (1);
	return (0);
}

void draw_line(mlx_image_t *image, t_vec2f start, t_vec2f end)
{
	double m;
	double c;

	m = (start.y - end.y) / (start.x - end.x);
	c = start.y - m * start.x;
	for (uint32_t i = 0; i < image->width; i++)
	{
		for (uint32_t j = 0; j < image->height; j++)
		{
			if (cmp_float((double)i * m + c, (double)j))
				mlx_put_pixel(image, i, j, 0xFFDB5CFF);
		}
	}
}
// x' = x * cos(theta) - y * sin(theta)
// y' = x * sin(theta) _ y * costheta)
double deg_to_rad(double deg)
{
	double rad;

	rad = deg * PI;
	rad = rad / 180.0f;
	return (rad);
}
t_vec2f rotate(t_vec2f vec, double angle)
{
	t_vec2f new_vec;

	angle = deg_to_rad(angle);
	new_vec.x = vec.x * cos(angle) - vec.y * sin(angle);
	new_vec.x = vec.x * sin(angle) + vec.y * cos(angle);
	FVEC(new_vec);
	return (new_vec);
}
void put_player_ray(mlx_image_t *player, t_vec2d p)
{
	t_vec2f vec = {32, 32};
	put_pixels(player, p, vec2d(player->width / 3, player->height / 3), 0xFFDB5CFF);

	// for (int i = 0;i<=90;i++)
	// {
	// 	vec = rotate(vec,  i);
	// 	draw_line(player, vec2f(0, 0), vec);
	// }
}
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
	const double eps = 1e-3;
	if (dx > 0)
		return (ceil(x + sign(dx) * eps));
	else if (dx < 0)
		return (floor(x + sign(dx) * eps));
	return x;
}

// start and end are grid coord
t_vec2d ray_casting(t_data *data, t_vec2f start, t_vec2f end)
{
	t_vec2f d;
	double x3 = 0, y3 = 0;

	d = sub2f(end, start);
	FVEC(d)
	if (d.x != 0)
	{
		double m = d.y / d.x;
		double c = start.y - start.x * m;
		double x2 = snap(start.x, d.x);
		double y2 = x2 * m + c;
		if (m != 0)
		{
			FINT(start.y)
			y3 = snap(start.y, d.y);
			x3 = (y3 - c) / m;
			t_vec2d dv = vec2d(x3 * GRID_X, y3 * GRID_Y);
			VEC(dv)
		}
		t_vec2f a = vec2f(x2, y2);
		t_vec2f b = vec2f(x3, y3);
		t_vec2f p2 = min_distance(a, b, start);
		t_vec2d p = vec2d(p2.x * GRID_X, p2.y * GRID_Y);
		VEC(p)
		return (p);
	}
	else
	{
		// TODO : this need to be test
		y3 = snap(start.y, d.y);
		x3 = start.x;
		t_vec2d dv = vec2d(x3 * GRID_X, y3 * GRID_Y);
		return (dv);
	}
	return (vec2d(0, 0));
}


int main(void)
{
	t_data data;
	mlx_image_t *player;
	t_vec2d p = {64 / 3, 64 / 3};

	char map[][16] = {
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
		{'1', '0', '0', '0', '0', '1', '1', '1', '0', '1', '0', '0', '1', '1', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '1', '1', '0', '1'},
		{'1', '0', '0', '0', '0', '1', '1', '1', '0', '1', '0', '0', '1', '1', '0', '1'},
		{'1', '0', 'W', '0', '0', '1', '1', '1', '0', '1', '0', '0', '1', '1', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '0', '1', '1', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '1', '1', '0', '1'},
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	};
	data = init_screen();
	player = new_image_to_window(&data, vec2d(WIDTH / 2, HEIGHT / 2), vec2d(64, 64));
	t_vec2d pos = mini_map_render(&data, map);
	// f(&data, 1023, 511);

	put_pixels(data.image, pos, vec2d(GRID_X / 3, GRID_Y / 3), 0x050C9CFF);
	// put_pixels(data.image, vec2d(pos.x, pos.y),vec2d(4, 4), 0xFFFFFFFF);
	t_vec2d pos2 = {.x = 64 * 8, .y = 64};
	data.pos = pos2;
	// data.map = map;
	put_point(&data, pos2);
	t_vec2d point = pos;
	for (int i = 0;i<6;i++)
	{
		point = ray_casting(&data, grid(point), grid(pos2));
		put_point(&data, point);
	}

	// ray_casting(&data, grid(pos), grid(pos3));;
	// for(double m = 0.5f; m < 100.0f;m += 0.5f){
	// put_player_ray(player, p);
	// }

	mlx_key_hook(data.mlx, keybord, &data);
	// mlx_loop_hook(data.mlx, ft_hook, &data);

	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
