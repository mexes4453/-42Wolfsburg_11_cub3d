/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:31:14 by fsemke            #+#    #+#             */
/*   Updated: 2021/12/20 14:13:19 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int		i;
	char	*ptr_src;
	char	*ptr_dest;

	ptr_src = (char *)src;
	ptr_dest = (char *)dest;
	if (dest < src)
	{
		i = 0;
		while (i < (int)n)
		{
			ptr_dest[i] = ptr_src[i];
			i++;
		}
	}
	else
	{
		i = n - 1;
		while (i >= 0)
		{
			ptr_dest[i] = ptr_src[i];
			i--;
		}
	}
	return (dest);
}
