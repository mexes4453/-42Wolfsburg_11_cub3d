/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_custom.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:49:42 by fsemke            #+#    #+#             */
/*   Updated: 2023/03/18 17:36:56 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static size_t	countwords(const char *s, char c)
{
	size_t		i;
	size_t		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count + 1);
}

static char	*write_word(const char *s, long begin, long end)
{
	char	*word;
	size_t	i;

	i = 0;
	word = malloc((end - begin + 1) * sizeof(char));
	while (begin < end)
		word[i++] = s[begin++];
	word[i] = '\0';
	return (word);
}

char	**ft_split_custom(const char *s, char c)
{
	char	**arr;
	long	i;
	size_t	arr_iter;
	long	begin;

	arr = malloc((countwords(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	begin = -1;
	i = 0;
	arr_iter = 0;
	while (i <= (long)ft_strlen(s))
	{
		if (begin < 0)
			begin = i;
		if ((s[i] == c || s[i] == '\0') && begin >= 0)
		{
			arr[arr_iter++] = write_word(s, begin, i);
			begin = -1;
		}
		i++;
	}
	arr[arr_iter] = NULL;
	return (arr);
}
