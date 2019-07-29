/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 16:24:04 by magrab            #+#    #+#             */
/*   Updated: 2019/07/29 13:52:45 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void				hud_aim(t_doom *doom)
{
	int x;
	int y;
	int	size;
	int len;

	if (doom->game.player.hand->id <= GUN)
		size = 2;
	else if (doom->game.player.hand->id == SHOTGUN)
		size = 25;
	else
		size = 10;
	len = 10;
	x = doom->sdl.size.x / 2;
	y = doom->sdl.size.y / 2;
	while (len)
	{
		doom->sdl.screen[(x + size + len) + (y) *  doom->sdl.size.x] = 0x00FF00FF;
		doom->sdl.screen[(x) + (y - size - len) *  doom->sdl.size.x] = 0x00FF00FF;
		doom->sdl.screen[(x) + (y + size + len) *  doom->sdl.size.x] = 0x00FF00FF;
		doom->sdl.screen[(x - size - len) + (y) *  doom->sdl.size.x] = 0x00FF00FF;
		len--;
	}
}

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
	//hud_aim(doom);
	return (0);
}
