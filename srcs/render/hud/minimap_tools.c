/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 05:27:48 by akrache           #+#    #+#             */
/*   Updated: 2019/08/13 05:28:43 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "color.h"

int				bold_point2(t_minimap *mini, t_vct2 pos, Uint32 color)
{
	int tmp;

	tmp = pos.y * mini->sdl->size.x;
	if (pos.y > mini->d.y && pos.y < mini->a.y - 1
		&& pos.x < mini->a.x - 1 && pos.x > mini->d.x)
	{
		mini->sdl->screen[pos.x + tmp] = color;
		mini->sdl->screen[pos.x + 1 + tmp] = color;
		mini->sdl->screen[pos.x - 1 + tmp] = color;
		mini->sdl->screen[pos.x + 1 + tmp + mini->sdl->size.x] = color;
		mini->sdl->screen[pos.x - 1 + tmp + mini->sdl->size.x] = color;
		mini->sdl->screen[pos.x + 1 + tmp - mini->sdl->size.x] = color;
		mini->sdl->screen[pos.x - 1 + tmp - mini->sdl->size.x] = color;
		mini->sdl->screen[pos.x + tmp + mini->sdl->size.x] = color;
		mini->sdl->screen[pos.x + tmp - mini->sdl->size.x] = color;
	}
	return (1);
}

void			minibord(t_minimap *mini)
{
	int i;
	int j;

	i = mini->d.x - 1;
	j = mini->a.y - 1;
	while (++i < mini->a.x - 1)
	{
		mini->sdl->screen[i + mini->d.y * mini->sdl->size.x] = WHITE;
		mini->sdl->screen[i + j * mini->sdl->size.x] = WHITE;
	}
	j = mini->sdl->size.y - (mini->sdl->size.y >> 2) - 1;
	while (++j < mini->a.y)
	{
		mini->sdl->screen[mini->d.x + j * mini->sdl->size.x] = WHITE;
		mini->sdl->screen[i + j * mini->sdl->size.x] = WHITE;
	}
}
