/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybord.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:54:08 by hibenouk          #+#    #+#             */
/*   Updated: 2024/07/08 09:33:19 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_point_grid(t_data *data, t_vec2f point, int color)
{
	t_vec2d	vec;

	vec = vec2d(point.x * CELLSIZE, point.y * CELLSIZE);
	put_pixels(data->image, vec, vec2d(5, 5), color);
}

void	keybord(mlx_key_data_t keydata, void *param)
{
	t_data	*data;
	t_vec2d	pos;
	t_vec2f	point;

	data = param;
	if (MLX_KEY_ESCAPE == keydata.key)
		mlx_close_window(data->mlx);
	if (keydata.key == MLX_KEY_LEFT)
		data->player_angle += (data->player_angle < 360);
	else if (keydata.key == MLX_KEY_RIGHT)
		data->player_angle -= (data->player_angle > 0);
	pos = mini_map_render(data, data->param->map_data);
	point = grid(pos);
	put_point_grid(data, point, 0x543310FF);
	point = get_wall_postion(data->param->map_data, point, data->player_angle);
	put_point_grid(data, point, 0x543310FF);
}
