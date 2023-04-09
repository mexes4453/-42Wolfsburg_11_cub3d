/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 17:27:18 by cudoh             #+#    #+#             */
/*   Updated: 2023/04/02 22:49:05 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void ft_player_init(t_player *p, t_map *m, t_app *app)
{
    //t_line img_line;
    //t_pos idx;
    
    //idx = dir_pos;
    
    ft_memset((void *)p, 0, sizeof(t_player));
    p->Pos[origin][X] = (m->player_x * IMG_SZ_X_WALL) + (IMG_SZ_X_WALL / 2);
    p->Pos[origin][Y] = (m->player_y * IMG_SZ_Y_WALL) + (IMG_SZ_Y_WALL / 2);
    p->Pos[dir_pos][X] = -1;
    p->Pos[dir_pos][Y] = -1;
    p->Pos[dir][X] = -1;
    p->Pos[dir][Y] = -1;
    p->Pos[dir_neg][X] = -1;
    p->Pos[dir_neg][Y] = -1;
    p->Pos[next][X] = p->Pos[origin][X];
    p->Pos[next][Y] = p->Pos[origin][Y];
    // get the cordinate of other point with reference to the origin cordinate (player)
    // direction vector
/*     p->Pos[dir][X] = p->Pos[origin][X];
    p->Pos[dir][Y] = p->Pos[origin][Y] - DIR_LENGTH; */

    // direct plane negative vector
/*     p->Pos[dir_neg][X] = p->Pos[origin][X] + ((cos(((FOV / 2) + 90) * PI / 180.0)) * DIR_LENGTH);
    p->Pos[dir_neg][Y] = p->Pos[dir][Y]; */

    // direct plane positive vector
/*     p->Pos[dir_pos][X] = p->Pos[origin][X] + cos((90 - (FOV / 2)) * PI / 180.0) * DIR_LENGTH;
    p->Pos[dir_pos][Y] = p->Pos[dir][Y]; */
    
    // create player image
	p->img = ft_img_create_color_img(app->com, COL_PLAYER, IMG_SZ_X_PLAYER, IMG_SZ_Y_PLAYER);
    p->black_img = ft_img_create_color_img(app->com, COL_BLACK, IMG_SZ_X_PLAYER, IMG_SZ_Y_PLAYER);

    // draw lines
/*     img_line.startPosX = p->Pos[origin][X];
    img_line.startPosY = p->Pos[origin][Y];
    while (idx < MaxPos)
    {
        img_line.endPosX = p->Pos[idx][X];
        img_line.endPosY = p->Pos[idx][Y];
        ft_draw_line(app->com, app->win, &img_line);
        idx++;
    } */
 

    
    
    
    if (m->player_orientation == NORTH)
        p->heading_angle = PI * 1.5;
    else if(m->player_orientation == WEST)
        p->heading_angle = PI;
    else if(m->player_orientation == SOUTH)
        p->heading_angle = PI * 0.5;
    else if(m->player_orientation == EAST)
        p->heading_angle = 0;

    //p->img = NULL; why?
    p->delta_x = cos(p->heading_angle) * PX_MOVE;
    p->delta_y = sin(p->heading_angle) * PX_MOVE;
    /*
    ft_memset((void *)&(p->img), 0, sizeof(t_img));
    p->img->addr = NULL;
    p->img->img_ref_ptr = NULL;
    p->img->sz_x = IMG_SZ_X_PLAYER;
    p->img->sz_y = IMG_SZ_Y_PLAYER;
    */
}

