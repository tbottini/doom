#include "doom_nukem.h"

//on peut voir si un point est dans le frustum

int			on_frustum(t_player player, t_wall *wall)
{
	t_fvct2	dist;
	float	angle;

	dist.x = wall->pillar.x - player.pos.x;
	dist.y = wall->pillar.y - player.pos.y;
	angle = atan2(dist.y, dist.x) * TOANGLE;
	if (angle < 0)
		angle = 360 + angle;
	angle = (angle - player.rot.y);
	angle = double_modulo(angle);
	if (angle < -180)
		angle += 360;
	else if (angle > 180)
		angle -= 360;
	wall->angle = angle;
	wall->frust = (angle >= -player.fov / 2.0 && angle <= player.fov / 2.0) ? 1 : 0;
	return (wall->frust);
}

void		sector_frustum(t_sector *sector, t_player player)
{
	int		i;

	i = 0;
	while (i < sector->len)
	{
		on_frustum(player, &sector->wall[i]);
		i++;
	}
}

int			root_draw(t_sector sector)
{
	t_wall	*wall;
	int		i;

	i = 0;
	wall = sector.wall;
	while ((wall[i].frust || !wall[i + 1].frust) && i < sector.len)
		i++;
	return (i);
}

/*
**	buncherisation mets les murs affichable d'un secteur dans une liste
**	i_wall correspond a l'index des mur parcourus
**	i_bunch est l'index dans le bunch
*/
int			buncherisation(t_sector sector, t_wall **bunch)
{
	int 	i_wall;
	int		i_bunch;
	t_wall	*wall;

	i_bunch = 0;
	i_wall = 0;
	wall = sector.wall;
	while (i_wall < sector.len - 1)
	{
		if (wall[i_wall + 1].frust)
		{
			bunch[i_bunch] = &wall[i_wall];
			i_bunch++;
		}
		else if (wall->frust)
		{
			bunch[i_bunch] = &wall[i_wall];
			bunch[i_bunch + 1] = &wall[i_wall + 1];
			i_bunch += 2;
			i_wall++;
		}
		i_wall++;
	}
	if (wall[i_wall].frust)
	{
		bunch[i_bunch] = wall;
		i_bunch++;
	}
	bunch[i_bunch] = NULL;
	return (1);
}

void		bunch_comsuption(t_doom *doom, t_player player, t_wall **bunch)
{
	int		px;
	int		i;
	float	dist;

	i = 0;
	//describe_bunch(bunch);
	while (bunch[i] != NULL)
	{
		//printf("bunch angle %f %d\n", bunch[i]->angle, bunch[i]->frust);
		if (i == 0 && bunch[i]->frust == 0)
		{
			px = doom->sdl.size.x - 1;
			dist = wall_clipping(*bunch[i], *bunch[i + 1], player.pos, player.rot.y + player.fov / 2.0);
		}
		else if (!bunch[i + 1] && bunch[i]->frust == 0)
		{
			px = 0;
			dist = wall_clipping(*bunch[i], *bunch[i + 1], player.pos, player.rot.y - player.fov / 2.0);
		}
		else
		{
			px = ((float)(doom->sdl.size.x - 1) / 2.0) - (float)(doom->sdl.size.x) / player.fov * bunch[i]->angle;
			dist = distance(player.pos, bunch[i]->pillar);
		}
		draw_wall(*doom, px, dist);
		i++;
	}
}

void		portal_engine(t_doom *doom)
{
	t_wall	*bunch[50];

	ft_bzero(doom->sdl.screen, doom->sdl.size.x * doom->sdl.size.y * 4);
	sector_frustum(doom->sector, doom->player);
	buncherisation(*doom->sector, bunch);
	describe_bunch(bunch);
	//bunch_comsuption(doom, doom->player, bunch);
	sdl_present(&doom->sdl);
}
