/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 04:07:06 by akrache           #+#    #+#             */
/*   Updated: 2019/06/06 05:51:56 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "doom_nukem.h"

void	music_free(t_sound *sound)
{
	Mix_FreeMusic(sound->music);
	sound->music = NULL;
}

int		music_init(t_sound *sound)
{
	if (!(sound->music = Mix_LoadMUS("/Users/akrache/Desktop/music/new_dawn.wav")))//change path
	{
		ft_printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		return (0);
	}
	sound->on = 1;
	return (1);
}