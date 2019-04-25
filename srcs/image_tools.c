/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 19:35:56 by tbottini          #+#    #+#             */
/*   Updated: 2019/04/25 19:35:58 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		decomp(uint32_t color)
{
	int		composant[4];
	uint32_t	rest;
	int			i;

	i = 3;
	rest = color;
	while (i >= 0)
	{
		composant[i] = rest % 256;
		rest /= 256;
		printf("%d;", composant[i]);
		i--;
	}
	printf("\n");
}

void		print_image(SDL_Surface *png)
{
	uint32_t		*texture;
	int				i;

	i = 0;
	printf("largeur %d hauteur %d\n", png->w, png->h);
	texture = (uint32_t*)png->pixels;
	printf ("r %d g %d b %d\n", texture[0] / (256 * 256 * 256),
			(texture[0] / (256 * 256)) % 256,
			(texture[0] / (256 * 256 * 256)) % (256 * 256));
	decomp(texture[0]);
	while (i < png->w * png->h)
	{
		decomp(texture[i]);
		i++;
	}
	printf("\n");
}
