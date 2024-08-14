/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 21:21:45 by hibenouk          #+#    #+#             */
/*   Updated: 2024/08/06 10:58:40 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_vec2d	vec2d(int x, int y)
{
	return ((t_vec2d){.x = x, .y = y});
}

t_vec2f	vec2f(double x, double y)
{
	return ((t_vec2f){.x = x, .y = y});
}

t_vec2f	sub2f(t_vec2f v, t_vec2f u)
{
	return (vec2f(v.x - u.x, v.y - u.y));
}

t_vec2f	add2f(t_vec2f v, t_vec2f u)
{
	return (vec2f(v.x + u.x, v.y + u.y));
}

double	vec_distance(t_vec2f a, t_vec2f b)
{
	return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)));
}
