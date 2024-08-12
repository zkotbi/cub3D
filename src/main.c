/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:12:51 by zkotbi            #+#    #+#             */
/*   Updated: 2024/08/12 14:30:33 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	windows_resize(int width, int height, void *param)
{
	t_data	*data;

	data = param;
	if (!mlx_resize_image(data->image, width, height))
		return (error_exit(data));
	data->height = height;
	data->width = width;
	game(data);
}

// void leaks() {system("leaks cub3D");}//WARNING

int	main(int ac, char **argv)
{
	t_data	data;

	if (ac != 2)
	{
		printf("Invalid number of argument\n");
		printf("usage: cub3d map.cub\n");
		return (1);
	}
	data = init_data(argv[1]);
	mlx_key_hook(data.mlx, keybord, &data);
	mlx_resize_hook(data.mlx, windows_resize, &data);
	mlx_loop(data.mlx);
	clean_exit(&data);
	return (EXIT_SUCCESS);
}
