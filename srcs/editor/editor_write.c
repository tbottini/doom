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
#include "color.h"
#include "screen.h"
#define ISNUMPADNUM(x) ((SDLK_KP_1 <= x && x <= SDLK_KP_9) || x == SDLK_KP_0)

/*
** void draw_forme(t_doom *doom, unsigned int x)
** {
** 	t_pilier *pil;
** 	t_pilier *pil2;
** 	t_vct2		mov;
** 	t_vct2		vel;
** 	double		angle;
** 	double		angleincrem;
** 	double		len;
**
** 	ft_printf("DRAWING %d!\n", x);
** 	if (x < 2)
** 		return ;
** 	if (x == 2)
** 	{
** 		if (!(pil = ft_pillarpushend(&doom->edit.pillist, doom->edit.mapmouse)))
** 			ft_printf("Error adding pillar\n");
** 		ft_wallpushend(&doom->edit.map->murs, doom->edit.currpilier, pil,
**			doom->edit.txtrgame[0]);
** 		return ;
** 	}
** 	mov.x = doom->edit.mapmouse.x - doom->edit.currpilier->pos.x;
** 	mov.y = doom->edit.mapmouse.y - doom->edit.currpilier->pos.y;
** 	pil = doom->edit.currpilier;
** 	pil2 = pil;
** 	angle = atan2(-mov.y, mov.x);
**
** 	angleincrem = -(360.0 / x - 180.0) * PI180;
**
** 	len = sqrt(mov.x * mov.x + mov.y * mov.y);
**
** 	printf("Start with angle : %f\tangleincrem : %f\tlen : %f\n",
**		angle * TOANGLE, angleincrem * TOANGLE, len);
** 	while (x >= 2)
** 	{
** 		vel.x = cos(angle) * len;
** 		vel.y = -sin(angle) * len;
**
** 		printf("\tangle %12f\tvel : %12d %12d\t%12d %12d\n", angle * TOANGLE,
**			vel.x, vel.y, mov.x, mov.y);
**
** 		if (!(pil = ft_pillarpushend(&doom->edit.pillist,
**				(t_vct2){pil->pos.x + vel.x, pil->pos.y + vel.y})))
** 			ft_printf("Error adding pillar\n");
** 		pil2 = pil;
** 		angle += angleincrem;
** 		if (angle < 0)
** 			angle += M_PI * 2;
** 		else if (angle * TOANGLE > 360)
** 			angle -= M_PI * 2;
** 		x--;
** 	}
** }
*/

int			editor_reset(t_editor *edit)
{
	if (edit->ennlist)
		ft_clear_entity_list(&(edit->ennlist));
	if (edit->sectors)
		ft_clear_secteur_list(&(edit->sectors));
	if (edit->pillist)
		ft_clear_pillar_list(&(edit->pillist));
	edit->txtrscroll = 0;
	ft_bzero(edit->txtrreal, sizeof(SDL_Texture *) * MAXTXTRNUMBER);
	edit->map = NULL;
	edit->currmur = NULL;
	edit->currstat = NULL;
	edit->currpilier = NULL;
	return (1);
}

static void	on_writing(t_doom *doom, char *str)
{
	unsigned int x;

	x = ft_lil_super_atoi(str);
	if (x < MAXEDITVAR)
		*doom->edit.currwriter = x;
	else
		*doom->edit.currwriter = MAXEDITVAR;
	doom->edit.status = ED_LOADED;
}

static int	lil_write_hook(t_doom *doom, char *str, SDL_KeyboardEvent e)
{
	if (e.keysym.sym == SDLK_RETURN || e.keysym.sym == SDLK_KP_ENTER)
	{
		if (doom->edit.status == ED_SAVING)
		{
			if (try_save(doom, e) == -1)
				return (-1);
			doom->edit.status = ED_LOADED;
		}
		else if (doom->edit.status == ED_WRITING)
			on_writing(doom, str);
		else if (doom->edit.status == ED_OPEN)
		{
			editor_reset(&doom->edit);
			if (read_file_to_editor(&doom->edit, str) != 0)
				ft_printf(WRED"fail\n"WEND);
			else
				doom->edit.status = ED_LOADED;
		}
		ft_bzero(str, sizeof(char) * MAXFILENAMELEN);
	}
	return (0);
}

/*
**	ouvre un input pour remplir la chaine de caracteres str
*/

int			write_hook(t_doom *doom, char *str, SDL_KeyboardEvent e)
{
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
		push_char(str, '\0');
	else if (e.keysym.sym == SDLK_BACKQUOTE)
	{
		ft_bzero(str, sizeof(char) * MAXFILENAMELEN);
		doom->edit.status = ED_LOADED;
	}
	else
		return (lil_write_hook(doom, str, e));
	return (0);
}

/*
**		else if (doom->edit.status == ED_FORME)
**		{
**			x = ft_lil_super_atoi(str);
**			if (x > 10)
**				x = 0;
**			draw_forme(doom, x);
**			doom->edit.status = ED_LOADED;
**		}
*/