int    ft_key_pressed(int key, t_app *a)
{
    if (key == KEY_ESC)
        ft_app_close(a);
    else if (key == KEY_W)
    {
        a->player->Pos[next][X] = a->player->Pos[origin][X] + a->player->delta_x;
        a->player->Pos[next][Y] = a->player->Pos[origin][Y] + a->player->delta_y;
    }
        //a->player->key_w = 1;
    else if (key == KEY_A)
    {
        a->player->Pos[next][X] = a->player->Pos[origin][X] + (cos(a->player->heading_angle - (PI/2)) * PX_MOVE);
        a->player->Pos[next][Y] = a->player->Pos[origin][Y] + (sin(a->player->heading_angle - (PI/2)) * PX_MOVE);
    }
        //a->player->key_a = 1;
    else if (key == KEY_S)
    {
        a->player->Pos[next][X] = a->player->Pos[origin][X] - a->player->delta_x;
        a->player->Pos[next][Y] = a->player->Pos[origin][Y] - a->player->delta_y;
    }
    //    a->player->key_s = 1;
    else if (key == KEY_D)
    {
        a->player->Pos[next][X] = a->player->Pos[origin][X] + (cos(a->player->heading_angle + (PI/2)) * PX_MOVE);
        a->player->Pos[next][Y] = a->player->Pos[origin][Y] + (sin(a->player->heading_angle + (PI/2)) * PX_MOVE);
    }
    //   a->player->key_d = 1;
    else if (key == KEY_LEFT)
    {
        a->player->heading_angle -= ROTATE_ANGLE_OFFSET;
        if (a->player->heading_angle < 0)
        {
            a->player->heading_angle += (2 * PI);
        }
        a->player->delta_x = cos(a->player->heading_angle) * PX_MOVE;
        a->player->delta_y = sin(a->player->heading_angle) * PX_MOVE;
    
    }
    // a->player->key_left = 1;
    
    else if (key == KEY_RIGHT)
    {
        a->player->heading_angle += ROTATE_ANGLE_OFFSET;
        if (a->player->heading_angle > (2 * PI))
        {
            a->player->heading_angle -= (2 * PI);
        }
        a->player->delta_x = cos(a->player->heading_angle) * PX_MOVE;
        a->player->delta_y = sin(a->player->heading_angle) * PX_MOVE;

    }
    //a->player->key_right = 1;
    else
    {
        printf("New Button %d pressed\n", key);
        printf("heading: %f\n", a->player->heading_angle);
        printf("posx: %f, posy: %f\n", a->player->Pos[origin][X], a->player->Pos[origin][Y]);

        printf("my: %d\n", a->ray->my);
        printf("mx: %d\n", a->ray->mx);
        printf("dof: %d\n", a->ray->dof);
        printf("rx: %f, ry: %f\n", a->ray->rx, a->ray->ry);
    }
    return (0);
}

#if 0
int    ft_key_released(int key, t_player *p)
{
    if (key == KEY_W)
        p->key_w = 0;
    else if (key == KEY_A)
        p->key_a = 0;
    else if (key == KEY_S)
        p->key_s = 0;
    else if (key == KEY_D)
        p->key_d = 0;
    else if (key == KEY_LEFT)
        p->key_left = 0;
    else if (key == KEY_RIGHT)
        p->key_right = 0;
    return (0);
}

#endif


