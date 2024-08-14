/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 08:52:36 by zkotbi            #+#    #+#             */
/*   Updated: 2024/08/12 14:07:03 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "cub3D.h"

static void	load_png(t_text *texture, t_param *param)
{
	texture->north = mlx_load_png(param->north_texture);
	if (texture->north == NULL)
	{
		exit_strerror("mlx_load_png failed 1\n", 1);
	}
	texture->south = mlx_load_png(param->south_texture);
	if (texture->south == NULL)
	{
		destroy_texture(texture, 0);
		exit_strerror("mlx_load_png failed 2\n", 1);
	}
	texture->east = mlx_load_png(param->east_texture);
	if (texture->east == NULL)
	{
		destroy_texture(texture, 1);
		exit_strerror("mlx_load_png failed 3\n", 1);
	}
	texture->west = mlx_load_png(param->west_texture);
	if (texture->west == NULL)
	{
		destroy_texture(texture, 2);
		exit_strerror("mlx_load_png failed 4\n", 1);
	}
}

static void	load_png_text(t_data *data, t_text *text)
{
	data->texture->west = mlx_texture_to_image(data->mlx, text->west);
	if (data->texture->west == NULL)
	{
		destroy_img(data->texture, data->mlx, 3, text);
		mlx_terminate(data->mlx);
		exit_strerror("mlx_texture_to_image failed\n", 1);
	}
}

static void	load_img(t_data *data, t_text *text)
{
	data->texture->north = mlx_texture_to_image(data->mlx, text->north);
	if (data->texture->north == NULL)
	{
		mlx_terminate(data->mlx);
		exit_strerror("mlx_texture_to_image failed\n", 1);
	}
	data->texture->south = mlx_texture_to_image(data->mlx, text->south);
	if (data->texture->south == NULL)
	{
		destroy_img(data->texture, data->mlx, 1, text);
		mlx_terminate(data->mlx);
		exit_strerror("mlx_texture_to_image failed\n", 1);
	}
	data->texture->east = mlx_texture_to_image(data->mlx, text->east);
	if (data->texture->east == NULL)
	{
		destroy_img(data->texture, data->mlx, 2, text);
		mlx_terminate(data->mlx);
		exit_strerror("mlx_texture_to_image failed\n", 1);
	}
	load_png_text(data, text);
}

void	get_texture(t_data *data)
{
	t_text	*textures;

	textures = malloc(sizeof(t_text));
	malloc_null_check(textures);
	load_png(textures, data->param);
	data->texture = malloc(sizeof(t_img));
	malloc_null_check(data->texture);
	load_img(data, textures);
	destroy_texture(textures, 5);
	free(textures);
}
