/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:53:36 by fsemke            #+#    #+#             */
/*   Updated: 2022/04/08 13:32:05 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printf(const char *input, ...)
{
	t_notes	*notes;
	int		i;
	int		length;

	notes = malloc(sizeof(t_notes));
	if (!notes)
		return (-1);
	ft_set_default(notes);
	va_start(notes->args, input);
	i = -1;
	while (input[++i] != '\0')
	{
		if (input[i] == '%')
			i = ft_special_format(input, i, notes);
		else
		{
			write(1, &input[i], 1);
			notes->print_len++;
		}
	}
	va_end(notes->args);
	length = notes->print_len;
	free (notes);
	return (length);
}
