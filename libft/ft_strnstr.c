/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:29:44 by fsemke            #+#    #+#             */
/*   Updated: 2021/12/20 14:14:23 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i + j] && little[j] && (i + j) < len)
	{
		if (big[i + j] == little[j])
		{
			j++;
			if (little[j] == '\0')
				return ((char *)big + i);
		}
		else
		{
			j = 0;
			i++;
		}
	}
	return (NULL);
}
