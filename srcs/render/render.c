#include "doom_nukem.h"

//une liste de wall


//on peut voir si un point est dans le frustum
int		on_frustum(t_player player, t_fvct2 point)
{
	t_fvct2	dist;
	float	diff;

	dist.x = point.x - player.pos.x;
	dist.y = point.y - player.pos.y;
	diff = atan2(dist.y, dist.x) * TOANGLE;
	if (diff < 0)
		diff = 360 + diff;
	diff = diff - player.rot.y + (player.fov / 2.0);
	diff = double_modulo(diff);
	if (diff > 0 && diff < player.fov)
		return (1);
	else
	{
		printf("angle dif %f\n", diff);
		return (0);
	}
}

//on determine tous les point du secteur qui sont dans le frustum
//on recupere le point
int		buncherisation(t_player player, t_sector sector, t_wl **bunch)
{
	int 	i;
	t_wl	*wall;

	i = 0;
	wall = sector.root_wall;
	while (wall != sector.root_wall || !i)
	{
		if (on_frustum(player, wall->next->pos))
		{
			//ajouter le fait d'ajouter les deux point si
			//il le prochain mur est dans frustum
			//pblm un mur next si il n'est pas dans le frustum
			//mais qu'un mur qu'il est est liee avec lui
			//alors ce mur hors du frustum ne sera pas ajoute
			//alors alors qu'il est liee
			//si le prochain mur est dans le frustum alors il faut
			//ajouter le prochain directement


			//mais il faut pas que ca boucle a l'infinie
			//et qu'il s'arrete bien a la derniere boucle
			bunch[i] = wall;
			bunch[i + 1] = wall->next;
			printf("add wall to bunch\n");
			i++;
		}
		else if (on_frustum(player, wall->pos))
		{
			bunch[i] = wall;
			printf("add wall to bunch\n");
			i++;
		}
		wall = wall->next;
	}
	bunch[i] = NULL;
	return (1);
}

void		describe_bunch(t_wl **bunch)
{
	int		i;

	i = 0;
	while (bunch[i] != NULL)
	{
		fvct2_msg("pt", bunch[i]->pos);
		i++;
	}
}

void		bunch_comsuption(t_player player, t_wl *bunch)
{
	int		i;
	int		px;
	t_fvct2	dist;
	float	angle;

	dist.x = bunch->pos.x - player.pos.x;
	dist.y = bunch->pos.y - player.pos.y;
	angle = atan2(dist.y, dist.x) * TOANGLE;
	if (angle < 0)
		angle += 360;
	angle = double_modulo(angle);
	px = 1920.0 / player.fov * angle;
	printf("px %d\n", px);
}

void		portal_engine(t_player player, t_sector *sector)
{
	t_wl	*bunch[50];

	t_fvct2 test;
	test.x = 2.0;
	test.y = 0.0;
	buncherisation(player, *sector, bunch);
	//on_frustum(player, test);
	describe_bunch(bunch);
	bunch_comsuption(player, bunch[1]);
	//player_to_point(player, sector->root_wall->next->next->pos);
}
