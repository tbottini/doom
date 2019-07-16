#include "doom_nukem.h"

/*
**	renvoie la position en pixel d'un point
*/
int			px_point(t_arch *arch, t_player *player, double h_diff, double depth_wall)
{
	double	wall_angle;
	int px;
	double	player_angle;

	player_angle = (player->stat.rot.x - 90) * PI180;
	wall_angle = atan2(h_diff, depth_wall);
	px = arch->sdl->size.y / 2 - tan(wall_angle) * arch->cam->d_screen;
	px += (player->stat.rot.x - 90) * 45;

	//vraies cervicales
	//px = tan(wall_angle - player_angle) * arch->cam->d_screen;
	//px = arch->sdl->size.y / 2 - px;
	return (px);
}

/*
**	renvoie la surface en px qu'un pillier prend
**	en fonction de la hauteur du joueur (player)
**	de la hauteur du mur (wall_height)
**	et de la distance par rapport au mur (depth)
**	up est la difference entre le point de vue de la camera
**		et le haut du mur
*/
t_fvct2			surface_pillar(t_arch *arch, t_player *player, double depth)
{
	t_fvct2		wall_portion;

	double		up;
	double		down;

	down = -player->stat.height - (player->stat.pos.z - arch->sector->h_floor);
	up = down + arch->sector->h_ceil;
	wall_portion.x = px_point(arch, player, up, depth);
	wall_portion.y = px_point(arch, player, down, depth);
	return (wall_portion);
}

/*
**	rearrange les parametre pour que l'on rende les colonnes de gauche a droite
*/
void			reorder(t_arch *arch)
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


/*
**	fait des coeficient pour rendre les colomnes entre les deux pilier
*/
//zline temporaire pour ne pas refaire un passage pillar_to_pillar
void			pillar_to_pillar(t_arch *arch, t_player *player)
{
	t_fvct2		pillar;
	t_fvct2		pillar_next;
   	t_fvct2		neutre;
   	t_fvct2		coef_surface;
	double		coef_neutre;

	int			start;
	t_borne		borne_tmp;
	t_sector	*sector_tmp;

	pillar = surface_pillar(arch, player, arch->depth.x);
	pillar_next = surface_pillar(arch, player, arch->depth.y);
	coef_surface.x = coef_diff(pillar.x - pillar_next.x, arch->px);
	coef_surface.y = coef_diff(pillar.y - pillar_next.y, arch->px);
	neutre.x = (double)(arch->sdl->size.y) / arch->depth.x;
	neutre.y = (double)(arch->sdl->size.y) / arch->depth.y;
	coef_neutre = coef_vct(neutre, arch->px);

	start = arch->px.x;
	if (arch->wall->status == PORTAL)
		borne_svg(arch, &borne_tmp);

	while (arch->px.x != arch->px.y)
	{
		if (arch->wall->status == WALL)
		{
			if (z_line_buffer(arch, neutre.x, arch->px.x))
				draw_column(arch, pillar);
		}
		else if (arch->wall->status == PORTAL)
		{
			if (zline_portal(arch, borne_tmp.zline, neutre.x, start))
				draw_portal(arch, pillar, &borne_tmp, start);
		}
		pillar.x -= coef_surface.x;
		pillar.y -= coef_surface.y;
		neutre.x += coef_neutre;
		arch->px.x++;
	}
	if (arch->wall->status == PORTAL)
	{
		arch->px.x = start;
		set_borne_horizontal(arch);
		arch->bound.decal_portal = arch->decal;
		arch->bound.depth_portal = arch->depth;
		sector_tmp = arch->sector;
		arch->depth_portal++;
		sector_render(arch, player, arch->wall->link);
		arch->sector = sector_tmp;
		borne_load(arch, &borne_tmp, start);
	}

}

/*
**	les etapes de rendu pour un mur
**	recuperation d'information supplementaire
**	affichage d'un pillier a un autre
*/
void		render_wall(t_arch *arch, t_player *player)
{
	if (wall_screen_info(arch, player))
	{
		reorder(arch);
		pillar_to_pillar(arch, player);
	}
}
