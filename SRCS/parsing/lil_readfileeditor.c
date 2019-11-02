/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lil_readfileeditor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 07:16:38 by magrab            #+#    #+#             */
/*   Updated: 2019/08/13 07:16:39 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

SDL_Texture	*find_texture(SDL_Texture **txtrs, char **edpath,
	char *surfpath)
{
	int			x;

	x = 0;
	while (edpath[x] && ft_strcmp(edpath[x], surfpath))
		x++;
	return (txtrs[x]);
}

t_secteur	*find_secteur(t_lstsec secteurs, t_game *g, t_sector *sector)
{
	int			index;

	index = 0;
	while (sector != &g->sectors[index] && index < g->len.nb_sects)
		index++;
	while (index--)
		secteurs = secteurs->next;
	return (secteurs);
}

t_mur		*find_mur_in_secteur(t_lstsec secteurs, t_game *g, t_wall *wall)
{
	int			sectindex;
	int			murindex;
	t_mur		*of_the_jedi;

	sectindex = 0;
	murindex = 0;
	while (sectindex < g->len.nb_sects
		&& &g->sectors[sectindex].wall[murindex] != wall)
	{
		murindex = 0;
		while (murindex < g->sectors[sectindex].len
				&& &g->sectors[sectindex].wall[murindex] != wall)
			murindex++;
		if (&g->sectors[sectindex].wall[murindex] != wall)
			sectindex++;
	}
	while (sectindex--)
		secteurs = secteurs->next;
	of_the_jedi = secteurs->murs;
	while (murindex--)
		of_the_jedi = of_the_jedi->next;
	return (of_the_jedi);
}

static void	lil_fill_ent(t_lstsec secteurs, t_entity *ent,
	int sectindex, int murindex)
{
	t_mur		*mur;

	while (sectindex--)
		secteurs = secteurs->next;
	if (!secteurs)
		return ;
	mur = secteurs->murs;
	while (murindex--)
		mur = mur->next;
	ent->stat.mursec = secteurs;
	ent->stat.mur = mur;
}

void		fill_ent(t_lstsec secteurs, t_game *g, t_entity *ent, t_prop *prop)
{
	int			sectindex;
	int			murindex;

	if (!prop->wall)
	{
		ent->stat.mur = NULL;
		ent->stat.mursec = NULL;
		return ;
	}
	sectindex = 0;
	murindex = 0;
	while (sectindex < g->len.nb_sects && murindex < g->sectors[sectindex].len
		&& &g->sectors[sectindex].wall[murindex] != prop->wall)
	{
		murindex = 0;
		while (murindex < g->sectors[sectindex].len
				&& &g->sectors[sectindex].wall[murindex] != prop->wall)
			murindex++;
		if (&g->sectors[sectindex].wall[murindex] != prop->wall)
			sectindex++;
	}
	if (&g->sectors[sectindex].wall[murindex] != prop->wall)
		return ;
	lil_fill_ent(secteurs, ent, sectindex, murindex);
}
