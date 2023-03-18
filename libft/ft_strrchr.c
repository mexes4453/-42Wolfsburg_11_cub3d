/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:21:11 by fsemke            #+#    #+#             */
/*   Updated: 2021/12/20 14:14:26 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*result;

	if (c > 128)
		c = c % 128;
	result = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			result = (char *)s + i;
		}
		i++;
	}
	if (c == '\0')
		result = (char *)s + i;
	return (result);
}
