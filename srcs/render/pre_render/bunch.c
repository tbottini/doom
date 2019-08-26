/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bunch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 01:52:58 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 14:34:15 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "input.h"

int			on_frustum(t_arch *arch, t_player *player, t_pillar *pillar)
{
	t_fvct2	dist;
	double	angle;

	if (arch->wall && (pillar == arch->wall->pillar
		|| pillar == arch->wall->next))
		return (0);
	dist.x = pillar->p.x - player->stat.pos.x;
	dist.y = pillar->p.y - player->stat.pos.y;
	angle = atan2(dist.y, dist.x) * TOANGLE;
	if (angle < 0)
		angle = 360 + angle;
	angle = double_modulo(angle - player->stat.rot.y);
	if (angle < -180)
		angle += 360;
	else if (angle > 180)
		angle -= 360;
	pillar->angle = angle;
	if (angle >= arch->portal.b_right && angle <= arch->portal.b_left)
		pillar->frust = 1;
	else
		pillar->frust = 0;
	return (pillar->frust);
}

void		wall_frustum(t_arch *arch, t_player *player, t_wall *wall)
{
	on_frustum(arch, player, wall->pillar);
	on_frustum(arch, player, wall->next);
}

/*
**	renvoie l'angle entre un pillier -> joueur -> pillier_next
*/

double		wall_angle_pers(t_arch *arch, t_wall wall)
{
	double	field;
	t_fvct2	angles;

	if (arch->portal.b_left * arch->portal.b_right > 0)
		return (0);
	angles.x = wall.pillar->angle;
	angles.y = wall.next->angle;
	if (wall.pillar->angle < 0)
		angles.x += 360;
	if (wall.next->angle < 0)
		angles.y += 360;
	field = fabs(angles.y - angles.x);
	return (field);
}

/*
**	prend une autre reference pour les angles : ex
**	la reference est la rotation du joueur ce qui est a gauche + a droite -
**	ca sera utilise pour les borne de la fenetre
*/

double		local_angle(double borne, double angle)
{
	angle = angle - borne;
	if (angle < 0)
		angle += 360;
	return (angle);
}

int			equal_pillar(t_wall *wall1, t_wall *wall2)
{
	if (!wall1 || !wall2)
		return (1);
	if (wall1->pillar == wall2->pillar && wall1->next == wall2->next)
		return (0);
	if (wall1->pillar == wall2->next && wall1->next == wall2->pillar)
		return (0);
	return (1);
}
