#include "render.h"
#include "calcul.h"
#include "debug.h"

int				is_door(t_arch *arch)
{
	return (arch->wall->status == OPEN_DOOR || arch->wall->status == CLOSE_DOOR);
}


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
**	compare a door_split
**	door_split info ne rend pas le mur mais prepare les info pour le rendu avec
**		pillar_to_pillar
**	on determine le taux d'ouverture de la porte
**	la position du bout de la porte, son px, les nouveau shift_txtr de la
**		texture pour la porte
**	il y aura une fonction en aval qui determinera si la colonne rendu est une
**		partie
**	mur ou une partie portail
*/

void			door_split_info(t_arch *arch, t_pil_render *render_stuff, int flag)
{
	double			percent_open;
	double			percent_local;

	render_stuff->open_invert = (arch->px.x > arch->px.y);
	percent_open = (arch->timestamp - arch->wall->ots) / ((double)DOOR_OPEN_TIME);
	if (flag == OPEN_DOOR)
		percent_open = 1 - percent_open;
	if (percent_open > 1)
		percent_open = 1;
	if (percent_open < 0)
		percent_open = 0;
	render_stuff->perc_open = percent_open;
	percent_local = (arch->shift_txtr.x - (1 - percent_open))
		/ (arch->shift_txtr.x - arch->shift_txtr.y);
	if (percent_local > 1)
		render_stuff->inter = arch->next;
	else if (percent_local < 0)
		render_stuff->inter = arch->pillar;
	else
	{
		render_stuff->inter.x = arch->pillar.x + percent_local
			* (arch->next.x - arch->pillar.x);
		render_stuff->inter.y = arch->pillar.y + percent_local
			* (arch->next.y - arch->pillar.y);
	}
	if (render_stuff->inter.x < 0)
	{
		render_stuff->px_inter = arch->px.x;
		return ;
	}
	render_stuff->px_inter = arch->sdl->size.x / 2 - arch->sdl->size.x / 2 * (render_stuff->inter.y / render_stuff->inter.x);
	render_stuff->st_door.x = 1 - percent_open + (1 - arch->shift_txtr.x);
	if (arch->shift_txtr.y > 1 - percent_open)
		render_stuff->st_door.y = 1 - (arch->shift_txtr.y - (1 - percent_open));
	else
		render_stuff->st_door.y = 1;
}
