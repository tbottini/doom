#include "doom_nukem.h"

float		dist_simple(t_fvct2 pt1, t_fvct2 pt2)
{
	return ((pt2.x - pt1.x) + (pt2.y + pt1.y));
}

void			nearest_pillar(t_wall *bunch)
{

}

void			backface_culling(t_wall **bunch, t_player player)
{
	//on a un tableau zbuffer sur une ligne
	//on affiche un mur
	//on affiche le
	size_t		i;


	i = 0;
	while (bunch[i])
	{
		printf("dist_simple : %f\n", dist_simple(bunch[i]->pillar.p, *(t_fvct2*)&player.pos));
		i++;
	}
}