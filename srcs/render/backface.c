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

	if (len_pillar > doom.zline[px])
	{
		doom.zline[px] = len_pillar;
		return (1);
	}
	return (0);
}

void				zline_reset(t_doom *doom)
{
	int				i;

	i = 0;
	while (i < doom->sdl.size.x)
	{
		//doom->zline[i] = X;
		doom->zline[i] = 0;
		i++;
	}
}
