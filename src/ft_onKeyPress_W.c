/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_onKeyPress_W.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:11:01 by fsemke            #+#    #+#             */
/*   Updated: 2023/03/28 19:44:31 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */





#include "../cub3d.h"

void ft_onKeyPress_W(t_app *a)
{
    a->map->idx_x = (int)((a->player->Pos[origin][X] + a->player->delta_x) / IMG_SZ_X_WALL);
    a->map->idx_y = (int)((a->player->Pos[origin][Y] - a->player->delta_y) / IMG_SZ_Y_WALL);

    if (a->map->map[(int)(a->player->Pos[origin][Y] / IMG_SZ_Y_WALL)][a->map->idx_x] != '1')
        a->player->Pos[origin][X] += a->player->delta_x * MOVE_SPEED;
    if (a->map->map[a->map->idx_y][(int)(a->player->Pos[origin][X] / IMG_SZ_X_WALL)] != '1')
        a->player->Pos[origin][Y] -= a->player->delta_y * MOVE_SPEED;
    a->print_flag = 1;
}
