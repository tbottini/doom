/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 19:44:27 by magrab            #+#    #+#             */
/*   Updated: 2019/07/28 19:44:28 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

SDL_Texture		*add_fist(t_doom *doom)
{
	t_html tmp;

	tmp.txtr = IMG_LoadTexture(doom->sdl.rend, HANDHOLLOWPATH);
	return (tmp.txtr);
}

SDL_Texture		*add_handgun(t_doom *doom)
{
	t_html tmp;

	tmp.txtr = IMG_LoadTexture(doom->sdl.rend, GUNHOLLOWPATH);
	return (tmp.txtr);
}

SDL_Texture		*add_shotgun(t_doom *doom)
{
	t_html tmp;

	tmp.txtr = IMG_LoadTexture(doom->sdl.rend, SHOTGUNHOLLOWPATH);
	return (tmp.txtr);
}

SDL_Texture		*add_rifle(t_doom *doom)
{
	t_html tmp;

	tmp.txtr = IMG_LoadTexture(doom->sdl.rend, RIFLEHOLLOWPATH);
	return (tmp.txtr);
}
