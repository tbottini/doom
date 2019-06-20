#include "calcul.h"

double			coef_vct(t_fvct2 quantity, t_vct2 step)
{
	return ((quantity.y - quantity.x) / (step.y - step.x));
}

double			coef_diff(double diff, t_vct2 step)
{
	return (diff / (step.y - step.x));
}