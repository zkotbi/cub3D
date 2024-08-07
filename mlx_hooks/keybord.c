/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybord.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:54:08 by hibenouk          #+#    #+#             */
/*   Updated: 2024/08/07 15:02:02 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_collisions(t_data *data, double mov_ang)
{
	double	l;
	double	r;
	t_vec2f	point;
	double	distance;

	l = mov_ang - COLLISIONS_ANGLE;
	r = mov_ang + COLLISIONS_ANGLE;
	while (l <= r)
	{
		point = get_wall_postion(data->param->map_data,
				data->param->map_data->pos, l);
		distance = vec_distance(data->param->map_data->pos, point);
		if (distance <= MIN_DISTANCE)
			return (1);
		l += 5.0f;
	}
	return (0);
}

static void	move_player(t_data *data, enum e_move_dir dir)
{
	t_vec2f			d;
	t_vec2f *const	pos = &data->param->map_data->pos;
	double			move_angle;

	move_angle = data->player_angle;
	if (dir == BACK)
		move_angle += 180;
	else if (dir == LEFT)
		move_angle += 90.0f;
	else if (dir == RIGHT)
		move_angle -= 90.0f;
	if (check_collisions(data, move_angle))
		return ;
	d = direction(move_angle);
	*pos = add2f(*pos, scale(d, MOVE_SEEP));
}

void	clean_exit(t_data *data)
{
	mlx_delete_image(data->mlx, data->image);
	mlx_terminate(data->mlx);
	free_param(data->param);
	free(data->texture);
	exit(0);
}

void	error_exit(t_data *data)
{
	printf("Error: MLX42: %s\n", mlx_strerror(mlx_errno));
	mlx_delete_image(data->mlx, data->image);
	mlx_terminate(data->mlx);
	free_param(data->param);
	free(data->texture);
	exit(1);
}

void	keybord(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (MLX_KEY_ESCAPE == keydata.key)
		clean_exit(data);
	if (keydata.key == MLX_KEY_RIGHT)
		data->player_angle = (data->player_angle < 360) * (data->player_angle
				+ ROTATE_SEEP);
	else if (keydata.key == MLX_KEY_LEFT)
		data->player_angle = (data->player_angle >= 0) * (data->player_angle
				- ROTATE_SEEP) + (data->player_angle < 0) * 360;
	else if (keydata.key == MLX_KEY_W)
		move_player(data, FRONT);
	else if (keydata.key == MLX_KEY_S)
		move_player(data, BACK);
	else if (keydata.key == MLX_KEY_D)
		move_player(data, LEFT);
	else if (keydata.key == MLX_KEY_A)
		move_player(data, RIGHT);
	game(data);
}
