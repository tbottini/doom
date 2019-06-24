#include "calcul.h"

double			affine_val(t_affine affine, int x)
{
	return (affine.a * x + affine.b);
}

/*
**	renvoie l'intersection des deux droite affine
<<<<<<< HEAD
**	si .a == -1 alors la fonction verticale
*/
t_fvct2			interpolation_linear(t_affine fct1, t_affine fct2)
{
	t_fvct2		inter;

	//if ((int)fct1.a == -1)
	//	inter.x = fct1.b;
	////else
		inter.x = (fct2.b - fct1.b) / (fct1.a - fct2.a);
	inter.y = affine_val(fct2, inter.x);
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
