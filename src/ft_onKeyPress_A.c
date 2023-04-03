/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_onKeyPress_A.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:07:06 by fsemke            #+#    #+#             */
/*   Updated: 2023/04/03 13:13:28 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_onKeyPress_A(t_app *a)
{
	int	idx_x;
	int	idx_y;

	idx_x = (int)(a->player->Pos[origin][X] + a->player->vec_dir[Y] * MOVE_SPEED);
	idx_y = (int)(a->player->Pos[origin][Y] - a->player->vec_dir[X] * MOVE_SPEED);
	if (a->map->map[(int)a->player->Pos[origin][Y]][idx_x] != '1')
		a->player->Pos[origin][X] += a->player->vec_dir[Y] * MOVE_SPEED;
	if (a->map->map[idx_y][(int)a->player->Pos[origin][X]] != '1')
		a->player->Pos[origin][Y] -= a->player->vec_dir[X] * MOVE_SPEED;
    a->print_flag = 1;
}
