/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 17:27:18 by cudoh             #+#    #+#             */
/*   Updated: 2023/03/21 22:42:40 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void ft_player_init(t_player *p, t_map *m, t_app *app)
{
    t_line img_line;
    t_pos idx;
    
    idx = dir_pos;
    
    ft_memset((void *)p, 0, sizeof(t_player));
    p->Pos[origin][X] = (m->player_x * IMG_SZ_X_WALL) + (IMG_SZ_X_WALL / 2);
    p->Pos[origin][Y] = (m->player_y * IMG_SZ_Y_WALL) + (IMG_SZ_Y_WALL / 2);
    
    // get the cordinate of other point with reference to the origin cordinate (player)
    // direction vector
    p->Pos[dir][X] = p->Pos[origin][X];
    p->Pos[dir][Y] = p->Pos[origin][Y] - DIR_LENGTH;

    // direct plane negative vector
    p->Pos[dir_neg][X] = p->Pos[origin][X] + ((cos(((FOV / 2) + 90) * PI / 180.0)) * DIR_LENGTH);
    p->Pos[dir_neg][Y] = p->Pos[dir][Y];

    // direct plane positive vector
    p->Pos[dir_pos][X] = p->Pos[origin][X] + cos((90 - (FOV / 2)) * PI / 180.0) * DIR_LENGTH;
    p->Pos[dir_pos][Y] = p->Pos[dir][Y];
    
    // create player image
	p->img = ft_img_create_color_img(app->com, 0x00FF0000, IMG_SZ_X_PLAYER, IMG_SZ_Y_PLAYER);

    // draw lines
    img_line.startPosX = p->Pos[origin][X];
    img_line.startPosY = p->Pos[origin][Y];
    while (idx < MaxPos)
    {
        img_line.endPosX = p->Pos[idx][X];
        img_line.endPosY = p->Pos[idx][Y];
        ft_draw_line(app->com, app->win, &img_line);
        idx++;
    }
 

    
    
    
    if (m->player_orientation == NORTH)
        p->heading_angle = PI * 0.5;
    else if(m->player_orientation == WEST)
        p->heading_angle = PI;
    else if(m->player_orientation == SOUTH)
        p->heading_angle = PI * 1.5;
    else if(m->player_orientation == EAST)
        p->heading_angle = 0;

    //p->img = NULL; why?
    p->delta_x = cos(p->heading_angle);
    p->delta_y = sin(p->heading_angle);
    /*
    ft_memset((void *)&(p->img), 0, sizeof(t_img));
    p->img->addr = NULL;
    p->img->img_ref_ptr = NULL;
    p->img->sz_x = IMG_SZ_X_PLAYER;
    p->img->sz_y = IMG_SZ_Y_PLAYER;
    */
}

/* int    ft_key_pressed(int key, t_app *a)
{
    if (key == KEY_ESC)
        ft_app_close(a);
    else if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
        ft_player_move(key, a);
    else if (key == KEY_LEFT || key == KEY_RIGHT)
        ft_player_angle(key, a);

    else
        printf("New Button %d pressed\n", key);
    return (0);
} */

int    ft_key_pressed(int key, t_app *a)
{
    if (key == KEY_ESC)
        ft_app_close(a);
    else if (key == KEY_W)
        a->player->key_w = 1;
    else if (key == KEY_A)
        a->player->key_a = 1;
    else if (key == KEY_S)
        a->player->key_s = 1;
    else if (key == KEY_D)
        a->player->key_d = 1;
    else if (key == KEY_LEFT)
        a->player->key_left = 1;
    else if (key == KEY_RIGHT)
        a->player->key_right = 1;
    else
        printf("New Button %d pressed\n", key);
    return (0);
}

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

int ft_player_move(int key, t_app *a)
{
    (void)key;
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
    mlx_put_image_to_window(a->com, a->win, a->player->img->img_ref_ptr, a->player->Pos[origin][X], a->player->Pos[origin][Y]);
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
    ft_player_angle(0, app);
	ft_player_move(0, app);
    return (0);
}