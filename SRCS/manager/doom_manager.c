/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 08:02:36 by akrache           #+#    #+#             */
/*   Updated: 2019/08/26 20:54:48 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		secure_doom(t_doom *doom)
{
	int fd;

	if ((fd = open(TTFWOLF, O_RDONLY | O_NOFOLLOW | O_NONBLOCK)) < 0)
		return (-1);
	close(fd);
	if ((fd = open(TTFIMPACT, O_RDONLY | O_NOFOLLOW | O_NONBLOCK)) < 0)
		return (-1);
	close(fd);
	ft_bzero(doom, sizeof(t_doom));
	return (0);
}

void	doom_exit(t_doom *doom)
{
	ui_free(&doom->ui);
	editor_free(doom);
	sdl_free(&doom->sdl);
	borne_free(&doom->game.arch.portal);
	free_game(&doom->game);
	music_free(&doom->game.sound);
	effect_free(&doom->game.sound);
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	free(doom);
	exit(0);
}

t_doom	*doom_init(void)
{
	t_doom	*doom;

	if (!(doom = (t_doom *)malloc(sizeof(t_doom))))
		exit(0);
	if (secure_doom(doom))
		doom_exit(doom);
	doom->game.player.fov = 90;
	if (!sdl_init(&doom->sdl, "Doom-Nukem"))
		doom_exit(doom);
	if (!ui_init(&doom->ui))
		doom_exit(doom);
	if (!ui_by_sdl(doom, &doom->ui))
		doom_exit(doom);
	camera_init(&doom->game.camera, &doom->sdl, 90);
	if (!arch_init(&doom->game.arch, &doom->sdl, &doom->game.camera))
		doom_exit(doom);
	if (!(doom->edit.ui = &doom->ui) || !editor_init(&doom->edit))
		doom_exit(doom);
	if (!music_init(&doom->game.sound))
		doom_exit(doom);
	doom->game.ui = &doom->ui;
	doom->game.difficulty = MEDIUM;
	doom->timestamp = SDL_GetTicks();
	SDL_RaiseWindow(doom->sdl.win);
	return (doom);
}
