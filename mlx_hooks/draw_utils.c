/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 23:40:31 by zkotbi            #+#    #+#             */
/*   Updated: 2024/08/09 01:39:27 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_draw(t_draw *draw, t_data *data)
{
	draw->line_height = (int)(data->height / draw->distance);
	draw->draw_start = -draw->line_height / 2 + data->height / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = draw->line_height / 2 + data->height / 2;
	if (draw->draw_end >= data->height)
		draw->draw_end = data->height - 1;
	draw->step = 1.0 * draw->img->height / draw->line_height;
}

void	ver__line(t_data	*data, int x, t_draw	*draw)
{
	double		tex_pos;
	uint32_t	*pix;
	uint32_t	color;

	pix = (uint32_t *)draw->img->pixels;
	init_draw(draw, data);
	tex_pos = (draw->draw_start - data->height / 2.0
			+ draw->line_height / 2.0) * draw->step;
	while (draw->draw_start <= draw->draw_end)
	{
		tex_pos += draw->step;
		if (tex_pos < 0)
			tex_pos = 0;
		if (tex_pos >= draw->img->height)
			tex_pos = draw->img->height - 1;
		color = pix[(uint32_t)tex_pos * draw->img->width + draw->x_pos];
		color = reverse_bytes(color);
		mlx_put_pixel(data->image, x, draw->draw_start, color);
		draw->draw_start++;
	}
}
