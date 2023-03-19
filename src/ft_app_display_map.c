/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_app_display_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:42:50 by cudoh             #+#    #+#             */
/*   Updated: 2023/03/19 17:56:40 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
        
int	ft_app_display_map(t_app *a, t_map *m, char *S, t_img *i)
{
    m->idx_y = 0;
	while (m->idx_y < m->map_size_y)
	{
		m->idx_x = 0;
		while ((m->idx_x < m->map_size_x) && *(m->map[m->idx_y] + m->idx_x) != '\0')
		{
            a->px = (m->idx_x * IMG_SZ_X_WALL);
	        a->py = (m->idx_y * IMG_SZ_Y_WALL);
			m->chr = m->map[m->idx_y][m->idx_x];
			if (m->chr == S[0])
				mlx_put_image_to_window(a->com, a->win, i->img_ref_ptr, a->px, a->py);
			m->idx_x++;
		}
		m->idx_y++;
	}
	return (0);
}