#include "doom_nukem.h"

int			on_frustum(t_player player, t_pillar *pillar)
{
	t_fvct2	dist;
	double	angle;

	dist.x = pillar->p.x - player.pos.x;
	dist.y = pillar->p.y - player.pos.y;
	angle = atan2(dist.y, dist.x) * TOANGLE;
	if (angle < 0)
		angle = 360 + angle;
	angle = double_modulo(angle - player.rot.y);
	if (angle < -180)
		angle += 360;
	else if (angle > 180)
		angle -= 360;
	pillar->angle = angle;
	if (angle >= -player.fov / 2.0 && angle <= player.fov / 2.0)
		pillar->frust = 1;
	else
		pillar->frust = 0;
	return (pillar->frust);
}

void		sector_frustum(t_sector *sector, t_player player)
{
	int		i;

	i = 0;
	while (i < sector->len)
	{
		on_frustum(player, &sector->wall[i].pillar);
		i++;
	}
}

double		wall_angle_pers(t_wall wall)
{
	double	field;
	t_fvct2	angles;

	angles.x = wall.pillar.angle;
	angles.y = wall.next->angle;
	if (wall.pillar.angle < 0)
		angles.x += 360;
	if (wall.next->angle < 0)
		angles.y += 360;
	field = fabs(angles.y - angles.x);
	return (field);
}

/*
**	buncherisation mets les murs affichable d'un secteur dans une liste
**	i_wall correspond a l'index des mur parcourus
**	i_bunch est l'index dans le bunch
*/
//si l'un des pillier du mur est dans le frustum alors on ajoute le mur

int			buncherisation(t_sector sector, t_wall **bunch)
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
			++i_bunch;
		}
		else if (wall_angle_pers(wall[i_wall]) > 180)
		{
			wall_angle_pers(wall[i_wall]);
			bunch[i_bunch] = &wall[i_wall];
			++i_bunch;
		}
		++i_wall;
	}
	bunch[i_bunch] = NULL;
	return (1);
}

void		bunch_comsuption(t_doom *doom, t_wall **bunch)
{
	int		i;

	i = 0;
	while (bunch[i] != NULL)
	{
		draw_wall(*doom, *bunch[i]);
		i++;
	}
}

void		portal_engine(t_doom *doom)
{
	t_wall	*bunch[50];

	sector_frustum(doom->sector, doom->player);
	buncherisation(*doom->sector, bunch);
	bunch_comsuption(doom, bunch);
	//minimap(doom);
	sdl_present(&doom->sdl);
}
