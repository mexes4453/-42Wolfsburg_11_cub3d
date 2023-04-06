/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:46:02 by fsemke            #+#    #+#             */
/*   Updated: 2023/04/06 17:09:32 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
 * This function selects the texture image to be rendered
 * depending on the wall orientation of the ray cast line.
 */
static void	ft_select_wall_texture(t_app *a, t_cmp_lines *l)
{
	if (l->pole == SOUTH)
		a->texture = a->text_s;
	else if (l->pole == NORTH)
		a->texture = a->text_n;
	else if (l->pole == EAST)
		a->texture = a->text_e;
	else if (l->pole == WEST)
		a->texture = a->text_w;
}

/*
 * This function performs the followings;
 * select wall texture for ray based on its orientation on map
 * Put Texture to Image
*/
void	ft_render_wall(t_app *a, t_cmp_lines *l, int x)
{
	int	draw_start;
	int	draw_end;
	int	render_height;
	int	text_y;

	render_height = (int)(SCR_HEIGHT_PX / l->perp_w_dist);
	draw_start = -render_height / 2 + SCR_HEIGHT_PX / 2;
	draw_end = render_height / 2 + SCR_HEIGHT_PX / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= SCR_HEIGHT_PX)
		draw_end = SCR_HEIGHT_PX - 1;
	ft_select_wall_texture(a, l);
	while (draw_start < draw_end)
	{
		text_y = abs((((draw_start * IMG_SZ_Y_WALL * 4 \
			- (SCR_HEIGHT_PX / 2 * IMG_SZ_Y_WALL * 4) \
			+ render_height * (IMG_SZ_Y_WALL / 2) * 4) \
			* IMG_SZ_Y_WALL) / render_height) / (IMG_SZ_Y_WALL * 4));
		ft_memcpy(a->main_img->addr + 4 * SCR_WIDTH_PX * draw_start + x * 4, \
		&a->texture->addr[text_y % IMG_SZ_Y_WALL * a->texture->line_length + \
		l->text_x % 64 * a->texture->bpp / 8], sizeof(int));
		++draw_start;
	}
}
