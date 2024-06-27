/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 21:43:25 by zkotbi            #+#    #+#             */
/*   Updated: 2024/06/27 16:23:47 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void find_max_size(t_lst *lst, int *size)
{
	t_lst *tmp;

	size[0] = 0;
	size[1] = 0;
	tmp = lst;
	while (tmp != NULL && tmp->content[0] != '\n')
	{
		if (tmp->size > size[0])
			size[0] = tmp->size;
		tmp = tmp->next;
		size[1]++;
	}
}

void copy_and_fill(char *str, char *to_copy, int max)
{
	int i;

	i = 0;
	while (to_copy[i] != 0 && to_copy[i] != '\n')
	{
		str[i] = to_copy[i];
		i++;
	}
	while (i < max)
	{
		str[i] = ' ';
		i++;
	}
	str[i] = 0;
}

void init_map_data(t_map *map)
{
	int i;
	int j;

	i = 0;
	map->pos = malloc(sizeof(t_vec2d));
	malloc_null_check(map->pos);
	map->sizes = malloc(sizeof(t_vec2d));
	malloc_null_check(map->sizes);
	while (map->map[i] != NULL)
	{
		j = 0;
		while (map->map[i][j] != 0)
		{
			if (map->map[i][j] != '0' && map->map[i][j] != '1'
				&& map->map[i][j] != ' ')
			{
				if (map->map[i][j] == 'N')
					map->init_direc = NORTH;
				else if (map->map[i][j] == 'W')
					map->init_direc = WEST;
				else if (map->map[i][j] == 'E')
					map->init_direc = EAST;
				else if (map->map[i][j] == 'S')
					map->init_direc = SOUTH;
				map->pos->x = j;
				map->pos->y = i;
			}
			j++;
		}
		i++;
	}
	map->sizes->x = j;
	map->sizes->y = i;
}

void parser_map(t_param *param, t_lst *lst)
{
	int size[2];
	t_lst *tmp;
	int i;

	i = 0;
	tmp = lst;
	while (tmp != NULL && tmp->content[0] == '\n')
		tmp = tmp->next;
	find_max_size(tmp, size);
	param->map_data = malloc(sizeof(t_map));
	malloc_null_check(param->map_data);
	param->map_data->map = malloc(sizeof(char *) * (size[1] + 1));
	malloc_null_check(param->map_data->map);
	while (i < size[1])
	{
		param->map_data->map[i] = malloc(sizeof(char ) * (size[0] + 1));
		malloc_null_check(param->map_data->map[i]);
		copy_and_fill(param->map_data->map[i], tmp->content, size[0]);
		tmp = tmp->next;
		i++;
	}
	param->map_data->map[i] = NULL;
	init_map_data(param->map_data);
}
