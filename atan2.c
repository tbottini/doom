#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int ac, char **av)
{
	double		a, b;

	a = atof(av[1]);
	b = atof(av[2]);

	printf("atan2(): %f\n", atan2(a,b));
	return (0);
}
