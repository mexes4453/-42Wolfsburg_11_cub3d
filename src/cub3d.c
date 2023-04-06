/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:08:44 by fsemke            #+#    #+#             */
/*   Updated: 2023/04/06 23:39:10 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_init_map_default(t_map *map)
{
	ft_memset((void *)map, 0, sizeof(t_map));
	map->map = NULL;
	map->no_texture = NULL;
	map->ea_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
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
	a->text_n = malloc(sizeof(t_img));
	a->text_s = malloc(sizeof(t_img));
	a->text_w = malloc(sizeof(t_img));
	a->text_e = malloc(sizeof(t_img));
	a->text_n->img_ref_ptr = mlx_xpm_file_to_image(a->com, a->map->no_texture, \
	&(a->text_n->sz_x), &(a->text_n->sz_y));
	a->text_s->img_ref_ptr = mlx_xpm_file_to_image(a->com, a->map->so_texture, \
	&(a->text_s->sz_x), &(a->text_s->sz_y));
	a->text_w->img_ref_ptr = mlx_xpm_file_to_image(a->com, a->map->we_texture, \
	&(a->text_w->sz_x), &(a->text_w->sz_y));
	a->text_e->img_ref_ptr = mlx_xpm_file_to_image(a->com, a->map->ea_texture, \
	&(a->text_e->sz_x), &(a->text_e->sz_y));
	a->text_n->addr = mlx_get_data_addr(a->text_n->img_ref_ptr, \
	&(a->text_n->bpp), &(a->text_n->line_length), &(a->text_n->endian));
	a->text_s->addr = mlx_get_data_addr(a->text_s->img_ref_ptr, \
	&(a->text_s->bpp), &(a->text_s->line_length), &(a->text_s->endian));
	a->text_w->addr = mlx_get_data_addr(a->text_w->img_ref_ptr, \
	&(a->text_w->bpp), &(a->text_w->line_length), &(a->text_w->endian));
	a->text_e->addr = mlx_get_data_addr(a->text_e->img_ref_ptr, \
	&(a->text_e->bpp), &(a->text_e->line_length), &(a->text_e->endian));
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
	app.com = mlx_init();
	app.win_3d = mlx_new_window(app.com, SCR_WIDTH_PX, SCR_HEIGHT_PX, \
	WIN_TITLE_WORLD);
	ft_text_to_img(&app);
	ft_player_init(&player, &map);
	app.player = &player;
	mlx_hook(app.win_3d, ON_DESTROY, 1L, ft_app_close, &app);
	mlx_hook(app.win_3d, ON_KEYDOWN, 1, ft_key_pressed, &app);
	mlx_hook(app.win_3d, ON_KEYUP, 2, ft_key_released, &player);
	mlx_loop_hook(app.com, ft_loop_player, &app);
	mlx_loop(app.com);
}
