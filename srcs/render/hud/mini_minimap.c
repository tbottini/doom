/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 05:19:24 by akrache           #+#    #+#             */
/*   Updated: 2019/08/13 05:24:06 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "color.h"

static void			miniprops(t_minimap *mini, t_sector *sector, t_fvct3 pos)
{
	t_vct3	tmp;

	tmp.z = -1;
	while (++tmp.z < sector->len_prop)
	{
		tmp.x = (mini->a.x - (mini->size.x / 2))
			+ ((sector->props[tmp.z].pos.x - pos.x)) * (UNIT);
		tmp.y = (mini->a.y - (mini->size.y / 2))
			+ ((pos.y - sector->props[tmp.z].pos.y)) * (UNIT);
		bold_point2(mini, (t_vct2){tmp.x, tmp.y}, DEEPBLUE);
		tmp.x = (mini->a.x - (mini->size.x / 2))
			+ (((sector->props[tmp.z].pos.x + HITBOXSIZE) - pos.x)) * (UNIT);
		tmp.y = (mini->a.y - (mini->size.y / 2))
			+ ((pos.y - (sector->props[tmp.z].pos.y + HITBOXSIZE))) * (UNIT);
		bold_point2(mini, (t_vct2){tmp.x, tmp.y}, 0);
		tmp.y = (mini->a.y - (mini->size.y / 2))
			+ ((pos.y - (sector->props[tmp.z].pos.y + -HITBOXSIZE))) * (UNIT);
		bold_point2(mini, (t_vct2){tmp.x, tmp.y}, 0);
		tmp.x = (mini->a.x - (mini->size.x / 2))
			+ (((sector->props[tmp.z].pos.x + -HITBOXSIZE) - pos.x)) * (UNIT);
		bold_point2(mini, (t_vct2){tmp.x, tmp.y}, 0);
		tmp.y = (mini->a.y - (mini->size.y / 2))
			+ ((pos.y - (sector->props[tmp.z].pos.y + HITBOXSIZE))) * (UNIT);
		bold_point2(mini, (t_vct2){tmp.x, tmp.y}, 0);
	}
}

static void			minienemies(t_minimap *mini, t_sector *sector, t_fvct3 pos)
{
	int		i;
	t_vct2	tmp;
	t_enemy	*enn;

	i = 0;
	enn = sector->enemys;
	while (enn)
	{
		tmp.x = (mini->a.x - (mini->size.x / 2))
			+ ((enn->stat.pos.x - pos.x)) * (UNIT);
		tmp.y = (mini->a.y - (mini->size.y / 2))
			+ ((pos.y - enn->stat.pos.y)) * (UNIT);
		bold_point2(mini, tmp, CENEMY);
		enn = enn->next;
	}
}

static void			lil_miniinv(t_minimap *mini, t_player *p, SDL_Rect rect)
{
	int tmp;

	tmp = (mini->a.y - mini->d.y) / 5;
	rect.y += tmp;
	if (p->inv.key1)
		SDL_RenderCopy(mini->sdl->rend, mini->ui->props[10], NULL, &rect);
	rect.y += tmp;
	if (p->inv.key2)
		SDL_RenderCopy(mini->sdl->rend, mini->ui->props[11], NULL, &rect);
	rect.y += tmp;
	if (p->inv.key3)
		SDL_RenderCopy(mini->sdl->rend, mini->ui->props[12], NULL, &rect);
	rect.y += tmp;
	if (p->inv.last_key)
		SDL_RenderCopy(mini->sdl->rend, mini->ui->props[13], NULL, &rect);
}

void				miniinv(t_minimap *mini, t_player *player)
{
	int			tmp;
	SDL_Rect	rect;

	tmp = (mini->a.y - mini->d.y) / 5;
	rect = (SDL_Rect){mini->a.x, mini->d.y, tmp, tmp};
	if (player->inv.jetpack != -1)
	{
		SDL_RenderCopy(mini->sdl->rend, mini->ui->props[6], NULL, &rect);
		if (!player->inv.jetpack)
		{
			SDL_SetRenderDrawColor(mini->sdl->rend, 128, 128, 128, 255);
			SDL_RenderDrawRect(mini->sdl->rend, &rect);
			SDL_SetRenderDrawColor(mini->sdl->rend, 0, 0, 0, 0);
		}
	}
	lil_miniinv(mini, player, rect);
}

void				minimap(t_minimap *mini, t_player *player)
{
	miniwalls(player, player->stat.sector, mini);
	minifill(mini, player->stat.health, player->power);
	minibord(mini);
	minifield(player, mini);
	miniprops(mini, player->stat.sector, player->stat.pos);
	minienemies(mini, player->stat.sector, player->stat.pos);
	bold_point2(mini, mini->mid, WHITE);
}
