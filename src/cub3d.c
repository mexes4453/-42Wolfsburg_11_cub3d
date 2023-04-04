/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:08:44 by fsemke            #+#    #+#             */
/*   Updated: 2023/03/28 21:04:335 by fsemke           ###   ########.fr       */
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

static void	ft_print_all_information(t_map *map)
{
	//Testfunction delete it!
	printf("NO_Texture: %s\n", map->NO_texture);
	printf("EA_Texture: %s\n", map->EA_texture);
	printf("SO_Texture: %s\n", map->SO_texture);
	printf("WE_Texture: %s\n\n", map->WE_texture);

	printf("Floor color: %d\n", map->floor_c);
	printf("Ceilling color: %d\n\n", map->ceilling_c);

	printf("Map_size_x: %d\n", map->map_size_x);
	printf("Map_size_y: %d\n\n", map->map_size_y);

	printf("Map: \n");
	for (int i = 0; map->map[i]; ++i)
	{
		printf("%s\n", map->map[i]);
	}
}

void	ft_init(char **argv, t_map *map)
{
	ft_init_map_default(map);
	ft_read_map(argv[1], map);
	ft_print_all_information(map);
}

void	ft_text_to_img(t_app *a)
{
	a->text_N = malloc(sizeof(t_img));
	a->text_S = malloc(sizeof(t_img));
	a->text_W = malloc(sizeof(t_img));
	a->text_E = malloc(sizeof(t_img));
	a->text_N->img_ref_ptr = mlx_xpm_file_to_image(a->com, a->map->NO_texture, &(a->text_N->sz_x), &(a->text_N->sz_y));
	a->text_S->img_ref_ptr = mlx_xpm_file_to_image(a->com, a->map->SO_texture, &(a->text_S->sz_x), &(a->text_S->sz_y));
	a->text_W->img_ref_ptr = mlx_xpm_file_to_image(a->com, a->map->WE_texture, &(a->text_W->sz_x), &(a->text_W->sz_y));
	a->text_E->img_ref_ptr = mlx_xpm_file_to_image(a->com, a->map->EA_texture, &(a->text_E->sz_x), &(a->text_E->sz_y));
	a->text_N->addr = mlx_get_data_addr(a->text_N->img_ref_ptr, &(a->text_N->bits_per_pixel), &(a->text_N->line_length), &(a->text_N->endian));
	a->text_S->addr = mlx_get_data_addr(a->text_S->img_ref_ptr, &(a->text_S->bits_per_pixel), &(a->text_S->line_length), &(a->text_S->endian));
	a->text_W->addr = mlx_get_data_addr(a->text_W->img_ref_ptr, &(a->text_W->bits_per_pixel), &(a->text_W->line_length), &(a->text_W->endian));
	a->text_E->addr = mlx_get_data_addr(a->text_E->img_ref_ptr, &(a->text_E->bits_per_pixel), &(a->text_E->line_length), &(a->text_E->endian));
}

int	main(int argc, char **argv)
{
	t_map	    map;
    t_app	    app;
    t_img       *wall_img;
    t_player    player;
	//t_mlx	mlx;

	if (argc != 2)
	{
		ft_putendl_fd("Insert one map (*.cub)", 1);
		exit(1);
	}
	ft_init(argv, &map);
    app.map = &map;
    ft_app_var_init(&app, app.map);
    

    // create player map
    app.com = mlx_init();
	app.win = mlx_new_window(app.com, app.win_sz_x, app.win_sz_y, WIN_TITLE_MAP);
	app.win_world = mlx_new_window(app.com, SCR_WIDTH_PX, SCR_HEIGHT_PX, WIN_TITLE_WORLD);
/* 	t_line perspective_line;
	perspective_line.startPosX = 0;
	perspective_line.startPosY = SCR_HEIGHT_PX / 2;
	perspective_line.endPosX = SCR_WIDTH_PX;
	perspective_line.endPosY = SCR_HEIGHT_PX / 2;
	perspective_line.color = 0x00FFFF00;
	ft_draw_line(app.com, app.win_world, &perspective_line); */

    /* Create player map */
    wall_img = ft_img_create_color_img(app.com, 0x00FFFFBB, IMG_SZ_X_WALL, IMG_SZ_Y_WALL);

	
    app.img = wall_img;
	app.black_backgroud = ft_img_create_color_img(app.com, 0x00000000, app.win_sz_x, app.win_sz_y);
	
	ft_text_to_img(&app);
	ft_player_init(&player, &map, &app);
	app.player = &player;
    //ft_app_display_img(&app, &(app.img), FALSE_DESTROY);
    // loop
    ft_app_display_map(&app, &map, "1", wall_img);
    /* mlx_put_image_to_window(app.com, app.win, player.img->img_ref_ptr, player.Pos[origin][X], player.Pos[origin][Y]);
    mlx_put_image_to_window(app.com, app.win, player.img->img_ref_ptr, player.Pos[dir][X], player.Pos[dir][Y]);
    mlx_put_image_to_window(app.com, app.win, player.img->img_ref_ptr, player.Pos[dir_neg][X], player.Pos[dir_neg][Y]);
    mlx_put_image_to_window(app.com, app.win, player.img->img_ref_ptr, player.Pos[dir_pos][X], player.Pos[dir_pos][Y]); */


    //mlx_put_image_to_window(app.com, app.win, wall_img->img_ref_ptr, IMG_SZ_X, IMG_SZ_Y);
    // end loop

    
	//ft_app_render_imgs(&app);
	//mlx_hook(app.win, ON_KEYDOWN, 1L, ft_app_key_handler, &app);
	mlx_hook(app.win_world, ON_DESTROY, 1L, ft_app_close, &app);
	mlx_hook(app.win_world, ON_KEYDOWN, 1, ft_key_pressed, &app);
	mlx_hook(app.win_world, ON_KEYUP, 2, ft_key_released, &player);
	mlx_loop_hook(app.com, ft_loop_player, &app);
	mlx_loop(app.com);
}
