/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybord.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:54:08 by hibenouk          #+#    #+#             */
/*   Updated: 2024/07/16 15:28:34 by zkotbi           ###   ########.fr       */
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
	t_vec2f point;
	t_draw draw;

	data = param;
	if (MLX_KEY_ESCAPE == keydata.key)
		mlx_close_window(data->mlx);
	if (keydata.key == MLX_KEY_RIGHT)
		data->player_angle = (data->player_angle < 360) * (data->player_angle + ROTATE_SEEP);
	else if (keydata.key == MLX_KEY_LEFT)
		data->player_angle =
			(data->player_angle >= 0) * (data->player_angle - ROTATE_SEEP) + (data->player_angle < 0) * 360;
	int f = *(int *)&(data->param->floor_color);
	int c = *(int *)&(data->param->celling_color);
	color_floor_ceiling(data, f, c);
	mini_map_render(data, data->param->map_data);
	point = data->param->map_data->pos;
	t_vec2f tmp = point;

	double delta = FOV / (WIDTH - 1);
	double angle = data->player_angle - FOV / 2;
	for (int x = 0; x < WIDTH; x++)
	{
		angle += delta;
		point = get_wall_postion(data->param->map_data, tmp, angle);
		DDALine(data, pixels(tmp), pixels(point));
	    draw.distance = vec_distance(tmp, point);
		draw.img = get_img_direc(point, data);
		draw.x_pos = get_tex_x(point, angle, draw.img);
		ver_line(data, x, &draw);
	}
}

// uint32_t color = 0;// ft_pixel(img->pixels[(5 & 63) * 64 + 5], img->pixels[5& 63 * 64 + 1], img->pixels[5&63 * 64 + 2], 255);
// int side = get_side(point);
// INT(side)
// get_dir(angle);
// printf("%f\n", angle);
// printf("%x\n", color);
// ver_line(data, x, drawStart, drawEnd, 0x1A5319FF);
// printf("%f-%f\n", point.x, point.y);
// if (get_side(point) == 0)
// 	wall_x = point.y ;//+ distance * direction(angle).x;
// else 
// 	wall_x = point.x ;//+ distance * direction(angle).y;

// wall_x -= floor(wall_x);

// int texX = (int)(wall_x * (double)(img->width));
// if ((direction(angle).x < 0 && get_side(point) == 0) 
// 	|| (direction(angle).y > 0 && get_side(point) == 1)) 
// 	texX = img->width - texX - 1;
// if (get_side(point) == 0 && )
// FINT(wall_x)
// INT(wall.x)
// Starting texture coordinate color = img->pixels[start & 63 * 64 + x1];
// printf("%x\n", color);
// color = ft_pixel(img->pixels[((int)start & 63) * 64  +5], img->pixels[(int)start&63 * 64  + 6],
// 		img->pixels[(int)start&63 * 64  + 7], 255);
// color = ft_pixel(img->pixels[texY* (int)img->height + x1], img->pixels[texY * (int)img->height + x1+1], 
// 		img->pixels[texY * (int)img->height + x1+ 2], 255);
