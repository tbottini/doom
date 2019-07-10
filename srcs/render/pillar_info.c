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

	angle.x = local_angle(arch->borne.x, arch->wall->pillar->angle);
	angle.y = local_angle(arch->borne.x, arch->wall->next->angle);

	diff = fabs(angle.x - angle.y);
	polarite = (arch->wall->next->angle > arch->borne.x ? -1 : 1) * (diff < 180 ? 1 : -1);
	arch->px.x = (polarite == -1) ? 0 : arch->sdl->size.x -1;
	arch->px.y = arch->sdl->size.x - 1 - arch->px.x;
}

int			pillar_polarite(t_arch *arch, t_pillar *pillar, t_pillar *next)
{
	double	angle;
	double	angle_next;
	double	borne;

	angle = local_angle(arch->borne.x, pillar->angle);
	angle_next = local_angle(arch->borne.x, next->angle);
	borne = local_angle(arch->borne.x, arch->borne.y);


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
		arch->px.x = pillar_polarite(arch, &arch->wall->pillar, arch->wall->next);
		if (arch->px.x == 0)
		{
			arch->px.x = arch->sdl->size.x / 2.0 - (tan(arch->borne.x * PI180) * arch->cam->d_screen);
			angle = p->stat.rot.y + arch->borne.x;
		}
		else
		{
			arch->px.x = arch->sdl->size.x / 2.0 - (tan(arch->borne.y * PI180) * arch->cam->d_screen);
			angle = p->stat.rot.y + arch->borne.y;
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
		arch->px.y = pillar_polarite(arch, arch->wall->next, &arch->wall->pillar);
		if (arch->px.y == 0)
		{
			arch->px.y = arch->sdl->size.x / 2.0 - (tan(arch->borne.x * PI180) * arch->cam->d_screen);
			angle = p->stat.rot.y + arch->borne.x;
		}
		else
		{
			arch->px.y = arch->sdl->size.x / 2.0 - (tan(arch->borne.y * PI180) * arch->cam->d_screen);
			angle = p->stat.rot.y + arch->borne.y;
		}
		arch->shift_txtr.y = wall_clipping(arch, p, &tmp, angle);
		arch->depth.y = tmp.x;
		arch->decal.y = tmp.y;
	}
}


void			wall_screen_info(t_arch *arch, t_player *p)
{
	pillar_screen_info(arch, p);
}
