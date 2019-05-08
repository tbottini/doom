#include "doom_nukem.h"

/*
**	1.on recupere la distance
**	on determine la taille sol/plafond/mur
**	2.on recupere la hauteur du mur et du joueur
**	le mur et place au millieur la difference du joueur et du sol
**	determine la hauteur suplementaire du mur
**	ce qui est en dessous est le sol
**	//les sous secteur
*/

void		draw_part(t_doom doom, int *istart, int length, uint32_t color)
{
	int		i;

	i = 0;
	while (i < length)
	{
		doom.sdl.screen[*istart] = color;
		*istart += doom.sdl.size.x;
		i++;
	}
}

/*	!!!!on commence le dessin en partant du bas
**	on determine le coeficient pour la changement de taille du mur
**	en fonction du prochain mur
**	on augmente cette index pour chaque pixel
*/

void		draw_wall(t_doom doom, int px, float dist)
{
	float	column_size;
	int		sky_size;
	int		i;
	int		cursor;
	float	coef_mur;
	int		iprint;

	cursor = px;
	//il faut recupere deux distance
	i = -1;

	iprint = px;

	draw_part(doom, &iprint, 100, INT_MAX);
	//dist *= cos(fabs(wolf->rot - ray.angle) * PI / 180.00);
	column_size = doom.sdl.size.y / dist;
	sky_size =  (doom.sdl.size.y - (int)column_size) / 2;
	iprint = px;
	printf("column_size=====%d/%d====\n", (int)column_size, doom.sdl.size.y);
	printf("column_id  -----%d------\n", px);
	draw_part(doom, &iprint, sky_size, BLUE_SKY);
	draw_part(doom, &iprint, column_size, INT_MAX);
	sky_size += ((doom.sdl.size.y - (int)column_size) % 2);
	draw_part(doom, &iprint, sky_size, PINK_FLOOR);
}
