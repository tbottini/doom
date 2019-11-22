/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 19:17:11 by magrab            #+#    #+#             */
/*   Updated: 2019/07/29 19:17:12 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "render.h"

void	scroll_limits(int *value, int addition, int smin, int smax)
{
	if (!value)
		return ;
	if (*value + addition < smin)
		*value = smin;
	else if (*value + addition > smax)
		*value = smax;
	else
		*value += addition;
}

void	draw_one_wall(t_editor *editor, t_lstmur currwall)
{
	if (currwall == editor->currmur)
		map_draw_line(editor, currwall->pil1->pos, currwall->pil2->pos,
			(SDL_Color){200, 0, 70, 0xFF});
	else if (currwall == editor->hovermur)
		map_draw_line(editor, currwall->pil1->pos, currwall->pil2->pos,
			(SDL_Color){0, 200, 70, 0xFF});
	else if (editor->currstat && editor->currstat->mur == currwall)
		map_draw_line(editor, currwall->pil1->pos, currwall->pil2->pos,
			(SDL_Color){75, 100, 255, 0xFF});
	else if (currwall->portal_ptr)
		map_draw_line(editor, currwall->pil1->pos, currwall->pil2->pos,
			(SDL_Color){230, 230, 100, 0xFF});
	else
		map_draw_line(editor, currwall->pil1->pos, currwall->pil2->pos,
			(SDL_Color){180, 180, 250, 0xFF});
	draw_objs(editor, currwall->wproplist);
}

void	norm_draw_walls(t_editor *editor, t_lstsec currsec)
{
	t_lstmur currwall;

	currwall = currsec->murs;
	while (currwall)
	{
		map_draw_line(editor, currwall->pil1->pos, currwall->pil2->pos,
			(SDL_Color){150, 150, 150, 0xFF});
		draw_objs(editor, currwall->wproplist);
		currwall = currwall->next;
	}
}
