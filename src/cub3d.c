/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:08:44 by fsemke            #+#    #+#             */
/*   Updated: 2023/03/16 12:28:15 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_init_map_default(t_map *map)
{
	map->map = NULL;
	map->map_size_x = 0;
	map->map_size_y = 0;
	map->NO_texture = NULL;
	map->EA_texture = NULL;
	map->SO_texture = NULL;
	map->WE_texture = NULL;
	map->floor_c = 0;
	map->ceilling_c = 0;
	map->player_x = -1;
	map->player_y = -1;
	map->player_orientation = -1;
}

static void	ft_print_all_information(t_map *map)
{
	//Testfunction delete it!
	printf("NO_Texture: %s\n", map->NO_texture);
	printf("EA_Texture: %s\n", map->EA_texture);
	printf("SO_Texture: %s\n", map->SO_texture);
	printf("WE_Texture: %s\n\n", map->WE_texture);

	printf("Floor color: %d\n", map->floor_c);
	printf("Ceilling color: %d\n\n", map->ceilling_c);

	printf("Map_size_x: %d\n", map->map_size_x);
	printf("Map_size_y: %d\n\n", map->map_size_y);

	printf("Map: \n");
	for (int i = 0; map->map[i]; ++i)
	{
		printf("%s\n", map->map[i]);
	}
}

void	ft_init(char **argv, t_map *map)
{
	ft_init_map_default(map);
	ft_read_map(argv[1], map);
	ft_print_all_information(map);
}

int	main(int argc, char **argv)
{
	t_map	map;
	//t_mlx	mlx;

	if (argc != 2)
	{
		ft_putendl_fd("Insert one map (*.cub)", 1);
		exit(1);
	}
	ft_init(argv, &map);
	ft_clean_parsing(&map);
}
