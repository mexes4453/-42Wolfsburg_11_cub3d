/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:49:20 by fsemke            #+#    #+#             */
/*   Updated: 2021/12/23 14:46:49 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_it;
	t_list	*new_lst_begin;

	if (!lst || !f)
		return (NULL);
	new_lst_begin = NULL;
	while (lst)
	{
		new_it = ft_lstnew(f(lst->content));
		if (!new_it)
		{
			ft_lstclear(&new_lst_begin, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst_begin, new_it);
		lst = lst->next;
	}
	return (new_lst_begin);
}
