/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prop_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 18:17:36 by magrab            #+#    #+#             */
/*   Updated: 2019/08/18 18:17:39 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** =============key 1====================
*/

void	addkey1(t_inv *inv)
{
	if (inv->key1 == false)
		inv->key1 = true;
}

/*
** =============key 3====================
*/

void	addkey2(t_inv *inv)
{
	if (inv->key2 == false)
		inv->key2 = true;
}

/*
** =============key 3====================
*/

void	addkey3(t_inv *inv)
{
	if (inv->key3 == false)
		inv->key3 = true;
}

/*
** =============Last Key====================
*/

void	addlastkey(t_inv *inv)
{
	if (inv->last_key == false)
		inv->last_key = true;
}
