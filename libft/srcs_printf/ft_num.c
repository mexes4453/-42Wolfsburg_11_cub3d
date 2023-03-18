/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:47:30 by fsemke            #+#    #+#             */
/*   Updated: 2022/05/13 10:14:09 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printint(int n, t_notes *notes)
{
	char	*str;
	int		strlen;

	str = ft_itoa(n);
	if (n < 0 && notes->dot == 1)
		notes->precision += 1;
	if (notes->precision > (int)ft_strlen(str))
		str = add_precision_int(str, notes->precision);
	if ((notes->space || notes->plus) && notes->zero && n >= 0)
		notes->width -= 1;
	if (notes->zero == 1 && notes->width > (int)ft_strlen(str)
		&& notes->precision == 0)
		str = add_precision_int(str, notes->width);
	if (notes->space && n >= 0)
		ft_putchar_fd(' ', 1);
	if (notes->plus && n >= 0)
		ft_putchar_fd('+', 1);
	ft_putstr_fd(str, 1);
	strlen = ft_strlen(str);
	if ((notes->space || notes->plus) && n >= 0)
		strlen++;
	if (notes->width > strlen && notes->minus == 1)
		strlen += fill_width(strlen, notes->width, ' ');
	free (str);
	return (strlen);
}

int	ft_printdec(unsigned int num, t_notes *notes)
{
	int	length;

	length = ft_num_length(num, 10);
	length = ft_dec_prefix(length, notes);
	ft_printdec_recursive(num, 1);
	if (notes->width > length && notes->minus == 1)
		length += fill_width(length, notes->width, ' ');
	return (length);
}

int	ft_printdec_recursive(unsigned int num, int first)
{
	unsigned int	cache;
	const char		*str;
	static int		counter;

	counter = 0;
	if (num != 0 || first == 1)
	{
		str = "0123456789";
		cache = num % 10;
		num = num / 10;
		ft_printdec_recursive(num, 0);
		counter++;
		write(1, &str[cache], 1);
	}
	return (counter);
}

int	ft_dec_prefix(int length, t_notes *notes)
{
	int	cache;

	cache = 0;
	if (length < notes->precision)
	{
		if (notes->minus == 0)
			cache = fill_width(notes->precision, notes->width, ' ');
		length += fill_width(length, notes->precision, '0') + cache;
	}
	else if (notes->width > length && !notes->minus
		&& notes->zero && !notes->precision)
		length += fill_width(length, notes->width, '0');
	else if (notes->width > length && !notes->minus
		&& !notes->zero && !notes->precision)
		length += fill_width(length, notes->width, ' ');
	return (length);
}
