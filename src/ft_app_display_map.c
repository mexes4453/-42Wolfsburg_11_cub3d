/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_app_display_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:42:50 by cudoh             #+#    #+#             */
/*   Updated: 2023/04/06 19:16:02 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_app_display_map(t_app *a, t_map *m, char *S, t_img *i)
{
	m->idx_y = 0;
	while (m->idx_y < m->map_size_y)
	{
		m->idx_x = 0;
		while ((m->idx_x < m->map_size_x)
			&& *(m->map[m->idx_y] + m->idx_x) != '\0')
		{
			a->px = (m->idx_x * IMG_SZ_X_WALL);
			a->py = (m->idx_y * IMG_SZ_Y_WALL);
			m->chr = m->map[m->idx_y][m->idx_x];
			if (m->chr == S[0])
				mlx_put_image_to_window(a->com, a->win, \
				i->img_ref_ptr, a->px, a->py);
			m->idx_x++;
		}
		m->idx_y++;
	}
	return (0);
}

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
