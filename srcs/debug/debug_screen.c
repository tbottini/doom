#include "doom_nukem.h"

t_vct2		hot_point(t_fvct2 vct, t_vct2 size_s)
{
	t_vct2	px;
	double	rap;

	px.x = ((vct.x + 10.0) / 20.0) * size_s.x;
	rap = 20.0 / (double)size_s.x * (double)size_s.y;
	px.y = ((vct.y + rap/2.0) / rap) * size_s.y;
	return (px);
}

void		bold_point(t_vct2 v, Uint32 color, t_doom *doom)
{
	int tmp;

	tmp = v.y * doom->sdl.size.x;
	if (v.y > 0 && v.y < (doom->sdl.size.y - 1) && (v.x < doom->sdl.size.x - 1) && v.x > 0)
	{
		doom->sdl.screen[v.x + tmp] = color;
		doom->sdl.screen[v.x + 1 + tmp] = color;
		doom->sdl.screen[v.x - 1 + tmp] = color;
		doom->sdl.screen[v.x + 1 + tmp + doom->sdl.size.x] = color;
		doom->sdl.screen[v.x - 1 + tmp + doom->sdl.size.x] = color;
		doom->sdl.screen[v.x + 1 + tmp - doom->sdl.size.x] = color;
		doom->sdl.screen[v.x - 1 + tmp - doom->sdl.size.x] = color;
		doom->sdl.screen[v.x + tmp + doom->sdl.size.x] = color;
		doom->sdl.screen[v.x + tmp - doom->sdl.size.x] = color;
	}
}

void		debug_up(t_doom *doom)
{
	int i;
	t_vct2	cursor;
	t_vct2	cursor2;
	t_wall	*wall;

	i = 0;
	wall = doom->sector->wall;
	ft_bzero(doom->sdl.screen, doom->sdl.size.x * doom->sdl.size.y);
	cursor = hot_point(*(t_fvct2*)&doom->player.pos, doom->sdl.size);
	bold_point(cursor, RED_WALL, doom);
	i = 0;
	cursor = hot_point(*(t_fvct2*)&wall[0].pillar, doom->sdl.size);
	while (i < doom->sector->len)
	{
		cursor2 = hot_point(*(t_fvct2*)&wall[i + 1].pillar, doom->sdl.size);
		bold_point(cursor, INT_MAX, doom);
		trait(doom, cursor, cursor2, INT_MAX);
		i++;
		cursor = cursor2;
	}
	sdl_MultiRenderCopy(&doom->sdl);
}
