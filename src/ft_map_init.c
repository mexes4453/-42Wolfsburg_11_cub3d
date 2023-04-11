/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 20:56:13 by cudoh             #+#    #+#             */
/*   Updated: 2023/04/11 06:46:58 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


t_err_code ft_map_init(tt_map *m, int map_array[10][10], int x, int y)
{
    t_err_code return_code = err_null_ptr;
    if (m != NULL && map_array != NULL)
    {
        ft_memset(m, 0, sizeof(tt_map));
        m->size_x = x;
        m->size_y = y;
        ft_memcpy((void *)m->ptr, (void *)map_array, sizeof(int) * x * y);
        m->print = ft_map_print;

        return_code = err_ok;
    }
    return (return_code);
}
