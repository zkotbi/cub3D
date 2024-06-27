/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 21:43:25 by zkotbi            #+#    #+#             */
/*   Updated: 2024/06/27 00:57:44 by zkotbi           ###   ########.fr       */
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
	param->map = malloc(sizeof(char *) * (size[1] + 1));
	malloc_null_check(param);
	while (i < size[1])
	{
		param->map[i] = malloc(sizeof(char ) * (size[0] + 1));
		malloc_null_check(param->map[i]);
		copy_and_fill(param->map[i], tmp->content, size[0]);
		tmp = tmp->next;
		i++;
	}
	param->map[i] = NULL;
}
