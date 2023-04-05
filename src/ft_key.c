/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:09:59 by fsemke            #+#    #+#             */
/*   Updated: 2023/04/05 23:25:31 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_key_pressed(int key, t_app *a)
{
	if (key == KEY_ESC)
		ft_app_close(a);
	else if (key == KEY_W)
		a->player->key_w = 1;
	else if (key == KEY_A)
		a->player->key_a = 1;
	else if (key == KEY_S)
		a->player->key_s = 1;
	else if (key == KEY_D)
		a->player->key_d = 1;
	else if (key == KEY_LEFT)
		a->player->key_left = 1;
	else if (key == KEY_RIGHT)
		a->player->key_right = 1;
	return (0);
}

int	ft_key_released(int key, t_player *p)
{
	if (key == KEY_W)
		p->key_w = 0;
	else if (key == KEY_A)
		p->key_a = 0;
	else if (key == KEY_S)
		p->key_s = 0;
	else if (key == KEY_D)
		p->key_d = 0;
	else if (key == KEY_LEFT)
		p->key_left = 0;
	else if (key == KEY_RIGHT)
		p->key_right = 0;
	return (0);
}
