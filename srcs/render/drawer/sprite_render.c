/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 19:05:45 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 15:57:22 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "calcul.h"

void			sprite_render_list(t_sprite *sprite, t_arch *arch)
{
	while (sprite)
	{
		sprite_draw(sprite, arch);
		sprite = sprite->next;
	}
}

void			sprite_render_sector(t_arch *arch, t_sector *sector
	, t_player *player)
{
	t_sprite	*sprite;

	sprite = NULL;
	sprite_from_enemy(&sprite, sector->enemys, player, arch);
	sprite_from_props(&sprite, sector, player, arch);
	sprite_render_list(sprite, arch);
	sprite_iter(sprite, &sprite_free);
}
