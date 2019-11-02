/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <magrab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 19:36:28 by magrab            #+#    #+#             */
/*   Updated: 2019/04/27 13:13:03 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

unsigned int	ft_lil_super_atoi(const char *str)
{
	unsigned int ret;

	if (!*str)
		return (0);
	ret = 0;
	while (*str && ft_isdigit(*str))
	{
		ret = ret * 10 + *str - 48;
		str++;
	}
	return (*str ? 0 : ret);
}

void			free_textures_folder(SDL_Texture **txtrs, char **txtrsname)
{
	int tot;

	tot = 0;
	while (txtrs[tot] && tot < MAXTXTRNUMBER)
	{
		SDL_DestroyTexture(txtrs[tot]);
		txtrs[tot] = NULL;
		tot++;
	}
	tot = 0;
	while (txtrsname[tot] && tot < MAXTXTRNUMBER)
	{
		free(txtrsname[tot]);
		txtrsname[tot] = NULL;
		tot++;
	}
}
