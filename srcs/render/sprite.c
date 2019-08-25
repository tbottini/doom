/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 10:59:07 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/25 20:56:07 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "calcul.h"

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

t_sprite			*sprite_from_enemy(t_sprite **sprite_list, t_enemy *e
	, t_player *p, t_arch *a)
{
	t_sprite		*s;
	double			e_angle;
	int				posx;

	while (e)
	{
		e_angle = fvct2_angle(*(t_fvct2*)&p->stat.pos
			, *(t_fvct2*)&e->stat.pos, p->stat.rot.y);
		if (e_angle < 90 && e_angle > -90)
		{
			s = sprite_new(e->sprites, p->stat.pos, e->stat.pos, e_angle);
			if (!s)
				return (sprite_list_free(sprite_list));
			posx = a->sdl->size.x / 2 - s->pos.y / s->pos.x * a->cam->d_screen;
			s->heigth = cam_get_enemy_surface(a, e, p, s->pos.x);
			s->width = txtr_width(&s->texture, s->heigth, posx);
			sprite_insert(sprite_list, s);
		}
		e = e->next;
	}
	return (*sprite_list);
}

void				sprite_info_props(t_sprite *sprite, t_arch *arch
	, t_player *player, t_prop *props)
{
	int				posx;

	posx = arch->sdl->size.x / 2 - sprite->pos.y
		/ sprite->pos.x * arch->cam->d_screen;
	sprite->heigth = player_prop_heigth_surface(arch, player
		, props, sprite->pos.x);
	sprite->width = txtr_width(&sprite->texture, sprite->heigth, posx);
}

t_sprite			*sprite_from_props(t_sprite **sprite_list, t_prop *props
	, t_player *player, int len, t_arch *arch)
{
	t_sprite		*sprite;
	double			e_angle;
	int				i;

	i = -1;
	while (++i < len)
	{
		e_angle = fvct2_angle(*(t_fvct2*)&player->stat.pos
			, *(t_fvct2*)&props[i].pos, player->stat.rot.y);
		if (e_angle < 90 && e_angle > -90)
		{
			sprite = sprite_new(props[i].tex, player->stat.pos
				, props[i].pos, e_angle);
			if (!sprite)
				return (sprite_list_free(sprite_list));
			sprite_info_props(sprite, arch, player, &props[i]);
			if (point_behind_portal(arch, player, sprite->pos))
				sprite_insert(sprite_list, sprite);
			else
				free(sprite);
		}
	}
	return (*sprite_list);
}
