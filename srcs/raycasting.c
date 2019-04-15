#include "wolf3d.h"


t_fvct2			next_inter_hor(t_fvct2 pos, t_fvct2 ratio)
{
	t_fvct2		inter;

	inter.y = (float)(int)pos.y + 1;
	inter.x = (int)pos.x + (pos.y - inter.y) / tan(ratio.y / ratio.x);

	printf("ratio x %f y %f\n", ratio.x, ratio.y);
	printf("x %f y %f\n", inter.x, inter.y);
	printf("pos x %f y %f", pos.x, pos.y);
	return (inter);
}

/*t_vct2			next_inter(t_vct2 pos, t_vct2 ratio)
{
	t_vct2		inter;


}*/


int				raythrowing(t_wolf *wolf, int pixel_xi)
{
	t_fvct2		ratio;
	t_fvct2		accu;

	ratio.y = 1;
	ratio.x = (pixel_xi - (wolf->data->size.x / 2.0)) / (wolf->data->size.x / 2.0);

	accu.x = wolf->position.x;
	accu.y = wolf->position.y;

	next_inter_hor(accu, ratio);

	return (1);
}