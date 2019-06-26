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
	t_fvct2			up, left, right, bot;
	t_shape			shape;

	up.x = 100;
	up.y = 100;

	left.x = 100;
	left.y = 500;

	right.x = 500;
	right.y = 100;

	bot.x = 500;
	bot.y = 500;
	shape = shape_reajust(left, bot, right, up);
	i_sector = 0;

	sector_render(doom, doom->sector);
	while (i_sector < doom->sector->len_sub)
	{
		sector_render(doom, &doom->sector->ssector[i_sector]);
		i_sector++;
	}
	minimap(doom);
	draw_part_line(&doom->sdl, &shape, 0xffffffff);
	sdl_MultiRenderCopy(&doom->sdl);
	zline_reset(&doom->tool);
	return (1);
}
