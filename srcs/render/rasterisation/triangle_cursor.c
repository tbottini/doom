#include "rasterize.h"

void	sort_verticles3(t_fvct3 *verticles)
{
	int		i;
	bool	sort;
	t_fvct3	tmp;

	sort = false;
	while (!sort)
	{
		i = 0;
		sort = true;
		while (i < 2)
		{
			if (verticles[i].y > verticles[i + 1].y)
			{
				tmp = verticles[i];
				verticles[i] = verticles[i + 1];
				verticles[i + 1] = tmp;
				sort = false;
			}
			i++;
		}

	}
}

void	cursor_init(t_sdl *sdl, t_cursor *cursor, t_tri *triangle)
{
	t_fvct3		verticles[3];
	double		modulo_pixel;

	verticles[0] = triangle->v0;
	verticles[1] = triangle->v1;
	verticles[2] = triangle->v2;
	sort_verticles3((t_fvct3*)verticles);
	cursor->mid_on_left = (cross_product((t_fvct2*)&verticles[0], (t_fvct2*)&verticles[2], (t_fvct2*)&verticles[1]) < 0);
	cursor->mid_limit = verticles[1].y;
	cursor->down_limit = (verticles[2].y > sdl->size.y) ? sdl->size.y - 1 : verticles[2].y;
	cursor->long_curve = (verticles[2].x - verticles[0].x) / (verticles[2].y - verticles[0].y);
	cursor->up_curve = (verticles[1].x - verticles[0].x) / (verticles[1].y - verticles[0].y);
	cursor->down_curve = (verticles[1].x - verticles[2].x) / (verticles[1].y - verticles[2].y);
	modulo_pixel = fmod(verticles[0].y, 1.0);
	cursor->cursor.y = (verticles[0].y < 0) ? 0 : verticles[0].y;
	if (cursor->mid_on_left)
	{
		cursor->buff_cursor.y = cursor->long_curve * (modulo_pixel + cursor->cursor.y - verticles[0].y) + verticles[0].x;
		cursor->buff_cursor.x = cursor->up_curve * (modulo_pixel + cursor->cursor.y - verticles[0].y) + verticles[0].x;
	}
	else
	{
		cursor->buff_cursor.y = cursor->up_curve * (modulo_pixel + cursor->cursor.y - verticles[0].y) + verticles[0].x;
		cursor->buff_cursor.x = cursor->long_curve * (modulo_pixel + cursor->cursor.y - verticles[0].y) + verticles[0].x;
	}
	if (cursor->buff_cursor.x < 0)
		cursor->buff_cursor.x = 0;
	else if (cursor->buff_cursor.y > sdl->size.x)
		cursor->buff_cursor.y = sdl->size.x - 1;
	cursor->line = (t_vct2){(int)cursor->buff_cursor.x, (int)cursor->buff_cursor.y};
}

bool		get_next_draw_line(t_cursor *cursor, int screenx)
{
	if (cursor->cursor.y > cursor->down_limit)
		return (0);
	cursor->cursor.y++;
	if (cursor->mid_on_left)
	{
		cursor->buff_cursor.x += (cursor->cursor.y < cursor->mid_limit) ? cursor->up_curve : cursor->down_curve;
		cursor->buff_cursor.y += cursor->long_curve;
	}
	else
	{
		cursor->buff_cursor.x += cursor->long_curve;
		cursor->buff_cursor.y += (cursor->cursor.y < cursor->mid_limit) ? cursor->up_curve : cursor->down_curve;
	}
	cursor->line = (t_vct2){(int)cursor->buff_cursor.x, (int)cursor->buff_cursor.y};
	if (cursor->line.x < 0)
		cursor->line.x = 0;
	if (cursor->line.y > screenx)
		cursor->line.y = screenx - 1;
	cursor->cursor.x = cursor->line.x;
	return (1);
}

/*
**	utilise un barycentre pour avoir une texture correct
*/
void		correct_texture(t_sdl *sdl, t_tri *primary, t_vct2 *point)
{
	t_fvct2		texel;
	double		correct_depth;
	uint32_t	color;
	t_fvct3		barycentre;
	t_fvct3		normal;

	normal.x = cross_product_px((t_fvct2*)&primary->v0, (t_fvct2*)&primary->v1, point);
	normal.y = cross_product_px((t_fvct2*)&primary->v1, (t_fvct2*)&primary->v2, point);
	normal.z = cross_product_px((t_fvct2*)&primary->v2, (t_fvct2*)&primary->v0, point);
	barycentrique_coord(&barycentre, primary->area, &normal);
	correct_depth = 1 / (1 / primary->v0.z * barycentre.x + 1 / primary->v1.z * barycentre.y + 1 / primary->v2.z * barycentre.z);
	texel.x = (primary->c0.x * barycentre.x / primary->v0.z
		+ primary->c1.x * barycentre.y / primary->v1.z
			+ primary->c2.x * barycentre.z / primary->v2.z)
				* correct_depth;
	texel.y = (primary->c0.y * barycentre.x / primary->v0.z
		+ primary->c1.y * barycentre.y / primary->v1.z
			+ primary->c2.y * barycentre.z / primary->v2.z)
				* correct_depth;
	texel.x = fmod(texel.x, primary->texture.surface->w / primary->texture.repeatx) * (primary->texture.repeatx);
	texel.y = fmod(texel.y, primary->texture.surface->h / primary->texture.repeaty) * (primary->texture.repeaty);
	color = primary->texture.txtr[(int)texel.x + (int)texel.y * primary->texture.surface->w];
	sdl->screen[point->x + point->y * sdl->size.x] = color;
}

/*
**	parcours une ligne donne par le cursor
*/
void			fill_line(t_sdl *sdl, t_tri *primary, t_cursor *cursor, void (*pixel_effector)(t_sdl*, t_tri*, t_vct2*))
{
	primary->texture.repeatx = 1;
	primary->texture.repeaty = 3;

	while (cursor->cursor.x < cursor->line.y)
	{
		pixel_effector(sdl, primary, &cursor->cursor);
		cursor->cursor.x++;
	}
}


void			triangle_cursor_fill(t_sdl *sdl, t_tri primitive)
{
	t_cursor	cursor;
	cursor_init(sdl, &cursor, &primitive);


    texture_load(&primitive.texture, "wall.jpg");

    primitive.c0 = (t_vct2){0, 0};
    primitive.c1 = (t_vct2){primitive.texture.surface->w, 0};
	primitive.c2 = (t_vct2){0, primitive.texture.surface->h};

	bold_point(sdl->screen, sdl->size.x, sdl->size.y, cursor.cursor, 0xffffffff);
	primitive.area = cross_product((t_fvct2*)&primitive.v0, (t_fvct2*)&primitive.v1, (t_fvct2*)&primitive.v2);
	while (get_next_draw_line(&cursor, sdl->size.x))
	{
		bold_point(sdl->screen, sdl->size.x, sdl->size.y, cursor.cursor, 0xffffffff);
		bold_point(sdl->screen, sdl->size.x, sdl->size.y, (t_vct2){cursor.line.y, cursor.cursor.y}, 0xff0000ff);
		fill_line(sdl, &primitive, &cursor, &correct_texture);
	}
}
