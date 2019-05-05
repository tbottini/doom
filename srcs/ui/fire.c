/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 12:13:10 by akrache           #+#    #+#             */
/*   Updated: 2019/05/05 21:08:37 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	fill_palette(t_wolf *tab)
{
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
}

void		fire_on_off(t_wolf *tab, int on)
{
	int i;

	i = -1;
	if (on)
	{
		while (++i < WIDTH)
			tab->fire.pixel[(HEIGHT - 1) * WIDTH + i] = 37;
	}
	else
	{
		while (++i < WIDTH)
			tab->fire.pixel[(HEIGHT - 1) * WIDTH + i] = 0;
	}
}

void		fire_init(t_wolf *tab)
{
	int i;

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
	fill_palette(tab);
	ft_memset(tab->fire.pixel, 1, HEIGHT * WIDTH * 4);
	fire_on_off(tab, 1);
}

void		spread(t_wolf *tab, int x)
{
	int			deg;
	int			p;
	int			pix;

	pix = tab->fire.pixel[x];
	if (pix == 0)
	{
		tab->fire.pixel[x - WIDTH] = 1;
	}
	else if (pix)
	{
		p = lrint(random()) % (FIRE_HEIGHT);
		deg = x - (p & 3) + 1;
		tab->fire.pixel[deg - WIDTH] = pix - (p ? 0 : 1);
	}
}

void		fire(t_wolf *tab)
{
	int		i;
	int		j;
	int		ind;

	i = 0;
	while (i < WIDTH)
	{
		j = HEIGHT - 1;
		while (j > 1)
		{
			ind = j * WIDTH + i;
			spread(tab, ind);
			tab->img_adr[ind] = tab->fire.pal[tab->fire.pixel[ind]];
			j--;
		}
		i++;
	}
	mlx_put_image_to_window(tab->mlx_ptr, tab->win_ptr, tab->img_ptr, 0, 0);
}
