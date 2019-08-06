#include "vector.h"

int				double_sup(double a, double b)
{
	//if (debug == 6)
	//	printf("comparaison a %f b %f res %d\n", a,b, a>b);
	return (a > b);
}

int				double_inf(double a, double b)
{
	return (a < b);
}

/*
**	recupere deux elements, les compare recupere celui qui est le plus coherant
**	compare le plus coherent a celui affecte
**	l'affecte si la coherence est plus haute
*/
void			dbl_cmp_affect2(double *affect, double b, double c, int (*cmp)(double, double))
{
	double		max_s;

	max_s = (cmp(b, c)) ? b : c;
	if (cmp(max_s, *affect))
		*affect = max_s;
}

void			dbl_cmp_affect(double *affect, double b, double c, int (*cmp)(double, double))
{
	*affect = (cmp(b, c)) ? b : c;
}

void			fvct2_cmp_affect(t_fvct2 *affect, t_fvct2 *b, t_fvct2 *c, int (*cmp)(double, double))
{
	dbl_cmp_affect(&affect->x, b->x, c->x, cmp);
	dbl_cmp_affect(&affect->y, b->y, c->y, cmp);
}

void			fvct2_cmp_affect2(t_fvct2 *affect, t_fvct2 *b, t_fvct2 *c, int (*cmp)(double, double))
{
	dbl_cmp_affect2(&affect->x, b->x, c->x, cmp);
	dbl_cmp_affect2(&affect->y, b->y, c->y, cmp);
}
