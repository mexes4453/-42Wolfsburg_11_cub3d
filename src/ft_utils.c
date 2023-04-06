/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:16:34 by fsemke            #+#    #+#             */
/*   Updated: 2023/04/07 01:43:52 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_line_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		++i;
	if (line[i] == '\0')
		return (1);
	else
		return (0);
}

char	*ft_strdup_up_to_space(const char *s)
{
	size_t	length;
	size_t	i;
	char	*ptr;

	length = 0;
	while (s[length] != '\0' && s[length] != ' ')
		++length;
	ptr = (char *)malloc(sizeof(char) * (length + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < length)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	ft_check_file_ext(char *filename, char *file_ext, t_map *m)
{
	size_t	strlen_filename;
	size_t	strlen_file_ext;
	char	*ptr_ext;

	strlen_filename = 0;
	strlen_file_ext = 0;
	ptr_ext = NULL;
	strlen_filename = ft_strlen(filename);
	strlen_file_ext = ft_strlen(file_ext);
	if (strlen_file_ext == 0 || strlen_filename == 0)
		error_exit("Error\nfile path not found \n", m);
	else if (strlen_filename < strlen_file_ext)
		error_exit("Error\nfile format not found\n", m);
	else
	{
		ptr_ext = ft_strrchr(filename, '.');
		if (ptr_ext == NULL)
			error_exit("Error\nfile format not found\n", m);
		if (ft_strncmp(ptr_ext, file_ext, strlen_file_ext) != 0)
			error_exit("Error\nWrong file format\n", m);
	}
}

int	ft_combine_rgb(int r, int g, int b)
{
	return (255 << 24 | r << 16 | g << 8 | b);
}
