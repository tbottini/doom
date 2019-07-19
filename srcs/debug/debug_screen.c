#include "doom_nukem.h"

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

void		b_point_debug(t_arch *arch, t_fvct2 v, Uint32 color)
{
	t_vct2	b;

	b.x = arch->sdl->size.x / 2.0 + (v.x * (double)arch->zoom) - 1;
	b.y = arch->sdl->size.y / 2.0 - (v.y * (double)arch->zoom) - 1;
	bold_point_debug(b, color, arch);
	b.x += 2;
	bold_point_debug(b, color, arch);
	b.y += 2;
	bold_point_debug(b, color, arch);
	b.x -= 2;
	bold_point_debug(b, color, arch);
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

	borne_up.a = tan(PI180 * arch->bound.b_left);
	borne_down.a = tan(PI180 * arch->bound.b_right);
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

void		draw_wall(t_arch *arch, uint32_t color)
{
	t_vct2	point1;
	t_vct2	point2;

	point1.x = arch->sdl->size.x / 2.0 + (arch->depth.x * arch->zoom);
	point1.y = arch->sdl->size.y / 2.0 - (arch->decal.x * arch->zoom);
	point2.x = arch->sdl->size.x / 2.0 + (arch->depth.y * arch->zoom);
	point2.y = arch->sdl->size.y / 2.0 - (arch->decal.y * arch->zoom);
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

void		draw_affine(t_arch *arch, t_affine affine, uint32_t color)
{
	t_vct2	point1;
	t_vct2	point2;

	double	x_value;
	x_value = (arch->sdl->size.x / 2.0) / arch->zoom;
	point1.x = arch->sdl->size.x - 1;
	point1.y = arch->sdl->size.y / 2.0 - (affine.a * x_value + affine.b) * arch->zoom;
	point2.x = 0;
	point2.y = arch->sdl->size.y / 2.0 - (affine.a * -x_value + affine.b) * arch->zoom;
	trait(arch, point1, point2, color);
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

