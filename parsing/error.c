/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 05:31:08 by zkotbi            #+#    #+#             */
/*   Updated: 2024/06/25 05:32:56 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void exit_strerror(char *str, int code)
{
	if (str != NULL)
	{
		fd_putstr("Error\n", 2);
		fd_putstr(str, 2);
	}
	exit(code);
}

void malloc_null_check(void *ptr)
{
	if (ptr == NULL)
		exit_strerror("malloc failed\n", 1);
}
