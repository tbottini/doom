/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_man.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:08:22 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 15:44:00 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "calcul.h"

t_sprite			*sprite_new(t_txtr texture, t_fvct3 origin
	, t_fvct3 dist, double angle)
{
	t_sprite		*sprite;

	sprite = (t_sprite*)malloc(sizeof(t_sprite));
	if (!sprite)
		return (NULL);
	sprite->texture = texture;
	sprite->next = NULL;
	sprite->pos.x = distance(*(t_fvct2*)&origin, *(t_fvct2*)&dist);
	sprite->pos.y = sprite->pos.x * sin(angle * TO_RADIAN);
	sprite->pos.x = sprite->pos.x * cos(angle * TO_RADIAN);
	return (sprite);
}

void				sprite_free(t_sprite *sprite)
{
	if (sprite)
	{
		free(sprite);
		sprite = NULL;
	}
}

void				sprite_iter(t_sprite *sprite, void (*effector)(t_sprite*))
{
	t_sprite		*tmp;

	while (sprite)
	{
		tmp = sprite->next;
		effector(sprite);
		sprite = tmp;
	}
}

t_sprite			*sprite_list_free(t_sprite **sprite_list)
{
	sprite_iter(*sprite_list, &sprite_free);
	*sprite_list = NULL;
	return (NULL);
}

void				sprite_insert(t_sprite **sprite_list
	, t_sprite *sprite_node)
{
	t_sprite		*sprite_insert;

	sprite_insert = *sprite_list;
	if (!sprite_insert)
		*sprite_list = sprite_node;
	else if (sprite_node->pos.x > sprite_insert->pos.x)
	{
		sprite_node->next = *sprite_list;
		*sprite_list = sprite_node;
	}
	else
	{
		while (sprite_insert->next && sprite_node->pos.x
			< sprite_insert->next->pos.x)
			sprite_insert = sprite_insert->next;
		sprite_node->next = sprite_insert->next;
		sprite_insert->next = sprite_node;
	}
}
