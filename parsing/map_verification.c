/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verification.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:50:59 by zkotbi            #+#    #+#             */
/*   Updated: 2024/06/27 00:21:38 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
// char	**env_lst_to_arr(t_lst *lst)
// {
// 	char	**arr;
// 	int		i;

// 	i = 0;
// 	arr = malloc(sizeof(char *) * count_map_size(lst));
// 	malloc_null_check(arr);
// 	lst = env->front;
// 	while (lst)
// 	{
// 		if (lst->state == DISPLAY)
// 			arr[i++] = ft_strdup(lst->varible);
// 		lst = lst->next;
// 	}
// 	arr[i] = NULL;
// 	return (arr);

// }

int is_border(t_lst *lst, int index)
{
	if (lst->content[index] != ' ')
	{
		if (lst->prev == NULL || lst->prev->content[0] == '\n'
			|| lst->prev->size <= index 
			|| lst->prev->content[index] == ' ')
			return (1);
		if (lst->next == NULL || lst->next->content[0] == '\n'
			|| lst->next->size <= index 
			|| lst->next->content[index] == ' ')
			return (2);
		if (lst->content[index + 1] == ' ' || lst->content[index + 1] == '\n'
			|| lst->content[index + 1] == 0)
			return (3);
		if (index == 0 || lst->content[index - 1] == ' ' 
			|| lst->content[index - 1] == '\n' || lst->content[index - 1] == 0)
			return (4);
		if (lst->prev->size == index + 1 || lst->prev->content[index + 1] == ' ' 
			|| lst->prev->content[index - 1] == ' ')
			return (5);
		if (lst->next->size == index + 1 || lst->next->content[index + 1] == ' ' 
			|| lst->next->content[index - 1] == ' ')
			return (6);
	}
	return (0);
}
static void	checking_loop(t_lst *lst)
{
	t_lst *tmp;
	int i;

	tmp = lst;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->content[i] != 0 && tmp->content[i] != '\n')
		{
			if (is_border(tmp, i) != 0 && tmp->content[i] != '1')
				exit_strerror("invalid map border\n", 1);
			i++;
		}
		tmp = tmp->next;
	}
}

void is_map_contunied(t_lst *lst)
{
	t_lst *tmp;

	tmp = lst;
	while (tmp != NULL && tmp->content[0] == '\n')
		tmp = tmp->next;
	while (tmp != NULL && tmp->content[0] != '\n')
		tmp =  tmp->next;
	while (tmp != NULL)
	{
		if (tmp->content[0] != '\n')
			exit_strerror("map not continued\n", 1);
		tmp = tmp->next;
	}
}

static void count_and_check_char(t_lst *lst)
{
	t_lst *tmp;
	int i;
	int pos;

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
			if (tmp->content[i] != '0' && tmp->content[i] != '1' && tmp->content[i] != ' ')
				pos++;
			i++;
		}
		tmp->size = i;
		tmp = tmp->next;
	}
	if (pos != 1)
		exit_strerror("missing or duplicate start position\n", 1);
}

void verify_borders(t_lst *lst)
{
	t_lst *tmp;

	tmp = lst;
	while (tmp != NULL && tmp->content[0] == '\n')
		tmp = tmp->next;
	checking_loop(tmp);
}

void verify_map(t_param *param, t_lst *lst)
{
	count_and_check_char(lst);	
	is_map_contunied(lst);
	verify_borders(lst);
	parser_map(param, lst);
}
