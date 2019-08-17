#include "render.h"
#include "debug.h"

/*
**	renvoie la position en pixel d'un point
**	wall_angle est l'angle du point par rapport au joueur
*/
int			px_point(t_arch *arch, t_player *player, double h_diff, double depth)
{
	double	wall_angle;
	int		px;
	double	player_angle;

	player_angle = (player->stat.rot.x - 90) * PI180;
	wall_angle = atan2(h_diff, depth);
	px = arch->sdl->size.y / 2 - tan(wall_angle) * arch->cam->d_screen;
	px += (player->stat.rot.x - 90) * 15.5;
	return (px);
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

	//b_point_debug(arch, (t_fvct2){depth, len_sector.x}, RED);
	//b_point_debug(arch, (t_fvct2){depth, len_sector.y}, RED);
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
void			pillar_to_pillar(t_arch *arch, t_pil_render *render_stuff)
{
   	t_fvct2		neutre;
   	t_fvct2		coef_surface;
	double		coef_neutre;
	double		coef_distance;
	double		dist_px;
	int			i = 0;

	render_stuff->px_start = arch->px.x;
	coef_surface.x = coef_diff(render_stuff->pillar.x - render_stuff->next.x, arch->px);
	coef_surface.y = coef_diff(render_stuff->pillar.y - render_stuff->next.y, arch->px);
	neutre.x = (double)(arch->sdl->size.y) / arch->pillar.x;
	neutre.y = (double)(arch->sdl->size.y) / arch->next.x;
	coef_neutre = coef_vct(neutre, arch->px);
	coef_distance = (arch->next.x - arch->pillar.x) / (arch->px.y - arch->px.x);
	dist_px = arch->pillar.x;
	while (arch->px.x != arch->px.y)
	{
		if (arch->portal.b_up[arch->px.x] > (uint32_t)arch->sdl->size.y)
			arch->portal.b_up[arch->px.x] = arch->sdl->size.y - 1;
		if (arch->portal.b_down[arch->px.x] > (uint32_t)arch->sdl->size.y)
			arch->portal.b_down[arch->px.x] = arch->sdl->size.y - 1;
		if (arch->wall->status == WALL)
		{
			if (zline_wall(arch, render_stuff, neutre.x))
			{
				draw_wall(arch, render_stuff);
				props_draw_column(arch->wall->props, arch, render_stuff->pillar);
			}
		}
		else if (arch->wall->status == PORTAL)
		{
			if (zline_portal(arch, render_stuff, neutre.x))
				draw_portal(arch, render_stuff);
		}
		else if (arch->wall->status == OPEN_DOOR
			|| arch->wall->status == CLOSE_DOOR)
		{
			if ((arch->px.x > render_stuff->px_inter) ^ render_stuff->open_invert)
			{
				if (zline_wall(arch, render_stuff, neutre.x))
					draw_door(arch, render_stuff, PORTAL);
			}
			else if (zline_wall(arch, render_stuff, neutre.x))
				draw_door(arch, render_stuff, WALL);
			//draw_door(arch, render_stuff);
		}
		render_stuff->pillar.x -= coef_surface.x;
		render_stuff->pillar.y -= coef_surface.y;
		neutre.x += coef_neutre;
		arch->px.x++;
		i++;
		if (i % 5 == 0 && debug == 5)
		{
			sdl_MultiRenderCopy(arch->sdl);
			SDL_RenderPresent(arch->sdl->rend);
		}
		dist_px += coef_distance;
	}
}

void				render_surface(t_arch *arch, t_player *player)
{
	t_fvct2			len_sector;
	t_sector		*sector_tmp;
	t_vct2			px_draw;
	t_pil_render	render_stuff;

	if (arch->wall->status == OPEN_DOOR || arch->wall->status == CLOSE_DOOR)
	{
		door_split_info(arch, &render_stuff, arch->wall->status);
	}
	reorder(arch);
	len_sector = length_sector(player, arch->sector);
	render_stuff.pillar = surface_pillar(arch, player, len_sector, arch->pillar.x);
	render_stuff.next = surface_pillar(arch, player, len_sector, arch->next.x);
	prop_iter_v(arch->wall->props, arch->wall->nb_props, &prop_init_render, arch);
	if (debug_screen == 2)
	{
		if (arch->wall->status == PORTAL)
			draw_wall_debug(arch, YELLOW);
		else if (arch->wall->status == WALL)
			draw_wall_debug(arch, WHITE);
	}
	if (arch->wall->status == PORTAL)
	{
		if (debug == 9)
			printf("borne_svg(%d) %d %d\n", arch->depth_portal, arch->portal.b_up[arch->sdl->size.x/2], arch->portal.b_down[arch->sdl->size.x/2]);
		borne_svg(arch, &render_stuff.borne_tmp);
		px_draw = arch->px;
	}
	pillar_to_pillar(arch, &render_stuff);
	if (arch->wall->status == PORTAL)
	{
		arch->px.x = px_draw.x;
		set_borne_horizontal(arch);
		arch->portal.pillar = arch->pillar;
		arch->portal.next = arch->next;
		sector_tmp = arch->sector;
		arch->depth_portal++;
		if (debug == 9)
			printf("borne(%d-->%d) %d %d\n", arch->depth_portal - 1, arch->depth_portal, arch->portal.b_up[arch->sdl->size.x/2], arch->portal.b_down[arch->sdl->size.x/2]);
		sector_render(arch, player, arch->wall->link);
		arch->depth_portal--;
		arch->sector = sector_tmp;
		borne_load(arch, &render_stuff.borne_tmp, px_draw);
		if (debug == 9)
			printf("borne_load(%d) %d %d\n\n", arch->depth_portal, arch->portal.b_up[arch->sdl->size.x/2], arch->portal.b_down[arch->sdl->size.x/2]);
	}
}

/*
**	on recupere les info du pillier
**	on regarde si le mur est derriere le portail ou non
**	on reorder les info du portail
**	on rend la surface
*/
void			render_wall(t_arch *arch, t_player *player)
{
	pillar_screen_info(arch, player);
	if (arch->depth_portal == 0 || (wall_behind_portal(arch)))
	{
		render_surface(arch, player);
	}
	else if (debug_screen == 2)
		draw_wall_debug(arch, RED);
}
