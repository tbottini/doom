#include "doom_nukem.h"

void		ft_putfloat(float num)
{
	int		i;

	i = 4;
	ft_putnbr((int)num);
	num = num - (int)num;
	ft_putchar('.');
	while (--i)
	{
		ft_putchar((int)(num * 10.0) + '0');
		num *= 10;
		num -= (int)num;
	}
}

void		fvct2_print(t_fvct2 vct)
{
	ft_putfloat(vct.x);
	ft_putchar(' ');
	ft_putfloat(vct.y);
}

void		sector_describe(t_sector sector)
{
	t_wl	*wall;

	ft_putstr("height floor : ");
	ft_putfloat(sector.h_floor);
	ft_putstr("\nheight ceil : ");
	ft_putfloat(sector.h_ceil);
	wall = NULL;
	while (!wall || wall->next != sector.root_wall)
	{
		if (wall == NULL)
			wall = sector.root_wall;
		else
			wall = wall->next;
		ft_putchar('\n');
		fvct2_print(wall->pos);
		ft_putstr(" to ");
		fvct2_print(wall->next->pos);
	}
	ft_putchar('\n');
}