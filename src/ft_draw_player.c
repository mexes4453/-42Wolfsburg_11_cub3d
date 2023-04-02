/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 08:40:49 by cudoh             #+#    #+#             */
/*   Updated: 2023/04/02 10:53:08 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void ft_draw_player(t_app *a)
{
    
    mlx_put_image_to_window(a->com, a->win, a->player->black_img->img_ref_ptr, a->player->Pos[origin][X], a->player->Pos[origin][Y]); //black
    mlx_put_image_to_window(a->com, a->win, a->player->img->img_ref_ptr, a->player->Pos[origin][X], a->player->Pos[origin][Y]);
    
    // draw headline
    a->player->headline->startPosX = a->player->Pos[origin][X];
    a->player->headline->startPosY = a->player->Pos[origin][Y];
    a->player->headline->endPosX = a->player->Pos[origin][X] + (a->player->delta_x * 5); //PX_MOVE);
    a->player->headline->endPosY = a->player->Pos[origin][Y] + (a->player->delta_y * 5); //PX_MOVE);
    ft_draw_line(a->com, a->win, a->player->headline);
}