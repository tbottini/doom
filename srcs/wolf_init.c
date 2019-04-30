/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 18:01:30 by magrab            #+#    #+#             */
/*   Updated: 2019/04/26 18:26:36 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		void_wolf(t_doom *doom)
{
	ft_bzero(doom, sizeof(t_doom));
}

static t_wall	load_texture(t_doom *doom, const char *file)
{
	SDL_RWops	*rwop;
	SDL_Surface	*surf;
	SDL_Surface	*tmp;
	t_wall		wall;

	rwop = SDL_RWFromFile(file, "rb");
	if (!(tmp = IMG_LoadXPM_RW(rwop)))
	{
		ft_printf("IMG_LoadXPM_RW: %s\n", IMG_GetError());
		prog_quit(doom);
	}
	if (!(surf = SDL_ConvertSurface(tmp, doom->sdl.format, 0)))
	{
		ft_printf("SDL_ConvertSurface: failed\n");
		prog_quit(doom);
	}
	SDL_FreeSurface(tmp);
	SDL_RWclose(rwop);
	wall.txture = surf->pixels;
	wall.surf = surf;
	wall.w = surf->w;
	wall.h = surf->h;
	return (wall);
}

void			lil_wolf_init(t_doom *doom)
{
	doom->wall[0] = load_texture(doom, "./ressources/textures/wall_blue.xpm");
	doom->wall[1] = load_texture(doom, "./ressources/textures/wall.xpm");
	doom->wall[2] = load_texture(doom, "./ressources/textures/plaqueor.xpm");
	doom->wall[3] = load_texture(doom, "./ressources/textures/test.xpm");
}

t_doom			*wolf_init(void)
{
	t_doom *doom;

	if (!(doom = (t_doom *)malloc(sizeof(t_doom))))
		return (NULL);
	void_wolf(doom);
	if (sdl_start(doom, "Doom-Nukem"))
		return (NULL);
	doom->ui.btnarr[0] = add_wolf_button(doom);
	doom->ui.btnarr[1] = add_start_button(doom);
	doom->ui.btnarr[2] = add_opt_button(doom);
	doom->ui.btnarr[3] = add_quit_button(doom, " Quit ");
	doom->ui.btnmap[0] = add_quit_button(doom, " Return ");
	doom->ui.btnmap[1] = add_mapmenu_button(doom);
	doom->ui.btnopt[0] = doom->ui.btnmap[0];
	doom->ui.btnopt[1] = doom->ui.btnarr[0];
	lil_wolf_init(doom);
	doom->ui.slidopt[0] = add_fov_slider(doom);
	doom->pos.x = 0;
	doom->pos.y = 0;
	doom->fov = 90;
	doom->rot = 90;
	doom->map = NULL;
	return (doom);
}
