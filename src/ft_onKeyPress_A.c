/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_onKeyPress_A.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:07:06 by fsemke            #+#    #+#             */
/*   Updated: 2023/04/05 13:00:03 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_onKeyPress_A(t_app *a)
{
	int	idx_x;
	int	idx_y;

	idx_x = (int)(a->player->Pos[origin][X] + a->player->dir[Y] * MS);
	idx_y = (int)(a->player->Pos[origin][Y] - a->player->dir[X] * MS);
	if (a->map->map[(int)a->player->Pos[origin][Y]][idx_x] != '1')
		a->player->Pos[origin][X] += a->player->dir[Y] * MS;
	if (a->map->map[idx_y][(int)a->player->Pos[origin][X]] != '1')
		a->player->Pos[origin][Y] -= a->player->dir[X] * MS;
}
