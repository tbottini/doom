/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_write_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 02:21:43 by magrab            #+#    #+#             */
/*   Updated: 2019/08/13 02:21:44 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		sdl_draw_filename(t_editor *edit, const char *text)
{
	t_sloc		box;
	SDL_Texture	*texture;
	SDL_Surface	*surf;

	box.snapx = 1;
	box.snapy = 1;
	box.pos.x = 50;
	box.pos.y = 20;
	surf = TTF_RenderText_Shaded(edit->ui->fonts.s32, text,
		(SDL_Color){250, 250, 250, 255}, (SDL_Color){0, 0, 0, 255});
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

void	draw_writer(t_editor *edit)
{
	if (edit->status == ED_WRITING)
		sdl_string_put((t_sp){edit->rend, edit->ui->fonts.s64,
			(t_vct2){edit->size.x / 2 - 50, 20}, "HEIGHT",
			(SDL_Color){250, 250, 250, 255}});
	else if (edit->status == ED_SAVING)
		sdl_string_put((t_sp){edit->rend, edit->ui->fonts.s64,
			(t_vct2){edit->size.x / 2 - 50, 20}, "Saving",
			(SDL_Color){250, 250, 250, 255}});
	else if (edit->status == ED_OPEN)
		sdl_string_put((t_sp){edit->rend, edit->ui->fonts.s64,
			(t_vct2){edit->size.x / 2 - 50, 20}, "Open",
			(SDL_Color){250, 250, 250, 255}});
	sdl_draw_filename(edit, edit->filename);
}

/*
**	else if (edit->status == ED_FORME)
**		sdl_string_put((t_sp){edit->rend, edit->ui->fonts.s64,
**			(t_vct2){edit->size.x / 2 - 120, 20}, "Number of points",
**			(SDL_Color){250, 250, 250, 255}});
*/

void	push_char(char *str, char c)
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

int		try_save(t_doom *doom, SDL_KeyboardEvent e)
{
	char path[512];

	ft_strcpy(path, "ressources/map/");
	if (save_editor_to_file(&doom->edit))
		return (-1);
	if (e.keysym.mod != 0)
		close_editor(doom);
	return (0);
}

/*
** To auto open on save
**	else if (doom->ui.m_status == MENU_MAIN)
**	{
**		ft_strcat(path, doom->edit.filename);
**		//main_menu_button(doom);
**		if (check_file(path))
**		{
**			read_file(&doom->game, path, false);
**			player_init(&doom->game.player);
**			change_music(&doom->game.sound, doom->game.sound.on, 5000);
**			sdl_set_status(doom, MENU_INGAME);
**			SDL_RaiseWindow(doom->sdl.win);
**		}
**	}
**	return (0);
**}
*/
