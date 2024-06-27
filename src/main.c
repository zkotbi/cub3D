/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:12:51 by zkotbi            #+#    #+#             */
/*   Updated: 2024/06/26 21:45:39 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "MLX42/MLX42.h"
#include "cub3D.h"

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void ft_hook(void *param)
{
	t_data *data;

	data = param;
	mlx_t *mlx = data->mlx;
	mlx_image_t *image = data->image;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);

}

// -----------------------------------------------------------------------------
t_data init_screen(void)
{
	t_data data;
	// Gotta error check this stuff
	if (!(data.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		exit(1);
	}
	if (!(data.image = mlx_new_image(data.mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(data.mlx);
		fd_putstr(mlx_strerror(mlx_errno), 2);
		exit(1);
	}

	if (mlx_image_to_window(data.mlx, data.image, 0, 0) == -1)
	{
		mlx_close_window(data.mlx);
		fd_putstr(mlx_strerror(mlx_errno), 2);
		exit(1);
	}
	return (data);
}

void put_pixels(mlx_image_t *image, t_vec2 coord, t_vec2 size, int color) 
{

	for (int i = coord.x; i < coord.x + size.x; i++) 
	{
		for (int j = coord.y; j < coord.y + size.y; j++) 
			mlx_put_pixel(image, i, j, color);
	}
}
void mini_map_rander(t_data *data, int n, int m, char map[9][7])
{

	int grid_size_x = WIDTH / n;
	int grid_size_y = HEIGHT / m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (map[i][j] == '1')
				put_pixels(data->image, vec2d(i * grid_size_x, j * grid_size_y), vec2d(grid_size_x, grid_size_y), 0xFFFFFFFF);
			else if (map[i][j] == 'W')
				put_pixels(data->image, vec2d(i * grid_size_x, j * grid_size_y), vec2d(grid_size_x, grid_size_y), 0x37B7C3);
			else 
				put_pixels(data->image, vec2d(i * grid_size_x, j * grid_size_y), vec2d(grid_size_x, grid_size_y), 0x623f239);
		}
	}
}
int main(void)
{
	t_data data;
	int n = 9, m = 7;


	char map[9][7] = {
		{'1', '1', '1', '1', '1', '1', '1'},
		{'1', '1', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '1', '0', '1'},
		{'1', '0', '0', '0', '1', '1', '1'},
		{'1', '0', 'W', '0', '1', '1', '1'},
		{'1', '0', '0', '0', '1', '1', '1'},
		{'1', '0', '0', '0', '1', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '1'},
		{'1', '1', '1', '1', '1', '1', '1'},
	};
	data = init_screen();
	mini_map_rander(&data, n, m, map);


	// mlx_key_hook(data.mlx, ft_hook, data.mlx);
	mlx_loop_hook(data.mlx, ft_hook, &data);

	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
