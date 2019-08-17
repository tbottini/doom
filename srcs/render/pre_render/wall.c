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
**	arch shift_txtr .y correspond a la vision par rapport a next
**	si (arch->shift_txtr.y > 1 - percent_open)
**		alors la gauche du champ de vision a depasser la limite de la porte
**		par rapport a droite
*/
void				door_split(t_arch *arch, t_player *player, int flag)
{
	double			percent_open;
	double			percent_local;
	t_fvct2			inter;
	int				px_tmp;
	t_vct2			px_end;
	double			shift_txtr_tmp;
	t_fvct2			next_tmp;
	bool			render_portal;

	percent_open = (arch->timestamp - arch->wall->ots) / ((double)DOOR_OPEN_TIME);
	if (flag == OPEN_DOOR)
		percent_open = 1 - percent_open;
	if (percent_open > 1)
		percent_open = 1;
	if (percent_open < 0)
		percent_open = 0;

	percent_local = (arch->shift_txtr.x - (1 - percent_open)) / (arch->shift_txtr.x - arch->shift_txtr.y);
	if (percent_local > 1)
	{
		inter = arch->next;
	}
	else
	{
		inter.x = arch->pillar.x + percent_local * (arch->next.x - arch->pillar.x);
		inter.y = arch->pillar.y + percent_local * (arch->next.y - arch->pillar.y);
	}

	if (arch->shift_txtr.y > 1)
		return ;
	if (1 - arch->shift_txtr.x < percent_open)
	{
		px_tmp = arch->px.y;
		px_end.y = arch->px.y;
		shift_txtr_tmp = arch->shift_txtr.y;
		next_tmp = arch->next;
		arch->px.y = arch->sdl->size.x / 2 - arch->sdl->size.x / 2 * (inter.y / inter.x);
		px_end.x = arch->px.y;
		arch->next = inter;
		arch->shift_txtr.x = 1 - percent_open + (1 - arch->shift_txtr.x);
		if (debug == 8)
		{
			printf("arch->px wall %d %d\n", arch->px.x, arch->px.y);
		}
		render_portal = !(arch->shift_txtr.y > 1 - percent_open);

		if (!render_portal)
			arch->shift_txtr.y = 1 - (arch->shift_txtr.y - (1 - percent_open));
		else
			arch->shift_txtr.y = 1;

		arch->wall->status = WALL;
		render_surface(arch, player);
		if (render_portal)
		{
			arch->wall->status = PORTAL;
			arch->px.x = arch->px.y;
			arch->px.y = px_tmp;
			arch->px = px_end;
			arch->pillar = arch->next;
			arch->next = next_tmp;
			arch->shift_txtr.x = arch->shift_txtr.y;
			arch->shift_txtr.y = shift_txtr_tmp;
			render_surface(arch, player);
		}

	}
	else
	{
		arch->wall->status = PORTAL;
		reorder(arch);
		render_surface(arch, player);
	}
	arch->wall->status = flag;
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

	//si le pourcentage d'ouverture est plus petit que
	//le pourcentage de texture.x
	//alors on ne rend pas la porte
	//on evite les calculs faux et inutiles de l'intersection

	//besoin pour le portail ?
	//condition pour rendre le portail

	//plutot que recupere l'intersection
	//recuperer directement quel partit de chaque bord il faut calculer
	//et on recalcule selon le retour

	if (percent_local > 1)
		render_stuff->inter = arch->next;
	else
	{
		render_stuff->inter.x = arch->pillar.x + percent_local
			* (arch->next.x - arch->pillar.x);
		render_stuff->inter.y = arch->pillar.y + percent_local
			* (arch->next.y - arch->pillar.y);
	}
	render_stuff->px_inter = arch->sdl->size.x / 2 - arch->sdl->size.x / 2 * (render_stuff->inter.y / render_stuff->inter.x);
	render_stuff->st_door.x = 1 - percent_open + (1 - arch->shift_txtr.x);
	if (arch->shift_txtr.y > 1 - percent_open)
		render_stuff->st_door.y = 1 - (arch->shift_txtr.y - (1 - percent_open));
	else
		render_stuff->st_door.y = 1;
}
