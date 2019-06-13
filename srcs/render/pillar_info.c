#include "doom_nukem.h"

/*
**	si au moins l'un des pilier est hors frustum il passe pas l'extremite de
**	l'ecran, on determine laquelle avec une polarite (-1 == 0px et 1 == max)
**	si l'angle entre le joueur est les deux pillier est superieur a 180
**	la polarite de depart (position du premier pillier) s'inverse
*/
double		pillar_polarite(t_pillar pillar, t_pillar next, int max)
{
	t_fvct2	angle;
	double	diff;
	int		polarite;

	polarite = 0;
	angle.x = pillar.angle;
	angle.y = next.angle;
	if (angle.x < 0)
		angle.x = 360 + angle.x;
	if (angle.y < 0)
		angle.y = 360 + angle.y;
	diff = fabs(angle.x - angle.y);
	polarite = (pillar.angle > 0 ? -1 : 1) * (diff < 180 ? 1 : -1);
	return ((polarite == -1) ? 0 : max);
}

void			pillar_screen_info(t_doom *doom, t_wall wall)
{
	float		angle;
	t_player	*p;
	int			size;

	p = &doom->player;
	size = doom->sdl.size.x;
	if (wall.pillar.frust)
	{
		doom->tool.px.x = fish_bowl_px(doom, wall.pillar);
		doom->tool.dist.x = distance(*(t_fvct2*)&p->stat.pos, wall.pillar.p);
		fish_eyes(&doom->tool.dist.x, wall.pillar.angle);
	}
	else
	{
		doom->tool.px.x = pillar_polarite(*wall.next, wall.pillar, size - 1);
		angle = (doom->tool.px.x == 0) ? p->stat.rot.y + p->fov / 2.0 : p->stat.rot.y - p->fov / 2.0;
		doom->tool.dist.x = wall_clipping(wall, *(t_fvct2*)&p->stat.pos, angle);
		fish_eyes(&doom->tool.dist.x, angle - p->stat.rot.y);
	}
	if (wall.next->frust)
	{
		doom->tool.px.y = fish_bowl_px(doom, *wall.next);
		doom->tool.dist.y = distance(*(t_fvct2*)&p->stat.pos, wall.next->p);
		fish_eyes(&doom->tool.dist.y, wall.next->angle);
	}
	else
	{
		doom->tool.px.y = pillar_polarite(wall.pillar, *wall.next, size - 1);
		angle = (doom->tool.px.y == 0) ? p->stat.rot.y + p->fov / 2.0 : p->stat.rot.y - p->fov / 2.0;
		doom->tool.dist.y = wall_clipping(wall, *(t_fvct2*)&p->stat.pos, angle);
		fish_eyes(&doom->tool.dist.y, angle - p->stat.rot.y);
	}
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
