#include "doom_nukem.h"

/*
**	on recupere la distance brut
**	on la convertit en profondeur
**	on la compare a celle actuelle via l'index
**		si elle est plus proche on renvoie 1 pour qu'on puisse
**		calculer et afficher la colomne
**	tout est inverse car on ne recoit pas la distance mais la taille du pillier
*/
int			z_line_buffer(t_arch *arch, double len_pillar, int px)
{

	if (len_pillar > arch->zline[px])
	{
		arch->zline[px] = len_pillar;
		return (1);
	}
	return (0);
}

int			clean_zline(t_arch *arch, double len_pillar, int px)
{
	if (len_pillar > arch->zline[px])
	{
		arch->zline[px] = 0;
		return (1);
	}
	return (0);
}