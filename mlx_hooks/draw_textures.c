/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:26:12 by zkotbi            #+#    #+#             */
/*   Updated: 2024/08/13 10:24:09 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

uint32_t	reverse_bytes(uint32_t value)
{
	return (((value & 0xFF000000) >> 24)
		| ((value & 0x00FF0000) >> 8)
		| ((value & 0x0000FF00) << 8)
		| ((value & 0x000000FF) << 24));
}

static int	get_side(t_vec2f	point)
{
	if (point.x == floor(point.x))
		return (0);
	return (1);
}

int	get_tex_x(t_vec2f	point, double angle, mlx_image_t *img)
{
	int		tex_x;
	double	wall_x;

	if (get_side(point) == 0)
		wall_x = point.y ;
	else
		wall_x = point.x ;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)(img->width));
	if ((get_side(point) == 0 && direction(angle).x < 0)
		|| (direction(angle).y > 0 && get_side(point) == 1))
		tex_x = img->width - tex_x - 1;
	return (tex_x);
}

mlx_image_t	*get_img_direc(t_vec2f point, t_data *data)
{
	if (get_side(point) == 0 && data->param->map_data->pos.x < point.x)
		return (data->texture->west);
	if (get_side(point) == 0 && data->param->map_data->pos.x > point.x)
		return (data->texture->east);
	if (get_side(point) == 1 && data->param->map_data->pos.y > point.y)
		return (data->texture->north);
	if (get_side(point) == 1 && data->param->map_data->pos.y < point.y)
		return (data->texture->south);
	return (NULL);
}
