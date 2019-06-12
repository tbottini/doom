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
	fvct3_msg("Pos", player.stat.pos);
	fvct3_msg("Vel", player.stat.vel);
	double_msg("Height", player.stat.height);
	printf("Rot : %f\t%f\n", player.stat.rot.x, player.stat.rot.y);
	printf("Fov : %d\n", player.fov);
	printf("Speed : %f\n", player.stat.speed);
	ft_putendl("------------------");
}

void		describe_wall(t_wall wall)
{
	printf("pillar %f %f ang %f\nnext %f %f ang %f\n",
		wall.pillar.p.x, wall.pillar.p.y, wall.pillar.angle,
		wall.next->p.x, wall.next->p.y, wall.next->angle);

}

void		ft_putnchar(char c, int i)
{
	while (--i != -1)
		ft_putchar(c);
}

void		describe_sub_sector(t_sector sector, int sub)
{
	int		i;
	t_wall	*wall;
	t_pillar	a;
	i = 0;
	ft_putnchar('\t', sub);
	ft_putendl("-------sector-------");
	ft_putnchar('\t', sub);
	double_msg("height floor :", sector.h_floor);
	ft_putnchar('\t', sub);
	double_msg("height ceil :", sector.h_ceil);
	ft_putnchar('\t', sub);
	int_msg("son sector :", sector.len_sub);
	wall = sector.wall;
	while (i < sector.len)
	{
		ft_putnchar('\t', sub);
		fvct2_print(*(t_fvct2*)&sector.wall[i].pillar);
		ft_putstr(" --> ");
		a = *sector.wall[i].next;
		fvct2_print(*(t_fvct2*)&a);
		ft_putchar('\n');
		i++;
	}
}

void		sector_recursif(t_sector sector, int sub)
{
	int		i;

	i = 0;

	describe_sub_sector(sector, sub);
	if (sector.len_sub)
	{
		ft_putnchar('\t', sub);
		ft_putendl("--->son");
	}
	while (i < sector.len_sub)
	{
		sector_recursif(sector.ssector[i], sub + 1);
		++i;
	}
	ft_putnchar('\t', sub);
	ft_putendl("--------------------");
}

void		describe_sector_recursif(t_sector sector)
{
	printf("\e[31m\e[1m=============sector_recursivite===============\033[0m\n");
	sector_recursif(sector, 0);
	printf("\e[31m\e[1m==============================================\033[0m\n");
}
