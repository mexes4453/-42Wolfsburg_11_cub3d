/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:02:07 by fsemke            #+#    #+#             */
/*   Updated: 2021/12/20 14:13:54 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	n;
	size_t	i;
	char	*ptr;

	n = ft_strlen(s);
	ptr = (char *)malloc((n * sizeof(char)) + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i <= n)
	{
		ptr[i] = s[i];
		i++;
	}
	return (ptr);
}
