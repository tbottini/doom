#include "doom_nukem.h"

/*
**	rearrange les parametre pour que l'on rende les colonnes de gauche a droite
*/
void			reorder(t_arch *arch)
{
	double		tmp;
	int			tmpint;

	if (arch->px.x > arch->px.y)
	{
		tmpint = arch->px.x;
		arch->px.x = arch->px.y;
		arch->px.y = tmpint;
		tmp = arch->depth.x;
		arch->depth.x = arch->depth.y;
		arch->depth.y = tmp;
		tmp = arch->decal.x;
		arch->decal.x = arch->decal.y;
		arch->decal.y = tmp;
		tmp = arch->shift_txtr.x;
		arch->shift_txtr.x = arch->shift_txtr.y;
		arch->shift_txtr.y = tmp;
	}
}


/*
**	fait des coeficient pour rendre les colomnes entre les deux pilier
*/
//zline temporaire pour ne pas refaire un passage pillar_to_pillar
void			pillar_to_pillar(t_arch *arch, t_player *player)
{
	t_fvct2		pillar;
	t_fvct2		pillar_next;
   	t_fvct2		neutre;
   	t_fvct2		coef_surface;
	double		coef_neutre;

	int			start;
	t_borne		borne_tmp;
	t_sector	*sector_tmp;

	static int  i = 0;


	pillar = surface_pillar(arch, player, arch->depth.x);
	pillar_next = surface_pillar(arch, player, arch->depth.y);
	coef_surface.x = coef_diff(pillar.x - pillar_next.x, arch->px);
	coef_surface.y = coef_diff(pillar.y - pillar_next.y, arch->px);
	neutre.x = (double)(arch->sdl->size.y) / arch->depth.x;
	neutre.y = (double)(arch->sdl->size.y) / arch->depth.y;
	coef_neutre = coef_vct(neutre, arch->px);

	start = arch->px.x;
	if (arch->wall->status == PORTAL)
		borne_svg(arch, &borne_tmp);

	while (arch->px.x != arch->px.y)
	{
		i++;
		if (arch->wall->status == WALL)
		{
			if (z_line_buffer(arch, neutre.x, arch->px.x))
				draw_column(arch, pillar);
		}
		else if (arch->wall->status == PORTAL)
		{
			if (zline_portal(arch, borne_tmp.zline, neutre.x, start))
				draw_portal(arch, pillar, &borne_tmp, start);
			//if (z_line_buffer(arch, neutre.x, arch->px.x))
			//{
			//	draw_portal(arch, player, pillar);
			//}
		}
		pillar.x -= coef_surface.x;
		pillar.y -= coef_surface.y;
		neutre.x += coef_neutre;
		arch->px.x++;
		//if (i % 4 == 0)
		//{
		//	sdl_MultiRenderCopy(arch->sdl);
		//	SDL_RenderPresent(arch->sdl->rend);
		//}
	}
	if (arch->wall->status == PORTAL)
	{
		//les borne up et down sont mise
		//on calcul les borne left et right
		//le zline est sauvegarde
		//on sauvegarde le sector
		//printf("arch->borne parent x %f y %f\n", arch->borne.x, arch->borne.y);
		arch->px.x = start;
		set_borne_horizontal(arch);
		//printf("arch->borne child x %f y %f\n", arch->borne.x, arch->borne.y);
		sector_tmp = arch->sector;
		sector_render(arch, player, arch->wall->link);
		arch->sector = sector_tmp;
		borne_load(arch, &borne_tmp, start);
		//printf("arch->borne parent dans le futur x %f y %f\n", arch->borne.x, arch->borne.y);

	}
}

/*
**	les etapes de rendu pour un mur
**	recuperation d'information supplementaire
**	affichage d'un pillier a un autre
*/
void		render_wall(t_arch *arch, t_player *player)
{

	wall_screen_info(arch, player);
	reorder(arch);
	pillar_to_pillar(arch, player);
}
