/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   architect.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 16:39:33 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 20:50:35 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARCHITECT_H
# define ARCHITECT_H

# include "sector.h"
# include "screen.h"
# include <stdbool.h>

/*
**	structure principale pour la recursivite
**
**	-le zline va definir les profondeur localement par rapport au secteur
**	-b_down b_up le champ libre de dessin
**	-b_left, b_rigth les borne horizontal de rendu (on ne doit les depasser)
**	-pillar et next sont les coordonnes du portail pour check
**		si un pillier est derriere ou non
**	-sector_svg permet de retablir le secteur quand on a fini la recursion
*/

typedef struct			s_borne
{
	double				*zline;
	uint32_t			*b_down;
	uint32_t			*b_up;
	double				b_left;
	double				b_right;
	t_fvct2				pillar;
	t_fvct2				next;
	t_sector			*sector_svg;
	t_vct2				px_svg;
}						t_borne;

/*
**	structure regroupand les information de rendu
**	a ne pas calculer plusieurs fois entre chaque colonnes
**	-perc_open pourcentage d'ouverture si c'est une porte
**	-open_invert sens d'ouverture de la porte inverse ou non
*/
typedef struct			s_pil_render
{
	t_fvct2				pillar;
	t_fvct2				next;
	t_borne				borne_tmp;
	int					px_start;
	t_fvct2				st_door;
	int					px_inter;
	t_fvct2				inter;
	bool				open_invert;
	double				perc_open;
}						t_pil_render;

/*
**	structure de rendu
**		contient les information sur la surface rendu
**	-le sector dans lequelle elle est
**	-elle meme
**	-la camera et la sdl pour un acce au rendu
**	-le nombre de portail parcouru
**	-pillar next (le pillier et le pillier next) de la surface
**		dans le referentiel de la camera
**	-shift_txtr le pourcentage du mur concerne par les bornes
**	-portal: les informations liees a la limitation
**		du champ de vision par le portail
**	-timestamp le temps qui coule dans le torrent de la vie
**	-render_method les differente methode de rendu de pillier
**		selon le status de la surface concerne
*/

typedef struct			s_arch
{
	t_sector			*sector;
	t_wall				*wall;
	t_camera			*cam;
	t_sdl				*sdl;
	uint16_t			depth_portal;
	t_fvct2				pillar;
	t_fvct2				next;
	t_vct2				px;
	t_fvct2				shift_txtr;
	t_borne				portal;
	uint32_t			timestamp;
	void				(*render_method[5])(struct s_arch*
		, t_pil_render*, double);
}						t_arch;

int						arch_init(t_arch *arch, t_sdl *sdl, t_camera *cam);
void					arch_free(t_arch *arch);
int						is_door(t_arch *arch);

/*
**	backface
*/

int						zline_wall(t_arch *arch, t_pil_render *render_stuff
	, double len_pillar);
int						zline_portal(t_arch *arch, t_pil_render *render_stuff
	, double len_pillar);
int						z_line_buffer(t_arch *arch, double len_pillar, int px);
int						zline_compare(t_arch *arch, double len_pillar, int px);
int						clean_zline(t_arch *arch, double len_pillar, int px);

/*
**	manager
*/

void					architect_reset(t_arch *arch);
void					arch_set_method(t_arch *arch);

/*
**	borne
*/

t_borne					*borne_init(t_borne *borne, int len);
t_borne					*borne_svg(t_arch *arch, t_borne *borne, t_vct2 px);
void					borne_free(t_borne *borne);
void					borne_load(t_arch *arch, t_borne *borne
	, t_vct2 px_draw);
void					borne_reset(t_arch *arch);
void					set_borne_vertical(t_arch *arch, t_vct2 surface
	, int i);
void					set_borne_horizontal(t_arch *arch);
void					borne_svg_vertical(t_arch *arch
	, t_pil_render *render_stuff, t_fvct2 portal_part);
void					borne_secur(t_arch *arch);

#endif
