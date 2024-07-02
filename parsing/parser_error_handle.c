/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error_handle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 08:20:36 by zkotbi            #+#    #+#             */
/*   Updated: 2024/07/02 17:30:46 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


int extension_check(char *argv)
{
	int i;
	int k;
	char *extension = ".cub";

	i = 1;
	while (argv[i] != 0)
	{
		k = 0;
		while (argv[i + k] != 0 && argv[i + k] == extension[k])
			k++;
		if (k == 4 && argv[i + k] == 0)
			return (1);
		i++;
	}
	return (fd_putstr("Error\nmissing extension .cub\n", 2), 0);
}

// void free_tokens(t_token *tokens, t_lst *content)
// {
// 	if (tokens == NULL || content == NULL)
// 		return ;
// }

t_param *parser_and_error_check(char *argv)
{
	t_lst *file_content;
	t_token *tokens;
	t_param *param;

	if (extension_check(argv) == 0)
		exit(1);
	file_content = allocate_file_content(argv);
	if (file_content->content == NULL)
		exit_strerror("empty file\n", 1);
	tokens = tokeniz_file_content(file_content);
	param = get_and_verify_param(tokens);
	free_tokens(tokens, file_content);
	// while(1){}
	return (param);
}

// void exit_strerror(char *str, int code)
// {
// 	if (str != NULL)
// 	{
// 		fd_putstr("Error\n", 2);
// 		fd_putstr(str, 2);
// 	}
// 	exit(code);
// }


// int information_check(char *argv)
// {
// 	int		 fd;
// 	char	*tmp;
// 	int		i;
// 	int		count[7];

// 	i = 0;
// 	fd = open(argv, O_RDONLY);
// 	while (i < 7)
// 		count[i++] = 0;
// 	tmp = get_next_line(fd);

// 	while (tmp != NULL)
// 	{
// 		if (verify_line(tmp, count, fd) == 0)
// 			return (0);
// 		free(tmp);
// 		tmp = get_next_line(fd);
// 	}
// 	i = 0;
// 	while (i < 7)
// 	{
// 		if (count[i] == 0)
// 			return (0);
// 	}
// 	return (1);
// }

