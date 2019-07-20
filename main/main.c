#include "doom_nukem.h"

int			main(int ac, char **av)
{
	t_affine a;


	a.a = atof(av[1]);
	a.b = atof(av[2]);

	t_fvct2	point;

	point.x = atof(av[3]);
	point.y = atof(av[4]);

	printf(WGREEN"affine %f %f point %f %f\n"WEND, a.a, a.b, point.x, point.y);
	printf("point behind portal %d\n", point_behind_portal(a, point));
	//test de l'interpolation

	return (0);
}
