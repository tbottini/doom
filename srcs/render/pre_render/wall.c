#include "render.h"
#include "calcul.h"
#include "debug.h"

/*
**	trouve l'intersection entre le mur et un angle donne
**	renvoie le pourcentage de l'intersection par rapport au mur (debut pilier)
*/
double			wall_clipping(t_arch *arch, t_player *p, t_fvct2 *inter_local, double angle)
{
	t_fvct2		inter;
	t_fvct2		diff;
	t_fvct2		diff2;
	double		coef_ang;
	double		coef_wall;
	double		b;
	double		percent;

	diff.x = arch->wall->pillar->p.x - p->stat.pos.x;
	diff.y = arch->wall->pillar->p.y - p->stat.pos.y;
	diff2.x = arch->wall->next->p.x - p->stat.pos.x;
	diff2.y = arch->wall->next->p.y - p->stat.pos.y;
	coef_ang = tan(angle * PI180);
	if (diff2.x == diff.x && diff2.x == diff.x)
	{
		inter.x = diff.x;
		inter.y = diff.x * coef_ang;
		percent = (diff2.y - inter.y) / (diff2.y - diff.y);
	}
	else
	{
		coef_wall = (diff2.y - diff.y) / (diff2.x - diff.x);
		b = diff.y - diff.x * coef_wall;
		inter.x = b / (coef_ang - coef_wall);
		inter.y = coef_wall * inter.x + b;
		percent = (diff2.x - inter.x) / (diff2.x - diff.x);
	}
	inter_local->y = hypothenuse(inter);
	inter_local->x = cos((angle - p->stat.rot.y) * PI180) * inter_local->y;
	inter_local->y = sin((angle - p->stat.rot.y) * PI180) * inter_local->y;
	return (percent);
}

/*
**	va separer la porte en deux partie un portail et un mur
*/
void				door_split(t_arch *arch, t_player *player, int flag)
{
	double			percent_open;
	double			local_percent;
	t_fvct2			inter;
	t_fvct2			tmp;
	int				px_tmp;

	percent_open = (arch->timestamp - arch->wall->ots) / ((double)DOOR_OPEN_TIME * 3);
	//printf("timestamp %d start %d DOOR_TIME %d\n", arch->timestamp, arch->wall->ots, DOOR_OPEN_TIME);

	//!!!! secur a enlever
	if (percent_open > 1)
		percent_open = 1;

	//percent_open = 0.7;

	printf("percent_open %f", percent_open);
	printf("shift_txtr %f %f\n", arch->shift_txtr.x, arch->shift_txtr.y);

	if (arch->shift_txtr.x == arch->shift_txtr.y)
		return ;

	if (percent_open > arch->shift_txtr.x)
	{
		local_percent = (percent_open - arch->shift_txtr.x) / (arch->shift_txtr.y - arch->shift_txtr.x);
		if (local_percent <= 1)
		{
			printf("local_percent %f\n", local_percent);
			inter.x = local_percent * (arch->next.x - arch->pillar.x) + arch->pillar.x;
			inter.y = local_percent * (arch->next.y - arch->pillar.y) + arch->pillar.y;
			tmp = arch->next;
			arch->next = inter;
			if (debug_screen == 2)
			{
				b_point_debug(arch->next, RED);
			}
			px_tmp = arch->px.y;
			arch->px.y = arch->sdl->size.x / 2 - ((arch->next.y / arch->next.x) * (arch->sdl->size.x / 2));
			if (arch->px.y >= arch->sdl->size.x)
				arch->px.y = arch->sdl->size.x - 1;
			arch->wall->status = WALL;
			arch->shift_txtr.x = (1 - percent_open) + arch->shift_txtr.x;
			arch->shift_txtr.y = 1;
			render_surface(arch, player);
			arch->next = tmp;
			arch->px.y = px_tmp;
			arch->wall->status = flag;
		}
		else
		{//arch->next ne change pas, si local_percent > 1 on affiche que le mur

			if (debug_screen == 2)
			{
				b_point_debug(arch->next, RED);
			}
			arch->shift_txtr.x = (1 - percent_open) + arch->shift_txtr.x;
			arch->shift_txtr.y = 1 - (percent_open - arch->shift_txtr.y);
			arch->wall->status = WALL;
			render_surface(arch, player);
			arch->wall->status = flag;
		}


	}



	if (debug_screen == 8)
	{
		fill_line_debug(arch, arch->sdl, (t_vct2){arch->px.x, arch->sdl->size.y / 2}, (t_vct2){arch->px.y, arch->sdl->size.y / 2}, 0xffffffff);
	}



}