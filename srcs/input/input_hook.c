/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:18:09 by magrab            #+#    #+#             */
/*   Updated: 2019/08/26 14:30:54 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		unblock(t_stat *s)
{
	t_fvct2	d;

	d.x = sin(s->rot.y * PI180) / 10.0;
	d.y = cos(s->rot.y * PI180) / 10.0;
	s->pos.x += d.y * 0.5;
	s->pos.y += d.x * 0.5;
}

void		save_png(t_sdl *sdl)
{
	SDL_Surface	*s_shot;

	s_shot = SDL_CreateRGBSurfaceWithFormatFrom(sdl->screen, sdl->size.x,
	sdl->size.y, 8, sizeof(uint32_t) * sdl->size.x, SDL_PIXELFORMAT_RGBA8888);
	ft_printf("png save : %d\n", IMG_SaveJPG(s_shot, "screenshot.jpg", 90));
	SDL_FreeSurface(s_shot);
}

int			game_key_press(int k, t_doom *d)
{
	if (k == SDLK_RETURN || k == SDLK_BACKQUOTE)
		sdl_set_status(d, MENU_IGMAIN);
	else if (k == SDLK_LGUI && d->game.player.inv.jetpack)
		crouch(&d->game.player);
	else if (k == SDLK_z)
		jetpack_on_off(&d->game.player);
	else if (k == SDLK_b)
		save_png(&d->sdl);
	else if (k == SDLK_m)
		unblock(&d->game.player.stat);
	else if (d->timestamp > d->game.player.occupied)
	{
		if (k == SDLK_e)
			action(d, &d->game.player.stat, &d->game.player.inv);
		else if (k == SDLK_r && d->game.player.hand->id != FIST)
			reload(d->timestamp, &d->game.player,
			d->game.player.hand, &d->game.sound);
		else if (k == SDLK_1 || k == SDLK_2 || k == SDLK_3 || k == SDLK_4)
			change_weapon(&d->game.player, k - '0' - 1);
		else
			ft_nodeadd_int(&(d->sdl.keys), k);
	}
	else
		ft_nodeadd_int(&(d->sdl.keys), k);
	return (0);
}

/*
** Add here function that need to be done when a key is pressed
** (wont trigger in loop_hook)
** Example :
** else if (key == SDLK_yourkey)
**		action();
*/

void		key_press(int key, t_doom *doom)
{
	if ((key == SDLK_RETURN || key == SDLK_BACKQUOTE)
		&& doom->ui.m_status == MENU_IGMAIN)
		sdl_set_status(doom, MENU_INGAME);
	else if (key == SDLK_PERIOD)
		doom->ui.fire = (t_pal){{0, 268448001, 336017154, 420429059, 504775428,
		0x221e4905, 0x27254f06, 0x2c2c5507, 0x30345b08, 0x353c6109, 0x3a43670A,
		0x3e4b6d0B, 0x4352730C, 0x4859790D, 0x4c617f0E, 0x5169850F, 0x56708b10,
		0x5a789111, 0x5f7f9812, 0x64879e13, 0x688ea414, 0x6d96aa15, 0x729db016,
		0x76a5b617, 0x7bacbc18, 0x80b3c219, 0x84bbc81A, 0x89c3ce1B, 0x8ecad41C,
		0x92d2da1D, 0x97d9e01E, 0x9ce1e61F, 0xa0e8ec20, 0xa5f0f221, 0xaaf7f822,
		0xafffff23, 0xcfffff24, 0xFFFFFF25},
		(doom->sdl.size.y / 80), doom->sdl.screen, &doom->sdl.size};
	else if (key == SDLK_COMMA)
		doom->ui.fire = (t_pal){{0, 117901057, 520554242, 789513987, 0x470F0704,
		0x57170705, 0x671F0706, 0x771F0707, 0x8F270708, 0x9F2F0709, 0xAF3F070A,
		0xBF47070B, 0xC747070C, 0xDF4F070D, 0xDF57070E, 0xDF57070F, 0xD75F0710,
		0xD75F0711, 0xD7670F12, 0xCF6F0F13, 0xCF770F14, 0xCF7F0F15, 0xCF871716,
		0xCC8A1817, 0xD18E1918, 0xDB8E2119, 0xD9A8091A, 0xE2B00B1B, 0xF8C2281C,
		0xF8C2291D, 0xF1D62F1E, 0xF1D62F1F, 0xF1E62F20, 0xDDB73721, 0xCFBF6F22,
		0xDFDF9F23, 0xEFEFC724, 0xF5F5DB25},
		(doom->sdl.size.y / 80), doom->sdl.screen, &doom->sdl.size};
	else
		ft_nodeadd_int(&(doom->sdl.keys), key);
}

/*
** Add here function that need to be done when a key is released
** Example :
** else if (key == SDLK_yourkey)
**		action();
*/

int			key_release(int key, t_doom *doom)
{
	ft_noderm_int(&(doom->sdl.keys), key);
	if (key == SDLK_w || key == SDLK_LSHIFT)
		sprint_release(&doom->game.player.stat);
	else if (key == SDLK_LGUI)
		crouch_release(&doom->game.player);
	return (0);
}
