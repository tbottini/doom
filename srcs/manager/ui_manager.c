#include "doom_nukem.h"

void	ui_free(t_ui *ui)
{
	int i;

	i = -1;
	if (i > 1)
		free(ui->btnmap[i].data);

	if (ui->fonts.s64)
		TTF_CloseFont(ui->fonts.s64);
	if (ui->fonts.s32)
		TTF_CloseFont(ui->fonts.s32);
	if (ui->fonts.s128)
		TTF_CloseFont(ui->fonts.s128);

	//free weaponhud sprites, props, propssurf enemy
	i = 0;
	while (i <= 20)
	{
		SDL_FreeSurface(ui->propssurf[i]);
		i++;
	}
	i = 0;
	while (i < 18)
	{
		SDL_DestroyTexture(ui->props[i]);
		i++;
	}
	i = 0;
	while (i < ENDSPRITES)
	{
		SDL_DestroyTexture(ui->sprites[i]);
		i++;
	}
	i = 0;
	while (i < ENEMYTXTRTOTAL)
	{
		SDL_FreeSurface(ui->enemy[i]);
		i++;
	}
	i = 0;
	while (i <= 100)
	{
		free(ui->btnmap[i].data);
		i++;
	}
}

int		load_weapons(t_doom *doom, t_ui *ui)
{
	int x;
	char path[50];

	ft_strcpy(path, SPRITEPATH);
	x = KICKSTART;
	while (x < ENDSPRITES)
	{
		concat_atoi(&path[19], x);
		if (!(ui->sprites[x] = IMG_LoadTexture(doom->sdl.rend, path)))
			return (0);
		x++;
	}
	return (1);
}

int		link_txtr(t_doom *doom, t_ui *ui)
{
	int x;
	SDL_Surface *tmp;

	x = -1;
	while (++x < 18)
	{
		if (!(ui->props[x] = SDL_CreateTextureFromSurface(doom->sdl.rend, ui->propssurf[x])))
			return (0);
		tmp = ui->propssurf[x];
		ui->propssurf[x] = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGBA8888, 0);
		SDL_FreeSurface(tmp);
	}
	return (1);
}

int		load_props(t_doom *doom, t_ui *ui)
{
	if    (!(ui->propssurf[0] = IMG_Load(PROPHEALTH))
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


int		load_enemies(t_doom *doom, t_ui *ui)
{
	int x;
	char path[50];
	SDL_Surface *tmp;

	ft_strcpy(path, ENEMYPATH);
	x = 0;
	while (x < ENEMYTXTRTOTAL)
	{
		concat_atoi(&path[35], x);
		if (!(tmp = IMG_Load(path)))
			return (0);
		ui->enemy[x] = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGBA8888, 0);
		SDL_FreeSurface(tmp);
		x++;
	}
	return (1);
}

int		ui_by_sdl(t_doom *doom, t_ui *ui)
{
	ui->btnarr[0] = add_doom_button(doom, " Doom-Nukem ");
	ui->btnarr[1] = add_start_button(doom);
	ui->btnarr[2] = add_opt_button(doom);
	ui->btnarr[3] = add_editor_button(doom);
	ui->btnarr[4] = add_quit_button(doom, " Quit ", &doom_exit);
	ui->btnmap[0] = add_quit_button(doom, " Return ", &return_button);
	ui->btnmap[1] = add_mapmenu_button(doom);
	ui->btnopt[0] = ui->btnmap[0];
	ui->btnopt[1] = add_doom_button(doom, " Options ");
	ui->btnopt[2] = add_middle_difficulty_button(doom, &(ui->btnopt[1].loc.area));
	ui->btnopt[3] = add_left_difficulty_button(doom, &(ui->btnopt[2].loc.area));
	ui->btnopt[4] = add_right_difficulty_button(doom, &(ui->btnopt[2].loc.area));
	ui->slidopt[0] = add_fov_slider(doom);
	ui->slidopt[0].loc.parent = &(ui->btnopt[1].loc.area);
	ui->slidopt[1] = add_music_slider(doom);
	ui->slidopt[1].loc.parent = &(ui->slidopt[0].loc.area);
	ui->slidopt[2] = add_effect_slider(doom);
	ui->slidopt[2].loc.parent = &(ui->slidopt[1].loc.area);
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

int		ui_init(t_ui *ui)
{
	ui->m_status = MENU_MAIN;
	ui->curr_btn_controller = -2;
	if (!(ui->fonts.s64 = TTF_OpenFont(TTFWOLF, 64)))
		return (0);
	if (!(ui->fonts.s128 = TTF_OpenFont(TTFWOLF, 128)))
		return (0);
	if (!(ui->fonts.s32 = TTF_OpenFont(TTFIMPACT, 32)))
		return (0);
	return (1);
}
