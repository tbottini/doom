/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 11:12:19 by magrab            #+#    #+#             */
/*   Updated: 2019/08/16 11:12:22 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		pos_in_rect(SDL_Rect rect, int x, int y)
{
	if (rect.x <= x && x <= rect.x + rect.w
		&& rect.y <= y && y <= rect.y + rect.h)
	{
		return (1);
	}
	return (0);
}

void	updatetext(t_updatetext t)
{
	SDL_Surface		*tmp;

	SDL_DestroyTexture(*t.text);
	tmp = TTF_RenderText_Shaded(t.font, t.str, t.fg, t.bg);
	SDL_GetClipRect(tmp, t.loc);
	*t.text = SDL_CreateTextureFromSurface(t.rend, tmp);
	SDL_FreeSurface(tmp);
}
