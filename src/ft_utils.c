/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:16:34 by fsemke            #+#    #+#             */
/*   Updated: 2023/03/18 20:10:03 by fsemke           ###   ########.fr       */
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
