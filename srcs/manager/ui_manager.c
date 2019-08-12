#include "doom_nukem.h"

void	ui_free(t_ui *ui)
{
	int i;

	i = -1;
	//while (ui->btnarr[++i].txture)
	//	SDL_DestroyTexture(ui->btnarr[i].txture);
	i = -1;
	//while (ui->btnmap[++i].txture)
	//{
	//	SDL_DestroyTexture(ui->btnmap[i].txture);
		if (i > 1)
			free(ui->btnmap[i].data);
	//}
	if (ui->fonts.s64)
		TTF_CloseFont(ui->fonts.s64);
	if (ui->fonts.s32)
		TTF_CloseFont(ui->fonts.s32);
	if (ui->fonts.s128)
		TTF_CloseFont(ui->fonts.s128);
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

int		load_props(t_doom *doom, t_ui *ui)
{
	if    (!(ui->props[0] = IMG_LoadTexture(doom->sdl.rend, PROPHEALTH))
		|| !(ui->props[1] = IMG_LoadTexture(doom->sdl.rend, PROPCASS))
		|| !(ui->props[2] = IMG_LoadTexture(doom->sdl.rend, PROPMUN))
		|| !(ui->props[3] = IMG_LoadTexture(doom->sdl.rend, PROPRPILL))
		|| !(ui->props[4] = IMG_LoadTexture(doom->sdl.rend, PROPGPILL))
		|| !(ui->props[5] = IMG_LoadTexture(doom->sdl.rend, PROPBPILL))
		|| !(ui->props[6] = IMG_LoadTexture(doom->sdl.rend, PROPJETPACK))
		|| !(ui->props[7] = IMG_LoadTexture(doom->sdl.rend, PROPGUN))
		|| !(ui->props[8] = IMG_LoadTexture(doom->sdl.rend, PROPSHOTGUN))
		|| !(ui->props[9] = IMG_LoadTexture(doom->sdl.rend, PROPRIFLE))
		|| !(ui->props[10] = IMG_LoadTexture(doom->sdl.rend, PROPKEY1))
		|| !(ui->props[11] = IMG_LoadTexture(doom->sdl.rend, PROPKEY2))
		|| !(ui->props[12] = IMG_LoadTexture(doom->sdl.rend, PROPKEY3))
		|| !(ui->props[13] = IMG_LoadTexture(doom->sdl.rend, PROPCORE))
		|| !(ui->props[14] = IMG_LoadTexture(doom->sdl.rend, PROPBTN))
		|| !(ui->props[15] = IMG_LoadTexture(doom->sdl.rend, PROPWINBTN))
		|| !(ui->props[16] = IMG_LoadTexture(doom->sdl.rend, PROPIMPACT)))
		return (0);
	return (1);
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
