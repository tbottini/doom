/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfileeditor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 21:39:35 by magrab            #+#    #+#             */
/*   Updated: 2019/08/12 13:27:01 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#define EDITORSTEPX 100.0
#define EDITORSTEPY -100.0

void		add_prop(t_game *game, t_editor *edit, t_sector *gamesec)
{
	int			y;
	t_prop		*prop;
	t_entity	*ent;

	y = 0;
	while (y < gamesec->len_prop)
	{
		prop = &gamesec->props[y];
		ent = ft_enemypushend(&edit->ennlist,
			(t_vct2){prop->pos.x * EDITORSTEPX, prop->pos.y * EDITORSTEPY},
			prop->type, find_secteur(edit->sectors, game, prop->sector));
		fill_ent(edit->sectors, game, ent, prop);
		y++;
	}
}

void		add_wall_prop(t_game *g, t_editor *e, t_wall *gamewall, t_mur *mur)
{
	int			y;
	t_prop		*prop;
	t_entity	*ent;

	y = 0;
	while (y < gamewall->nb_props)
	{
		prop = &gamewall->props[y];
		ent = ft_enemypushend(&mur->wproplist,
			(t_vct2){prop->pos.x * EDITORSTEPX, prop->pos.y * EDITORSTEPY},
			prop->type, find_secteur(e->sectors, g, prop->sector));
		y++;
	}
}

void		add_enemies(t_editor *e, t_sector *gsec, t_secteur *sec)
{
	t_enemy		*enn;

	enn = gsec->enemys;
	while (enn)
	{
		ft_enemypushend(&e->ennlist, (t_vct2){enn->stat.pos.x * EDITORSTEPX,
			enn->stat.pos.y * EDITORSTEPY}, enn->type, sec);
		enn = enn->next;
	}
}

void		lil_game_to_editor(t_game *g, t_editor *e, int x)
{
	t_secteur *sec;

	sec = push_secteur(&e->sectors, find_texture(e->txtrgame, e->txtrname,
		g->surfpath[g->sectors[x].txtrtop.id]), find_texture(e->txtrgame,
		e->txtrname, g->surfpath[g->sectors[x].txtrsol.id]));
	sec->htop = g->sectors[x].h_ceil * EDITORSTEPX;
	sec->hsol = g->sectors[x].h_floor * EDITORSTEPX;
	sec->gravity = ((g->sectors[x].gravity.z == G_MOON));
}

int			game_to_editor(t_game *g, t_editor *e)
{
	int			x;
	t_secteur	*sec;

	x = -1;
	while (++x < g->len.nb_pills)
		ft_pillarpushend(&e->pillist, (t_vct2){g->pillars[x].p.x * EDITORSTEPX,
			g->pillars[x].p.y * EDITORSTEPY});
	x = -1;
	while (++x < g->len.nb_sects)
		lil_game_to_editor(g, e, x);
	e->player.stat.pos.x = g->player.stat.pos.x * EDITORSTEPX;
	e->player.stat.pos.y = g->player.stat.pos.y * EDITORSTEPY;
	e->player.stat.roty = g->player.stat.rot.y + 90.0;
	e->player.stat.sector = find_secteur(e->sectors, g, g->player.stat.sector);
	sec = e->sectors;
	x = 0;
	while (x < g->len.nb_sects)
	{
		add_walls(g, e, &g->sectors[x], sec);
		add_prop(g, e, &g->sectors[x]);
		add_enemies(e, &g->sectors[x], sec);
		sec = sec->next;
		x++;
	}
	return (0);
}
