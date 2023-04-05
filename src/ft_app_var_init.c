/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_app_var_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 09:53:10 by cudoh             #+#    #+#             */
/*   Updated: 2023/04/05 23:39:53 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_app_var_init(t_app *a, t_map *m)
{
	a->win_sz_x = IMG_SZ_X_WALL * m->map_size_x;
	a->win_sz_y = IMG_SZ_X_WALL * m->map_size_y;
	a->img = NULL;
	a->px = 0;
	a->py = 0;
	a->nbr_of_rays = SCR_WIDTH_PX;
}
