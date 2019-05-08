#include "doom_nukem.h"

/*
**trouve l'intersection entre le mur et un angle donne
**pour ne pas afficher ce qui en dehors
*/
float			wall_clipping(t_wall wall1, t_wall wall2, t_fvct2 origin, float ang)
{
	t_fvct2		inter;
	t_fvct2		diff;
	t_fvct2		diff2;
	float		coef_ang;
	float		coef_wall;
	float		b;

	diff.x = wall1.pillar.x - origin.x;
	diff.y = wall1.pillar.y - origin.y;
	diff2.x = wall2.pillar.x - origin.x;
	diff2.y = wall2.pillar.y - origin.y;
	coef_ang = tan(ang * PI180);
	if (diff2.x - diff.x < 0.001 && diff2.x - diff.x > -0.001)
	{
		inter.x = diff.x;
		inter.y = diff.x * coef_ang;
	}
	else
	{
		coef_wall = (diff2.y - diff.y) / (diff2.x - diff.x);
		b = diff.x * coef_wall + diff.y;
		inter.x = b / (coef_ang - coef_wall);
		inter.y = coef_wall * inter.x + b;
	}
	return (distance(diff, diff2));
}
