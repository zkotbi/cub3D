/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:06:55 by hibenouk          #+#    #+#             */
/*   Updated: 2024/08/17 11:38:15 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	mlx_error42(t_data *data)
{
	printf("Error: MLX42: %s\n", mlx_strerror(mlx_errno));
	free_param(data->param);
	mlx_terminate(data->mlx);
	exit(1);
}

static mlx_image_t	*new_image_to_window(t_data *data, t_vec2d wsize)
{
	mlx_image_t	*image;

	image = mlx_new_image(data->mlx, wsize.x, wsize.y);
	if (!image)
		return (mlx_error42(data), NULL);
	if (mlx_image_to_window(data->mlx, image, 0, 0) == -1)
	{
		mlx_delete_image(data->mlx, image);
		return (mlx_error42(data), NULL);
	}
	return (image);
}

t_data	init_data(char *path)
{
	t_data	data;

	data.param = parser_and_error_check(path);
	data.width = 1600;
	data.height = 1024;
	data.mlx = mlx_init(data.width, data.height, "cub3D", true);
	if (!data.mlx)
	{
		printf("Error: MLX42: %s\n", mlx_strerror(mlx_errno));
		free_param(data.param);
		exit(1);
	}
	data.image = new_image_to_window(&data, vec2d(data.width, data.height));
	get_texture(&data);
	data.player_angle = data.param->map_data->init_direc;
	return (data);
}
