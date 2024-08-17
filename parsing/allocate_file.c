/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 08:41:02 by zkotbi            #+#    #+#             */
/*   Updated: 2024/08/17 12:26:58 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	allocate_file_content_utils(t_lst *lst_tmp)
{
	lst_tmp->content = NULL;
	lst_tmp->prev = NULL;
}

t_lst	*allocate_file_content(char	*file_name)
{
	const int		fd = open(file_name, O_RDONLY);
	t_lst			*content;
	t_lst			*lst_tmp;
	char			*line;

	line = get_next_line(fd);
	content = malloc(sizeof(t_lst));
	malloc_null_check(content);
	lst_tmp = content;
	allocate_file_content_utils(lst_tmp);
	while (line != NULL)
	{
		lst_tmp->content = line;
		line = get_next_line(fd);
		if (line != NULL)
		{
			lst_tmp->next = malloc(sizeof(t_lst));
			malloc_null_check(lst_tmp);
			lst_tmp->next->prev = lst_tmp;
		}
		else
			lst_tmp->next = NULL;
		lst_tmp = lst_tmp->next;
	}
	return (close(fd), content);
}
