#include "doom_nukem.h"


int				fish_bowl_px(t_doom *doom, t_pillar pillar)
{
	int			px;
	int			sx;

	sx = doom->sdl.size.x / 2.0;
	px = sx - (tan(pillar.angle * PI180) * doom->camera.d_screen);
	return (px);
}

void			fish_eyes(double *dist, double angle)
{
	*dist = cos(angle * PI180) * *dist;
}