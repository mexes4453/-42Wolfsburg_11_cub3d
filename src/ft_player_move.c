/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:05:49 by fsemke            #+#    #+#             */
/*   Updated: 2023/03/28 21:23:132 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int ft_player_move(int key, t_app *a)
{
	(void)key;
	int old[MaxPos][2];
	int i;

	i = 0;
	while (i < MaxPos)
	{
		old[i][X] = a->player->Pos[i][X];
		old[i][Y] = a->player->Pos[i][Y];
		++i;
	}

	//move the player
	if (a->player->key_w)
		ft_onKeyPress_W(a);
	if (a->player->key_a)
		ft_onKeyPress_A(a);
	if (a->player->key_s)
		ft_onKeyPress_S(a);
	if (a->player->key_d)
		ft_onKeyPress_D(a);

	if  (a->print_flag == 1)
	{
		//overwrite everything
		mlx_put_image_to_window(a->com, a->win, a->black_backgroud->img_ref_ptr, 0, 0);
		ft_app_display_map(a, a->map, "1", a->img);
		
		a->px = 0;
		a->py = 0;
		//calculating new coordinates
		a->player->Pos[dir][X] = a->player->Pos[origin][X] + (a->player->delta_x * DIR_LENGTH);
		a->player->Pos[dir][Y] = a->player->Pos[origin][Y] - (a->player->delta_y * DIR_LENGTH);
		a->player->Pos[dir_neg][X] = a->player->Pos[origin][X] + (cos(a->player->heading_angle + ((FOV / 2) * PI / 180.0)) * DIR_LENGTH);
		a->player->Pos[dir_neg][Y] = a->player->Pos[origin][Y] - (sin(a->player->heading_angle + ((FOV / 2) * PI / 180.0)) * DIR_LENGTH);
		a->player->Pos[dir_pos][X] = a->player->Pos[origin][X] + (cos(a->player->heading_angle - ((FOV / 2) * PI / 180.0)) * DIR_LENGTH);
		a->player->Pos[dir_pos][Y] = a->player->Pos[origin][Y] - (sin(a->player->heading_angle - ((FOV / 2) * PI / 180.0)) * DIR_LENGTH);
		
		//override old line with black
		
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
		
		//draw new lines
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
		

		// cast ray
		// compute  (FOV / (FOV/SCR_WIDTH) / RAY_LINE_PX_WIDTH) + 1
		
		t_cmp_lines horz;
		t_cmp_lines vert;
/* 		t_img *big_img;
		
		big_img = mlx_new_image(a->com, SCR_WIDTH_PX, SCR_HEIGHT_PX); */

		double offsetangle = (FOV / 2) * RADIENT;
		double increment =  ((double)FOV / (double)SCR_WIDTH_PX) * RADIENT * RAY_LINE_PX_WIDTH;
		//int i = 0;
		while (offsetangle >  (-FOV / 2) * RADIENT)
		{
			ft_ray_get_dist_horz(a, a->player, offsetangle, &horz);
			ft_ray_get_dist_vert(a, a->player, offsetangle, &vert);
			t_line line;
			line.startPosX = (int)a->player->Pos[origin][X];
			line.startPosY = (int)a->player->Pos[origin][Y];
			line.color = 0x0000FF00;
			if (horz.raylength < vert.raylength)
			{
				line.endPosX = horz.wall_x;
				line.endPosY = horz.wall_y;
				//ft_save_ray_length(a, horz.raylength);
				ft_render_wall(a, &horz);
			}
			else
			{
				line.endPosX = vert.wall_x;
				line.endPosY = vert.wall_y;
				//ft_save_ray_length(a, vert.raylength);
				ft_render_wall(a, &vert);
			}
			ft_draw_line(a->com, a->win, &line);
			offsetangle -=increment;
			//++i;
		}
		//ft_printf("Amount of Raylines: %d", i);
		//i = 0;
		a->print_flag = 0;
	}
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
		a->print_flag = 1;
	}
	if (a->player->key_right)
	{
		a->player->heading_angle -= ANGLE_SENSITIVITY;
		if (a->player->heading_angle < 0)
			a->player->heading_angle = 2 * PI;
		a->player->delta_x = cos(a->player->heading_angle);
		a->player->delta_y = sin(a->player->heading_angle);
		a->print_flag = 1;
	}
	return (0);
}

int ft_loop_player(t_app *app)
{
	ft_player_angle(0, app);
	ft_player_move(0, app);
	//ft_calc_wall(a, horz.raylength);// Need to create
	return (0);
}
