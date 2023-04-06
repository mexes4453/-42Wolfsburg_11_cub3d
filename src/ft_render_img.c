/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 23:12:45 by fsemke            #+#    #+#             */
/*   Updated: 2023/04/06 14:58:26 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* Printing ray for the map
 */
static void	ft_print_map_ray(t_app *a, t_cmp_lines *rayline)
{
	t_line	line;

	line.startPosX = (int)(a->player->Pos[origin][X] * IMG_SZ_X_WALL);
	line.startPosY = (int)(a->player->Pos[origin][Y] * IMG_SZ_Y_WALL);
	line.color = 0x0000FF00;
	line.endPosX = rayline->coord_hit[X];
	line.endPosY = rayline->coord_hit[Y];
	ft_draw_line(a->com, a->win, &line);
}

static void	ft_update_player_var(t_app *a, t_cmp_lines *rayline, int x)
{
	a->player->cameraX = 2 * x / (double)SCR_WIDTH_PX - 1;
	a->player->rayDir[X] = a->player->dir[X] + a->player->plane[X] \
	* a->player->cameraX;
	a->player->rayDir[Y] = a->player->dir[Y] + a->player->plane[Y] \
	* a->player->cameraX;
	a->player->map_pos[X] = (int) a->player->Pos[origin][X];
	a->player->map_pos[Y] = (int) a->player->Pos[origin][Y];
	ft_ray_get_dist(a, rayline);
	ft_print_map_ray(a, rayline);
}

static void	ft_fill_img_color(t_img *img, uint32_t ceilling_c, uint32_t floor_c)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->sz_y / 2)
	{
		x = -1;
		while (++x < img->sz_x)
			ft_app_pixel_put_on_img(img, x, y, ceilling_c);
		++y;
	}
	while (y < img->sz_y)
	{
		x = -1;
		while (++x < img->sz_x)
			ft_app_pixel_put_on_img(img, x, y, floor_c);
		++y;
	}
}

void	ft_render_img(t_app *a)
{
	t_cmp_lines	rayline;
	int			x;

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
