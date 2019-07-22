#include "doom_nukem.h"

/*
**	on recupere les information du secteur par rapport au frustum (champs de vision du joueur)
**	on definit un bunch contenant les mur visibles
**	on affiche ce bunch
*/
void				sector_render(t_arch *arch, t_player *player, t_sector *sector)
{
	t_wall			*wall;
	int				i;
	t_wall			*portal_tmp;

	i = 0;
	wall = sector->wall;
	sector_frustum(arch, sector, player);
	arch->sector = sector;
	portal_tmp = arch->wall;
	while (i < sector->len)
	{
		on_frustum(arch, player, wall[i].pillar);
		on_frustum(arch, player, wall[i].next);
		if (((wall[i].pillar->frust || wall[i].next->frust)
			||	borne_in_wall_angle(arch, &wall[i]))
				&& equal_pillar(&wall[i], arch->wall))
		{
			portal_tmp = arch->wall;
			arch->wall = &wall[i];
			render_wall(arch, player);
			arch->wall = portal_tmp;
		}
		i++;
	}
}

void				clear_screen(t_sdl *sdl)
{
	int			i;

	i = 0;
	while (i < sdl->size.x * sdl->size.y)
	{
		sdl->screen[i] = 0;
		i++;
	}
}

/*
**	les etapes de rendu du jeu
**	on initialise arch wall a null
**	(NULL est un signal pour indiquer que le rendu du secteur ne se fait
**		pas a travers un portail)
**	doom_render fait le premier rendu de secteur (celui dans lequel le joueur se trouve)
*/

int					doom_render(t_doom *doom)
{
	int				i;

	i = 0;
	if (debug == 1)
		printf("\n-------start render-------\n");
	doom->game.arch.depth_portal = 0;
	doom->game.arch.wall = NULL;
	draw_borne(&doom->game.arch, RED);
	draw_frustum(&doom->game.arch, SCREEN_ON | FOV_HORI);
	sector_render(&doom->game.arch, &doom->game.player, doom->game.player.stat.sector);
	minimap(doom);
	debug_screen_copy(&doom->game.arch);
	sdl_MultiRenderCopy(&doom->sdl);
	architect_reset(&doom->game.arch);
	clear_screen(&doom->sdl);
	ft_bzero(&doom->game.arch.sc_debug, sizeof(Uint32) * doom->sdl.size.x * doom->sdl.size.y);
	if (debug == 1)
		printf("\n--------------------------\n");
	return (1);
}
