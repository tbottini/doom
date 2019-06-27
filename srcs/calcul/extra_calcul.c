#include "calcul.h"
#include "math.h"

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