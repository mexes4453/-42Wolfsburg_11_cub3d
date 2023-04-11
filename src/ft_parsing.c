/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:22:59 by fsemke            #+#    #+#             */
/*   Updated: 2023/04/06 23:49:59 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_set_spawn(t_map *map, int x, int y)
{
	if (map->player_x != -1 || map->player_y != -1)
		error_exit("Error\nMultiple Player Spawn point\n", map);
	map->player_x = x;
	map->player_y = y;
	if (map->map[y][x] == 'N')
		map->player_orientation = NORTH;
	else if (map->map[y][x] == 'E')
		map->player_orientation = EAST;
	else if (map->map[y][x] == 'S')
		map->player_orientation = SOUTH;
	else
		map->player_orientation = WEST;
	map->map[y][x] = '0';
}

void	ft_parse_infos(char *line, t_map *map)
{
	if (line[0] == 'N' && line[1] == 'O')
		ft_set_texture(line, &map->no_texture, map);
	else if (line[0] == 'E' && line[1] == 'A')
		ft_set_texture(line, &map->ea_texture, map);
	else if (line[0] == 'S' && line[1] == 'O')
		ft_set_texture(line, &map->so_texture, map);
	else if (line[0] == 'W' && line[1] == 'E')
		ft_set_texture(line, &map->we_texture, map);
	else if ((line[0] == 'F' || line[0] == 'C'))
		ft_set_color(line, map);
	else if (line[0] == '\n' || line[0] == '\0')
		return ;
}

int	ft_parse_map(char *line, t_map *map)
{
	static int	y = -1;

	if (map->map == NULL)
	{
		map->map = (char **)malloc (sizeof(char *) * (map->map_size_y + 1));
		if (map->map == NULL)
			return (-1);
		map->map[map->map_size_y] = NULL;
	}
	if (ft_line_empty(line) == 0)
	{
		map->map[++y] = ft_strdup(line);
		if (!map->map[y])
			return (-1);
		return (0);
	}
	else
		return (1);
}

void	ft_set_mapsize(char **file, int i, t_map *map)
{
	int		tmp_length;
	char	**map_begin;

	map_begin = &file[i];
	tmp_length = 0;
	map->map_size_x = 0;
	map->map_size_y = 0;
	while (map_begin[map->map_size_y]
		&& ft_line_empty(map_begin[map->map_size_y]) == 0)
	{
		tmp_length = ft_strlen(map_begin[map->map_size_y]);
		if (tmp_length > map->map_size_x)
			map->map_size_x = tmp_length;
		++map->map_size_y;
	}
	if (map->map_size_x == 0 || map->map_size_y == 0)
	{
		ft_clean_2d_array(file);
		error_exit("Error:\nMapfile is corrupted\n", map);
	}
}

void	ft_parsing_file(char **file, t_map *map)
{
	int	i;
	int	ret;

	i = 0;
	while (file[i])
	{
		ft_parse_infos(file[i], map);
		++i;
		if (map->no_texture && map->ea_texture && map->so_texture
			&& map->we_texture && map->floor_c != 0 && map->ceilling_c != 0)
			break ;
	}
	while (file[i] && ft_line_empty(file[i]) == 1)
		++i;
	ft_set_mapsize(file, i, map);
	while (file[i])
	{
		ret = ft_parse_map(file[i], map);
		if (ret == 1 || ret == -1)
			break ;
		++i;
	}
	if (ret == -1)
		error_exit("Error:\nOccured by allocating memory for the map", map);
}
