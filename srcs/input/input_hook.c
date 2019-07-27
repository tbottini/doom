/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:18:09 by magrab            #+#    #+#             */
/*   Updated: 2019/07/27 15:06:59 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			save_png(t_sdl *sdl)
{
	SDL_Surface	*s_shot;

	s_shot = SDL_CreateRGBSurfaceWithFormatFrom(sdl->screen, sdl->size.x,
		sdl->size.y, 8, sizeof(uint32_t) * sdl->size.x, SDL_PIXELFORMAT_RGBA8888);
	IMG_SavePNG(s_shot, "out.png");
	ft_printf("png save\n");
	SDL_FreeSurface(s_shot);
}

void			clean_screen(t_sdl *sdl)
{
	int			i;
	i = 0;

	while (i < sdl->size.x * sdl->size.y)
	{
		sdl->screen[i] = 0;
		i++;
	}
}

void			debug_code(int key)
{
	debug = key - SDLK_KP_1 + 1;
	printf("debug keycode %d\n", debug);
}


int		game_key_press(int key, t_doom *doom)
{
	if (doom->ui.curr_btn_controller > 0)
		doom->ui.curr_btn_controller = -doom->ui.curr_btn_controller;
	else if (key == SDLK_RETURN || key == SDLK_BACKQUOTE)
		sdl_set_status(doom, MENU_IGMAIN);
	else if (key == SDLK_LGUI && doom->game.player.stat.jetpack)
		crouch(&doom->game.player);
	else if (key == SDLK_z)
		jetpack_on_off(&doom->game.player);
	else if (key == SDLK_b)
		save_png(&doom->sdl);
	else if (key == SDLK_9)//
		change_music(&doom->game.sound, 10, 5000);
	else if (key == SDLK_k)//
		game_over(doom, true);
	else if (doom->timestamp > doom->game.player.occupied)
	{
		if (key == SDLK_e)
			action(doom, &doom->game.player.stat);
		else if (key == SDLK_r)
			reload(doom->timestamp, &doom->game.player, &doom->game.player.hand);
		else if (key == SDLK_v)
			kick(doom->timestamp, &doom->game.sound, &doom->game.player);
		else if (key == SDLK_1 || key == SDLK_2 || key == SDLK_3 || key == SDLK_4)
			change_weapon(&doom->game.player, key - '0' - 1);
		else
			ft_nodeadd_int(&(doom->sdl.keys), key);
	}
	else
		ft_nodeadd_int(&(doom->sdl.keys), key);
	return (0);
}

/*
** Add here function that need to be done when a key is pressed (wont trigger in loop_hook)
** Example :
** else if (key == SDLK_yourkey)
**		action();
*/
int		key_press(int key, t_doom *doom)
{
	if (doom->ui.curr_btn_controller > 0)
		doom->ui.curr_btn_controller = -doom->ui.curr_btn_controller;
	else if ((key == SDLK_RETURN || key == SDLK_BACKQUOTE) && doom->ui.m_status == MENU_IGMAIN)
		sdl_set_status(doom, MENU_INGAME);
	else if (key <= SDLK_KP_9 && key >= SDLK_KP_1)
		debug_code(key);
	else if (key == SDLK_h)
	{
		describe_player(doom->game.player);
		describe_sector_recursif(*doom->game.sectors);
	}
	else if (key == SDLK_KP_MINUS)
		doom->game.arch.zoom /= 2;
	else if (key == SDLK_KP_PLUS)
		doom->game.arch.zoom *= 2;
	else if (key == SDLK_PERIOD)
		doom->ui.fire = (t_pal){{0, 0x10003101, 0x14073702, 0x190f3d03, 0x1e164304,
		0x221e4905, 0x27254f06, 0x2c2c5507, 0x30345b08, 0x353c6109, 0x3a43670A,
		0x3e4b6d0B, 0x4352730C, 0x4859790D, 0x4c617f0E, 0x5169850F, 0x56708b10,
		0x5a789111, 0x5f7f9812, 0x64879e13, 0x688ea414, 0x6d96aa15, 0x729db016,
		0x76a5b617, 0x7bacbc18, 0x80b3c219, 0x84bbc81A, 0x89c3ce1B, 0x8ecad41C,
		0x92d2da1D, 0x97d9e01E, 0x9ce1e61F, 0xa0e8ec20, 0xa5f0f221, 0xaaf7f822,
		0xafffff23, 0xcfffff24, 0xFFFFFF25}, (doom->sdl.size.y / 80), doom->sdl.screen, &doom->sdl.size};
	else if (key == SDLK_COMMA)
		doom->ui.fire = (t_pal){{0, 0x07070701, 0x1F070702, 0x2F0F0703, 0x470F0704,
		0x57170705, 0x671F0706, 0x771F0707, 0x8F270708, 0x9F2F0709, 0xAF3F070A,
		0xBF47070B, 0xC747070C, 0xDF4F070D, 0xDF57070E, 0xDF57070F, 0xD75F0710,
		0xD75F0711, 0xD7670F12, 0xCF6F0F13, 0xCF770F14, 0xCF7F0F15, 0xCF871716,
		0xCC8A1817, 0xD18E1918, 0xDB8E2119, 0xD9A8091A, 0xE2B00B1B, 0xF8C2281C,
		0xF8C2291D, 0xF1D62F1E, 0xF1D62F1F, 0xF1E62F20, 0xDDB73721, 0xCFBF6F22,
		0xDFDF9F23, 0xEFEFC724, 0xF5F5DB25}, (doom->sdl.size.y / 80), doom->sdl.screen, &doom->sdl.size};
	else if (key == SDLK_j)
	{
		doom->game.arch.portal.b_left += 2;
		printf("borne %f %f\n", doom->game.arch.portal.b_left, doom->game.arch.portal.b_right);
		clean_screen(&doom->sdl);
	}
	else if (key == SDLK_k)
	{
		doom->game.arch.portal.b_right += 2;
		printf("borne %f %f\n", doom->game.arch.portal.b_left, doom->game.arch.portal.b_right);
		clean_screen(&doom->sdl);
	}
	else if (key == SDLK_u)
	{
		doom->game.arch.portal.b_left -= 2;
		printf("borne %f %f\n", doom->game.arch.portal.b_left, doom->game.arch.portal.b_right);
		clean_screen(&doom->sdl);
	}
	else if (key == SDLK_i)
	{
		doom->game.arch.portal.b_right -= 2;
		printf("borne %f %f\n", doom->game.arch.portal.b_left, doom->game.arch.portal.b_right);
		clean_screen(&doom->sdl);
	}
	else
		ft_nodeadd_int(&(doom->sdl.keys), key);
	return (0);
}

