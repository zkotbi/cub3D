/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybord.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:54:08 by hibenouk          #+#    #+#             */
/*   Updated: 2024/07/02 16:27:51 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "cub3D.h"


void put_point(t_data *data, t_vec2d vec);

t_vec2d ray_casting(t_data *data, t_vec2f start, t_vec2f end);
void keybord(mlx_key_data_t keydata, void *param)
{

	t_data *data = param;
	if (MLX_KEY_ESCAPE == keydata.key)
		exit(0);
	if (keydata.key == MLX_KEY_LEFT)
		data->pos.x -= MOVE_SPEED;
	else if (keydata.key == MLX_KEY_RIGHT)
		data->pos.x += MOVE_SPEED;
	else if (keydata.key == MLX_KEY_UP)
		data->pos.y -= MOVE_SPEED;
	else if (keydata.key == MLX_KEY_DOWN)
		data->pos.y += MOVE_SPEED;
	t_vec2d pos = mini_map_render(data, data->param->map_data);
	put_point(data, data->pos);
	put_pixels(data->image, pos, vec2d(GRID_X / 3, GRID_Y / 3), 0x050C9CFF);
	t_vec2d point = pos;
	for (int i = 0;i<3;i++)
	{
		point = ray_casting(data, grid(point), grid(data->pos));
		put_point(data, point);
	}

}
