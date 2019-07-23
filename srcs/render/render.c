#include "doom_nukem.h"

/*
**	on recupere les information du secteur par rapport au frustum (champs de vision du joueur)
**	on definit un bunch contenant les mur visibles
**	on affiche ce bunch
*/
void				sector_render(t_arch *arch, t_player *player, t_sector *sector)
{
	t_wall			*wall;
	int				i_wall;
	t_wall			*portal_tmp;
	t_minimap		mini;

	i_wall = 0;
	wall = sector->wall;
	draw_borne(arch, 0xff0000ff);
	sector_frustum(arch, sector, player);
	arch->sector = sector;
	portal_tmp = arch->wall;
	mini = miniinit(arch->sdl);
	while (i_wall < sector->len)
	{
		on_frustum(arch, player, wall[i_wall].pillar);
		on_frustum(arch, player, wall[i_wall].next);
		if ((wall[i_wall].pillar->frust || wall[i_wall].next->frust)
			&& equal_pillar(&wall[i_wall], arch->wall))
		{
			portal_tmp = arch->wall;
			arch->wall = &wall[i_wall];
			render_wall(arch, player);
			arch->wall = portal_tmp;
			//bunch[i_bunch] = &wall[i_wall];
			//i_bunch++;
		}
		else if (borne_in_wall_angle(arch, &wall[i_wall])
			&& equal_pillar(&wall[i_wall], arch->wall))
		{
			portal_tmp = arch->wall;
			arch->wall = &wall[i_wall];
			render_wall(arch, player);
			//mini_draw_wall(arch->wall, player->stat.pos, &mini);//test
			arch->wall = portal_tmp;
			//bunch[i_bunch] = &wall[i_wall];
			//i_bunch++;
		}
		i_wall++;
	}
	//buncherisation(arch, sector, bunch);

	//bunch_comsuption(arch, player, bunch, sector);
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
	t_minimap		mini;
	int				i;

	i = 0;
	if (debug == 1)
		printf("\n-------start render-------\n");
	doom->game.arch.depth_portal = 0;
	doom->game.arch.wall = NULL;
	sector_render(&doom->game.arch, &doom->game.player, doom->game.player.stat.sector);
	mini = miniinit(&doom->sdl);
	minimap(&mini, &doom->game.player);
	debug_screen_copy(&doom->game.arch);
	sdl_MultiRenderCopy(&doom->sdl);
	architect_reset(&doom->game.arch);
	clear_screen(&doom->sdl);
	ft_bzero(&doom->game.arch.sc_debug, sizeof(Uint32) * doom->sdl.size.x * doom->sdl.size.y);
	if (debug == 1)
		printf("\n--------------------------\n");
	return (1);
}
