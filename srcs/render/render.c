#include "doom_nukem.h"

/*
**	on recupere les information du secteur par rapport au frustum (champs de vision du joueur)
**	on definit un bunch contenant les mur visibles
**	on affiche ce bunch
*/
void				sector_render(t_doom *doom, t_sector *sector)
{
	t_wall			*bunch[50];

	sector_frustum(sector, doom->player);
	buncherisation(*sector, bunch);
	bunch_comsuption(doom, bunch, sector);
}

/*
**	on rend le secteur definit avec ses sous secteur
**	futurement appele recursivement ?
*/
void				root_sector_render(t_doom *doom, t_sector *sector)
{
	int				i_sector;

	i_sector = 0;
	sector_render(doom, sector);
	while (i_sector < sector->len_sub)
	{
		sector_render(doom, &sector->ssector[i_sector]);
		i_sector++;
	}
}

/*
**	les etapes de rendu du jeu
*/
int					doom_render(t_doom *doom)
{
	int				i;

	i = 0;
	root_sector_render(doom, doom->sector);
	minimap(doom);
	sdl_MultiRenderCopy(&doom->sdl);
	zline_reset(&doom->tool);
	while (i < doom->sdl.size.x * doom->sdl.size.y)
	{
		doom->sdl.screen[i] = 0;
		i++;
	}
	return (1);
}
