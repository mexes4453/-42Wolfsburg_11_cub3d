/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_app_close.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:11:23 by cudoh             #+#    #+#             */
/*   Updated: 2023/03/19 16:18:41 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_app_close(void *params)
{
	t_app	*a;

	a = (t_app *)params;
	ft_printf("\nExiting application...\n");
	//mlx_destroy_image(a->com, (a->p.p_img.img));
	mlx_destroy_image(a->com, (a->img->img_ref_ptr));
	mlx_destroy_window(a->com, a->win);
	//ft_app_free_gmap(a->map);
    ft_clean_parsing(a->map);
    
	//mlx_destroy_display(a->com);
	free(a->com);
	exit(EXIT_SUCCESS);
	return (0);
}