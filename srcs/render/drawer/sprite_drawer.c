/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_drawer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:29:54 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 22:17:05 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "calcul.h"

int						needle_get_cursor(t_arch *arch, t_needle *needle
	, t_sprite *sprite)
{
	int				start_index;

	if (sprite->heigth.x < (int)arch->portal.b_up[needle->txtr_col])
	{
		start_index = (int)arch->portal.b_up[needle->txtr_col];
		needle->buff = (arch->portal.b_up[needle->txtr_col] - sprite->heigth.x)
			* needle->coef;
	}
	else
	{
		start_index = sprite->heigth.x;
		needle->buff = 0;
	}
	needle->numcol = needle->txtr_col + (start_index * arch->sdl->size.x);
	return (needle->numcol);
}

/*
**	...
*/

extern	inline uint32_t	horror_pixel(t_arch *arch, t_needle *nd
	, double buffer_w)
{
	if (nd->numcol >= 0 && nd->numcol < arch->sdl->size.x * arch->sdl->size.y
	&& (int)buffer_w + (int)nd->buff * nd->txtr->w < nd->txtr->h * nd->txtr->w)
	{
		return (opacity(arch->sdl->screen[nd->numcol],
			nd->txtr->pixels[(int)buffer_w + (int)nd->buff * nd->txtr->w],
				1 - (unsigned char)(nd->txtr->pixels[(int)buffer_w
					+ (int)nd->buff * nd->txtr->w]) / 255.0));
	}
	return (0);
}

void					secur_start(t_arch *arch, t_sprite *sprite
	, double *buff_w, double p_buff_w)
{
	if (sprite->width.x < 0)
	{
		*buff_w = -sprite->width.x * p_buff_w;
		sprite->width.x = 0;
	}
	else
		*buff_w = 0;
	if (sprite->width.y > arch->sdl->size.x)
		sprite->width.y = arch->sdl->size.x;
}

extern inline void		sprite_draw_column(t_arch *arch, t_needle *nd
	, double buff_w, t_sprite *sprite)
{
	if (sprite->heigth.y > (int)arch->portal.b_down[nd->txtr_col])
		nd->surface.y = arch->portal.b_down[nd->txtr_col] * arch->sdl->size.x;
	else
		nd->surface.y = sprite->heigth.y * arch->sdl->size.x;
	while (nd->numcol < (int)nd->surface.y
	&& nd->numcol < arch->sdl->size.x * arch->sdl->size.y
	&& nd->numcol > 0 && nd->buff < nd->txtr->h)
	{
		arch->sdl->screen[nd->numcol] = horror_pixel(arch, nd, buff_w);
		needle_indent_down(nd, arch);
	}
}

void					sprite_draw(t_sprite *spri, t_arch *arch)
{
	double			p_buff_w;
	double			buff_w;
	double			neutral_distance;
	t_needle		nd;

	if (!(spri->texture.pixels))
		return ;
	nd.txtr = &spri->texture;
	nd.coef = (double)nd.txtr->h / (double)(spri->heigth.y - spri->heigth.x);
	p_buff_w = spri->texture.w / (double)(spri->width.y - spri->width.x);
	neutral_distance = (double)(arch->sdl->size.y) / spri->pos.x;
	secur_start(arch, spri, &buff_w, p_buff_w);
	nd.txtr_col = spri->width.x;
	while ((int)nd.txtr_col < spri->width.y && buff_w < spri->texture.w)
	{
		if (zline_compare(arch, neutral_distance, nd.txtr_col))
		{
			needle_get_cursor(arch, &nd, spri);
			sprite_draw_column(arch, &nd, buff_w, spri);
		}
		nd.txtr_col++;
		buff_w += p_buff_w;
	}
}
