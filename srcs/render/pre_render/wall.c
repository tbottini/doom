/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 21:55:18 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/13 04:24:57 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "calcul.h"

/*
**	trouve l'intersection entre le mur et un angle donne
**	renvoie le pourcentage de l'intersection par rapport au mur (debut pilier)
*/

double		wall_clipping(t_arch *arch, t_player *p,
		t_fvct2 *inter_local, double angle)
{
	t_fvct3		inter;
	t_fvct2		d;
	t_fvct2		d2;
	t_fvct3		t;

	d = (t_fvct2){arch->wall->pillar->p.x - p->stat.pos.x,
		arch->wall->pillar->p.y - p->stat.pos.y};
	d2 = (t_fvct2){arch->wall->next->p.x - p->stat.pos.x,
		arch->wall->next->p.y - p->stat.pos.y};
	t.x = tan(angle * PI180);
	if (d2.x == d.x && d2.x == d.x)
		inter = (t_fvct3){d.x, d.x * t.x, (d2.y - inter.y) / (d2.y - d.y)};
	else
	{
		t.y = (d2.y - d.y) / (d2.x - d.x);
		t.z = d.y - d.x * t.y;
		inter.x = t.z / (t.x - t.y);
		inter.y = t.y * inter.x + t.z;
		inter.z = (d2.x - inter.x) / (d2.x - d.x);
	}
	inter_local->y = hypothenuse((t_fvct2){inter.x, inter.y});
	inter_local->x = cos((angle - p->stat.rot.y) * PI180) * inter_local->y;
	inter_local->y = sin((angle - p->stat.rot.y) * PI180) * inter_local->y;
	return (inter.z);
}

/*
**	va separer la porte en deux partie un portail et un mur
*/

static void	if_door_visible(t_arch *arch, t_player *player,
		t_fvct2 i, double po)
{
	int				px_tmp;
	double			shift_txtr_tmp;
	t_fvct2			next_tmp;

	px_tmp = arch->px.y;
	shift_txtr_tmp = arch->shift_txtr.y;
	next_tmp = arch->next;
	arch->px.y = arch->sdl->size.x / 2 - arch->sdl->size.x / 2 * (i.y / i.x);
	arch->next = i;
	arch->shift_txtr.x = 1 - po + (1 - arch->shift_txtr.x);
	if (arch->shift_txtr.y > 1 - po)
		arch->shift_txtr.y = 1 - (arch->shift_txtr.y - (1 - po));
	else
		arch->shift_txtr.y = 1;
	arch->wall->status = WALL;
	reorder(arch);
	render_surface(arch, player);
	arch->wall->status = PORTAL;
	arch->px.x = arch->px.y;
	arch->px.y = px_tmp;
	arch->pillar = arch->next;
	arch->next = next_tmp;
	arch->shift_txtr = (t_fvct2){arch->shift_txtr.y, shift_txtr_tmp};
	reorder(arch);
	render_surface(arch, player);
}

void		lil_door_split(t_arch *arch, t_player *player)
{
	arch->wall->status = PORTAL;
	reorder(arch);
	render_surface(arch, player);
}

void		door_split(t_arch *arch, t_player *player, int flag)
{
	double			po;
	double			pl;
	t_fvct2			inter;

	po = (arch->timestamp - arch->wall->ots) / ((double)DOOR_OPEN_TIME);
	if (flag == OPEN_DOOR)
		po = 1 - po;
	if (po > 1)
		po = 1;
	if (po < 0)
		po = 0;
	pl = (arch->shift_txtr.x - (1 - po))
		/ (arch->shift_txtr.x - arch->shift_txtr.y);
	if (pl > 1)
		inter = arch->next;
	else
		inter = (t_fvct2){arch->pillar.x + pl * (arch->next.x - arch->pillar.x),
			arch->pillar.y + pl * (arch->next.y - arch->pillar.y)};
	if (arch->shift_txtr.y > 1)
		return ;
	if (1 - arch->shift_txtr.x < po)
		if_door_visible(arch, player, inter, po);
	else
		lil_door_split(arch, player);
	arch->wall->status = flag;
}
