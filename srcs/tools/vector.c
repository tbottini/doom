#include "vector.h"
#include <math.h>

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

t_fvct2			fvct2_rotation(t_fvct2 vector, double rotation)
{
	double		tmp_x;

	tmp_x = cos(rotation) * vector.x - sin(rotation) * vector.y;
	vector.y = sin(rotation) * vector.x + cos(rotation) * vector.y;
	vector.x = tmp_x;
	return (vector);
}

t_fvct2			fvct2_addition(t_fvct2 vector, t_fvct2 add)
{
	vector.x += add.x;
	vector.y += add.y;
	return (vector);
}

/*
**	angle en radian
**	on recupere un vecteur a partir de l'angle
*/
t_fvct2			fvct2_from_angle(double angle)
{
	t_fvct2		vector_dir;

	vector_dir.x = cos(angle);
	vector_dir.y = sin(angle);
	return (vector_dir);
}

double			fvct2_angle(t_fvct2 origin, t_fvct2 pos, double rot_origin)
{
	t_fvct2		dist;
	double		angle;

	dist.x = pos.x - origin.x;
	dist.y = pos.y - origin.y;
	angle = atan2(dist.y, dist.x) * TOANGLE;
	if (angle < 0)
		angle = 360 + angle;
	angle = double_modulo(angle - rot_origin);
	if (angle < -180)
		angle += 360;
	else if (angle > 180)
		angle -= 360;
	return (angle);
}
