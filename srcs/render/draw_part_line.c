#include "doom_nukem.h"

/*
**	rendu d'une section de shape
*/
void		draw_section(t_vct2 *cursor, t_sdl *sdl, t_fvct2 *portion, int borne, double *edge, uint32_t color)
{
	while (cursor->y < borne)
	{

		while (cursor->x <= portion->y)
		{
			++cursor->x;
			sdl->screen[cursor->x + cursor->y * sdl->size.x] = color;
		}
		portion->x += edge[0];
		portion->y += edge[1];
		cursor->x = portion->x;
		++cursor->y;
	}
}

/*
**	rendu ligne par ligne d'un shape
*/
void		draw_part_line(t_sdl *sdl, t_shape *shape, uint32_t color)
{
	double		edge[2];
	t_vct2		cursor;
	t_fvct2		portion;
	int			borne;

	borne = (shape->left.y < shape->right.y) ? shape->left.y : shape->right.y;
	edge[0] = coef_vct2(shape->up, shape->left);
	edge[1] = coef_vct2(shape->up, shape->right);
	portion.x = shape->up.x;
	if (!edge[1])
		portion.y = shape->right.x;
	else
		portion.y = shape->up.x;
	cursor.y = shape->up.y;
	cursor.x = portion.x;
	draw_section(&cursor, sdl, &portion, borne, edge, color);
	if (shape->right.y > shape->left.y)
	{
		borne = shape->right.y;
		edge[0] = coef_vct2(shape->left, shape->bot);
	}
	else
	{
		borne = shape->left.y;
		edge[1] = coef_vct2(shape->right, shape->bot);
	}
	draw_section(&cursor, sdl, &portion, borne, edge, color);
	if (shape->right.y > shape->left.y)
		edge[1] = coef_vct2(shape->right, shape->bot);
	else
		edge[0] = coef_vct2(shape->left, shape->bot);
	draw_section(&cursor, sdl, &portion, borne, edge, color);
}