#include "doom_nukem.h"

/*
**	renvoie le pixel a l'ecran d'un point d'un pillier
**	doom information generale
**	h_diff hauteur du point par rapport a la vision de la camera
**		(haut du pillier : h_diff = hauteur pillier - hauteur joueur)
**	rot	rotation du joueur
**	dist_wall	la distance du joueur par rapport au pillier
*/
int			px_point(t_doom doom, double h_diff, double dist_wall)
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

t_fvct2		px_wall(t_doom doom, int wall_height, double dist)
{
	t_fvct2	wall_portion;

	double	up;
	double	down;

	up = wall_height - doom.player.height - (doom.player.pos.z - doom.player.sector->h_floor);
	down = -doom.player.height - (doom.player.pos.z - doom.player.sector->h_floor);

	wall_portion.x = px_point(doom, up, dist);
	wall_portion.y = px_point(doom, down, dist);
	return (wall_portion);
}

void		draw_part_texture(t_doom *doom, t_wall *wall, int numcol, int col_txtr, t_fvct2 surface)
{
	double	coef;
	int		px;
	double	buff;
	int		px_screen;

	px = col_txtr;
	buff = 0;
	coef = wall->txtr.h / (surface.y - surface.x);
	if (surface.y < 0)
		return ;
	if (surface.x < 0)
	{
		buff = -surface.x * coef;
		if (buff > 1.0)
		{
			px += (int)buff * wall->txtr.w;
			buff = buff - (int)buff;
		}
		surface.x = 0;
	}
	while (surface.x < surface.y && surface.x < doom->sdl.size.y)
	{
		doom->sdl.screen[numcol] = wall->txtr.pixels[px];
		surface.x++;
		numcol += doom->sdl.size.x;
		buff += coef;
		if (buff > 1.0)
		{
			px += (int)buff * wall->txtr.w;
			buff = buff - (int)buff;
		}

	}
}

void		draw_column(t_doom *doom, t_wall *wall, int numcol, t_fvct2 surface)
{
	int		i;
	int		len;
	int		ncol;

	i = 0;
	ncol = numcol;
	//utilisation de sector ?
	len = doom->sdl.size.x;
	while (i < surface.x && i < doom->sdl.size.y)
	{
		doom->sdl.screen[numcol] = BLUE_SKY;
		numcol += len;
		i++;
	}
	draw_part_texture(doom, wall, numcol, 1, surface);

	numcol = ncol + ((int)surface.y + 1) * len;
	i = surface.y;
	if (i < 0)
	{
		i = 0;
		numcol = ncol;
	}
	while (i < doom->sdl.size.y)
	{
		doom->sdl.screen[numcol] = 0x272130ff;
		numcol += len;
		i++;
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

void			pillar_to_pillar(t_doom *doom, t_vct2 px, t_fvct2 dist, t_sector sector, t_wall *wl)
{
	t_fvct2		pillar;
	t_fvct2		pillar_next;
   	t_fvct2		neutre;
	double		coef_surface;
	double		coef_down;
	double		coef_neutre;

	reorder(&px, &dist);
	pillar = px_wall(*doom, sector.h_ceil, dist.x);
	pillar_next = px_wall(*doom, sector.h_ceil, dist.y);

	coef_surface = (pillar.x - pillar_next.x) / (px.y - px.x);
	coef_down = (pillar.y - pillar_next.y) / (px.y - px.x);

	neutre.x = (double)(doom->sdl.size.y) / dist.x;
	neutre.y = (double)(doom->sdl.size.y) / dist.y;

	coef_neutre = (neutre.y - neutre.x) / (px.y - px.x);
	while (px.x != px.y)
	{
		if (z_line_buffer(*doom, neutre.x, px.x) > 0)
		{
			draw_column(doom, wl, px.x, pillar);
		}
		pillar.x -= coef_surface;
		pillar.y -= coef_down;
		neutre.x += coef_neutre;
		px.x++;
	}
}

void		draw_wall(t_doom *doom, t_wall wall, t_sector sector_wall)
{
	t_vct2	column_id;
	t_fvct2	dist;

	//printf("wall.texture w %d h %d\n", wall.txtr.w, wall.txtr.h);
	pillar_screen_info(*doom, wall, &dist, &column_id);
	pillar_to_pillar(doom, column_id, dist, sector_wall, &wall);
}
