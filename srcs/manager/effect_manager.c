/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effect_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 01:18:06 by akrache           #+#    #+#             */
/*   Updated: 2019/08/26 16:44:18 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void				effect_free(t_sound *sound)
{
	int i;

	i = 0;
	while (i < 14 && sound->tab_effect[i])
	{
		Mix_FreeChunk(sound->tab_effect[i]);
		sound->tab_effect[i] = NULL;
		i++;
	}
}

void				effect_volume(t_sound *sound)
{
	int tmp;

	tmp = abs(sound->effectvolume - 255);
	Mix_SetDistance(0, tmp);
	Mix_SetDistance(1, tmp);
	Mix_SetDistance(2, tmp);
	Mix_SetDistance(3, tmp);
}

static Mix_Chunk	*ldef(char *track)
{
	Mix_Chunk *res;

	if (!(res = Mix_LoadWAV(track)))
		return (0);
	return (res);
}

int					effect_init(t_sound *sound)
{
	if (!(sound->tab_effect[0] = ldef("ressources/effect/walk.wav"))
		|| !(sound->tab_effect[1] = ldef("ressources/effect/run.wav"))
		|| !(sound->tab_effect[2] = ldef("ressources/effect/crouch.wav"))
		|| !(sound->tab_effect[3] = ldef("ressources/effect/door_open.wav"))
		|| !(sound->tab_effect[4] = ldef("ressources/effect/door_close.wav"))
		|| !(sound->tab_effect[5] = ldef("ressources/effect/door_blocked.wav"))
		|| !(sound->tab_effect[6] = ldef("ressources/effect/punch.wav"))
		|| !(sound->tab_effect[7] = ldef("ressources/effect/shot.wav"))
		|| !(sound->tab_effect[8] = ldef("ressources/effect/shotgun.wav"))
		|| !(sound->tab_effect[9] = ldef("ressources/effect/reload.wav"))
		|| !(sound->tab_effect[10] = ldef("ressources/effect/teleporter.wav"))
		|| !(sound->tab_effect[11] = ldef("ressources/effect/win.wav"))
		|| !(sound->tab_effect[12] = ldef("ressources/effect/gameover_0.wav"))
		|| !(sound->tab_effect[13] = ldef("ressources/effect/gameover_1.wav")))
		return (0);
	if (Mix_AllocateChannels(4) != 4)
		return (0);
	sound->effectvolume = 0;
	effect_volume(sound);
	return (1);
}
