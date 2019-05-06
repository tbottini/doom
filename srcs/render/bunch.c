#include "doom_nukem.h"

//on peut voir si un point est dans le frustum

int			on_frustum(t_player player, t_wl *wall)
{
	t_fvct2	dist;
	float	angle;

	dist.x = wall->pos.x - player.pos.x;
	dist.y = wall->pos.y - player.pos.y;
	angle = atan2(dist.y, dist.x) * TOANGLE;
	if (angle < 0)
		angle = 360 + angle;
	angle = (angle - player.rot.y);
	angle = double_modulo(angle);
	if (angle < -180)
		angle += 360;
	else if (angle > 180)
		angle -= 360;
	printf("x %f y %f angle %f\n", wall->pos.x, wall->pos.y, angle);

	wall->angle = angle;
	//if (angle < -180)
	//	angle = 360 + angle;
	wall->frust = (angle >= -player.fov / 2.0 && angle <= player.fov / 2.0) ? 1 : 0;
	return (wall->frust);
}

void		wall_frustum(t_wl *root, t_player player)
{
	t_wl	*wall;

	wall = root->next;
	while (wall != root)
	{
		on_frustum(player, wall);
		wall = wall->next;
	}
	on_frustum(player, wall);
}

t_wl		*root_draw(t_sector sector)
{
	t_wl	*wall;
	int		i;

	i = 0;
	wall = sector.root_wall;
	while ((wall->frust || !wall->next->frust) && i < sector.len)
	{
		wall = wall->next;
		i++;
	}
	return (wall);
}

/*
**buncherisation mets les murs affichable d'un secteur dans une liste
**i_wall correspond a l'index des mur parcourus
**i_bunch est l'index dans le bunch
*/
int			buncherisation(t_sector sector, t_wl **bunch)
{
	int 	i_wall;
	int		i_bunch;
	t_wl	*wall;

	i_bunch = 0;
	i_wall = 0;
	wall = root_draw(sector);
	while (i_wall < sector.len)
	{
		if (wall->next->frust)
		{
			bunch[i_bunch] = wall;
			i_bunch++;
		}
		else if (wall->frust)
		{
			bunch[i_bunch] = wall;
			bunch[i_bunch + 1] = wall->next;
			i_bunch += 2;
			i_wall++;
			wall = wall->next;
		}
		i_wall++;
		wall = wall->next;
	}
	bunch[i_bunch] = NULL;
	return (1);
}

void		bunch_comsuption(t_doom *doom, t_player player, t_wl **bunch)
{
	int		px;
	int		i;

	i = 0;
	describe_bunch(bunch);
	while (bunch[i] != NULL)
	{
		printf("bunch angle %f %d\n", bunch[i]->angle, bunch[i]->frust);

		if (i == 0 && bunch[i]->frust == 0)
			px = doom->sdl.size.x - 1;
		else if (!bunch[i + 1] && bunch[i]->frust == 0)
			px = 0;
		else
			px = ((float)(doom->sdl.size.x - 1) / 2.0) - (float)(doom->sdl.size.x) / player.fov * bunch[i]->angle;
		draw_wall(*doom, px, dist(player.pos, bunch[i]->pos));
		i++;
	}
}

void		portal_engine(t_doom *doom)
{
	t_wl	*bunch[50];

	ft_bzero(doom->sdl.screen, doom->sdl.size.x * doom->sdl.size.y * 4);
	wall_frustum(doom->sector->root_wall, doom->player);
	buncherisation(*doom->sector, bunch);
	bunch_comsuption(doom, doom->player, bunch);
	sdl_present(&doom->sdl);
}
