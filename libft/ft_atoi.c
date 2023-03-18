/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:28:04 by fsemke            #+#    #+#             */
/*   Updated: 2021/12/27 13:36:46 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int			i;
	int			value;
	int			negativ;

	while (nptr && ((*nptr >= 7 && *nptr <= 13) || *nptr == ' '))
		nptr++;
	negativ = 0;
	if (nptr[0] == '-')
	{
		nptr++;
		negativ = 1;
	}
	else if (nptr[0] == '+')
		nptr++;
	value = 0;
	i = 0;
	while (nptr && (nptr[i] >= '0' && nptr[i] <= '9'))
		value = (value * 10) + ((int)nptr[i++] - 48);
	if (negativ == 1)
		value *= -1;
	return (value);
}
