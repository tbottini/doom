#include "debug.h"
#include "doom_nukem.h"
#include "render.h"

t_vct2		conv_sc_debug(t_arch *arch, t_vct2 vct)
{
	vct.x = arch->sdl->size.x / 2.0 + vct.x * arch->zoom;
	vct.y = arch->sdl->size.y / 2.0 - vct.y * arch->zoom;
	return (vct);
}

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

t_vct2		b_point_debug(t_fvct2 v, Uint32 color)
{
	t_vct2	b;
	t_screen	screen;
	t_vct2	save;
	screen = (t_screen){arch_debug_extern->sc_debug, arch_debug_extern->sdl->size.x, arch_debug_extern->sdl->size.y};
	b.x = arch_debug_extern->sdl->size.x / 2.0 + (v.x * (double)arch_debug_extern->zoom) - 1;
	b.y = arch_debug_extern->sdl->size.y / 2.0 - (v.y * (double)arch_debug_extern->zoom) - 1;
	save = b;
	bold_point_debug(b, color, &screen);
	b.x += 2;
	bold_point_debug(b, color, &screen);
	b.y += 2;
	bold_point_debug(b, color, &screen);
	b.x -= 2;
	bold_point_debug(b, color, &screen);
	return (save);
}

void		debug_segment(t_arch *arch, t_fvct2 v, t_fvct2 v2, Uint32 color, Uint32 color_wall)
{
	t_vct2	a;
	t_vct2	b;
	t_screen	screen;
	screen = (t_screen){arch->sc_debug, arch->sdl->size.x, arch->sdl->size.y};

	a = b_point_debug(v, color);
	b = b_point_debug(v2, color);
	trait(&screen, a, b, color_wall);
}

/*
**	dessine les borne actuel
*/
void		draw_borne(t_arch *arch, uint32_t color)
{
	t_affine	borne_up;
	t_affine	borne_down;
	t_vct2		point1;
	t_vct2		point2;
	t_screen	screen_tmp;

	screen_tmp = (t_screen){arch->sc_debug, arch->sdl->size.x, arch->sdl->size.y};

	borne_up.a = tan(PI180 * arch->portal.b_left);
	borne_down.a = tan(PI180 * arch->portal.b_right);
	borne_up.b = 0;
	borne_down.b = 0;
	point1.x = arch->sdl->size.x / 2.0;
	point1.y = arch->sdl->size.y / 2.0;
	point2.x = arch->sdl->size.x - 1;
	point2.y = arch->sdl->size.y / 2 - affine_val(borne_up, point2.x / 2.0);
	fill_line_debug(arch, arch->sdl, point1, point2, color);
	point2.y = arch->sdl->size.y / 2 - affine_val(borne_down, point2.x / 2.0);
	fill_line_debug(arch, arch->sdl, point1, point2, color);
}

void		draw_wall_debug(t_arch *arch, uint32_t color)
{
	t_vct2	point1;
	t_vct2	point2;

	point1.x = arch->sdl->size.x / 2.0 + (arch->pillar.x * arch->zoom);
	point1.y = arch->sdl->size.y / 2.0 - (arch->pillar.y * arch->zoom);
	point2.x = arch->sdl->size.x / 2.0 + (arch->next.x * arch->zoom);
	point2.y = arch->sdl->size.y / 2.0 - (arch->next.y * arch->zoom);
	fill_line_debug(arch, arch->sdl, point1, point2, color);

}

void		p_debug(t_fvct2 a, Uint32 color, t_arch *arch)
{
	t_vct2	v;
	t_vct2 mid;

	mid.x = arch->sdl->size.x / 2.0;
	mid.y = arch->sdl->size.y / 2.0;
	v.x = arch->sdl->size.x / 2.0 + a.x * arch->zoom;
	v.y = arch->sdl->size.y / 2.0 - a.y * arch->zoom;
	fill_line_debug(arch, arch->sdl, mid, v, color);
}

/*
**	on dessine l'affine sur une portion x de l'ecran
**	la portion est la borne de l'ecran en pixel elle sera convertie en unite
*/
void		draw_affine_portion(t_arch *arch, t_affine affine, t_fvct2 portion, uint32_t color)
{
	t_vct2	point1;
	t_vct2	point2;
	t_screen	screen_tmp;

	screen_tmp = (t_screen){arch->sc_debug, arch->sdl->size.x, arch->sdl->size.y};

	point1.x = portion.x;
	point2.x = portion.y;
	portion.x = (portion.x - arch->sdl->size.x / 2.0) / arch->zoom;
	portion.y = (portion.y - arch->sdl->size.x / 2.0) / arch->zoom;
	point1.y = arch->sdl->size.y / 2.0 - affine_val(affine, portion.x) * arch->zoom;
	point2.y = arch->sdl->size.y / 2.0 - affine_val(affine, portion.y) * arch->zoom;
	trait(&screen_tmp, point1, point2, color);
}

