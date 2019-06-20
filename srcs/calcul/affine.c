#include "calcul.h"

double			affine_val(t_affine affine, int x)
{
	return (affine.a * x + affine.b);
}

/*
**	renvoie l'intersection des deux droite affine
*/
t_fvct2			interpolation_linear(t_affine d1, t_affine d2)
{
	t_fvct2		inter;

	inter.x = (d2.b - d1.b) / (d1.a - d2.a);
	inter.y = affine_val(d1, inter.x);
	return (inter);
}

t_affine		affine_points(t_fvct2 point1, t_fvct2 point2)
{
	t_affine	fct;

	fct.a = (point2.y - point1.y) / (point2.x - point1.x);
	fct.b = point1.y - fct.a * point1.x;
	return (fct);
}

t_affine		affine_def(double a, double b)
{
	return ((t_affine){a, b});
}
