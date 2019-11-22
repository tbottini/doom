/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_render_draw.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 03:03:30 by magrab            #+#    #+#             */
/*   Updated: 2019/08/13 03:03:30 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "render.h"

void	map_draw_line(t_editor *editor, t_vct2 pos0, t_vct2 pos1,
	SDL_Color c)
{
	pos0 = get_screen_mappos(editor, pos0.x, pos0.y);
	pos1 = get_screen_mappos(editor, pos1.x, pos1.y);
	SDL_SetRenderDrawColor(editor->rend, c.r, c.g, c.b, c.a);
	SDL_RenderDrawLine(editor->rend, pos0.x, pos0.y, pos1.x, pos1.y);
}

void	draw_grid(t_editor *editor, t_vct2 center, int dist, int master)
{
	t_vct2 curr;

	(void)master;
	if (dist >= 400)
		draw_grid(editor, center, dist / 10, dist);
	if (dist >= 400)
		SDL_SetRenderDrawColor(editor->rend, 110, 110, 110, 255);
	else
		SDL_SetRenderDrawColor(editor->rend, 70, 70, 70, 255);
	curr.x = center.x % dist - dist;
	curr.y = center.y % dist - dist;
	while (curr.x < editor->size.x)
	{
		SDL_RenderDrawLine(editor->rend, curr.x, 0, curr.x, editor->size.y);
		curr.x += dist;
	}
	while (curr.y < editor->size.y)
	{
		SDL_RenderDrawLine(editor->rend, 0, curr.y, editor->size.x, curr.y);
		curr.y += dist;
	}
}

void	draw_player(t_editor *editor)
{
	t_vct2		loc;
	SDL_Rect	tmp;

	if (editor->currstat == &(editor->player.stat))
		SDL_SetRenderDrawColor(editor->rend, 100, 255, 100, 255);
	else if (editor->player.stat.sector == editor->map)
		SDL_SetRenderDrawColor(editor->rend, 100, 205, 100, 255);
	else
		SDL_SetRenderDrawColor(editor->rend, 100, 150, 100, 255);
	loc = get_screen_mappos(editor, editor->player.stat.pos.x,
		editor->player.stat.pos.y);
	tmp.x = loc.x - 10;
	tmp.y = loc.y - 10;
	tmp.w = 20;
	tmp.h = 20;
	SDL_RenderDrawRect(editor->rend, &tmp);
	tmp.x = cos((editor->player.stat.roty - 90.0) * PI180) * 50.0;
	tmp.y = -sin((editor->player.stat.roty - 90.0) * PI180) * 50.0;
	SDL_RenderDrawLine(editor->rend, loc.x, loc.y,
		loc.x + tmp.x, loc.y + tmp.y);
	SDL_SetRenderDrawColor(editor->rend, 0, 0, 0, 255);
}

void	draw_props(t_editor *editor, t_entity *curr,
	SDL_Texture **sprites, int proppos)
{
	SDL_Rect	tmp;
	t_vct2		loc;
	int			type;

	if (editor->currstat == &(curr->stat))
		SDL_SetRenderDrawColor(editor->rend, 75, 100, 255, 255);
	else if (curr->stat.sector == editor->map)
		SDL_SetRenderDrawColor(editor->rend, 50, 75, 150, 255);
	else
		SDL_SetRenderDrawColor(editor->rend, 50, 75, 100, 255);
	loc = get_screen_mappos(editor, curr->stat.pos.x, curr->stat.pos.y);
	tmp = (SDL_Rect){loc.x - 10, loc.y - 10, 20, 20};
	type = curr->stat.type - proppos;
	SDL_RenderCopy(editor->rend, sprites[type], NULL, &tmp);
	tmp = (SDL_Rect){tmp.x - 1, tmp.y - 1, tmp.w + 2, tmp.h + 2};
	SDL_RenderDrawRect(editor->rend, &tmp);
	tmp = (SDL_Rect){tmp.x - 1, tmp.y - 1, tmp.w + 2, tmp.h + 2};
	SDL_RenderDrawRect(editor->rend, &tmp);
	tmp = (SDL_Rect){tmp.x - 1, tmp.y - 1, tmp.w + 2, tmp.h + 2};
	SDL_RenderDrawRect(editor->rend, &tmp);
}

void	draw_enemies(t_editor *editor, t_entity *curr)
{
	SDL_Rect	tmp;
	t_vct2		loc;

	if (editor->currstat == &(curr->stat))
		SDL_SetRenderDrawColor(editor->rend, 220, 105, 255, 255);
	else if (curr->stat.sector == editor->map)
		SDL_SetRenderDrawColor(editor->rend, 170, 100, 205, 255);
	else
		SDL_SetRenderDrawColor(editor->rend, 120, 100, 155, 255);
	loc = get_screen_mappos(editor, curr->stat.pos.x, curr->stat.pos.y);
	if (curr->stat.type <= 2)
		tmp = (SDL_Rect){loc.x - 5, loc.y - 5, 10, 10};
	else
		tmp = (SDL_Rect){loc.x - curr->stat.type * 2 - 2,
			loc.y - curr->stat.type * 2 - 2, curr->stat.type * 4 + 4,
			curr->stat.type * 4 + 4};
	if (curr->stat.type % 2)
		SDL_RenderDrawRect(editor->rend, &tmp);
	else
		SDL_RenderFillRect(editor->rend, &tmp);
	tmp.x = cos(curr->stat.roty * PI180) * curr->stat.type * 8;
	tmp.y = -sin(curr->stat.roty * PI180) * curr->stat.type * 8;
	SDL_RenderDrawLine(editor->rend,
		loc.x, loc.y, loc.x + tmp.x, loc.y + tmp.y);
}
