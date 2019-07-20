/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameover.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 18:30:40 by akrache           #+#    #+#             */
/*   Updated: 2019/07/20 18:33:48 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		game_over(t_doom *doom, bool win)
{
	//changer m status
	free_game(&doom->game);
	if (win)
		;//Afficher Fin du Jeu
	else
		;//Afficher Game over sur X frames;
	//lancer menu principal
}