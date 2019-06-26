#include "doom_nukem.h"

void				sector_render(t_doom *doom, t_sector *sector)
{
	t_wall			*bunch[50];

	sector_frustum(sector, doom->player);
	buncherisation(*sector, bunch);
	bunch_comsuption(doom, bunch, sector);
}

int					doom_render(t_doom *doom)
{
	int				i_sector;
	t_fvct2			a,b,c,d;

	a.x = 100;
	a.y = 100;
	b.x = 100;
	b.y = 500;
	c.x = 500;
	c.y = 100;
	d.x = 500;
	d.y = 500;
	i_sector = 0;

	sector_render(doom, doom->sector);
	while (i_sector < doom->sector->len_sub)
	{
		sector_render(doom, &doom->sector->ssector[i_sector]);
		i_sector++;
	}
	minimap(doom);
	draw_part_line(&doom->sdl, a, b, c, d);
	sdl_MultiRenderCopy(&doom->sdl);
	zline_reset(&doom->tool);
	return (1);
}
