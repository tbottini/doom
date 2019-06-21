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
	//px += (player->stat.pos.z - player->stat.sector->h_ceil);
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

void		draw_part_texture(t_designer *arch, t_wall *wall, int numcol, double col_txtr, t_fvct2 surface)
{
	double	coef;
	int		px;
	double	buff;

	(void)col_txtr;
	//px = arch->shift_txtr.x;
	//futur appel de texture_interpolation2
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
	draw_part_texture(arch, wall, numcol, 1, surface);
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

/*
**	rearrange les parametre pour que l'on rende les colonnes de gauche a droite
*/
void			reorder(t_designer *arch)
{
	double		tmp;
	int			tmpint;

	if (arch->px.x > arch->px.y)
	{
		tmpint = arch->px.x;
		arch->px.x = arch->px.y;
		arch->px.y = tmpint;
		tmp = arch->depth.x;
		arch->depth.x = arch->depth.y;
		arch->depth.y = tmp;
		tmp = arch->decal.x;
		arch->decal.x = arch->decal.y;
		arch->decal.y = tmp;
		tmp = arch->shift_txtr.x;
		arch->shift_txtr.x = arch->shift_txtr.y;
		arch->shift_txtr.y = tmp;
	}
}

void			pillar_to_pillar(t_designer *arch, t_player *player)
{
	t_fvct2		pillar;
	t_fvct2		pillar_next;
   	t_fvct2		neutre;
	double		coef_surface;
	double		coef_down;
	double		coef_neutre;
	double		coef_txtr;

	reorder(arch);
	pillar = surface_pillar(arch, player, arch->sector->h_ceil, arch->depth.x);
	pillar_next = surface_pillar(arch, player, arch->sector->h_ceil, arch->depth.y);

	coef_surface = coef_diff(pillar.x - pillar_next.x, arch->px);
	coef_down = coef_diff(pillar.y - pillar_next.y, arch->px);
	//coef_txtr = coef_vct(arch->shift_txtr, arch->px) * arch->wall->txtr.w;

	//arch->shift_txtr.x *= arch->wall->txtr.w;
	neutre.x = (double)(arch->sdl->size.y) / arch->depth.x;
	neutre.y = (double)(arch->sdl->size.y) / arch->depth.y;

	coef_neutre = coef_vct(neutre, arch->px);
	while (arch->px.x != arch->px.y)
	{
		if (z_line_buffer(arch, neutre.x, arch->px.x) > 0)
		{
			draw_column(arch, arch->wall, arch->px.x, pillar);
		}
		pillar.x -= coef_surface;
		pillar.y -= coef_down;
		neutre.x += coef_neutre;
		arch->px.x++;
		//arch->shift_txtr.x += coef_txtr;
	}
}

/*
**	les etapes de rendu pour un mur
**	recuperation d'information supplementaire
**	affichage d'un pillier a un autre
*/
void		draw_wall(t_designer *arch, t_player *player)
{
	wall_screen_info(arch, player);
	pillar_to_pillar(arch, player);
}
