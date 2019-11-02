/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:30:42 by magrab            #+#    #+#             */
/*   Updated: 2019/07/16 14:30:43 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	if_pos_zero(t_editor *edit, int cas, t_lstsec sec)
{
	if (!sec)
		edit->map = push_secteur(&(edit->sectors), edit->txtrgame[0],
			edit->txtrgame[0]);
	else if (cas)
	{
		edit->map = NULL;
		if (sec->prvs)
			sec->prvs->next = sec->next;
		if (sec->next)
			sec->next->prvs = sec->prvs;
		if (sec == edit->sectors)
		{
			if (edit->sectors->next)
			{
				edit->sectors = sec->next;
				edit->sectors->prvs = NULL;
			}
			else
				edit->sectors = NULL;
		}
		ft_clear_secteur(&sec);
	}
	else
		edit->map = sec;
}

/*
** cas == 0 : selectionne le nouveau secteur
** cas == 1 : supprime le secteur selectionne
** cas == 2 : renvoie le secteur selectionne
*/

t_secteur	*sector_menu_click(t_editor *edit, int pos, int cas)
{
	t_lstsec	sec;

	pos = (pos - edit->sectscroll) / SBH;
	edit->currpilier = NULL;
	sec = edit->sectors;
	while (pos > 0 && sec)
	{
		sec = sec->next;
		pos--;
	}
	if (pos == 0)
	{
		if (cas == 2)
			return (sec);
		if_pos_zero(edit, cas, sec);
	}
	else if (pos == 1 && cas != 2)
		edit->map = push_secteur(&(edit->sectors), edit->txtrgame[0],
			edit->txtrgame[0]);
	else if (cas != 2)
		edit->map = NULL;
	return (NULL);
}
