/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 18:01:30 by magrab            #+#    #+#             */
/*   Updated: 2019/04/25 19:37:49 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		void_wolf(t_wolf *wolf)
{
	ft_bzero(wolf, sizeof(t_wolf));
}

static t_wall	nload_texture(t_wolf *wolf, const char *file)
{
	SDL_RWops *rwop;
	SDL_Surface *surf;
	SDL_Surface *tmp;
	t_wall		wall;

	rwop = SDL_RWFromFile(file, "rb");
	if(!(tmp = IMG_LoadXPM_RW(rwop)))
	{
		ft_printf("IMG_LoadXPM_RW: %s\n", IMG_GetError());
		prog_quit(wolf);
	}
	if(!(surf = SDL_ConvertSurface(tmp, wolf->sdl.format, 0)))
	{
		ft_printf("SDL_ConvertSurface: failed\n");
		prog_quit(wolf);
	}
	SDL_FreeSurface(tmp);
	SDL_RWclose(rwop);
	wall.txture = surf->pixels;
	wall.surf = surf;
	wall.w = surf->w;
	wall.h = surf->h;
	return (wall);
}

void			lil_wolf_init(t_wolf *wolf)
{
	wolf->nwall[0] = nload_texture(wolf, "./ressources/textures/wall_blue.xpm");
	wolf->nwall[1] = nload_texture(wolf, "./ressources/textures/wall.xpm");
	wolf->nwall[2] = nload_texture(wolf, "./ressources/textures/plaqueor.xpm");
	wolf->nwall[3] = nload_texture(wolf, "./ressources/textures/test.xpm");
}

t_wolf			*wolf_init(void)
{
	t_wolf *wolf;

	if (!(wolf = (t_wolf *)malloc(sizeof(t_wolf))))
		return (NULL);
	void_wolf(wolf);
	if (sdl_start(wolf, "Wolf 3D"))
		return (NULL);
	wolf->ui.btnarr[0] = add_wolf_button(wolf);
	wolf->ui.btnarr[1] = add_start_button(wolf);
	wolf->ui.btnarr[2] = add_opt_button(wolf);
	wolf->ui.btnarr[3] = add_quit_button(wolf, " Quit ");
	wolf->ui.btnmap[0] = add_quit_button(wolf, " Return ");
	wolf->ui.btnmap[1] = add_mapmenu_button(wolf);
	wolf->ui.btnopt[0] = wolf->ui.btnmap[0];
	wolf->ui.btnopt[1] = wolf->ui.btnarr[0];
	lil_wolf_init(wolf);
	wolf->ui.slidopt[0] = add_fov_slider(wolf);
	wolf->pos.x = 0;
	wolf->pos.y = 0;
	wolf->fov = 90;
	wolf->rot = 90;
	return (wolf);
}
