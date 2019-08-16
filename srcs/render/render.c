/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:06:44 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/13 08:24:14 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "render.h"

void				sprites_list_render(t_arch *arch, t_player *player
	, t_sector *sector)
{
	t_sprite		*sprite;

	sprite = NULL;
	sprite_from_enemy(&sprite, sector->enemys, player, arch);
	sprite_from_props(&sprite, sector->props, player, sector->len_prop, arch);
	sprite_render_list(sprite, arch);
	sprite_iter(sprite, &sprite_free);
}

/*
**	on recupere les information du secteur par rapport
**		au frustum (champs de vision du joueur)
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
	sector_frustum(arch, sector, player);
	arch->sector = sector;
	portal_tmp = arch->wall;
	while (i < sector->len)
	{
		on_frustum(arch, player, wall[i].pillar);
		on_frustum(arch, player, wall[i].next);
		if (((wall[i].pillar->frust || wall[i].next->frust)
			|| borne_in_wall_angle(arch, &wall[i]))
				&& equal_pillar(&wall[i], arch->wall))
		{
			portal_tmp = arch->wall;
			arch->wall = &wall[i];
			render_wall(arch, player);
			arch->wall = portal_tmp;
		}
		i++;
	}
	sprites_list_render(arch, player, sector);
}

void				clear_screen(t_sdl *sdl)
{
	int			i;

	i = 0;
	while (i < sdl->size.x * sdl->size.y)
	{
		sdl->screen[i] = 0;
		i++;
	}
}

/*
**	les etapes de rendu du jeu
**	on initialise arch wall a null
**	(NULL est un signal pour indiquer que le rendu du secteur ne se fait
**		pas a travers un portail)
**	doom_render fait le premier rendu de secteur
**		(celui dans lequel le joueur se trouve)
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
