/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_app_close.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:11:23 by cudoh             #+#    #+#             */
/*   Updated: 2023/03/28 2040:06 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_app_close(void *params)
{
	t_app	*a;

	a = (t_app *)params;
	ft_printf("\nExiting application...\n");
	ft_free_img(a->com, a->text_N);
	ft_free_img(a->com, a->text_S);
	ft_free_img(a->com, a->text_W);
	ft_free_img(a->com, a->text_E);
	ft_free_img(a->com, a->black_backgroud);
	ft_free_img(a->com, a->player->black_img);
	ft_free_img(a->com, a->player->img);
	ft_free_img(a->com, a->img);
	mlx_destroy_window(a->com, a->win);
	mlx_destroy_window(a->com, a->win_3d);
	mlx_destroy_display(a->com);
	free(a->com);
    ft_clean_parsing(a->map);
	exit(EXIT_SUCCESS);
	return (0);
}
