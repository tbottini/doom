/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   musi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 03:47:35 by akrache           #+#    #+#             */
/*   Updated: 2019/06/10 03:34:40 by akrache          ###   ########.fr       */
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
	ft_printf("effect = %d\n", e);
	Mix_PlayChannel(-1, sound->tab_effect[e], 0);
}