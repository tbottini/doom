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

	t_fvct2		pillar_tmp;

	if (arch->px.x > arch->px.y)
	{
		tmpint = arch->px.x;
		arch->px.x = arch->px.y;
		arch->px.y = tmpint;
		pillar_tmp = arch->pillar;
		arch->pillar = arch->next;
		arch->next = pillar_tmp;
		tmp = arch->shift_txtr.x;
		arch->shift_txtr.x = arch->shift_txtr.y;
		arch->shift_txtr.y = tmp;
	}
}

/*
**	fait des coeficient pour rendre les colomnes entre les deux pilier
**	et si c'est un portail prepare
**		-sauvegarde la borne actuel dans borne_tmp
**		-la borne pour la recursivite arch->bound
**		-recharge borne_tmp dans arch->bound
*/
//zline temporaire pour ne pas refaire un passage pillar_to_pillar
void			pillar_to_pillar(t_arch *arch, t_player *player)
{
	t_fvct2		pillar;
	t_fvct2		pillar_next;
   	t_fvct2		neutre;
   	t_fvct2		coef_surface;
	double		coef_neutre;

	static		int i = 0;

	int			start;
	t_borne		borne_tmp;
	t_sector	*sector_tmp;

	pillar = surface_pillar(arch, player, arch->pillar.x);
	pillar_next = surface_pillar(arch, player, arch->next.x);
	coef_surface.x = coef_diff(pillar.x - pillar_next.x, arch->px);
	coef_surface.y = coef_diff(pillar.y - pillar_next.y, arch->px);
	neutre.x = (double)(arch->sdl->size.y) / arch->pillar.x;
	neutre.y = (double)(arch->sdl->size.y) / arch->next.x;
	coef_neutre = coef_vct(neutre, arch->px);
	if (debug == 3)
	{
		d_wall(arch->wall);
		borne_print(&arch->bound);
	}
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
		i++;
		if (debug == 2 && i % 5 == 0)
		{
			sdl_MultiRenderCopy(arch->sdl);
			SDL_RenderPresent(arch->sdl->rend);
		}
	}
	if (arch->wall->status == PORTAL)
	{
		//sinon mauvais calcul de borne gauche
		arch->px.x = start;
		set_borne_horizontal(arch);
		//set portal borne
		arch->bound.decal_portal = (t_fvct2){arch->pillar.y, arch->next.y};
		arch->bound.depth_portal = (t_fvct2){arch->pillar.x, arch->next.x};
		sector_tmp = arch->sector;
		arch->depth_portal++;
		if (debug == 1)
			printf("--->\n");
		sector_render(arch, player, arch->wall->link);
		if (debug == 1)
			printf("<---\n");
		arch->depth_portal--;
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
		if (arch->wall->status == PORTAL)
			draw_wall(arch, 0xffff00ff);
		else if (arch->wall->status == WALL)
			draw_wall(arch, 0xffffffff);
		reorder(arch);
		pillar_to_pillar(arch, player);
	}
	else
		draw_wall(arch, RED);
}
