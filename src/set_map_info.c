/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:13:22 by fsemke            #+#    #+#             */
/*   Updated: 2023/03/18 17:45:28 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_set_texture(char *line, char **var_texture, t_map *map)
{
	int	i;

	i = 2;
	while (line[i] == ' ')
		i++;
	if (*var_texture)
		error_exit("ERROR:\nYou set a texture more than once\n", map);
	*var_texture = ft_strdup(&line[i]);
}

void	ft_set_color(char *line, t_map *map)
{
	int	i;

	i = 1;
	while (line[++i])
	{
		if (line[i] == ' ' || line[i] == ',')
			continue ;
		else if (!ft_isdigit(line[i]))
			error_exit("Error:\nThe color format isn't RGB\n", map);
	}
	if (line[0] == 'F' && map->floor_c == 0)
		map->floor_c = ft_color_to_int(line, map);
	else if (line[0] == 'C' && map->ceilling_c == 0)
		map->ceilling_c = ft_color_to_int(line, map);
	else
		error_exit("Error:\nSet floor or ceil color multiple times\n", map);
}

int	ft_color_to_int(char *line, t_map *map)
{
	int		rgb[3];
	char	**tmp;
	int		i;
	int		result;

	tmp = ft_split(&line[2], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2] || tmp[3])
		error_exit("Error:\nThe color format isn't RGB\n", map);
	i = -1;
	while (++i < 3)
		rgb[i] = ft_atoi(tmp[i]);
	if (ft_check_rgb(rgb) == -1)
		error_exit("Error:\nThe color format isn't RGB\n", map);
	result = ft_combine_rgb(rgb[0], rgb[1], rgb[2]);
	ft_clean_2d_array(tmp);
	return (result);
}

int	ft_check_rgb(int rgb[3])
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (-1);
	}
	return (0);
}

int	ft_combine_rgb(int r, int g, int b)
{
	return (255 << 24 | r << 16 | g << 8 | b);
}
