/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:12:51 by zkotbi            #+#    #+#             */
/*   Updated: 2024/07/15 10:39:08 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "MLX42/MLX42.h"
#include "cub3D.h"

mlx_image_t *new_image_to_window(t_data *data, t_vec2d pos, t_vec2d size)
{
	mlx_image_t *image;
	if (!(image = mlx_new_image(data->mlx, size.x, size.y)))
	{
		mlx_close_window(data->mlx);
		fd_putstr(mlx_strerror(mlx_errno), 2);
		exit(1);
	}

	if (mlx_image_to_window(data->mlx, image, pos.x, pos.y) == -1)
	{
		mlx_close_window(data->mlx);
		fd_putstr(mlx_strerror(mlx_errno), 2);
		exit(1);
	}
	return (image);
}

// void load_png(t_text *texture, t_param *param)
// {
// 	texture->north = mlx_load_png(param->north_texture);
// 	if (texture->north == NULL)
// 	{
// 		destroy_texture(texture, 1);
// 		exit_strerror("mlx_load_png failed\n", 1);
// 	}
// 	texture->south = mlx_load_png(param->south_texture);
// 	if (texture->south == NULL)
// 	{
// 		destroy_texture(texture, 2);
// 		exit_strerror("mlx_load_png failed\n", 1);
// 	}
// 	texture->east = mlx_load_png(param->east_texture);
// 	if (texture->east == NULL)
// 	{
// 		destroy_texture(texture, 3);
// 		exit_strerror("mlx_load_png failed\n", 1);
// 	}
// 	texture->west = mlx_load_png(param->west_texture);
// 	if (texture->west == NULL)
// 	{
// 		destroy_texture(texture, 4);
// 		exit_strerror("mlx_load_png failed\n", 1);
// 	}
// }

// void get_texture(t_data *data)
// {
// 	t_text textures;
// 	
// 	load_png(&textures, data->param);
// 	data->texture = malloc(sizeof(textures));
// 	malloc_null_check(data->texture);
// 	load_img(data->texture, &textures);
// }

t_data init_screen(void)
{
	t_data data;
	// Gotta error check this stuff
	if (!(data.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		exit(1);
	}
	data.image = new_image_to_window(&data, vec2d(0, 0), vec2d(WIDTH, HEIGHT));
	data.min_map = new_image_to_window(&data, vec2d(0, 0), vec2d(CELLSIZE * 16, 12 * CELLSIZE));
	return (data);
}

void put_pixels(mlx_image_t *image, t_vec2d coord, t_vec2d size, int color)
{
	for (int i = coord.x; i < coord.x + size.x; i++)
	{
		for (int j = coord.y; j < coord.y + size.y; j++)
			mlx_put_pixel(image, i, j, color);
	}
}

t_vec2d cvec_min(t_vec2d v, t_vec2d u)
{
	const int x = min(v.x, u.x);
	const int y = min(v.y, u.y);
	return (vec2d(x, y));
}

void min_map_rng(t_data *const data)
{
	const t_map *const map_data = data->param->map_data;
	const t_vec2f player = map_data->pos;
	const t_vec2d distWx = vec2d(player.y, map_data->sizes.y - player.y - 1);
	const t_vec2d distWy = vec2d(player.x, map_data->sizes.x - player.x - 1);

	data->rng.h = cvec_min(distWx, vec2d(MIN_MAP_X, MIN_MAP_X));
	data->rng.v = cvec_min(distWy, vec2d(MIN_MAP_Y, MIN_MAP_Y));
}
void k42assert(int cond, const char *mesg)
{
	if (cond)
		return;
	printf("%s\n", mesg);
	exit(23);
}
void render_min_map(t_data *data, t_map *map_data)
{
	char **map;
	const t_vec2d size = vec2d(CELLSIZE - 1, CELLSIZE - 1);
	const t_vec2d sizes = map_data->sizes;
	map = map_data->map;

	min_map_rng(data);
	int startX = map_data->pos.x - data->rng.h.x, endX = map_data->pos.x + data->rng.h.y;
	int startY = map_data->pos.y - data->rng.v.x, endY = map_data->pos.y + data->rng.v.y;

	int rng_x = endX - startX;
	int rng_y = endY - startY;
	INT(rng_x)
	INT(rng_y)

	for (int i = 0; i < rng_y; i++)
	{
		int _s = startX;
		
		for (int j = 0; j < rng_x; j++)
		{
			k42assert(_s < sizes.x ,"size x");
			k42assert(_s >= 0 ,"X is neg");
			k42assert(startY < sizes.y ,"size y");
			k42assert(startY >= 0,"Y is neg");
			if (map[startY][_s] == '1')
			{
				put_pixels(data->min_map, vec2d(j * CELLSIZE, i * CELLSIZE), size, 0xFFFFFFFF);
			}
			else if (
				map[startY][_s] == 'W' || map[startY][_s] == 'E' || map[startY][_s] == 'N' || map[startY][_s] == 'S')
			{
				put_pixels(data->min_map, vec2d(j * CELLSIZE, i * CELLSIZE), size, 0xFF8F00ff);
			}
			else if (map[startY][_s] == '0')
				put_pixels(data->min_map, vec2d(j * CELLSIZE, i * CELLSIZE), size, 0xFF8F00ff);
			_s++;
		}
		startY++;
	}
}

void print_map(t_param *param)
{
	t_map *map_data = param->map_data;

	char **map = map_data->map;
	for (int i = 0; i < map_data->sizes.y; i++)
	{
		printf("|");
		for (int j = 0; j < map_data->sizes.x; j++)
			printf("%c", map[i][j]);
		printf("|\n");
	}
}


int main(int ac, char **argv)
{
	(void)ac;
	t_data data;
	t_param *param;

	param = parser_and_error_check("./maps/map2.cub");
	printf(
		"%d, %d, %d, %d\n",
		param->floor_color.red,
		param->floor_color.green,
		param->floor_color.blue,
		param->floor_color.alpha);
	print_map(param);

	data = init_screen();
	data.param = param;
	data.param->map_data->pos.x += 0.3f;
	data.param->map_data->pos.y += 0.3f;
	data.player_angle = param->map_data->init_direc;
	get_texture(&data);
	// mini_map_render(&data, data.param->map_data);
	mlx_key_hook(data.mlx, keybord, &data);

	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
