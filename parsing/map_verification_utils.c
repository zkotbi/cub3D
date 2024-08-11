/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verification_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:18:13 by zkotbi            #+#    #+#             */
/*   Updated: 2024/08/11 09:23:47 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	utils(t_lst *tmp, int i)
{
	return (tmp->content[i] != '0' && tmp->content[i] != '1'
		&& tmp->content[i] != ' ');
}

void	count_and_check_char(t_lst *lst)
{
	t_lst	*tmp;
	int		i;
	int		pos;

	tmp = lst;
	pos = 0;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->content[i] != 0 && tmp->content[i] != '\n')
		{
			if (tmp->content[i] != '0' && tmp->content[i] != '1'
				&& tmp->content[i] != 'N' && tmp->content[i] != 'E'
				&& tmp->content[i] != 'W' && tmp->content[i] != 'S'
				&& tmp->content[i] != ' ')
				exit_strerror("invalid map charcter\n", 1);
			if (utils(tmp, i))
				pos++;
			i++;
		}
		tmp->size = i;
		tmp = tmp->next;
	}
	if (pos != 1)
		exit_strerror("missing or duplicate start position\n", 1);
}
