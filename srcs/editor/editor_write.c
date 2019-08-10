/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:28 by magrab            #+#    #+#             */
/*   Updated: 2019/08/10 22:38:30 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#define ISNUMPADNUM(x) ((SDLK_KP_1 <= x && x <= SDLK_KP_9) || x == SDLK_KP_0)

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

static int try_save(t_doom *doom, SDL_KeyboardEvent e)
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

/*
** ARMAAAAND
*/
void draw_forme(t_doom *doom, unsigned int x)
{
	t_pilier *pil;
	t_pilier *pil2;
	t_vct2		mov;
	t_vct2		vel;
	double		angle;
	double		angleincrem;
	double		len;

	ft_printf("DRAWING %d!\n", x);
	if (x < 2)
		return ;
	if (x == 2)
	{
		if (!(pil = ft_pillarpushend(&doom->edit.pillist, doom->edit.mapmouse)))
			ft_printf("Error adding pillar\n");
		ft_wallpushend(&doom->edit.map->murs, doom->edit.currpilier, pil, doom->edit.txtrgame[0]);
		return ;
	}
	//mov.x = doom->edit.currpilier->pos.x - doom->edit.mapmouse.x;
	//mov.y = doom->edit.currpilier->pos.y - doom->edit.mapmouse.y;
	mov.x = doom->edit.mapmouse.x - doom->edit.currpilier->pos.x; // Initialisation de la premiere position
	mov.y = doom->edit.mapmouse.y - doom->edit.currpilier->pos.y; // Initialisation de la premiere position
	pil = doom->edit.currpilier;
	pil2 = pil;
	angle = atan2(-mov.y, mov.x); // Calcul de l'angle initial par rapport aux deux premiers points

	angleincrem = -(360.0 / x - 180.0) * PI180; // Calcul de l'angle entre chacuns des sommets (Voir Geogebra)

	len = sqrt(mov.x * mov.x + mov.y * mov.y); // Calcul de la longueur entre chaque points

	printf("Start with angle : %f\tangleincrem : %f\tlen : %f\n", angle * TOANGLE, angleincrem * TOANGLE, len);
	while (x >= 2)
	{
		vel.x = cos(angle) * len;
		vel.y = -sin(angle) * len; // Calcul de la prochaine position par rapport a la pos actuelle (velocite FTW)

		printf("\tangle %12f\tvel : %12d %12d\t%12d %12d\n", angle * TOANGLE, vel.x, vel.y, mov.x, mov.y);

		if (!(pil = ft_pillarpushend(&doom->edit.pillist, (t_vct2){pil->pos.x + vel.x, pil->pos.y + vel.y}))) // Ajout pilier
			ft_printf("Error adding pillar\n");
		
		ft_wallpushend(&doom->edit.map->murs, pil, pil2, doom->edit.txtrgame[0]); // Creation du mur entre les 2 piliers

		pil2 = pil;
		angle += angleincrem;// Ajout de la Rotation
		if (angle < 0)
			angle += M_PI * 2;
		else if (angle * TOANGLE > 360)
			angle -= M_PI * 2;
		x--;
	}
	//ft_wallpushend(&doom->edit.map->murs, pil, doom->edit.currpilier, doom->edit.txtrgame[0]);
}

/*
**	ouvre un input pour remplir la chaine de caracteres str
*/
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
			if (try_save(doom, e) == -1)
				return (-1);
			doom->edit.status = ED_LOADED;
		}
		else if (doom->edit.status == ED_WRITING)
		{
			x = ft_lil_super_atoi(str);
			if (x < MAXEDITVAR)
				*doom->edit.currwriter = x;
			else
				*doom->edit.currwriter = MAXEDITVAR;
			doom->edit.status = ED_LOADED;
		}
		else if (doom->edit.status == ED_FORME)
		{
			x = ft_lil_super_atoi(str);
			if (x > 10)
				x = 0;
			draw_forme(doom, x);
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
	else if (edit->status == ED_FORME)
		sdl_string_put(edit->rend, edit->ui->fonts.s64, (t_vct2){edit->size.x / 2 - 120, 20}, "Number of points", (SDL_Color){250, 250, 250, 255});
	else if (edit->status == ED_SAVING)
		sdl_string_put(edit->rend, edit->ui->fonts.s64, (t_vct2){edit->size.x / 2 - 50, 20}, "Saving", (SDL_Color){250, 250, 250, 255});
	else if (edit->status == ED_OPEN)
		sdl_string_put(edit->rend, edit->ui->fonts.s64, (t_vct2){edit->size.x / 2 - 50, 20}, "Open", (SDL_Color){250, 250, 250, 255});
	sdl_draw_filename(edit, edit->filename);
}
