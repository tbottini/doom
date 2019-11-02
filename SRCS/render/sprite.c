/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 10:59:07 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 15:56:57 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "calcul.h"

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

t_sprite			*sprite_from_props(t_sprite **sprite_list, t_sector *s
	, t_player *player, t_arch *arch)
{
	t_sprite		*sprite;
	double			e_angle;
	int				i;

	i = -1;
	while (++i < s->len_prop)
	{
		e_angle = fvct2_angle(*(t_fvct2*)&player->stat.pos
			, *(t_fvct2*)&s->props[i].pos, player->stat.rot.y);
		if (e_angle < 90 && e_angle > -90 && s->props[i].hitbox.h >= 0)
		{
			sprite = sprite_new(s->props[i].tex, player->stat.pos
				, s->props[i].pos, e_angle);
			if (!sprite)
				return (sprite_list_free(sprite_list));
			sprite_info_props(sprite, arch, player, &s->props[i]);
			if (point_behind_portal(arch, player, sprite->pos))
				sprite_insert(sprite_list, sprite);
			else
				free(sprite);
		}
	}
	return (*sprite_list);
}
