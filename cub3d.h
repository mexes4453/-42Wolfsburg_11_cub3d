/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:08:57 by fsemke            #+#    #+#             */
/*   Updated: 2023/03/21 20:47:56by fsemke           ###   ########.fr       */
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
#  define A_KEY 0
#  define W_KEY 13
#  define S_KEY 1
#  define D_KEY 2
#  define LEFT_KEY 123
#  define RIGHT_KEY 124
#  define ESC_KEY 53
#  define X_BTN 17

# elif defined __unix__
#  include "mlx_linux/mlx.h"
/*
#  define A_KEY 97
#  define W_KEY 119
#  define S_KEY 115
#  define D_KEY 100
#  define LEFT_KEY 65361
#  define RIGHT_KEY 65363
#  define ESC_KEY 65307
#  define X_BTN 33
*/
enum e_E_APP_EVENT{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum e_KEYS
{
	KEY_ESC = 65307,
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363,
	KEY_APP_CLOSE_ICON = -16777904L
};
# endif

# define NORTH 1
# define EAST 2
# define SOUTH 3
# define WEST 4

# define PI 3.1415926
# define X 0
# define Y 1

# define DIR_LENGTH 50
# define ANGLE_SENSITIVITY 0.0003 //higher == faster
# define MOVE_SPEED 0.01 //higher == faster
# define FOV 90

# define IMG_SZ_X_WALL (50)
# define IMG_SZ_Y_WALL (50)
# define IMG_SZ_X_PLAYER (2)
# define IMG_SZ_Y_PLAYER (2)
# define BIT_SIZE_BYTE (8)
# define TRUE_DESTROY (1)
# define FALSE_DESTROY (0)
# define WIN_TITLE_MAP ("cub3d_map")
# define COL_PLAYER (0x00FFFF00)        // YELLOW
# define COL_BLACK (0x00000000)        // BLACK
# define PX_MOVE (5)
# define ROTATE_ANGLE_OFFSET (0.1)




typedef struct s_map
{
	char	**map; //freed in ft_clean_parsing()
	int		map_size_x;
	int		map_size_y;
	char	*NO_texture; //freed in ft_clean_parsing()
	char	*EA_texture; //freed in ft_clean_parsing()
	char	*SO_texture; //freed in ft_clean_parsing()
	char	*WE_texture; //freed in ft_clean_parsing()
	int		floor_c;
	int		ceilling_c;
	int		player_x; //Default -1
	int		player_y; //Default -1
	int		player_orientation; //Default -1
    int     idx_x; // used to iterate within map arrays
    int     idx_y; // used to iterate over arrays store in map ptr
    char    chr;    // stores the char read from the map array
}	t_map;

typedef struct s_img
{
	void	*img_ref_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		endian;
	int		line_length;
	int		sz_x;
	int		sz_y;
}			t_img;


typedef enum e_pos
{
	origin,
	dir_pos,
	dir_neg,
	dir,
    next,
	/*-----*/
	MaxPos
}	t_pos;


typedef struct s_line
{
	int startPosX;
	int startPosY;
	int endPosX;
	int endPosY;
	int color;
}	t_line;

typedef struct s_ray
{
    int r;
    int mx;
    int my;
    int mp;
    int dof;
    int rlen_max;
    float rx;
    float ry;
    float ra;
    float xo;
    float yo;
    float aTan;
    t_line  *rayline;
}   t_ray;


typedef struct s_player
{
	double		Pos[MaxPos][2];
	double		heading_angle;
	double		delta_x;
	double		delta_y;
	int			key_w;
	int			key_a;
	int			key_s;
	int			key_d;
	int			key_left;
	int			key_right;
	t_img	    *img;
	t_img	    *black_img;
    double      world_pos_x;
    double      world_pos_y;
    t_line      *headline;
	//t_img	    *img_dir;
	/*
	t_img	    *img_dir_neg;
	t_img	    *
	*/
}			t_player;



typedef struct s_app
{
	void		*win;
	void		*com;
	int			rc;
	int			win_sz_x;
	int			win_sz_y;
	size_t		px;
	size_t		py;
	t_map		*map;
	t_img		*img;
	t_player	*player;
    t_ray       *ray;
 //   t_player	p;
//	t_queue		*rq;
//	t_queue		*cq;
//	char		**matrix;
//	int			t_r;
//	int			t_c;
//	int			p_r;
//	int			p_c;
}				t_app;




//ft_split custom
char	**ft_split_custom(const char *s, char c);

//cleanup
void	ft_clean_2d_array(char **array);
void	ft_clean_parsing(t_map *map);

// cub3d
void	ft_init_map_default(t_map *map);
void	ft_init(char **argv, t_map *map);

//error
void	error_exit(char *s, t_map *map);

//parsing
void	ft_set_spawn(t_map *map, int x, int y);
void	ft_parse_infos(char *line, t_map *map);
void	ft_parsing_file(char **file, t_map *map);

//read_map
char	*ft_read(int fd);
char	**ft_read_file(char *filename);
int		ft_map_extension(char *filename);
int		ft_read_map(char *filename, t_map *map);

//set_map_info
void	ft_set_texture(char *line, char **var_texture, t_map *map);
void	ft_set_color(char *line, t_map *map);
int		ft_color_to_int(char *line, t_map *map);
int		ft_check_rgb(int rgb[3]);
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
int     ft_app_close(void *params);
t_img	*ft_img_create_color_img(void *mlxPtr, uint32_t color, int szX, int szY);
int     ft_app_display_map(t_app *a, t_map *m, char *S, t_img *i);
void    ft_player_init(t_player *p, t_map *m, t_app *app);
int		ft_key_pressed(int key, t_app *a);
int		ft_key_released(int key, t_player *p);
int		ft_player_move(t_app *a);
int		ft_player_angle(int key, t_app *a);
int		ft_loop_player(t_app *app);
void    ft_draw_line(void *mlx, void *win, t_line *line);




/* new functions */
void ft_draw_player(t_app *a);
void ft_draw_rays(t_app *a);

#endif