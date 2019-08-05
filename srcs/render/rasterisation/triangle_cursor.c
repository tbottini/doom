#include "rasterize.h"

void	triangle_adapt_barycentre(t_triangle *triangle)
{
	double		ztmp;

	ztmp = triangle->v[0].p.y;
	triangle->v[0].p.y = triangle->v[0].p.z;
	triangle->v[0].p.z = ztmp;
	ztmp = triangle->v[1].p.y;
	triangle->v[1].p.y = triangle->v[1].p.z;
	triangle->v[1].p.z = ztmp;
	ztmp = triangle->v[2].p.y;
	triangle->v[2].p.y = triangle->v[2].p.z;
	triangle->v[2].p.z = ztmp;
}

double	cross_product(t_fvct2 *origin, t_fvct2 *vct1, t_fvct2 *vct2)
{
	double		tmp;

	tmp = (vct2->x - origin->x) * (vct1->y - origin->y);
	tmp -= (vct2->y - origin->y) * (vct1->x - origin->x);
	return (tmp);
}

double	cross_product_px(t_fvct3 *origin, t_fvct3 *vct1, t_vct2 *vct2)
{
	double		tmp;

	tmp = (vct2->x - origin->x) * (vct1->y - origin->y);
	tmp -= (vct2->y - origin->y) * (vct1->x - origin->x);
	return (tmp);
}

void	barycentrique_coord(t_fvct3 *barycentr, double area, t_fvct3 *normal)
{
	barycentr->x = fabs(normal->y / area);
	barycentr->z = fabs(normal->x / area);
	barycentr->y = fabs(normal->z / area);
}

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

void	cursor_init(t_sdl *sdl, t_cursor *cursor, t_triangle *triangle)
{
	t_fvct3		verticles[3];
	double		modulo_pixel;

	verticles[0] = triangle->v[0].p;
	verticles[1] = triangle->v[1].p;
	verticles[2] = triangle->v[2].p;
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
void		correct_texture(t_sdl *sdl, t_triangle *triangle, t_vct2 *point)
{
	t_fvct2		texel;
	double		correct_depth;
	uint32_t	color;
	t_fvct3		barycentre;
	t_fvct3		normal;

	normal.x = cross_product_px(&triangle->v[0].p, &triangle->v[1].p, point);
	normal.y = cross_product_px(&triangle->v[1].p, &triangle->v[2].p, point);
	normal.z = triangle->area - (normal.x + normal.y);
	barycentrique_coord(&barycentre, triangle->area, &normal);
	correct_depth = 1 / (barycentre.x / triangle->v[0].p.z + barycentre.y / triangle->v[1].p.z + barycentre.z / triangle->v[2].p.z);
	texel.x = (triangle->v[0].texel.x * barycentre.x
			+ triangle->v[1].texel.x * barycentre.y
			+ triangle->v[2].texel.x * barycentre.z)
			* correct_depth;
	texel.y = (triangle->v[0].texel.y * barycentre.x
			+ triangle->v[1].texel.y * barycentre.y
			+ triangle->v[2].texel.y * barycentre.z)
			* correct_depth;
	//texel.x = fmod(texel.x, triangle->texture->w / triangle->texture->repeatx) * (triangle->texture->repeatx);
	//texel.y = fmod(texel.y, triangle->texture->h / triangle->texture->repeaty) * (triangle->texture->repeaty);
	color = triangle->texture->pixels[(int)texel.x + (int)texel.y * triangle->texture->w];
	sdl->screen[point->x + point->y * sdl->size.x] = color;
}

/*
**	parcours une ligne donne par le cursor
*/
void			cursor_fill_line(t_sdl *sdl, t_triangle *triangle, t_cursor *cursor)
{
	triangle->texture->repeatx = 1;
	triangle->texture->repeaty = 3;

	while (cursor->cursor.x < cursor->line.y)
	{
		correct_texture(sdl, triangle, &cursor->cursor);
		cursor->cursor.x++;
	}
}


void			texture_mapping(t_sdl *sdl, t_triangle *triangle)
{
	t_cursor	cursor;

	triangle_adapt_barycentre(triangle);
	cursor_init(sdl, &cursor, triangle);
	triangle->v[0].texel.x /= triangle->v[0].p.z;
	triangle->v[1].texel.x /= triangle->v[1].p.z;
	triangle->v[2].texel.x /= triangle->v[2].p.z;
	triangle->v[0].texel.y /= triangle->v[0].p.z;
	triangle->v[1].texel.y /= triangle->v[1].p.z;
	triangle->v[2].texel.y /= triangle->v[2].p.z;


	//bold_point(sdl->screen, sdl->size.x, sdl->size.y, cursor.cursor, 0xffffffff);
	triangle->area = cross_product((t_fvct2*)&triangle->v[0].p, (t_fvct2*)&triangle->v[1].p, (t_fvct2*)&triangle->v[2].p);
	while (get_next_draw_line(&cursor, sdl->size.x))
	{
		//bold_point(sdl->screen, sdl->size.x, sdl->size.y, cursor.cursor, 0xffffffff);
		//bold_point(sdl->screen, sdl->size.x, sdl->size.y, (t_vct2){cursor.line.y, cursor.cursor.y}, 0xff0000ff);
		cursor_fill_line(sdl, triangle, &cursor);
	}
}
