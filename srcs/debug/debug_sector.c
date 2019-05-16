#include "doom_nukem.h"

void		ft_putnbr_msg(char *msg, int nb)
{
	ft_putstr(msg);
	ft_putstr(" : ");
	ft_putnbr(nb);
	ft_putchar('\n');
}

void		ft_putdouble(double num)
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

void		double_msg(char *msg, double num)
{
	ft_putstr(msg);
	ft_putchar(' ');
	ft_putdouble(num);
	ft_putchar('\n');
}

void		int_msg(char *msg, int num)
{
	ft_putstr(msg);
	ft_putchar(' ');
	ft_putnbr(num);
	ft_putchar('\n');
}

void		fvct2_print(t_fvct2 vct)
{
	ft_putdouble(vct.x);
	ft_putchar(' ');
	ft_putdouble(vct.y);
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
	double_msg("height floor :", sector.h_floor);
	double_msg("height ceil :", sector.h_ceil);
	int_msg("son sector :", sector.len_sub);
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

void		sector_recursif(t_sector sector)
{
	int		i;

	i = 0;
	sector_describe(sector);
	if (sector.len_sub)
		ft_putendl("|--->son");
	while (i < sector.len_sub)
	{
		sector_recursif(sector.ssector[i]);
		++i;
	}
}

void		describe_sector_recursif(t_sector sector)
{
	ft_putendl("---------sector_recursive--------");
	sector_recursif(sector);
	ft_putendl("---------------------------------");
}
