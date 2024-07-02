/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybord.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:54:08 by hibenouk          #+#    #+#             */
/*   Updated: 2024/07/02 22:22:30 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "MLX42/MLX42.h"
#include "cub3D.h"


void put_point(t_data *data, t_vec2d vec);

t_vec2d ray_casting(t_data *data, t_vec2f start, t_vec2f end);


int check_wall(t_vec2f p1, const t_vec2f d, t_map *map_data)
{
	int x = floor(p1.x + eps * d.x);
	int y = floor(p1.y + eps * d.y);
	if (map_data->map[x][y] == '1')
		return (1);
	return (0);

}
void keybord(mlx_key_data_t keydata, void *param)
{

	t_data *data = param;
	if (MLX_KEY_ESCAPE == keydata.key)
		exit(0);
	if (keydata.key == MLX_KEY_LEFT)
		data->pos.x -= (data->pos.x < WIDTH) * MOVE_SPEED;
	else if (keydata.key == MLX_KEY_RIGHT)
		data->pos.x += (data->pos.x < WIDTH) * MOVE_SPEED;
	else if (keydata.key == MLX_KEY_UP)
		data->pos.y -= (data->pos.y < HEIGHT) * MOVE_SPEED;
	else if (keydata.key == MLX_KEY_DOWN)
		data->pos.y += (data->pos.y < HEIGHT) * MOVE_SPEED;
	t_vec2d pos = mini_map_render(data, data->param->map_data);
	put_point(data, data->pos);
	put_pixels(data->image, pos, vec2d(GRID_X / 3, GRID_Y / 3), 0x050C9CFF);
	const t_vec2f d = direction(pos, data->pos);
	t_vec2d point = pos;
	for (int i = 0;i<10;i++)
	{
		point = ray_casting(data, grid(point), d);		// data->pos = {64, 128};
		if (check_wall(grid(point), d, data->param->map_data))
		{
			printf("found well break\n");
			break;
		}
		put_point(data, point);
	}

}
