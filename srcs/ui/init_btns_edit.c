/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_btns_edit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:28 by magrab            #+#    #+#             */
/*   Updated: 2019/04/16 00:18:29 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_btn	add_test_button(t_editor *edit, SDL_Rect *parent)
{
	t_btn			tmp;

	ft_bzero(&tmp, sizeof(t_btn));
	tmp.func = NULL;
	tmp.loc.parent = parent;
	tmp.loc.pos.x = 10;
	tmp.loc.pos.y = 10;
	tmp.loc.snapx = 4;
	tmp.loc.snapy = 4;
	tmp.fgcolor = (SDL_Color){255, 255, 255, 0};
	tmp.bgcolor = (SDL_Color){191, 35, 44, 0};
	updatetext((t_updatetext){edit->rend, edit->ui->fonts.s32, &tmp.txture,
		&tmp.loc.area, "truc", tmp.fgcolor, tmp.bgcolor});
	return (tmp);
}
