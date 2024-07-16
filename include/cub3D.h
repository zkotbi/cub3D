/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 23:29:00 by zkotbi            #+#    #+#             */
/*   Updated: 2024/07/16 15:30:17 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <MLX42/MLX42.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1600
# define HEIGHT 1024
# define CELLSIZE 32.0f
# define ROTATE_SEEP 3
# define PI 3.14159265359f
# define eps 1e-4
# define MAX_VIEW_POINT 1
# define FOV 66.0f
# define DIR_LENGTH 2.0f
#define enforce(condition) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "Assertion failed: (%s), function %s, file %s, line %d.\n", \
                    #condition, __FUNCTION__, __FILE__, __LINE__); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

# include <MLX42/MLX42.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define VEC(v) printf("%s => (%d, %d)\n", #v, v.x, v.y);
# define FVEC(v) printf("%s => (%lf, %lf)\n", #v, v.x, v.y);
# define pair2f(x, y) printf("(%lf, %lf)\n", x, y);
# define pair2d(x, y) printf("(%d, %d)\n", x, y);
# define INT(x) printf("%s=>(%d)\n", #x, x);
# define HEX(x) printf("%s=>(%x)\n", #x, x);
# define CHAR(x) printf("%s=>(%c)\n", #x, x);
# define UINT(x) printf("%s=>(%u)\n", #x, x);
# define STR(x) printf("%s=>(%s)\n", #x, x);
# define FINT(x) printf("%s=>(%lf)\n", #x, x);


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
enum				param_type
{
	CELLING,
	FLOOR,
	NORTH  = 270,
	SOUTH = 90,
	EAST = 0,
	WEST = 180,
};
typedef struct s_lst
{
	char			*content;
	struct s_lst	*next;
	struct s_lst	*prev;
	long size; // ONLY FOR MAP
}					t_lst;

typedef struct s_draw
{
	int x_pos;
	mlx_image_t *img;
	double distance;
} t_draw;

typedef struct s_vec2d
{
	int				x;
	int				y;
}					t_vec2d;

typedef struct s_vec2f
{
	double			x;
	double			y;
}					t_vec2f;

typedef struct s_map
{
	char			**map;
	t_vec2d			sizes;
	t_vec2f			pos;
	enum param_type	init_direc;
}					t_map;

typedef struct s_token
{
	t_lst			*map;
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	char			*celling_color;
	char			*floor_color;
}					t_token;

typedef struct s_color
{
	uint8_t			alpha;
	uint8_t			blue;
	uint8_t			green;
	uint8_t			red;
}					t_color;

typedef struct s_param
{
	t_color			floor_color;
	t_color			celling_color;
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	t_map			*map_data;
}					t_param;

typedef struct s_text 
{
    mlx_texture_t *north;
    mlx_texture_t *south;
	mlx_texture_t *east;
    mlx_texture_t *west;

} t_text;

typedef struct s_img
{
	mlx_image_t	*north;
	mlx_image_t	*south;
	mlx_image_t	*east;
	mlx_image_t	*west;
}  t_img;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_image_t		*player;
	t_param			*param;
	double			player_angle;
	t_img		*texture;
}					t_data;


/*---------------TEXTURES---------------*/
void				get_texture(t_data *data);

/*---------------FREE---------------*/
void				free_tokens(t_token *tokens, t_lst *content);
void				free_tab(char **tab);
void				free_lst(t_lst *lst);
void				free_param(t_param *param);
void				destroy_texture(t_text *texture, int n);
void				destroy_img(t_img *img, mlx_t *mlx, int n, t_text *text);

/*-----parsing_and_error_handle-----*/
t_param				*parser_and_error_check(char *argv);
int					extension_check(char *argv);
void				exit_strerror(char *str, int code);
void				malloc_null_check(void *ptr);
int					verify_line(char *info, int *count, int fd);
t_lst				*allocate_file_content(char *argv);
t_token				*tokeniz_file_content(t_lst *file_content);
t_param				*get_and_verify_param(t_token *tokens);
void				verify_map(t_param *param, t_lst *lst);
void				parser_map(t_param *param, t_lst *lst);
/*math */
t_vec2d				vec2d(int x, int y);
t_vec2f				vec2f(double x, double y);
t_vec2d				sub2d(t_vec2d v, t_vec2d u);
t_vec2f				sub2f(t_vec2f v, t_vec2f u);
t_vec2f				add2f(t_vec2f v, t_vec2f u);
t_vec2d				add2d(t_vec2d v, t_vec2d u);

t_vec2f				min_distance(t_vec2f a, t_vec2f b, t_vec2f origin);
double				vec_distance(t_vec2f a, t_vec2f b);
t_vec2f				line_eqution(t_vec2f v, t_vec2f u);
t_vec2f				grid(t_vec2d vec);
t_vec2d				pixel(t_vec2d vec);
t_vec2f				direction(double angle);
t_vec2f				vec2dtf(t_vec2d v);
double				sign(double n);
double				max(double a, double b);
double				min(double a, double b);
t_vec2f				scale(t_vec2f vec, double scalar);
t_vec2f				mul(t_vec2f v, t_vec2f u);
t_vec2f				lerp(t_vec2f v, t_vec2f u, double alpha);

/*ray Casting*/
// t_vec2f				ray_casting(t_vec2f position, t_vec2f direction);
t_vec2f				get_wall_postion(t_map *map_data, t_vec2f player_position,
						double angle);
// int		verify_type(char *info, int *count);

void				ver_line(t_data *data, int x, t_draw *draw);
void				color_floor_ceiling(t_data *data, int fcolor, int ccolor);
int					get_tex_x(t_vec2f point, double angle, mlx_image_t *img);
mlx_image_t			*get_img_direc(t_vec2f point, t_data *data);
/*-----LIBFT-----*/
void				fd_putstr(const char *str, int fd);
char				*get_next_line(int fd);
char				*ft_memdel(char **ptr);
char				*ft_strchr(const char *s, int c);
char				*ft_strjoin(char *s1, char *s2, int r);
char				*ft_strdup(const char *s1);
char				**ft_split(char *s, char c);
int					ft_atoi(const char *str);
char				*ft_strtrim(char *str, char c);
// mlx hooks
void				keybord(mlx_key_data_t keydata, void *param);

void				mini_map_render(t_data *data, t_map *map_data);
void				put_pixels(mlx_image_t *image, t_vec2d coord, t_vec2d size,
						int color);
#endif
