/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 23:12:45 by fsemke            #+#    #+#             */
/*   Updated: 2023/04/06 20:28:35 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_update_player_var(t_app *a, t_cmp_lines *rayline, int x)
{
	a->player->camerax = 2 * x / (double)SCR_WIDTH_PX - 1;
	a->player->raydir[X] = a->player->dir[X] + a->player->plane[X] \
	* a->player->camerax;
	a->player->raydir[Y] = a->player->dir[Y] + a->player->plane[Y] \
	* a->player->camerax;
	a->player->map_pos[X] = (int) a->player->pos[X];
	a->player->map_pos[Y] = (int) a->player->pos[Y];
	ft_ray_get_dist(a, rayline);
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
