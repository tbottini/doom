/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_ptr_from_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 19:47:49 by magrab            #+#    #+#             */
/*   Updated: 2019/08/21 19:47:50 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	remove_in_stat(t_ecoord *coord, void *ptr)
{
	if (coord->sector == ptr)
		coord->sector = NULL;
	if (coord->mur == ptr)
		coord->mur = NULL;
	if (coord->mursec == ptr)
		coord->mursec = NULL;
}

static void	remove_in_wall(t_mur *mur, void *ptr)
{
	t_entity *ent;

	if (mur->portal_ptr == ptr)
		mur->portal_ptr = NULL;
	if (mur->txtr == ptr)
		mur->txtr = NULL;
	if (mur->wproplist == ptr)
		mur->wproplist = mur->wproplist->next;
	ent = mur->wproplist;
	while (ent)
	{
		remove_in_stat(&ent->stat, ptr);
		ent = ent->next;
	}
}

static void	remove_in_props(t_lstent lstent, void *ptr)
{
	while (lstent)
	{
		remove_in_stat(&lstent->stat, ptr);
		lstent = lstent->next;
	}
}

void		remove_ptr_from_map(t_lstsec lstsec, t_lstent lstent, void *ptr)
{
	t_mur		*mur;

	if (!ptr)
		return ;
	while (lstsec)
	{
		if (lstsec->sol == ptr)
			lstsec->sol = NULL;
		if (lstsec->top == ptr)
			lstsec->top = NULL;
		if (lstsec->murs == ptr)
			lstsec->murs = lstsec->murs->next;
		mur = lstsec->murs;
		while (mur)
		{
			remove_in_wall(mur, ptr);
			mur = mur->next;
		}
		lstsec = lstsec->next;
	}
	remove_in_props(lstent, ptr);
}
