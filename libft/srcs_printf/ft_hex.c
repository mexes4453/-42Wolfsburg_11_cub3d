/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:45:19 by fsemke            #+#    #+#             */
/*   Updated: 2022/04/08 13:15:13 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_preprinthex(int num, int len, char x, t_notes *nt)
{
	int	cache;

	cache = 0;
	if (num == 0 && nt->hash == 1)
		nt->hash = 0;
	if (nt->hash == 1)
	{
		len += 2;
		if (nt->precision > 0)
			nt->precision += 2;
	}
	if (len < nt->precision)
	{
		if (nt->minus == 0)
			cache = fill_width(nt->precision, nt->width, ' ');
		ft_printhashprefix(x, nt);
		len += fill_width(len, nt->precision, '0') + cache;
	}
	if (nt->width > len && !nt->minus && nt->zero && !nt->precision)
		len += fill_width(len, nt->width, '0');
	else if (nt->width > len && !nt->minus && !nt->zero && !nt->precision)
		len += fill_width(len, nt->width, ' ');
	ft_printhashprefix(x, nt);
	return (len);
}

void	ft_printhashprefix(char x, t_notes *notes)
{
	if (notes->hash == 1 && x == 'x')
		ft_putstr_fd("0x", 1);
	else if (notes->hash == 1 && x == 'X')
		ft_putstr_fd("0X", 1);
	notes->hash = 0;
}

int	ft_printhex(unsigned long num, char x, t_notes *notes)
{
	int	length;

	length = ft_num_length(num, 16);
	length = ft_preprinthex(num, length, x, notes);
	ft_printhex_recursive(num, x, 1);
	if (notes->width > length && notes->minus == 1)
		length += fill_width(length, notes->width, ' ');
	return (length);
}

int	ft_printhex_recursive(unsigned long num, char x, int first)
{
	char			*convert;
	unsigned long	remainder;
	unsigned long	result;
	static int		counter;

	counter = 0;
	if (num != 0 || first == 1)
	{
		result = num / 16;
		remainder = num - (result * 16);
		num = result;
		ft_printhex_recursive(num, x, 0);
		if (x == 'x')
			convert = "0123456789abcdef";
		else
			convert = "0123456789ABCDEF";
		write(1, &convert[remainder], 1);
		counter++;
	}
	return (counter);
}

int	ft_printhex_ptr(unsigned long num, char x, t_notes *notes)
{
	int	length;

	length = ft_num_length(num, 16);
	length += 2;
	if (notes->width > length && notes->minus == 0)
		length += fill_width(length, notes->width, ' ');
	ft_putstr_fd("0x", 1);
	ft_printhex_recursive(num, x, 0);
	if (notes->width > length && notes->minus == 1)
		length += fill_width(length, notes->width, ' ');
	return (length);
}
