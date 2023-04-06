/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:43:21 by fsemke            #+#    #+#             */
/*   Updated: 2023/04/06 14:42:50 by fsemke           ###   ########.fr       */
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

	deltax = line->endPosX - line->startPosX;
	deltay = line->endPosY - line->startPosY;
	pixelx = line->startPosX;
	pixely = line->startPosY;
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