/*
** Add here function that need to be done when a key is released
** Example :
** else if (key == SDLK_yourkey)
**		action();
*/
int		key_release(int key, t_doom *doom)
{
	ft_noderm_int(&(doom->sdl.keys), key);
	if (key == SDLK_w || key == SDLK_LSHIFT)
		sprint_release(&doom->game.player.stat);
	else if (key == SDLK_LGUI)
		crouch_release(&doom->game.player);
	return (0);
}

/*
** Add here function that need to be done when mouse is pressed
** Example :
** else if (btn == SDL_BUTTON_yourbutton)
**		action();
*/
int		mouse_press(int btn, int x, int y, t_doom *doom)
{
	t_btn *curr_btn;

	SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
	if (btn == SDL_BUTTON_LEFT)
	{
		//doom->ui.curr_btn = NULL;
		curr_btn = btn_hover(doom, x, y);
		if (curr_btn && curr_btn->func)
			(*curr_btn->func)(doom);
		else
		{
			if (doom->ui.m_status != 0)
				btn_click(doom, x, y);
			else if (!(doom->game.player.hand.rate))
				shoot(doom->timestamp, &doom->game.sound, &doom->game.player);
			else
				ft_nodeadd_int(&(doom->sdl.keys), SDL_BUTTON_LEFT);
		}
	}
	//else if (btn == SDL_BUTTON_RIGHT)
		//fire_on_off(doom->sdl.screen, doom->sdl.size, 0); // Debug thing
	return (0);
}

int mouse_wheel(SDL_MouseWheelEvent e, t_doom *doom)
{
	if (doom->ui.m_status == MENU_INGAME)
	{
		if (e.y > 0)
			next_weapon(&doom->game.player);
		else if (e.y < 0)
			prev_weapon(&doom->game.player);
	}
	else if (doom->ui.m_status == MENU_MAP)
	{
		if (doom->ui.btnmap[1].loc.pos.y + e.y > 0)
			doom->ui.btnmap[1].loc.pos.y = 0;
		else
			doom->ui.btnmap[1].loc.pos.y += e.y;
	}
	return (0);
}

/*
** Add here function that need to be done when mouse is released
** Example :
** else if (btn == SDL_BUTTON_yourbutton)
**		action();
*/
int		mouse_release(int btn, int x, int y, t_doom *doom)
{
	doom->ui.currslid = NULL;
	(void)btn;
	(void)x;
	(void)y;
	if (btn == SDL_BUTTON_LEFT && doom->game.player.hand.rate)
		ft_noderm_int(&(doom->sdl.keys), btn);
	return (0);
}

/*
** Add here function that need to be done when mouse if moved in window
** x and y are relative postions when in gamemode
*/
int		mouse_move(int x, int y, t_doom *doom)
{
	t_slid	*tmp;

	doom->sdl.m_pos.x = x;
	doom->sdl.m_pos.y = y;
	doom->ui.curr_btn = btn_hover(doom, x, y);
	if (doom->ui.curr_btn && doom->ui.curr_btn->func)
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
	else
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
	if (doom->ui.m_status == MENU_INGAME)
	{
		doom->game.player.stat.rot.y -= x / SENSIBILITY;
		doom->game.player.stat.rot.x -= y / (SENSIBILITY * 2);
		return (0);
	}
	if (doom->ui.currslid)
	{
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE));
		tmp = doom->ui.currslid;
		update_slider_value(doom, tmp, x);
		if (tmp == &(doom->ui.slidopt[0]))
			doom->game.camera.d_screen = (doom->sdl.size.x / 2.0) / tan(doom->game.player.fov / 2.0 * PI180);
		else if (tmp == &(doom->ui.slidopt[1]))
			Mix_VolumeMusic(doom->game.sound.musicvolume);
		else if (tmp == &(doom->ui.slidopt[2]))
			effect_volume(&doom->game.sound);
	}
	return (0);
}
