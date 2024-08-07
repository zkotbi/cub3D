/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:26:12 by zkotbi            #+#    #+#             */
/*   Updated: 2024/08/07 12:25:50 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t reverse_bytes(uint32_t value) {
    return ((value & 0xFF000000) >> 24) |
           ((value & 0x00FF0000) >> 8)  |
           ((value & 0x0000FF00) << 8)  |
           ((value & 0x000000FF) << 24);
}

/*********zkotbi modification********/

void ver_line(t_data *data, int x, t_draw *draw)
{
	double step;
	double tex_pos;
	uint32_t *pix;
	uint32_t color;

	int line_height = (int)(data->height / draw->distance);
	int draw_start = -line_height / 2 + data->height / 2;
	if (draw_start < 0)
		draw_start = 0;
	int draw_end = line_height / 2 + data->height / 2;
	if (draw_end >= data->height)
		draw_end = data->height - 1;
	pix = (uint32_t *)draw->img->pixels;
	step = 1.0 * draw->img->height / line_height;
	tex_pos = (draw_start - data->height / 2.0 + line_height / 2.0) * step;
	while (draw_start <= draw_end)
	{
		tex_pos += step;
		if (tex_pos < 0)
			tex_pos = 0;
		if (tex_pos >= draw->img->height)
			tex_pos = draw->img->height - 1;
		color = pix[(uint32_t)tex_pos * draw->img->width + draw->x_pos];
		color = reverse_bytes(color);
		mlx_put_pixel(data->image, x, draw_start, color);
		draw_start++;
	}
}



static int get_side(t_vec2f point)
{
	if (point.x == floor(point.x))
		return (0);
	return (1);
}

int get_tex_x(t_vec2f point, double angle, mlx_image_t *img)
{
	int tex_x;
	double wall_x;

	if (get_side(point) == 0)
		wall_x = point.y ;
	else 
		wall_x = point.x ;

	wall_x -= floor(wall_x);

	tex_x = (int)(wall_x * (double)(img->width));
	if ((direction(angle).x < 0 && get_side(point) == 0) 
		|| (direction(angle).y > 0 && get_side(point) == 1)) 
		tex_x = img->width - tex_x - 1;
	return (tex_x);
}

mlx_image_t *get_img_direc(t_vec2f point, t_data *data)
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

