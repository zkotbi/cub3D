/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:45:05 by zkotbi            #+#    #+#             */
/*   Updated: 2024/08/12 14:26:42 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	color_floor_ceiling(t_data *data)
{
	const uint32_t	half = data->image->height / 2;
	uint32_t		i;
	uint32_t		j;

	i = 0;
	while (i < data->image->height)
	{
		j = 0;
		while (j < data->image->width)
		{
			if (i > half)
				mlx_put_pixel(data->image, j, i,
					*(uint32_t *)&data->param->floor_color);
			else
				mlx_put_pixel(data->image, j, i,
					*(uint32_t *)&data->param->celling_color);
			j++;
		}
		i++;
	}
}

void	game(t_data *data)
{
	const t_vec2f	pos = data->param->map_data->pos;
	t_vec2f			point;
	t_draw			draw;
	int				x;
	double			val[2];

	color_floor_ceiling(data);
	val[0] = FOV / (data->width - 1);
	val[1] = data->player_angle - FOV / 2;
	x = 0;
	while (x < data->width)
	{
		point = get_wall_postion(data->param->map_data, pos, val[1]);
		draw.distance = vec_distance(pos, point);
		draw.img = get_img_direc(point, data);
		draw.x_pos = get_tex_x(point, val[1], draw.img);
		ver__line(data, x++, &draw);
		val[1] += val[0];
	}
}
