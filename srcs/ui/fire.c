/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 12:13:10 by akrache           #+#    #+#             */
/*   Updated: 2019/05/06 19:56:23 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
/*
static void	fill_palette(t_pal *p)
{
	*p = (t_pal){0, 0x070707, 0x1F0707, 0x2F0F07, 0x470F07, 0x571707, 0x671F07,
		0x771F07, 0x8F2707, 0x9F2F07, 0xAF3F07, 0xBF4707, 0xC74707, 0xDF4F07,
		0xDF5707, 0xDF5707, 0xD75F07, 0xD75F07, 0xD7670F, 0xCF6F0F, 0xCF770F,
		0xCF7F0F, 0xCF8717, 0xC78717, 0xC78F17, 0xC7971F, 0xBF9F1F, 0xBF9F1F,
		0xBFA727, 0xBFA727, 0xBFAF2F, 0xB7AF2F, 0xB7B72F, 0xB7B737, 0xCFCF6F,
		0xDFDF9F, 0xEFEFC7, 0xFFFFFF, 1};
	
	tab->fire.pal[37] = 0xFFFFFF;
	tab->fire.pal[36] = 0xEFEFC7;
	tab->fire.pal[35] = 0xDFDF9F;
	tab->fire.pal[34] = 0xCFCF6F;
	tab->fire.pal[33] = 0xB7B737;
	tab->fire.pal[32] = 0xB7B72F;
	tab->fire.pal[31] = 0xB7AF2F;
	tab->fire.pal[30] = 0xBFAF2F;
	tab->fire.pal[29] = 0xBFA727;
	tab->fire.pal[28] = 0xBFA727;
	tab->fire.pal[27] = 0xBF9F1F;
	tab->fire.pal[26] = 0xBF9F1F;
	tab->fire.pal[25] = 0xC7971F;
	tab->fire.pal[24] = 0xC78F17;
	tab->fire.pal[23] = 0xC78717;
	tab->fire.pal[22] = 0xCF8717;
	tab->fire.pal[21] = 0xCF7F0F;
	tab->fire.pal[20] = 0xCF770F;
	tab->fire.pal[19] = 0xCF6F0F;
	tab->fire.pal[18] = 0xD7670F;
	tab->fire.pal[17] = 0xD75F07;
	tab->fire.pal[16] = 0xD75F07;
	tab->fire.pal[15] = 0xDF5707;
	tab->fire.pal[14] = 0xDF5707;
	tab->fire.pal[13] = 0xDF4F07;
	tab->fire.pal[12] = 0xC74707;
	tab->fire.pal[11] = 0xBF4707;
	tab->fire.pal[10] = 0xAF3F07;
	tab->fire.pal[9] = 0x9F2F07;
	tab->fire.pal[8] = 0x8F2707;
	tab->fire.pal[7] = 0x771F07;
	tab->fire.pal[6] = 0x671F07;
	tab->fire.pal[5] = 0x571707;
	tab->fire.pal[4] = 0x470F07;
	tab->fire.pal[3] = 0x2F0F07;
	tab->fire.pal[2] = 0x1F0707;
	tab->fire.pal[1] = 0x070707;
	tab->fire.pal[0] = 0;
}
*/

void fire_on_off(uint32_t *screen, t_vct2 size, int status)
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

void fire_init(t_doom *doom)
{
	/* old palette
	doom->ui.fire = (t_pal){0, 0x07070701, 0x1F070702, 0x2F0F0703, 0x470F0704, 0x57170705,
							0x671F0706, 0x771F0707, 0x8F270708, 0x9F2F0709, 0xAF3F070A, 0xBF47070B, 0xC747070C,
							0xDF4F070D, 0xDF57070E, 0xDF57070F, 0xD75F0710, 0xD75F0711, 0xD7670F12, 0xCF6F0F13,
							0xCF770F14, 0xCF7F0F15, 0xCF871716, 0xC7871717, 0xC78F1718, 0xC7971F19, 0xBF9F1F1A,
							0xBF9F1F1B, 0xBFA7271C, 0xBFA7271D, 0xBFAF2F1E, 0xB7AF2F1F, 0xB7B72F20, 0xB7B73721,
							0xCFCF6F22, 0xDFDF9F23, 0xEFEFC724, 0xFFFFFF25};
	*/
	doom->ui.fire = (t_pal){{0, 0x07070701, 0x1F070702, 0x2F0F0703, 0x470F0704,
		0x57170705, 0x671F0706, 0x771F0707, 0x8F270708, 0x9F2F0709, 0xAF3F070A,
		0xBF47070B, 0xC747070C, 0xDF4F070D, 0xDF57070E, 0xDF57070F, 0xD75F0710,
		0xD75F0711, 0xD7670F12, 0xCF6F0F13, 0xCF770F14, 0xCF7F0F15, 0xCF871716,
		0xCC8A1817, 0xD18E1918, 0xDB8E2119, 0xD9A8091A, 0xE2B00B1B, 0xF8C2281C,
		0xF8C2291D, 0xF1D62F1E, 0xF1D62F1F, 0xF1E62F20, 0xDDB73721, 0xCFBF6F22,
		0xDFDF9F23, 0xEFEFC724, 0xF5F5DB25}, (doom->sdl.size.y / 145)};
	fire_on_off(doom->sdl.screen, doom->sdl.size, 1);
}

/*
static void spread(uint32_t *img, int pal[38], int width, int x)
{
	int p;
	int pix;

	pix = (img[x] & 0xFF) % 38;
	if (pix == 0)
	{
		img[x - width] = pal[1];
	}
	else if (pix)
	{
		p = (rand()) % 5;
		img[x - (p & 3) + 1 - width] = pal[pix - (p ? 0 : 1)];
	}
}
*/

void fire(t_doom *doom)
{
	int i;
	int p;
	int pix;

	i = doom->sdl.size.x * (doom->sdl.size.y / 3);
	while (++i < doom->sdl.size.x * doom->sdl.size.y)
	{
		pix = (doom->sdl.screen[i] & 0xFF) % 38;
		//pix = (doom->sdl.screen[i] % 256) % 38;  2 fois moins opti
		if (pix == 0)
		{
			doom->sdl.screen[i - doom->sdl.size.x] = doom->ui.fire.pal[1];
		}
		else
		{
			p = (rand()) % doom->ui.fire.height;
			doom->sdl.screen[i - (p & 3) + 1 - doom->sdl.size.x] = doom->ui.fire.pal[pix - (p ? 0 : 1)];
		}
		// Je gagne 7 fps si je passe pas a la fonction #Skill #Optimisation #Jai passe beaucoup trop de temps dessus
		// spread(doom->sdl.screen, doom->ui.fire.pal, doom->sdl.size.x, i);
	}
	SDL_RenderCopy(doom->sdl.rend, doom->sdl.txture, NULL, NULL);
}
