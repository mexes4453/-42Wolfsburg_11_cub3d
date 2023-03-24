/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 17:27:18 by cudoh             #+#    #+#             */
/*   Updated: 2023/03/23 15:10:53 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void ft_player_init(t_player *p, t_map *m, t_app *app)
{
    ft_memset((void *)p, 0, sizeof(t_player));
    p->Pos[origin][X] = (m->player_x * IMG_SZ_X_WALL) + (IMG_SZ_X_WALL / 2);
    p->Pos[origin][Y] = (m->player_y * IMG_SZ_Y_WALL) + (IMG_SZ_Y_WALL / 2);
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
        p->heading_angle = PI * 0.5;
    else if(m->player_orientation == WEST)
        p->heading_angle = PI;
    else if(m->player_orientation == SOUTH)
        p->heading_angle = PI * 1.5;
    else if(m->player_orientation == EAST)
        p->heading_angle = 0;

    p->delta_x = cos(p->heading_angle);
    p->delta_y = sin(p->heading_angle);
    /*
    ft_memset((void *)&(p->img), 0, sizeof(t_img));
    p->img->addr = NULL;
    p->img->img_ref_ptr = NULL;
    p->img->sz_x = IMG_SZ_X_PLAYER;
    p->img->sz_y = IMG_SZ_Y_PLAYER;
    */
}
