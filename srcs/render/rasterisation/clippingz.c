#include "rasterize.h"

void		clipping_z(t_fvct3 *behind, t_fvct3 *correct)
{
	double	diff_percent;

	diff_percent = (correct->y - 1) / (correct->y - behind->y);
	behind->z = (correct->z) - diff_percent * (correct->z - behind->z);
	behind->x = (correct->x) - diff_percent * (correct->x - behind->x);
	behind->y = 1;
}

void		verticle_clipping_z(t_verticle *behind, t_verticle *correct)
{
	double	diff_percent;

	diff_percent = (correct->p.y - 1) / (correct->p.y - behind->p.y);
	behind->p.z = (correct->p.z) - diff_percent * (correct->p.z - behind->p.z);
	behind->p.x = (correct->p.x) - diff_percent * (correct->p.x - behind->p.x);
	behind->p.y = 1;

	//clip texture
	behind->texel.x = (1 - diff_percent) * behind->texel.x;
	behind->texel.y = (1 - diff_percent) * behind->texel.y;
}