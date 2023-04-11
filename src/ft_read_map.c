/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:05:45 by fsemke            #+#    #+#             */
/*   Updated: 2023/04/06 23:44:04 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*ft_join_str(char *s1, char *s2)
{
	char	*comb;
	int		i;
	size_t	j;
	size_t	new_lgth;

	if (!s2)
		return (NULL);
	new_lgth = ft_strlen(s1);
	new_lgth += ft_strlen(s2);
	comb = (char *)malloc(new_lgth + 1);
	if (!comb)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		comb[i] = s1[i];
		i++;
	}
	j = -1;
	while (s2[++j])
		comb[i + j] = s2[j];
	comb[i + j] = '\0';
	free (s1);
	return (comb);
}

char	*ft_read(int fd)
{
	char	*buffer;
	char	*str;
	int		read_bytes;

	buffer = malloc(sizeof(char) * 2);
	str = malloc(sizeof(char));
	str[0] = '\0';
	if (!buffer || fd < 0)
		return (NULL);
	read_bytes = 1;
	while (read_bytes != 0)
	{
		read_bytes = read(fd, buffer, 1);
		if (read_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		str = ft_join_str(str, buffer);
	}
	free (buffer);
	return (str);
}

char	**ft_read_file(char *filename)
{
	int		fd;
	char	*tmp;
	char	**file;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	tmp = ft_read(fd);
	close(fd);
	if (!tmp)
		return (NULL);
	file = ft_split_custom(tmp, '\n');
	free(tmp);
	return (file);
}

int	ft_read_map(char *filename, t_map *map)
{
	ft_check_file_ext(filename, FILE_EXT_MAP, map);
	map->file = ft_read_file(filename);
	if (!(map->file))
		error_exit("ERROR:\nCan't load the file\n", map);
	ft_parsing_file(map->file, map);
	ft_check_errors(map);
	return (0);
}
