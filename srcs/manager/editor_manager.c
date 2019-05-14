/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:28 by magrab            #+#    #+#             */
/*   Updated: 2019/05/06 17:46:28 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		close_editor(t_doom *doom)
{
	fire_on_off(doom->sdl.screen, doom->sdl.size, 1);
	SDL_HideWindow(doom->edit.win);
	doom->edit.status = 0;
	return (0);
}

void	open_editor(t_doom *doom)
{
	fire_on_off(doom->sdl.screen, doom->sdl.size, 0);
	SDL_ShowWindow(doom->edit.win);
	SDL_RaiseWindow(doom->edit.win);
	doom->edit.status = 1;
}

void	editor_free(t_editor *editor)
{
	SDL_ShowWindow(editor->win);
	if (editor->map)
		free(editor->map); // Must Change
	if (editor->txture)
		SDL_DestroyTexture(editor->txture);
	if (editor->rend)
		SDL_DestroyRenderer(editor->rend);
	if (editor->win)
		SDL_DestroyWindow(editor->win);
}

int		editor_init(t_editor *editor)
{
	void	*tmp;
	int		pitch;

	if (!(editor->win = SDL_CreateWindow("Editor", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_HIDDEN)))
		return (0);
	if (!(editor->rend = SDL_CreateRenderer(editor->win, -1, 1)))
		return (0);
	editor->txture = SDL_CreateTexture(editor->rend,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	if (SDL_LockTexture(editor->txture, NULL, &tmp, &pitch))
		return (0);
	editor->screen = (Uint32*)tmp;
	SDL_GetWindowSize(editor->win, &(editor->size.x), &(editor->size.y));
	editor->mappos = (t_vct2){editor->size.x / 2, editor->size.y / 2};
	editor->mapzoom = 1;
	if (!(editor->map = ft_newpillar((t_vct2){0, 0})))
		return (0);
	return (1);
}
