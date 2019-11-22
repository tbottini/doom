/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 08:15:30 by akrache           #+#    #+#             */
/*   Updated: 2019/08/26 20:47:34 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static int	load_props(t_doom *doom, t_ui *ui)
{
	if (!(ui->propssurf[0] = IMG_Load(PROPHEALTH))
		|| !(ui->propssurf[1] = IMG_Load(PROPCASS))
		|| !(ui->propssurf[2] = IMG_Load(PROPMUN))
		|| !(ui->propssurf[3] = IMG_Load(PROPRPILL))
		|| !(ui->propssurf[4] = IMG_Load(PROPGPILL))
		|| !(ui->propssurf[5] = IMG_Load(PROPBPILL))
		|| !(ui->propssurf[6] = IMG_Load(PROPJETPACK))
		|| !(ui->propssurf[7] = IMG_Load(PROPGUN))
		|| !(ui->propssurf[8] = IMG_Load(PROPSHOTGUN))
		|| !(ui->propssurf[9] = IMG_Load(PROPRIFLE))
		|| !(ui->propssurf[10] = IMG_Load(PROPKEY1))
		|| !(ui->propssurf[11] = IMG_Load(PROPKEY2))
		|| !(ui->propssurf[12] = IMG_Load(PROPKEY3))
		|| !(ui->propssurf[13] = IMG_Load(PROPCORE))
		|| !(ui->propssurf[14] = IMG_Load(PROPBTN))
		|| !(ui->propssurf[15] = IMG_Load(PROPWINBTN))
		|| !(ui->propssurf[16] = IMG_Load(PROPIMPACT))
		|| !(ui->propssurf[17] = IMG_Load(PROPARROW))
		|| !(ui->propssurf[18] = IMG_Load(PROPCROSS))
		|| !(ui->propssurf[19] = IMG_Load(PROPEXIT))
		|| !(ui->propssurf[20] = IMG_Load(PROPBTNOPEN)))
		return (0);
	return (link_txtr(doom, ui));
}

static int	load_enemies(t_doom *doom, t_ui *ui)
{
	int			x;
	char		path[50];
	SDL_Surface	*tmp;

	(void)doom;
	ft_strcpy(path, ENEMYPATH);
	x = 0;
	while (x < ENEMYTXTRTOTAL)
	{
		concat_atoi(&path[35], x);
		if (!(tmp = IMG_Load(path)))
			return (0);
		ui->enemy[x] =
		SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGBA8888, 0);
		SDL_FreeSurface(tmp);
		x++;
	}
	return (1);
}

static int	ui_by_sdl2(t_doom *doom, t_ui *ui)
{
	ui->btnpse[0] = add_pause_button(doom);
	ui->btnpse[1] = add_resume_button(doom);
	ui->btnpse[2] = add_middle_music_button(doom);
	ui->btnpse[3] = add_left_music_button(doom, &(ui->btnpse[2].loc.area));
	ui->btnpse[4] = add_right_music_button(doom, &(ui->btnpse[2].loc.area));
	ui->btnpse[5] = add_ing_opt_button(doom);
	ui->btnpse[6] = add_main_menu_button(doom);
	if (!(ui->weaponhud[FIST] = add_fist(doom))
		|| !(ui->weaponhud[GUN] = add_handgun(doom))
		|| !(ui->weaponhud[SHOTGUN] = add_shotgun(doom))
		|| !(ui->weaponhud[RIFLE] = add_rifle(doom)))
		return (0);
	if (!(load_weapons(doom, ui)))
		return (0);
	if (!(load_props(doom, ui)))
		return (0);
	if (!(load_enemies(doom, ui)))
		return (0);
	return (1);
}

int			ui_by_sdl(t_doom *doom, t_ui *ui)
{
	doom->game.sound.musicvolume = 100;
	ui->btnarr[0] = add_doom_button(doom, " Doom-Nukem ");
	ui->btnarr[1] = add_start_button(doom);
	ui->btnarr[2] = add_opt_button(doom);
	ui->btnarr[3] = add_editor_button(doom);
	ui->btnarr[4] = add_quit_button(doom, " Quit ", &doom_exit);
	ui->btnmap[0] = add_quit_button(doom, " Return ", &return_button);
	ui->btnmap[1] = add_mapmenu_button(doom);
	ui->btnopt[0] = ui->btnmap[0];
	ui->btnopt[1] = add_doom_button(doom, " Options ");
	ui->btnopt[2] = add_middle_diff_button(doom, &(ui->btnopt[1].loc.area));
	ui->btnopt[3] = add_left_diff_button(doom, &(ui->btnopt[2].loc.area));
	ui->btnopt[4] = add_right_diff_button(doom, &(ui->btnopt[2].loc.area));
	ui->slidopt[0] = add_fov_slider(doom);
	ui->slidopt[0].loc.parent = &(ui->btnopt[1].loc.area);
	ui->slidopt[1] = add_music_slider(doom);
	ui->slidopt[1].loc.parent = &(ui->slidopt[0].loc.area);
	ui->slidopt[2] = add_effect_slider(doom);
	ui->slidopt[2].loc.parent = &(ui->slidopt[1].loc.area);
	return (ui_by_sdl2(doom, ui));
}

int			ui_init(t_ui *ui)
{
	ui->m_status = MENU_MAIN;
	if (!(ui->fonts.s64 = TTF_OpenFont(TTFWOLF, 64)))
		return (0);
	if (!(ui->fonts.s128 = TTF_OpenFont(TTFWOLF, 128)))
		return (0);
	if (!(ui->fonts.s32 = TTF_OpenFont(TTFIMPACT, 32)))
		return (0);
	return (1);
}
