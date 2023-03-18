/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cases.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:26:54 by fsemke            #+#    #+#             */
/*   Updated: 2022/04/08 13:15:18 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief notes all of the special characters,
 * and call all of the different functions to write them. 
 * 
 * @param input the input string
 * @param i position of the %
 * @param notes all of the notes
 * @return last position of the % command (e.g. "%d" will return 1)
 */
int	ft_special_format(const char *input, int i, t_notes *notes)
{
	i++;
	if (input[i] == '%')
	{
		ft_putchar_fd('%', 1);
		notes->print_len++;
		return (i);
	}
	while (ft_strchr("0-+ #", input[i]) != NULL)
	{
		i = check_specials(input, i, '0', &notes->zero);
		i = check_specials(input, i, '-', &notes->minus);
		i = check_specials(input, i, '+', &notes->plus);
		i = check_specials(input, i, ' ', &notes->space);
		i = check_specials(input, i, '#', &notes->hash);
	}
	if (ft_isdigit(input[i]))
		notes->width = ft_getnumber(input, &i);
	i = check_specials(input, i, '.', &notes->dot);
	if (ft_isdigit(input[i]) && notes->dot == 1)
		notes->precision = ft_getnumber(input, &i);
	ft_types(input, &i, notes);
	ft_notesreset(notes);
	return (--i);
}

/**
 * @brief check which type of input it is and save it in the notes.
 * 
 * @param input the given string
 * @param i position we are looking at
 * @param nt the notes
 */
void	ft_types(const char *input, int *i, t_notes *nt)
{
	if (input[*i] == 'd' || input[*i] == 'i')
		nt->print_len += ft_printint(va_arg(nt->args, int), nt);
	else if (input[*i] == 'c')
		nt->print_len += ft_printchar(va_arg(nt->args, int), nt);
	else if (input[*i] == 's')
		nt->print_len += ft_printstr(va_arg(nt->args, char *), nt);
	else if (input[*i] == 'p')
		nt->print_len += ft_printptr(va_arg(nt->args, unsigned long), nt);
	else if (input[*i] == 'x' || input[*i] == 'X')
		nt->print_len += ft_printhex(va_arg(nt->args, unsigned int),
				input[*i], nt);
	else if (input[*i] == 'u')
		nt->print_len += ft_printdec(va_arg(nt->args, unsigned int), nt);
	*i = *i + 1;
}

int	ft_printstr(char *str, t_notes *notes)
{
	int		strlen;
	char	*newstr;

	if (str == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	newstr = str;
	strlen = ft_strlen(newstr);
	if (notes->dot == 1 && notes->precision < strlen)
	{
		newstr = ft_substr(str, 0, notes->precision);
		strlen = ft_strlen(newstr);
	}
	if (notes->width > strlen && notes->minus == 0)
		strlen += fill_width(strlen, notes->width, ' ');
	ft_putstr_fd(newstr, 1);
	if (notes->width > strlen && notes->minus == 1)
		strlen += fill_width(strlen, notes->width, ' ');
	if (ft_strlen(str) != ft_strlen(newstr))
		free (newstr);
	return (strlen);
}

int	ft_printchar(char c, t_notes *notes)
{
	int	length;

	length = 1;
	if (notes->width > 1 && notes->minus == 0)
		length += fill_width(1, notes->width, ' ');
	write(1, &c, 1);
	if (notes->width > 1 && notes->minus == 1)
		length += fill_width(1, notes->width, ' ');
	return (length);
}

int	ft_printptr(unsigned long dec_address, t_notes *notes)
{
	if (dec_address == 0)
		return (ft_printstr("0x0", notes));
	return (ft_printhex_ptr(dec_address, 'x', notes));
}
