/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybord.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:54:08 by hibenouk          #+#    #+#             */
/*   Updated: 2024/07/16 14:40:31 by zkotbi           ###   ########.fr       */
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

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}
uint32_t reverse_bits(uint32_t n) {
    n = ((n >> 1) & 0x55555555) | ((n & 0x55555555) << 1);
    n = ((n >> 2) & 0x33333333) | ((n & 0x33333333) << 2);
    n = ((n >> 4) & 0x0F0F0F0F) | ((n & 0x0F0F0F0F) << 4);
    n = ((n >> 8) & 0x00FF00FF) | ((n & 0x00FF00FF) << 8);
    n = (n >> 16) | (n << 16);
    return n;
}
uint32_t reverse_bytes(uint32_t value) {
    return ((value & 0xFF000000) >> 24) |
           ((value & 0x00FF0000) >> 8)  |
           ((value & 0x0000FF00) << 8)  |
           ((value & 0x000000FF) << 24);
}

/*********zkotbi modification********/

void ver_line(t_data *data, int x, t_draw *draw)
{
	double step;
	double tex_pos;
	uint32_t *pix;
	uint32_t color;

	int line_height = (int)(HEIGHT / draw->distance);
	int draw_start = -line_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	int draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	pix = (uint32_t *)draw->img->pixels;
	step = 1.0 * draw->img->height / line_height;
	tex_pos = (draw_start - HEIGHT / 2.0 + line_height / 2.0) * step;
	while (draw_start <= draw_end)
	{
		tex_pos += step;
		if (tex_pos < 0)
			tex_pos = 0;
		if (tex_pos >= draw->img->height)
			tex_pos = draw->img->height - 1;
		color = pix[(uint32_t)tex_pos * draw->img->width + draw->x_pos];
		color = reverse_bytes(color);
		mlx_put_pixel(data->image, x, draw_start, color);
		draw_start++;
	}
}

void color_floor_ceiling(t_data *data, int fcolor, int ccolor)
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

int get_side(t_vec2f point)
{
	if (point.x == floor(point.x))
		return (0);
	return (1);
}
int get_tex_x(t_vec2f point, double angle, mlx_image_t *img)
{
	int tex_x;
	double wall_x;

	if (get_side(point) == 0)
		wall_x = point.y ;
	else 
		wall_x = point.x ;

	wall_x -= floor(wall_x);

	tex_x = (int)(wall_x * (double)(img->width));
	if ((direction(angle).x < 0 && get_side(point) == 0) 
		|| (direction(angle).y > 0 && get_side(point) == 1)) 
		tex_x = img->width - tex_x - 1;
	return (tex_x);
}

mlx_image_t *get_img_direc(t_vec2f point, t_data *data)
{
	if (get_side(point) == 0 && data->param->map_data->pos.x < point.x)
		return (data->texture->west);
	if (get_side(point) == 0 && data->param->map_data->pos.x > point.x)
		return (data->texture->east);
	if (get_side(point) == 1 && data->param->map_data->pos.y > point.y)
		return (data->texture->north);
	if (get_side(point) == 1 && data->param->map_data->pos.y < point.y)
		return (data->texture->south);
	return (NULL);
}

/*********zkotbi modification********/

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
