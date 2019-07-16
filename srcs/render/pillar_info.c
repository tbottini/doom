#include <doom_nukem.h>

/*
**	si au moins l'un des pilier est hors frustum il passe pas l'extremite de
**	l'ecran, on determine laquelle avec une polarite (-1 == 0px et 1 == max)
**	si l'angle entre le joueur est les deux pillier est superieur a 180
**	la polarite de depart (position du premier pillier) s'inverse
*/
void		px_polarite(t_arch *arch)
{
	t_fvct2	angle;
	double	diff;
	int		polarite;

	angle.x = local_angle(arch->bound.b_left, arch->wall->pillar->angle);
	angle.y = local_angle(arch->bound.b_left, arch->wall->next->angle);

	diff = fabs(angle.x - angle.y);
	polarite = (arch->wall->next->angle > arch->bound.b_left ? -1 : 1) * (diff < 180 ? 1 : -1);
	arch->px.x = (polarite == -1) ? 0 : arch->sdl->size.x -1;
	arch->px.y = arch->sdl->size.x - 1 - arch->px.x;
}

int			pillar_polarite(t_arch *arch, t_pillar *pillar, t_pillar *next)
{
	double	angle;
	double	angle_next;
	double	borne;

	angle = local_angle(arch->bound.b_left, pillar->angle);
	angle_next = local_angle(arch->bound.b_left, next->angle);
	borne = local_angle(arch->bound.b_left, arch->bound.b_right);


	if (angle < borne - 180)
		return (0);
	else if (angle > 180)
		return (arch->sdl->size.x - 1);
	else if (fabs(angle - angle_next) > 180)
		return (0);
	else
		return (arch->sdl->size.x - 1);
}


void			pillar_screen_info(t_arch *arch, t_player *p)
{
	float		angle;
	int			size;
	t_fvct2		tmp;

	size = arch->sdl->size.x;
	if (arch->wall->pillar->frust)
	{
		arch->px.x = fish_bowl_px(arch, *arch->wall->pillar);
		arch->depth.x = distance(*(t_fvct2*)&p->stat.pos, arch->wall->pillar->p);
		arch->decal.x = sin(arch->wall->pillar->angle * PI180) * arch->depth.x;
		arch->depth.x = cos(arch->wall->pillar->angle * PI180) * arch->depth.x;
		arch->shift_txtr.x = 1;
	}
	else
	{
		arch->px.x = pillar_polarite(arch, arch->wall->pillar, arch->wall->next);
		if (arch->px.x == 0)
		{
			arch->px.x = arch->sdl->size.x / 2.0 - (tan(arch->bound.b_left * PI180) * arch->cam->d_screen);
			angle = p->stat.rot.y + arch->bound.b_left;
		}
		else
		{
			arch->px.x = arch->sdl->size.x / 2.0 - (tan(arch->bound.b_right * PI180) * arch->cam->d_screen);
			angle = p->stat.rot.y + arch->bound.b_right;
		}
		arch->shift_txtr.x = wall_clipping(arch, p, &tmp, angle);
		arch->depth.x = tmp.x;
		arch->decal.x = tmp.y;
	}
	if (arch->wall->next->frust)
	{
		arch->px.y = fish_bowl_px(arch, *arch->wall->next);
		arch->depth.y = distance(*(t_fvct2*)&p->stat.pos, arch->wall->next->p);
		arch->decal.y = sin(arch->wall->next->angle * PI180) * arch->depth.y;
		arch->depth.y = cos(arch->wall->next->angle * PI180) * arch->depth.y;
		arch->shift_txtr.y = 0;
	}
	else
	{
		arch->px.y = pillar_polarite(arch, arch->wall->next, arch->wall->pillar);
		if (arch->px.y == 0)
		{
			arch->px.y = arch->sdl->size.x / 2.0 - (tan(arch->bound.b_left * PI180) * arch->cam->d_screen);
			angle = p->stat.rot.y + arch->bound.b_left;
		}
		else
		{
			arch->px.y = arch->sdl->size.x / 2.0 - (tan(arch->bound.b_right * PI180) * arch->cam->d_screen);
			angle = p->stat.rot.y + arch->bound.b_right;
		}
		arch->shift_txtr.y = wall_clipping(arch, p, &tmp, angle);
		arch->depth.y = tmp.x;
		arch->decal.y = tmp.y;
	}
}

/*
**	renvoie la position du mur par rapport au portail de rendu
**	0 si le portail est devant le portail
**	1 si le portail est derriere le portail
*/
int				wall_behind_portal(t_arch *arch)
{
	t_affine	a_wall;
	t_affine	a_portal;

	if (arch->bound.depth_portal.x == arch->bound.depth_portal.y)
	{
		printf("%f\n", arch->bound.depth_portal.x);
		if (arch->depth.x > arch->bound.depth_portal.x)
			return (0);
		else if (arch->depth.y > arch->bound.depth_portal.x)
			return (0);
		return (1);
	}

	//verif si le mur a un coeficient directeur
	a_wall.a = (arch->decal.y - arch->decal.x) / (arch->depth.y - arch->depth.x);
	a_wall.b = arch->decal.y - a_wall.a * arch->depth.y;
	a_portal.a = (arch->bound.decal_portal.y - arch->bound.decal_portal.x) /
		(arch->bound.depth_portal.y - arch->bound.depth_portal.x);
	a_portal.b = arch->bound.decal_portal.y - a_portal.a * arch->bound.depth_portal.y;
	if (arch->depth.x < affine_val_index(a_portal, arch->depth.x))
	{
		return (0);
	}
	else if (arch->depth.y < affine_val_index(a_portal, arch->depth.y))
	{
		return (0);
	}
	return (1);

}

int			wall_screen_info(t_arch *arch, t_player *p)
{
	pillar_screen_info(arch, p);
	if (arch->depth_portal > 0)
	{
		printf("wall_behind_portal %d\n", wall_behind_portal(arch));
		return (wall_behind_portal(arch));
	}
	return (1);
}
