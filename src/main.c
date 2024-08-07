/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:12:51 by zkotbi            #+#    #+#             */
/*   Updated: 2024/08/07 12:29:17 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "cub3D.h"


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

void windows_resize(int width, int height, void* param)
{
	t_data *data;

	data = param;
	if (!mlx_resize_image(data->image, width, height))
		return (error_exit(data));
	data->height = height;
	data->width = width;
	game(data);
}

void leaks() {system("leaks cub3D");}//WARNING

int main(int ac, char **argv)
{
	atexit(leaks);//WARNING
	t_data data;

	if (ac != 2)
	{
		printf("Invalid number of argument\n");
		printf("usage: cub3d map.cub\n");
		return (1);
	}
	data = init_data(argv[1]);
	print_map(data.param);
	mlx_key_hook(data.mlx, keybord, &data);
	mlx_resize_hook(data.mlx, windows_resize, &data);
	mlx_loop(data.mlx);
	clean_exit(&data);
	return (EXIT_SUCCESS);
}
