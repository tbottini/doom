#include "doom_nukem.h"

/*
**	si au moins l'un des pilier est hors frustum il passe pas l'extremite de
**	l'ecran, on determine laquelle avec une polarite (-1 == 0px et 1 == max)
**	si l'angle entre le joueur est les deux pillier est superieur a 180
**	la polarite de depart (position du premier pillier) s'inverse
*/
double		pillar_polarite(t_pillar *pillar, t_pillar next, int max)
{
	t_fvct2	angle;
	double	diff;
	int		polarite;

	polarite = 0;
	angle.x = pillar->angle;
	angle.y = next.angle;
	if (angle.x < 0)
		angle.x = 360 + angle.x;
	if (angle.y < 0)
		angle.y = 360 + angle.y;
	diff = fabs(angle.x - angle.y);
	polarite = (pillar->angle > 0 ? -1 : 1) * (diff < 180 ? 1 : -1);
	return ((polarite == -1) ? 0 : max);
}

void			pillar_screen_info(t_designer *arch, t_wall *wall, t_player *p, int *px, double *depth, double *decal)
{
	float		angle;
	int			size;

	size = arch->sdl->size.x;
	if (wall->pillar.frust)
	{
		*px = fish_bowl_px(arch, wall->pillar);
		*depth = distance(*(t_fvct2*)&p->stat.pos, wall->pillar.p);
		*decal = sin(wall->pillar.angle * PI180) * *depth;
		*depth = cos(wall->pillar.angle * PI180) * *depth;
	}
	else
	{
		*px = pillar_polarite(wall->next, wall->pillar, size - 1);
		angle = (*px == 0) ? p->stat.rot.y + p->fov / 2.0 : p->stat.rot.y - p->fov / 2.0;
		*depth = wall_clipping(arch, wall, *(t_fvct2*)&p->stat.pos, angle);
		*decal = sin((angle - p->stat.rot.y) * PI180) * *depth;
		*depth = cos((angle - p->stat.rot.y) * PI180) * *depth;
	}
}

void			wall_screen_info(t_designer *arch, t_player *p)
{
	t_wall		wall;
	double		tmp;

	arch->shift_txtr = (t_fvct2){0, 0};
	pillar_screen_info(arch, arch->wall, p, &arch->px.x, &arch->depth.x, &arch->decal.x);
	tmp = arch->shift_txtr.x;
	wall.pillar = *arch->wall->next;
	wall.next = &arch->wall->pillar;

	arch->shift_txtr.x = 0;
	pillar_screen_info(arch, &wall, p, &arch->px.y, &arch->depth.y, &arch->decal.y);
	if (arch->shift_txtr.x == 0.0)
		arch->shift_txtr.y = 0.0;
	else
		arch->shift_txtr.y = 1 - arch->shift_txtr.x;
	arch->shift_txtr.x = !tmp ? 1 : tmp;
}

/*
**	on calcul la portion de l'ecran appartenant au mur
**	sector : recup la hauteur au plafond,
*/
t_vct2			sector_starend(t_sector sector, double depth, t_doom doom)
{
	t_vct2		surface;
	double		point;
	double		alpha;

	point = sector.h_ceil - doom.player.stat.height;
	alpha = (doom.player.stat.rot.x - 90) * PI180 - atan(depth / point);
	surface.x = doom.sdl.size.y / 2.0 - tan(alpha) * doom.camera.d_screen;
	point = -doom.player.stat.height;
	alpha = (doom.player.stat.rot.x - 90) * PI180 - atan(depth / point);
	surface.y = doom.sdl.size.y / 2.0 - tan(alpha) * doom.camera.d_screen;
	return (surface);
}
