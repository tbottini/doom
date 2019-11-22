/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   needle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 03:37:11 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/23 03:44:34 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void			needle_buff_affect(t_needle *needle)
{
	if (needle->buff > 1.0)
	{
		needle->txtr_col += (int)needle->buff * needle->txtr->w;
		needle->buff = needle->buff - (int)needle->buff;
	}
}

t_needle		needle_prepare(int numcol, t_txtr *txtr, uint32_t txtr_col
	, t_vct2 surface)
{
	t_needle	needle;

	needle.numcol = numcol;
	needle.txtr = txtr;
	needle.surface = surface;
	needle.txtr_col = txtr_col;
	needle.buff = 0;
	needle.coef = (double)needle.txtr->h
		/ (needle.surface.y - needle.surface.x);
	return (needle);
}

void			needle_reajust2(t_needle *needle, int limit)
{
	needle->buff = (-needle->surface.x + limit) * needle->coef;
	needle_buff_affect(needle);
	needle->surface.x = limit;
}

void			needle_reajust(t_arch *arch, t_needle *needle, int limit)
{
	needle->numcol = arch->px.x + limit * arch->sdl->size.x;
	needle->buff = (limit - needle->surface.x) * needle->coef;
	needle_buff_affect(needle);
	needle->surface.x = limit;
}

void			needle_indent_down(t_needle *needle, t_arch *arch)
{
	needle->surface.x++;
	needle->numcol += arch->sdl->size.x;
	needle->buff += needle->coef;
}
