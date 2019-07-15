/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 21:39:35 by magrab            #+#    #+#             */
/*   Updated: 2019/07/10 17:09:52 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#define EDITORSTEPX 100.0
#define EDITORSTEPY -100.0

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
			ft_wallpushend(&sec->murs, find_pillar_from_game(game->pillars, game->sectors[x].wall[y].pillar, edit->pillist), find_pillar_from_game(game->pillars, game->sectors[x].wall[y].next, edit->pillist), edit->txtrgame[0]);
			y++;
		}
		sec = sec->next;
		x++;
	}
	return (0);
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
		free_gamemap(&game);
		return (-2);
	}
	free_gamemap(&game);
	ft_putendl("Successfully read ressources/map/editor.map\n");
	return (0);
}
