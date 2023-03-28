
#include "../cub3d.h"

void	ft_save_ray_length(t_app *a, double distance)
{
	static int i = 0;

	a->raylengths[i] = distance;
	++i;

	if (i == a->nbr_of_rays)
		i = 0;
}
