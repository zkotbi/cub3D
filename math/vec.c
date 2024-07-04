/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 21:21:45 by hibenouk          #+#    #+#             */
/*   Updated: 2024/07/03 16:00:22 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>

t_vec2d	vec2d(int x, int y)
{
	return ((t_vec2d){.x = x, .y = y});
}

t_vec2f	vec2f(double x, double y)
{
	return ((t_vec2f){.x = x, .y = y});
}

t_vec2d	sub2d(t_vec2d v, t_vec2d u)
{
	return (vec2d(v.x - u.x, v.y - u.y));
}

t_vec2f	sub2f(t_vec2f v, t_vec2f u)
{
	return (vec2f(v.x - u.x, v.y - u.y));
}

t_vec2f	add2f(t_vec2f v, t_vec2f u)
{
	return (vec2f(v.x + u.x, v.y + u.y));
}

t_vec2d	add2d(t_vec2d v, t_vec2d u)
{
	return (vec2d(v.x + u.x, v.y + u.y));
}

t_vec2f	line_eqution(t_vec2f v, t_vec2f u)
{
	t_vec2f	uv;
	double	m;
	double	c;

	uv = sub2f(v, u);
	m = uv.y / uv.x;
	c = v.y - m * v.x;
	return (vec2f(m, c));
}
double	vec_distance(t_vec2f a, t_vec2f b)
{
	return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)));
}

t_vec2f	min_distance(t_vec2f a, t_vec2f b, t_vec2f origin)
{
	double	dao;
	double	dbo;

	dao = vec_distance(origin, a);
	dbo = vec_distance(origin, b);
	if (dao < dbo)
		return (a);
	return (b);
}

t_vec2f	grid(t_vec2d vec)
{
	return (vec2f(vec.x / CELLSIZE, vec.y / CELLSIZE));
}

t_vec2d	pixel(t_vec2d vec)
{
	return (vec2d(vec.x * CELLSIZE, vec.y * CELLSIZE));
}
t_vec2f	direction(double angle)
{
	double	rad;

	rad = angle * (PI / 180);
	return (vec2f(cos(rad), sin(rad)));
}

t_vec2f	vec2dtf(t_vec2d v)
{
	return (vec2f(v.x, v.y));
}
