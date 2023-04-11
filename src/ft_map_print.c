/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 21:18:47 by cudoh             #+#    #+#             */
/*   Updated: 2023/04/11 07:02:46 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"


t_err_code ft_map_print(void *m)
{
    t_err_code r_code;
    tt_map *map;
    int x;
    int y;
    
    r_code = err_null_ptr;
    map = NULL;
    map = (tt_map *)m;
    x = 0;
    y = 0;
    if (map->ptr != NULL)
    {
        r_code = err_invalid_idx;
        if (map->size_x <= 0 || map->size_y <= 0)
            return (r_code);
        while (y < map->size_y)
        {
            x = 0;
            while (x < map->size_x)
            {
                ft_printf("%d, ", (map->ptr)[y][x]);
                x++;
            }
            ft_printf("\n");
            y++;
        }
        r_code = err_ok;
    }
    return (r_code);
}