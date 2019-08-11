/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effect_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 01:18:06 by akrache           #+#    #+#             */
/*   Updated: 2019/08/09 15:53:31 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "doom_nukem.h"

void				effect_free(t_sound *sound)
{
	int i;

	i = 0;
	while (i < 9 && sound->tab_effect[i])
	{
		Mix_FreeChunk(sound->tab_effect[i]);
		sound->tab_effect[i] = NULL;
		i++;
	}
	//leaks possible ?
}

void				effect_volume(t_sound *sound)
{
	/*Mix_SetPanning(0, sound->effectvolume, sound->effectvolume);
	Mix_SetPanning(1, sound->effectvolume, sound->effectvolume);
	Mix_SetPanning(2, sound->effectvolume, sound->effectvolume);
	Mix_SetPanning(3, sound->effectvolume, sound->effectvolume);*/
	int tmp;

	tmp = abs(sound->effectvolume - 255);
	Mix_SetDistance(0, tmp);
	Mix_SetDistance(1, tmp);
	Mix_SetDistance(2, tmp);
	Mix_SetDistance(3, tmp);
}

static Mix_Chunk	*loadef(char *track)
{
	Mix_Chunk *res;

	if (!(res = Mix_LoadWAV(track)))
	{
		ft_printf( "SDL_mixer Error: %s\n", Mix_GetError());
		return (0);
	}
	return (res);
}

int					effect_init(t_sound *sound)
{
	if (!(sound->tab_effect[0] = loadef("ressources/effect/walk.wav"))
		|| !(sound->tab_effect[1] = loadef("ressources/effect/run.wav"))
		|| !(sound->tab_effect[2] = loadef("ressources/effect/crouch.wav"))
		|| !(sound->tab_effect[3] = loadef("ressources/effect/door_open.wav"))
		|| !(sound->tab_effect[4] = loadef("ressources/effect/door_close.wav"))
		|| !(sound->tab_effect[5] = loadef("ressources/effect/door_blocked.wav"))
		|| !(sound->tab_effect[6] = loadef("ressources/effect/punch.wav"))
		|| !(sound->tab_effect[7] = loadef("ressources/effect/shot.wav"))
		|| !(sound->tab_effect[8] = loadef("ressources/effect/shotgun.wav"))
		|| !(sound->tab_effect[9] = loadef("ressources/effect/reload.wav"))
		|| !(sound->tab_effect[10] = loadef("ressources/effect/teleporter.wav"))
		|| !(sound->tab_effect[11] = loadef("ressources/effect/win.wav"))
		|| !(sound->tab_effect[12] = loadef("ressources/effect/gameover_0.wav"))
		|| !(sound->tab_effect[13] = loadef("ressources/effect/gameover_1.wav")))
		return (0);
	if (Mix_AllocateChannels(4) != 4)
		return (0);
	sound->effectvolume = 0;
	effect_volume(sound);
	return (1);
}
