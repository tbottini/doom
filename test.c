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
	double	angle_pillar;
	double	angle_next;
	int		polarite;
	double	borne_l;
	double	borne_r;

	borne_r = atof(av[1]);
	angle_pillar = atof(av[2]);
	angle_next = atof(av[3]);
	printf("borne 0 %f\npillar %f next %f\n", borne_r, angle_pillar, angle_next);
	if (angle_pillar < borne_r - 180)
		polarite = 0;
	else if (angle_pillar > 180)
		polarite = 1;
	else if (fabs(angle_pillar - angle_next) > 180)
		polarite = 0;
	else
		polarite = 1;
	printf("%s\n", (polarite == 1) ? "droite" : "gauche");
	return (0);
}
