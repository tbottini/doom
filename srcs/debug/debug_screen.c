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

	//on soustrait chaque valeurs qui devrait etre ajoute pcq screen est inverse



	point1.x = arch->sdl->size.x / 2.0;
	point1.y = arch->sdl->size.y / 2.0;

	point2.x = arch->sdl->size.x - 1;
	point2.y = arch->sdl->size.y / 2 - affine_val(borne_up, point2.x / 2.0);

	fill_line_debug(arch, arch->sdl, point1, point2, color);

	point2.y = arch->sdl->size.y / 2 - affine_val(borne_down, point2.x / 2.0);

	fill_line_debug(arch, arch->sdl, point1, point2, color);

	//on recupere le decalage sur quand on atteint le bord de l'ecran a partir du millieu

}

void		draw_wall(t_arch *arch, uint32_t color)
{
	t_vct2	point1;
	t_vct2	point2;

	point1.x = arch->sdl->size.x / 2.0 + (arch->depth.x * 40);
	point1.y = arch->sdl->size.y / 2.0 - (arch->decal.x * 40);
	point2.x = arch->sdl->size.x / 2.0 + (arch->depth.y * 40);
	point2.y = arch->sdl->size.y / 2.0 - (arch->decal.y * 40);

	fill_line_debug(arch, arch->sdl, point1, point2, color);

}

void		debug_screen_copy(t_arch *arch)
{
	int		i;

	i = 0;
	while (i < arch->sdl->size.x * arch->sdl->size.y)
	{
		if (arch->sc_debug[i] != 0)
		{
			//printf("pixel ecrit\n");
			arch->sdl->screen[i] = arch->sc_debug[i];
		}
		i++;
	}
}

