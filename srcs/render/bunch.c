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
	wall->pillar.frust = (angle >= -player.fov / 2.0 && angle <= player.fov / 2.0) ? 1 : 0;
	return (wall->pillar.frust);
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

/*
**	buncherisation mets les murs affichable d'un secteur dans une liste
**	i_wall correspond a l'index des mur parcourus
**	i_bunch est l'index dans le bunch
*/

//si l'un des pillier du mur est dans le frustum alors on ajoute le mur

int			buncherisation2(t_sector sector, t_wall **bunch)
{
	int		i_wall;
	int		i_bunch;
	t_wall	*wall;

	i_bunch = 0;
	i_wall = 0;
	wall = sector.wall;
	while (i_wall < sector.len)
	{
		if (wall[i_wall].pillar.frust || wall[i_wall].next->frust)
		{
			bunch[i_bunch] = &wall[i_wall];
			i_bunch++;
		}
		i_wall++;
	}
	bunch[i_bunch] = NULL;
	return (1);
}

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
		if (wall[i_wall + 1].pillar.frust)
		{
			bunch[i_bunch] = &wall[i_wall];
			i_bunch++;
		}
		else if (wall[i_wall].pillar.frust)
		{
			bunch[i_bunch] = &wall[i_wall];
			bunch[i_bunch + 1] = &wall[i_wall + 1];
			i_bunch += 2;
			i_wall++;
		}
		i_wall++;
	}
	if (wall[0].pillar.frust)
	{
		bunch[i_bunch] = &wall[i_wall];
		i_bunch++;
	}
	else if (wall[i_wall].pillar.frust && i_wall < sector.len)
	{
		bunch[i_bunch] = &wall[i_wall];
		bunch[i_bunch + 1] = &wall[0];
		i_bunch += 2;
	}
	bunch[i_bunch] = NULL;
	return (1);
}

void		bunch_comsuption(t_doom *doom, t_player player, t_wall **bunch)
{
	int		i;

	i = 0;
	while (bunch[i + 1] != NULL)
	{

		i++;
	}
}

void		portal_engine(t_doom *doom)
{
	t_wall	*bunch[50];

	ft_bzero(doom->sdl.screen, doom->sdl.size.x * doom->sdl.size.y * 4);
	sector_frustum(doom->sector, doom->player);
	//buncherisation(*doom->sector, bunch);
	buncherisation2(*doom->sector, bunch);
	describe_bunch(bunch);
	bunch_comsuption(doom, doom->player, bunch);
	minimap(doom);
	sdl_present(&doom->sdl);
}
