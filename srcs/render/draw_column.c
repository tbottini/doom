#include "doom_nukem.h"

/*
**	renvoie la position en pixel d'un point
*/
int			px_point(t_designer *arch, t_player *player, double h_diff, double depth_wall)
{
	double	wall_angle;
	double	limit_angle;
	int px;

	limit_angle = (player->fov / 2) * (M_PI / 180.0);
	wall_angle = atan2(h_diff, depth_wall);
	px = arch->sdl->size.y / 2 - tan(wall_angle) * arch->cam->d_screen;
	px += (player->stat.rot.x - 90) * 45;
	return (px);
}

/*
**	renvoie la surface en px qu'un pillier prend
**	en fonction de la hauteur du joueur (player)
**	de la hauteur du mur (wall_height)
**	et de la depthance par rapport au mur (depth)
*/
t_fvct2		surface_pillar(t_designer *arch, t_player *player, int wall_height, double depth)
{
	t_fvct2	wall_portion;

	double	up;
	double	down;

	up = wall_height - player->stat.height - (player->stat.pos.z - player->stat.sector->h_floor);
	down = -player->stat.height - (player->stat.pos.z - player->stat.sector->h_floor);

	wall_portion.x = px_point(arch, player, up, depth);
	wall_portion.y = px_point(arch, player, down, depth);
	return (wall_portion);
}

void		draw_part_texture(t_designer *arch, t_wall *wall, int numcol, t_fvct2 surface)
{
	double	coef;
	int		px;
	double	buff;

	px = texture_interpolation2D(arch);
	buff = 0;
	coef = (double)wall->txtr.h / (surface.y - surface.x);
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
	while (surface.x < surface.y && surface.x < arch->sdl->size.y)
	{
		arch->sdl->screen[numcol] = wall->txtr.pixels[px];
		surface.x++;
		numcol += arch->sdl->size.x;
		buff += coef;
		if (buff > 1.0)
		{
			px += (int)buff * wall->txtr.w;
			buff = buff - (int)buff;
		}
	}
}

/*
**	dessine les differente partie d'une colonne
*/
void		draw_column(t_designer *arch, t_wall *wall, int numcol, t_fvct2 surface)
{
	int		i;
	int		len;
	int		ncol;

	i = 0;
	ncol = numcol;
	len = arch->sdl->size.x;
	while (i < surface.x && i < arch->sdl->size.y)
	{
		arch->sdl->screen[numcol] = BLUE_SKY;
		numcol += len;
		i++;
	}
	draw_part_texture(arch, wall, numcol, surface);
	numcol = ncol + ((int)surface.y + 1) * len;
	i = surface.y;
	if (i < 0)
	{
		i = 0;
		numcol = ncol;
	}
	while (i < arch->sdl->size.y)
	{
		arch->sdl->screen[numcol] = 0x272130ff;
		numcol += len;
		i++;
	}
}
