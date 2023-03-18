/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:08:57 by fsemke            #+#    #+#             */
/*   Updated: 2023/03/16 12:35:45 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
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
#  define A_KEY 97
#  define W_KEY 119
#  define S_KEY 115
#  define D_KEY 100
#  define LEFT_KEY 65361
#  define RIGHT_KEY 65363
#  define ESC_KEY 65307
#  define X_BTN 33
# endif

# define NORTH 1
# define EAST 2
# define SOUTH 3
# define WEST 4

/* typedef struct s_mlx
{

}	t_mlx; */

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
}	t_map;


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

//check_map
int		ft_check_valid_file(char *file);
void	ft_check_errors(t_map *map);

#endif