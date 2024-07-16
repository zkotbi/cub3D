/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:03:21 by hibenouk          #+#    #+#             */
/*   Updated: 2024/07/13 16:01:34 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static double	snap(double x, double dx)
{
	if (dx > 0)
		return (ceil(x + sign(dx) * eps));
	else if (dx < 0)
		return (floor(x + sign(dx) * eps));
	return (x);
}

static t_vec2f	get_point(t_vec2f position, t_vec2f direction)
{
	t_vec2f	wvec;
	t_vec2f	uvec;
	t_vec2f	equ;
	t_vec2f	point;

	equ.x = direction.y / direction.x;
	equ.y = position.y - position.x * equ.x;
	uvec.x = snap(position.x, direction.x);
	uvec.y = uvec.x * equ.x + equ.y;
	if (equ.x != 0)
	{
		wvec.y = snap(position.y, direction.y);
		wvec.x = (wvec.y - equ.y) / equ.x;
	}
	else
		return (uvec);
	point = min_distance(uvec, wvec, position);
	return (point);
}

static t_vec2f	ray_casting(t_vec2f position, t_vec2f direction)
{
	t_vec2f	vec;

	if (direction.x != 0)
		return (get_point(position, direction));
	else
	{
		vec.y = snap(position.y, direction.y);
		vec.x = position.x;
		return (vec);
	}
	return (vec2f(0, 0));
}

// this may break

static int	hitting_wall(t_vec2f p1, const t_vec2f d, t_map *map_data)
{
	const int	x = floor(p1.x + eps * sign(d.x));
	const int	y = floor(p1.y + eps * sign(d.y));

	if (map_data->map[y][x] == '1')
		return (1);
	return (0);
}

t_vec2f	get_wall_postion(t_map *map_data, t_vec2f player_position, double angle)
{
	const t_vec2f	d = direction(angle);

	while (!hitting_wall(player_position, d, map_data))
		player_position = ray_casting(player_position, d);
	return (player_position);
}
