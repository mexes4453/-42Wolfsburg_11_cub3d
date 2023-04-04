/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:05:49 by fsemke            #+#    #+#             */
/*   Updated: 2023/03/28 21:23:132 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int ft_player_move(t_app *a)
{
	int old[MaxPos][2];
	int i;

	i = 0;
	while (i < MaxPos)
	{
		old[i][X] = a->player->Pos[i][X];
		old[i][Y] = a->player->Pos[i][Y];
		++i;
	}

	//move the player
	if (a->player->key_w)
		ft_onKeyPress_W(a);
	if (a->player->key_a)
		ft_onKeyPress_A(a);
	if (a->player->key_s)
		ft_onKeyPress_S(a);
	if (a->player->key_d)
		ft_onKeyPress_D(a);

	//if  (a->print_flag == 1)
	if  (1)
	{
		//overwrite everything on the map
		mlx_put_image_to_window(a->com, a->win, a->black_backgroud->img_ref_ptr, 0, 0);
		ft_app_display_map(a, a->map, "1", a->img);
		
		a->px = 0;
		a->py = 0;

		//print new player position dots on map
		(void)old;
/* 		if (old[dir][X] != -1)//dont run at first execution
		{
			mlx_put_image_to_window(a->com, a->win, a->player->black_img->img_ref_ptr, old[origin][X], old[origin][Y]); //print black img
			mlx_put_image_to_window(a->com, a->win, a->player->black_img->img_ref_ptr, old[dir][X], old[dir][Y]); //black
			mlx_put_image_to_window(a->com, a->win, a->player->black_img->img_ref_ptr, old[dir_neg][X], old[dir_neg][Y]); //black
			mlx_put_image_to_window(a->com, a->win, a->player->black_img->img_ref_ptr, old[dir_pos][X], old[dir_pos][Y]); //black
		} */
		mlx_put_image_to_window(a->com, a->win, a->player->img->img_ref_ptr, a->player->Pos[origin][X] * IMG_SZ_X_WALL, a->player->Pos[origin][Y] * IMG_SZ_Y_WALL);
/* 		mlx_put_image_to_window(a->com, a->win, a->player->img->img_ref_ptr, a->player->Pos[dir][X], a->player->Pos[dir][Y]);
		mlx_put_image_to_window(a->com, a->win, a->player->img->img_ref_ptr, a->player->Pos[dir_neg][X], a->player->Pos[dir_neg][Y]);
		mlx_put_image_to_window(a->com, a->win, a->player->img->img_ref_ptr, a->player->Pos[dir_pos][X], a->player->Pos[dir_pos][Y]); */
		

		// cast ray
		// compute  (FOV / (FOV/SCR_WIDTH) / RAY_LINE_PX_WIDTH) + 1
		
		t_cmp_lines rayline;
		//t_cmp_lines vert;
		t_img	*tmp;
		
		//Create main img
		tmp = ft_calloc(1, sizeof(t_img));
		tmp->sz_x = SCR_WIDTH_PX;
		tmp->sz_y = SCR_HEIGHT_PX;
		tmp->img_ref_ptr = mlx_new_image(a->com, SCR_WIDTH_PX, SCR_HEIGHT_PX);
		tmp->addr = mlx_get_data_addr(tmp->img_ref_ptr, &(tmp->bits_per_pixel), &(tmp->line_length), &(tmp->endian));

		ft_img_fill_floor_ceilling(tmp, a->map->ceilling_c, a->map->floor_c);
		a->main_img = tmp;

		int x;
		x = 0;
		while (x < SCR_WIDTH_PX)
		{
			//new try
			a->player->cameraX = 2 * x / (double)SCR_WIDTH_PX - 1;
			a->player->vec_rayDir[X] = a->player->vec_dir[X] + a->player->vec_plane[X] * a->player->cameraX;
			a->player->vec_rayDir[Y] = a->player->vec_dir[Y] + a->player->vec_plane[Y] * a->player->cameraX;
			a->player->map_pos[X] = (int) a->player->Pos[origin][X];
			a->player->map_pos[Y] = (int) a->player->Pos[origin][Y];

			
			ft_ray_get_dist(a, &rayline);

			t_line line; //print map rayline
			line.startPosX = (int)(a->player->Pos[origin][X] * IMG_SZ_X_WALL);
			line.startPosY = (int)(a->player->Pos[origin][Y] * IMG_SZ_Y_WALL);
			line.color = 0x0000FF00;
			
			line.endPosX = rayline.coord_hit[X];
			line.endPosY = rayline.coord_hit[Y];
			ft_draw_line(a->com, a->win, &line);
			
			ft_render_wall(a, &rayline, x);
			++x;
		}
		mlx_put_image_to_window(a->com, a->win_world, a->main_img->img_ref_ptr, 0, 0);
		mlx_destroy_image(a->com, a->main_img->img_ref_ptr);
		a->main_img = NULL;
		//ft_printf("Amount of Raylines: %d", i);
		a->print_flag = 0;
	}
	return (0);
}

int ft_player_angle(t_app *a)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = a->player->vec_dir[X];
	oldPlaneX = a->player->vec_plane[X];
	if (a->player->key_left)
	{	
		a->player->vec_dir[X] = a->player->vec_dir[X] * cos(-ROT_SPEED) - a->player->vec_dir[Y] * sin(-ROT_SPEED);
		a->player->vec_dir[Y] = oldDirX * sin(-ROT_SPEED) + a->player->vec_dir[Y] * cos(-ROT_SPEED);
		a->player->vec_plane[X] = a->player->vec_plane[X] * cos(-ROT_SPEED) - a->player->vec_plane[Y] * sin(-ROT_SPEED);
		a->player->vec_plane[Y] = oldPlaneX * sin(-ROT_SPEED) + a->player->vec_plane[Y] * cos(-ROT_SPEED);
		a->print_flag = 1;
	}
	if (a->player->key_right)
	{
		a->player->vec_dir[X] = a->player->vec_dir[X] * cos(ROT_SPEED) - a->player->vec_dir[Y] * sin(ROT_SPEED);
		a->player->vec_dir[Y] = oldDirX * sin(ROT_SPEED) + a->player->vec_dir[Y] * cos(ROT_SPEED);
		a->player->vec_plane[X] = a->player->vec_plane[X] * cos(ROT_SPEED) - a->player->vec_plane[Y] * sin(ROT_SPEED);
		a->player->vec_plane[Y] = oldPlaneX * sin(ROT_SPEED) + a->player->vec_plane[Y] * cos(ROT_SPEED);
		a->print_flag = 1;
	}
	return (0);
}

int ft_loop_player(t_app *app)
{
	ft_player_angle(app);
	ft_player_move(app);
	return (0);
}

void	ft_img_fill_floor_ceilling(t_img *img, uint32_t ceilling_c, uint32_t floor_c)
{
	int	x;
	int y;

	y = 0;
	while (y < img->sz_y / 2)
	{
		x = 0;
		while (x < img->sz_x)
		{
			ft_app_pixel_put_on_img(img, x, y, ceilling_c);
			++x;
		}
		++y;
	}
	while (y < img->sz_y)
	{
		x = 0;
		while (x < img->sz_x)
		{
			ft_app_pixel_put_on_img(img, x, y, floor_c);
			++x;
		}
		++y;
	}
}