/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 19:36:28 by tbottini          #+#    #+#             */
/*   Updated: 2019/04/27 13:13:03 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

unsigned int	color_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	return (r << 24 | g << 16 | b << 8 | 255);
}

/*
**void			*listdel(t_list **list)
**{
**	t_list		*tmp;
**
**	while (*list)
**	{
**		tmp = (*list)->next;
**		free((*list)->content);
**		free(*list);
**		*list = tmp;
**	}
**	return (NULL);
**}
**
** t_vct2			*vct2_value(t_vct2 *vct2, int x, int y)
** {
** 	vct2->x = x;
** 	vct2->y = y;
** 	return (vct2);
** }
**
**char			**tab_new(int y)
**{
**	char		**tab;
**
**	tab = (char **)malloc(sizeof(char *) * y);
**	if (!tab)
**		return (NULL);
**	return (tab);
**}
**
**void			lst_del_node(t_list **node)
**{
**	free((*node)->content);
**	free(*node);
**}
*/
