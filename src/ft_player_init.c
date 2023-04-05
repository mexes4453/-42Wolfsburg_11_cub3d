/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 17:27:18 by cudoh             #+#    #+#             */
/*   Updated: 2023/04/05 22:11:39 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void ft_player_init(t_player *p, t_map *m, t_app *app)
{
	ft_memset((void *)p, 0, sizeof(t_player));
	p->Pos[origin][X] = m->player_x + 0.5;
	p->Pos[origin][Y] = m->player_y + 0.5;
	p->Pos[dir_pos][X] = -1;
	p->Pos[dir_pos][Y] = -1;
	p->Pos[dir][X] = -1;
	p->Pos[dir][Y] = -1;
	p->Pos[dir_neg][X] = -1;
	p->Pos[dir_neg][Y] = -1;

	
	// create player image
	p->img = ft_img_create_color_img(app->com, 0x00FF0000, IMG_SZ_X_PLAYER, IMG_SZ_Y_PLAYER);
	p->black_img = ft_img_create_color_img(app->com, 0x00000000, IMG_SZ_X_PLAYER, IMG_SZ_Y_PLAYER);

	if (m->player_orientation == NORTH)
	{
		p->heading_angle = PI * 0.5; //old angle
		p->dir[X] = 0;
		p->dir[Y] = -1;
		p->plane[X] = 0.66;
		p->plane[Y] = 0;
	}
	else if(m->player_orientation == WEST)
	{
		p->heading_angle = PI; //old angle
		p->dir[X] = -1;
		p->dir[Y] = 0;
		p->plane[X] = 0;
		p->plane[Y] = -0.66;
	}
	else if(m->player_orientation == SOUTH)
	{
		p->heading_angle = PI * 1.5; //old angle
		p->dir[X] = 0;
		p->dir[Y] = 1;
		p->plane[X] = -0.66;
		p->plane[Y] = 0;
	}
	else if(m->player_orientation == EAST)
	{
		p->heading_angle = 0; //old angle
		p->dir[X] = 1;
		p->dir[Y] = 0;
		p->plane[X] = 0;
		p->plane[Y] = 0.66;
	}

}
