/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybord.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:54:08 by hibenouk          #+#    #+#             */
/*   Updated: 2024/07/16 15:56:18 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <cstdio>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "MLX42/MLX42.h"
#include "cub3D.h"

void put_point_grid(t_data *data, t_vec2f point, int color)
{
	t_vec2d	vec;

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


void keybord(mlx_key_data_t keydata, void *param)
{
	t_data *data;

	data = param;
	if (MLX_KEY_ESCAPE == keydata.key)
		mlx_close_window(data->mlx);
	if (keydata.key == MLX_KEY_RIGHT)
		data->player_angle = (data->player_angle < 360) * (data->player_angle + ROTATE_SEEP);
	else if (keydata.key == MLX_KEY_LEFT)
		data->player_angle =
			(data->player_angle >= 0) * (data->player_angle - ROTATE_SEEP) + (data->player_angle < 0) * 360;

	game(data, WIDTH);


}

