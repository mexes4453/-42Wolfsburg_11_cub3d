/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:21:32 by fsemke            #+#    #+#             */
/*   Updated: 2023/03/16 12:34:06 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
		free (array);
}

void	ft_clean_parsing(t_map *map)
{
	ft_clean_2d_array(map->map);
	if (map->NO_texture)
		free (map->NO_texture);
	if (map->EA_texture)
		free (map->EA_texture);
	if (map->SO_texture)
		free (map->SO_texture);
	if (map->WE_texture)
		free (map->WE_texture);
}
