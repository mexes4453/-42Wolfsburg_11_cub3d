/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:05:36 by fsemke            #+#    #+#             */
/*   Updated: 2023/04/05 23:32:16 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_free_img(void *mlx_ptr, t_img *img)
{
	mlx_destroy_image(mlx_ptr, img->img_ref_ptr);
	free(img);
	img = NULL;
}
