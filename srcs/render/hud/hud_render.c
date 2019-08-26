/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 16:24:04 by magrab            #+#    #+#             */
/*   Updated: 2019/08/26 16:16:30 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "input.h"

void				hud_aim(t_doom *d)
{
	int x;
	int y;
	int	size;
	int len;

	if (d->game.player.hand->id <= GUN)
		size = 2;
	else if (d->game.player.hand->id == SHOTGUN)
		size = 25;
	else
		size = 10;
	len = 10;
	x = d->sdl.size.x / 2;
	y = d->sdl.size.y / 2;
	while (len)
	{
		d->sdl.screen[(x + size + len) + (y) * d->sdl.size.x] = 0x00FF00FF;
		d->sdl.screen[(x) + (y - size - len) * d->sdl.size.x] = 0x00FF00FF;
		d->sdl.screen[(x) + (y + size + len) * d->sdl.size.x] = 0x00FF00FF;
		d->sdl.screen[(x - size - len) + (y) * d->sdl.size.x] = 0x00FF00FF;
		len--;
	}
}

static void			weapon_hollow(t_doom *d, SDL_Rect pos)
{
	int x;

	pos.h = 42;
	pos.w = 140;
	x = 1;
	while (x < NB_WEAPON)
	{
		if (d->game.player.weapons[(x + d->game.player.hand->id)
			% NB_WEAPON].on)
		{
			pos.y -= pos.h + 10;
			SDL_RenderCopy(d->sdl.rend,
			d->ui.weaponhud[d->game.player.weapons[(x
				+ d->game.player.hand->id) % NB_WEAPON].id], NULL, &pos);
		}
		x++;
	}
}

void				weaponhud_render(t_doom *d)
{
	SDL_Rect	pos;

	pos = (SDL_Rect){d->sdl.size.x - 215, d->sdl.size.y - 75, 200, 60};
	if (d->game.player.hand->id != FIST)
	{
		sdl_int_put((t_ip){d->sdl.rend, d->ui.fonts.s32, (t_vct2){pos.x - 70,
			pos.y - 10}, "", d->game.player.hand->clip, (SDL_Color){0xDD,
			0xDD, 0xDD, 0xFF}});
		sdl_int_put((t_ip){d->sdl.rend, d->ui.fonts.s32, (t_vct2){pos.x - 80,
			pos.y + 25}, "/ ", d->game.player.hand->ammo, (SDL_Color){0xDD,
			0xDD, 0xDD, 0xFF}});
	}
	SDL_RenderCopy(d->sdl.rend, d->ui.weaponhud[d->game.player.hand->id],
		NULL, &pos);
	pos.x += 60;
	weapon_hollow(d, pos);
}

int					hud_render(t_doom *d)
{
	weapon_render(d);
	weaponhud_render(d);
	return (0);
}
