/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 23:29:00 by zkotbi            #+#    #+#             */
/*   Updated: 2024/06/25 12:49:42 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
#define CUB3D_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MLX42/MLX42.h>

/*-----error_handle-----*/
void	error_check(char *argv);
int		extension_check(char *argv);

/*-----LIBFT-----*/
void	fd_putstr(char *str, int fd);
#endif
