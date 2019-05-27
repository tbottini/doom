#include "doom_nukem.h"

/*
**	on recupere la distance brut
**	on la convertit en profondeur
**	on la compare a celle actuelle via l'index
**		si elle est plus proche on renvoie 1 pour qu'on puisse
**		calculer et afficher la colomne
**	tout est inverse car on ne recoit pas la distance mais la taille du pillier
*/
int			z_line_buffer(t_doom doom, double len_pillar, int px)
{
	static int ap = 0;
	double	deep;
	double	angle;

	angle = ((double)px / doom.sdl.size.x) * doom.player.fov - (doom.player.fov / 2.0);
	deep = cos(fabs(angle) * PI180) * len_pillar;
	if (deep > doom.zline[px])
	{
		doom.zline[px] = deep;
		return (1);
	}
	return (0);
}