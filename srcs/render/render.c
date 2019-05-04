#include "doom_nukem.h"

//on peut voir si un point est dans le frustum

int			on_frustum(t_player player, t_wl *wall)
{
	t_fvct2	dist;
	float	diff;

	dist.x = wall->pos.x - player.pos.x;
	dist.y = wall->pos.y - player.pos.y;
	diff = atan2(dist.y, dist.x) * TOANGLE;
	if (diff < 0)
		diff = 360 + diff;
	diff = (diff - player.rot.y);
	diff = double_modulo(diff);
	printf("diff %f\n", diff);
	wall->angle = diff;
	wall->frust = (diff >= -player.fov / 2.0 && diff <= player.fov / 2.0) ? 1 : 0;
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

/*
**buncherisation mets les murs affichable d'un secteur dans une liste
**i_wall correspond a l'index des mur parcourus
**i_bunch est l'index dans le bunch
*/
int			buncherisation(t_player player, t_sector sector, t_wl **bunch)
{
	int 	i_wall;
	int		i_bunch;
	t_wl	*wall;
	t_vct2	ret;

	i_bunch = 0;
	i_wall = 0;
	wall = sector.root_wall;
	printf("sector len %d\n", sector.len);
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

void		bunch_comsuption(t_player player, t_wl **bunch)
{
	int		px;
	float	dist;
	int		i;

	i = 0;
	describe_bunch(bunch);
	while (bunch[i] != NULL)
	{
		if (i == 0 && bunch[i]->frust == 0)
			px = 1920;
		else if (!bunch[i + 1] && bunch[i]->frust == 0)
			px = 0;
		else
			px = (1920.0 / 2) - 1920.0 / player.fov * bunch[i]->angle;

		printf("%d\n", px);
		i++;
	}
}

void		portal_engine(t_player player, t_sector *sector)
{
	t_wl	*bunch[50];

	wall_frustum(sector->root_wall, player);
	buncherisation(player, *sector, bunch);
	bunch_comsuption(player, bunch);
	//wall_clipping(*bunch[0], player.pos, 180);
	//player_to_point(player, sector->root_wall->next->next->pos);
}
