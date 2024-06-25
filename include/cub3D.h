/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 23:29:00 by zkotbi            #+#    #+#             */
/*   Updated: 2024/06/25 12:50:23 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
#define CUB3D_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

enum param_type {
	CELLING,
	FLOOR,
	NORTH,
	SOUTH,
	EAST,
	WEST,
};
typedef struct s_lst
{
	char *content;
	struct s_lst *next;
	long size; // ONLY FOR MAP
} t_lst ;

typedef struct s_token
{
	t_lst *map;
	char *north_texture;
	char *south_texture;
	char *west_texture;
	char *east_texture;
	char *celling_color;
	char *floor_color;
} t_token;

typedef struct s_color
{
	int red;
	int green;
	int blue;
} t_color;

typedef struct s_param 
{
	t_color *floor_color;
	t_color *celling_color;
	char *north_texture;
	char *south_texture;
	char *west_texture;
	char *east_texture;
	char **map;
} t_param;

#ifndef BUFFER_SIZE 
#define BUFFER_SIZE 10
#endif

/*-----error_handle-----*/
void	error_check(char *argv);
int		extension_check(char *argv);
void	exit_strerror(char *str, int code);
void	malloc_null_check(void *ptr);
int		verify_line(char *info, int	*count, int fd);
t_lst	*allocate_file_content(char *argv);
t_token	*tokeniz_file_content(t_lst *file_content);
t_param	*get_and_verify_param(t_token *tokens);
// int		verify_type(char *info, int *count);

/*-----LIBFT-----*/
void	fd_putstr(char *str, int fd);
char	*get_next_line(int fd);
char	*ft_memdel(char	**ptr);
char	*ft_strchr(const char	*s, int c);
char	*ft_strjoin(char	*s1, char *s2, int r);
char	*ft_strdup(const char *s1);
char	**ft_split(char *s, char c);
int		ft_atoi(const char *str);
char	*ft_strtrim(char *str, char c);
#endif
