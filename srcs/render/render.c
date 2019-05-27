#include "doom_nukem.h"

void				sector_render(t_doom *doom, t_sector *sector)
{
	t_wall			*bunch[50];

	sector_frustum(sector, doom->player);
	buncherisation(*sector, bunch);
	bunch_comsuption(doom, bunch);
}


int					doom_render(t_doom *doom)
{
	//portal_engine(doom);

	//on rend un modele

	sector_render(doom, doom->sector);
	if (doom->sector->len_sub)
		sector_render(doom, &doom->sector->ssector[0]);
	minimap(doom);
	sdl_present(&doom->sdl);
	ft_bzero(doom->zline, sizeof(double) * doom->sdl.size.x);
	return (1);
}
