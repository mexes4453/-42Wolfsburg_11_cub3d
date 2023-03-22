/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_onKeyPress_A.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:07:06 by fsemke            #+#    #+#             */
/*   Updated: 2023/03/22 22:09:37 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_onKeyPress_A(t_app *a)
{
	a->map->idx_x = (int)((a->player->Pos[origin][X] + cos(a->player->heading_angle + (PI / 2))) / IMG_SZ_X_WALL);
	a->map->idx_y = (int)((a->player->Pos[origin][Y] - sin(a->player->heading_angle + (PI / 2))) / IMG_SZ_Y_WALL);

	if (a->map->map[(int)(a->player->Pos[origin][Y] / IMG_SZ_Y_WALL)][a->map->idx_x] != '1')
		a->player->Pos[origin][X] += cos(a->player->heading_angle + (PI / 2)) * MOVE_SPEED;
	if (a->map->map[a->map->idx_y][(int)(a->player->Pos[origin][X] / IMG_SZ_X_WALL)] != '1')
		a->player->Pos[origin][Y] -= sin(a->player->heading_angle + (PI / 2)) * MOVE_SPEED;
}
