/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:58:31 by fsemke            #+#    #+#             */
/*   Updated: 2021/12/08 17:22:53 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*copy;
	int		i;

	copy = lst;
	i = 0;
	while (copy)
	{
		copy = copy->next;
		i++;
	}
	return (i);
}
