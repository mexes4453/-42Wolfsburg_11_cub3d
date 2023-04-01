/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_app_var_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 09:53:10 by cudoh             #+#    #+#             */
/*   Updated: 2023/03/28 21:49:220 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_app_var_init(t_app *a, t_map *m)
{
	a->win_sz_x = IMG_SZ_X_WALL * m->map_size_x;
	a->win_sz_y = IMG_SZ_X_WALL * m->map_size_y;
    
    //initialise the image struct
	a->img = NULL;
    
	a->px = 0;
	a->py = 0;


	// compute  the number of rays to be casted
	a->nbr_of_rays = 0;
	//a->nbr_of_rays = (SCR_WIDTH_PX / RAY_LINE_PX_WIDTH) + 1;
	a->nbr_of_rays = SCR_WIDTH_PX;
	a->raylengths = (double *)ft_calloc(a->nbr_of_rays, sizeof(double));
}
