/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 15:29:31 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 15:30:36 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
**	on recupere les information pour le pilier et pour le pilier next
*/

void			pillar_screen_info(t_arch *arch, t_player *p)
{
	pil_screen_info(arch, p);
	next_screen_info(arch, p);
}
