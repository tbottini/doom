#include "doom_nukem.h"


/*
**	-on determine avec px.x et px.y les nouvelles bornes de l'ecran
**	-sur le zline on mets sur 0 les pixels ou le portail est plus proche
**	-on ajuste les bornes up et down au debut du portail
**
**	-on lance une recursion sur le render sector avec une definition du portail
**
**	modif render
**	-si un portail de reference est definit dans l'arch
**		on rentre dans le bunch que les pillier qui sont plus loin que le portail de ref
** 		on n'ajoute pas le portail (qui fait partie du secteur) au bunch
**		sinon il y a une recursive
*/


/*
**	recupere le pixel actuel fait une verif si le wall
*/

void			set_bornes(t_arch *arch, t_player *player)
{
	t_fvct2		pillar;
	t_fvct2		pillar_next;
   	t_fvct2		neutre;
   	t_fvct2		coef_surface;
	double		coef_neutre;

	pillar = surface_pillar(arch, player, arch->depth.x);
	pillar_next = surface_pillar(arch, player, arch->depth.y);
	coef_surface.x = coef_diff(pillar.x - pillar_next.x, arch->px);
	coef_surface.y = coef_diff(pillar.y - pillar_next.y, arch->px);
	neutre.x = (double)(arch->sdl->size.y) / arch->depth.x;
	neutre.y = (double)(arch->sdl->size.y) / arch->depth.y;
	coef_neutre = coef_vct(neutre, arch->px);

	while (arch->px.x != arch->px.y)
	{
		if (z_line_buffer(arch, neutre.x, arch->px.x) > 0)
		{
			if (arch->wall->status == WALL)
				draw_column(arch, pillar);
			else if (arch->wall->status == PORTAL_DIRECT)
				draw_portal(arch, player, pillar);
		}
		pillar.x -= coef_surface.x;
		pillar.y -= coef_surface.y;
		neutre.x += coef_neutre;
		arch->px.x++;
	}
}

void		render_portal(t_arch *arch, t_player *player)
{
	wall_screen_info(arch, player);
	reorder(arch);
	//portal_surface(arch, player);
}