int ft_player_move(t_app *a)
{
    
    mlx_put_image_to_window(a->com, a->win, a->player->black_img->img_ref_ptr,
                                a->player->Pos[origin][X],
                                a->player->Pos[origin][Y]); //print black img

    a->player->headline->color = COL_BLACK;
    ft_draw_line(a->com, a->win, a->player->headline);

    // print player image on new position
    mlx_put_image_to_window(a->com, a->win, a->player->img->img_ref_ptr,
                                a->player->Pos[next][X],
                                a->player->Pos[next][Y]); 
    
    // update the player origin with next pos value
    a->player->Pos[origin][X] = a->player->Pos[next][X];
    a->player->Pos[origin][Y] = a->player->Pos[next][Y];
    
    a->player->headline->color = COL_PLAYER;
    // draw headline
    a->player->headline->startPosX = a->player->Pos[origin][X];
    a->player->headline->startPosY = a->player->Pos[origin][Y];
    a->player->headline->endPosX = a->player->Pos[origin][X] + (a->player->delta_x * 5); //PX_MOVE);
    a->player->headline->endPosY = a->player->Pos[origin][Y] + (a->player->delta_y * 5); //PX_MOVE);
    ft_draw_line(a->com, a->win, a->player->headline);

    
#if 0
    (void)key;
    int old[MaxPos][2];
    
    old[origin][X] = a->player->Pos[origin][X];
    old[origin][Y] = a->player->Pos[origin][Y];
    old[dir][X] = a->player->Pos[dir][X];
    old[dir][Y] = a->player->Pos[dir][Y];
    old[dir_neg][X] = a->player->Pos[dir_neg][X];
    old[dir_neg][Y] = a->player->Pos[dir_neg][Y];
    old[dir_pos][X] = a->player->Pos[dir_pos][X];
    old[dir_pos][Y] = a->player->Pos[dir_pos][Y];
    
    if (a->player->key_w)
    {
        a->player->Pos[origin][X] += a->player->delta_x * MOVE_SPEED;
        a->player->Pos[origin][Y] -= a->player->delta_y * MOVE_SPEED;
    }
    if (a->player->key_a)
    {
        a->player->Pos[origin][X] += cos(a->player->heading_angle + (PI / 2)) * MOVE_SPEED;
        a->player->Pos[origin][Y] -= sin(a->player->heading_angle + (PI / 2)) * MOVE_SPEED;
    }
    if (a->player->key_s)
    {
        a->player->Pos[origin][X] -= a->player->delta_x * MOVE_SPEED;
        a->player->Pos[origin][Y] += a->player->delta_y * MOVE_SPEED;
    }
    if (a->player->key_d)
    {
        a->player->Pos[origin][X] -= cos(a->player->heading_angle + (PI / 2)) * MOVE_SPEED;
        a->player->Pos[origin][Y] += sin(a->player->heading_angle + (PI / 2)) * MOVE_SPEED;
    }
    
    
    //calculating new coordinates
    a->player->Pos[dir][X] = a->player->Pos[origin][X] + (a->player->delta_x * DIR_LENGTH);
    a->player->Pos[dir][Y] = a->player->Pos[origin][Y] - (a->player->delta_y * DIR_LENGTH);
    a->player->Pos[dir_neg][X] = a->player->Pos[origin][X] + (cos(a->player->heading_angle + ((FOV / 2) * PI / 180.0)) * DIR_LENGTH);
    a->player->Pos[dir_neg][Y] = a->player->Pos[origin][Y] - (sin(a->player->heading_angle + ((FOV / 2) * PI / 180.0)) * DIR_LENGTH);
    a->player->Pos[dir_pos][X] = a->player->Pos[origin][X] + (cos(a->player->heading_angle - ((FOV / 2) * PI / 180.0)) * DIR_LENGTH);
    a->player->Pos[dir_pos][Y] = a->player->Pos[origin][Y] - (sin(a->player->heading_angle - ((FOV / 2) * PI / 180.0)) * DIR_LENGTH);
    
    //remove old line
    t_line  img_line;
    t_pos   idx;
    img_line.color = 0x00000000;
    idx = dir_pos;
    img_line.startPosX = old[origin][X];
    img_line.startPosY = old[origin][Y];
    while (idx < MaxPos)
    {
        img_line.endPosX = old[idx][X];
        img_line.endPosY = old[idx][Y];
        if (img_line.endPosX != -1 && img_line.endPosY != -1)//dont run at first execution
            ft_draw_line(a->com, a->win, &img_line);
        idx++;
    }
    
    //draw new line
    idx = dir_pos;
    img_line.color = 0x00FF0000;
    img_line.startPosX = a->player->Pos[origin][X];
    img_line.startPosY = a->player->Pos[origin][Y];
    while (idx < MaxPos)
    {
        img_line.endPosX = a->player->Pos[idx][X];
        img_line.endPosY = a->player->Pos[idx][Y];
        ft_draw_line(a->com, a->win, &img_line);
        idx++;
    }
#endif
#if 0
    //print new positions
    (void)old;
    if (old[dir][X] != -1)//dont run at first execution
    {
        mlx_put_image_to_window(a->com, a->win, a->player->black_img->img_ref_ptr, old[origin][X], old[origin][Y]); //print black img
        mlx_put_image_to_window(a->com, a->win, a->player->black_img->img_ref_ptr, old[dir][X], old[dir][Y]); //black
        mlx_put_image_to_window(a->com, a->win, a->player->black_img->img_ref_ptr, old[dir_neg][X], old[dir_neg][Y]); //black
        mlx_put_image_to_window(a->com, a->win, a->player->black_img->img_ref_ptr, old[dir_pos][X], old[dir_pos][Y]); //black
    }
    mlx_put_image_to_window(a->com, a->win, a->player->img->img_ref_ptr, a->player->Pos[origin][X], a->player->Pos[origin][Y]);
    mlx_put_image_to_window(a->com, a->win, a->player->img->img_ref_ptr, a->player->Pos[dir][X], a->player->Pos[dir][Y]);
    mlx_put_image_to_window(a->com, a->win, a->player->img->img_ref_ptr, a->player->Pos[dir_neg][X], a->player->Pos[dir_neg][Y]);
    mlx_put_image_to_window(a->com, a->win, a->player->img->img_ref_ptr, a->player->Pos[dir_pos][X], a->player->Pos[dir_pos][Y]);
#endif
    return (0);
}


int ft_player_angle(int key, t_app *a)
{
    (void)key;
    if (a->player->key_left)
    {
        a->player->heading_angle += ANGLE_SENSITIVITY;
        if (a->player->heading_angle > 2 * PI)
            a->player->heading_angle = 0;
        a->player->delta_x = cos(a->player->heading_angle);
        a->player->delta_y = sin(a->player->heading_angle);
    }
    if (a->player->key_right)
    {
        a->player->heading_angle -= ANGLE_SENSITIVITY;
        if (a->player->heading_angle < 0)
            a->player->heading_angle = 2 * PI;
        a->player->delta_x = cos(a->player->heading_angle);
        a->player->delta_y = sin(a->player->heading_angle);
    }
    return (0);
}

int ft_loop_player(t_app *app)
{
    //ft_player_angle(0, app);
    ft_draw_rays(app);
	ft_player_move(app);
    return (0);
}
