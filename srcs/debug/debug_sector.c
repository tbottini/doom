#include "doom_nukem.h"

void		ft_putnbr_msg(char *msg, int nb)
{
	ft_putstr(msg);
	ft_putstr(" : ");
	ft_putnbr(nb);
	ft_putchar('\n');
}

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

void		fvct2_msg(char *msg, t_fvct2 vct)
{
	ft_putstr(msg);
	ft_putstr(" : ");
	fvct2_print(vct);
	ft_putchar('\n');
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
	}
	ft_putchar('\n');
}

void		describe_bunch(t_wl **bunch)
{
	int		i;

	i = 0;
	while (bunch[i] != NULL)
	{
		ft_putchar(bunch[i]->frust +'0');
		fvct2_msg(" pt", bunch[i]->pos);
		i++;
	}
}

void		debug_player(t_player player)
{
	ft_putendl("------player------");
	fvct2_msg("pos", player.pos);
	fvct2_msg("rot", player.rot);
	ft_putnbr_msg("fov", player.fov);
	ft_putendl("------------------");
}