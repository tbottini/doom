#include <stdio.h>
#include <stdlib.h>

typedef struct	s_fvct2
{
	double		x;
	double		y;
}				t_fvct2;

typedef struct  s_fvct3
{
	double		x;
	double		y;
	double		z;
}				t_fvct3;

typedef struct	s_triangle
{
	t_fvct2		v0;
	t_fvct2		v1;
	t_fvct2		v2;
}				t_triangle;

double	cross_product(t_fvct2 *origin, t_fvct2 *vct1, t_fvct2 *vct2)
{
	double		tmp;

	tmp = (vct2->x - origin->x) * (vct1->y - origin->y);
	tmp -= (vct2->y - origin->y) * (vct1->x - origin->x);
	return (tmp);
}

t_fvct3	*barycentrique_coord(t_fvct3 *barycentr, double area, t_fvct3 *normal)
{
	barycentr->x = normal->y / area;
	barycentr->y = normal->z / area;
	barycentr->z = normal->x / area;
	return (barycentr);
}

int main(int ac, char **av)
{
	t_triangle	primary;
	t_fvct3		barycentr;
	t_fvct3		normal;
	t_fvct2		p;
	int			inprimary;
	double		area;

	if (ac < 3)
	{
		printf("ac < 3\n");
		return (0);
	}
	primary.v0 = (t_fvct2){2, 2};
	primary.v1 = (t_fvct2){6, 5};
	primary.v2 = (t_fvct2){7, 1};

	p.x = atoi(av[1]);
	p.y = atoi(av[2]);

	normal.x = cross_product(&primary.v0, &primary.v1, &p);
	normal.y = cross_product(&primary.v1, &primary.v2, &p);
	normal.z = cross_product(&primary.v2, &primary.v0, &p);

	inprimary = (normal.x >= 0) + (normal.y >= 0) + (normal.z >= 0);

	printf("cross product res %f %f %f\n", normal.x, normal.y, normal.z);

	if (inprimary == 3 || inprimary == 0)
	{
		printf("point in primary\n");
		area = cross_product(&primary.v0, &primary.v1, &primary.v2);
		printf("area*2 triangle res %f\n", area);
		barycentrique_coord(&barycentr, area, &normal);
		printf("barycentr coord %f %f %f\n", barycentr.x, barycentr.y, barycentr.z);
	}
	else
	{
		printf("point out primary %d\n", inprimary);
	}
	return (0);
}
