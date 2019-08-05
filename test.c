#include <math.h>
#include <stdio.h>

int main()
{
	double		res;
	double		angle;

	angle = 30;
	double angle2 = 60;

	angle = angle * M_PI / 180;
	angle2 = angle2 * M_PI / 180;

	double x = 1;
	double y = 0;

	//x = (cos(angle) * x - sin(angle) * y);
	//y = (sin(angle) * x + cos(angle) * y);

	//printf(".x %f .y %f\n", x, y)

	y = (sin(angle2) * (cos(angle) * x - sin(angle) * y))
		+ (cos(angle2) * (sin(angle * x + cos(angle) * y)));


	printf("y %f\n", y);
	return (0);
}