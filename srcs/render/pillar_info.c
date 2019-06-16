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

void			wall_screen_info(t_designer *arch, t_wall *wall, t_player *p, int *px, double *dist)
{
	float		angle;
	int			size;

	size = arch->sdl->size.x;
	if (wall->pillar.frust)
	{
		*px = fish_bowl_px(arch, wall->pillar);
		*dist = distance(*(t_fvct2*)&p->stat.pos, wall->pillar.p);
		fish_eyes(dist, wall->pillar.angle);
	}
	else
	{
		*px = pillar_polarite(wall->next, wall->pillar, size - 1);
		angle = (*px == 0) ? p->stat.rot.y + p->fov / 2.0 : p->stat.rot.y - p->fov / 2.0;
		//if ((int)arch->wall->pillar.p.x == 0 && (int)arch->wall->pillar.p.y == 0)
		//	printf("wall clipping\n");
		*dist = wall_clipping(arch, wall, *(t_fvct2*)&p->stat.pos, angle);
		fish_eyes(dist, angle - p->stat.rot.y);
	}
}

void			pillar_screen_info(t_designer *arch, t_player *p)
{
	t_wall		wall;
	double		tmp;
	//la disposition normal est x = 1 et y = 0

	arch->shift_txtr = (t_fvct2){0, 0};
	wall_screen_info(arch, arch->wall, p, &arch->px.x, &arch->dist.x);
	tmp = arch->shift_txtr.x;
	//arch->shift_txtr.x = arch->shift_txtr.y;
	wall.pillar = *arch->wall->next;
	wall.next = &arch->wall->pillar;

	arch->shift_txtr.x = 0;
	wall_screen_info(arch, &wall, p, &arch->px.y, &arch->dist.y);
	//arch->shift_txtr.y = !arch->shift_txtr.x ? 0 : 1 - arch->shift_txtr.x;
	//printf("percent %f return\n", arch->shift_txtr.x);

	if (arch->shift_txtr.x == 0.0)
		arch->shift_txtr.y = 0.0;
	else
		arch->shift_txtr.y = 1 - arch->shift_txtr.x;
	arch->shift_txtr.x = !tmp ? 1 : tmp;
	if ((int)arch->wall->pillar.p.x == 0 && (int)arch->wall->pillar.p.y == 39)
		printf("shift_txtr .y %f .x %f\n", arch->shift_txtr.y, arch->shift_txtr.x);
}
/*
**	on calcul la portion de l'ecran appartenant au mur
**	sector : recup la hauteur au plafond,
*/
t_vct2			sector_starend(t_sector sector, double dist, t_doom doom)
{

	t_vct2		surface;
	double		point;
	double		alpha;

	point = sector.h_ceil - doom.player.stat.height;
	//dist_point = sqrt(dist * dist + up * up);
	alpha = (doom.player.stat.rot.x - 90) * PI180 - atan(dist / point);
	surface.x = doom.sdl.size.y / 2.0 - tan(alpha) * doom.camera.d_screen;

	point = -doom.player.stat.height;
	alpha = (doom.player.stat.rot.x - 90) * PI180 - atan(dist / point);
	surface.y = doom.sdl.size.y / 2.0 - tan(alpha) * doom.camera.d_screen;
	//on recupere la distance x du point celon le point de vue
	return (surface);
}
