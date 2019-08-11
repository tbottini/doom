#include "render.h"
#include "debug.h"

void				prop_init(t_prop *prop)
{
	double			hyp;

	hyp = sqrt(prop->pos.x * prop->pos.x + prop->pos.y * prop->pos.y);
	prop->left.x = (hyp - 0.5) / hyp * prop->pos.x;
	prop->left.y = (hyp - 0.5) / hyp * prop->pos.y;
	prop->right.x = (hyp + 0.5) / hyp * prop->pos.x;
	prop->right.y = (hyp + 0.5) / hyp * prop->pos.y;
	printf("left %f %f right %f %f\n", prop->left.x, prop->left.y, prop->right.x, prop->right.y);
}

void				prop_iter(t_prop *prop, int len, void(*prop_iter)(t_prop*))
{
	int				i;

	i = 0;
	while (i < len)
	{
		prop_iter(&prop[i]);
		i++;
	}
}
