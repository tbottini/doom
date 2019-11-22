/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 21:07:11 by akrache           #+#    #+#             */
/*   Updated: 2019/07/01 21:19:31 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		fire_on_off(Uint32 *screen, t_vct2 size, int status)
{
	int i;
	int x;

	i = -1;
	x = size.x * (size.y - 1);
	if (status)
	{
		while (++i < size.x)
			screen[x + i] = 37;
	}
	else
	{
		while (++i < size.x)
			screen[x + i] = 0;
	}
}

void		fire_init(t_doom *doom)
{
	doom->ui.fire = (t_pal){{0, 0x07070701, 0x1F070702, 0x2F0F0703, 0x470F0704,
		0x57170705, 0x671F0706, 0x771F0707, 0x8F270708, 0x9F2F0709, 0xAF3F070A,
		0xBF47070B, 0xC747070C, 0xDF4F070D, 0xDF57070E, 0xDF57070F, 0xD75F0710,
		0xD75F0711, 0xD7670F12, 0xCF6F0F13, 0xCF770F14, 0xCF7F0F15, 0xCF871716,
		0xCC8A1817, 0xD18E1918, 0xDB8E2119, 0xD9A8091A, 0xE2B00B1B, 0xF8C2281C,
		0xF8C2291D, 0xF1D62F1E, 0xF1D62F1F, 0xF1E62F20, 0xDDB73721, 0xCFBF6F22,
		0xDFDF9F23, 0xEFEFC724, 0xF5F5DB25}, (doom->sdl.size.y / 80),
		doom->sdl.screen, &doom->sdl.size};
	fire_on_off(doom->sdl.screen, doom->sdl.size, 1);
}

void		fire(t_pal *f)
{
	int				i;
	int				p;
	unsigned char	pix;

	i = f->size->x * 2;
	while (i < f->size->x * f->size->y)
	{
		pix = f->screen[i] & 0xFF;
		if (pix == 0)
		{
			f->screen[i - f->size->x] = f->pal[1];
		}
		else
		{
			p = (rand()) >> 28;
			f->screen[i - (p & 3) + 1 - f->size->x] = f->pal[pix - (!p)];
		}
		++i;
	}
}
