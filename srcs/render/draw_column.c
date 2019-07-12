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

	down = -player->stat.height - (player->stat.pos.z - player->stat.sector->h_floor);
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
int		draw_part_texture(t_arch *arch, int numcol, t_vct2 surface)
{
	double	coef;
	uint32_t		px;
	double	buff;

	px = texture_interpolation2D(arch);
	buff = 0;
	coef = (double)arch->wall->txtr.h / (surface.y - surface.x);
	if (surface.y < 0)
		return (numcol + surface.y * arch->sdl->size.x);
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

/*
**
**			on donne la surface(sans le facteur largeur)
**			on convertit la valeur
**			on la trunc
*/
double		draw_part(t_arch *arch, t_vct2 surface, uint32_t color)
{
	if (surface.x <= 0)
		surface.x = arch->px.x;
	else
	{
		surface.x = surface.x * arch->sdl->size.x + arch->px.x;
		//surface.x = surface.x * arch->sdl->size.x;
	}
	if (surface.y > arch->sdl->size.y)
		surface.y = arch->px.x + (arch->sdl->size.y - 1) * arch->sdl->size.x;
	else
		surface.y = surface.y * arch->sdl->size.x;
	//printf("depassement %d %d\n", surface.x, surface.y);
	while (surface.x < surface.y)
	{
		arch->sdl->screen[surface.x] = color;
		surface.x += arch->sdl->size.x;
	}
	return (surface.x);
}

void		draw_column(t_arch *arch, t_fvct2 surface)
{
	double	cursor;
	t_vct2	surface_tmp;

	surface_tmp = (t_vct2){0, surface.x};
	cursor = draw_part(arch, surface_tmp, 0);
	surface_tmp = (t_vct2){surface.x, surface.y};
	draw_part_texture(arch, cursor, surface_tmp);
	surface_tmp = (t_vct2){surface.y, arch->sdl->size.y};
	draw_part(arch, surface_tmp, 0x272130ff);
}

/*
**	calcul la surface du portail selon la hauteur du prochain secteur
**	on calcul le pourcentage de hauteur du prochain secteur (pour le plafond puis pour le sol)
**	on fait le rapport avec la surface du mur
**	si la surface du portail est plus grand que la suface du mur on la tronque
**	-->renvoie sans le facteur largeur (arch->sdl->size.x)
*/
t_fvct2		surface_portal(t_fvct2 surface, t_sector *parent, t_sector *child)
{
	t_fvct2	s_portal;

	s_portal.y = (child->h_floor - parent->h_floor) / parent->h_ceil;
	s_portal.x = (child->h_floor - parent->h_floor + child->h_ceil) / parent->h_ceil;
	s_portal.y = surface.y - s_portal.y * (surface.y - surface.x);
	s_portal.x = surface.y - s_portal.x * (surface.y - surface.x);
	if (s_portal.x < surface.x)
		s_portal.x = surface.x;
	if (s_portal.y > surface.y)
		s_portal.y = surface.y;
	return (s_portal);
}


/*
**	on determine la surface du portail
**	on dessine : le ciel, la liaison haute du mur, le portail, la liaison basse, le sol
*/
void		draw_portal(t_arch *arch, t_player *player, t_fvct2 surface)
{
	t_fvct2		s_portal;
	t_vct2		surf;
	t_vct2		tmp;

	s_portal = surface_portal(surface, arch->sector, arch->wall->link);

	(void)player;

	tmp = (t_vct2){0, surface.x};
	surf.x = draw_part(arch, tmp, 0);
	tmp = (t_vct2){surface.x, s_portal.x};
	surf.x = draw_part_texture(arch, surf.x, tmp);
	tmp = (t_vct2){s_portal.x, s_portal.y};
	surf.x = draw_part(arch, tmp, ORANGE);
	tmp = (t_vct2){s_portal.y, surface.y};
	surf.x = draw_part_texture(arch, surf.x, tmp);
}
