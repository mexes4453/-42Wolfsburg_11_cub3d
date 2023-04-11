/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:08:57 by fsemke            #+#    #+#             */
/*   Updated: 2023/04/11 19:13:31 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdint.h>
# include "libft/libft.h"

# ifdef __APPLE__
#  include "mlx_darwin/mlx.h"
#  define KEY_A 0
#  define KEY_W 13
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_ESC 53
#  define X_BTN 17

# elif defined __unix__
#  include "mlx_linux/mlx.h"

#  define KEY_A 97
#  define KEY_W 119
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_ESC 65307
#  define X_BTN 33

# endif

enum e_E_APP_EVENT{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

# define NORTH 1
# define EAST 2
# define SOUTH 3
# define WEST 4

# define PI 3.1415926
# define RADIENT 0.01745329 //Multiply with degree val will get radient
# define X 0
# define Y 1

# define RS 0.03 //Rotation Speed higher == faster
# define MS 0.03 //Moving Speed higher == faster
# define GAP 0.25
# define SCR_WIDTH_PX 800
# define SCR_HEIGHT_PX 600

# define IMG_SZ_X_WALL (64)
# define IMG_SZ_Y_WALL (64)
# define BIT_SIZE_BYTE (8)
# define WIN_TITLE_WORLD ("cub3d_world")
# define FILE_EXT_TEXTURE (".xpm")
# define FILE_EXT_MAP (".cub")
# define WHITESPACE_CHAR ("\t ")

typedef struct s_map
{
	char	**map;
	char	**file;
	int		map_size_x;
	int		map_size_y;
	char	*no_texture;
	char	*ea_texture;
	char	*so_texture;
	char	*we_texture;
	int		floor_c;
	int		ceilling_c;
	int		player_x;
	int		player_y;
	int		player_orientation;
	int		idx_x;
	int		idx_y;
	char	chr;
}	t_map;

//bpp = bits_per_pixel
typedef struct s_img
{
	void	*img_ref_ptr;
	char	*addr;
	int		bpp;
	int		endian;
	int		line_length;
	int		sz_x;
	int		sz_y;
}			t_img;

//Used to print the raylines
typedef struct s_line
{
	int		start_posx;
	int		start_posy;
	int		end_posx;
	int		end_posy;
	double	raylength;
	int		color;
}	t_line;

//camerax pixel left = -1, mid = 0, right = 1
typedef struct s_player
{
	double	pos[2];
	double	dir[2];
	double	plane[2];
	double	raydir[2];
	double	camerax;
	int		map_pos[2];
	int		key_w;
	int		key_a;
	int		key_s;
	int		key_d;
	int		key_left;
	int		key_right;
}			t_player;

//Map var: win_sz_x, win_sz_y, px, py, *img, *black_background
typedef struct s_app
{
	void		*win_3d;
	void		*com;
	int			rc;
	int			win_sz_x;
	int			win_sz_y;
	size_t		px;
	size_t		py;
	t_map		*map;
	t_img		*main_img;
	t_img		*text_n;
	t_img		*text_s;
	t_img		*text_e;
	t_img		*text_w;
	t_img		*texture;
	t_player	*player;
	double		*raylengths;
}				t_app;

//Map var: coord_hit
typedef struct s_cmp_lines
{
	double	perp_w_dist;
	int		side;
	int		pole;
	double	wall_x;
	int		text_x;
	double	coord_hit[2];
}	t_cmp_lines;

typedef enum e_coord
{
	s,
	delta,
}	t_coord;

//ft_split custom
char	**ft_split_custom(const char *s, char c);

//cleanup
void	ft_clean_2d_array(char **array);
void	ft_clean_parsing(t_map *map);

// cub3d
void	ft_init_map_default(t_map *map);
void	ft_init(char **argv, t_map *map, t_app *app);

//error
void	error_exit(char *s, t_map *map);

//parsing
void	ft_set_spawn(t_map *map, int x, int y);
void	ft_parse_infos(char *line, t_map *map);
void	ft_parsing_file(char **file, t_map *map);

//read_map
char	*ft_read(int fd);
char	**ft_read_file(char *filename);
int		ft_read_map(char *filename, t_map *map);

//set_map_info
void	ft_set_texture(char *line, char **var_texture, t_map *map);
void	ft_set_color(char *line, t_map *map);
int		ft_color_to_int(char *line, t_map *map);
int		ft_combine_rgb(int r, int g, int b);

//ft_utlis
int		ft_line_empty(char *line);
char	*ft_strdup_up_to_space(const char *s);

//check_map
int		ft_check_valid_file(char *file);
void	ft_check_errors(t_map *map);

/**
 * @brief 
 * This function initialises the app variable to default value.
 * It updates the application window size by using the map size 
 * (x, y) and multiplying it with default pixel size 
 * 
 * @param a // pointer to app variable 
 * @param m // pointer to map variable
 */
void	ft_app_var_init(t_app *a, t_map *m);
int		ft_app_close(void *params);
t_img	*ft_img_create_color_img(void *mlxPtr, uint32_t color, \
int szX, int szY);
void	ft_player_init(t_player *p, t_map *m);
int		ft_key_pressed(int key, t_app *a);
int		ft_key_released(int key, t_player *p);
int		ft_player_move(t_app *a);
int		ft_player_angle(t_app *a);
int		ft_loop_player(t_app *app);
void	ft_draw_line(void *mlx, void *win, t_line *line);
void	ft_on_key_press_w(t_app *a);
void	ft_on_key_press_a(t_app *a);
void	ft_on_key_press_s(t_app *a);
void	ft_on_key_press_d(t_app *a);
void	ft_ray_get_dist(t_app *a, t_cmp_lines *line);
void	ft_render_wall(t_app *a, t_cmp_lines *l, int i);
void	ft_render_img(t_app *a);
void	ft_app_pixel_put_on_img(t_img *data, int x, int y, uint32_t color);
void	ft_text_to_img(t_app *a);
t_img	*ft_create_new_img(void *mlx_ptr);
void	ft_free_img(void *mlx_ptr, t_img *img);
void	ft_check_file_ext(char *filename, char *file_ext, t_map *m);

#endif