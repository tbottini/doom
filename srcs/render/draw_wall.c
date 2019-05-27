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

void			pillar_screen_info(t_doom doom, t_wall wall, t_fvct2 *dist, t_vct2 *column_id)
{
	t_vct2 		px;
	t_fvct2 	d;
	float		angle;
	t_player	*p;
	int			size;

	p = &doom.player;
	size = doom.sdl.size.x;
	if (wall.pillar.frust)
	{
		px.x = (double)(size) / 2.0;
		px.x -= (double)(size - 1) / doom.player.fov * wall.pillar.angle;
		d.x = distance(*(t_fvct2*)&p->pos, wall.pillar.p);
	}
	else
	{
		px.x = pillar_polarite(*wall.next, wall.pillar, size - 1);
		angle = (px.x == 0) ? p->rot.y + p->fov / 2.0 : p->rot.y - p->fov / 2.0;
		d.x = wall_clipping(wall, *(t_fvct2*)&p->pos, angle);
	}
	if (wall.next->frust)
	{
		px.y = (double)(size) / 2.0;
		px.y -= (double)(size - 1) / doom.player.fov * wall.next->angle;
		d.y = distance(*(t_fvct2*)&p->pos, wall.next->p);
	}
	else
	{
		px.y = pillar_polarite(wall.pillar, *wall.next, size - 1);
		angle = (px.y == 0) ? p->rot.y + p->fov / 2.0 : p->rot.y - p->fov / 2.0;
		d.y = wall_clipping(wall, *(t_fvct2*)&p->pos, angle);
	}
	*column_id = px;
	*dist = d;
}

void		draw_column(t_sdl *sdl, int ipx, int length, uint32_t color)
{
	int		i;
	int		sky_size;

	i = 0;
	if (length > sdl->size.y)
		length = sdl->size.y - 1;
	sky_size = (sdl->size.y - length) / 2;
	while (i < sky_size)
	{
		sdl->screen[ipx] = BLUE_SKY;
		ipx += sdl->size.x;
		i++;
	}
	i = 0;
	while (i < length)
	{
		sdl->screen[ipx] = color;
		ipx += sdl->size.x;
		i++;
	}
	sky_size += length % 2;
	i = 0;
	while (i < sky_size)
	{
		sdl->screen[ipx] = 0x272130ff;
		ipx += sdl->size.x;
		i++;
	}
}


void		fish_eyes(double fov, int screenx, t_vct2 px, t_fvct2 *dist)
{
	double	angle;

	angle = ((double)px.x / screenx) * fov - (fov / 2.0);
	dist->x = cos(fabs(angle) * PI180) * dist->x;
	angle = ((double)px.y / screenx) * fov - (fov / 2.0);
	dist->y = cos(fabs(angle) * PI180) * dist->y;
}

/*
**	draw column from a pillar to another pillar
**	use : z_line_buffer	who check if the new pillar is neareast
**	than the last one
*/
void		pillar_to_pillar(t_doom *doom, t_vct2 px, t_fvct2 dist)
{
	double	coef_dist_px;
	int		fact_px;
	int		column;
	t_fvct2	column_len;

	column = px.x;
	fact_px = (px.x < px.y) ? 1 : -1;
	fish_eyes(doom->player.fov, doom->sdl.size.x, px, &dist);
	column_len.x = (double)(doom->sdl.size.y) / dist.x;
	column_len.y = (double)(doom->sdl.size.y) / dist.y;
	coef_dist_px = (column_len.y - column_len.x) / (px.y - px.x) * fact_px;
	while (column != px.y)
	{
		column += fact_px;
		if (z_line_buffer(*doom, column_len.x, column) > 0)
			draw_column(&doom->sdl, column, column_len.x, PINK_FLOOR);
		column_len.x += coef_dist_px;
	}
	//draw_column(&doom->sdl, px.x, doom->sdl.size.y, RED_WALL);
	//draw_column(&doom->sdl, px.y, doom->sdl.size.y, RED_WALL);

}

void		draw_wall(t_doom *doom, t_wall wall)
{
	t_vct2	column_id;
	t_fvct2	dist;

	pillar_screen_info(*doom, wall, &dist, &column_id);
	pillar_to_pillar(doom, column_id, dist);
}
