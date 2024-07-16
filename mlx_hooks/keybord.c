/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybord.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:54:08 by hibenouk          #+#    #+#             */
/*   Updated: 2024/07/16 16:12:36 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "cub3D.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

void	put_point_grid(t_data *data, t_vec2f point, int color)
{
	t_vec2d	vec;

	vec = vec2d(point.x * CELLSIZE, point.y * CELLSIZE);
	put_pixels(data->image, vec, vec2d(5, 5), color);
}

void	bresenham(t_data *data, t_vec2d p1, t_vec2d p2)
{
	const t_vec2d	d = {.x = p2.x - p1.x, .y = p2.y - p1.y};
	const int		step = abs((int)max(d.x, d.y));
	const int		x_incr = (int)d.x / step;
	const int		y_incr = (int)d.y / step;
}

t_vec2d	pixels(t_vec2f v)
{
	return (vec2d(v.x * CELLSIZE, v.y * CELLSIZE));
}

void	DDALine(t_data *data, t_vec2d v, t_vec2d u)
{
	const t_vec2d	d = {.x = u.x - v.x, .y = u.y - v.y};
	int				step;
	float			x_incr;
	float			y_incr;
	float			x;
	float			y;

	if (abs(d.x) > abs(d.y))
		step = abs(d.x);
	else
		step = abs(d.y);
	x_incr = 0;
	y_incr = 0;
	if (step)
	{
		x_incr = (float)d.x / step;
		y_incr = (float)d.y / step;
	}
	x = v.x;
	y = v.y;
	for (int i = 0; i < step; i++)
	{
		mlx_put_pixel(data->min_map, round(x), round(y), 0xE4003AFF);
		x += x_incr;
		y += y_incr;
	}
}




t_vec2f rotate(double angle)
{
	return (direction(angle));
}

int check_collisions(t_data *data, double mov_ang)
{
	int r;
	int l;
	t_vec2f point;
	double distance;

	r = mov_ang + COLLISIONS_ANGLE;
	l = mov_ang - COLLISIONS_ANGLE;
	point = data->param->map_data->pos;
	while (l <= r)
	{
		point = get_wall_postion(data->param->map_data, point, l);
		distance = vec_distance(data->param->map_data->pos, point);
		if (distance <= MIN_DISTANCE)
			return (1);
		l++;
	}
	return (0);

}
void	move_player(t_data *data, enum e_move_dir dir)
{
	t_vec2f	d;
	t_vec2f *const pos = &data->param->map_data->pos;
	double move_angle;

	move_angle = data->player_angle;
	if (dir == BACK)
		move_angle += 180;
	else if (dir == LEFT)
		move_angle += 90.0f;
	else if (dir == RIGHT)
		move_angle -= 90.0f;
	if (check_collisions(data, move_angle))
		return ;
	d = direction(move_angle);
	*pos = add2f(*pos, scale(d, MOVE_SEEP));
}





void keybord(mlx_key_data_t keydata, void *param)
{
	t_data *data;

	data = param;
	if (MLX_KEY_ESCAPE == keydata.key)
		mlx_close_window(data->mlx);
	if (keydata.key == MLX_KEY_RIGHT)
		data->player_angle = (data->player_angle < 360) * (data->player_angle
				+ ROTATE_SEEP);
	else if (keydata.key == MLX_KEY_LEFT)
		data->player_angle = (data->player_angle >= 0) * (data->player_angle
				- ROTATE_SEEP) + (data->player_angle < 0) * 360;
	else if (keydata.key == MLX_KEY_W)
		move_player(data, FRONT);
	else if (keydata.key == MLX_KEY_S)
		move_player(data, BACK);
	else if (keydata.key == MLX_KEY_D)
		move_player(data, LEFT);
	else if (keydata.key == MLX_KEY_A)
		move_player(data, RIGHT);

	game(data, WIDTH);

}

