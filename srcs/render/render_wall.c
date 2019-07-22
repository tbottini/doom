#include "doom_nukem.h"

/*
**	renvoie la position en pixel d'un point
**	wall_angle est l'angle du point par rapport au joueur
*/
int			px_point(t_arch *arch, t_player *player, double h_diff, double depth)
{
	double	wall_angle;
	int px;
	double	player_angle;

	player_angle = (player->stat.rot.x - 90) * PI180;
	wall_angle = atan2(h_diff, depth);
	px = arch->sdl->size.y / 2 - tan(wall_angle) * arch->cam->d_screen;
	px += (player->stat.rot.x - 90) * 45;

	//vraies cervicales
	//px = tan(wall_angle - player_angle) * arch->cam->d_screen;
	//px = arch->sdl->size.y / 2 - px;
	return (px);
}

/*
**	renvoie la position au sol qui rejoint le bas du pillier
**	up : la position en z du haut du pillier par rapport au joueur (en u)
**	down : idem que up mais pour le bas (en u)
**	surface : la taille du pillier sur l'ecran
*/
t_fvct2		floor_pos(t_arch *arch, t_fvct2 len, t_fvct2 surface, t_fvct2 *pillar)
{
	double		px_to_u;
	t_fvct2		floor_pos;

	px_to_u = (len.x - len.y) / (surface.y / surface.x);
	//on recupere l'intersection en profondeur
	floor_pos.x = len.x / arch->cam->fov_ver;
	floor_pos.x = floor_pos.x * px_to_u;
	//on recupere decal
	floor_pos.y = (pillar->y / pillar->x) * floor_pos.x;
	return (floor_pos);
}

/*
**	calcul la taille du secteur par rapport au joueur
**	length.x = up
**	length.y = down
*/
t_fvct2		length_sector(t_player *player, t_sector *sector)
{
	t_fvct2	length;

	length.y = -player->stat.height - (player->stat.pos.z - sector->h_floor);
	length.x = length.y + sector->h_ceil;
	return (length);
}


/*
**	renvoie la surface en pixels d'un pillier
**	params : la hauteur du joueur (player)
**	de la hauteur du mur (wall_height)
**	et de la distance par rapport au mur (depth)
**	up est la difference entre le point de vue de la camera
**		et le haut du mur
*/
t_fvct2			surface_pillar(t_arch *arch, t_player *player, t_fvct2 len_sector, double depth)
{
	t_fvct2		wall_portion;

	b_point_debug(arch, (t_fvct2){depth, len_sector.x}, RED);
	b_point_debug(arch, (t_fvct2){depth, len_sector.y}, RED);
	wall_portion.x = px_point(arch, player, len_sector.x, depth);
	wall_portion.y = px_point(arch, player, len_sector.y, depth);
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
**		-la borne pour la recursivite arch->portal
**		-recharge borne_tmp dans arch->portal
*/
void			pillar_to_pillar(t_arch *arch, t_fvct2 *pillar, t_fvct2 *next, t_borne *borne_tmp)
{
   	t_fvct2		neutre;
   	t_fvct2		coef_surface;
	double		coef_neutre;
	int			start;

	start = arch->px.x;
	coef_surface.x = coef_diff(pillar->x - next->x, arch->px);
	coef_surface.y = coef_diff(pillar->y - next->y, arch->px);
	neutre.x = (double)(arch->sdl->size.y) / arch->pillar.x;
	neutre.y = (double)(arch->sdl->size.y) / arch->next.x;
	coef_neutre = coef_vct(neutre, arch->px);
	while (arch->px.x != arch->px.y)
	{
		if (arch->wall->status == WALL)
		{
			if (z_line_buffer(arch, neutre.x, arch->px.x))
				draw_column(arch, *pillar);
		}
		else if (arch->wall->status == PORTAL)
		{
			if (zline_portal(arch, borne_tmp->zline, neutre.x, start))
				draw_portal(arch, *pillar, borne_tmp, start);
		}
		pillar->x -= coef_surface.x;
		pillar->y -= coef_surface.y;
		neutre.x += coef_neutre;
		arch->px.x++;
	}
}

/*
**	les etapes de rendu pour un mur
**	recuperation d'information supplementaire
**	affichage d'un pillier a un autre
*/
void			render_wall(t_arch *arch, t_player *player)
{
	t_fvct2		pillar_px;
	t_fvct2		next_px;
	t_fvct2		len_sector;
	t_borne		borne_tmp;
	t_sector	*sector_tmp;
	int			start;

	if (wall_screen_info(arch, player))
	{
		reorder(arch);

		len_sector = length_sector(player, arch->sector);
		pillar_px = surface_pillar(arch, player, len_sector, arch->pillar.x);
		next_px = surface_pillar(arch, player, len_sector, arch->next.x);


		//render_floor (botton, down)
		//render_ceil (botton, down)
		//render_wall (arch, surface_wall, surface)
		if (arch->wall->status == PORTAL)
			borne_svg(arch, &borne_tmp);
		start = arch->px.x;
		pillar_to_pillar(arch, &pillar_px, &next_px, &borne_tmp);
		if (arch->wall->status == PORTAL)
		{
			arch->px.x = start;
			set_borne_horizontal(arch);
			arch->portal.pillar = arch->pillar;
			arch->portal.next = arch->next;
			sector_tmp = arch->sector;
			arch->depth_portal++;
			sector_render(arch, player, arch->wall->link);
			arch->depth_portal--;
			arch->sector = sector_tmp;
			borne_load(arch, &borne_tmp, start);
		}
	}
}
