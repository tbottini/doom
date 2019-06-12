/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   musi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 03:47:35 by akrache           #+#    #+#             */
/*   Updated: 2019/06/12 15:07:30 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "doom_nukem.h"



void		change_music(t_sound *sound, int n, int fade)
{
	if (n >= 0 && n < 11)
	{
		sound->music = sound->tab_music[n];
		Mix_FadeInMusic(sound->music, -1, fade);
	}
	else if (n == -1 && Mix_PlayingMusic())
		Mix_FadeOutMusic(fade);
}

void		play_effect(t_sound *sound, int e)//debug fonction
{
	Mix_PlayChannel(-1, sound->tab_effect[e], 0);
}

void		next_track(t_doom *doom)
{
	static char *lol[] = {" Track 0 ", " Track 1 ", " Track 2 ", " Track 3 ",
		" Track 4 ", " Track 5 ", " Track 6 ",
		" Track 7 ", " Track 8 ", " Track 9 "};

	doom->sound.on += 1;
	if (!(doom->sound.on % doom->sound.maxmusic))
		doom->sound.on = 1;
	change_music(&doom->sound, doom->sound.on, 5000);
	updateText(doom->sdl.rend, doom->ui.fonts.s64, &doom->ui.btnpse[2].txture, &doom->ui.btnpse[2].loc.area, lol[doom->sound.on], doom->ui.btnpse[2].fgcolor, doom->ui.btnpse[2].bgcolor);
}

void		prev_track(t_doom *doom)
{
	static char *lol[] = {" Track 0 ", " Track 1 ", " Track 2 ", " Track 3 ",
		" Track 4 ", " Track 5 ", " Track 6 ",
		" Track 7 ", " Track 8 ", " Track 9 "};

	doom->sound.on -= 1;
	if (!(doom->sound.on))
		doom->sound.on = doom->sound.maxmusic - 1;
	change_music(&doom->sound, doom->sound.on, 5000);
	updateText(doom->sdl.rend, doom->ui.fonts.s64, &doom->ui.btnpse[2].txture, &doom->ui.btnpse[2].loc.area, lol[doom->sound.on], doom->ui.btnpse[2].fgcolor, doom->ui.btnpse[2].bgcolor);
}