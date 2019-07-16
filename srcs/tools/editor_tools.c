/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 15:04:20 by magrab            #+#    #+#             */
/*   Updated: 2019/07/16 15:04:22 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_vct2 get_rel_mappos(t_editor *editor, int x, int y)
{
	t_vct2 pos;

	pos.x = (x - editor->mappos.x) * EDITORPRECISION / editor->mappos.z;
	pos.y = (y - editor->mappos.y) * EDITORPRECISION / editor->mappos.z;
	return (pos);
}

t_vct2 get_screen_mappos(t_editor *editor, int x, int y)
{
	t_vct2 pos;

	pos.x = x * editor->mappos.z / EDITORPRECISION + editor->mappos.x;
	pos.y = y * editor->mappos.z / EDITORPRECISION + editor->mappos.y;
	return (pos);
}

t_vct2 line_percent(t_vct2 pos1, t_vct2 pos2, double percent)
{
	t_vct2 middle;

	middle.x = pos1.x - (pos1.x - pos2.x) * percent;
	middle.y = pos1.y - (pos1.y - pos2.y) * percent;
	return (middle);
}
