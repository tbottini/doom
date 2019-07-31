#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_fvct3
{
	double x,y,z;
}		t_fvct3;

typedef struct s_fvct2
{
	double x,y;
}		t_fvct2;

int				main(int ac, char **av)
{
	t_fvct3		point;
	t_fvct2		rot;

	point = (t_fvct3){atof(av[1]), atof(av[2]), atof(av[3])};
	rot = (t_fvct2){atof(av[4]) * (M_PI / 180.0), atof(av[5]) * (M_PI / 180.0)};


	t_fvct2		wall_angle;
	t_fvct2		distance;

	printf("point .x %f .y %f .z %f\n---> rotx %f roty %f\n",point.x,point.y,point.z,
		rot.x / (M_PI/180.0), rot.y / (M_PI/180.0));

	//on recupere les rotation a faire sur le point
	t_fvct3	tmp;
	tmp = point;
	point.x = tmp.x * cos(rot.y) + tmp.z * sin(rot.y);
	point.z = tmp.x * -sin(rot.y) + tmp.z * cos(rot.y);
	tmp = point;
	point.y = tmp.y * cos(rot.x) - tmp.z * sin(rot.x);
	point.z = tmp.y * sin(rot.x) + tmp.z * cos(rot.x);
	printf("point .x %f .y %f .z%f\n", point.x, point.y, point.z);

	return (0);
}