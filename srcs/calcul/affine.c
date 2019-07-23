 #include "calcul.h"

double			affine_val(t_affine affine, double x)
{
	return (affine.a * x + affine.b);
}

double			affine_val_index(t_affine affine, double y)
{
	return ((y - affine.b) / affine.a);
}

/*
**	renvoie l'intersection des deux droite affine
**	si .a == -1 alors la fonction verticale
*/
t_fvct2			interpolation_linear(t_affine fct1, t_affine fct2)
{
	t_fvct2		inter;

	//if ((int)fct1.a == -1)
	//	inter.x = fct1.b;
	////else
	//si fct1.a == fct2.a && fct1.b != fct2.b
	//	erreur
	if (fct1.b == fct2.b)
		return ((t_fvct2){0, fct1.b});
	else if (fct1.a == fct2.a)
		return ((t_fvct2){0, 0});
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

t_affine		affine_points_secur(t_fvct2 point1, t_fvct2 point2)
{
	t_affine 	fct;

	fct.lock = (point1.x == point2.x);
	if (!fct.lock)
		fct.b = point1.x;
	else
	{
		fct.a = (point2.y - point1.y) / (point2.x - point1.x);
		fct.b = point1.y - fct.a * point1.x;
	}
	return (fct);
}

t_affine		affine_def(double a, double b)
{
	return ((t_affine){a, b, 0});
}


//gestion de l'affine lock sur une abscise
int				interpolation_linear_secur(t_affine affine1, t_affine affine2, t_fvct2 *inter)
{
	if (affine1.lock && affine2.lock)
		return (0);
	if (affine1.a == affine2.a)
		return (0);
	if (affine1.lock)
		*inter = (t_fvct2){affine1.b, affine_val(affine2, affine1.b)};
	else if (affine2.lock)
		*inter = (t_fvct2){affine2.b, affine_val(affine1, affine2.b)};
	else
	{
		inter->x = (affine2.b - affine1.b) / (affine1.a - affine2.a);
		inter->y = affine_val(affine2, inter->x);
	}
	return (0);
}

t_fvct2			inter(t_fvct2 p1, t_fvct2 p2, t_fvct2 p3, t_fvct2 p4)
{
	t_affine	a;
	t_affine	b;
	t_fvct2		inter;

	a = affine_points_secur(p1, p2);
	b = affine_points_secur(p3, p4);

	interpolation_linear_secur(a, b, &inter);
	return (inter);
}