#include "wolf3d.h"


float		float_modulo(float num)
{
	return ((int)num % 360 + num - (int)num);
}

double		angle_adaptater(double angle)
{
	if (angle < 0.0)
		angle += 360;
	else if (angle > 360.0)
		angle = float_modulo(angle);
	return (angle);
}
