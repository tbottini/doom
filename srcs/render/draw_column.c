#include "doom_nukem.h"

/*
**	renvoie la position en pixel d'un point
*/
int			px_point(t_designer *arch, t_player *player, double h_diff, double depth_wall)
{
	double	wall_angle;
	double	limit_angle;
	int px;
	double	player_angle;


	player_angle = (player->stat.rot.x - 90) * PI180;

	limit_angle = (player->fov / 2) * (M_PI / 180.0);
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
t_fvct2		surface_pillar(t_designer *arch, t_player *player, double depth)
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

void		draw_part_texture(t_designer *arch, t_wall *wall, int numcol, t_fvct2 surface)
{
	double	coef;
	int		px;
	double	buff;
	int		ncol;

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
		if (px < 0)
			printf("px %d\n", px);
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

double		draw_part(t_designer *arch, t_vct2 surface, uint32_t color)
{
	while (surface.x < surface.y)
	{
		arch->sdl->screen[surface.x] = color;
		surface.x += arch->sdl->size.x;
	}
	return (surface.x);
}

void		draw_sky(t_designer *arch, t_fvct2 surface)
{

}

void		draw_column(t_designer *arch, t_wall *wall, int numcol, t_fvct2 surface)
{
	t_vct2	surf;
	int		ncol;

	ncol = numcol;
	surf.x = numcol;
	surf.y = (int)surface.x * arch->sdl->size.x;
	if (surface.x > arch->sdl->size.y)
		surf.y = arch->sdl->size.y * arch->sdl->size.x;
	else
		surf.y = (int)surface.x * arch->sdl->size.x;
	surf.x = draw_part(arch, surf, BLUE_SKY);
	draw_part_texture(arch, wall, surf.x, surface);
	surf.x = ncol + ((int)surface.y + 1) * arch->sdl->size.x;
	if (surface.y < 0)
		surf.x = ncol;
	surf.y = arch->sdl->size.y * arch->sdl->size.x;
	draw_part(arch, surf, 0x272130ff);
}

void		draw_portal(t_designer *arch, t_player *player, t_fvct2 surface)
{
	t_fvct2	surface_up;
	t_fvct2	surface_down;
	t_fvct2	surface_portal;

	surface_portal.x = (arch->sector->h_ceil / player->stat.sector->h_ceil) * (surface.y - surface.x) + surface.x;
	surface_portal.y = surface.y - (arch->sector->h_floor / player->stat.sector->h_floor) * (surface.y - surface.x);
	surface_up.x = surface_portal.x - surface.x;
	surface_up.y = surface_portal.y - surface.y;

}


