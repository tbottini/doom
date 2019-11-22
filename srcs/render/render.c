/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:06:44 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 14:10:41 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "render.h"

/*
**	va checker si le mur est un portail qui est lie a lui meme
*/

int					portal_link_self(t_wall *wall, t_sector *sector)
{
	if (wall->status == PORTAL)
	{
		return (wall->link == sector);
	}
	return (0);
}

bool				surface_is_printable(t_arch *arch, t_wall *wall
	, t_sector *sector)
{
	return (((wall->pillar->frust || wall->next->frust)
			|| borne_in_wall_angle(arch, wall))
			&& equal_pillar(wall, arch->wall)
			&& !portal_link_self(wall, sector));
}

/*
**	on recupere les information du secteur par rapport au frustum
**		(champs de vision du joueur)
**	on definit un bunch contenant les mur visibles
**	on affiche ce bunch
*/

void				sector_render(t_arch *arch, t_player *player
	, t_sector *sector)
{
	t_wall			*wall;
	int				i;
	t_wall			*portal_tmp;

	i = 0;
	wall = sector->wall;
	arch->sector = sector;
	portal_tmp = arch->wall;
	while (i < sector->len)
	{
		wall_frustum(arch, player, &wall[i]);
		if (surface_is_printable(arch, &wall[i], sector))
		{
			portal_tmp = arch->wall;
			arch->wall = &wall[i];
			render_wall(arch, player);
			arch->wall = portal_tmp;
		}
		i++;
	}
	sprite_render_sector(arch, sector, player);
}

void				render_recursivite(t_arch *arch, t_player *player
	, t_vct2 pixel_portal)
{
	arch->px = pixel_portal;
	set_borne_horizontal(arch);
	arch->portal.pillar = arch->pillar;
	arch->portal.next = arch->next;
	arch->depth_portal++;
	sector_render(arch, player, arch->wall->link);
	arch->depth_portal--;
}

/*
**	les etapes de rendu du jeu
**	on initialise arch wall a null
**	(NULL est un signal pour indiquer que le rendu du secteur ne se fait
**		pas a travers un portail)
**	doom_render fait le premier rendu de secteur (celui dans lequel
**		le joueur se trouve)
*/

int					doom_render(t_doom *doom)
{
	int				i;
	t_minimap		mini;

	i = 0;
	doom->game.arch.depth_portal = 0;
	doom->game.arch.wall = NULL;
	sector_render(&doom->game.arch, &doom->game.player
		, doom->game.player.stat.sector);
	mini = miniinit(&doom->sdl, &doom->ui);
	minimap(&mini, &doom->game.player);
	hud_aim(doom);
	sdl_multirendercopy(&doom->sdl);
	miniinv(&mini, &doom->game.player);
	architect_reset(&doom->game.arch);
	return (1);
}
