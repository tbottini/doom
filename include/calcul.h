#include "vector.h"

typedef struct	s_affine
{
	double		a;
	double		b;
}				t_affine;

/*
**	coef
*/
double			coef_vct(t_fvct2 quantity, t_vct2 step);
double			coef_diff(double diff, t_vct2 step);

/*
**	affine fonctions
*/
double			affine_val(t_affine affine, int x);
t_fvct2			interpolation_linear(t_affine d1, t_affine d2);
t_affine		affine_points(t_fvct2 point1, t_fvct2 point2);
t_affine		affine_def(double a, double b);
