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

int				fish_bowl_px(t_doom doom, t_pillar pillar)
{
	int			px;
	int			sx;

	sx = doom.sdl.size.x / 2.0;
	px = sx - (tan(pillar.angle * PI180) * doom.camera.d_screen);
	return (px);
}

void			fish_eyes(double *dist, double angle)
{
	*dist = cos(angle * PI180) * *dist;
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
		px.x = fish_bowl_px(doom, wall.pillar);
		d.x = distance(*(t_fvct2*)&p->pos, wall.pillar.p);
		fish_eyes(&d.x, wall.pillar.angle);
	}
	else
	{
		px.x = pillar_polarite(*wall.next, wall.pillar, size - 1);
		angle = (px.x == 0) ? p->rot.y + p->fov / 2.0 : p->rot.y - p->fov / 2.0;
		d.x = wall_clipping(wall, *(t_fvct2*)&p->pos, angle);
		fish_eyes(&d.x, angle - p->rot.y);
	}
	if (wall.next->frust)
	{
		px.y = fish_bowl_px(doom, *wall.next);
		d.y = distance(*(t_fvct2*)&p->pos, wall.next->p);
		fish_eyes(&d.y, wall.next->angle);
	}
	else
	{
		px.y = pillar_polarite(wall.pillar, *wall.next, size - 1);
		angle = (px.y == 0) ? p->rot.y + p->fov / 2.0 : p->rot.y - p->fov / 2.0;
		d.y = wall_clipping(wall, *(t_fvct2*)&p->pos, angle);
		fish_eyes(&d.y, angle - p->rot.y);
	}
	*column_id = px;
	*dist = d;
}

void		draw_column2(t_doom *doom, t_sector sector, int numcol, int length)
{
	int		sky_size;
	int		i;

	i = 0;
	//sky_size = (doom->sdl.size.y - length) / 2;
	sky_size = doom->sdl.size.y / 2 - ((sector.h_ceil - doom->player.height) / sector.h_ceil) * length;
	length += sky_size;
	while (i < doom->sdl.size.y)
	{
		if (i < sky_size)
			doom->sdl.screen[numcol] = BLUE_SKY;
		else if (i < length)
			doom->sdl.screen[numcol] = PINK_FLOOR;
		else
			doom->sdl.screen[numcol] = 0x272130ff;
		i++;
		numcol += doom->sdl.size.x;
	}
}

/*
**	draw column from a pillar to another pillar
**	use : z_line_buffer	who check if the new pillar is neareast
**	than the last one
*/
void			pillar_to_pillar(t_doom *doom, t_vct2 px, t_fvct2 dist, t_sector sector)
{
	double		coef_dist_px;
	int			fact_px;
	t_fvct2		column_len;
	t_fvct2		neutre;
	double		coef_neutre;

	fact_px = (px.x < px.y) ? 1 : -1;
	column_len.x = (((double)(doom->sdl.size.y) / 5) / dist.x) * sector.h_ceil;
	column_len.y = (((double)(doom->sdl.size.y) / 5) / dist.y) * sector.h_ceil;

	neutre.x = (double)(doom->sdl.size.y) / dist.x;
	neutre.y = (double)(doom->sdl.size.y) / dist.y;
	coef_neutre = (neutre.y - neutre.x) / (px.y - px.x) * fact_px;
	coef_dist_px = (column_len.y - column_len.x) / (px.y - px.x) * fact_px;

	while (px.x != px.y)
	{
		if (z_line_buffer(*doom, neutre.x, px.x) > 0)
		{
			draw_column2(doom, sector, px.x, column_len.x);
		}
			//draw_column(&doom->sdl, column, column_len.x, PINK_FLOOR, doom->player);
		column_len.x += coef_dist_px;
		neutre.x += coef_neutre;
		px.x += fact_px;
	}

}

void		draw_wall(t_doom *doom, t_wall wall, t_sector sector_wall)
{
	t_vct2	column_id;
	t_fvct2	dist;

	pillar_screen_info(*doom, wall, &dist, &column_id);
	pillar_to_pillar(doom, column_id, dist, sector_wall);
}
