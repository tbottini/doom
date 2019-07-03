#include "doom_nukem.h"

int			on_frustum(t_arch *arch, t_player *player, t_pillar *pillar)
{
	t_fvct2	dist;
	double	angle;

	dist.x = pillar->p.x - player->stat.pos.x;
	dist.y = pillar->p.y - player->stat.pos.y;
	angle = atan2(dist.y, dist.x) * TOANGLE;
	if (angle < 0)
		angle = 360 + angle;
	angle = double_modulo(angle - player->stat.rot.y);
	if (angle < -180)
		angle += 360;
	else if (angle > 180)
		angle -= 360;
	pillar->angle = angle;

	//!!!<---- ajout des bornes

	//if (angle >= -player.fov / 2.0 && angle <= player.fov / 2.0)
	if (angle >= arch->borne.y && angle <= arch->borne.x)
		pillar->frust = 1;
	else
		pillar->frust = 0;
	return (pillar->frust);
}

void		sector_frustum(t_arch *arch, t_sector *sector, t_player *player)
{
	int		i;

	i = 0;
	while (i < sector->len)
	{
		on_frustum(arch, player, &sector->wall[i].pillar);
		i++;
	}
}

/*
**	renvoie l'angle entre un pillier -> joueur -> pillier_next
*/
double		wall_angle_pers(t_arch *arch, t_wall wall)
{
	double	field;
	t_fvct2	angles;

	if (arch->borne.x * arch->borne.y > 0)
		return (0);
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
**	prend une autre reference pour les angles : ex
**	la reference est la rotation du joueur ce qui est a gauche + a droite -
**	ca sera utilise pour les borne de la fenetre
*/
double		local_angle(double borne, double angle)
{
	angle = angle - borne;
	if (angle < 0)
		angle += 360;
	return (angle);
}


/*
**	fonction a utiliser pour les bornes si il n'y a aucun pillier dans le frustum
**	determine si les bornes sont entre les angles des mur
*/
int			borne_in_wall_angle(t_arch *arch, t_wall *wall)
{
	t_fvct2	angles;

	angles.x = local_angle(arch->borne.x, wall->pillar.angle);
	angles.y = local_angle(arch->borne.x, wall->next->angle);
	return ((fabs(angles.y - angles.x) > 180.0));
}

/*
**	buncherisation mets les murs visible d'un secteur dans une liste
**		un mur est visible si l'un des pillier est dans le frustrum ou
**		ou si l'angle mur joueur est plus grand que le joueur (les pillier depasse mais passe
**											devant le joueur)
**	i_wall correspond a l'index des mur parcourus
**	i_bunch est l'index dans le bunch
*/
int			buncherisation(t_arch *arch, t_sector sector, t_wall **bunch)
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
			//printf("wall frustum\n");
		}
		else if (borne_in_wall_angle(arch, &wall[i_wall]))
		{
			//printf("wall borne\n");
			bunch[i_bunch] = &wall[i_wall];
			i_bunch++;
		}
		i_wall++;
	}
	//printf("passage %d\n", i);
	//i = 0;
	//printf("%d\n", i_bunch);
	bunch[i_bunch] = NULL;
	return (1);
}

void		bunch_comsuption(t_doom *doom, t_wall **bunch, t_sector *sector)
{
	int		i;

	i = 0;
	doom->arch.sector = sector;
	while (bunch[i] != NULL)
	{
		doom->arch.wall = bunch[i];
		render_wall(&doom->arch, &doom->player);
		i++;
	}
}
