/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 15:44:55 by akrache           #+#    #+#             */
/*   Updated: 2019/08/26 16:14:28 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void			reload_anim(t_doom *d, SDL_Rect rect)
{
	if (d->game.player.hand->id == GUN)
		SDL_RenderCopy(d->sdl.rend, d->ui.sprites[GUNSTART], NULL, &rect);
	else if (d->game.player.hand->id == SHOTGUN)
		SDL_RenderCopy(d->sdl.rend, d->ui.sprites[SHOTGUNSTART], NULL, &rect);
	else if (d->game.player.hand->id == RIFLE)
		SDL_RenderCopy(d->sdl.rend, d->ui.sprites[RIFLESTART], NULL, &rect);
}

void				action_render(t_doom *d, int start, int len)
{
	int			img;
	SDL_Rect	rect;

	rect = (SDL_Rect){0, d->sdl.size.y / 2, d->sdl.size.x, d->sdl.size.y / 2};
	img = ((double)d->timestamp - (double)d->game.player.occupied)
		/ ((double)d->game.player.occupied - (double)d->game.player.timeact)
		* (double)len + len;
	if (img < len)
		SDL_RenderCopy(d->sdl.rend, d->ui.sprites[start + img], NULL, &rect);
}

void				weapon_render(t_doom *d)
{
	SDL_Rect rect;

	rect = (SDL_Rect){0, d->sdl.size.y / 2, d->sdl.size.x, d->sdl.size.y / 2};
	if (d->timestamp > d->game.player.occupied)
		reload_anim(d, rect);
	else if (d->game.player.act)
	{
		if (d->game.player.hand->id == GUN)
			action_render(d, GUNRELOADSTART, GUNRELOADLEN);
		else if (d->game.player.hand->id == SHOTGUN)
			action_render(d, SHOTGUNRELOADSTART, SHOTGUNRELOADLEN);
		else if (d->game.player.hand->id == RIFLE)
			action_render(d, RIFLERELOADSTART, RIFLERELOADLEN);
	}
	else if (d->game.player.act == false)
	{
		if (d->game.player.hand->id == FIST)
			action_render(d, KICKSTART, KICKLEN);
		else if (d->game.player.hand->id == GUN)
			action_render(d, GUNSHOOTSTART, GUNSHOOTLEN);
		else if (d->game.player.hand->id == SHOTGUN)
			action_render(d, SHOTGUNSHOOTSTART, SHOTGUNSHOOTLEN);
		else if (d->game.player.hand->id == RIFLE)
			action_render(d, RIFLESHOOTSTART, RIFLESHOOTLEN);
	}
}
