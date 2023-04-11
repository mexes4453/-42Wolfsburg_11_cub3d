/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 13:37:03 by fsemke            #+#    #+#             */
/*   Updated: 2023/04/11 06:58:37 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, void * const src, size_t n)
{
	unsigned int		i;
	unsigned char		*ptr_dest;
	unsigned char	* ptr_src;

	ptr_dest = (unsigned char *)dest;
	ptr_src = (unsigned char * const)src;
	i = 0;
	if (ptr_dest != NULL && ptr_src != NULL)
	{
		while (i < n)
		{
			ptr_dest[i] = ptr_src[i];
			i++;
		}
	}
	return (dest);
}
