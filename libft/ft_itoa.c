/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:54:26 by fsemke            #+#    #+#             */
/*   Updated: 2021/12/27 13:52:07 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_create_new_str(int n, size_t	*size)
{
	char	*s;
	long	cache;

	cache = n;
	*size = 0;
	if (cache < 0)
	{
		cache = cache * -1;
		*size = *size + 1;
	}
	else if (cache == 0)
		*size = 1;
	while (cache > 0)
	{
		cache = cache / 10;
		*size = *size + 1;
	}
	s = (char *)malloc((*size + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	s[*size] = '\0';
	return (s);
}

static void	ft_writenum(char *s, long cache, size_t size)
{
	long	lastnum;

	while (size > 0)
	{
		lastnum = cache % 10;
		cache = cache / 10;
		size--;
		s[size] = (char)(lastnum + 48);
	}
	return ;
}

char	*ft_itoa(int n)
{
	char	*s;
	long	cache;
	size_t	*size;
	size_t	size_value;

	size = &size_value;
	s = ft_create_new_str(n, size);
	if (n < 0)
	{
		cache = n;
		cache = cache * -1;
		s[0] = '-';
		ft_writenum((s + 1), cache, *size - 1);
	}
	else
		ft_writenum(s, n, *size);
	return (s);
}
