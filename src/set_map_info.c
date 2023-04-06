/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:13:22 by fsemke            #+#    #+#             */
/*   Updated: 2023/04/06 23:47:00 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_set_texture(char *line, char **var_texture, t_map *map)
{
	int	i;

	i = 2;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\r')
		i++;
	if (*var_texture)
		error_exit("ERROR:\nYou set a texture more than once\n", map);
	*var_texture = ft_strdup_up_to_space(&line[i]);
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

static int	ft_check_color_val_str(char *str_col, int *int_col)
{
	char	*str_col_ptr;
	char	*str_itoa;
	int		err_code;

	err_code = 0;
	if (str_col != NULL)
	{
		str_col_ptr = ft_strtrim(str_col, WHITESPACE_CHAR);
		*int_col = ft_atoi(str_col_ptr);
		str_itoa = ft_itoa(*int_col);
		if (ft_strncmp(str_col_ptr, str_itoa, ft_strlen(str_col_ptr)) != 0)
			err_code = -1;
		else if (*int_col < 0 || *int_col > 255)
			err_code = -1;
		free(str_col_ptr);
		free(str_itoa);
		str_col_ptr = NULL;
		str_itoa = NULL;
	}
	return (err_code);
}

int	ft_color_to_int(char *line, t_map *map)
{
	int		rgb[3];
	char	**tmp;
	int		i;
	int		result;

	tmp = ft_split(&line[2], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2] || tmp[3])
	{
		ft_clean_2d_array(tmp);
		error_exit("Error:\nThe color format isn't RGB\n", map);
	}
	i = -1;
	while (++i < 3)
	{
		if (ft_check_color_val_str(&(tmp[i][0]), &rgb[i]) < 0)
		{
			ft_clean_2d_array(tmp);
			error_exit("Error:\ncorrupt color format\n", map);
		}
	}
	result = ft_combine_rgb(rgb[0], rgb[1], rgb[2]);
	ft_clean_2d_array(tmp);
	return (result);
}
