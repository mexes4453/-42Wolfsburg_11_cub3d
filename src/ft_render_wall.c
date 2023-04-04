

#include "../cub3d.h"

void ft_render_wall(t_app *a, t_cmp_lines *l, int x)
{
	int draw_start;
	int	draw_end;
	int render_height;
	int text_y; //read position

	render_height = (int)(SCR_HEIGHT_PX / l->perpWallDist);
	draw_start = -render_height / 2 + SCR_HEIGHT_PX / 2;
	draw_end = render_height / 2 + SCR_HEIGHT_PX / 2;
	if (draw_start < 0)
		draw_start = 0;	
	if (draw_end >= SCR_HEIGHT_PX)
		draw_end = SCR_HEIGHT_PX - 1;

	//double step = 1.0 * IMG_SZ_Y_WALL / render_height;
	// select wall texture for ray based on its orientation on map
	if (l->pole == SOUTH)
		a->texture = a->text_S;
	else if (l->pole == NORTH)
		a->texture = a->text_N;
	else if (l->pole == EAST)
		a->texture = a->text_E;
	else if (l->pole == WEST)
		a->texture = a->text_W;
	//Put Texture to Image
	while (draw_start < draw_end)
	{
		text_y = abs((((draw_start * IMG_SZ_Y_WALL * 4 - (SCR_HEIGHT_PX / 2 * IMG_SZ_Y_WALL * 4) \
		+ render_height * (IMG_SZ_Y_WALL / 2) * 4) * IMG_SZ_Y_WALL) / render_height) / (IMG_SZ_Y_WALL * 4));
		ft_memcpy(a->main_img->addr + 4 * SCR_WIDTH_PX * draw_start + x * 4, \
		&a->texture->addr[text_y % IMG_SZ_Y_WALL * a->texture->line_length + l->text_x % 64 * a->texture->bits_per_pixel / 8], sizeof(int));
		++draw_start;
	}
}
