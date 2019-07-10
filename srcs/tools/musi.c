/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   musi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 03:47:35 by akrache           #+#    #+#             */
/*   Updated: 2019/07/10 14:17:53 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "doom_nukem.h"

/*
** returns the color c as if it passes throught a transparent screen of color s.
** double f determines the opacity of the "screen".
** f must be between 0 and 1, returning the color s, 0 the color c.
*/

int					opacity(int s, int c, double f)
{
	if (f == 1)
		return (s);
	else if (!f)
		return (c);
	return (((int)((c >> 8 & 255) + f * ((s >> 8 & 255) - (c >> 8 & 255))) << 8)
	+ ((int)((c >> 16 & 255) + f * ((s >> 16 & 255) - (c >> 16 & 255))) << 16)
	+ ((int)((c >> 24 & 255) + f * ((s >> 24 & 255) - (c >> 24 & 255))) << 24)
	+ 255);
}

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
	char tmp[10];

	ft_strcpy(tmp, " Track 1 ");
	doom->game.sound.on += 1;
	if (!(doom->game.sound.on % doom->game.sound.maxmusic))
		doom->game.sound.on = 1;
	change_music(&doom->game.sound, doom->game.sound.on, 5000);
	tmp[7] = doom->game.sound.on + '0';
	updateText(doom->sdl.rend, doom->ui.fonts.s64, &doom->ui.btnpse[2].txture, &doom->ui.btnpse[2].loc.area, tmp, doom->ui.btnpse[2].fgcolor, doom->ui.btnpse[2].bgcolor);
}

void		prev_track(t_doom *doom)
{
	char tmp[10];

	ft_strcpy(tmp, " Track 1 ");
	doom->game.sound.on -= 1;
	if (!(doom->game.sound.on))
		doom->game.sound.on = doom->game.sound.maxmusic - 1;
	change_music(&doom->game.sound, doom->game.sound.on, 5000);
	tmp[7] = doom->game.sound.on + '0';
	updateText(doom->sdl.rend, doom->ui.fonts.s64, &doom->ui.btnpse[2].txture, &doom->ui.btnpse[2].loc.area, tmp, doom->ui.btnpse[2].fgcolor, doom->ui.btnpse[2].bgcolor);
}
