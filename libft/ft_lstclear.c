/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:16:37 by fsemke            #+#    #+#             */
/*   Updated: 2021/12/20 14:12:45 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*copy;

	if (lst == NULL || *lst == NULL || del == NULL)
		return ;
	while (*lst)
	{
		copy = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = copy;
	}
}
