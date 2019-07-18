/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:28 by magrab            #+#    #+#             */
/*   Updated: 2019/07/16 18:03:12 by akrache          ###   ########.fr       */
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
		if (e.keysym.mod & (KMOD_LSHIFT | KMOD_RSHIFT | KMOD_CAPS))
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
	else if (e.keysym.sym == SDLK_BACKQUOTE)
	{
		ft_bzero(str, sizeof(char) * MAXFILENAMELEN);
		doom->edit.status = ED_LOADED;
	}
	else if (e.keysym.sym == SDLK_RETURN)
	{
		if (doom->edit.status == ED_SAVING)
		{
			if (save_editor_to_file(&doom->edit))
			{
				return (-1);
			}
			if (e.keysym.mod == 0)
				close_editor(doom);
		}
		else if (doom->edit.status == ED_WRITING)
		{
			*doom->edit.currwriter = ft_atoi(str);
			doom->edit.status = ED_LOADED;
		}
		ft_bzero(str, sizeof(char) * MAXFILENAMELEN);
	}
	return (0);
}

int	sdl_draw_filename(t_editor *edit, const char *text)
{
	t_sloc box;
	SDL_Texture *texture;
	SDL_Surface *surf;

	box.snapx = 1;
	box.snapy = 1;
	box.pos.x = 50;
	box.pos.y = 20;
	surf = TTF_RenderText_Shaded(edit->ui->fonts.s32, text, (SDL_Color){250, 250, 250, 255}, (SDL_Color){0, 0, 0, 255});
	SDL_GetClipRect(surf, &box.area);
	texture = SDL_CreateTextureFromSurface(edit->rend, surf);
	update_loc(edit->size, &box, box.area);
	SDL_RenderCopy(edit->rend, texture, NULL, &box.area);
	SDL_SetRenderDrawColor(edit->rend, 200, 200, 200, 250);
	SDL_RenderDrawRect(edit->rend, &box.area);
	SDL_SetRenderDrawColor(edit->rend, 0, 0, 0, 0);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surf);
	return (0);
}


void draw_writer(t_editor *edit)
{
	if (edit->status == ED_WRITING)
		sdl_string_put(edit->rend, edit->ui->fonts.s64, (t_vct2){edit->size.x / 3, 20}, "Editing Variable", (SDL_Color){250, 250, 250, 255});
	else if (edit->status == ED_SAVING)
		sdl_string_put(edit->rend, edit->ui->fonts.s64, (t_vct2){edit->size.x / 3, 20}, "Saving", (SDL_Color){250, 250, 250, 255});
	sdl_draw_filename(edit, edit->filename);
}
