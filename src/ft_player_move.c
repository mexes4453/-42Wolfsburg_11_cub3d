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
		t_img	*tmp;
		
		//Create main img
		tmp = ft_calloc(1, sizeof(t_img));
		tmp->sz_x = SCR_WIDTH_PX;
		tmp->sz_y = SCR_HEIGHT_PX;
		tmp->img_ref_ptr = mlx_new_image(a->com, SCR_WIDTH_PX, SCR_HEIGHT_PX);
		tmp->addr = mlx_get_data_addr(tmp->img_ref_ptr, &(tmp->bits_per_pixel), &(tmp->line_length), &(tmp->endian));

		ft_img_fill_floor_ceilling(tmp, a->map->ceilling_c, a->map->floor_c);
		a->main_img = tmp;

		double offsetangle = ((double)FOV / 2.0) * RADIENT;
		double increment = ((double)FOV / (double)SCR_WIDTH_PX) * RADIENT;
		int i = 0;
		//while (offsetangle >  (-FOV / 2.0) * RADIENT)
		while (i < SCR_WIDTH_PX)
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
				line.raylength = horz.raylength;
				//ft_save_ray_length(a, horz.raylength);
				ft_render_wall(a, &horz);
			}
			else
			{
				line.endPosX = vert.wall_x;
				line.endPosY = vert.wall_y;
				line.raylength = vert.raylength;
				//ft_save_ray_length(a, vert.raylength);
				ft_render_wall(a, &vert);
			}
			ft_draw_line(a->com, a->win, &line);
			//printf("raylength (%f), perpendicular dist(%f)\n", line.raylength, line.raylength * cos(offsetangle));
			
			//printf("offsetange %f\n", offsetangle * 180 / PI);
			//printf("playerangle %f\n", (a->player->heading_angle) * 180 / PI);
			offsetangle -= increment;
			++i;
		}
		mlx_put_image_to_window(a->com, a->win_world, a->main_img->img_ref_ptr, 0, 0);
		mlx_destroy_image(a->com, a->main_img->img_ref_ptr);
		a->main_img = NULL;
		//ft_printf("Amount of Raylines: %d", i);
		i = 0;
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
	return (0);
}

void	ft_img_fill_floor_ceilling(t_img *img, uint32_t ceilling_c, uint32_t floor_c)
{
	int	x;
	int y;

	y = 0;
	while (y < img->sz_y / 2)
	{
		x = 0;
		while (x < img->sz_x)
		{
			ft_app_pixel_put_on_img(img, x, y, ceilling_c);
			++x;
		}
		++y;
	}
	while (y < img->sz_y)
	{
		x = 0;
		while (x < img->sz_x)
		{
			ft_app_pixel_put_on_img(img, x, y, floor_c);
			++x;
		}
		++y;
	}
}