/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:28 by magrab            #+#    #+#             */
/*   Updated: 2019/07/16 17:45:57 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void push_char(char *str, char c)
{
	int x;

	x = 0;
	while (x < MAXFILENAMELEN - 1 && str[x])
		x++;
	if (c == '\0' && x > 0 && str[x] == '\0')
		str[x - 1] = c;
	else
		str[x] = c;
}

int write_hook(t_doom *doom, char *str, SDL_KeyboardEvent e)
{
	if (ft_isalnum(e.keysym.sym))
	{
		if (e.keysym.mod & (KMOD_LSHIFT | KMOD_RSHIFT))
			push_char(str, e.keysym.sym - 32);
		else
			push_char(str, e.keysym.sym);
		ft_printf("%d\t%d\t%s\n", e.keysym.mod, (KMOD_LSHIFT | KMOD_RSHIFT), str);
	}
	else if (e.keysym.sym == SDLK_BACKSPACE)
	{
		push_char(str, '\0');
		ft_printf("%s\n", str);
	}
	else if (e.keysym.sym == SDLK_RETURN)
	{
		if (save_editor_to_file(&doom->edit))
		{
			return (-1);
		}
		close_editor(doom);
		ft_bzero(str, sizeof(char) * MAXFILENAMELEN);
	}
	return (0);
}

int	sdl_draw_filename(t_doom *doom, const char *text)
{
	t_sloc box;
	SDL_Texture *texture;
	SDL_Surface *surf;

	box.snapx = 1;
	box.snapy = 1;
	box.pos.x = 50;
	box.pos.y = 20;
	surf = TTF_RenderText_Shaded(doom->ui.fonts.s32, text, (SDL_Color){250, 250, 250, 255}, (SDL_Color){0, 0, 0, 255});
	SDL_GetClipRect(surf, &box.area);
	texture = SDL_CreateTextureFromSurface(doom->edit.rend, surf);
	update_loc(doom->edit.size, &box, box.area);
	SDL_RenderCopy(doom->edit.rend, texture, NULL, &box.area);
	SDL_SetRenderDrawColor(doom->edit.rend, 200, 200, 200, 250);
	SDL_RenderDrawRect(doom->edit.rend, &box.area);
	SDL_SetRenderDrawColor(doom->edit.rend, 0, 0, 0, 0);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surf);
	return (0);
}


void draw_writer(t_doom *doom)
{
	sdl_draw_filename(doom, doom->edit.filename);
}
