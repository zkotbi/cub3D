/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybord.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:54:08 by hibenouk          #+#    #+#             */
/*   Updated: 2024/07/01 16:58:03 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "cub3D.h"

t_vec2d mini_map_render(t_data *data, char map[][16]);

void put_point(t_data *data, t_vec2d vec);

t_vec2d ray_casting(t_data *data, t_vec2f start, t_vec2f end);
void keybord(mlx_key_data_t keydata, void *param)
{

	t_data *data = param;

	if (keydata.key == MLX_KEY_LEFT)
		data->pos.x += MOVE_SPEED;
	else if (keydata.key == MLX_KEY_RIGHT)
		data->pos.x -= MOVE_SPEED;
	t_vec2d pos = mini_map_render(data, data->map);
	// put_point(data, data->pos);
	// t_vec2d point = pos;
	// for (int i = 0;i<6;i++)
	// {
	// 	point = ray_casting(data, grid(point), grid(data->pos));
	// 	put_point(data, point);
	// }

}
