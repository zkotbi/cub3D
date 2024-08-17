/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error_handle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 08:20:36 by zkotbi            #+#    #+#             */
/*   Updated: 2024/08/17 11:42:21 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	extension_check(char *file_name)
{
	int			i;
	int			k;
	const char	*extension = ".cub";

	i = 0;
	while (file_name[i] != 0)
	{
		k = 0;
		while (i != 0 && file_name[i -1] != '/'
			&& file_name[i + k] != 0 && file_name[i + k] == extension[k])
			k++;
		if (k == 4 && file_name[i + k] == 0)
			return (1);
		i++;
	}
	return (fd_putstr("Error\nmissing extension .cub\n", 2), 0);
}

t_param	*parser_and_error_check(char *file_name)
{
	t_lst	*file_content;
	t_token	*tokens;
	t_param	*param;

	if (extension_check(file_name) == 0)
		exit(1);
	file_content = allocate_file_content(file_name);
	if (file_content->content == NULL)
		exit_strerror("empty file\n", 1);
	tokens = tokeniz_file_content(file_content);
	param = get_and_verify_param(tokens);
	free_tokens(tokens, file_content);
	param->map_data->pos.x += 0.5f;
	param->map_data->pos.y += 0.5f;
	return (param);
}
