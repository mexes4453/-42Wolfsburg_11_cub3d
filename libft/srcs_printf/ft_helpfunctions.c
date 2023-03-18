/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helpfunctions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 13:38:23 by fsemke            #+#    #+#             */
/*   Updated: 2022/04/08 13:15:15 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_getnumber(const char *input, int *i)
{
	int		begin;
	int		length;
	char	*num_string;
	int		ret_num;

	begin = *i;
	length = 0;
	while (ft_isdigit(input[*i]))
	{
		length++;
		*i = *i + 1;
	}
	num_string = ft_substr(input, begin, length);
	if (!num_string)
		return (-1);
	ret_num = ft_atoi(num_string);
	free (num_string);
	return (ret_num);
}

int	check_specials(const char *input, int i, char compare, int *value)
{
	if (input[i] == compare)
	{
		*value = 1;
		i++;
	}
	return (i);
}

/**
 * @brief fill the remaining width with the given character
 * 
 * @param str_len size of the string yet
 * @param width how big the string should be
 * @param fill_with the character we want to print at the end
 * @return the amount of printed characters in this function
 */
int	fill_width(int str_len, int width, char fill_with)
{
	int	i;

	i = 0;
	while (str_len < width)
	{
		write(1, &fill_with, 1);
		str_len++;
		i++;
	}
	return (i);
}

/**
 * @brief add some Zeros at the end of the string
 * 
 * @param str string with the integer
 * @param precision precision we want
 * @return char* return new str with zeros included
 */
char	*add_precision_int(char *str, int precision)
{
	int		length;
	char	*newstr;
	int		i;
	int		j;

	length = ft_strlen(str);
	newstr = malloc(sizeof(char) * (precision + 1));
	if (!newstr)
		return (NULL);
	i = -1;
	j = 0;
	if (str[0] == '-')
	{
		newstr[0] = '-';
		length -= 1;
		j++;
		i++;
	}
	while (++i < (precision - length))
		newstr[i] = '0';
	while (i < precision)
		newstr[i++] = str[j++];
	newstr[i] = '\0';
	free (str);
	return (newstr);
}

int	ft_num_length(unsigned long num, int dec_or_hex)
{
	int	count;

	count = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num /= dec_or_hex;
		count++;
	}
	return (count);
}
