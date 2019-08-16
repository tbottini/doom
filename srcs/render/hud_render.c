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

void				weaponhud_render(t_doom *doom)
{
	SDL_Rect pos;
	int x;

	pos.h = 60;
	pos.w = 200;
	pos.x = doom->sdl.size.x - pos.w - 15;
	pos.y = doom->sdl.size.y - pos.h - 15;
	if (doom->game.player.hand->id != FIST)
	{
		sdl_int_put((t_ip){doom->sdl.rend, doom->ui.fonts.s32, (t_vct2){pos.x - 70, pos.y - 10}, "", doom->game.player.hand->clip, (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF}});
		sdl_int_put((t_ip){doom->sdl.rend, doom->ui.fonts.s32, (t_vct2){pos.x - 80, pos.y + 25}, "/ ", doom->game.player.hand->ammo, (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF}});
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
}

void				action_render(t_doom *doom, int start, int len)
{
	int currimg;
	SDL_Rect rect;

	rect = (SDL_Rect){0, doom->sdl.size.y / 2, doom->sdl.size.x, doom->sdl.size.y / 2};
	currimg = ((double)doom->timestamp - (double)doom->game.player.occupied) / ((double)doom->game.player.occupied - (double)doom->game.player.timeact) * (double)len + len;
	if (currimg < len)
		SDL_RenderCopy(doom->sdl.rend, doom->ui.sprites[start + currimg], NULL, &rect);
}

void				weapon_render(t_doom *doom)
{
	SDL_Rect rect;

	rect = (SDL_Rect){0, doom->sdl.size.y / 2, doom->sdl.size.x, doom->sdl.size.y / 2};
	if (doom->timestamp > doom->game.player.occupied)
	{
		if (doom->game.player.hand->id == GUN)
			SDL_RenderCopy(doom->sdl.rend, doom->ui.sprites[GUNSTART], NULL, &rect);
		else if (doom->game.player.hand->id == SHOTGUN)
			SDL_RenderCopy(doom->sdl.rend, doom->ui.sprites[SHOTGUNSTART], NULL, &rect);
		else if (doom->game.player.hand->id == RIFLE)
			SDL_RenderCopy(doom->sdl.rend, doom->ui.sprites[RIFLESTART], NULL, &rect);
	}
	else if (doom->game.player.act)
	{
		if (doom->game.player.hand->id == GUN)
			action_render(doom, GUNRELOADSTART, GUNRELOADLEN);
		else if (doom->game.player.hand->id == SHOTGUN)
			action_render(doom, SHOTGUNRELOADSTART, SHOTGUNRELOADLEN);
		else if (doom->game.player.hand->id == RIFLE)
			action_render(doom, RIFLERELOADSTART, RIFLERELOADLEN);
	}
	else if (doom->game.player.act == false)
	{
		if (doom->game.player.hand->id == FIST)
			action_render(doom, KICKSTART, KICKLEN);
		else if (doom->game.player.hand->id == GUN)
			action_render(doom, GUNSHOOTSTART, GUNSHOOTLEN);
		else if (doom->game.player.hand->id == SHOTGUN)
			action_render(doom, SHOTGUNSHOOTSTART, SHOTGUNSHOOTLEN);
		else if (doom->game.player.hand->id == RIFLE)
			action_render(doom, RIFLESHOOTSTART, RIFLESHOOTLEN);
	}
}

int					hud_render(t_doom *doom)
{
	weapon_render(doom);
	weaponhud_render(doom);
	//hud_aim(doom);
	return (0);
}
