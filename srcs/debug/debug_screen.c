#include "doom_nukem.h"

t_vct2		hot_point(t_fvct2 vct, t_vct2 size_s)
{
	t_vct2	px;
	float	rap;

	px.x = ((vct.x + 10.0) / 20.0) * size_s.x;
	rap = 20.0 / (float)size_s.x * (float)size_s.y;
	px.y = ((vct.y + rap/2.0) / rap) * size_s.y;
	return (px);
}

void		point_gras(t_vct2 cursor, uint32_t color, t_doom *doom)
{
	doom->sdl.screen[cursor.x + cursor.y * doom->sdl.size.x] = color;
	doom->sdl.screen[(cursor.x + 1) + cursor.y * (doom->sdl.size.x)] = color;
	doom->sdl.screen[(cursor.x - 1) + cursor.y * (doom->sdl.size.x)] = color;
	doom->sdl.screen[cursor.x + (cursor.y + 1)* doom->sdl.size.x] = color;
	doom->sdl.screen[(cursor.x + 1) + (cursor.y + 1)* (doom->sdl.size.x)] = color;
	doom->sdl.screen[(cursor.x - 1) + (cursor.y + 1)* (doom->sdl.size.x)] = color;
	doom->sdl.screen[cursor.x + (cursor.y - 1) * doom->sdl.size.x] = color;
	doom->sdl.screen[(cursor.x + 1) + (cursor.y - 1) * (doom->sdl.size.x)] = color;
	doom->sdl.screen[(cursor.x - 1) + (cursor.y - 1) * (doom->sdl.size.x)] = color;
}


void		debug_up(t_doom *doom)
{
	int i;
	t_vct2	cursor;
	t_vct2	cursor2;
	t_wl	*wall;

	i = 0;
	//taille de la map max = 10.0
	wall = doom->sector->root_wall;
	while (doom->sdl.size.x * doom->sdl.size.y > i)
	{
		doom->sdl.screen[i] = 0;
		i++;
	}
	cursor = hot_point(doom->player.pos, doom->sdl.size);
	point_gras(cursor, RED_WALL, doom);
	i = 0;
	cursor = hot_point(wall->pos, doom->sdl.size);
	while (i < doom->sector->len)
	{
		cursor2 = hot_point(wall->next->pos, doom->sdl.size);
		point_gras(cursor, INT_MAX, doom);
		trait(doom, cursor, cursor2, INT_MAX);
		wall = wall->next;
		i++;
		cursor = cursor2;
	}
	sdl_present(&doom->sdl);
}