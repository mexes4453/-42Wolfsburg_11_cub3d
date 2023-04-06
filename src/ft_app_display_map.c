/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_app_display_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:42:50 by cudoh             #+#    #+#             */
/*   Updated: 2023/04/06 20:21:37 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
 * This function draw a rayline to our map
 * pixels = number of pixels we’ll have to draw
 */
void	ft_draw_line(void *mlx, void *win, t_line *line)
{
	double	deltax;
	double	deltay;
	double	pixelx;
	double	pixely;
	int		pixels;

	deltax = line->end_posx - line->start_posx;
	deltay = line->end_posy - line->start_posy;
	pixelx = line->start_posx;
	pixely = line->start_posy;
	pixels = sqrt((deltax * deltax) + (deltay * deltay));
	deltax /= pixels;
	deltay /= pixels;
	while (pixels)
	{
		mlx_pixel_put(mlx, win, pixelx, pixely, line->color);
		pixelx += deltax;
		pixely += deltay;
		--pixels;
	}
}
