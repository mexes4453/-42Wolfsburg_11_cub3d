

#include "../cub3d.h"

void ft_render_wall(t_app *a, t_cmp_lines *l, int i)
{
	//int	text_y;
	int draw_start;
	int	draw_end;
	int render_height;

	render_height = (int)(SCR_HEIGHT_PX / l->perpWallDist);
	draw_start = -render_height / 2 + SCR_HEIGHT_PX / 2;
	draw_end = render_height / 2 + SCR_HEIGHT_PX / 2;
	if (draw_start < 0)
		draw_start = 0;	
	if (draw_end >= SCR_HEIGHT_PX)
		draw_end = SCR_HEIGHT_PX - 1;

	//double step = 1.0 * IMG_SZ_Y_WALL / render_height;
	//double text_pos = draw_start - SCR_HEIGHT_PX / 2 + render_height / 2;
	//Put Texture to Image
	while (draw_start < draw_end)
	{
		ft_app_pixel_put_on_img(a->main_img, i, draw_start, 0x00FF0000);
		++draw_start;

/* 		text_y = text_pos;
		text_pos += step;
		uint32_t color = img-> [IMG_SZ_Y_WALL * text_y + l->text_x]; */

	}
}
