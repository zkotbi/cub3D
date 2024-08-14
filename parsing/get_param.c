/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 08:11:19 by zkotbi            #+#    #+#             */
/*   Updated: 2024/08/14 08:16:27 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	verify_texture(t_param *param, char *path, enum e_param_type type)
{
	int	i;

	i = 2;
	while (path[i] == ' ')
		i++;
	if (path[i] == 0 || i == 2)
		exit_strerror("empty or invalid informaton\n", 1);
	if (type == NORTH)
		param->north_texture = ft_strtrim(&path[i], '\n');
	else if (type == SOUTH)
		param->south_texture = ft_strtrim(&path[i], '\n');
	else if (type == EAST)
		param->east_texture = ft_strtrim(&path[i], '\n');
	else if (type == WEST)
		param->west_texture = ft_strtrim(&path[i], '\n');
}

static void	set_rgb(char *info, t_color *rgb)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(info, ',');
	if (tmp == NULL)
		exit_strerror("invalid color informaton\n", 1);
	*rgb = (t_color){-1, -1, -1, -1};
	while (tmp[i] != NULL)
	{
		if (i > 2)
			exit_strerror("invalid color informaton\n", 1);
		if (i == 0)
			rgb->red = ft_atoi(tmp[i]);
		if (i == 1)
			rgb->green = ft_atoi(tmp[i]);
		if (i == 2)
			rgb->blue = ft_atoi(tmp[i]);
		i++;
	}
	free_tab(tmp);
}

static void	verify_color(t_param *param, char *path, enum e_param_type type)
{
	int	i;

	i = 1;
	while (path[i] == ' ')
		i++;
	if (path[i] == 0 || i == 1)
		exit_strerror("empty or invalid informaton\n", 1);
	if (type == CELLING)
	{
		set_rgb(&path[i], &(param->celling_color));
	}
	else if (type == FLOOR)
	{
		set_rgb(&path[i], &(param->floor_color));
	}
}

t_param	*get_and_verify_param(t_token *tokens)
{
	t_param	*param;

	param = malloc(sizeof(t_param));
	malloc_null_check(param);
	verify_texture(param, tokens->north_texture, NORTH);
	verify_texture(param, tokens->south_texture, SOUTH);
	verify_texture(param, tokens->west_texture, WEST);
	verify_texture(param, tokens->east_texture, EAST);
	verify_color(param, tokens->floor_color, FLOOR);
	verify_color(param, tokens->celling_color, CELLING);
	verify_map(param, tokens->map);
	return (param);
}
