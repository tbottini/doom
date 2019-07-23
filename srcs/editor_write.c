/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:28 by magrab            #+#    #+#             */
/*   Updated: 2019/07/21 13:37:27 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

unsigned int ft_lil_super_atoi(const char *str)
{
	unsigned int ret;

	if (!*str)
		return (0);
	ret = 0;
	while (*str && ft_isdigit(*str))
	{
		ret = ret * 10 + *str - 48;
		str++;
	}
	return (*str ? 0 : ret);
}

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

/*
**	ouvre un input pour remplir la chaine de caracteres str
*/
#define ISNUMPADNUM(x) ((SDLK_KP_1 <= x && x <= SDLK_KP_9) || x == SDLK_KP_0)

int write_hook(t_doom *doom, char *str, SDL_KeyboardEvent e)
{
	unsigned int x;

	if (ft_isalnum(e.keysym.sym) || ISNUMPADNUM(e.keysym.sym))
	{
		if (e.keysym.mod & (KMOD_LSHIFT | KMOD_RSHIFT | KMOD_CAPS))
			push_char(str, e.keysym.sym - 32);
		else if (SDLK_KP_1 <= e.keysym.sym && e.keysym.sym <= SDLK_KP_9)
			push_char(str, e.keysym.sym - 1073741864);
		else if (e.keysym.sym == SDLK_KP_0)
			push_char(str, e.keysym.sym - 1073741874);
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
	else if (e.keysym.sym == SDLK_RETURN || e.keysym.sym == SDLK_KP_ENTER)
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
			//x = ft_atoi(str);
			x = ft_lil_super_atoi(str);
			if (x < MAXEDITVAR)
				*doom->edit.currwriter = x;
			else
				*doom->edit.currwriter = MAXEDITVAR;
			doom->edit.status = ED_LOADED;
		}
		else if (doom->edit.status == ED_OPEN)
		{
			editor_reset(&doom->edit);
			printf(WGREEN"Tentative d'ouverture du fichier %s\n"WEND, str);
			if (read_file_to_editor(&doom->edit, str) != 0)
				printf(WRED"fail\n"WEND);
			else
			{
				printf(WGREEN"open\n"WEND);
				doom->edit.status = ED_LOADED;
			}
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
		sdl_string_put(edit->rend, edit->ui->fonts.s64, (t_vct2){edit->size.x / 2 - 50, 20}, "HEIGHT", (SDL_Color){250, 250, 250, 255});
	else if (edit->status == ED_SAVING)
		sdl_string_put(edit->rend, edit->ui->fonts.s64, (t_vct2){edit->size.x / 2 - 50, 20}, "Saving", (SDL_Color){250, 250, 250, 255});
	else if (edit->status == ED_OPEN)
		sdl_string_put(edit->rend, edit->ui->fonts.s64, (t_vct2){edit->size.x / 2 - 50, 20}, "Open", (SDL_Color){250, 250, 250, 255});
	sdl_draw_filename(edit, edit->filename);
}
