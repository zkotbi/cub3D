/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybord.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:54:08 by hibenouk          #+#    #+#             */
/*   Updated: 2024/07/10 17:30:21 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdint.h>
#include <time.h>
#include "MLX42/MLX42.h"
#include "cub3D.h"

void put_point_grid(t_data *data, t_vec2f point, int color)
{
	t_vec2d vec;

	vec = vec2d(point.x * CELLSIZE, point.y * CELLSIZE);
	put_pixels(data->image, vec, vec2d(5, 5), color);
}

void bresenham(t_data *data, t_vec2d p1, t_vec2d p2)
{
	const t_vec2d d = {.x = p2.x - p1.x, .y = p2.y - p1.y};
	const int step = abs((int)max(d.x, d.y));
	const int x_incr = (int)d.x / step;
	const int y_incr = (int)d.y / step;
}

t_vec2d pixels(t_vec2f v)
{
	return (vec2d(v.x * CELLSIZE, v.y * CELLSIZE));
}

void DDALine(t_data *data, t_vec2d v, t_vec2d u)
{
	const t_vec2d d = {.x = u.x - v.x, .y = u.y - v.y};
	int step;
	float x_incr;
	float y_incr;
	float x;
	float y;

	// Calculate dx and dy
	// If dx > dy we will take step as dx
	// else we will take step as dy to draw the complete
	// line
	if (abs(d.x) > abs(d.y))
		step = abs(d.x);
	else
		step = abs(d.y);
	// Calculate x-increment and y-increment for each step
	x_incr = 0;
	y_incr = 0;
	if (step)
	{
		x_incr = (float)d.x / step;
		y_incr = (float)d.y / step;
	}
	// Take the initial points as x and y
	x = v.x;
	y = v.y;
	for (int i = 0; i < step; i++)
	{
		mlx_put_pixel(data->image, round(x), round(y), 0xE4003AFF);
		x += x_incr;
		y += y_incr;
	}
}
void ver_line(t_data *data, int x, int start, int end, int color)
{
	while (start <= end)
	{
		mlx_put_pixel(data->image, x, start, color);
		start++;
	}
}
void color_floor_ceil(t_data *data, int fcolor, int ccolor)
{
	const uint32_t half = data->image->height / 2;


	for (uint32_t i = 0;i<data->image->width;i++)
	{
		for (uint32_t j = 0;j<data->image->height;j++) 
		{
			if (j > half)
				mlx_put_pixel(data->image, i, j, fcolor);
			else
				mlx_put_pixel(data->image, i, j, ccolor);
		}
	}

}
void keybord(mlx_key_data_t keydata, void *param)
{
	t_data *data;
	t_vec2d pos;
	t_vec2f point;
	t_vec2d p;

	data = param;
	if (MLX_KEY_ESCAPE == keydata.key)
		mlx_close_window(data->mlx);
	if (keydata.key == MLX_KEY_LEFT)
		data->player_angle = (data->player_angle < 360) * (data->player_angle + ROTATE_SEEP);
	else if (keydata.key == MLX_KEY_RIGHT)
		data->player_angle =
			(data->player_angle >= 0) * (data->player_angle - ROTATE_SEEP) + (data->player_angle < 0) * 360;
	color_floor_ceil(data, 0x987D9Aff, 0xEECEB9FF);
	pos  =mini_map_render(data, data->param->map_data);
	// pos = *data->param->map_data->pos;
	point = grid(pos);
	t_vec2f tmp = point;

	double delta = FOV / (WIDTH - 1);
	double angle = data->player_angle - FOV / 2;
	for (int x = 0; x < WIDTH; x++)
	{
		angle += delta;
		point = get_wall_postion(data->param->map_data, tmp, angle);
		DDALine(data, pixels(tmp), pixels(point));
		double distance = vec_distance(tmp, point);



		int lineHeight = (int)(HEIGHT / distance);
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		ver_line(data, x, drawStart, drawEnd, 0x1A5319FF);
	}

}
