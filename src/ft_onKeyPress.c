/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_onKeyPress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:07:06 by fsemke            #+#    #+#             */
/*   Updated: 2023/04/05 23:45:06 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_on_key_press_a(t_app *a)
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

void	ft_on_key_press_d(t_app *a)
{
	int	idx_x;
	int	idx_y;

	idx_x = (int)(a->player->Pos[origin][X] - a->player->dir[Y] * MS);
	idx_y = (int)(a->player->Pos[origin][Y] + a->player->dir[X] * MS);
	if (a->map->map[(int)a->player->Pos[origin][Y]][idx_x] != '1')
		a->player->Pos[origin][X] -= a->player->dir[Y] * MS;
	if (a->map->map[idx_y][(int)a->player->Pos[origin][X]] != '1')
		a->player->Pos[origin][Y] += a->player->dir[X] * MS;
}

void	ft_on_key_press_s(t_app *a)
{
	int	idx_x;
	int	idx_y;

	idx_x = (int)(a->player->Pos[origin][X] - a->player->dir[X] * MS);
	idx_y = (int)(a->player->Pos[origin][Y] - a->player->dir[Y] * MS);
	if (a->map->map[(int)a->player->Pos[origin][Y]][idx_x] != '1')
		a->player->Pos[origin][X] -= a->player->dir[X] * MS;
	if (a->map->map[idx_y][(int)a->player->Pos[origin][X]] != '1')
		a->player->Pos[origin][Y] -= a->player->dir[Y] * MS;
}

void	ft_on_key_press_w(t_app *a)
{
	int	idx_x;
	int	idx_y;

	idx_x = (int)(a->player->Pos[origin][X] + a->player->dir[X] * MS);
	idx_y = (int)(a->player->Pos[origin][Y] + a->player->dir[Y] * MS);
	if (a->map->map[(int)(a->player->Pos[origin][Y])][idx_x] != '1')
		a->player->Pos[origin][X] += a->player->dir[X] * MS;
	if (a->map->map[idx_y][(int)(a->player->Pos[origin][X])] != '1')
		a->player->Pos[origin][Y] += a->player->dir[Y] * MS;
}
