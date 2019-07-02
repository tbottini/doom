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
t_fvct2		surface_pillar(t_arch *arch, t_player *player, double depth)
{
	t_fvct2	wall_portion;

	double	up;
	double	down;

	//hauteur du mur - hauteur du perso - la difference de position par rapport au sol + la diff du sect joueur et sectr rendu
	//si c'est un mur on prend tout
	//si c'est un portail on determine la hauteur par rapport au prochain portail
	//up = wall_height - player->stat.height - (player->stat.pos.z - player->stat.sector->h_floor);
	//printf ("player sector %f -- sector render %f\n", player->stat.sector->h_floor, arch->sector->h_floor);
	down = -player->stat.height - (player->stat.pos.z - player->stat.sector->h_floor);
	//if (arch->wall->status == PORTAL_DIRECT)
	//{
	//	down += (arch->sector->h_floor - player->stat.sector->h_floor);
	//	up = down + arch->sector->h_ceil;
	//}
	//else
	up = down + player->stat.sector->h_ceil;
	wall_portion.x = px_point(arch, player, up, depth);
	wall_portion.y = px_point(arch, player, down, depth);
	return (wall_portion);
}

/*
**	numcol index de depart
**	surface : colonne de depart et colonne de fin, (sans la multiplication avec les range)
**	-> renvoie l'index de fin
*/
int		draw_part_texture(t_arch *arch, int numcol, t_fvct2 surface)
{
	double	coef;
	int		px;
	double	buff;

	px = texture_interpolation2D(arch);
	buff = 0;
	coef = (double)arch->wall->txtr.h / (surface.y - surface.x);
	if (surface.y < 0)
		return (numcol + (int)surface.y * arch->sdl->size.x);
	if (surface.x < 0)
	{
		buff = -surface.x * coef;
		if (buff > 1.0)
		{
			px += (int)buff * arch->wall->txtr.w;
			buff = buff - (int)buff;
		}
		surface.x = 0;
	}
	while (surface.x < surface.y && surface.x < arch->sdl->size.y)
	{
		arch->sdl->screen[numcol] = arch->wall->txtr.pixels[px];
		surface.x++;
		numcol += arch->sdl->size.x;
		buff += coef;
		if (buff > 1.0)
		{
			px += (int)buff * arch->wall->txtr.w;
			buff = buff - (int)buff;
		}
	}
	return (numcol);
}

double		draw_part(t_arch *arch, t_vct2 surface, uint32_t color)
{
	while (surface.x < surface.y)
	{
		arch->sdl->screen[surface.x] = color;
		surface.x += arch->sdl->size.x;
	}
	return (surface.x);
}

void		draw_column(t_arch *arch, t_fvct2 surface)
{
	t_vct2	surf;
	int		ncol;

	ncol = arch->px.x;
	surf.x = arch->px.x;
	if (surface.x > arch->sdl->size.y)
		surf.y = arch->sdl->size.y * arch->sdl->size.x;
	else
		surf.y = (int)surface.x * arch->sdl->size.x;
	surf.x = draw_part(arch, surf, 0);
	draw_part_texture(arch, surf.x, surface);
	surf.x = ncol + ((int)surface.y) * arch->sdl->size.x;
	if (surface.y < 0)
		surf.x = ncol;
	surf.y = arch->sdl->size.y * arch->sdl->size.x;
	draw_part(arch, surf, 0x272130ff);
}

void		draw_portal(t_arch *arch, t_player *player, t_fvct2 surface)
{
	t_fvct2		surface_portal;
	t_fvct2		surface_tmp;
	t_vct2		surf;
	t_sector	*parent;
	t_sector	*child;

	child = arch->sector;
	parent = player->stat.sector;
	surface_portal.y = (child->h_floor - parent->h_floor) / parent->h_ceil;
	surface_portal.y = surface.y - surface_portal.y * (surface.y - surface.x);
	surface_portal.x = (child->h_floor - parent->h_floor + child->h_ceil) / parent->h_ceil;
	surface_portal.x = surface.y - surface_portal.x * (surface.y - surface.x);
	if (surface_portal.x < surface.x)
		surface_portal.x = surface.x;
	if (surface_portal.y > surface.y)
		surface_portal.y = surface.y;
	surf.x = arch->px.x;

	if (surface.x > arch->sdl->size.y)
		surf.y = arch->sdl->size.y * arch->sdl->size.x;
	else
		surf.y = (int)surface.x * arch->sdl->size.x;
	surf.x = draw_part(arch, surf, 0);
	surface_tmp.x = surface.x;
	surface_tmp.y = surface_portal.x;
	surf.x = draw_part_texture(arch, surf.x, surface_tmp);
	if (surface_tmp.y < 0)
		surf.x = arch->px.x;
	if (surface_portal.y > arch->sdl->size.y)
		surf.y = (arch->sdl->size.y - 1) * arch->sdl->size.x + arch->px.x;
	else
		surf.y = arch->px.x + ((int)surface_portal.y - 1) * arch->sdl->size.x;
	surf.x = draw_part(arch, surf, ORANGE);
	surface_tmp.y = surface.y;
	surface_tmp.x = surface_portal.y;
	draw_part_texture(arch, surf.x, surface_tmp);
	surf.x = arch->px.x + ((int)surface.y) * arch->sdl->size.x;
	if (surface.y < 0)
		surf.x = arch->px.x;
	surf.y = arch->sdl->size.y * arch->sdl->size.x;
	draw_part(arch, surf, 0x272130ff);
}
