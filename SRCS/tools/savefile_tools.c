/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savefile_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 05:16:44 by magrab            #+#    #+#             */
/*   Updated: 2019/08/13 05:16:45 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

char	*get_path(t_editor *edit, SDL_Texture *txtr)
{
	int	x;

	x = 0;
	while (x < MAXTXTRNUMBER && edit->txtrgame[x])
	{
		if (edit->txtrgame[x] == txtr)
			return (edit->txtrname[x]);
		x++;
	}
	return (NULL);
}

void	load_used_textures(t_editor *edit)
{
	t_lstsec	currsec;
	t_lstmur	currwall;

	currsec = edit->sectors;
	while (currsec)
	{
		currsec->idtop = push_texture(edit, currsec->top);
		currsec->idsol = push_texture(edit, currsec->sol);
		currwall = currsec->murs;
		while (currwall)
		{
			currwall->idtxtr = push_texture(edit, currwall->txtr);
			currwall = currwall->next;
		}
		currsec = currsec->next;
	}
}

int		push_texture(t_editor *edit, SDL_Texture *txtr)
{
	int	x;

	x = 0;
	while (x < MAXTXTRNUMBER && edit->txtrreal[x])
	{
		if (edit->txtrreal[x] == txtr)
		{
			return (x);
		}
		x++;
	}
	if (x < MAXTXTRNUMBER && !(edit->txtrreal[x]))
	{
		edit->txtrreal[x] = txtr;
		return (x);
	}
	return (-1);
}
