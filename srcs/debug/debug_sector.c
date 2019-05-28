#include "doom_nukem.h"

void		ft_putnbr_msg(char *msg, int nb)
{
	ft_putstr(msg);
	ft_putstr(" : ");
	ft_putnbr(nb);
	ft_putchar('\n');
}

void		int_msg(char *msg, int num)
{
	ft_putstr(msg);
	ft_putchar(' ');
	ft_putnbr(num);
	ft_putchar('\n');
}

void		describe_sector(t_sector sector)
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

void		describe_player(t_player player)
{
	ft_putendl("------player------");
	printf("Player :\n");
	fvct3_msg("Pos", player.pos);
	fvct3_msg("Vel", player.vel);
	printf("Rot : %f\t%f\n", player.rot.x, player.rot.y);
	printf("Fov : %d\n", player.fov);
	ft_putendl("------------------");
}

void		describe_wall(t_wall wall)
{
	fvct2_msg("pillar", wall.pillar.p);
	fvct2_msg("next", wall.next->p);
}

void		sector_recursif(t_sector sector)
{
	int		i;

	i = 0;
	describe_sector(sector);
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
