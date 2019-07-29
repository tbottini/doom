/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfileeditor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 21:39:35 by magrab            #+#    #+#             */
/*   Updated: 2019/07/20 22:41:36 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#define EDITORSTEPX 100.0
#define EDITORSTEPY -100.0

t_secteur		*find_secteur(t_lstsec secteurs, t_sector *stock_sector, t_sector *sector)
{
	int			index;

	index = 0;
	while (sector != &stock_sector[index])
		index++;
	while (index--)
		secteurs = secteurs->next;
	return (secteurs);

}

t_pilier *find_pillar_from_game(t_pillar *pillars, t_pillar *to_find, t_lstpil pillst)
{
	int x;

	x = 0;
	while (&(pillars[x]) != to_find)
	{
		pillst = pillst->next;
		x++;
	}
	return (pillst);
}

int game_to_editor(t_game *game, t_editor *edit)
{
	int x;
	int y;
	t_vct2 pos;
	t_secteur *sec;
	t_mur	*mur;

	x = 0;
	while (x < game->len.nb_pills)
	{
		pos.x = game->pillars[x].p.x * EDITORSTEPX;
		pos.y = game->pillars[x].p.y * EDITORSTEPY;
		ft_pillarpushend(&edit->pillist, pos);
		x++;
	}
	x = 0;
	while (x < game->len.nb_sects)
	{
		push_secteur(&edit->sectors, edit->txtrgame[0], edit->txtrgame[0]);
		x++;
	}
	sec = edit->sectors;
	x = 0;
	while (x < game->len.nb_sects)
	{
		y = 0;
		while (y < game->sectors[x].len)
		{
			mur = ft_wallpushend(&sec->murs, find_pillar_from_game(game->pillars, game->sectors[x].wall[y].pillar, edit->pillist), find_pillar_from_game(game->pillars, game->sectors[x].wall[y].next, edit->pillist), edit->txtrgame[0]);
			mur->portal_id = game->sectors[x].wall[y].status;
			y++;
		}
		sec = sec->next;
		x++;
	}
	return (0);
}

int	relink_sector(t_game *game, t_editor *edit)
{
	t_secteur			*secteur;
	t_mur				*mur;
	int					idsec;
	int					idmur;

	idsec = 0;
	secteur = edit->sectors;
	while (secteur)
	{
		idmur = 0;
		mur = secteur->murs;
		while (mur)
		{
			// Parcours
			if (ISPORTAL(mur->portal_id))
				mur->portal_ptr = find_secteur(edit->sectors, game->sectors, game->sectors[idsec].wall[idmur].link);

			mur = mur->next;
			idmur++;
		}
		secteur = secteur->next;
		idsec++;
	}
	return (1);
}

int	read_file_to_editor(t_editor *edit, const char *file)
{
	t_game	game;
	int		returncode;
	t_slen	len;

	if ((returncode = read_file(&game, file)))
	{
		return (-1);
	}
	if (game_to_editor(&game, edit))
	{
		free_game(&game);
		return (-2);
	}
	relink_sector(&game, edit);
	free_game(&game);
	ft_putendl("Successfully read ressources/map/editor.map\n");
	return (0);
}
