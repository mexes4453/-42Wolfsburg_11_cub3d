/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:39:20 by cudoh             #+#    #+#             */
/*   Updated: 2023/04/03 12:54:46 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void ft_draw_rays(t_app *a)
{
#if 1
    a->ray->rlen_max = a->map->map_size_y;
    a->ray->ra = a->player->heading_angle;
    a->ray->r = 0;
    while(a->ray->r < 1)
    {
        // check for horizontal number
        a->ray->dof = 0;
        a->ray->aTan = -1/tan(a->ray->ra);
        printf("tan %f; atan %f\n", tan(a->ray->ra), a->ray->aTan);
        if (a->ray->ra < PI )           // it means player is looking upward
        {
           a->ray->ry = (int)((a->player->Pos[origin][Y] / IMG_SZ_Y_WALL) * IMG_SZ_Y_WALL);
           a->ray->rx = ((a->player->Pos[origin][Y] - a->ray->ry) * a->ray->aTan) + a->player->Pos[origin][X];
           printf("px: %f; py: %f\n", a->player->Pos[origin][X], a->player->Pos[origin][Y]);
           printf("rx: %f; ry: %f; ra: %f\n", a->ray->rx, a->ray->ry, a->ray->ra);
           a->ray->yo = IMG_SZ_Y_WALL;
           a->ray->xo = -(a->ray->yo) * a->ray->aTan;
           printf("xo: %f; yo: %f\n", a->ray->xo, a->ray->yo);
        }
        
        else if (a->ray->ra > PI) // it means player is looking downward
        {
            a->ray->ry = ((int)(a->player->Pos[origin][Y] / IMG_SZ_Y_WALL) * IMG_SZ_Y_WALL) + IMG_SZ_Y_WALL;
            a->ray->rx = ((a->player->Pos[origin][Y] - a->ray->ry) * a->ray->aTan) + a->player->Pos[origin][X];
            //printf("rx: %f\n", a->ray->rx);
            a->ray->yo = IMG_SZ_Y_WALL;
            a->ray->xo = -(a->ray->yo) * a->ray->aTan;
        }
        #if 0
        else if (a->ray->ra == 0 || a->ray->ra == PI) // player is looking horizontal left or right
        {
            a->ray->rx = a->player->Pos[origin][X];
            a->ray->ry = a->player->Pos[origin][Y];
            a->ray->dof = a->ray->rlen_max;
            return;
        }
        #endif
        // check map to see if we hit a wall
        a->ray->mx = 0;
        a->ray->my = 0;
        //while (a->ray->mx < a->map->map_size_x && a->ray->mx > 0 && 
        //       a->ray->my < a->map->map_size_y && a->ray->my > 0)
        while (a->ray->dof < a->ray->rlen_max)
        {
            a->ray->mx = abs((int)a->ray->rx / IMG_SZ_X_WALL);
            a->ray->my = abs((int)a->ray->ry / IMG_SZ_Y_WALL);
            printf("mx: %d; my: %d; mapx: %d, mapy: %d", a->ray->mx, a->ray->my, a->map->map_size_x, a->map->map_size_y);

            if (a->ray->mx < a->map->map_size_x && a->ray->my < a->map->map_size_y && 
                a->map->map[a->ray->my][a->ray->mx] == '1')
            {
                a->ray->dof = a->ray->rlen_max;
                break ;
            }
            else
            {
               a->ray->rx += a->ray->xo;
               a->ray->ry += a->ray->yo;
               (a->ray->dof)++;
               printf("\ndof: %d; ", a->ray->dof);
            }
        }
        (a->ray->r)++;  // increment ray count
    }
    a->ray->rayline->color = 0x000000FF; // color or rayline;
    a->ray->rayline->startPosX = a->player->Pos[origin][X];
    a->ray->rayline->startPosY = a->player->Pos[origin][Y];
    a->ray->rayline->endPosX = a->ray->rx;
    a->ray->rayline->endPosY = a->ray->ry;
    ft_draw_line(a->com, a->win, a->ray->rayline);
    
    
#endif 
}