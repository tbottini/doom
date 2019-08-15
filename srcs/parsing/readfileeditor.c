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

void add_prop(t_game *game, t_editor *edit, t_sector *gamesec)
{
	int y;
	t_prop *prop;
	t_entity *ent;

	y = 0;
	while (y < gamesec->len_prop)
	{
		prop = &gamesec->props[y];
		ent = ft_enemypushend(&edit->ennlist, (t_vct2){prop->pos.x * EDITORSTEPX, prop->pos.y * EDITORSTEPY}, prop->type, find_secteur(edit->sectors, game, prop->sector));
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

void		lil_relink_sector(t_game *g, t_editor *e, t_mur *mur, t_vct3 id)
{
	t_entity			*ent;

	if (mur->portal_id != WALL)
		mur->portal_ptr = find_secteur(e->sectors, g,
			g->sectors[id.x].wall[id.y].link);
	id.z = 0;
	ent = mur->wproplist;
	while (ent)
	{
		fill_ent(e->sectors, g, ent,
			&g->sectors[id.x].wall[id.y].props[id.z]);
		ent = ent->next;
		id.z++;
	}
}

int			relink_sector(t_game *g, t_editor *e)
{
	t_secteur			*secteur;
	t_mur				*mur;
	t_vct3				id;

	id.x = 0;
	secteur = e->sectors;
	while (secteur)
	{
		id.y = 0;
		mur = secteur->murs;
		while (mur)
		{
			lil_relink_sector(g, e, mur, id);
			mur = mur->next;
			id.y++;
		}
		secteur = secteur->next;
		id.x++;
	}
	return (1);
}

int			read_file_to_editor(t_editor *e, const char *file)
{
	t_game	g;
	int		returncode;
	char	path[512];

	ft_strcpy(path, "ressources/map/");
	ft_strcpy(&(path[15]), file);
	ft_bzero(&g, sizeof(t_game));
	if ((returncode = read_file(&g, path, true)))
	{
		printf("Error : %d\n", returncode);
		return (-1);
	}
	if (game_to_editor(&g, e))
	{
		free_game(&g);
		return (-2);
	}
	relink_sector(&g, e);
	free_game(&g);
	ft_putendl("Successfully read ressources/map/editor.map\n");
	e->map = e->sectors;
	if (!(e->player.stat.sector))
		e->player.stat.sector = e->map;
	e->status = ED_LOADED;
	return (0);
}
