#include "rasterize.h"

double	cross_product(t_fvct2 *origin, t_fvct2 *vct1, t_fvct2 *vct2)
{
	double		tmp;

	tmp = (vct2->x - origin->x) * (vct1->y - origin->y);
	tmp -= (vct2->y - origin->y) * (vct1->x - origin->x);
	return (tmp);
}

double	cross_product_px(t_fvct2 *origin, t_fvct2 *vct1, t_vct2 *vct2)
{
	double		tmp;

	tmp = (vct2->x - origin->x) * (vct1->y - origin->y);
	tmp -= (vct2->y - origin->y) * (vct1->x - origin->x);
	return (tmp);
}

t_fvct3	*barycentrique_coord(t_fvct3 *barycentr, double area, t_fvct3 *normal)
{
	barycentr->x = normal->y / area;
	barycentr->y = normal->z / area;
	barycentr->z = normal->x / area;
	return (barycentr);
}

t_fvct2	fvct2_gen(int ac, char **av)
{
	t_fvct2	gen;

	if (ac < 3)
		exit(0);
	gen.x = atoi(av[1]);
	gen.y = atoi(av[2]);
	return (gen);
}

void		barycentr_texture(t_sdl *sdl, t_tri primary, t_texture *txtr)
{
	t_fvct3		barycentr;
	t_fvct3		normal;
	int			inprimary;
	double		area;
	t_fvct2		p;
	t_vct2		cursor;
	double		x, y;

	double	percent_depth;
	uint32_t	color;

	double	repeatx = 1;
	double	repeaty = 3;

	t_cursor	 cur;


	//cursor_init(&cur, &primary);

	p = (t_fvct2){0, 0};
	cursor = (t_vct2){0, 0};

	area = cross_product((t_fvct2*)&primary.v0, (t_fvct2*)&primary.v1, (t_fvct2*)&primary.v2);


	while (cursor.y < sdl->size.y)
	{
		while (cursor.x < sdl->size.x)
		{



			normal.x = cross_product((t_fvct2*)&primary.v0, (t_fvct2*)&primary.v1, &p);
			normal.y = cross_product((t_fvct2*)&primary.v1, (t_fvct2*)&primary.v2, &p);
			normal.z = cross_product((t_fvct2*)&primary.v2, (t_fvct2*)&primary.v0, &p);

			inprimary = (normal.x >= 0) + (normal.y >= 0) + (normal.z >= 0);

			if (inprimary == 3 || inprimary == 0)
			{
				barycentrique_coord(&barycentr, area, &normal);

				//z ==
				percent_depth = 1 / (1 / primary.v0.z * barycentr.x + 1 / primary.v1.z * barycentr.y + 1 / primary.v2.z * barycentr.z);

				// u / z
				x = ( primary.c0.x * barycentr.x / primary.v0.z
					+ primary.c1.x * barycentr.y / primary.v1.z
					+ primary.c2.x * barycentr.z / primary.v2.z );

				// v / z
				y = ( primary.c0.y * barycentr.x / primary.v0.z
					+ primary.c1.y * barycentr.y / primary.v1.z
					+ primary.c2.y * barycentr.z / primary.v2.z );

				// (u / z) / (1 / z)
				x *= percent_depth;
				y *= percent_depth;

				x = fmod(x, txtr->surface->w / repeatx) * (repeatx);
				y = fmod(y, txtr->surface->h / repeaty) * (repeaty);

				//x et y sont des composant selon z (en perspective)
 				sdl->screen[cursor.x + cursor.y * sdl->size.x] = txtr->txtr[(int)x + (int)y * txtr->surface->w];
			}




			p.x++;
			cursor.x++;
		}
		p.x = 0;
		p.y++;
		cursor.x = 0;
		cursor.y++;
	}
}

void			render_triangle(t_sdl *sdl)
{
	t_tri		primary;

	primary = primitive_gen(sdl);

    texture_load(&primary.texture, "wall.jpg");

    primary.c0 = (t_vct2){0, 0};
    primary.c1 = (t_vct2){primary.texture.surface->w, 0};
	primary.c2 = (t_vct2){0, primary.texture.surface->h};

	barycentr_texture(sdl, primary, &primary.texture);


/*
	// /primary.c1.y = texture.surface->h;
	// /primary.c2.x = texture.surface->w;
	// /primary.c2.y = texture.surface->h;

	//texture_show(sdl, &texture, (t_vct2){0, 0});

	primary.v0 = (t_fvct3){10, -40, 20};
	primary.v0.x /= primary.v0.z;
	primary.v0.y /= primary.v0.z;
	primary.v0.x = (1 + primary.v0.x) * 0.5 * sdl->size.x;
	primary.v0.y = (1 + primary.v0.y) * 0.5 * sdl->size.y;
	primary.c0 = (t_vct2){texture.surface->w, texture.surface->h};

	//barycentr_texture(sdl, primary, &texture);
	barycentr_texture(sdl, primary, &texture);*/
}
