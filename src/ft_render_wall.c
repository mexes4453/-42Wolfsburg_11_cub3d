

#include "../cub3d.h"

void ft_render_wall(t_app *a, t_cmp_lines *l)
{
/* 	int render_height = (IMG_SZ_Y_WALL * SCR_HEIGHT_PX) / l->raylength;
	a->py = (SCR_HEIGHT_PX / 2) - (render_height / 2);

	// draw rectangle
	a->wall = ft_img_create_color_img(a->com, 0x00FF0000, RAY_LINE_PX_WIDTH, render_height);
	mlx_put_image_to_window(a->com, a->win_world, a->wall->img_ref_ptr, a->px, a->py);
	mlx_destroy_image(a->com, a->wall->img_ref_ptr);
	a->wall = NULL;
	(a->px) += RAY_LINE_PX_WIDTH; */


	static int x = 0;
	int y;
	int render_height;
	int	end;

	render_height = (IMG_SZ_Y_WALL * SCR_HEIGHT_PX) / l->perpWallDist;
	y = ((SCR_HEIGHT_PX - render_height) / 2) - 1;
	end = (SCR_HEIGHT_PX / 2) + (render_height / 2);
	if (end > SCR_HEIGHT_PX)
		end = SCR_HEIGHT_PX;
	if (y < 0)
		y = -1;
	while (++y < end)
	{
		ft_app_pixel_put_on_img(a->main_img, x, y, 0x00FF0000);
		//ft_app_pixel_put_on_img(a->main_img, x+1, y, 0x00FF0000);
		//ft_app_pixel_put_on_img(a->main_img, x+2, y, 0x00FF0000);
	}
	if (++x == a->nbr_of_rays)
		x = 0;
}
