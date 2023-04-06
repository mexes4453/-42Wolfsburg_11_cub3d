/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:21:32 by fsemke            #+#    #+#             */
/*   Updated: 2023/04/06 23:37:07 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_free_img(void *mlx_ptr, t_img *img)
{
	mlx_destroy_image(mlx_ptr, img->img_ref_ptr);
	free(img);
	img = NULL;
}

void	ft_clean_2d_array(char **array)
{
	int	i;

	if (array && array[0])
	{
		i = -1;
		while (array[++i])
			free (array[i]);
	}
	if (array)
	{
		free (array);
		array = NULL;
	}
}

void	ft_clean_parsing(t_map *map)
{
	if (map->file)
		ft_clean_2d_array(map->file);
	ft_clean_2d_array(map->map);
	if (map->no_texture)
		free (map->no_texture);
	if (map->ea_texture)
		free (map->ea_texture);
	if (map->so_texture)
		free (map->so_texture);
	if (map->we_texture)
		free (map->we_texture);
}
