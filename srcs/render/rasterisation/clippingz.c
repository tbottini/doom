#include "rasterize.h"

void		clipping_z(t_fvct3 *behind, t_fvct3 *correct)
{
	double	diff_percent;

	diff_percent = (correct->y - 1) / (correct->y - behind->y);
	behind->z = (correct->z) - diff_percent * (correct->z - behind->z);
	behind->x = (correct->x) - diff_percent * (correct->x - behind->x);
	behind->y = 1;
}