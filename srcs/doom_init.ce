/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 18:01:30 by magrab            #+#    #+#             */
/*   Updated: 2019/04/26 18:26:36 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static int		secure_doom(t_doom *doom)
{
	int fd;

	if ((fd = open(TTFWOLF, O_RDONLY | O_NOFOLLOW)) < 0)
		return (-1);
	close(fd);
	if ((fd = open(TTFIMPACT, O_RDONLY | O_NOFOLLOW)) < 0)
		return (-1);
	close(fd);
	if ((fd = open(WALLBLUE, O_RDONLY | O_NOFOLLOW)) < 0)
		return (-1);
	close(fd);
	if ((fd = open(WALL, O_RDONLY | O_NOFOLLOW)) < 0)
		return (-1);
	close(fd);
	if ((fd = open(GOLD, O_RDONLY | O_NOFOLLOW)) < 0)
		return (-1);
	close(fd);
	if ((fd = open(TEST, O_RDONLY | O_NOFOLLOW)) < 0)
		return (-1);
	close(fd);
	ft_bzero(doom, sizeof(t_doom));
	return (0);
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

void			lil_doom_init(t_doom *doom)
{
	doom->wall[0] = load_texture(doom, WALL);
	doom->wall[1] = load_texture(doom, WALL);
	doom->wall[2] = load_texture(doom, WALL);
	doom->wall[3] = load_texture(doom, WALL);
}

t_doom			*doom_init(void)
{
	t_doom *doom;

	if (!(doom = (t_doom *)malloc(sizeof(t_doom))))
		return (NULL);
	if (secure_doom(doom))
		return (NULL);
	if (sdl_start(doom, "Doom-Nukem"))
		return (NULL);
	doom->ui.btnarr[0] = add_doom_button(doom);
	doom->ui.btnarr[1] = add_start_button(doom);
	doom->ui.btnarr[2] = add_opt_button(doom);
	doom->ui.btnarr[3] = add_editor_button(doom);
	doom->ui.btnarr[4] = add_quit_button(doom, " Quit ");
	doom->ui.btnmap[0] = add_quit_button(doom, " Return ");
	doom->ui.btnmap[1] = add_mapmenu_button(doom);
	doom->ui.btnopt[0] = doom->ui.btnmap[0];
	doom->ui.btnopt[1] = doom->ui.btnarr[0];
	lil_doom_init(doom);
	doom->ui.slidopt[0] = add_fov_slider(doom);
	doom->pos.x = 0;
	doom->pos.y = 0;
	doom->fov = 90;
	doom->rot = 90;
	doom->map = NULL;
	return (doom);
}
