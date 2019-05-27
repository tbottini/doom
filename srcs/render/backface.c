#include "doom_nukem.h"

/*
**	on recupere la distance brut
**	on la convertit en profondeur
**	on la compare a celle actuelle via l'index
**		si elle est plus proche on renvoie 1 pour qu'on puisse
**		calculer et afficher la colomne
*/
int			z_line_buffer(t_doom doom, double dist, int px)
{
	static int ap = 0;
	double	deep;
	double	angle;

	ap++;
	//determiner l'angle du pillier par rapport au point de vue du
	//joueur avec l'id du pixel
	angle = ((double)px / doom.sdl.size.x) * doom.player.fov - (doom.player.fov / 2.0);
	deep = sin(-fabs(angle) * PI180) * dist;
	if (ap % 100 == 0)
	{
		//printf("px %d angle %f\n", px , angle);
		printf("angle %f dist %f deep %f\n", angle, dist, deep);
	}
	if (deep < doom.zline[px])
	{
		doom.zline[px] = deep;
		return (1);
	}
	return (0);
}