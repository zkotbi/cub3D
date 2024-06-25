/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 08:37:33 by zkotbi            #+#    #+#             */
/*   Updated: 2024/06/25 07:51:59 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
#include <sys/fcntl.h>

t_lst *allocate_file_content(char *argv)
{
	int fd;
	t_lst *content;
	t_lst *lst_tmp;
	char *line;

	fd = open(argv, O_RDONLY);
	line = get_next_line(fd);
	content = malloc(sizeof(t_lst));
	malloc_null_check(content);
	lst_tmp = content;
	lst_tmp->content = NULL;
	while (line != NULL)
	{
		lst_tmp->content = line;
		line = get_next_line(fd);
		if (line != NULL)
		{
			lst_tmp->next = malloc(sizeof(t_lst));
			malloc_null_check(lst_tmp);
		}
		else
			lst_tmp->next = NULL;
		lst_tmp = lst_tmp->next;
	}
	close (fd);
	return (content);
}

void tokens_init(t_token *tokens)
{
	tokens->map = NULL;
	tokens->floor_color = NULL;
	tokens->east_texture = NULL;
	tokens->west_texture = NULL;
	tokens->north_texture = NULL;
	tokens->south_texture = NULL;
	tokens->celling_color = NULL;
}
t_token *tokeniz_file_content(t_lst *file_content)
{
	t_lst *lst_tmp;
	t_token *tokens;

	tokens = malloc(sizeof(t_token));
	malloc_null_check(tokens);
	tokens_init(tokens);
	lst_tmp = file_content;
	while (lst_tmp != NULL && (tokens->celling_color == NULL
			|| tokens->floor_color == NULL || tokens->south_texture == NULL
			|| tokens->north_texture == NULL || tokens->west_texture == NULL
			|| tokens->east_texture == NULL))
	{
		// printf("%s\n", lst_tmp->content);
		if (lst_tmp->content[0] == 'C' && tokens->celling_color == NULL)
			tokens->celling_color = lst_tmp->content;
		else if (lst_tmp->content[0] == 'F' && tokens->floor_color == NULL)
			tokens->floor_color = lst_tmp->content;
		else if (lst_tmp->content[0] == 'N' && lst_tmp->content[1] == 'O' &&  tokens->north_texture == NULL)
			tokens->north_texture = lst_tmp->content;
		else if (lst_tmp->content[0] == 'S' && lst_tmp->content[1] == 'O' &&  tokens->south_texture == NULL)
			tokens->south_texture = lst_tmp->content;
		else if (lst_tmp->content[0] == 'E' && lst_tmp->content[1] == 'A' &&  tokens->east_texture == NULL)
			tokens->east_texture = lst_tmp->content;
		else if (lst_tmp->content[0] == 'W' && lst_tmp->content[1] == 'E' &&  tokens->west_texture == NULL)
			tokens->west_texture = lst_tmp->content;
		else if (lst_tmp->content[0] != '\n')
			return (exit_strerror("invalid or missing information\n", 1), NULL);
		lst_tmp = lst_tmp->next;
	}
	tokens->map = lst_tmp;
	if (tokens->celling_color == NULL || tokens->map == NULL
		|| tokens->floor_color == NULL || tokens->south_texture == NULL
		|| tokens->north_texture == NULL || tokens->west_texture == NULL
		|| tokens->east_texture == NULL)
		return (exit_strerror("invalid or missing information\n", 1), NULL);
	return (tokens);
}

// int main(int argc, char **argv)
// {
// 	t_lst *lst;
// 	if (argc != 2)
// 		return (printf("chkatkhawr\n"), 1);
// 	lst = allocate_file_content(argv[1]);
// 	while (lst != NULL)
// 	{
// 		printf("%s", lst->content);
// 		lst = lst->next;
// 	}
// 	return (0);
// }
// int verify_type(char *info, int *count)
// {
// 	int i;

// 	i = 0;
// 	while (info[i] != 0 && info[i] != ' ')
// 		i++;
// 	if ((i != 1 && i != 2) || info[i] == 0 || info[i + 1] == 0)
// 		return (fd_putstr("Error\nbad type identifier or bad information\n", 2), 0);
// 	if (info[0] == 'F' && info[1] == ' ' && count[4] == 0)
// 		count[4]++;
// 	else if (info[0] == 'C' && info[1] == ' ' && count[5] == 0)
// 		count[5]++;
// 	else if (info[0] == 'N' && info[1] == 'O' && count[0] == 0)
// 		count[0]++;
// 	else if (info[0] == 'S' && info[1] == 'O' && count[1] == 0)
// 		count[1]++;
// 	else if (info[0] == 'W' && info[1] == 'E' && count[2] == 0)
// 		count[2]++;
// 	else if (info[0] == 'E' && info[1] == 'A' && count[3] == 0)
// 		count[3]++;
// 	else 
// 		return (fd_putstr("Error\nbad type identifier or bad information\n", 2), 0);
// 	return (1);
// }

// // int verify_top_bottom(char *line, int *charc)
// // {
// // 	return (1);		
// // }

// // int verify_map_line(char *line, int *charc)
// // {
// // 	return (1);
// // }

// int verify_map(char *info, int *count, int fd)
// {
// 	// char *tmp;
// 	// int charc;
// 	// int i;

// 	// i = 0;
// 	// charc = 0;
// 	// tmp = NULL;
// 	// if (verify_top_bottom(info, &charc) == 0)
// 	// 	return (fd_putstr("Error\nmap not valid\n", 2), 0);
// 	// while (info != NULL)
// 	// {
// 	// 	if (verify_map_line(info, &charc) == 0)
// 	// 		return (fd_putstr("Error\nmap not valid\n", 2), free(tmp), free(info), 0);
// 	// 	free(tmp);
// 	// 	tmp = info;
// 	// 	info = get_next_line(fd);
// 	// 	while (info != NULL && info[0] == '\n')
// 	// 	{
// 	// 		free(info);
// 	// 		info = get_next_line(fd);
// 	// 	}
// 	// 	if (info != NULL)
// 	// 		return (fd_putstr("Error\nmap not valid\n", 2), free(tmp), free(info), 0);
// 	// }
// 	// if (verify_top_bottom(tmp, &charc) == 0 || charc != 1)
// 	// 	return (fd_putstr("Error\nmap not valid\n", 2), free(tmp), 0);
// 	printf("--%s--%d--%d--\n", info , *count, fd);
// 	exit(8);
// 	return (1);
// }

// int verify_line(char *info, int *count, int fd)
// {
// 	int i = 0;

// 	if (info[0] == '\n')
// 		return (1);
// 	while (i < 6 && count[i] == 1)
// 		i++;
// 	if (i != 6)
// 		return (verify_type(info, count));
// 	else 
// 		return (verify_map(info, count, fd));
// 	return (1);
// }
// int extension_check(char *argv)
// {
// 	int i;
// 	int k;
// 	char *extension = ".cub";

// 	i = 1;
// 	while (argv[i] != 0)
// 	{
// 		k = 0;
// 		while (argv[i + k] != 0 && argv[i + k] == extension[k])
// 			k++;
// 		if (k == 4 && argv[i + k] == 0)
// 			return (1);
// 		i++;
// 	}
// 	return (fd_putstr("Error\nmissing extension .cub\n", 2), 0);
// }
// int main(int argc, char **argv)
// {
// 	if (argc < 2)
// 		return (printf("few arguments\n"), 1);
// 	if (extension_check(argv[1]) == 0)
// 		return (printf("extension a bnadm\n"), 1);
// 	printf("nadi\n");
// 	return (0);
// }
