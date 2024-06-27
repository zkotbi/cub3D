/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 23:29:00 by zkotbi            #+#    #+#             */
/*   Updated: 2024/06/27 15:59:03 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <MLX42/MLX42.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

enum param_type {
  CELLING,
  FLOOR,
  NORTH,
  SOUTH,
  EAST,
  WEST,
};
typedef struct s_lst {
  char *content;
  struct s_lst *next;
  struct s_lst *prev;
  long size; // ONLY FOR MAP
} t_lst;

typedef struct s_vec2d {
  int x;
  int y;
} t_vec2d;

typedef struct s_map {
  char **map;
  t_vec2d *sizes;
  t_vec2d *pos;
  enum param_type init_direc;
} t_map;

typedef struct s_token {
  t_lst *map;
  char *north_texture;
  char *south_texture;
  char *west_texture;
  char *east_texture;
  char *celling_color;
  char *floor_color;
} t_token;

typedef struct s_color {
  int red;
  int green;
  int blue;
} t_color;

typedef struct s_param {
  t_color *floor_color;
  t_color *celling_color;
  char *north_texture;
  char *south_texture;
  char *west_texture;
  char *east_texture;
  t_map *map_data;
} t_param;

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

/*---------------FREE---------------*/
void	free_tokens(t_token *tokens, t_lst *content);
void	free_tab(char **tab);
void	free_lst(t_lst *lst);
void	free_param(t_param *param);

/*-----parsing_and_error_handle-----*/
t_param			*parser_and_error_check(char *argv);
int				extension_check(char *argv);
void			exit_strerror(char *str, int code);
void			malloc_null_check(void *ptr);
int				verify_line(char *info, int *count, int fd);
t_lst			*allocate_file_content(char *argv);
t_token			*tokeniz_file_content(t_lst *file_content);
t_param			*get_and_verify_param(t_token *tokens);
void			verify_map(t_param *param, t_lst *lst);
void			parser_map(t_param *param, t_lst *lst);
t_vec2d			vec2d(int x, int y);
// int		verify_type(char *info, int *count);

/*-----LIBFT-----*/
void fd_putstr(char *str, int fd);
char *get_next_line(int fd);
char *ft_memdel(char **ptr);
char *ft_strchr(const char *s, int c);
char *ft_strjoin(char *s1, char *s2, int r);
char *ft_strdup(const char *s1);
char **ft_split(char *s, char c);
int ft_atoi(const char *str);
char *ft_strtrim(char *str, char c);
#endif
