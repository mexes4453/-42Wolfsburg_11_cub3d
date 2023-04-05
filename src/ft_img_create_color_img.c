/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_img_create_color_img.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:08:22 by cudoh             #+#    #+#             */
/*   Updated: 2023/04/05 23:31:30 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_app_pixel_put_on_img(t_img *data, int x, int y, uint32_t color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length);
	dst += (x * (data->bpp / BIT_SIZE_BYTE));
	*(unsigned int *)dst = color;
}

static void	ft_app_color_fill_img(t_img *img, uint32_t color)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->sz_y)
	{
		x = 0;
		while (x < img->sz_x)
		{
			ft_app_pixel_put_on_img(img, x, y, color);
			x++;
		}
		y++;
	}
}

t_img	*ft_img_create_color_img(void *mlxPtr, uint32_t color, int szX, int szY)
{
	t_img	*img;

	img = ft_calloc(1, sizeof(t_img));
	img->sz_x = szX;
	img->sz_y = szY;
	img->img_ref_ptr = mlx_new_image(mlxPtr, szX, szY);
	img->addr = mlx_get_data_addr(img->img_ref_ptr, \
									&(img->bpp), \
									&(img->line_length), \
									&(img->endian));
	ft_app_color_fill_img((img), color);
	return (img);
}
