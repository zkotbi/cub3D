/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 23:07:33 by zkotbi            #+#    #+#             */
/*   Updated: 2024/07/16 10:06:07 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "cub3D.h"

void free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void free_lst(t_lst *lst)
{
	t_lst *tmp;

	tmp = lst;
	while (tmp->next != NULL)
	{
		free(tmp->content);
		tmp = tmp->next;
		free(tmp->prev);
		tmp->prev = NULL;
	}
	free(tmp->content);
	free(tmp);
}
void free_tokens(t_token *tokens, t_lst *content)
{
	free_lst(content);
	free(tokens);
}

void free_map(t_map *map)
{
	free_tab(map->map);
	free(map);
}

void free_param(t_param *param)
{
	free(param->east_texture);
	free(param->west_texture);
	free(param->north_texture);
	free(param->south_texture);
	free_map(param->map_data);
	free(param);
}

void destroy_texture(t_text *texture, int n)
{
	if (n >= 0)
		mlx_delete_texture(texture->north);
	if (n >= 1)
		mlx_delete_texture(texture->south);
	if (n >= 2)
		mlx_delete_texture(texture->east);
	if (n >= 3)
		mlx_delete_texture(texture->west);
}

void destroy_img(t_img *img, mlx_t *mlx, int n, t_text *text)
{
	if (n >= 1)
		mlx_delete_image(mlx, img->north);
	if (n >= 2)
		mlx_delete_image(mlx, img->south);
	if (n >= 3)
		mlx_delete_image(mlx, img->east);
	if (n >= 4)
		mlx_delete_image(mlx, img->west);
	if (text != NULL)
		destroy_texture(text, 4);
}


