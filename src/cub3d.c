/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:08:44 by fsemke            #+#    #+#             */
/*   Updated: 2023/04/06 14:53:00 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_init_map_default(t_map *map)
{
	ft_memset((void *)map, 0, sizeof(t_map));
	map->map = NULL;
	map->NO_texture = NULL;
	map->EA_texture = NULL;
	map->SO_texture = NULL;
	map->WE_texture = NULL;
	map->player_x = -1;
	map->player_y = -1;
	map->player_orientation = -1;
}

void	ft_init(char **argv, t_map *map, t_app *app)
{
	ft_init_map_default(map);
	ft_read_map(argv[1], map);
	app->map = map;
	ft_app_var_init(app, app->map);
}

void	ft_text_to_img(t_app *a)
{
	a->text_N = malloc(sizeof(t_img));
	a->text_S = malloc(sizeof(t_img));
	a->text_W = malloc(sizeof(t_img));
	a->text_E = malloc(sizeof(t_img));
	a->text_N->img_ref_ptr = mlx_xpm_file_to_image(a->com, a->map->NO_texture, \
	&(a->text_N->sz_x), &(a->text_N->sz_y));
	a->text_S->img_ref_ptr = mlx_xpm_file_to_image(a->com, a->map->SO_texture, \
	&(a->text_S->sz_x), &(a->text_S->sz_y));
	a->text_W->img_ref_ptr = mlx_xpm_file_to_image(a->com, a->map->WE_texture, \
	&(a->text_W->sz_x), &(a->text_W->sz_y));
	a->text_E->img_ref_ptr = mlx_xpm_file_to_image(a->com, a->map->EA_texture, \
	&(a->text_E->sz_x), &(a->text_E->sz_y));
	a->text_N->addr = mlx_get_data_addr(a->text_N->img_ref_ptr, \
	&(a->text_N->bpp), &(a->text_N->line_length), &(a->text_N->endian));
	a->text_S->addr = mlx_get_data_addr(a->text_S->img_ref_ptr, \
	&(a->text_S->bpp), &(a->text_S->line_length), &(a->text_S->endian));
	a->text_W->addr = mlx_get_data_addr(a->text_W->img_ref_ptr, \
	&(a->text_W->bpp), &(a->text_W->line_length), &(a->text_W->endian));
	a->text_E->addr = mlx_get_data_addr(a->text_E->img_ref_ptr, \
	&(a->text_E->bpp), &(a->text_E->line_length), &(a->text_E->endian));
}

/*
 * Map stuff only
 */
static void	ft_init_map_stuff(t_app *a)
{
	a->com = mlx_init();
	a->win = mlx_new_window(a->com, a->win_sz_x, a->win_sz_y, WIN_TITLE_MAP);
	a->img = ft_img_create_color_img(a->com, 0x00FFFFBB, IMG_SZ_X_WALL, \
	IMG_SZ_Y_WALL);
	a->black_backgroud = ft_img_create_color_img(a->com, 0x00000000, \
	a->win_sz_x, a->win_sz_y);
}

int	main(int argc, char **argv)
{
	t_map		map;
	t_app		app;
	t_player	player;

	if (argc != 2)
	{
		ft_putendl_fd("Insert one map (*.cub)", 1);
		exit(1);
	}
	ft_init(argv, &map, &app);
	ft_init_map_stuff(&app);
	app.win_3d = mlx_new_window(app.com, SCR_WIDTH_PX, SCR_HEIGHT_PX, \
	WIN_TITLE_WORLD);
	ft_text_to_img(&app);
	ft_player_init(&player, &map, &app);
	app.player = &player;
	ft_app_display_map(&app, &map, "1", app.img);
	mlx_hook(app.win_3d, ON_DESTROY, 1L, ft_app_close, &app);
	mlx_hook(app.win_3d, ON_KEYDOWN, 1, ft_key_pressed, &app);
	mlx_hook(app.win_3d, ON_KEYUP, 2, ft_key_released, &player);
	mlx_loop_hook(app.com, ft_loop_player, &app);
	mlx_loop(app.com);
}
