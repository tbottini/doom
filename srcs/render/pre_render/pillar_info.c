/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pillar_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 21:55:18 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 15:30:31 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
**	si au moins l'un des pilier est hors frustum il passe pas l'extremite de
**	l'ecran, on determine laquelle avec une polarite (-1 == 0px et 1 == max)
**	si l'angle entre le joueur est les deux pillier est superieur a 180
**	la polarite de depart (position du premier pillier) s'inverse
*/

void			px_polarite(t_arch *arch)
{
	t_fvct2		angle;
	double		diff;
	int			polarite;

	angle.x = local_angle(arch->portal.b_left, arch->wall->pillar->angle);
	angle.y = local_angle(arch->portal.b_left, arch->wall->next->angle);
	diff = fabs(angle.x - angle.y);
	polarite = (arch->wall->next->angle > arch->portal.b_left ? -1 : 1)
		* (diff < 180 ? 1 : -1);
	arch->px.x = (polarite == -1) ? 0 : arch->sdl->size.x - 1;
	arch->px.y = arch->sdl->size.x - 1 - arch->px.x;
}

int				pillar_polarite(t_arch *arch, t_pillar *pillar, t_pillar *next)
{
	double		angle;
	double		angle_next;
	double		borne;

	angle = local_angle(arch->portal.b_left, pillar->angle);
	angle_next = local_angle(arch->portal.b_left, next->angle);
	borne = local_angle(arch->portal.b_left, arch->portal.b_right);
	if (angle < borne - 180)
		return (0);
	else if (angle > 180)
		return (arch->sdl->size.x - 1);
	else if (fabs(angle - angle_next) > 180)
		return (0);
	else
		return (arch->sdl->size.x - 1);
}

void			pillar_out_frust(t_arch *a, t_player *p, int flag)
{
	if (flag == PILLAR)
	{
		a->px.x = fish_bowl_px(a, *a->wall->pillar);
		a->pillar.x = distance(*(t_fvct2*)&p->stat.pos, a->wall->pillar->p);
		a->pillar.y = sin(a->wall->pillar->angle * PI180) * a->pillar.x;
		a->pillar.x = cos(a->wall->pillar->angle * PI180) * a->pillar.x;
		a->shift_txtr.x = 1;
	}
	else
	{
		a->px.y = fish_bowl_px(a, *a->wall->next);
		a->next.x = distance(*(t_fvct2*)&p->stat.pos, a->wall->next->p);
		a->next.y = sin(a->wall->next->angle * PI180) * a->next.x;
		a->next.x = cos(a->wall->next->angle * PI180) * a->next.x;
		a->shift_txtr.y = 0;
	}
}

void			pil_screen_info(t_arch *a, t_player *p)
{
	float		angle;
	t_fvct2		tmp;

	if (a->wall->pillar->frust)
		pillar_out_frust(a, p, PILLAR);
	else
	{
		a->px.x = pillar_polarite(a, a->wall->pillar, a->wall->next);
		if (a->px.x == 0)
		{
			a->px.x = a->sdl->size.x / 2.0 - (tan(a->portal.b_left * PI180)
				* a->cam->d_screen);
			angle = p->stat.rot.y + a->portal.b_left;
		}
		else
		{
			a->px.x = a->sdl->size.x / 2.0 - (tan(a->portal.b_right * PI180)
				* a->cam->d_screen);
			angle = p->stat.rot.y + a->portal.b_right;
		}
		a->shift_txtr.x = wall_clipping(a, p, &tmp, angle);
		a->pillar = tmp;
	}
}

void			next_screen_info(t_arch *a, t_player *p)
{
	float		angle;
	t_fvct2		tmp;

	if (a->wall->next->frust)
		pillar_out_frust(a, p, NEXT);
	else
	{
		a->px.y = pillar_polarite(a, a->wall->next, a->wall->pillar);
		if (a->px.y == 0)
		{
			a->px.y = a->sdl->size.x / 2.0 - (tan(a->portal.b_left * PI180)
				* a->cam->d_screen);
			angle = p->stat.rot.y + a->portal.b_left;
		}
		else
		{
			a->px.y = a->sdl->size.x / 2.0 - (tan(a->portal.b_right * PI180)
				* a->cam->d_screen);
			angle = p->stat.rot.y + a->portal.b_right;
		}
		a->shift_txtr.y = wall_clipping(a, p, &tmp, angle);
		a->next = tmp;
	}
}
