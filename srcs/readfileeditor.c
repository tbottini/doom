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

int game_to_editor(t_game *game, t_editor *edit)
{
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
