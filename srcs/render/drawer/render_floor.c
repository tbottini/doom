#include "render.h"
#include "debug.h"
#include "rasterize.h"

/*
**	retourne une intersection avec le sol selon la rotation x du joueur
**	dans le referentiel du monde
**	-vecteur directeur de l'angle (rot.x + fov_vertical / 2)
**	-recuperation de la profondeur avec l'intersection au sol
**	-multiplication de la profondeur avec le ratio de distance avec le pillier pour recuperer
**		la difference sur .y avec l'intersection au sol
**		on a donc la profondeur (z avec l'intersection
								x avec le rapport
								y la hauteur du sol ne change pas)
**	-on change le inter.(x, y) (x et z) pour les passer dans le referentiel du monde
**		avec une rotation inverse du joueur sur y
**		et une translation avec la position du joueur
*/
t_fvct2			frustum_floor_intersection(t_fvct2 *pillar_pos, t_camera *camera, t_fvct2 *len_sector, t_stat *stat)
{
	t_fvct2		angle_vector;
	t_fvct2		inter;

	if (debug == 7)
		printf("fov_ver %f\n", camera->fov_ver);
	angle_vector = fvct2_from_angle((stat->rot.x - 90) * TO_RADIAN - (camera->fov_ver / 2));
	if (debug == 7)
		printf("angle_vector %f %f\n", angle_vector.x, angle_vector.y);
	if (angle_vector.y >= 0)
	{
		if (debug == 7)
			printf("angle_vector.y == 0 pas d'intersection avec le sol\n");
		return ((t_fvct2){0, 0});
	}
	inter.x = len_sector->y / angle_vector.y * angle_vector.x;
	if (debug == 7)
		printf("len_sector.y %f intersection selon x %f\n", len_sector->y, inter.x);
	inter.y = inter.x / pillar_pos->x * pillar_pos->y;
	if (debug == 7)
		printf("pillar_pos .x %f .y %f\ninter .x %f .y %f\n", pillar_pos->x, pillar_pos->y, inter.x, inter.y);
	if (debug_screen == 2)
		b_point_debug(inter, YELLOW);
	return (inter);
}

t_fvct2		fvct2_camera_to_world(t_fvct2 vector_cam, t_stat *stat)
{
	t_fvct2	vector_world;

	vector_world = fvct2_rotation(vector_cam, -(360 - stat->rot.y) * TO_RADIAN);
	vector_world = fvct2_addition(vector_world, *(t_fvct2*)&stat->pos);
	if (debug_screen == 3)
		b_point_debug(vector_world, YELLOW);

	return (vector_world);
}

/*
**	rendu du sol, en dessous du mur coullissant
**	down_px est le px de depart du sol, .x pour la fin du pillar, .y pour la fin de next
*/
void				render_under_floor(t_arch *arch, t_fvct2 len_sector, t_player *player, t_fvct2 down_px)
{
	t_fvct2			inter_camera;
	t_fvct2			inter_world;
	t_verticle		quad[4];
	t_triangle		tri1, tri2;
	t_screen		screen;

	screen = (t_screen){arch->sdl->screen, arch->sdl->size.x, arch->sdl->size.y};

	quad[0].p = (t_fvct3){arch->px.x, down_px.x, arch->pillar.y};
	inter_world = fvct2_camera_to_world(arch->pillar, &player->stat);
	quad[0].texel = sector_get_floor_texel(arch->sector, inter_world);

	quad[1].p = (t_fvct3){arch->px.y, down_px.y, arch->next.y};
	inter_world = fvct2_camera_to_world(arch->next, &player->stat);
	quad[1].texel = sector_get_floor_texel(arch->sector, inter_world);

	//on recupere la position dans le secteur des intersection avec le frustum
	inter_camera = frustum_floor_intersection(&arch->pillar, arch->cam, &len_sector, &player->stat);
	inter_world = fvct2_camera_to_world(inter_camera, &player->stat);
	quad[2].p = (t_fvct3){arch->px.x, arch->portal.b_down[arch->px.x], inter_camera.x};
	quad[2].texel = sector_get_floor_texel(arch->sector, inter_world);

	inter_camera = frustum_floor_intersection(&arch->next, arch->cam, &len_sector, &player->stat);
	inter_world = fvct2_camera_to_world(inter_camera, &player->stat);
	quad[3].p = (t_fvct3){arch->px.y, arch->portal.b_down[arch->px.y], inter_camera.x};
	quad[3].texel = sector_get_floor_texel(arch->sector, inter_world);

	quad_to_triangle_wall(&quad, &tri1, &tri2);
	triangle_show_verticles(&screen, &tri1);
	if (debug == 9)
	{
		printf("print tri1 %f %f\n", tri1.v[0].p.x, tri1.v[0].p.y);
		printf("print tri1 %f %f\n", tri1.v[1].p.x, tri1.v[1].p.y);
	}
	//texture_mapping(sdl, &triangle_divide);
}