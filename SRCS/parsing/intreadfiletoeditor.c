/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intreadfiletoeditor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 21:08:41 by magrab            #+#    #+#             */
/*   Updated: 2019/08/15 21:08:42 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

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
		ft_printf("Error : %d\n", returncode);
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
