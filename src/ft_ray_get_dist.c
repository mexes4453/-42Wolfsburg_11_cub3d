/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_get_dist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:10:07 by fsemke            #+#    #+#             */
/*   Updated: 2023/04/06 17:09:32 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_calc_more_stuff(t_player *p, double (*c)[2][2], int (*step)[2])
{
	(*c)[delta][X] = fabs(1 / p->raydir[X]);
	(*c)[delta][Y] = fabs(1 / p->raydir[Y]);
	if (p->raydir[X] < 0)
	{
		(*step)[X] = -1;
		(*c)[s][X] = (p->pos[X] - p->map_pos[X]) * (*c)[delta][X];
	}
	else
	{
		(*step)[X] = 1;
		(*c)[s][X] = (p->map_pos[X] + 1.0 - p->pos[X]) * \
		(*c)[delta][X];
	}
	if (p->raydir[Y] < 0)
	{
		(*step)[Y] = -1;
		(*c)[s][Y] = ((p->pos[Y] - p->map_pos[Y]) * (*c)[delta][Y]);
	}
	else
	{
		(*step)[Y] = 1;
		(*c)[s][Y] = (p->map_pos[Y] + 1.0 - p->pos[Y]) * \
		(*c)[delta][Y];
	}
}

/*
 * This function computes the perpendicular distance of each ray endpoint
 * (vertical or horizontal wall) to the players view plane.
 * This operation is performed considering the orientation of the wall hit
 * by the ray
 * 		(line->side = 0 : West or East).
 * 		(line->side = 1 : North or South)
 *
 * it also checks if a ray hits a wall facing north or south
 * 		a->player->raydir[Y] < 0) 
 *
 * it also checks if a ray hits a wall facing east or west
 * 		a->player->raydir[X] < 0) 
 */
static void	ft_calc_perp_dist(t_app *a, t_cmp_lines *line, int (*step)[2])
{
	if (line->side == 0)
	{
		line->perp_w_dist = (a->player->map_pos[X] - \
		a->player->pos[X] + (1 - (*step)[X]) / 2) / a->player->raydir[X];
		line->wall_x = a->player->pos[Y] + \
			line->perp_w_dist * a->player->raydir[Y];
		line->wall_x -= floor(line->wall_x);
		if (a->player->raydir[X] < 0)
			line->pole = WEST;
		else
			line->pole = EAST;
	}
	else
	{
		line->perp_w_dist = (a->player->map_pos[Y] - \
		a->player->pos[Y] + (1 - (*step)[Y]) / 2) / a->player->raydir[Y];
		line->wall_x = a->player->pos[X] + \
			line->perp_w_dist * a->player->raydir[X];
		line->wall_x -= floor(line->wall_x);
		if (a->player->raydir[Y] < 0)
			line->pole = NORTH;
		else
			line->pole = SOUTH;
	}
}

/*
 * This function computes the x position where the texture placement should
 * start
 */
static void	ft_get_texture_xpos(t_app *a, t_cmp_lines *line)
{
	line->text_x = (int)(line->wall_x * (double)IMG_SZ_X_WALL);
	if ((line->side == 0 && a->player->raydir[X] > 0) || \
		(line->side == 1 && a->player->raydir[Y] < 0))
	{
		line->text_x = IMG_SZ_X_WALL - line->text_x - 1;
	}
	line->coord_hit[X] = (a->player->pos[X] + \
							(a->player->raydir[X] * line->perp_w_dist)) * \
						IMG_SZ_X_WALL;
	line->coord_hit[Y] = (a->player->pos[Y] + \
							(a->player->raydir[Y] * line->perp_w_dist)) * \
						IMG_SZ_Y_WALL;
}

/*
 * This function computes the ray distance to the players's plane
 * using the DDA algorithm
 */
void	ft_ray_get_dist(t_app *a, t_cmp_lines *line)
{
	double	c[2][2];
	int		step[2];
	int		hit;

	hit = 0;
	ft_calc_more_stuff(a->player, &c, &step);
	while (hit == 0)
	{
		if (c[s][X] < c[s][Y])
		{
			c[s][X] += c[delta][X];
			a->player->map_pos[X] += step[X];
			line->side = 0;
		}
		else
		{
			c[s][Y] += c[delta][Y];
			a->player->map_pos[Y] += step[Y];
			line->side = 1;
		}
		if (a->map->map[a->player->map_pos[Y]][a->player->map_pos[X]] == '1')
			hit = 1;
	}
	ft_calc_perp_dist(a, line, &step);
	ft_get_texture_xpos(a, line);
}
