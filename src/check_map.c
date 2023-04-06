/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:55:43 by fsemke            #+#    #+#             */
/*   Updated: 2023/04/06 22:15:25 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_check_valid_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	else
	{
		close(fd);
		return (0);
	}
}

void	ft_check_map(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map->map[y] && map->map[y][x])
	{
		while (map->map[y][x])
		{
			if (ft_strchr("NSEW", map->map[y][x]) != NULL)
				ft_set_spawn(map, x, y);
			else if (map->map[y][x] == ' ')
				map->map[y][x] = '0';
			else if (map->map[y][x] != '0' && map->map[y][x] != '1')
				error_exit("Error\nCharacter found that is not allowed\n", map);
			++x;
		}
		++y;
		x = 0;
	}
	if (map->player_x == -1 || map->player_y == -1)
		error_exit("Error\nNo Spawnpoint found\n", map);
}

int	ft_wallcheck(char **map, int x, int y)
{
	map[y][x] = 'G';
	if ((y - 1) < 0 || !map[y - 1] || !map[y - 1][x])
		return (-1);
	if (map[y - 1] && map[y - 1][x] && map[y - 1][x] == '0')
		if (ft_wallcheck(map, x, y - 1) == -1)
			return (-1);
	if (!map[y][x + 1])
		return (-1);
	if (map[y][x + 1] && map[y][x + 1] == '0')
		if (ft_wallcheck(map, x + 1, y) == -1)
			return (-1);
	if (!map[y + 1] || !map[y + 1][x])
		return (-1);
	if (map[y + 1] && map[y + 1][x] && map[y + 1][x] == '0')
		if (ft_wallcheck(map, x, y + 1) == -1)
			return (-1);
	if ((x - 1) < 0 || !map[y][x - 1])
		return (-1);
	if (map[y][x - 1] && map[y][x - 1] == '0')
		if (ft_wallcheck(map, x - 1, y) == -1)
			return (-1);
	return (0);
}

char	**ft_copy_gamemap(t_map *map)
{
	int		i;
	char	**copy;

	copy = (char **)malloc(sizeof(char *) * (map->map_size_y + 1));
	if (!copy)
		error_exit("Error\nMemory allocation failed\n", map);
	i = 0;
	while (map->map[i])
	{
		copy[i] = ft_strdup(map->map[i]);
		++i;
	}
	copy[i] = NULL;
	return (copy);
}

void	ft_check_errors(t_map *map)
{
	char	**mapcopy;

	ft_check_file_ext(map->no_texture, FILE_EXT_TEXTURE, map);
	ft_check_file_ext(map->ea_texture, FILE_EXT_TEXTURE, map);
	ft_check_file_ext(map->so_texture, FILE_EXT_TEXTURE, map);
	ft_check_file_ext(map->we_texture, FILE_EXT_TEXTURE, map);
	if (ft_check_valid_file(map->no_texture) == -1)
		error_exit("Error\nCan't open North texture file\n", map);
	if (ft_check_valid_file(map->ea_texture) == -1)
		error_exit("Error\nCan't open East texture file\n", map);
	if (ft_check_valid_file(map->so_texture) == -1)
		error_exit("Error\nCan't open South texture file\n", map);
	if (ft_check_valid_file(map->we_texture) == -1)
		error_exit("Error\nCan't open West texture file\n", map);
	ft_check_map(map);
	mapcopy = ft_copy_gamemap(map);
	if (ft_wallcheck(mapcopy, map->player_x, map->player_y) == -1)
	{
		ft_clean_2d_array(mapcopy);
		error_exit("Error\nMap not surrounded by a wall\n", map);
	}
	ft_clean_2d_array(mapcopy);
}
