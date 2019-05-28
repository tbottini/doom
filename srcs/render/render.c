#include "doom_nukem.h"

void				sector_render(t_doom *doom, t_sector *sector)
{
	t_wall			*bunch[50];

	sector_frustum(sector, doom->player);
	buncherisation(*sector, bunch);
	bunch_comsuption(doom, bunch);
}


void				zline_reset(t_doom *doom)
{
	int				i;

	i = 0;
	while (i < doom->sdl.size.x)
	{
		doom->zline[i] = ULONG_MAX;
		i++;
	}
}

int					doom_render(t_doom *doom)
{
	int				i_sector;

	i_sector = 0;
	sector_render(doom, doom->sector);

	while (i_sector < doom->sector->len_sub)
	{
		sector_render(doom, &doom->sector->ssector[i_sector]);
		i_sector++;
	}
	minimap(doom);
	sdl_present(&doom->sdl);
	ft_bzero(doom->zline, sizeof(double) * doom->sdl.size.x);
	return (1);
}
