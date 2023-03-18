/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:35:38 by fsemke            #+#    #+#             */
/*   Updated: 2021/12/20 14:14:36 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t max_len)
{
	size_t	i;
	char	*sub;
	size_t	sub_len;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	sub_len = ft_strlen(s + start);
	if (sub_len < max_len)
		max_len = sub_len;
	sub = (char *)malloc((max_len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (s[start + i] && i < max_len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
