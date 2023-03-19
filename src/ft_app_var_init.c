/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_app_var_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 09:53:10 by cudoh             #+#    #+#             */
/*   Updated: 2023/03/19 17:56:03 by cudoh            ###   ########.fr       */
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
#if 0
	a->p.p_img.img_ref_ptr = NULL;
	a->p.p_img.addr = NULL;
	a->rq = NULL;
	a->cq = NULL;
	a->rc = 0;
	a->matrix = NULL;
#endif
}