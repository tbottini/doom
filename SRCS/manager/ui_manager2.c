/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_manager2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 08:26:10 by akrache           #+#    #+#             */
/*   Updated: 2019/08/26 20:50:04 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		ui_texture_free(t_ui *ui)
{
	int		i;

	i = 0;
	while (i <= 20)
	{
		SDL_FreeSurface(ui->propssurf[i]);
		i++;
	}
	i = 0;
	while (i < 18)
	{
		SDL_DestroyTexture(ui->props[i]);
		i++;
	}
	i = 0;
	while (i < ENDSPRITES)
	{
		SDL_DestroyTexture(ui->sprites[i]);
		i++;
	}
}

void		ui_surface_free(t_ui *ui)
{
	int		i;

	i = 0;
	while (i < ENEMYTXTRTOTAL)
	{
		SDL_FreeSurface(ui->enemy[i]);
		i++;
	}
}

void		ui_free(t_ui *ui)
{
	int	i;

	i = -1;
	if (i > 1)
		free(ui->btnmap[i].data);
	if (ui->fonts.s64)
		TTF_CloseFont(ui->fonts.s64);
	if (ui->fonts.s32)
		TTF_CloseFont(ui->fonts.s32);
	if (ui->fonts.s128)
		TTF_CloseFont(ui->fonts.s128);
	ui_texture_free(ui);
	ui_surface_free(ui);
	i = 0;
	while (i <= 100)
	{
		free(ui->btnmap[i].data);
		i++;
	}
}

int			load_weapons(t_doom *doom, t_ui *ui)
{
	int		x;
	char	path[50];

	ft_strcpy(path, SPRITEPATH);
	x = KICKSTART;
	while (x < ENDSPRITES)
	{
		concat_atoi(&path[19], x);
		if (!(ui->sprites[x] = IMG_LoadTexture(doom->sdl.rend, path)))
			return (0);
		x++;
	}
	return (1);
}

int			link_txtr(t_doom *doom, t_ui *ui)
{
	int			x;
	SDL_Surface	*tmp;

	x = -1;
	while (++x < 18)
	{
		if (!(ui->props[x] =
		SDL_CreateTextureFromSurface(doom->sdl.rend, ui->propssurf[x])))
			return (0);
		tmp = ui->propssurf[x];
		ui->propssurf[x] =
		SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGBA8888, 0);
		SDL_FreeSurface(tmp);
	}
	return (1);
}
