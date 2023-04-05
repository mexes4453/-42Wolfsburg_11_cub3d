/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:05:49 by fsemke            #+#    #+#             */
/*   Updated: 2023/04/05 21:09:24 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_update_player_var(t_app *a, t_cmp_lines *rayline, int x)
{
	a->player->cameraX = 2 * x / (double)SCR_WIDTH_PX - 1;
	a->player->rayDir[X] = a->player->dir[X] + a->player->plane[X] \
	* a->player->cameraX;
	a->player->rayDir[Y] = a->player->dir[Y] + a->player->plane[Y] \
	* a->player->cameraX;
	a->player->map_pos[X] = (int) a->player->Pos[origin][X];
	a->player->map_pos[Y] = (int) a->player->Pos[origin][Y];
	ft_ray_get_dist(a, rayline);
	//Map stuff
	{
		t_line	line;
		line.startPosX = (int)(a->player->Pos[origin][X] * IMG_SZ_X_WALL);
		line.startPosY = (int)(a->player->Pos[origin][Y] * IMG_SZ_Y_WALL);
		line.color = 0x0000FF00;
		line.endPosX = rayline->coord_hit[X];
		line.endPosY = rayline->coord_hit[Y];
		ft_draw_line(a->com, a->win, &line);
	}
}

void	ft_render_img(t_app *a)
{
	t_cmp_lines	rayline;
	int			x;

	//Create main img
	a->main_img = ft_create_new_img(a->com);
	ft_fill_img_color(a->main_img, a->map->ceilling_c, a->map->floor_c);
	x = 0;
	while (x < SCR_WIDTH_PX)
	{
		ft_update_player_var(a, &rayline, x);
		ft_render_wall(a, &rayline, x);
		++x;
	}
	mlx_put_image_to_window(a->com, a->win_3d, a->main_img->img_ref_ptr, 0, 0);
	mlx_destroy_image(a->com, a->main_img->img_ref_ptr);
	free (a->main_img);
	a->main_img = NULL;
}

t_img	*ft_create_new_img(void *mlx_ptr)
{
	t_img	*img;

	img = ft_calloc(1, sizeof(t_img));
	img->sz_x = SCR_WIDTH_PX;
	img->sz_y = SCR_HEIGHT_PX;
	img->img_ref_ptr = mlx_new_image(mlx_ptr, SCR_WIDTH_PX, SCR_HEIGHT_PX);
	img->addr = mlx_get_data_addr(img->img_ref_ptr, &(img->bits_per_pixel), \
	&(img->line_length), &(img->endian));
	return (img);
}

int ft_player_move(t_app *a)
{
	//move the player
	if (a->player->key_w)
		ft_onKeyPress_W(a);
	if (a->player->key_a)
		ft_onKeyPress_A(a);
	if (a->player->key_s)
		ft_onKeyPress_S(a);
	if (a->player->key_d)
		ft_onKeyPress_D(a);

	//Map stuff
	{
		//overwrite everything on the map with black
		mlx_put_image_to_window(a->com, a->win, a->black_backgroud->img_ref_ptr, 0, 0);
		ft_app_display_map(a, a->map, "1", a->img);
		//set var for map calculations
		a->px = 0;
		a->py = 0;
		//print new player position on map
		mlx_put_image_to_window(a->com, a->win, a->player->img->img_ref_ptr, a->player->Pos[origin][X] * IMG_SZ_X_WALL, \
		a->player->Pos[origin][Y] * IMG_SZ_Y_WALL);
	}
	return (0);
}

int	ft_player_angle(t_app *a)
{
	double		old_dirx;
	double		old_planex;
	t_player	*p;

	p = a->player;
	old_dirx = p->dir[X];
	old_planex = p->plane[X];
	if (p->key_left)
	{	
		p->dir[X] = p->dir[X] * cos(-RS) - p->dir[Y] * sin(-RS);
		p->dir[Y] = old_dirx * sin(-RS) + p->dir[Y] * cos(-RS);
		p->plane[X] = p->plane[X] * cos(-RS) - p->plane[Y] * sin(-RS);
		p->plane[Y] = old_planex * sin(-RS) + p->plane[Y] * cos(-RS);
	}
	if (p->key_right)
	{
		p->dir[X] = p->dir[X] * cos(RS) - p->dir[Y] * sin(RS);
		p->dir[Y] = old_dirx * sin(RS) + p->dir[Y] * cos(RS);
		p->plane[X] = p->plane[X] * cos(RS) - p->plane[Y] * sin(RS);
		p->plane[Y] = old_planex * sin(RS) + p->plane[Y] * cos(RS);
	}
	return (0);
}

int ft_loop_player(t_app *app)
{
	ft_player_angle(app);
	ft_player_move(app);
	ft_render_img(app);
	return (0);
}

void	ft_fill_img_color(t_img *img, uint32_t ceilling_c, uint32_t floor_c)
{
	int	x;
	int	y;

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
