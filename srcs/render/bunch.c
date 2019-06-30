#include "doom_nukem.h"

int			on_frustum(t_designer *arch, t_player *player, t_pillar *pillar)
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

void		sector_frustum(t_designer *arch, t_sector *sector, t_player *player)
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
**	fonction a utiliser pour les bornes si il n'y a aucun pillier dans le frustum
**	determine si les bornes sont entre les angles des mur
*/
int			borne_in_wall_angle(t_designer *arch, t_wall *wall)
{
	int		polarite_left;
	int		polarite_right;
	t_fvct2	angles;
	t_fvct2	borne;

	angles.x = wall->pillar.angle;
	angles.y = wall->next->angle;
	borne.x = arch->borne.x;
	borne.y = arch->borne.y;
	if (arch->borne.x * arch->borne.y < 0)
		return (0);
	if (angles.x < 0)
		angles.x += 360;
	if (angles.y < 0)
		angles.y += 360;
	if (borne.x < 0)
		borne.x += 360;
	if (borne.y < 0)
		borne.y += 360;
	//si l'angle est superieur a la borne alors
	//l'angle est a gauche de la borne

	polarite_left = (angles.x > borne.x) ? 1 : -1;
	polarite_right = (angles.y < borne.y) ? 1 : -1;
	//if (polarite_left == polarite_right)
	//	printf("pillar %f borne %f next %f borne right %f\n", wall->pillar.angle, arch->borne.x, wall->next->angle, arch->borne.y);
	return ((polarite_left == polarite_right) ? 1 : 0);
	//on determine si l'angle de pillar est a droite ou a gauche du mur
	//si il est a gauche il faut verifier que le next est a droite de la borne droite
	//		si oui alors on renvoie un on ajoute le mur au bunch
	//si l'angle de pillar est a droite de la borne gauche alors l'angle de next
		//doit etre a gauche de l'angle de next
}

/*
**	buncherisation mets les murs visible d'un secteur dans une liste
**		un mur est visible si l'un des pillier est dans le frustrum ou
**		ou si l'angle mur joueur est plus grand que le joueur (les pillier depasse mais passe
**											devant le joueur)
**	i_wall correspond a l'index des mur parcourus
**	i_bunch est l'index dans le bunch
*/
int			buncherisation(t_designer *arch, t_sector sector, t_wall **bunch)
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
		else if (wall_angle_pers(wall[i_wall]) > 180)
		{
			bunch[i_bunch] = &wall[i_wall];
			i_bunch++;
		}
		else if (borne_in_wall_angle(arch, &wall[i_wall]))
		{
			printf("borne wall\n");
			bunch[i_bunch] = &wall[i_wall];
			i_bunch++;
		}
		//sinon si la borne est entre les angles de mur
		//else if ()
		i_wall++;
	}
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
