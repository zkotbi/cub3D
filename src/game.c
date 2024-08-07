/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:45:05 by zkotbi            #+#    #+#             */
/*   Updated: 2024/08/07 12:22:36 by hibenouk         ###   ########.fr       */
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
	double			delta;
	double			angle;
	int				x;

	color_floor_ceiling(data);
	delta = FOV / (data->width - 1);
	angle = data->player_angle - FOV / 2;
	x = 0;
	while (x < data->width)
	{
		point = get_wall_postion(data->param->map_data, pos, angle);
		draw.distance = vec_distance(pos, point);
		draw.img = get_img_direc(point, data);
		draw.x_pos = get_tex_x(point, angle, draw.img);
		ver_line(data, x++, &draw);
		angle += delta;
	}
}
