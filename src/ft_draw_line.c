/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:43:21 by fsemke            #+#    #+#             */
/*   Updated: 2023/03/21 21:03:48 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    ft_draw_line(void *mlx, void *win, t_line *line)
{
	double deltaX;
	double deltaY;
	double pixelX;
	double pixelY;

	deltaX = line->endPosX - line->startPosX; // 10
	deltaY = line->endPosY - line->startPosY; // 0
	pixelX = line->startPosX;
	pixelY = line->startPosY;

	//From this, we can approximate the number of pixels we’ll have to draw along the way.

	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	//  pixels = sqrt((10 * 10) + (0 * 0)) = sqrt(100) = 10

	//The reason why we used double was so we can divide the total distance of our line by the amount of pixels we’ll have to draw.

	deltaX /= pixels; // 1
	deltaY /= pixels; // 0

	//So we can finally start plotting the line with a very simple loop:
	
	while (pixels)
	{
		mlx_pixel_put(mlx, win, pixelX, pixelY, line->color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}
