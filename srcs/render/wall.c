#include "doom_nukem.h"

/*
**trouve l'intersection entre le mur et un angle donne
**pour ne pas afficher ce qui en dehors
*/
float			wall_clipping(t_wall wall, t_fvct2 pos, float angle)
{
	t_fvct2		inter;
	t_fvct2		diff;
	t_fvct2		diff2;
	float		coef_ang;
	float		coef_wall;
	float		b;

	diff.x = wall.pillar.p.x - pos.x;
	diff.y = wall.pillar.p.y - pos.y;
	diff2.x = wall.next->p.x - pos.x;
	diff2.y = wall.next->p.y - pos.y;
	coef_ang = tan(angle * PI180);
	printf("-WALL CLIPPING-\n");
	printf("angle coef: %f\n", coef_ang);
	fvct2_msg("diff pillar", diff);
	fvct2_msg("diff next", diff2);
	if (diff2.x - diff.x < 0.001 && diff2.x - diff.x > -0.001)
	{
		printf("!sans wall_coef\n");
		inter.x = diff.x;
		inter.y = diff.x * coef_ang;
		fvct2_msg("inter :", inter);
	}
	else
	{
		coef_wall = (diff2.y - diff.y) / (diff2.x - diff.x);
		b = diff.x * coef_wall + diff.y;
		inter.x = b / (coef_ang - coef_wall);
		inter.y = coef_wall * inter.x + b;
	}
	return (distance((t_fvct2){0.0, 0.0}, inter));
}
