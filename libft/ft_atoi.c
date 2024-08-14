/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:30:49 by zkotbi            #+#    #+#             */
/*   Updated: 2024/08/13 09:13:30 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	ft_atoi(const char *str)
{
	int	result;

	result = 0;
	if (str[0] == 0 || str[0] == '\n')
		exit_strerror("invalid color informaton3\n", 1);
	while (*str != 0 && *str != '\n')
	{
		if (*str < '0' || *str > '9')
			exit_strerror("invalid color informaton3\n", 1);
		result = result * 10 + (*str - 48);
		if (result > 255)
			exit_strerror("invalid color informaton3\n", 1);
		str++;
	}
	return (result);
}
