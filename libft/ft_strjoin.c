/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:04:10 by fsemke            #+#    #+#             */
/*   Updated: 2021/12/21 12:03:49 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*comb;
	int		i;
	size_t	j;
	size_t	ls1;
	size_t	ls2;

	if (!s1 || !s2)
		return (NULL);
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	comb = (char *)malloc(ls1 + ls2 + 1);
	if (!comb)
		return (NULL);
	i = -1;
	while (s1[++i])
		comb[i] = s1[i];
	j = 0;
	while (s2[j])
	{
		comb[i + j] = s2[j];
		j++;
	}
	comb[i + j] = '\0';
	return (comb);
}
