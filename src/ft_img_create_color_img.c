/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_img_create_color_img.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:08:22 by cudoh             #+#    #+#             */
/*   Updated: 2023/03/31 19:02:21 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_app_pixel_put_on_img(t_img *data, int x, int y, uint32_t color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length);
	dst += (x * (data->bits_per_pixel / BIT_SIZE_BYTE));
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



t_img   *ft_img_create_color_img(void *mlxPtr, uint32_t color, int szX, int szY)
{
    t_img   *img;
    
    img = ft_calloc(1, sizeof(t_img));
    img->sz_x = szX;
    img->sz_y = szY;
	img->img_ref_ptr = mlx_new_image(mlxPtr, szX, szY);
	img->addr = mlx_get_data_addr(img->img_ref_ptr, \
									&(img->bits_per_pixel), \
									&(img->line_length), \
									&(img->endian));
	ft_app_color_fill_img((img), color);
    return (img);
}


#if 0
void	ft_app_create_file_img(t_app *a, t_img *i, char *fp_img)
{
	i->img = mlx_xpm_file_to_image(a->com, fp_img, &(i->sz_x), &(i->sz_y));
}

/**
 * @brief 		This function displays img on window. Img objects passed in
 * 				are destroyed if flag = TRUE_DESTORY.
 * todo			Ensure that the pixel cordinate is update accordingly before push
 * 
 * @param a 
 * @param i 
 * @param flag 
 */
void	ft_app_display_img(t_app *a, t_img *i, int flag)
{
	mlx_put_image_to_window(a->com, a->win, i->img, a->px, a->py);
	if (flag == TRUE_DESTROY)
		mlx_destroy_image(a->com, i->img);
}
#endif 


