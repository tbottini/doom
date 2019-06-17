/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 04:07:06 by akrache           #+#    #+#             */
/*   Updated: 2019/06/16 14:49:42 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "doom_nukem.h"

void				music_free(t_sound *sound)
{
	int i;

	i = 0;
	while (i < 11 && sound->tab_music[i])
	{
		Mix_FreeMusic(sound->tab_music[i]);
		sound->tab_music[i] = NULL;
		i++;
	}
	sound->music = NULL;
}

static Mix_Music	*loadmus(char *track)
{
	Mix_Music *res;

	if (!(res = Mix_LoadMUS(track)))
	{
		ft_printf( "SDL_mixer Error: %s\n", Mix_GetError());
		return (0);
	}
	return (res);
}

int					music_init(t_sound *sound)
{
	if (!(sound->tab_music[0] = loadmus("ressources/music/new_dawn.ogg"))
		|| !(sound->tab_music[1] = loadmus("ressources/music/pilot.ogg"))
		|| !(sound->tab_music[2] = loadmus("ressources/music/graviton.ogg"))
		|| !(sound->tab_music[3] = loadmus("ressources/music/impact.ogg"))
		|| !(sound->tab_music[4] = loadmus("ressources/music/normandy.ogg"))
		|| !(sound->tab_music[5] = loadmus("ressources/music/venice.wav"))
		|| !(sound->tab_music[6] = loadmus("ressources/music/patriots.ogg"))
		|| !(sound->tab_music[7] = loadmus("ressources/music/normandy_atk.ogg"))
		|| !(sound->tab_music[8] = loadmus("ressources/music/guile.ogg"))
		|| !(sound->tab_music[9] = loadmus("ressources/music/gerudo.ogg"))
		|| !(sound->tab_music[10] = loadmus("ressources/music/snake.ogg")))
		return (0);
	if (!effect_init(sound))
		return (0);
	sound->music = sound->tab_music[0];
	sound->maxmusic = 8;
	sound->musicvolume = 0;
	Mix_VolumeMusic(sound->musicvolume);
	return (sound->on = 1);
}
