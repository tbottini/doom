#include <math.h>
#include <stdio.h>
#include "vector.h"

int main()
{
	t_fvct2			wall_vct;
	double			hyp;
	double			coef;



	//wall_vct.x = (prop->wall->next.x - prop->wall->pillar.x);
	//wall_vct.y = (prop->wall->next.y - prop->wall->pillar.y);

	wall_vct.x = 5;
	wall_vct.y = 0;

	t_fvct2 pos;

	pos.x = 2.5;
	pos.y = 0;


	t_fvct2			left;
	t_fvct2			right;

	//if (wall_vct.x == 0)
	//{
	//	left = (t_fvct2){pos.x, pos.y - 0.5};
	//	right = (t_fvct2){pos.x, pos.y + 0.5};
	//}


	/*
	coef = wall_vct.y / wall_vct.x;
	hyp = sqrt(pos.x * pos.x + pos.y * pos.y);
	left.x = (hyp - 0.5) / (hyp) * pos.x;
	left.y = left.x * coef;
	right.x = (hyp + 0.5) / (hyp) * pos.x;
	right.y = right.x * coef;
	*/

	hyp = sqrt(pos.x * pos.x + pos.y * pos.y);
	left.x = (hyp - 0.5) / hyp * pos.x;
	left.y = (hyp - 0.5) / hyp * pos.y;
	right.x = (hyp + 0.5) / hyp * pos.x;
	right.y = (hyp + 0.5) / hyp * pos.y;
	printf("left %f %f right %f %f\n", left.x, left.y, right.x, right.y);


	//printf("r %f %f l %f %f\n", right.x, right.y, left.x, left.y);
	return (0);
}