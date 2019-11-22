/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lil_readfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 06:06:17 by magrab            #+#    #+#             */
/*   Updated: 2019/08/13 06:06:18 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		read_one_texture(int fd, SDL_Surface **surf, char **sp)
{
	int			pathlen;
	char		path[512];
	SDL_Surface	*tmp;

	if (read(fd, &pathlen, sizeof(int)) != sizeof(int) ||
			pathlen >= 512 || pathlen <= 0)
		return (-23);
	if (read(fd, path, sizeof(char) * (pathlen + 1))
			!= sizeof(char) * (pathlen + 1))
		return (-24);
	path[pathlen] = '\0';
	if (!(tmp = IMG_Load(path)))
		return (-25);
	if (sp && !(*sp = ft_strdup(path)))
		return (-26);
	*surf = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGBA8888, 0);
	SDL_FreeSurface(tmp);
	if (read(fd, path, sizeof(char)) != sizeof(char) || *path != '\v')
		return (-27);
	return (0);
}

int		read_textures(int fd, SDL_Surface ***surf, t_slen *len, char ***sp)
{
	int			x;
	int			rtn;
	char		**localpath;
	SDL_Surface	**localsurf;

	if (read_balise(fd, "🌅", -2))
		return (-2);
	if (read(fd, &len->nb_txtrs, sizeof(int)) != sizeof(int))
		return (-21);
	if (!(*surf = (SDL_Surface **)malloc(sizeof(SDL_Surface *)
			* (len->nb_txtrs + 1))))
		return (-420);
	if (sp && !(*sp = (char **)malloc(sizeof(char *) * (len->nb_txtrs + 1))))
		return (-421);
	localsurf = *surf;
	localpath = (sp ? *sp : NULL);
	ft_bzero(localsurf, sizeof(SDL_Surface *) * (len->nb_txtrs + 1));
	x = -1;
	while (++x < len->nb_txtrs)
		if ((rtn = read_one_texture(fd, &(localsurf[x]),
				(sp ? &(localpath[x]) : NULL))))
			return (rtn);
	if (read_balise(fd, "🌌", 2))
		return (2);
	return (0);
}

int		read_one_pillar(int fd, t_pillar *pill)
{
	if ((read(fd, &pill->p.x, sizeof(double))) != sizeof(double))
		return (-32);
	if (read(fd, &pill->p.y, sizeof(double)) != sizeof(double))
		return (-33);
	return (0);
}

int		read_pillars(int fd, t_pillar **pillars, t_slen *len)
{
	int		x;
	int		rtn;

	if (read_balise(fd, "⛩", -3))
		return (-3);
	if ((read(fd, &len->nb_pills, sizeof(int)) != sizeof(int))
			|| len->nb_pills < 0)
		return (-31);
	if (!(*pillars = (t_pillar *)malloc(sizeof(t_pillar)
			* (len->nb_pills + 1))))
		return (-421);
	ft_bzero(*pillars, sizeof(t_pillar) * (len->nb_pills + 1));
	x = 0;
	while (x < len->nb_pills)
	{
		if ((rtn = read_one_pillar(fd, &(((*pillars)[x])))))
			return (rtn);
		x++;
	}
	if (read_balise(fd, "💊", 3))
		return (3);
	return (0);
}

int		read_sec_props(int fd, t_game *game, t_sector *sector, t_slen *len)
{
	int x;
	int	nbp;
	int rtn;

	if (read_balise(fd, "🚽", -8))
		return (-8);
	if ((read(fd, &nbp, sizeof(int)) != sizeof(int)))
		return (-81);
	if (!(sector->props = (t_prop *)malloc(sizeof(t_prop) * (nbp + 1))))
		return (-428);
	ft_bzero(sector->props, sizeof(t_prop) * (nbp + 1));
	x = 0;
	while (x < nbp)
	{
		if ((rtn = read_one_prop(fd, game, &(sector->props[x]), len)))
			return (rtn);
		x++;
	}
	sector->len_prop = nbp;
	if (read_balise(fd, "💩", 8))
		return (8);
	return (0);
}