void		draw_affine(t_arch *arch, t_affine affine, uint32_t color, int flag)
{
	t_fvct2	portion;

	if (flag == FULL)
		portion = (t_fvct2){0, arch->sdl->size.x - 1};
	else if (flag == MID)
		portion = (t_fvct2){arch->sdl->size.x / 2, arch->sdl->size.x - 1};
	else
		return ;
	draw_affine_portion(arch, affine, portion, color);
}


void		draw_screen(t_arch *arch, uint32_t color, int px_distance, t_affine fov_affine)
{
	t_vct2	pt1;
	t_vct2	pt2;
	t_screen screen_tmp;

	screen_tmp = (t_screen){arch->sc_debug, arch->sdl->size.x, arch->sdl->size.y};
	pt1.x = arch->sdl->size.x / 2 + px_distance;
	pt2.x = pt1.x;
	pt1.y = arch->sdl->size.y / 2 + (px_distance * fov_affine.a);
	pt2.y = arch->sdl->size.y / 2 + (px_distance * -fov_affine.a);
	trait(&screen_tmp, pt1, pt2, color);
}

/*
**	dessine le frustum horizontal
*/
void		draw_frustum(t_arch *arch, int flag)
{
	t_affine		fov_affine;
	uint32_t		color;

	if (flag & FOV_HORI)
	{
		fov_affine.a = tan((arch->cam->fov / 2.0) * PI180);
		color = BLUE_SOFT;
	}
	else
	{
		fov_affine.a = tan(arch->cam->fov_ver / 2 );
		color = GREEN;
	}
	fov_affine.b = 0;
	draw_affine(arch, fov_affine, color, MID);
	fov_affine.a = -fov_affine.a;
	draw_affine(arch, fov_affine, color, MID);


	if (flag & SCREEN_ON)
	{
		draw_screen(arch, color, arch->sdl->size.x / 12, fov_affine);
	}
}



void		debug_pillar_ver(t_arch *arch, t_fvct2 surface_pillar)
{
	t_affine	fov_affine;
	int			len_screen;
	int			dist;
	t_vct2		point1;
	t_vct2		point2;
	t_screen	screen_tmp;

	dist = arch->sdl->size.x / 2.5;
	fov_affine.a = tan(arch->cam->fov_ver / 2);
	fov_affine.b = 0;
	draw_screen(arch, BLUE_SOFT, dist, fov_affine);
	len_screen = 2 * (fov_affine.a * dist);

	point1.x = dist + arch->sdl->size.x / 2;
	point2.x = dist + arch->sdl->size.x / 2;

	point1.y = len_screen * (surface_pillar.x / arch->sdl->size.y) + (arch->sdl->size.y - len_screen) / 2;
	point2.y =  len_screen * (surface_pillar.y / arch->sdl->size.y) + (arch->sdl->size.y - len_screen) / 2;
	screen_tmp = (t_screen){arch->sc_debug, arch->sdl->size.x, arch->sdl->size.y};
	trait(&screen_tmp, point1, point2, YELLOW);
}

void		debug_pillar(t_arch *arch, int flag)
{
	t_affine	a_pillar;

	if (flag & P_PILLAR || !flag)
	{
		a_pillar = (t_affine){arch->pillar.y / arch->pillar.x, 0, 0};
		if (flag & TRACE)
			draw_affine(arch, a_pillar, BLUE_SOFT, MID);
		if (flag & POINT || !flag)
			b_point_debug(arch->pillar, RED);
	}
	if (flag & P_NEXT)
	{
		a_pillar = (t_affine){arch->next.y / arch->next.x, 0, 0};
		if (flag & TRACE)
			draw_affine(arch, a_pillar, BLUE_SOFT, MID);
		if (flag & POINT)
			b_point_debug(arch->next, RED);
	}
}

void		debug_screen_copy(t_arch *arch)
{
	int		i;

	i = 0;
	while (i < arch->sdl->size.x * arch->sdl->size.y)
	{
		if (arch->sc_debug[i] != 0)
			arch->sdl->screen[i] = arch->sc_debug[i];
		i++;
	}
}

void		debug_sector_box(t_arch *arch, t_box_txtr *box, uint32_t color)
{
	t_fvct2	square[4];

	square[0] = box->start;
	square[1] = (t_fvct2){box->start.x, box->start.y + box->length.y};
	square[2] = (t_fvct2){box->start.x + box->length.x, box->start.y + box->length.y};
	square[3] = (t_fvct2){box->start.x + box->length.x, box->start.y};
	debug_segment(arch, square[0], square[1], color, color);
	debug_segment(arch, square[1], square[2], color, color);
	debug_segment(arch, square[2], square[3], color, color);
	debug_segment(arch, square[3], square[0], color, color);
}

void		sdl_line(t_sdl *sdl, t_vct2 a, t_vct2 b, uint32_t color)
{
	t_screen	screen_tmp;

	screen_tmp = (t_screen){sdl->screen, sdl->size.x, sdl->size.y};
	trait(&screen_tmp, a, b, color);
}

void		debug_repr(t_arch *arch, int x, int y, uint32_t color)
{
	if (y > arch->sdl->size.y)
		printf("overwritting debug repr\n");
	else
		arch->sc_debug[x + arch->sdl->size.x * (arch->sdl->size.y / 2 + y)] = color;
}