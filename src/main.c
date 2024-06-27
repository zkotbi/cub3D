/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:12:51 by zkotbi            #+#    #+#             */
/*   Updated: 2024/06/27 16:30:54 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
// #include <stdio.h>

// #define WIDTH 512
// #define HEIGHT 512

// static mlx_image_t* image;

// // -----------------------------------------------------------------------------

// int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
// {
//     return (r << 24 | g << 16 | b << 8 | a);
// }

// void ft_randomize(void* param)
// {
// 	(void)param;
// 	for (uint32_t i = 0; i < image->width; ++i)
// 	{
// 		for (uint32_t y = 0; y < image->height; ++y)
// 		{
// 			uint32_t color = ft_pixel(
// 				rand() % 0xFF, // R
// 				rand() % 0xFF, // G
// 				rand() % 0xFF, // B
// 				rand() % 0xFF  // A
// 			);
// 			mlx_put_pixel(image, i, y, color);
// 		}
// 	}
// }

// void ft_hook(void* param)
// {
// 	mlx_t* mlx = param;

// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// 	if (mlx_is_key_down(mlx, MLX_KEY_UP))
// 		image->instances[0].y -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
// 		image->instances[0].y += 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
// 		image->instances[0].x -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
// 		image->instances[0].x += 5;
// }

// // -----------------------------------------------------------------------------

// int32_t main(void)
// {
// 	mlx_t* mlx;

// 	// Gotta error check this stuff
// 	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
// 	{
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (!(image = mlx_new_image(mlx, 128, 128)))
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	
// 	mlx_loop_hook(mlx, ft_randomize, mlx);
// 	mlx_loop_hook(mlx, ft_hook, mlx);

// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }
void f()
{
	system("leaks cub3D");
}
int main(int argc, char **argv)
{
	atexit(f);
	t_param *param;

	if (argc < 2)
		return (fd_putstr("few argument\n", 2), 1);
	param = parser_and_error_check(argv[1]);
	int i = 0;
	printf("north texture: %s\n", param->north_texture);
	printf("-------------------------\n");
	printf("south texture: %s\n", param->south_texture);
	printf("-------------------------\n");
	printf("west texture: %s\n", param->west_texture);
	printf("-------------------------\n");
	printf("east texture: %s\n", param->east_texture);
	printf("-------------------------\n");
    printf("celling: %d, %d, %d\n", param->celling_color->red, param->celling_color->green, param->celling_color->blue);
	printf("-------------------------\n");
    printf("floor: %d, %d, %d\n", param->floor_color->red, param->floor_color->green, param->floor_color->blue);
	printf("-------------------------\n");
    printf("lenght: %d, height: %d\n", param->map_data->sizes->x, param->map_data->sizes->y);
	printf("-------------------------\n");
    printf("player_pos: %d, %d\n", param->map_data->pos->x, param->map_data->pos->y);
	printf("-----------MAP-----------\n");
	while (param->map_data->map[i] != NULL)
	{
		printf("|%s|\n", param->map_data->map[i]);
		i++;
	}
	printf("-----------MAP-----------\n");
	free_param(param);
	// t_lst *lst;
	// if (argc != 2)
	// 	return (printf("chkatkhawr\n"), 1);
	// lst = allocate_file_content(argv[1]);
	// while (lst != NULL)
	// {
	// 	printf("%s", lst->content);
	// 	lst = lst->next;
	// }
	return (0);
}
