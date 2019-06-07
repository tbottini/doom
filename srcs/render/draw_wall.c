#include "doom_nukem.h"

/*
**	renvoie le pixel a l'ecran d'un point d'un pillier
**	doom information generale
**	h_diff hauteur du point par rapport a la vision de la camera
**		(haut du pillier : h_diff = hauteur pillier - hauteur joueur)
**	rot	rotation du joueur
**	dist_wall	la distance du joueur par rapport au pillier
*/

//pblm les mur change de taille quand on monte ou on baisse la tete


int			px_point(t_doom doom, double h_diff, double rot, double dist_wall)
{
	double	wall_angle;
	double	limit_angle;

	int px;

	limit_angle = (doom.player.fov / 2) * (M_PI / 180.0);
	wall_angle = atan2(h_diff, dist_wall);
	px = doom.sdl.size.y / 2 - tan(wall_angle) * doom.camera.d_screen;
	px += (doom.player.rot.x - 90) * 45;
	//px += (doom.player.pos.z - doom.player.sector->h_ceil);
	return (px);
}

t_fvct2		px_wall(t_doom doom, int wall_height, double rot, double dist)
{
	t_fvct2	wall_portion;

	double	up;
	double	down;

	up = wall_height - doom.player.height - (doom.player.pos.z - doom.player.sector->h_floor);
	down = -doom.player.height - (doom.player.pos.z - doom.player.sector->h_floor);

	wall_portion.x = px_point(doom, up, rot, dist);
	wall_portion.y = px_point(doom, down, rot, dist);
	return (wall_portion);
}


void		draw_column_s(t_doom *doom, t_sector sector, int numcol, t_fvct2 surface)
{
	int		i;
	int		len;

	i = 0;
	len = doom->sdl.size.x;
	while (i < surface.x && i < doom->sdl.size.y)
	{
		doom->sdl.screen[numcol] = BLUE_SKY;
		numcol += len;
		i++;
	}
	while (i < surface.y && i < doom->sdl.size.y)
	{
		doom->sdl.screen[numcol] = PINK_FLOOR;
		numcol += len;
		i++;
	}
	while (i < doom->sdl.size.y)
	{
		doom->sdl.screen[numcol] = 0x272130ff;
		numcol += len;
		i++;
	}
}

void		draw_column(t_doom *doom, t_sector sector, int numcol, int length)
{
	int		sky_size;
	int		i;
	double	up;

	i = 0;
	sky_size = (doom->sdl.size.y - length) / 2;
	up = doom->player.pos.z - doom->player.sector->h_floor;
	sky_size = doom->sdl.size.y / 2 + ((-sector.h_ceil + doom->player.height + up) / sector.h_ceil) * length;
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

void			reorder(t_vct2 *px, t_fvct2 *dist)
{
	double		tmp;
	int			tmpint;

	if (px->x > px->y)
	{
		tmpint = px->x;
		px->x = px->y;
		px->y = tmpint;
		tmp = dist->x;
		dist->x = dist->y;
		dist->y = tmp;
	}
}
void			pillar_to_pillar2(t_doom *doom, t_vct2 px, t_fvct2 dist, t_sector sector)
{
	t_fvct2		pillar;
	t_fvct2		pillar_next;
   	t_fvct2		neutre;
	double		coef_surface;
	double		coef_down;
	double		coef_neutre;

	reorder(&px, &dist);
	pillar = px_wall(*doom, sector.h_ceil, doom->player.rot.x, dist.x);
	pillar_next = px_wall(*doom, sector.h_ceil, doom->player.rot.x, dist.y);

	coef_surface = (pillar.x - pillar_next.x) / (px.y - px.x);
	coef_down = (pillar.y - pillar_next.y) / (px.y - px.x);

	neutre.x = (double)(doom->sdl.size.y) / dist.x;
	neutre.y = (double)(doom->sdl.size.y) / dist.y;

	coef_neutre = (neutre.y - neutre.x) / (px.y - px.x);
	while (px.x != px.y)
	{
		if (z_line_buffer(*doom, neutre.x, px.x) > 0)
		{
			draw_column_s(doom, sector, px.x, pillar);
		}
		pillar.x -= coef_surface;
		pillar.y -= coef_down;
		neutre.x += coef_neutre;
		px.x++;
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
			draw_column(doom, sector, px.x, column_len.x);
		}
		column_len.x += coef_dist_px;
		neutre.x += coef_neutre;
		px.x += fact_px;
	}

}

void		draw_wall(t_doom *doom, t_wall wall, t_sector sector_wall)
{
	t_vct2	column_id;
	t_fvct2	dist;

	//printf("player rott %f\n", doom->player.rot.x);
	//printf("player pos %f\n", doom->player.pos.z);
	//printf("sector floor %f\n", doom->player.sector->h)
	pillar_screen_info(*doom, wall, &dist, &column_id);
	pillar_to_pillar2(doom, column_id, dist, sector_wall);
}
