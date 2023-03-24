/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_get_dist_horz.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:10:07 by fsemke            #+#    #+#             */
/*   Updated: 2023/03/23 22:58:09 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"




void ft_ray_get_dist_horz(t_app *a, t_player *p, double o)
{
    t_ray ray;
    t_line line = {0};


    ray.dx = 0;
    ray.dir_x = cos((p->heading_angle / 2) + o);
/* 	if (a->print_flag)
	{
		printf("heading angle %f\n", p->heading_angle * 180 / PI);
		a->print_flag = 0;
	} */
    if (ray.dir_x > 0 && (p->heading_angle <= PI/2 && p->heading_angle > 0 )) // ray first quadrant
    {
            
        ray.dx = IMG_SZ_X_WALL - ((int)p->Pos[origin][X] % IMG_SZ_X_WALL);
        //printf ("distance dx: horizontal to wall axis on right: %f \n", dx);
        //printf ("distance x: horizontal to wall axis on right: %f \n", x);

        //dir = y/dx; // not required only to subdue compiler complaint
        // compute hypothenus side_y_distance;
        ray.hyp_y = ray.dx / ray.dir_x;
        ray.dy = ray.hyp_y * sin(p->heading_angle - o);
        
        line.startPosX = (int)p->Pos[origin][X];
        line.startPosY = (int)p->Pos[origin][Y];

        line.endPosX = (int)p->Pos[origin][X] + ray.dx;
        line.endPosY = (int)p->Pos[origin][Y] - ray.dy;
        line.color = 0x0000FF00;            // green color

        ray.idx_x = line.endPosX / IMG_SZ_X_WALL;
        ray.idx_y = line.endPosY / IMG_SZ_Y_WALL;
        ft_draw_line(a->com, a->win, &line);
/*

        if (a->map->map[ray.idx_y][ray.idx_x] == '1')
        {
            ft_draw_line(a->com, a->win, &line);
        }
        else
        {
            ray.dx = IMG_SZ_X_WALL - (line.endPosX % IMG_SZ_X_WALL);
            ray.hyp_y = ray.dx / ray.dir_x;
            ray.dy = ray.hyp_y * sin(p->heading_angle - o);
        }
        }*/

      
    }
}

double ft_ray_get_dist_vert(double x, double y, double h, double o)
{
    double dy;
    double dir;

    dy = 0;
    dir = sin(h - o);
    if (dir > 0 && (h <= PI/2 && h > 0 )) // ray in first quadrant
    {
        dy = ((int)y % IMG_SZ_X_WALL);
        printf ("distance dy: horizontal to wall axis on right: %f \n", dy);
        printf ("distance y: horizontal to wall axis on right: %f \n", y);

        dir = x/dy;  // not required only to subdue compiler complaint
        
    }
    return (dy);
}