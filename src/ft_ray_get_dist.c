/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_get_dist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:10:07 by fsemke            #+#    #+#             */
/*   Updated: 2023/03/31 10:53:43 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_calc_point(t_app *a, double (*c)[2][2], t_cmp_lines *line,
	int (*check)[3])
{
	while ((*check)[X] >= 0 && (*check)[X] < a->map->map_size_x
		&& (*check)[Y] >= 0 && (*check)[Y] < a->map->map_size_y
		&& a->map->map[(*check)[Y]][(*check)[X]] != '1')
	{
		(*c)[s][Y] += (*c)[delta][Y];
		(*c)[s][X] += (*c)[delta][X];
		if ((*check)[VERSION] == 1)
			(*check)[Y] = (int)(((a->player->Pos[origin][Y] + (*c)[s][Y]) / IMG_SZ_Y_WALL) - 1);
		else
			(*check)[Y] = (int)((a->player->Pos[origin][Y] + (*c)[s][Y]) / IMG_SZ_Y_WALL);
		if ((*check)[VERSION] == 2)
			(*check)[X] = (int)(((a->player->Pos[origin][X] + (*c)[s][X]) / IMG_SZ_X_WALL) - 1);
		else
			(*check)[X] = (int)((a->player->Pos[origin][X] + (*c)[s][X]) / IMG_SZ_X_WALL);
	}
	line->wall_x = (int)a->player->Pos[origin][X] + (*c)[s][X];
	line->wall_y = (int)a->player->Pos[origin][Y] + (*c)[s][Y];
	line->raylength = hypot((*c)[s][X], (*c)[s][Y]);
}

void	ft_ray_get_dist_horz(t_app *a, t_player *p, double offset, t_cmp_lines *line)
{
	double	c[2][2];
	double	angle;
	int		check[3];

	angle = p->heading_angle + offset;
	if ((angle <= PI && angle > 0) || (angle >= 2 * PI && angle <= 3 * PI)) // ray in above quadrant
	{
		line->orientation = NORTH;
		c[s][Y] = -fmod(p->Pos[origin][Y], IMG_SZ_Y_WALL);
		c[s][X] = -c[s][Y] / tan(angle);
		c[delta][Y] = -IMG_SZ_Y_WALL;
		c[delta][X] = -c[delta][Y] / tan(angle);
		check[X] = (int)((p->Pos[origin][X] + c[s][X]) / IMG_SZ_X_WALL);
		check[Y] = (int)(((p->Pos[origin][Y] + c[s][Y]) / IMG_SZ_Y_WALL) - 1);
		check[VERSION] = 1;
		ft_calc_point(a, &c, line, &check);
	}
	else //angle is looking down
	{
		line->orientation = SOUTH;
		angle -= PI;
		c[s][Y] = IMG_SZ_Y_WALL - fmod(p->Pos[origin][Y], IMG_SZ_Y_WALL);
		c[s][X] = -c[s][Y] / tan(angle);
		c[delta][Y] = IMG_SZ_Y_WALL;
		c[delta][X] = -c[delta][Y] / tan(angle);
		check[X] = (int)((p->Pos[origin][X] + c[s][X]) / IMG_SZ_X_WALL);
		check[Y] = (int)((p->Pos[origin][Y] + c[s][Y]) / IMG_SZ_Y_WALL);
		check[VERSION] = 0;
		ft_calc_point(a, &c, line, &check);
	}
}

void	ft_ray_get_dist_vert(t_app *a, t_player *p, double off, t_cmp_lines *l)
{
	double	c[2][2];
	double	angle;
	int		check[3];

	angle = p->heading_angle + off;
	if (angle <= (3 * PI) / 2 && angle > PI / 2) // ray to the Left
	{
		l->orientation = WEST;
		c[s][X] = -fmod(p->Pos[origin][X], IMG_SZ_X_WALL);
		c[s][Y] = c[s][X] * tan(PI - angle);
		c[delta][X] = -IMG_SZ_X_WALL;
		c[delta][Y] = c[delta][X] * tan(PI - angle);
		check[X] = (int)(((p->Pos[origin][X] + c[s][X]) / IMG_SZ_X_WALL) - 1);
		check[Y] = (int)((p->Pos[origin][Y] + c[s][Y]) / IMG_SZ_Y_WALL);
		check[VERSION] = 2;
		ft_calc_point(a, &c, l, &check);
	}
	else //ray to the right
	{
		l->orientation = EAST;
		c[s][X] = IMG_SZ_X_WALL - fmod(p->Pos[origin][X], IMG_SZ_X_WALL);
		c[s][Y] = -c[s][X] * tan(angle);
		c[delta][X] = IMG_SZ_X_WALL;
		c[delta][Y] = -c[delta][X] * tan(angle);
		check[X] = (int)((p->Pos[origin][X] + c[s][X]) / IMG_SZ_X_WALL);
		check[Y] = (int)((p->Pos[origin][Y] + c[s][Y]) / IMG_SZ_Y_WALL);
		check[VERSION] = 0;
		ft_calc_point(a, &c, l, &check);
	}
}
