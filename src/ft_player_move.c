/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:05:49 by fsemke            #+#    #+#             */
/*   Updated: 2023/04/06 20:23:00 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_img	*ft_create_new_img(void *mlx_ptr)
{
	t_img	*img;

	img = ft_calloc(1, sizeof(t_img));
	img->sz_x = SCR_WIDTH_PX;
	img->sz_y = SCR_HEIGHT_PX;
	img->img_ref_ptr = mlx_new_image(mlx_ptr, SCR_WIDTH_PX, SCR_HEIGHT_PX);
	img->addr = mlx_get_data_addr(img->img_ref_ptr, &(img->bpp), \
	&(img->line_length), &(img->endian));
	return (img);
}

int	ft_player_move(t_app *a)
{
	if (a->player->key_w)
		ft_on_key_press_w(a);
	if (a->player->key_a)
		ft_on_key_press_a(a);
	if (a->player->key_s)
		ft_on_key_press_s(a);
	if (a->player->key_d)
		ft_on_key_press_d(a);
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

int	ft_loop_player(t_app *app)
{
	ft_player_angle(app);
	ft_player_move(app);
	ft_render_img(app);
	return (0);
}
