/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 08:37:33 by zkotbi            #+#    #+#             */
/*   Updated: 2024/08/17 11:52:21 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
#include <sys/fcntl.h>

static void	tokens_init(t_token *tokens)
{
	tokens->map = NULL;
	tokens->floor_color = NULL;
	tokens->east_texture = NULL;
	tokens->west_texture = NULL;
	tokens->north_texture = NULL;
	tokens->south_texture = NULL;
	tokens->celling_color = NULL;
}

static int	is_token_null(t_token	*tokens)
{
	int	res;

	res = 0;
	if (tokens->celling_color == NULL
		|| tokens->floor_color == NULL || tokens->south_texture == NULL
		|| tokens->north_texture == NULL || tokens->west_texture == NULL
		|| tokens->east_texture == NULL)
		return (1);
	return (res);
}

static void	tokeniz_file_content_utils(t_lst *lst_tmp, t_token *tokens)
{
	if (lst_tmp->content[0] == 'C' && tokens->celling_color == NULL)
		tokens->celling_color = lst_tmp->content;
	else if (lst_tmp->content[0] == 'F' && tokens->floor_color == NULL)
		tokens->floor_color = lst_tmp->content;
	else if (lst_tmp->content[0] == 'N' && lst_tmp->content[1] == 'O'
		&& tokens->north_texture == NULL)
		tokens->north_texture = lst_tmp->content;
	else if (lst_tmp->content[0] == 'S' && lst_tmp->content[1] == 'O'
		&& tokens->south_texture == NULL)
		tokens->south_texture = lst_tmp->content;
	else if (lst_tmp->content[0] == 'E' && lst_tmp->content[1] == 'A'
		&& tokens->east_texture == NULL)
		tokens->east_texture = lst_tmp->content;
	else if (lst_tmp->content[0] == 'W' && lst_tmp->content[1] == 'E'
		&& tokens->west_texture == NULL)
		tokens->west_texture = lst_tmp->content;
	else if (lst_tmp->content[0] != '\n')
		exit_strerror("invalid or missing information\n", 1);
}

t_token	*tokeniz_file_content(t_lst *file_content)
{
	t_lst	*lst_it;
	t_token	*tokens;

	tokens = malloc(sizeof(t_token));
	malloc_null_check(tokens);
	tokens_init(tokens);
	lst_it = file_content;
	while (lst_it != NULL && is_token_null(tokens))
	{
		tokeniz_file_content_utils(lst_it, tokens);
		lst_it = lst_it->next;
	}
	tokens->map = lst_it;
	if (tokens->map == NULL || is_token_null(tokens))
		return (exit_strerror("invalid or missing information\n", 1), NULL);
	return (tokens);
}
