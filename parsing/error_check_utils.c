/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 08:37:33 by zkotbi            #+#    #+#             */
/*   Updated: 2024/06/24 09:19:09 by zkotbi           ###   ########.fr       */
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
	return (fd_putstr("missing extension .cub\n", 2), 0);
}

// int main(int argc, char **argv)
// {
// 	if (argc < 2)
// 		return (printf("few arguments\n"), 1);
// 	if (extension_check(argv[1]) == 0)
// 		return (printf("extension a bnadm\n"), 1);
// 	printf("nadi\n");
// 	return (0);
// }
