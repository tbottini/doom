#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double		local_angle(double borne, double angle)
{
	angle = angle - borne;
	if (angle < 0)
		angle += 360;
	return (angle);
}

int main(int ac, char **av)
{
	int		px;
	double	d_screen;
	double	borne;

	px = atoi(av[1]);
	d_screen = 650.0;
	printf("px hauteur %f px %d screenmid %d\n", (1300/2.0) - px, px, 1300);
	borne = atan2((1300/2.0) - px, d_screen) * (180 / M_PI);
	printf("%f\n", borne);
}
