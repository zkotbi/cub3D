/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:12:51 by zkotbi            #+#    #+#             */
/*   Updated: 2024/06/25 06:44:28 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	if (argc < 2)
		return (fd_putstr("few arguments\n", 2), 1);
	error_check(argv[1]);
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
