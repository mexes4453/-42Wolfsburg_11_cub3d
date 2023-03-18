/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:00:51 by fsemke            #+#    #+#             */
/*   Updated: 2021/12/20 14:13:51 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*character;

	i = 0;
	if (c > 128)
		c = c % 128;
	while (s[i])
	{
		if (s[i] == c)
		{
			character = (char *)s + i;
			return (character);
		}
		else
			i++;
	}
	if (c == '\0' && s[i] == '\0')
		return ((char *)s + i);
	return (NULL);
}
