/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:28 by magrab            #+#    #+#             */
/*   Updated: 2019/05/26 17:10:10 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		close_editor(t_doom *doom)
{
	fire_on_off(doom->sdl.screen, doom->sdl.size, 1);
	if (doom->edit.win)
	{
		doom->edit.status = 0;
		SDL_HideWindow(doom->edit.win);
		return (0);
	}
	return (-1);
}

void	start_editor(t_doom *doom)
{
	//fire_on_off(doom->sdl.screen, doom->sdl.size, 0);
	SDL_ShowWindow(doom->edit.win);
	doom->edit.status = 1;
}

void	editor_free(t_editor *editor)
{
	if (editor->map)
		ft_clear_pillar_list(&editor->map);
	if (editor->rend)
		SDL_DestroyRenderer(editor->rend);
	if (editor->win)
		SDL_DestroyWindow(editor->win);
}

int		editor_init(t_editor *editor)
{
	if (!(editor->win = SDL_CreateWindow("Editor", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE)))
		return (0);
	if (!(editor->rend = SDL_CreateRenderer(editor->win, -1, 1)))
		return (0);
	SDL_SetWindowMinimumSize(editor->win, MINWIDTH, MINHEIGHT);
	SDL_GetWindowSize(editor->win, &(editor->size.x), &(editor->size.y));
	return (1);
}
