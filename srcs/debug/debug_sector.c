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
	int		i;
	t_wall	*wall;
	t_pillar	a;
	i = 0;
	ft_putendl("-------sector-------");
	ft_putstr("height floor : ");
	ft_putfloat(sector.h_floor);
	ft_putstr("\nheight ceil : ");
	ft_putfloat(sector.h_ceil);
	ft_putchar('\n');
	wall = sector.wall;
	while (i < sector.len)
	{
		fvct2_print(*(t_fvct2*)&sector.wall[i].pillar);
		ft_putstr(" --> ");
		a = *sector.wall[i].next;
		fvct2_print(*(t_fvct2*)&a);
		ft_putchar('\n');
		i++;
	}
	ft_putendl("--------------------");
}

void		describe_bunch(t_wall **bunch)
{
	int		i;
	t_pillar	a;
	i = 0;
	ft_putendl("----bunch----");
	while (bunch[i] != NULL)
	{
		ft_putchar(bunch[i]->pillar.frust + '0');
		ft_putchar(' ');
		fvct2_print(*(t_fvct2*)&bunch[i]->pillar);
		ft_putstr(" --> ");
		a = *bunch[i]->next;
		fvct2_print(*(t_fvct2*)&a);
		ft_putchar(' ');
		ft_putchar(bunch[i]->next->frust + '0');
		ft_putchar('\n');
		i++;
	}
	ft_putendl("-------------");
}

void		debug_player(t_player player)
{
	ft_putendl("------player------");
	printf("Player :\n");
	printf("Pos : %f\t%f\n", player.pos.x, player.pos.y);
	printf("Rot : %f\t%f\n", player.rot.x, player.rot.y);
	printf("Fov : %d\n", player.fov);
	ft_putendl("------------------");
}
