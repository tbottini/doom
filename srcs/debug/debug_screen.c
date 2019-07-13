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

void		init_debug(t_doom *doom)
{
	t_vct2	c1;
	t_vct2	c2;

	c1.x = 0;
	c1.y = doom->sdl.size.y / 2;
	c2.x = doom->sdl.size.x;
	c2.y = doom->sdl.size.y / 2;
	ft_bzero(doom->sdl.screen, sizeof(uint32_t) * doom->sdl.size.x * doom->sdl.size.y);
	trait(doom, c1, c2, 0xffffffff);
	c1.x = doom->sdl.size.x / 2;
	c1.y = 0;
	c2.x = doom->sdl.size.x / 2;
	c2.y = doom->sdl.size.y;
	trait(doom, c1, c2, 0xffffffff);
	bold_point((t_vct2){doom->sdl.size.x / 2 + 1, doom->sdl.size.y / 2 + 1}, 0xff0000ff, doom);
}

void		debug_up(t_doom *doom)
{
	init_debug(doom);
	sdl_MultiRenderCopy(&doom->sdl);
}

void		pause_debug(t_doom *doom)
{

}