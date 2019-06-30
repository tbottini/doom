#include "doom_nukem.h"

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

/*
**	fait des coeficient pour rendre les colomnes entre les deux pilier
*/
void			pillar_to_pillar(t_designer *arch, t_player *player)
{
	t_fvct2		pillar;
	t_fvct2		pillar_next;
   	t_fvct2		neutre;
	double		coef_surface;
	double		coef_down;
	double		coef_neutre;

	reorder(arch);
	pillar = surface_pillar(arch, player, arch->depth.x);
	pillar_next = surface_pillar(arch, player, arch->depth.y);

	coef_surface = coef_diff(pillar.x - pillar_next.x, arch->px);
	coef_down = coef_diff(pillar.y - pillar_next.y, arch->px);
	neutre.x = (double)(arch->sdl->size.y) / arch->depth.x;
	neutre.y = (double)(arch->sdl->size.y) / arch->depth.y;
	coef_neutre = coef_vct(neutre, arch->px);

	while (arch->px.x != arch->px.y)
	{
		if (z_line_buffer(arch, neutre.x, arch->px.x) > 0)
		{
			if (arch->wall->status == WALL)
				draw_column(arch, pillar);
			else if (arch->wall->status == PORTAL_DIRECT)
				draw_portal(arch, player, pillar);
		}
		pillar.x -= coef_surface;
		pillar.y -= coef_down;
		neutre.x += coef_neutre;
		arch->px.x++;
	}
}

/*
**	les etapes de rendu pour un mur
**	recuperation d'information supplementaire
**	affichage d'un pillier a un autre
*/
void		render_wall(t_designer *arch, t_player *player)
{
	wall_screen_info(arch, player);
	pillar_to_pillar(arch, player);
}
