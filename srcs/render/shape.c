#include "render.h"

static void		swap(t_fvct2 *elem, t_fvct2 *elem2)
{
	t_fvct2		tmp;

	tmp = *elem;
	*elem = *elem2;
	*elem2 = tmp;
}

/*
**	bubble sort fvct2
*/
void			fvct2_sort_bubble(t_fvct2 *tab, int len)
{
	int			i;
	int			sort;
	t_fvct2		tmp;

	sort = 0;
	while (!sort)
	{
		i = 0;
		sort = 1;
		while (i + 1 < len)
		{
			if (tab[i].y > tab[i + 1].y)
			{
				swap(&tab[i], &tab[i + 1]);
				sort = 0;
			}
			else if (tab[i].y == tab[i + 1].y && tab[i].x > tab[i + 1].x)
			{
				swap(&tab[i], &tab[i + 1]);
				sort = 0;
			}
			i++;
		}
	}
}

/*
**	sort as tab fvct2, tab[0]=up, tab[3]=bot, verify left and right
*/
t_shape			shape_reajust(t_fvct2 a, t_fvct2 b, t_fvct2 c, t_fvct2 d)
{
	t_shape		shape;

	shape.up = a;
	shape.bot = d;
	shape.left = b;
	shape.right = c;
	fvct2_sort_bubble((t_fvct2*)&shape, 4);
	if (shape.left.x > shape.right.x)
		swap(&shape.left, &shape.right);
	return (shape);
}