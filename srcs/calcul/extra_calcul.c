#include "vector.h"
#include <math.h>

double			coef_vct(t_fvct2 quantity, t_vct2 step)
{
	return ((quantity.y - quantity.x) / (step.y - step.x));
}

double			coef_diff(double diff, t_vct2 step)
{
	return (diff / (step.y - step.x));
}

double		coef_vct2(t_fvct2 value, t_fvct2 value2)
{
	double	res;

	res = ((value2.x - value.x) / (value2.y - value.y));
	return ((res == INFINITY) ? 0.0 : res);
}

void			fvct3_sub(t_fvct3 *vector_sub, t_fvct3 *vector_sub2)
{
	vector_sub->x -= vector_sub2->x;
	vector_sub->y -= vector_sub2->y;
	vector_sub->z -= vector_sub2->z;
}

void			fvct3_rotation(t_fvct3 *point, t_fvct2 rot)
{
	t_fvct3		tmp;

	rot.x = (rot.x - 90) * (M_PI / 180);
	rot.y = -rot.y * (M_PI / 180);

	tmp = *point;
	point->x = tmp.x * cos(rot.y) + tmp.y * sin(rot.y);
	point->y = tmp.x * -sin(rot.y) + tmp.y * cos(rot.y);
	tmp = *point;
	point->z = tmp.z * cos(rot.x) - tmp.y * sin(rot.x);
	point->y = tmp.z * sin(rot.x) + tmp.y * cos(rot.x);
}
