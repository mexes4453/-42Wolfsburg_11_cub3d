/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_get_dist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh<ccudohtudent.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:10:07 by fsemke            #+#    #+#             */
/*   Updated: 2023/04/01 20:29:15 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* static void	ft_calc_point(t_app *a, double (*c)[2][2], t_cmp_lines *line,
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
} */

void	ft_ray_get_dist(t_app *a, t_cmp_lines *line)
{
	double	c[2][2];
	int		step[2];

	c[delta][X] = fabs(1 / a->player->vec_rayDir[X]);
	c[delta][Y] = fabs(1 / a->player->vec_rayDir[Y]);
	
	if (a->player->vec_rayDir[X] < 0) //x
	{
		step[X] = -1;
		c[s][X] = (a->player->Pos[origin][X] - a->player->map_pos[X]) * c[delta][X];
	}
	else
	{
		step[X] = 1;
		c[s][X] = (a->player->map_pos[X] + 1.0 - a->player->Pos[origin][X]) * c[delta][X];
	}
	if (a->player->vec_rayDir[Y] < 0)
	{
		step[Y] = -1;
		c[s][Y] = ((a->player->Pos[origin][Y] - a->player->map_pos[Y]) * c[delta][Y]);
	}
	else //x
	{
		step[Y] = 1;
		c[s][Y] = (a->player->map_pos[Y] + 1.0 - a->player->Pos[origin][Y]) * c[delta][Y];
	}
	
	//perform DDA Algo
	int hit;
	hit = 0;
/* 	check[X] = (int)(p->Pos[origin][X]);
	check[Y] = (int)(p->Pos[origin][Y] / IMG_SZ_X_WALL); */
	while (hit == 0)
	{
		if(c[s][X] < c[s][Y])
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
	if (line->side == 0)
	{
		line->perpWallDist = (a->player->map_pos[X] - a->player->Pos[origin][X] + (1 - step[X]) / 2) / a->player->vec_rayDir[X];
		line->wall_x = a->player->Pos[origin][Y] + line->perpWallDist * a->player->vec_rayDir[Y];
		line->wall_x -= floor(line->wall_x);
	}
	else
	{
		line->perpWallDist = (a->player->map_pos[Y] - a->player->Pos[origin][Y] + (1 - step[Y]) / 2) / a->player->vec_rayDir[Y];
		line->wall_x = a->player->Pos[origin][X] + line->perpWallDist * a->player->vec_rayDir[X];
		line->wall_x -= floor(line->wall_x);
	}
	

	line->text_x = (int)(line->wall_x * (double)IMG_SZ_X_WALL);
	if ((line->side == 0 && a->player->vec_rayDir[X] > 0)
		|| (line->side == 1 && a->player->vec_rayDir[Y] < 0))
			line->text_x = IMG_SZ_X_WALL - line->text_x - 1;
	//Map raylines
	line->coord_hit[X] = (a->player->Pos[origin][X] + (a->player->vec_rayDir[X] * line->perpWallDist)) * IMG_SZ_X_WALL;
	line->coord_hit[Y] = (a->player->Pos[origin][Y] + (a->player->vec_rayDir[Y] * line->perpWallDist)) * IMG_SZ_Y_WALL;
	
	//line->raylength = hypot(c[s][X], c[s][Y]);

/* 	angle = p->heading_angle + offset;
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
		line->perpWallDist = line->raylength * cos(offset);

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
		line->perpWallDist = line->raylength * cos(offset);
	} */
}

/* void	ft_ray_get_dist_vert(t_app *a, t_player *p, double off, t_cmp_lines *l)
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
		l->perpWallDist = l->raylength * cos(off);
		
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
			l->perpWallDist = l->raylength * cos(off);
			//l->perpWallDist = l->raylength;
			
		}
	} */
