/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 17:27:18 by cudoh             #+#    #+#             */
/*   Updated: 2023/04/06 20:27:56 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_init_p_orient_ns(t_map *m, t_player *p)
{
	if (m->player_orientation == NORTH)
	{
		p->dir[X] = 0;
		p->dir[Y] = -1;
		p->plane[X] = 0.66;
		p->plane[Y] = 0;
	}
	else if (m->player_orientation == SOUTH)
	{
		p->dir[X] = 0;
		p->dir[Y] = 1;
		p->plane[X] = -0.66;
		p->plane[Y] = 0;
	}
}

static void	ft_init_p_orient_ew(t_map *m, t_player *p)
{
	if (m->player_orientation == WEST)
	{
		p->dir[X] = -1;
		p->dir[Y] = 0;
		p->plane[X] = 0;
		p->plane[Y] = -0.66;
	}
	else if (m->player_orientation == EAST)
	{
		p->dir[X] = 1;
		p->dir[Y] = 0;
		p->plane[X] = 0;
		p->plane[Y] = 0.66;
	}
}

void	ft_player_init(t_player *p, t_map *m)
{
	ft_memset((void *)p, 0, sizeof(t_player));
	p->pos[X] = m->player_x + 0.5;
	p->pos[Y] = m->player_y + 0.5;
	ft_init_p_orient_ns(m, p);
	ft_init_p_orient_ew(m, p);
}
