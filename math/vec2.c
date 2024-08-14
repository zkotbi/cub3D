/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:58:06 by hibenouk          #+#    #+#             */
/*   Updated: 2024/08/09 00:20:26 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
 * dao distance from a to origin
 * dbo distance from b to origin
 */
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

t_vec2f	direction(double angle)
{
	double	rad;

	rad = angle * (PI / 180);
	return (vec2f(cos(rad), sin(rad)));
}

double	sign(double n)
{
	return ((n >= 0) - (n < 0));
}

t_vec2f	scale(t_vec2f v, double scalar)
{
	return (vec2f(v.x * scalar, v.y * scalar));
}
