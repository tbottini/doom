#include "sector.h"
#include "debug.h"
#include "player.h"

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

void		describe_bunch(t_wall **bunch)
{
	int		i;
	t_pillar	a;

	i = 0;
	ft_putendl("----bunch----");
	while (bunch[i] != NULL)
	{
		ft_putchar(bunch[i]->pillar->frust + '0');
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
	ft_putendl(WBLUE"------player------"WEND);
	printf(WBLUE"Player "WEND":\n");
	fvct3_msg(WBLUE"Pos"WEND, player.stat.pos);
	fvct3_msg(WBLUE"Vel"WEND, player.stat.vel);
	double_msg(WBLUE"Height"WEND" :", player.stat.height);
	printf(WBLUE"Rot "WEND": %f\t%f\n", player.stat.rot.x, player.stat.rot.y);
	printf(WBLUE"Fov "WEND": %d\n", player.fov);
	printf(WBLUE"Speed "WEND": %f\n", player.stat.speed);
	ft_putendl(WBLUE"------------------"WEND);
}

void		describe_wall(t_wall wall)
{
	printf("pillar %.2f %.2f ang %.2f\nnext %.2f %.2f ang %f.2\n",
		wall.pillar->p.x, wall.pillar->p.y, wall.pillar->angle,
		wall.next->p.x, wall.next->p.y, wall.next->angle);

}

void		ft_putnchar(char c, int i)
{
	while (--i != -1)
		ft_putchar(c);
}

void		d_wall(t_wall *wall)
{
	printf(WBLUE"frust %d"WEND" %.2f %.2f -->, ", wall->pillar->frust, wall->pillar->p.x, wall->pillar->p.y);
	printf("%.2f %.2f "WBLUE"%d frust"WEND, wall->next->p.x, wall->next->p.y, wall->pillar->frust);
	if (wall->status == WALL)
		printf(WBLUE" WALL"WEND);
	else if (wall->status == PORTAL)
		printf(WGREEN" PORTAL"WEND);

	printf(" angle %f %f", wall->pillar->angle, wall->next->angle);
	printf("\n");

}

void		describe_sector(t_sector sector)
{
	int		i;
	t_wall	*wall;

	i = 0;
	ft_putstr(WGREY);
	ft_putnchar('\t', 1);
	ft_putendl("-------sector-------");
	ft_putnchar('\t', 1);
	double_msg("height floor :", sector.h_floor);
	ft_putnchar('\t', 1);
	double_msg("height ceil :", sector.h_ceil);
	ft_putnchar('\t', 1);
	int_msg("son sector :", sector.len_sub);
	wall = sector.wall;
	while (i < sector.len)
	{
		if (sector.wall[i].status == WALL)
			printf("WALL\t");
		else if (sector.wall[i].status == PORTAL)
		{
			ft_putstr(WYELLOW);
			printf("PORT\t");
		}
		else if (sector.wall[i].status == PORTAL)
			printf("PORD\t");
		else if (sector.wall[i].status == WINDOW)
			printf("WIND\t");
		ft_putnchar('\t', 1);
		printf("%.2f %.2f --> %.2f %.2f\n", sector.wall[i].pillar->p.x, sector.wall[i].pillar->p.y, sector.wall[i].next->p.x, sector.wall[i].next->p.y);
		if (sector.wall[i].status == PORTAL)
		{
			ft_putstr(WEND);
			ft_putstr(WGREY);
		}
		i++;
	}
	ft_putnchar('\t', 1);
	ft_putendl("--------------------");
	ft_putstr(WEND);
}

void		describe_sub_sector(t_sector sector, int sub)
{
	int		i;
	t_wall	*wall;

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
		if (sector.wall[i].status == WALL)
			printf("WALL\t");
		else if (sector.wall[i].status == PORTAL)
		{
			ft_putstr(WYELLOW);
			printf("PORT\t");
		}
		else if (sector.wall[i].status == PORTAL)
			printf("PORD\t");
		else if (sector.wall[i].status == WINDOW)
			printf("WIND\t");
		ft_putnchar('\t', sub);
		printf("%f %f --> %f %f\n", sector.wall[i].pillar->p.x, sector.wall[i].pillar->p.y, sector.wall[i].next->p.x, sector.wall[i].next->p.y);
		if (sector.wall[i].status == PORTAL)
		{
			ft_putstr(WEND);
			describe_sector(*sector.wall[i].link);
		}
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
		ft_putnchar('\t', sub );
		ft_putendl("--->son");
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

void	borne_print(t_borne *borne)
{
	printf("-------borne------\n");
	printf("left %f right %f\nportal: %f %f - %f %f\n", borne->b_left, borne->b_right,
		borne->pillar.x, borne->pillar.y,
		borne->next.x, borne->next.y);
	printf("------------------\n");
}
