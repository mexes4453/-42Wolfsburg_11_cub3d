

#include "../cub3d.h"

void ft_render_wall(t_app *a, t_cmp_lines *l)
{

    int render_height = (IMG_SZ_Y_WALL * SCR_HEIGHT_PX) / l->raylength;
    a->py = (SCR_HEIGHT_PX / 2) - (render_height / 2);

    // draw rectangle
    a->wall = ft_img_create_color_img(a->com, 0x00FF0000, RAY_LINE_PX_WIDTH, render_height);
    mlx_put_image_to_window(a->com, a->win_world, a->wall->img_ref_ptr, a->px, a->py);
    mlx_destroy_image(a->com, a->wall->img_ref_ptr);
	//free(a->wall);
    a->wall = NULL;
    (a->px) += RAY_LINE_PX_WIDTH;
}
