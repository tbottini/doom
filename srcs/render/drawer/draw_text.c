/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 17:28:11 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/22 17:53:48 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int				sdl_string_put(t_sp sp)
{
	SDL_Texture	*texture;
	SDL_Surface	*surf;
	SDL_Rect	pos;

	surf = TTF_RenderText_Solid(sp.font, sp.text, sp.fg);
	SDL_GetClipRect(surf, &pos);
	pos.x = sp.loc.x;
	pos.y = sp.loc.y;
	texture = SDL_CreateTextureFromSurface(sp.rend, surf);
	SDL_RenderCopy(sp.rend, texture, NULL, &pos);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surf);
	return (0);
}

static int		ft_strlcpy_schlagg(char *dst, const char *src)
{
	int y;

	y = 0;
	while (y < 12 && src[y])
	{
		dst[y] = src[y];
		++y;
	}
	return (y);
}

int				sdl_int_put(t_ip norm)
{
	char res[25];

	ft_itoacpy(res + ft_strlcpy_schlagg(res, norm.label), norm.value);
	sdl_string_put((t_sp){norm.rend, norm.font, norm.loc, res, norm.fg});
	return (0);
}
