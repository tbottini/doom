/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 16:24:04 by magrab            #+#    #+#             */
/*   Updated: 2019/08/04 12:05:42 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "input.h"

int					hud_render(t_doom *doom)
{
	SDL_Rect pos;
	int x;

	pos.h = 60;
	pos.w = 200;
	pos.x = doom->sdl.size.x - pos.w - 15;
	pos.y = doom->sdl.size.y - pos.h - 15;
	if (doom->game.player.hand->id != FIST)
	{
		sdl_int_put(doom->sdl.rend, doom->ui.fonts.s32, (t_vct2){pos.x - 70, pos.y - 10}, "", doom->game.player.hand->clip, (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
		sdl_int_put(doom->sdl.rend, doom->ui.fonts.s32, (t_vct2){pos.x - 80, pos.y + 25}, "/ ", doom->game.player.hand->ammo, (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
	}
	SDL_RenderCopy(doom->sdl.rend, doom->ui.weaponhud[doom->game.player.hand->id], NULL, &pos);
	pos.x += 60;
	pos.h = 42;
	pos.w = 140;
	x = 1;
	while (x < NB_WEAPON)
	{
		if (doom->game.player.weapons[(x + doom->game.player.hand->id) % NB_WEAPON].on)
		{
			pos.y -= pos.h + 10;
			SDL_RenderCopy(doom->sdl.rend,
			doom->ui.weaponhud[doom->game.player.weapons[(x + doom->game.player.hand->id) % NB_WEAPON].id],
			NULL, &pos);
		}
		x++;
	}
	return (0);
}
